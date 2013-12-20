/* ============================================================================
 * Copyright (c) 2009, Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2009, Dr. Michael A. Groeber (US Air Force Research Laboratories)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of Michael A. Groeber, Michael A. Jackson, the US Air Force,
 * BlueQuartz Software nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  This code was written under United States Air Force Contract number
 *                           FA8650-07-D-5800
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include "DREAM3DLib/DataContainers/AttributeMatrix.h"

// C Includes

// C++ Includes
#include <iostream>
#include <fstream>

//HDF5 Includes
#include "H5Support/QH5Utilities.h"
#include "H5Support/QH5Lite.h"

// EbsdLib Includes
#include "EbsdLib/EbsdConstants.h"

// DREAM3D Includes
#include "DREAM3DLib/Math/DREAM3DMath.h"
#include "DREAM3DLib/OrientationOps/OrientationOps.h"
#include "DREAM3DLib/Utilities/DREAM3DRandom.h"

#include "DREAM3DLib/HDF5/VTKH5Constants.h"
#include "DREAM3DLib/HDF5/H5DataArrayReader.h"
#include "DREAM3DLib/DataArrays/StatsDataArray.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AttributeMatrix::AttributeMatrix(QVector<size_t> tDims, const QString& name, unsigned int attrType) :
  m_TupleDims(tDims),
  m_Name(name),
  m_Type(attrType)
{

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AttributeMatrix::~AttributeMatrix()
{

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void AttributeMatrix::setType(uint32_t value)
{
  m_Type = value;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
uint32_t AttributeMatrix::getType()
{
  return m_Type;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool AttributeMatrix::doesAttributeArrayExist(const QString& name)
{
  return  m_AttributeArrays.contains(name);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool AttributeMatrix::validateAttributeArraySizes()
{
  int64_t arraySize = 0;
  int64_t matrixSize = getNumTuples();
  for(QMap<QString, IDataArray::Pointer>::iterator iter = m_AttributeArrays.begin(); iter != m_AttributeArrays.end(); ++iter)
  {
    IDataArray::Pointer d = iter.value();
    arraySize = d->getNumberOfTuples();
    if(arraySize != matrixSize)
    {
      return false;
    }
  }
  return true;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int AttributeMatrix::addAttributeArray(const QString& name, IDataArray::Pointer data)
{
  if (data->getName().compare(name) != 0)
  {
    qDebug() << "Adding Attribute Array with different array name than key name" << "\n";
    qDebug() << "Key name: " << name << "\n";
    qDebug() << "Array Name:" << data->getName() << "\n";
    data->setName(name);
  }
  Q_ASSERT(m_NumTuples == data->getNumberOfTuples());

  m_AttributeArrays[name] = data;
  return 0;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
IDataArray::Pointer AttributeMatrix::getAttributeArray(const QString& name)
{
  QMap<QString, IDataArray::Pointer>::iterator it;
  it =  m_AttributeArrays.find(name);
  if ( it == m_AttributeArrays.end() )
  {
    return IDataArray::NullPointer();
  }
  return it.value();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
IDataArray::Pointer AttributeMatrix::removeAttributeArray(const QString& name)
{
  QMap<QString, IDataArray::Pointer>::iterator it;
  it =  m_AttributeArrays.find(name);
  if ( it == m_AttributeArrays.end() )
  {
    return IDataArray::NullPointer();
  }
  IDataArray::Pointer p = it.value();
  m_AttributeArrays.erase(it);
  return p;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool AttributeMatrix::renameAttributeArray(const QString& oldname, const QString& newname)
{
  QMap<QString, IDataArray::Pointer>::iterator it;
  it =  m_AttributeArrays.find(oldname);
  if ( it == m_AttributeArrays.end() )
  {
    return false;
  }
  IDataArray::Pointer p = it.value();
  p->setName(newname);
  removeAttributeArray(oldname);
  addAttributeArray(newname, p);
  return true;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void AttributeMatrix::setTupleDimensions(QVector<size_t> tupleDims)
{
  m_NumTuples = tupleDims[0];
  for(int i = 1; i < tupleDims.size(); i++)
  {
    m_NumTuples = m_NumTuples + tupleDims[i];
    }
    resizeAttributeArrays(m_NumTuples);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
size_t AttributeMatrix::getNumTuples()
{
  return m_NumTuples;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void AttributeMatrix::resizeAttributeArrays(size_t numTuples)
{
  // int success = 0;
  for(QMap<QString, IDataArray::Pointer>::iterator iter = m_AttributeArrays.begin(); iter != m_AttributeArrays.end(); ++iter)
  {
    //std::cout << "Resizing Array '" << (*iter).first << "' : " << success << std::endl;
    IDataArray::Pointer d = iter.value();
    d->resize(numTuples);
  }
  m_NumTuples = numTuples;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void AttributeMatrix::clearAttributeArrays()
{
  m_AttributeArrays.clear();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QList<QString> AttributeMatrix::getAttributeArrayNameList()
{
  QList<QString> keys;
  for(QMap<QString, IDataArray::Pointer>::iterator iter = m_AttributeArrays.begin(); iter != m_AttributeArrays.end(); ++iter)
  {
    keys.push_back( iter.key() );
  }
  return keys;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int AttributeMatrix::getNumAttributeArrays()
{
  return static_cast<int>(m_AttributeArrays.size());
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int AttributeMatrix::writeAttributeArraysToHDF5(hid_t parentId)
{
  int err;
  for(QMap<QString, IDataArray::Pointer>::iterator iter = m_AttributeArrays.begin(); iter != m_AttributeArrays.end(); ++iter)
  {
    IDataArray::Pointer d = iter.value();
    err = d->writeH5Data(parentId);
    if(err < 0)
    {
      return err;
    }
  }
  return 0;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int AttributeMatrix::addAttributeArrayFromHDF5Path(hid_t gid, QString name, bool preflight)
{
  int err = 0;
  QString classType;
  QH5Lite::readStringAttribute(gid, name, DREAM3D::HDF5::ObjectType, classType);
  //   qDebug() << groupName << " Array: " << *iter << " with C++ ClassType of " << classType << "\n";
  IDataArray::Pointer dPtr = IDataArray::NullPointer();

  if(classType.startsWith("DataArray") == true)
  {
    dPtr = H5DataArrayReader::readIDataArray(gid, name, preflight);
    if(preflight == true) dPtr->resize(m_NumTuples);
  }
  else if(classType.compare("StringDataArray") == 0)
  {
    dPtr = H5DataArrayReader::readStringDataArray(gid, name, preflight);
    if(preflight == true) dPtr->resize(m_NumTuples);
  }
  else if(classType.compare("vector") == 0)
  {

  }
  else if(classType.compare("NeighborList<T>") == 0)
  {
    dPtr = H5DataArrayReader::readNeighborListData(gid, name, preflight);
    if(preflight == true) dPtr->resize(m_NumTuples);
  }
  else if ( name.compare(DREAM3D::EnsembleData::Statistics) == 0)
  {
    StatsDataArray::Pointer statsData = StatsDataArray::New();
    statsData->setName(DREAM3D::EnsembleData::Statistics);
    statsData->readH5Data(gid);
    dPtr = statsData;
    if(preflight == true) dPtr->resize(m_NumTuples);
  }

  if (NULL != dPtr.get())
  {
    addAttributeArray(dPtr->getName(), dPtr);
  }

  return err;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int AttributeMatrix::readAttributeArraysFromHDF5(hid_t amGid, bool preflight, QSet<QString>& namesToRead)
{
  int err = 0;

  QList<QString> names;
  QH5Utilities::getGroupObjects(amGid, H5Utilities::H5Support_DATASET | H5Utilities::H5Support_ANY, names);
  //  qDebug() << "Number of Items in " << groupName << " Group: " << names.size() << "\n";
  QString classType;
  for (QList<QString>::iterator iter = names.begin(); iter != names.end(); ++iter)
  {
    QSet<QString>::iterator contains = namesToRead.find(*iter);
    if (contains == namesToRead.end()) { continue; } // Do not read this item if it is NOT in the set of arrays to read
    classType.clear();
    QH5Lite::readStringAttribute(amGid, *iter, DREAM3D::HDF5::ObjectType, classType);
    //   qDebug() << groupName << " Array: " << *iter << " with C++ ClassType of " << classType << "\n";
    IDataArray::Pointer dPtr = IDataArray::NullPointer();

    if(classType.startsWith("DataArray") == true)
    {
      dPtr = H5DataArrayReader::readIDataArray(amGid, *iter, preflight);
    }
    else if(classType.compare("StringDataArray") == 0)
    {
      dPtr = H5DataArrayReader::readStringDataArray(amGid, *iter, preflight);
    }
    else if(classType.compare("vector") == 0)
    {

    }
    else if(classType.compare("NeighborList<T>") == 0)
    {
      dPtr = H5DataArrayReader::readNeighborListData(amGid, *iter, preflight);
    }
    else if ( (*iter).compare(DREAM3D::EnsembleData::Statistics) == 0)
    {
      StatsDataArray::Pointer statsData = StatsDataArray::New();
      statsData->setName(DREAM3D::EnsembleData::Statistics);
      statsData->readH5Data(amGid);
      dPtr = statsData;
    }

    if (NULL != dPtr.get())
    {
      addAttributeArray(dPtr->getName(), dPtr);
    }

  }
  H5Gclose(amGid); // Close the Cell Group
  return err;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString AttributeMatrix::generateXdmfText(const QString& centering, const QString& dataContainerName, const QString& hdfFileName, const uint8_t gridType)
{
  QString xdmfText;
  QString block;
  QTextStream out(&xdmfText);

  for(QMap<QString, IDataArray::Pointer>::iterator iter = m_AttributeArrays.begin(); iter != m_AttributeArrays.end(); ++iter)
  {
    IDataArray::Pointer d = iter.value();
    block = writeXdmfAttributeData(d, centering, dataContainerName, hdfFileName, gridType);
    out << block << "\n";
  }
  return xdmfText;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString AttributeMatrix::writeXdmfAttributeDataHelper(int numComp, const QString& attrType,
                                                      const QString& dataContainerName,
                                                      IDataArray::Pointer array,
                                                      const QString& centering,
                                                      int precision, const QString& xdmfTypeName, const QString& hdfFileName, const uint8_t gridType)
{
  QString buf;
  QTextStream out(&buf);

  QString dimStr = QString::number(array->getNumberOfTuples()) + QString(" ") + QString::number(array->getNumberOfComponents());
  QString dimStrHalf = QString::number(array->getNumberOfTuples()) + QString(" ") + QString::number(array->getNumberOfComponents() / 2);

  if((numComp % 2) == 1)
  {
    out << "    <Attribute Name=\"" << array->getName() << "\" ";
    out << "AttributeType=\"" << attrType << "\" ";
    out << "Center=\"" << centering << "\">" << "\n";
    // Open the <DataItem> Tag
    out << "      <DataItem Format=\"HDF\" Dimensions=\"" << dimStr <<  "\" ";
    out << "NumberType=\"" << xdmfTypeName << "\" " << "Precision=\"" << precision << "\" >" << "\n";
    out << "        " << hdfFileName << ":/DataContainers/" << dataContainerName << "/" << getName() << "/" << array->getName() << "\n";
    out << "      </DataItem>" << "\n";
    out << "    </Attribute>" << "\n" << "\n";
  }
  else
  {
    //First Slab
    out << "    <Attribute Name=\"" << array->getName() << " (Feature 0)\" ";
    out << "AttributeType=\"" << attrType << "\" ";

    out << "Center=\"" << centering << "\">" << "\n";
    // Open the <DataItem> Tag
    out << "      <DataItem ItemType=\"HyperSlab\" Dimensions=\"" << dimStrHalf <<  "\" ";
    out << "Type=\"HyperSlab\" " << "Name=\"" << array->getName() << " (Feature 0)\" >" << "\n";
    out << "        <DataItem Dimensions=\"3 2\" " << "Format=\"XML\" >" << "\n";
    out << "          0        0" << "\n";
    out << "          1        1" << "\n";
    out << "          " << dimStrHalf << " </DataItem>" << "\n";
    out << "\n";
    out << "        <DataItem Format=\"HDF\" Dimensions=\"" << dimStr << "\" " << "NumberType=\"" << xdmfTypeName << "\" " << "Precision=\"" << precision << "\" >" << "\n";

    out << "        " << hdfFileName << ":/DataContainers/" << dataContainerName << "/" << getName() << "/" << array->getName() << "\n";
    out << "        </DataItem>" << "\n";
    out << "      </DataItem>" << "\n";
    out << "    </Attribute>" << "\n" << "\n";

    //Second Slab
    out << "    <Attribute Name=\"" << array->getName() << " (Feature 1)\" ";
    out << "AttributeType=\"" << attrType << "\" ";

    out << "Center=\"" << centering << "\">" << "\n";
    // Open the <DataItem> Tag
    out << "      <DataItem ItemType=\"HyperSlab\" Dimensions=\"" << dimStrHalf <<  "\" ";
    out << "Type=\"HyperSlab\" " << "Name=\"" << array->getName() << " (Feature 1)\" >" << "\n";
    out << "        <DataItem Dimensions=\"3 2\" " << "Format=\"XML\" >" << "\n";
    out << "          0        " << (array->getNumberOfComponents() / 2) << "\n";
    out << "          1        1" << "\n";
    out << "          " << dimStrHalf << " </DataItem>" << "\n";
    out << "\n";
    out << "        <DataItem Format=\"HDF\" Dimensions=\"" << dimStr << "\" " << "NumberType=\"" << xdmfTypeName << "\" " << "Precision=\"" << precision << "\" >" << "\n";
    out << "        " << hdfFileName << ":/DataContainers/" << dataContainerName << "/" << getName() << "/" << array->getName() << "\n";
    out << "        </DataItem>" << "\n";
    out << "      </DataItem>" << "\n";
    out << "    </Attribute>" << "\n" << "\n";
  }
  return buf;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString AttributeMatrix::writeXdmfAttributeData(IDataArray::Pointer array, const QString& centering, const QString& dataContainerName, const QString& hdfFileName, const uint8_t gridType)
{
  QString xdmfText;
  QTextStream out(&xdmfText);

  int precision = 0;
  QString xdmfTypeName;
  array->getXdmfTypeAndSize(xdmfTypeName, precision);
  if (0 == precision)
  {
    out << "<!-- " << array->getName() << " has unkown type or unsupported type or precision for XDMF to understand" << " -->" << "\n";
    return xdmfText;
  }
  int numComp = array->getNumberOfComponents();
  QString attrType = "Scalar";
  if(numComp > 2) { attrType = "Vector"; }

  QString block = writeXdmfAttributeDataHelper(numComp, attrType, dataContainerName, array, centering, precision, xdmfTypeName, hdfFileName, gridType);

  out << block << "\n";

  return xdmfText;
}
