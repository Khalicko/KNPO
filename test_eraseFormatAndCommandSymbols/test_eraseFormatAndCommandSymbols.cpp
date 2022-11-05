#include "pch.h"
#include "CppUnitTest.h"
#include "../Ignat_Knpo/functionsHeader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace testeraseFormatAndCommandSymbols
{
	TEST_CLASS(testeraseFormatAndCommandSymbols)
	{
	public:
		
		TEST_METHOD(TypeTest)
		{

			string origString("this text has\n several strings");
			bool isInPrintOrScan = false;

			string expectedString("this text has several strings");

			string editedString = eraseFormatAndCommandSymbols(origString, isInPrintOrScan);

			Assert::AreEqual(expectedString, editedString);


		};

		TEST_METHOD(SeveralCommandSymbols)
		{

			string origString("this \ntext has\n several\n strings");
			bool isInPrintOrScan = false;

			string expectedString("this text has several strings");

			string editedString = eraseFormatAndCommandSymbols(origString, isInPrintOrScan);

			Assert::AreEqual(expectedString, editedString);


		};

		TEST_METHOD(SeveralDifferentCommandSymbols)
		{

			string origString("this \vtext has\n several strings");
			bool isInPrintOrScan = false;

			string expectedString("this text has several strings");

			string editedString = eraseFormatAndCommandSymbols(origString, isInPrintOrScan);

			Assert::AreEqual(expectedString, editedString);


		};

		TEST_METHOD(CommandSymbolsOnly)
		{

			string origString("\n\n\n");
			bool isInPrintOrScan = false;

			string expectedString("");

			string editedString = eraseFormatAndCommandSymbols(origString, isInPrintOrScan);

			Assert::AreEqual(expectedString, editedString);


		};

		TEST_METHOD(StringInScanOrPrintFunction)
		{

			string origString("year = %dmonth = %d, day = %d");
			bool isInPrintOrScan = true;

			string expectedString("year = month = , day = ");

			string editedString = eraseFormatAndCommandSymbols(origString, isInPrintOrScan);

			Assert::AreEqual(expectedString, editedString);


		};

		TEST_METHOD(FormatSpecifierOnly)
		{

			string origString("%d");
			bool isInPrintOrScan = true;

			string expectedString("");

			string editedString = eraseFormatAndCommandSymbols(origString, isInPrintOrScan);

			Assert::AreEqual(expectedString, editedString);


		};

		TEST_METHOD(FormatSpecifierNotInScanPrintFunction)
		{

			string origString("These are weird letters:%d");
			bool isInPrintOrScan = false;

			string expectedString("These are weird letters:%d");

			string editedString = eraseFormatAndCommandSymbols(origString, isInPrintOrScan);

			Assert::AreEqual(expectedString, editedString);
		};

	};
}
