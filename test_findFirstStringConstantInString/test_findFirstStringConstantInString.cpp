#include "pch.h"
#include "CppUnitTest.h"
#include "../Ignat_Knpo/functionsHeader.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testfindFirstStringConstantInString
{
	TEST_CLASS(testfindFirstStringConstantInString)
	{
	public:
		
		TEST_METHOD(TypeTest)
		{
			string changableString("const char string2[10] = \"string2\";");

			bool isConstantInStringFound = false;


			string expectedString("string2");

			string expectedChangedString(";");

			string actualString = findFirstStringConstantInString(changableString, isConstantInStringFound);

			Assert::AreEqual(expectedString, actualString);
			Assert::AreEqual(expectedChangedString, changableString);

		};

		TEST_METHOD(NoConstsInString)
		{
			string changableString("int a=4;");

			bool isConstantInStringFound = false;


			string expectedString("int a=4;");

			string expectedChangedString("int a=4;");

			string actualString = findFirstStringConstantInString(changableString, isConstantInStringFound);

			Assert::AreEqual(expectedString, actualString);
			Assert::AreEqual(expectedChangedString, changableString);

		};

		TEST_METHOD(CharQuotesInString)
		{
			string changableString("char c ='\"';string(\"int a=4;\");");

			bool isConstantInStringFound = false;


			string expectedString("int a=4;");

			string expectedChangedString(");");

			string actualString = findFirstStringConstantInString(changableString, isConstantInStringFound);

			Assert::AreEqual(expectedString, actualString);
			Assert::AreEqual(expectedChangedString, changableString);

		};

		TEST_METHOD(SeveralQuotesInString)
		{
			string changableString("string c(\"int a=4;\");string b(\"string\");");

			bool isConstantInStringFound = false;


			string expectedString("int a=4;");

			string expectedChangedString(");string b(\"string\");");

			string actualString = findFirstStringConstantInString(changableString, isConstantInStringFound);

			Assert::AreEqual(expectedString, actualString);
			Assert::AreEqual(expectedChangedString, changableString);

		};


	};
}
