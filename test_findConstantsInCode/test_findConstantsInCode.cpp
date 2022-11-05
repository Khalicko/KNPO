#include "pch.h"
#include "CppUnitTest.h"
#include "../Ignat_Knpo/functionsHeader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace testfindConstantsInCode
{
	TEST_CLASS(testfindConstantsInCode)
	{
	public:
		
		TEST_METHOD(TypeTest)
		{

			functionUsedInCode functions[1]; //��� ������������ � ���� �������
			functionUsedInCode outside("-1", 0); //������,���������� ��� ���������,�� ����������� � ��������

			string programCode[10] =

			{ "void main()",
				"{",
			 "const char string1[10] = \"string1\";",
			 "const char string2[10] = \"string2\";",
			 "char string3[20];",
				"}"
			};

			int stringCount = 6; //����� ����� � ����
			int functionsCount = 0; //����� �������,��������� � ����
			errorInfo error; //������ � ����





			int expectedErrorID = -1; //��������� ��� ������
			int expectedErrorStringIndex = -1; //��������� ������ � �������



			short expectedOutsideConstCount = 0; //��������� ����� �������� ��� �������


			int expectedFunctionsCount = 1; //��������� ����� ������� � ����

			//�����: ������ ����������� ��������� 3� ���������� ����� ���������� ����� �������


			string expectedFunctionNames[1] = { "main" };
			short expectedFunctionConstCount[1] = { 2 };
			string expectedConstantNames[1][2] = { "string1", "string2" };

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //��������� �� ��������� � �������� ����� �������
			Assert::AreEqual(expectedErrorID, error.errID); //��������� �� ��������� � �������� ���� ������
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //��������� �� ��������� � �������� ������,���������� ������

			

			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //��������� �� ����� �������� ������� �������

			for (int i = 0; i < expectedOutsideConstCount; i++) 
				//�������� ��������,����������� ��� �������
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//�������� ��������,������������� ��������,� ����� �������
				Assert::AreEqual(expectedFunctionNames[i], functions[i].getFuncName());
				Assert::AreEqual(expectedFunctionConstCount[i], functions[i].getConstantNumber());

				for (int j = 0; j < expectedFunctionConstCount[i]; j++)
				{
					Assert::AreEqual(expectedConstantNames[i][j], functions[i].getConstant(j)->getName());
				}
			}
		};




		TEST_METHOD(NoFunctions)
		{

			functionUsedInCode functions[2]; //��� ������������ � ���� �������
			functionUsedInCode outside("-1", 0); //������,���������� ��� ���������,�� ����������� � ��������

			string programCode[5] =

			{ "int a=4;",
			 "const char string1[10] = \"string1\";",
			 "const char string2[10] = \"string2\";",
				"}"
			};

			int stringCount = 4; //����� ����� � ����
			int functionsCount = 0; //����� �������,��������� � ����

			errorInfo error; //������ � ����

			short expectedOutsideConstCount = 2; //��������� ����� �������� ��� �������


			int expectedFunctionsCount = 0; //��������� ����� ������� � ����


			string outsideConstantNames[2]{ "string1", "string2" };


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //��������� �� ��������� � �������� ����� �������

			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //��������� �� ����� �������� ������� �������

			for (int i = 0; i < expectedOutsideConstCount; i++) //�������� ��������,����������� ��� �������
				
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

		};


		TEST_METHOD(SeveralFunctions)
		{

			functionUsedInCode functions[2]; //��� ������������ � ���� �������
			functionUsedInCode outside("-1", 0); //������,���������� ��� ���������,�� ����������� � ��������

			string programCode[10] =

			{ "void main()",
				"{",
			 "const char string1[10] = \"string1\";",
			 "const char string2[10] = \"string2\";",
				"}",
				"int funcsName()",
				"{",
				"const char string3[10] = \"string3\"",
				"}"
			};

			int stringCount = 9; //����� ����� � ����
			int functionsCount = 0; //����� �������,��������� � ����

			errorInfo error; //������ � ����
			int expectedErrorID = -1; //��������� ��� ������
			int expectedErrorStringIndex = -1; //��������� ������ � �������


			short expectedOutsideConstCount = 0; //��������� ����� �������� ��� �������


			int expectedFunctionsCount = 2; //��������� ����� ������� � ����

			//�����: ������ ����������� ��������� 3� ���������� ����� ���������� ����� �������


			string expectedFunctionNames[2] = { "main","funcsName"};
			short expectedFunctionConstCount[2] = { 2,1 };
			string expectedConstantNames[2][2] = { { "string1", "string2" }, {"string3"}};

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //��������� �� ��������� � �������� ����� �������
			Assert::AreEqual(expectedErrorID, error.errID); //��������� �� ��������� � �������� ���� ������
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //��������� �� ��������� � �������� ������,���������� ������



			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //��������� �� ����� �������� ������� �������

			for (int i = 0; i < expectedOutsideConstCount; i++)
				//�������� ��������,����������� ��� �������
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//�������� ��������,������������� ��������,� ����� �������
				Assert::AreEqual(expectedFunctionNames[i], functions[i].getFuncName());
				Assert::AreEqual(expectedFunctionConstCount[i], functions[i].getConstantNumber());

				for (int j = 0; j < expectedFunctionConstCount[i]; j++)
				{
					Assert::AreEqual(expectedConstantNames[i][j], functions[i].getConstant(j)->getName());
				}
			}
		};

		TEST_METHOD(UnClosedQuote)
		{

			functionUsedInCode functions[1]; //��� ������������ � ���� �������
			functionUsedInCode outside("-1", 0); //������,���������� ��� ���������,�� ����������� � ��������

			string programCode[10] =

			{ "void main()",
				"{",
			 "const char string1[10] = \"string1;",
				"}"
			};

			int stringCount = 4; //����� ����� � ����
			int functionsCount = 0; //����� �������,��������� � ����
			errorInfo error; //������ � ����





			int expectedErrorID = 1; //��������� ��� ������
			int expectedErrorStringIndex = 2; //��������� ������ � �������



			short expectedOutsideConstCount = 0; //��������� ����� �������� ��� �������


			int expectedFunctionsCount = 1; //��������� ����� ������� � ����

			//�����: ������ ����������� ��������� 3� ���������� ����� ���������� ����� �������


			string expectedFunctionNames[1] = { "main" };
			short expectedFunctionConstCount[1] = { };
			string expectedConstantNames[1][2] = {};

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //��������� �� ��������� � �������� ����� �������
			Assert::AreEqual(expectedErrorID, error.errID); //��������� �� ��������� � �������� ���� ������
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //��������� �� ��������� � �������� ������,���������� ������



			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //��������� �� ����� �������� ������� �������

			for (int i = 0; i < expectedOutsideConstCount; i++)
				//�������� ��������,����������� ��� �������
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//�������� ��������,������������� ��������,� ����� �������
				Assert::AreEqual(expectedFunctionNames[i], functions[i].getFuncName());
				Assert::AreEqual(expectedFunctionConstCount[i], functions[i].getConstantNumber());

				for (int j = 0; j < expectedFunctionConstCount[i]; j++)
				{
					Assert::AreEqual(expectedConstantNames[i][j], functions[i].getConstant(j)->getName());
				}
			}
		};

		TEST_METHOD(UnClosedComment)
		{

			functionUsedInCode functions[1]; //��� ������������ � ���� �������
			functionUsedInCode outside("-1", 0); //������,���������� ��� ���������,�� ����������� � ��������

			string programCode[10] =

			{ "void main()",
				"{",
			 "const char string1[10] = \"string1\";",
				"}",
				"/*"
			};

			int stringCount = 5; //����� ����� � ����
			int functionsCount = 0; //����� �������,��������� � ����
			errorInfo error; //������ � ����





			int expectedErrorID = 2; //��������� ��� ������
			int expectedErrorStringIndex = 4; //��������� ������ � �������



			short expectedOutsideConstCount = 0; //��������� ����� �������� ��� �������


			int expectedFunctionsCount = 1; //��������� ����� ������� � ����

			//�����: ������ ����������� ��������� 3� ���������� ����� ���������� ����� �������


			string expectedFunctionNames[1] = { "main" };
			short expectedFunctionConstCount[1] = {1};
			string expectedConstantNames[1][2] = { "string1"};

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //��������� �� ��������� � �������� ����� �������
			Assert::AreEqual(expectedErrorID, error.errID); //��������� �� ��������� � �������� ���� ������
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //��������� �� ��������� � �������� ������,���������� ������



			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //��������� �� ����� �������� ������� �������

			for (int i = 0; i < expectedOutsideConstCount; i++)
				//�������� ��������,����������� ��� �������
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//�������� ��������,������������� ��������,� ����� �������
				Assert::AreEqual(expectedFunctionNames[i], functions[i].getFuncName());
				Assert::AreEqual(expectedFunctionConstCount[i], functions[i].getConstantNumber());

				for (int j = 0; j < expectedFunctionConstCount[i]; j++)
				{
					Assert::AreEqual(expectedConstantNames[i][j], functions[i].getConstant(j)->getName());
				}
			}
		};

		TEST_METHOD(CommandSymbolsInCode)
		{

			functionUsedInCode functions[1]; //��� ������������ � ���� �������
			functionUsedInCode outside("-1", 0); //������,���������� ��� ���������,�� ����������� � ��������

			string programCode[10] =

			{ "void main()",
				"{",
			 "const char string1[10] = \"string1\";",
			 "printf(\"two \nstrings\")",
			 "char string3[20];",
				"}"
			};

			int stringCount = 6; //����� ����� � ����
			int functionsCount = 0; //����� �������,��������� � ����
			errorInfo error; //������ � ����





			int expectedErrorID = -1; //��������� ��� ������
			int expectedErrorStringIndex = -1; //��������� ������ � �������



			short expectedOutsideConstCount = 0; //��������� ����� �������� ��� �������


			int expectedFunctionsCount = 1; //��������� ����� ������� � ����

			//�����: ������ ����������� ��������� 3� ���������� ����� ���������� ����� �������


			string expectedFunctionNames[1] = { "main" };
			short expectedFunctionConstCount[1] = { 2 };
			string expectedConstantNames[1][2] = { "string1", "two strings" };

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //��������� �� ��������� � �������� ����� �������
			Assert::AreEqual(expectedErrorID, error.errID); //��������� �� ��������� � �������� ���� ������
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //��������� �� ��������� � �������� ������,���������� ������



			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //��������� �� ����� �������� ������� �������

			for (int i = 0; i < expectedOutsideConstCount; i++)
				//�������� ��������,����������� ��� �������
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//�������� ��������,������������� ��������,� ����� �������
				Assert::AreEqual(expectedFunctionNames[i], functions[i].getFuncName());
				Assert::AreEqual(expectedFunctionConstCount[i], functions[i].getConstantNumber());

				for (int j = 0; j < expectedFunctionConstCount[i]; j++)
				{
					Assert::AreEqual(expectedConstantNames[i][j], functions[i].getConstant(j)->getName());
				}
			}
		};

		TEST_METHOD(FormatSpecifiersInCode)
		{

			functionUsedInCode functions[1]; //��� ������������ � ���� �������
			functionUsedInCode outside("-1", 0); //������,���������� ��� ���������,�� ����������� � ��������

			string programCode[10] =

			{ "void main()",
				"{",
			 "const char string1[10] = \"string1\";",
			 "printf(\"two plus two is %d\")",
			 "char string3[20];",
				"}"
			};

			int stringCount = 6; //����� ����� � ����
			int functionsCount = 0; //����� �������,��������� � ����
			errorInfo error; //������ � ����





			int expectedErrorID = -1; //��������� ��� ������
			int expectedErrorStringIndex = -1; //��������� ������ � �������



			short expectedOutsideConstCount = 0; //��������� ����� �������� ��� �������


			int expectedFunctionsCount = 1; //��������� ����� ������� � ����

			//�����: ������ ����������� ��������� 3� ���������� ����� ���������� ����� �������


			string expectedFunctionNames[1] = { "main" };
			short expectedFunctionConstCount[1] = { 2 };
			string expectedConstantNames[1][2] = { "string1", "two plus two is " };

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //��������� �� ��������� � �������� ����� �������
			Assert::AreEqual(expectedErrorID, error.errID); //��������� �� ��������� � �������� ���� ������
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //��������� �� ��������� � �������� ������,���������� ������



			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //��������� �� ����� �������� ������� �������

			for (int i = 0; i < expectedOutsideConstCount; i++)
				//�������� ��������,����������� ��� �������
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//�������� ��������,������������� ��������,� ����� �������
				Assert::AreEqual(expectedFunctionNames[i], functions[i].getFuncName());
				Assert::AreEqual(expectedFunctionConstCount[i], functions[i].getConstantNumber());

				for (int j = 0; j < expectedFunctionConstCount[i]; j++)
				{
					Assert::AreEqual(expectedConstantNames[i][j], functions[i].getConstant(j)->getName());
				}
			}
		};

		TEST_METHOD(ConstInComment)
		{

			functionUsedInCode functions[1]; //��� ������������ � ���� �������
			functionUsedInCode outside("-1", 0); //������,���������� ��� ���������,�� ����������� � ��������

			string programCode[10] =

			{ "void main()",
				"{",
			 "//const char string1[10] = \"string1\";",
			 "const char string2[10] = \"string2\";",
			 "char string3[20];",
				"}"
			};

			int stringCount = 6; //����� ����� � ����
			int functionsCount = 0; //����� �������,��������� � ����
			errorInfo error; //������ � ����





			int expectedErrorID = -1; //��������� ��� ������
			int expectedErrorStringIndex = -1; //��������� ������ � �������



			short expectedOutsideConstCount = 0; //��������� ����� �������� ��� �������


			int expectedFunctionsCount = 1; //��������� ����� ������� � ����

			//�����: ������ ����������� ��������� 3� ���������� ����� ���������� ����� �������


			string expectedFunctionNames[1] = { "main" };
			short expectedFunctionConstCount[1] = { 1 };
			string expectedConstantNames[1][1] = { "string2" };

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //��������� �� ��������� � �������� ����� �������
			Assert::AreEqual(expectedErrorID, error.errID); //��������� �� ��������� � �������� ���� ������
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //��������� �� ��������� � �������� ������,���������� ������



			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //��������� �� ����� �������� ������� �������

			for (int i = 0; i < expectedOutsideConstCount; i++)
				//�������� ��������,����������� ��� �������
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//�������� ��������,������������� ��������,� ����� �������
				Assert::AreEqual(expectedFunctionNames[i], functions[i].getFuncName());
				Assert::AreEqual(expectedFunctionConstCount[i], functions[i].getConstantNumber());

				for (int j = 0; j < expectedFunctionConstCount[i]; j++)
				{
					Assert::AreEqual(expectedConstantNames[i][j], functions[i].getConstant(j)->getName());
				}
			}
		};

		TEST_METHOD(ConstInMultiLineComment)
		{

			functionUsedInCode functions[1]; //��� ������������ � ���� �������
			functionUsedInCode outside("-1", 0); //������,���������� ��� ���������,�� ����������� � ��������

			string programCode[10] =

			{ "void main()",
				"{",
			 "/*const char string1[10] = \"string1\";",
				"const char strin3[20] = \"word\" */",
			 "const char string2[10] = \"string2\";",
			 "char string3[20];",
				"}"
			};

			int stringCount = 7; //����� ����� � ����
			int functionsCount = 0; //����� �������,��������� � ����
			errorInfo error; //������ � ����





			int expectedErrorID = -1; //��������� ��� ������
			int expectedErrorStringIndex = -1; //��������� ������ � �������



			short expectedOutsideConstCount = 0; //��������� ����� �������� ��� �������


			int expectedFunctionsCount = 1; //��������� ����� ������� � ����

			//�����: ������ ����������� ��������� 3� ���������� ����� ���������� ����� �������


			string expectedFunctionNames[1] = { "main" };
			short expectedFunctionConstCount[1] = { 1 };
			string expectedConstantNames[1][1] = { "string2" };

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //��������� �� ��������� � �������� ����� �������
			Assert::AreEqual(expectedErrorID, error.errID); //��������� �� ��������� � �������� ���� ������
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //��������� �� ��������� � �������� ������,���������� ������



			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //��������� �� ����� �������� ������� �������

			for (int i = 0; i < expectedOutsideConstCount; i++)
				//�������� ��������,����������� ��� �������
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//�������� ��������,������������� ��������,� ����� �������
				Assert::AreEqual(expectedFunctionNames[i], functions[i].getFuncName());
				Assert::AreEqual(expectedFunctionConstCount[i], functions[i].getConstantNumber());

				for (int j = 0; j < expectedFunctionConstCount[i]; j++)
				{
					Assert::AreEqual(expectedConstantNames[i][j], functions[i].getConstant(j)->getName());
				}
			}
		}

	};

}
