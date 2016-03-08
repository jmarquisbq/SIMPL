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

#include <QtCore/QCoreApplication>

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/SIMPLibVersion.h"
#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/Common/FilterManager.h"
#include "SIMPLib/Common/FilterFactory.hpp"
#include "SIMPLib/Common/FilterPipeline.h"
#include "SIMPLib/Common/TemplateHelpers.hpp"
#include "SIMPLib/Plugin/ISIMPLibPlugin.h"
#include "SIMPLib/Plugin/SIMPLibPluginLoader.h"
#include "SIMPLib/Utilities/UnitTestSupport.hpp"
#include "SIMPLib/Utilities/QMetaObjectUtilities.h"
#include "SIMPLib/FilterParameters/DynamicTableData.h"

#include "SIMPLib/CoreFilters/ArrayCalculator.h"
#include "SIMPLib/CoreFilters/CreateDataArray.h"

#include "SIMPLTestFileLocations.h"

class DummyObserver : public Observer
{
public:
  DummyObserver() : Observer() {}
  virtual ~DummyObserver() {}
  SIMPL_TYPE_MACRO(DummyObserver)

  void processPipelineMessage(const PipelineMessage& pm)
  {
    // Don't do anything...this class only exists to stifle the messages being dumped to the console
  }

private:
  DummyObserver(const DummyObserver&); // Copy Constructor Not Implemented
  void operator=(const DummyObserver&); // Operator '=' Not Implemented
};

class ArrayCalculatorTest
{
public:
  ArrayCalculatorTest() {}
  virtual ~ArrayCalculatorTest() {}
  SIMPL_TYPE_MACRO(ArrayCalculatorTest)

  // -----------------------------------------------------------------------------
  //
  // -----------------------------------------------------------------------------
  FilterPipeline::Pointer createPipeline()
  {
    FilterPipeline::Pointer pipeline = FilterPipeline::New();
    DummyObserver* obs = new DummyObserver();
    pipeline->addMessageReceiver(obs);

    {
      QString filtName = "CreateDataContainer";
      FilterManager* fm = FilterManager::Instance();
      IFilterFactory::Pointer factory = fm->getFactoryForFilter(filtName);
      DREAM3D_REQUIRE(factory.get() != NULL);

      AbstractFilter::Pointer filter = factory->create();
      DREAM3D_REQUIRE(filter.get() != NULL);

      bool propWasSet = false;
      propWasSet = filter->setProperty("CreatedDataContainer", "DataContainer");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      pipeline->pushBack(filter);
    }

    {
      QString filtName = "CreateAttributeMatrix";
      FilterManager* fm = FilterManager::Instance();
      IFilterFactory::Pointer factory = fm->getFactoryForFilter(filtName);
      DREAM3D_REQUIRE(factory.get() != NULL);

      AbstractFilter::Pointer filter = factory->create();
      DREAM3D_REQUIRE(filter.get() != NULL);

      bool propWasSet = false;
      QVariant var;
      DataArrayPath dap("DataContainer", "AttributeMatrix", "");
      var.setValue(dap);
      propWasSet = filter->setProperty("CreatedAttributeMatrix", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      var.setValue(3);
      propWasSet = filter->setProperty("AttributeMatrixType", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      var.setValue(DynamicTableData(std::vector<std::vector<double> >(1, std::vector<double>(1, 10))));
      propWasSet = filter->setProperty("TupleDimensions", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      pipeline->pushBack(filter);
    }

    {
      QString filtName = "CreateAttributeMatrix";
      FilterManager* fm = FilterManager::Instance();
      IFilterFactory::Pointer factory = fm->getFactoryForFilter(filtName);
      DREAM3D_REQUIRE(factory.get() != NULL);

      AbstractFilter::Pointer filter = factory->create();
      DREAM3D_REQUIRE(filter.get() != NULL);

      bool propWasSet = false;
      QVariant var;
      DataArrayPath dap("DataContainer", "NumericMatrix", "");
      var.setValue(dap);
      propWasSet = filter->setProperty("CreatedAttributeMatrix", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      var.setValue(3);
      propWasSet = filter->setProperty("AttributeMatrixType", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      var.setValue(DynamicTableData(std::vector<std::vector<double> >(1, std::vector<double>(1, 1))));
      propWasSet = filter->setProperty("TupleDimensions", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      pipeline->pushBack(filter);
    }

    {
      QString filtName = "CreateDataArray";
      FilterManager* fm = FilterManager::Instance();
      IFilterFactory::Pointer factory = fm->getFactoryForFilter(filtName);
      DREAM3D_REQUIRE(factory.get() != NULL);

      AbstractFilter::Pointer filter = factory->create();
      DREAM3D_REQUIRE(filter.get() != NULL);

      bool propWasSet = false;
      QVariant var;
      DataArrayPath dap("DataContainer", "AttributeMatrix", "Array1");
      var.setValue(dap);
      propWasSet = filter->setProperty("NewArray", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      var.setValue(1);
      propWasSet = filter->setProperty("NumberOfComponents", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      var.setValue(0);
      propWasSet = filter->setProperty("ScalarType", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      var.setValue(1);
      propWasSet = filter->setProperty("InitializationType", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      FPRangePair pair;
      pair.first = -10;
      pair.second = 10;
      var.setValue(pair);
      propWasSet = filter->setProperty("InitializationRange", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      pipeline->pushBack(filter);
    }

    {
      QString filtName = "CreateDataArray";
      FilterManager* fm = FilterManager::Instance();
      IFilterFactory::Pointer factory = fm->getFactoryForFilter(filtName);
      DREAM3D_REQUIRE(factory.get() != NULL);

      AbstractFilter::Pointer filter = factory->create();
      DREAM3D_REQUIRE(filter.get() != NULL);

      bool propWasSet = false;
      QVariant var;
      DataArrayPath dap("DataContainer", "AttributeMatrix", "Array2");
      var.setValue(dap);
      propWasSet = filter->setProperty("NewArray", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      var.setValue(1);
      propWasSet = filter->setProperty("NumberOfComponents", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      var.setValue(8);
      propWasSet = filter->setProperty("ScalarType", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      var.setValue(1);
      propWasSet = filter->setProperty("InitializationType", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      FPRangePair pair;
      pair.first = 0;
      pair.second = 20;
      var.setValue(pair);
      propWasSet = filter->setProperty("InitializationRange", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      pipeline->pushBack(filter);
    }

    return pipeline;
  }

  // -----------------------------------------------------------------------------
  //
  // -----------------------------------------------------------------------------
  void TestArrayCalculatorFilter()
  {
    FilterPipeline::Pointer pipeline = createPipeline();

    QString filtName = "ArrayCalculator";
    FilterManager* fm = FilterManager::Instance();
    IFilterFactory::Pointer factory = fm->getFactoryForFilter(filtName);
    DREAM3D_REQUIRE(factory.get() != NULL);

    AbstractFilter::Pointer filter = factory->create();
    DREAM3D_REQUIRE(filter.get() != NULL);

    pipeline->pushBack(filter);

    QVariant var;
    bool propWasSet = false;

    {
      // Empty Calculated Array Test
      propWasSet = filter->setProperty("InfixEquation", "3");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::EMPTY_CAL_ARRAY);

      // Set the calculated array using the NumericMatrix path
      DataArrayPath dap = DataArrayPath("DataContainer", "NumericMatrix", "NewArray");
      var.setValue(dap);
      propWasSet = filter->setProperty("CalculatedArray", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      // Empty Tests
      propWasSet = filter->setProperty("InfixEquation", "");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::EMPTY_EQUATION);

      propWasSet = filter->setProperty("InfixEquation", "          ");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::EMPTY_EQUATION);

      // Single Value Tests
      propWasSet = filter->setProperty("InfixEquation", "-3");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), 0);
      DREAM3D_REQUIRE_EQUAL(filter->getWarningCondition(), ArrayCalculator::NUMERIC_VALUE_WARNING);

      propWasSet = filter->setProperty("InfixEquation", "14");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), 0);
      DREAM3D_REQUIRE_EQUAL(filter->getWarningCondition(), ArrayCalculator::NUMERIC_VALUE_WARNING);

      // Incomplete Binary Operators Tests
      propWasSet = filter->setProperty("InfixEquation", "3-");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::INVALID_EQUATION);

      propWasSet = filter->setProperty("InfixEquation", "+");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::INVALID_EQUATION);

      propWasSet = filter->setProperty("InfixEquation", "-");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::INVALID_EQUATION);

      propWasSet = filter->setProperty("InfixEquation", "5 - (2+)");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::INVALID_EQUATION);

      // Incomplete Unary Operators Tests
      propWasSet = filter->setProperty("InfixEquation", "cos(-)");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::INVALID_EQUATION);

      propWasSet = filter->setProperty("InfixEquation", "log10()");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::INVALID_EQUATION);

      propWasSet = filter->setProperty("InfixEquation", "abs(+ 3 ^)");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::INVALID_EQUATION);

      propWasSet = filter->setProperty("InfixEquation", "sqrt(* 3 )");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::INVALID_EQUATION);

      propWasSet = filter->setProperty("InfixEquation", "sqrt( 3 /)");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::INVALID_EQUATION);

      // Mismatched Parentheses Tests
      propWasSet = filter->setProperty("InfixEquation", "(3*4)");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), 0);

      propWasSet = filter->setProperty("InfixEquation", "(3*4");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::MISMATCHED_PARENTHESES);

      propWasSet = filter->setProperty("InfixEquation", "3*4)");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::MISMATCHED_PARENTHESES);

      // Nested Unary Operator Tests
      propWasSet = filter->setProperty("InfixEquation", "abs( abs( abs( abs(3)/4) + 7.34)^2)");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), 0);

      propWasSet = filter->setProperty("InfixEquation", "abs( cos( log10( abs(3)/4) - 1)^2)*5");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), 0);

      // Incorrect Number Of Arguments Tests
      propWasSet = filter->setProperty("InfixEquation", "root(3)");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::INVALID_EQUATION);

      propWasSet = filter->setProperty("InfixEquation", "root(3, 5, 2)");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::INVALID_EQUATION);

      propWasSet = filter->setProperty("InfixEquation", "abs(2, -12)");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::INVALID_EQUATION);

      // Set the selected attribute matrix
      dap = DataArrayPath("DataContainer", "AttributeMatrix", "");
      var.setValue(dap);
      propWasSet = filter->setProperty("SelectedAttributeMatrix", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      // Single Array Tests (Force "Incorrect Tuple Count" Error)
      propWasSet = filter->setProperty("InfixEquation", "-Array1");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::INCORRECT_TUPLE_COUNT);

      propWasSet = filter->setProperty("InfixEquation", "Array2");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), ArrayCalculator::INCORRECT_TUPLE_COUNT);

      // Set the new calculated array path
      dap = DataArrayPath("DataContainer", "AttributeMatrix", "NewArray");
      var.setValue(dap);
      propWasSet = filter->setProperty("CalculatedArray", var);
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);

      // Single Array Tests
      propWasSet = filter->setProperty("InfixEquation", "-Array1");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), 0);

      propWasSet = filter->setProperty("InfixEquation", "Array2");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), 0);

      // Binary Operator Tests
      propWasSet = filter->setProperty("InfixEquation", "Array1 + Array2");
      DREAM3D_REQUIRE_EQUAL(propWasSet, true);
      pipeline->execute();
      DREAM3D_REQUIRE_EQUAL(filter->getErrorCondition(), 0);
    }
  }

  // -----------------------------------------------------------------------------
  //
  // -----------------------------------------------------------------------------
  void operator()()
  {
    std::cout << "#### ArrayCalculatorTest Starting ####" << std::endl;
    int err = EXIT_SUCCESS;
    DREAM3D_REGISTER_TEST(TestArrayCalculatorFilter())
  }

private:
  ArrayCalculatorTest(const ArrayCalculatorTest&); // Copy Constructor Not Implemented
  void operator=(const ArrayCalculatorTest&); // Operator '=' Not Implemented
};

