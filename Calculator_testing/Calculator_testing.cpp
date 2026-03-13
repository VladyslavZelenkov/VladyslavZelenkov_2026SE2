#include "pch.h"
#include "CppUnitTest.h"
#include "StringCalculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests
{
    TEST_CLASS(StringCalculatorTests)
    {
    public:
        StringCalculator calc;

        TEST_METHOD(EmptyStringReturnsZero)
        {
            Assert::AreEqual(0, calc.Calculate(""));
        }

        TEST_METHOD(SingleNumberReturnsValue)
        {
            Assert::AreEqual(0, calc.Calculate("0"));
            Assert::AreEqual(1, calc.Calculate("1"));
        }

        TEST_METHOD(MultipleNumbersCommaDelimited)
        {
            Assert::AreEqual(3, calc.Calculate("1,2"));
            Assert::AreEqual(6, calc.Calculate("1,2,3"));
        }

        TEST_METHOD(NumbersOverThousandAreIgnored)
        {
            Assert::AreEqual(3, calc.Calculate("1,10000,2"));
        }

        TEST_METHOD(CustomDelimiterSupport)
        {
            Assert::AreEqual(10, calc.Calculate("\\\\###2###2###6"));
        }

        TEST_METHOD(ThrowsExceptionOnNegative)
        {
            auto func = [this] { calc.Calculate("-2"); };
            Assert::ExpectException<std::runtime_error>(func);
        }

        TEST_METHOD(InvalidInputThrows)
        {
            auto func = [this] { calc.Calculate("abc"); };
            Assert::ExpectException<std::invalid_argument>(func);
        }
    };
}
