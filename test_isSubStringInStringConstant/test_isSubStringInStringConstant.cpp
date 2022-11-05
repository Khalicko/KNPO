#include "pch.h"
#include "CppUnitTest.h"
#include "../Ignat_Knpo/functionsHeader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testisSubStringInStringConstant
{
	TEST_CLASS(testisSubStringInStringConstant)
	{
	public:
		
		TEST_METHOD(TypeTest)
		{
			char string[] = "string s2 (\"one plus one is \" + \"2\")";

			int subStringStartIndex = 16;
			int subStringLength = 4;

			bool expectedSubStringInConstState = true;

			bool actualConstState = isSubStringInStringConstant(string, strlen(string), subStringStartIndex, subStringLength);

			Assert::AreEqual(expectedSubStringInConstState, actualConstState);

		};

		TEST_METHOD(HollowString)
		{
			char string[] = "";

			int subStringStartIndex = 0;
			int subStringLength = 0;

			bool expectedSubStringInConstState = false;

			bool actualConstState = isSubStringInStringConstant(string, strlen(string), subStringStartIndex, subStringLength);

			Assert::AreEqual(expectedSubStringInConstState, actualConstState);

		};

		TEST_METHOD(WrontStringLength)
		{
			char string[] = "string s2 (\"one plus one is \" + \"2\")";

			int subStringStartIndex = 16;
			int subStringLength = 4;

			bool expectedSubStringInConstState = false;

			bool actualConstState = isSubStringInStringConstant(string, -2, subStringStartIndex, subStringLength);

			Assert::AreEqual(expectedSubStringInConstState, actualConstState);

		};

		TEST_METHOD(TooLongSubString)
		{
			char string[] = "string s2 (\"one plus one is \" + \"2\")";

			int subStringStartIndex = 16;
			int subStringLength = 1000;

			bool expectedSubStringInConstState = false;

			bool actualConstState = isSubStringInStringConstant(string, strlen(string), subStringStartIndex, subStringLength);

			Assert::AreEqual(expectedSubStringInConstState, actualConstState);

		};

		TEST_METHOD(NegativeStartIndex)
		{
			char string[] = "string s2 (\"one plus one is \" + \"2\")";

			int subStringStartIndex = -1;
			int subStringLength = 4;

			bool expectedSubStringInConstState = false;

			bool actualConstState = isSubStringInStringConstant(string, strlen(string), subStringStartIndex, subStringLength);

			Assert::AreEqual(expectedSubStringInConstState, actualConstState);

		};

		TEST_METHOD(TooBigStartIndex)
		{
			char string[] = "string s2 (\"one plus one is \" + \"2\")";

			int subStringStartIndex = 1000;
			int subStringLength = 4;

			bool expectedSubStringInConstState = false;

			bool actualConstState = isSubStringInStringConstant(string, strlen(string), subStringStartIndex, subStringLength);

			Assert::AreEqual(expectedSubStringInConstState, actualConstState);

		};

		TEST_METHOD(SubStringExceedsString)
		{
			char string[] = "string s2 (\"one plus one is \" + \"2\")";

			int subStringStartIndex = 16;
			int subStringLength = 25;

			bool expectedSubStringInConstState = false;

			bool actualConstState = isSubStringInStringConstant(string, strlen(string), subStringStartIndex, subStringLength);

			Assert::AreEqual(expectedSubStringInConstState, actualConstState);

		};

		TEST_METHOD(NoStringConstants)
		{
			char string[] = "int a=4+14;";

			int subStringStartIndex = 4;
			int subStringLength = 3;

			bool expectedSubStringInConstState = false;

			bool actualConstState = isSubStringInStringConstant(string, strlen(string), subStringStartIndex, subStringLength);

			Assert::AreEqual(expectedSubStringInConstState, actualConstState);

		};

		TEST_METHOD(QuotesInCharInString)
		{
			char string[] = "string s2 (\"one plus one is \");char character = '\"' ";

			int subStringStartIndex = 16;
			int subStringLength = 4;

			bool expectedSubStringInConstState = true;

			bool actualConstState = isSubStringInStringConstant(string, strlen(string), subStringStartIndex, subStringLength);

			Assert::AreEqual(expectedSubStringInConstState, actualConstState);

		}

	};
}
