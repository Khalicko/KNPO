#include "pch.h"
#include "CppUnitTest.h"
#include "../Ignat_Knpo/functionsHeader.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testgetFunctionName
{
	TEST_CLASS(testgetFunctionName)
	{
	public:
		
		TEST_METHOD(TypeTest)
		{


			string originalString("void main()");

			string expectedName("main");
			string actualName = getFunctionName(originalString);

			Assert::AreEqual(expectedName, actualName);

		};


		TEST_METHOD(NoFunction)
		{


			string originalString("int a=4;");

			string expectedName("int a=4;");
			string actualName = getFunctionName(originalString);

			Assert::AreEqual(expectedName, actualName);

		};

		TEST_METHOD(intFuncType)
		{


			string originalString("int main()");

			string expectedName("main");
			string actualName = getFunctionName(originalString);

			Assert::AreEqual(expectedName, actualName);

		};

		TEST_METHOD(pointerBeforeName)
		{


			string originalString("int * func()");

			string expectedName("func");
			string actualName = getFunctionName(originalString);

			Assert::AreEqual(expectedName, actualName);

		};

		TEST_METHOD(severalWordsType)
		{


			string originalString("long long func()");

			string expectedName("func");
			string actualName = getFunctionName(originalString);

			Assert::AreEqual(expectedName, actualName);

		}

	};
}
