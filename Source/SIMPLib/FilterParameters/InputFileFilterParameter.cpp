/* ============================================================================
* Copyright (c) 2009-2016 BlueQuartz Software, LLC
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
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
* contributors may be used to endorse or promote products derived from this software
* without specific prior written permission.
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
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include "InputFileFilterParameter.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
InputFileFilterParameter::InputFileFilterParameter()
: m_FileExtension("")
, m_FileType("")
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
InputFileFilterParameter::~InputFileFilterParameter() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
InputFileFilterParameter::Pointer InputFileFilterParameter::New(const QString& humanLabel, const QString& propertyName, const QString& defaultValue, Category category,
                                                                const SetterCallbackType& setterCallback, const GetterCallbackType& getterCallback, const QString& fileExtension, const QString& fileType,
                                                                int groupIndex)
{
  InputFileFilterParameter::Pointer ptr = InputFileFilterParameter::New();
  ptr->setHumanLabel(humanLabel);
  ptr->setPropertyName(propertyName);
  ptr->setDefaultValue(defaultValue);
  ptr->setCategory(category);
  ptr->setFileExtension(fileExtension);
  ptr->setFileType(fileType);
  ptr->setGroupIndex(groupIndex);
  ptr->setSetterCallback(setterCallback);
  ptr->setGetterCallback(getterCallback);

  return ptr;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString InputFileFilterParameter::getWidgetType() const
{
  return QString("InputFileWidget");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void InputFileFilterParameter::readJson(const QJsonObject& json)
{
  QJsonValue jsonValue = json[getPropertyName()];
  if(jsonValue.isUndefined())
  {
    jsonValue = json[getLegacyPropertyName()];
  }
  if(!jsonValue.isUndefined() && m_SetterCallback)
  {
    m_SetterCallback(jsonValue.toString(""));
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void InputFileFilterParameter::writeJson(QJsonObject& json)
{
  if(m_GetterCallback)
  {
    json[getPropertyName()] = m_GetterCallback();
  }
}

// -----------------------------------------------------------------------------
InputFileFilterParameter::Pointer InputFileFilterParameter::NullPointer()
{
  return Pointer(static_cast<Self*>(nullptr));
}

// -----------------------------------------------------------------------------
InputFileFilterParameter::Pointer InputFileFilterParameter::New()
{
  Pointer sharedPtr(new(InputFileFilterParameter));
  return sharedPtr;
}

// -----------------------------------------------------------------------------
QString InputFileFilterParameter::getNameOfClass() const
{
  return QString("InputFileFilterParameter");
}

// -----------------------------------------------------------------------------
QString InputFileFilterParameter::ClassName()
{
  return QString("InputFileFilterParameter");
}

// -----------------------------------------------------------------------------
void InputFileFilterParameter::setFileExtension(const QString& value)
{
  m_FileExtension = value;
}

// -----------------------------------------------------------------------------
QString InputFileFilterParameter::getFileExtension() const
{
  return m_FileExtension;
}

// -----------------------------------------------------------------------------
void InputFileFilterParameter::setFileType(const QString& value)
{
  m_FileType = value;
}

// -----------------------------------------------------------------------------
QString InputFileFilterParameter::getFileType() const
{
  return m_FileType;
}

// -----------------------------------------------------------------------------
void InputFileFilterParameter::setSetterCallback(const InputFileFilterParameter::SetterCallbackType& value)
{
  m_SetterCallback = value;
}

// -----------------------------------------------------------------------------
InputFileFilterParameter::SetterCallbackType InputFileFilterParameter::getSetterCallback() const
{
  return m_SetterCallback;
}

// -----------------------------------------------------------------------------
void InputFileFilterParameter::setGetterCallback(const InputFileFilterParameter::GetterCallbackType& value)
{
  m_GetterCallback = value;
}

// -----------------------------------------------------------------------------
InputFileFilterParameter::GetterCallbackType InputFileFilterParameter::getGetterCallback() const
{
  return m_GetterCallback;
}
