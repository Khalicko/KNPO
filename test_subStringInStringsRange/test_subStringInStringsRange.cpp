#include "pch.h"
#include "CppUnitTest.h"
#include "../Ignat_Knpo/functionsHeader.h"
#include "../Ignat_Knpo/constantInFunction.h"
#include "../Ignat_Knpo/functionUsedInCode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestsubStringinStringsRange
{
	TEST_CLASS(TestsubStringinStringsRange)
	{
	public:

		TEST_METHOD(TypeTest)
		{

			char string[MAX_STRING_LENGTH] = "one plus one is two";
			char substring[MAX_STRING_LENGTH] = "one";
			int leftBorderIndex = 0;
			int rightBorderIndex = 18;

			int expectedCount = 2;
			int actualCount = subStringinStringsRange(string, substring, leftBorderIndex, rightBorderIndex);

			Assert::AreEqual(expectedCount, actualCount);
		};

		TEST_METHOD(EmptyString)
		{

			char string[MAX_STRING_LENGTH] = "";
			char substring[MAX_STRING_LENGTH] = "one";
			int leftBorderIndex = 0;
			int rightBorderIndex = 0;

			int expectedCount = 0;
			int actualCount = subStringinStringsRange(string, substring, leftBorderIndex, rightBorderIndex);

			Assert::AreEqual(expectedCount, actualCount);
		};

		TEST_METHOD(SubStringIsOneSymbol)
		{

			char string[MAX_STRING_LENGTH] = "one plus one is two";
			char substring[MAX_STRING_LENGTH] = "o";
			int leftBorderIndex = 0;
			int rightBorderIndex = 18;

			int expectedCount = 3;
			int actualCount = subStringinStringsRange(string, substring, leftBorderIndex, rightBorderIndex);

			Assert::AreEqual(expectedCount, actualCount);
		};

		TEST_METHOD(EmptySubString)
		{

			char string[MAX_STRING_LENGTH] = "one plus one is two";
			char substring[MAX_STRING_LENGTH] = "";
			int leftBorderIndex = 0;
			int rightBorderIndex = 18;

			int expectedCount = 0;
			int actualCount = subStringinStringsRange(string, substring, leftBorderIndex, rightBorderIndex);

			Assert::AreEqual(expectedCount, actualCount);
		};

		TEST_METHOD(NoSubStringInStringRange)
		{

			char string[MAX_STRING_LENGTH] = "one plus one is two";
			char substring[MAX_STRING_LENGTH] = "three";
			int leftBorderIndex = 0;
			int rightBorderIndex = 18;

			int expectedCount = 0;
			int actualCount = subStringinStringsRange(string, substring, leftBorderIndex, rightBorderIndex);

			Assert::AreEqual(expectedCount, actualCount);
		};

		TEST_METHOD(OnlySubStringStartInRange)
		{

			char string[MAX_STRING_LENGTH] = "one plus one is two";
			char substring[MAX_STRING_LENGTH] = "two";
			int leftBorderIndex = 0;
			int rightBorderIndex = 16;

			int expectedCount = 0;
			int actualCount = subStringinStringsRange(string, substring, leftBorderIndex, rightBorderIndex);

			Assert::AreEqual(expectedCount, actualCount);
		};

		TEST_METHOD(OnlySubStringEndInRange)
		{

			char string[MAX_STRING_LENGTH] = "three minus one is two";
			char substring[MAX_STRING_LENGTH] = "three";
			int leftBorderIndex = 1;
			int rightBorderIndex = 21;

			int expectedCount = 0;
			int actualCount = subStringinStringsRange(string, substring, leftBorderIndex, rightBorderIndex);

			Assert::AreEqual(expectedCount, actualCount);
		};

		TEST_METHOD(StringRangeEqualsSubString)
		{

			char string[MAX_STRING_LENGTH] = "one plus one is two";
			char substring[MAX_STRING_LENGTH] = "one plus one is two";
			int leftBorderIndex = 0;
			int rightBorderIndex = 18;

			int expectedCount = 1;
			int actualCount = subStringinStringsRange(string, substring, leftBorderIndex, rightBorderIndex);

			Assert::AreEqual(expectedCount, actualCount);
		};

		TEST_METHOD(StringRangeIsPartOfSubstring)
		{

			char string[MAX_STRING_LENGTH] = "one plus one is two";
			char substring[MAX_STRING_LENGTH] = "one plus one is two";
			int leftBorderIndex = 0;
			int rightBorderIndex = 3;

			int expectedCount = 0;
			int actualCount = subStringinStringsRange(string, substring, leftBorderIndex, rightBorderIndex);

			Assert::AreEqual(expectedCount, actualCount);
		};

		TEST_METHOD(OneSymbolInRange)
		{

			char string[MAX_STRING_LENGTH] = "one plus one is two";
			char substring[MAX_STRING_LENGTH] = "o";
			int leftBorderIndex = 0;
			int rightBorderIndex = 0;

			int expectedCount = 1;
			int actualCount = subStringinStringsRange(string, substring, leftBorderIndex, rightBorderIndex);

			Assert::AreEqual(expectedCount, actualCount);
		};

		TEST_METHOD(LeftBorderFartherThanRight)
		{

			char string[MAX_STRING_LENGTH] = "one plus one is two";
			char substring[MAX_STRING_LENGTH] = "one";
			int leftBorderIndex = 10;
			int rightBorderIndex = 4;

			int expectedCount = 0;
			int actualCount = subStringinStringsRange(string, substring, leftBorderIndex, rightBorderIndex);

			Assert::AreEqual(expectedCount, actualCount);
		};

		TEST_METHOD(BorderIndexLessThanZero)
		{

			char string[MAX_STRING_LENGTH] = "one plus one is two";
			char substring[MAX_STRING_LENGTH] = "one";
			int leftBorderIndex = -1;
			int rightBorderIndex = 18;

			int expectedCount = 0;
			int actualCount = subStringinStringsRange(string, substring, leftBorderIndex, rightBorderIndex);

			Assert::AreEqual(expectedCount, actualCount);
		};

		TEST_METHOD(BorderIndexMoreThanStringLength)
		{

			char string[MAX_STRING_LENGTH] = "one plus one is two";
			char substring[MAX_STRING_LENGTH] = "one";
			int leftBorderIndex = 0;
			int rightBorderIndex = 100;

			int expectedCount = 0;
			int actualCount = subStringinStringsRange(string, substring, leftBorderIndex, rightBorderIndex);

			Assert::AreEqual(expectedCount, actualCount);
		};
	};
}
