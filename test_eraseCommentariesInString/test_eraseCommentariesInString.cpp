#include "pch.h"
#include "CppUnitTest.h"
#include "../Ignat_Knpo/functionsHeader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace testeraseCommentariesInString
{
	TEST_CLASS(testeraseCommentariesInString)
	{
	public:
		
		TEST_METHOD(TypeTest)
		{

			string originalString("Int c=4;//no its 3");
			bool isStringInComment = false;

			string expectedString("Int c=4;");
			bool expectedCommentState = false;

			string actualString = eraseCommentariesInString(originalString, isStringInComment);

			Assert::AreEqual(expectedCommentState, isStringInComment);
			Assert::AreEqual(expectedString, actualString);


		};

		TEST_METHOD(NoCommentaries)
		{

			string originalString("Int c=4;");
			bool isStringInComment = false;

			string expectedString("Int c=4;");
			bool expectedCommentState = false;

			string actualString = eraseCommentariesInString(originalString, isStringInComment);

			Assert::AreEqual(expectedCommentState, isStringInComment);
			Assert::AreEqual(expectedString, actualString);


		};

		TEST_METHOD(MultiLineCommentStart)
		{

			string originalString("Int c=4;/*no its 3");
			bool isStringInComment = false;

			string expectedString("Int c=4;");
			bool expectedCommentState = true;

			string actualString = eraseCommentariesInString(originalString, isStringInComment);

			Assert::AreEqual(expectedCommentState, isStringInComment);
			Assert::AreEqual(expectedString, actualString);


		};

		TEST_METHOD(MultiLineCommentEnd)
		{
			
			string originalString("this is my message*/Int c=4;");
			bool isStringInComment = true;

			string expectedString("Int c=4;");
			bool expectedCommentState = false;

			string actualString = eraseCommentariesInString(originalString, isStringInComment);

			Assert::AreEqual(expectedCommentState, isStringInComment);
			Assert::AreEqual(expectedString, actualString);


		};

		TEST_METHOD(StringInCommentWithoutEnd)
		{

			string originalString("Int c=4;//no its 3");
			bool isStringInComment = true;

			string expectedString("Int c=4;//no its 3");
			bool expectedCommentState = true;

			string actualString = eraseCommentariesInString(originalString, isStringInComment);

			Assert::AreEqual(expectedCommentState, isStringInComment);
			Assert::AreEqual(expectedString, actualString);


		};

		TEST_METHOD(MultiLineCommentEndsAndStart)
		{

			string originalString("Int c=4;/*no its 3*/Int b=4;");
			bool isStringInComment = false;

			string expectedString("Int c=4;Int b=4;");
			bool expectedCommentState = false;

			string actualString = eraseCommentariesInString(originalString, isStringInComment);

			Assert::AreEqual(expectedCommentState, isStringInComment);
			Assert::AreEqual(expectedString, actualString);


		};

		TEST_METHOD(CommentInString)
		{

			string originalString("Int c=4;string newstring(\"//no its 3\")");
			bool isStringInComment = false;

			string expectedString("Int c=4;string newstring(\"//no its 3\")");
			bool expectedCommentState = false;

			string actualString = eraseCommentariesInString(originalString, isStringInComment);

			Assert::AreEqual(expectedCommentState, isStringInComment);
			Assert::AreEqual(expectedString, actualString);


		};
		
		TEST_METHOD(CommentStartsInComment)
		{

			string originalString("Int c=4;// /*no its 3");
			bool isStringInComment = false;

			string expectedString("Int c=4;");
			bool expectedCommentState = false;

			string actualString = eraseCommentariesInString(originalString, isStringInComment);

			Assert::AreEqual(expectedCommentState, isStringInComment);
			Assert::AreEqual(expectedString, actualString);


		};

		TEST_METHOD(SingleCommentInsideMultilineComment)
		{
			
			string originalString("Int c=4;/* // */");
			bool isStringInComment = false;

			string expectedString("Int c=4;");
			bool expectedCommentState = false;

			string actualString = eraseCommentariesInString(originalString, isStringInComment);

			Assert::AreEqual(expectedCommentState, isStringInComment);
			Assert::AreEqual(expectedString, actualString);
		}

	};
}
