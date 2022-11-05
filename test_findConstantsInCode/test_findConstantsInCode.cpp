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

			functionUsedInCode functions[1]; //Все обнаруженные в коде функции
			functionUsedInCode outside("-1", 0); //Объект,содержащий все константы,не находящиеся в функциях

			string programCode[10] =

			{ "void main()",
				"{",
			 "const char string1[10] = \"string1\";",
			 "const char string2[10] = \"string2\";",
			 "char string3[20];",
				"}"
			};

			int stringCount = 6; //Число строк в коде
			int functionsCount = 0; //Число функций,найденных в коде
			errorInfo error; //Ошибки в коде





			int expectedErrorID = -1; //Ожидаемый тип ошибки
			int expectedErrorStringIndex = -1; //Ожидаемая строка с ошибкой



			short expectedOutsideConstCount = 0; //Ожидаемое число констант вне функций


			int expectedFunctionsCount = 1; //Ожидаемое число функций в коде

			//Здесь: первая размерность следующих 3х параметров равна ожидаемому числу функций


			string expectedFunctionNames[1] = { "main" };
			short expectedFunctionConstCount[1] = { 2 };
			string expectedConstantNames[1][2] = { "string1", "string2" };

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //Совпадают ли ожидаемое и реальное число функций
			Assert::AreEqual(expectedErrorID, error.errID); //Совпадают ли ожидаемые и итоговые типы ошибок
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //Совпадают ли ожидаемые и реальные строки,вызывающие ошибки

			

			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //Совпадает ли число констант снаружи функций

			for (int i = 0; i < expectedOutsideConstCount; i++) 
				//Проверка констант,находящихся вне функций
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//Проверка констант,принадлежащих функциям,и самих функций
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

			functionUsedInCode functions[2]; //Все обнаруженные в коде функции
			functionUsedInCode outside("-1", 0); //Объект,содержащий все константы,не находящиеся в функциях

			string programCode[5] =

			{ "int a=4;",
			 "const char string1[10] = \"string1\";",
			 "const char string2[10] = \"string2\";",
				"}"
			};

			int stringCount = 4; //Число строк в коде
			int functionsCount = 0; //Число функций,найденных в коде

			errorInfo error; //Ошибки в коде

			short expectedOutsideConstCount = 2; //Ожидаемое число констант вне функций


			int expectedFunctionsCount = 0; //Ожидаемое число функций в коде


			string outsideConstantNames[2]{ "string1", "string2" };


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //Совпадают ли ожидаемое и реальное число функций

			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //Совпадает ли число констант снаружи функций

			for (int i = 0; i < expectedOutsideConstCount; i++) //Проверка констант,находящихся вне функций
				
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

		};


		TEST_METHOD(SeveralFunctions)
		{

			functionUsedInCode functions[2]; //Все обнаруженные в коде функции
			functionUsedInCode outside("-1", 0); //Объект,содержащий все константы,не находящиеся в функциях

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

			int stringCount = 9; //Число строк в коде
			int functionsCount = 0; //Число функций,найденных в коде

			errorInfo error; //Ошибки в коде
			int expectedErrorID = -1; //Ожидаемый тип ошибки
			int expectedErrorStringIndex = -1; //Ожидаемая строка с ошибкой


			short expectedOutsideConstCount = 0; //Ожидаемое число констант вне функций


			int expectedFunctionsCount = 2; //Ожидаемое число функций в коде

			//Здесь: первая размерность следующих 3х параметров равна ожидаемому числу функций


			string expectedFunctionNames[2] = { "main","funcsName"};
			short expectedFunctionConstCount[2] = { 2,1 };
			string expectedConstantNames[2][2] = { { "string1", "string2" }, {"string3"}};

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //Совпадают ли ожидаемое и реальное число функций
			Assert::AreEqual(expectedErrorID, error.errID); //Совпадают ли ожидаемые и итоговые типы ошибок
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //Совпадают ли ожидаемые и реальные строки,вызывающие ошибки



			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //Совпадает ли число констант снаружи функций

			for (int i = 0; i < expectedOutsideConstCount; i++)
				//Проверка констант,находящихся вне функций
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//Проверка констант,принадлежащих функциям,и самих функций
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

			functionUsedInCode functions[1]; //Все обнаруженные в коде функции
			functionUsedInCode outside("-1", 0); //Объект,содержащий все константы,не находящиеся в функциях

			string programCode[10] =

			{ "void main()",
				"{",
			 "const char string1[10] = \"string1;",
				"}"
			};

			int stringCount = 4; //Число строк в коде
			int functionsCount = 0; //Число функций,найденных в коде
			errorInfo error; //Ошибки в коде





			int expectedErrorID = 1; //Ожидаемый тип ошибки
			int expectedErrorStringIndex = 2; //Ожидаемая строка с ошибкой



			short expectedOutsideConstCount = 0; //Ожидаемое число констант вне функций


			int expectedFunctionsCount = 1; //Ожидаемое число функций в коде

			//Здесь: первая размерность следующих 3х параметров равна ожидаемому числу функций


			string expectedFunctionNames[1] = { "main" };
			short expectedFunctionConstCount[1] = { };
			string expectedConstantNames[1][2] = {};

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //Совпадают ли ожидаемое и реальное число функций
			Assert::AreEqual(expectedErrorID, error.errID); //Совпадают ли ожидаемые и итоговые типы ошибок
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //Совпадают ли ожидаемые и реальные строки,вызывающие ошибки



			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //Совпадает ли число констант снаружи функций

			for (int i = 0; i < expectedOutsideConstCount; i++)
				//Проверка констант,находящихся вне функций
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//Проверка констант,принадлежащих функциям,и самих функций
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

			functionUsedInCode functions[1]; //Все обнаруженные в коде функции
			functionUsedInCode outside("-1", 0); //Объект,содержащий все константы,не находящиеся в функциях

			string programCode[10] =

			{ "void main()",
				"{",
			 "const char string1[10] = \"string1\";",
				"}",
				"/*"
			};

			int stringCount = 5; //Число строк в коде
			int functionsCount = 0; //Число функций,найденных в коде
			errorInfo error; //Ошибки в коде





			int expectedErrorID = 2; //Ожидаемый тип ошибки
			int expectedErrorStringIndex = 4; //Ожидаемая строка с ошибкой



			short expectedOutsideConstCount = 0; //Ожидаемое число констант вне функций


			int expectedFunctionsCount = 1; //Ожидаемое число функций в коде

			//Здесь: первая размерность следующих 3х параметров равна ожидаемому числу функций


			string expectedFunctionNames[1] = { "main" };
			short expectedFunctionConstCount[1] = {1};
			string expectedConstantNames[1][2] = { "string1"};

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //Совпадают ли ожидаемое и реальное число функций
			Assert::AreEqual(expectedErrorID, error.errID); //Совпадают ли ожидаемые и итоговые типы ошибок
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //Совпадают ли ожидаемые и реальные строки,вызывающие ошибки



			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //Совпадает ли число констант снаружи функций

			for (int i = 0; i < expectedOutsideConstCount; i++)
				//Проверка констант,находящихся вне функций
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//Проверка констант,принадлежащих функциям,и самих функций
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

			functionUsedInCode functions[1]; //Все обнаруженные в коде функции
			functionUsedInCode outside("-1", 0); //Объект,содержащий все константы,не находящиеся в функциях

			string programCode[10] =

			{ "void main()",
				"{",
			 "const char string1[10] = \"string1\";",
			 "printf(\"two \nstrings\")",
			 "char string3[20];",
				"}"
			};

			int stringCount = 6; //Число строк в коде
			int functionsCount = 0; //Число функций,найденных в коде
			errorInfo error; //Ошибки в коде





			int expectedErrorID = -1; //Ожидаемый тип ошибки
			int expectedErrorStringIndex = -1; //Ожидаемая строка с ошибкой



			short expectedOutsideConstCount = 0; //Ожидаемое число констант вне функций


			int expectedFunctionsCount = 1; //Ожидаемое число функций в коде

			//Здесь: первая размерность следующих 3х параметров равна ожидаемому числу функций


			string expectedFunctionNames[1] = { "main" };
			short expectedFunctionConstCount[1] = { 2 };
			string expectedConstantNames[1][2] = { "string1", "two strings" };

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //Совпадают ли ожидаемое и реальное число функций
			Assert::AreEqual(expectedErrorID, error.errID); //Совпадают ли ожидаемые и итоговые типы ошибок
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //Совпадают ли ожидаемые и реальные строки,вызывающие ошибки



			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //Совпадает ли число констант снаружи функций

			for (int i = 0; i < expectedOutsideConstCount; i++)
				//Проверка констант,находящихся вне функций
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//Проверка констант,принадлежащих функциям,и самих функций
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

			functionUsedInCode functions[1]; //Все обнаруженные в коде функции
			functionUsedInCode outside("-1", 0); //Объект,содержащий все константы,не находящиеся в функциях

			string programCode[10] =

			{ "void main()",
				"{",
			 "const char string1[10] = \"string1\";",
			 "printf(\"two plus two is %d\")",
			 "char string3[20];",
				"}"
			};

			int stringCount = 6; //Число строк в коде
			int functionsCount = 0; //Число функций,найденных в коде
			errorInfo error; //Ошибки в коде





			int expectedErrorID = -1; //Ожидаемый тип ошибки
			int expectedErrorStringIndex = -1; //Ожидаемая строка с ошибкой



			short expectedOutsideConstCount = 0; //Ожидаемое число констант вне функций


			int expectedFunctionsCount = 1; //Ожидаемое число функций в коде

			//Здесь: первая размерность следующих 3х параметров равна ожидаемому числу функций


			string expectedFunctionNames[1] = { "main" };
			short expectedFunctionConstCount[1] = { 2 };
			string expectedConstantNames[1][2] = { "string1", "two plus two is " };

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //Совпадают ли ожидаемое и реальное число функций
			Assert::AreEqual(expectedErrorID, error.errID); //Совпадают ли ожидаемые и итоговые типы ошибок
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //Совпадают ли ожидаемые и реальные строки,вызывающие ошибки



			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //Совпадает ли число констант снаружи функций

			for (int i = 0; i < expectedOutsideConstCount; i++)
				//Проверка констант,находящихся вне функций
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//Проверка констант,принадлежащих функциям,и самих функций
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

			functionUsedInCode functions[1]; //Все обнаруженные в коде функции
			functionUsedInCode outside("-1", 0); //Объект,содержащий все константы,не находящиеся в функциях

			string programCode[10] =

			{ "void main()",
				"{",
			 "//const char string1[10] = \"string1\";",
			 "const char string2[10] = \"string2\";",
			 "char string3[20];",
				"}"
			};

			int stringCount = 6; //Число строк в коде
			int functionsCount = 0; //Число функций,найденных в коде
			errorInfo error; //Ошибки в коде





			int expectedErrorID = -1; //Ожидаемый тип ошибки
			int expectedErrorStringIndex = -1; //Ожидаемая строка с ошибкой



			short expectedOutsideConstCount = 0; //Ожидаемое число констант вне функций


			int expectedFunctionsCount = 1; //Ожидаемое число функций в коде

			//Здесь: первая размерность следующих 3х параметров равна ожидаемому числу функций


			string expectedFunctionNames[1] = { "main" };
			short expectedFunctionConstCount[1] = { 1 };
			string expectedConstantNames[1][1] = { "string2" };

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //Совпадают ли ожидаемое и реальное число функций
			Assert::AreEqual(expectedErrorID, error.errID); //Совпадают ли ожидаемые и итоговые типы ошибок
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //Совпадают ли ожидаемые и реальные строки,вызывающие ошибки



			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //Совпадает ли число констант снаружи функций

			for (int i = 0; i < expectedOutsideConstCount; i++)
				//Проверка констант,находящихся вне функций
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//Проверка констант,принадлежащих функциям,и самих функций
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

			functionUsedInCode functions[1]; //Все обнаруженные в коде функции
			functionUsedInCode outside("-1", 0); //Объект,содержащий все константы,не находящиеся в функциях

			string programCode[10] =

			{ "void main()",
				"{",
			 "/*const char string1[10] = \"string1\";",
				"const char strin3[20] = \"word\" */",
			 "const char string2[10] = \"string2\";",
			 "char string3[20];",
				"}"
			};

			int stringCount = 7; //Число строк в коде
			int functionsCount = 0; //Число функций,найденных в коде
			errorInfo error; //Ошибки в коде





			int expectedErrorID = -1; //Ожидаемый тип ошибки
			int expectedErrorStringIndex = -1; //Ожидаемая строка с ошибкой



			short expectedOutsideConstCount = 0; //Ожидаемое число констант вне функций


			int expectedFunctionsCount = 1; //Ожидаемое число функций в коде

			//Здесь: первая размерность следующих 3х параметров равна ожидаемому числу функций


			string expectedFunctionNames[1] = { "main" };
			short expectedFunctionConstCount[1] = { 1 };
			string expectedConstantNames[1][1] = { "string2" };

			string outsideConstantNames[2];


			findConstantsInCode(programCode, stringCount, functions, &outside, functionsCount, error);

			Assert::AreEqual(expectedFunctionsCount, functionsCount); //Совпадают ли ожидаемое и реальное число функций
			Assert::AreEqual(expectedErrorID, error.errID); //Совпадают ли ожидаемые и итоговые типы ошибок
			Assert::AreEqual(expectedErrorStringIndex, error.errStringIND); //Совпадают ли ожидаемые и реальные строки,вызывающие ошибки



			Assert::AreEqual(expectedOutsideConstCount, outside.getConstantNumber()); //Совпадает ли число констант снаружи функций

			for (int i = 0; i < expectedOutsideConstCount; i++)
				//Проверка констант,находящихся вне функций
				Assert::AreEqual(outsideConstantNames[i], outside.getConstant(i)->getName());

			for (int i = 0; i < expectedFunctionsCount; i++)
			{
				//Проверка констант,принадлежащих функциям,и самих функций
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
