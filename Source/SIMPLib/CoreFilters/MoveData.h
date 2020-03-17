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


#pragma once

#include <memory>

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/Filtering/AbstractFilter.h"

/**
 * @brief The MoveData class. See [Filter documentation](@ref movedata) for details.
 */
class SIMPLib_EXPORT MoveData : public AbstractFilter
{
    Q_OBJECT

#ifdef SIMPL_ENABLE_PYTHON
    PYB11_CREATE_BINDINGS(MoveData SUPERCLASS AbstractFilter)
    PYB11_SHARED_POINTERS(MoveData)
    PYB11_FILTER_NEW_MACRO(MoveData)
    PYB11_FILTER_PARAMETER(int, WhatToMove)
    PYB11_FILTER_PARAMETER(DataArrayPath, DataContainerDestination)
    PYB11_FILTER_PARAMETER(DataArrayPath, AttributeMatrixSource)
    PYB11_FILTER_PARAMETER(DataArrayPath, AttributeMatrixDestination)
    PYB11_FILTER_PARAMETER(DataArrayPath, DataArraySource)
    PYB11_PROPERTY(int WhatToMove READ getWhatToMove WRITE setWhatToMove)
    PYB11_PROPERTY(DataArrayPath DataContainerDestination READ getDataContainerDestination WRITE setDataContainerDestination)
    PYB11_PROPERTY(DataArrayPath AttributeMatrixSource READ getAttributeMatrixSource WRITE setAttributeMatrixSource)
    PYB11_PROPERTY(DataArrayPath AttributeMatrixDestination READ getAttributeMatrixDestination WRITE setAttributeMatrixDestination)
    PYB11_PROPERTY(DataArrayPath DataArraySource READ getDataArraySource WRITE setDataArraySource)
#endif

  public:
    using Self = MoveData;
    using Pointer = std::shared_ptr<Self>;
    using ConstPointer = std::shared_ptr<const Self>;
    using WeakPointer = std::weak_ptr<Self>;
    using ConstWeakPointer = std::weak_ptr<const Self>;
    static Pointer NullPointer();

    static std::shared_ptr<MoveData> New();

    /**
     * @brief Returns the name of the class for MoveData
     */
    QString getNameOfClass() const override;
    /**
     * @brief Returns the name of the class for MoveData
     */
    static QString ClassName();

    ~MoveData() override;

    /**
     * @brief Setter property for WhatToMove
     */
    void setWhatToMove(int value);
    /**
     * @brief Getter property for WhatToMove
     * @return Value of WhatToMove
     */
    int getWhatToMove() const;

    Q_PROPERTY(int WhatToMove READ getWhatToMove WRITE setWhatToMove)

    /**
     * @brief Setter property for DataContainerDestination
     */
    void setDataContainerDestination(const DataArrayPath& value);
    /**
     * @brief Getter property for DataContainerDestination
     * @return Value of DataContainerDestination
     */
    DataArrayPath getDataContainerDestination() const;

    Q_PROPERTY(DataArrayPath DataContainerDestination READ getDataContainerDestination WRITE setDataContainerDestination)

    /**
     * @brief Setter property for AttributeMatrixSource
     */
    void setAttributeMatrixSource(const DataArrayPath& value);
    /**
     * @brief Getter property for AttributeMatrixSource
     * @return Value of AttributeMatrixSource
     */
    DataArrayPath getAttributeMatrixSource() const;

    Q_PROPERTY(DataArrayPath AttributeMatrixSource READ getAttributeMatrixSource WRITE setAttributeMatrixSource)

    /**
     * @brief Setter property for AttributeMatrixDestination
     */
    void setAttributeMatrixDestination(const DataArrayPath& value);
    /**
     * @brief Getter property for AttributeMatrixDestination
     * @return Value of AttributeMatrixDestination
     */
    DataArrayPath getAttributeMatrixDestination() const;

    Q_PROPERTY(DataArrayPath AttributeMatrixDestination READ getAttributeMatrixDestination WRITE setAttributeMatrixDestination)

    /**
     * @brief Setter property for DataArraySource
     */
    void setDataArraySource(const DataArrayPath& value);
    /**
     * @brief Getter property for DataArraySource
     * @return Value of DataArraySource
     */
    DataArrayPath getDataArraySource() const;

    Q_PROPERTY(DataArrayPath DataArraySource READ getDataArraySource WRITE setDataArraySource)

    /**
     * @brief getCompiledLibraryName Reimplemented from @see AbstractFilter class
     */
    QString getCompiledLibraryName() const override;

    /**
     * @brief getBrandingString Returns the branding string for the filter, which is a tag
     * used to denote the filter's association with specific plugins
     * @return Branding string
     */
    QString getBrandingString() const override;

    /**
     * @brief getFilterVersion Returns a version string for this filter. Default
     * value is an empty string.
     * @return
     */
    QString getFilterVersion() const override;

    /**
     * @brief newFilterInstance Reimplemented from @see AbstractFilter class
     */
    AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters) const override;

    /**
     * @brief getGroupName Reimplemented from @see AbstractFilter class
     */
    QString getGroupName() const override;

    /**
     * @brief getSubGroupName Reimplemented from @see AbstractFilter class
     */
    QString getSubGroupName() const override;

    /**
     * @brief getUuid Return the unique identifier for this filter.
     * @return A QUuid object.
     */
    QUuid getUuid() const override;

    /**
     * @brief getHumanLabel Reimplemented from @see AbstractFilter class
     */
    QString getHumanLabel() const override;

    /**
     * @brief setupFilterParameters Reimplemented from @see AbstractFilter class
     */
    void setupFilterParameters() override;

    /**
     * @brief readFilterParameters Reimplemented from @see AbstractFilter class
     */
    void readFilterParameters(AbstractFilterParametersReader* reader, int index) override;

    /**
     * @brief execute Reimplemented from @see AbstractFilter class
     */
    void execute() override;


  protected:
    MoveData();

    /**
     * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
     */
    void dataCheck() override;

    /**
     * @brief Initializes all the private instance variables.
     */
    void initialize();

  public:
    MoveData(const MoveData&) = delete;       // Copy Constructor Not Implemented
    MoveData(MoveData&&) = delete;            // Move Constructor Not Implemented
    MoveData& operator=(const MoveData&) = delete; // Copy Assignment Not Implemented
    MoveData& operator=(MoveData&&) = delete;      // Move Assignment Not Implemented

  private:
    int m_WhatToMove = {};
    DataArrayPath m_DataContainerDestination = {};
    DataArrayPath m_AttributeMatrixSource = {};
    DataArrayPath m_AttributeMatrixDestination = {};
    DataArrayPath m_DataArraySource = {};
};

