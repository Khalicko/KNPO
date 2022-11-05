#include "constantInFunction.h"
#include "functionsHeader.h"
#include "Header.h"
#include "functionUsedInCode.h"
#include <fstream>
#include <string>
#pragma warning(disable:4996)

int main(const int argc, char* argv[])
{
	using namespace std;
	setlocale(LC_ALL, "ru");


	//----------ПРОВЕРКА ОШИБОК РАБОТЫ С ФАЙЛАМИ----------

	//Выдать ошибку, если входной файл не указан в аргументах командной строки
	if (argc == 1)
	{
		cout << "Неверно указан файл с входными данными. Возможно, файл по указанному расположению не существует.\n";
		return 1;
	}
	//Выдать ошибку, если выходной файл не указан в аргументах командной строки
	if (argc == 2)
	{
		cout << "Неверно указан файл с выходными данными. Возможно, файл по указанному расположению не существует.\n";
		return 2;
	}


	ifstream inputFile;	//Файл ввода
	inputFile.open(argv[1]);
	if (!inputFile.is_open()) //Выдать ошибку,если входной файл невозможно открыть
	{
		cout << "Невозможно открыть файл с входными данными. Возможно,файл имеет неправильное расширение.";
		return 3;
	}

	ofstream outputFile;	//Файл вывода
	outputFile.open(argv[2], ofstream::app);
	if (!outputFile.is_open()) //Выдать ошибку,если выходной файл невозможно открыть
	{
		cout << "Невозможно открыть файл с выходными данными. Возможно,файл имеет неправильное расширение.";
		return 4;
	}
	else
		outputFile.trunc;


	//Ввод кода программы из файла

		std::string programCode[MAX_STRING_NUMBER]; //Код проверяемой программы
		int stringCount = 0; //Число строк в коде программы

		while (!inputFile.eof() && stringCount <= MAX_STRING_NUMBER)
		{
			getline(inputFile, programCode[stringCount]); //Скопировать строку в массив
			cout << programCode[stringCount] << "\n";
			stringCount++; //Увеличить счётчик числа строк кода
		}





	//----------АНАЛИЗ КОДА ПРОГРАММЫ И ПОИСК КОНСТАНТ----------

	functionUsedInCode functions[MAX_FUNCTIONS_NUMBER]; //Все обнаруженные в коде функции
	functionUsedInCode outside("-1", 0); //Объект,содержащий все константы,не находящиеся в функциях
	outside.completeFunction(stringCount);

	int functionsCount = 0; //Число найденных функций

	errorInfo errorInCode; //Структура для ошибок в коде
	findConstantsInCode(programCode, stringCount, functions, &outside,functionsCount,errorInCode);




		//-----------ПОДВЕДЕНИЕ РЕЗУЛЬТАТОВ----------

	//Если под конец текста комментарий не кончился, ВЫДАТЬ ОШИБКУ


	if (errorInCode.errID == 2)
	{
		outputFile << "Некорректные входные данные:\n";
		outputFile.write("Не закрыт многострочный комментарий в строке ", 46);


		string tempString = std::to_string(errorInCode.errStringIND);
		char c_tempString[MAX_STRING_LENGTH];
		strcpy(c_tempString, tempString.c_str());
		outputFile.write(c_tempString, strlen(c_tempString));

		return 2;
	}

	if (errorInCode.errID == 1)
	{
		outputFile << "Некорректные входные данные:\n";
		outputFile.write("Не закрыта строковая константа в строке ", 41);


		string tempString = std::to_string(errorInCode.errStringIND);
		char c_tempString[MAX_STRING_LENGTH];
		strcpy(c_tempString, tempString.c_str());
		outputFile.write(c_tempString, strlen(c_tempString));

		return 1;
	}

	bool isMainFound = false;
	bool areAllFunctionsCorrect = true;
	bool areConstantsFound = false;
	string incorrectFunctionName = "-";

	for (int i = 0; i < functionsCount; i++)
	{
	
		/* СРЕДСТВА ОТЛАДКИ УДАЛИТЬ
		string newStr = functions[i].getFuncName();
		char amog[MAX_STRING_LENGTH];
		strcpy(amog, newStr.c_str());
		outputFile.write(amog, strlen(amog));
		outputFile.write("\n", 1);
		*/


		if (functions[i].getFuncName() == std::string("Main") || functions[i].getFuncName() == std::string("main"))
			isMainFound = true;

		if (functions[i].getConstantNumber() != 0)
			areConstantsFound = true;


		if (functions[i].getCompletionState() == false)
		{
			areAllFunctionsCorrect = false;
			incorrectFunctionName = functions[i].getFuncName();
		}
	}

	if (isMainFound == false)
	{
		outputFile << "Некорректные входные данные: \nотсутствует главная функция main()\n";
		return 0;
	}
	else if (areAllFunctionsCorrect == false)
	{
		outputFile << "Некорректные входные данные: \nотсутствует определение функции " << incorrectFunctionName;
		return 0;
	}

	if (areConstantsFound == false && outside.getConstantNumber() == 0)
	{
		outputFile << "В программе отсутствуют строковые константы!";
		return 0;
	}
	


	else //Если в коде программы есть строковые константы
	{
		outputFile.trunc; //Очистить выходной файл от предыдущих данных

		//Выписать все строковые константы,не находящиеся внутри функций
		{
			outputFile.write("Вне пределов функций:\n", 22);

			if (outside.getConstantNumber() == 0) //Если вне функций нет строковых констант:
				outputFile.write("Строковые константы не найдены!\n", 33);
			else
				for (int i = 0; i < outside.getConstantNumber(); i++) //Иначе для каждой константы:
				{
					//Выписать имя константы,добавив перенос строки после него...

						char curString[MAX_STRING_LENGTH]; //c-str версия имени константы
						strcpy(curString,outside.getConstant(i)->getName().c_str());
						outputFile.write(curString,strlen(curString));
						outputFile.write("\n\n", 2);


					//Выписать все строки,в которых встречается константа

						short constNumber = outside.getConstantNumber();
						for (short j = 0; j < constNumber; j++) //Для каждой строки,на которой встречается константа:
						{
							//Преобразовать номер строки в строковый тип
								short indexOfString = outside.getConstant(i)->getAppearingString(j); 
								string tempString = std::to_string(indexOfString);
								char curString[MAX_STRING_LENGTH];
								strcpy(curString,tempString.c_str());

							//Выписать номер строки и перенести на новую строку
								outputFile.write(curString, strlen(curString));
								outputFile.write("\n\n", 2);
						}
				}



		}

		
		
		//Выписать список функций и все строковые константы,находящиеся внутри них
		{
			//Для каждой найденной функции:
			for (int i = 0; i < functionsCount; i++)
			{
				char c_str_name[MAX_STRING_LENGTH]; 
				strcpy(c_str_name,functions[i].getFuncName().c_str());

				//Выписать на новую строку название функции
					outputFile.write(c_str_name, strlen(c_str_name));
					outputFile.write(":", 1);
					outputFile.write("\n", 1);


				//Написать,что функция не имеет строковых констант,если они не обнаружены в теле функции
				if (functions[i].getConstantNumber() == 0)
					outputFile.write("В функции отсутствуют строковые константы!\n", 45);

				else //Иначе каждой константы ...
					for (int j = 0; j < functions[i].getConstantNumber();j++)
					{


						//Выписать её название на новой строке...
							char c_str_const_Name[MAX_STRING_LENGTH];
							strcpy (c_str_const_Name, functions[i].getConstant(j)->getName().c_str());

							outputFile.write(c_str_const_Name, strlen(c_str_const_Name));
							outputFile.write("\n", 1);



							//Выписать все строки,в которых она встречается...
							for (int z = 0; z < functions[i].getConstant(j)->getAppearanceCount(); z++)
							{
								int appString = functions[i].getConstant(j)->getAppearingString(z);

								string tempString = std::to_string(appString);

								char curString[MAX_STRING_LENGTH];
								strcpy(curString, tempString.c_str());

								//Выписать номер строки и перенести на новую строку
								outputFile.write(curString, strlen(curString));
								outputFile.write("\n\n", 2);

							}

					}

			}


		}

	}



	





	outputFile.close();
	return 0;
}

void findConstantsInCode(std::string programCode[], int stringCount, functionUsedInCode functions[], functionUsedInCode* outside, int& functionsCount,errorInfo & error)
{
	using namespace std;

	//Считать, что текущая строка вне функций...
		bool isStringOutside = false; 
		functionUsedInCode* currentFunction = outside;

	bool isStringInComment = false; //Считать, что текущая строка вне многострочных комментариев
	bool isUnclosedQuoteInCode = false; //Считать,что в коде нет незакрытых кавычек
	int unclosedCommentStringIndex = -1; //Номер строки,в которой начат незакрытый к концу кода комментарий
	int functionDepthMeter = 0; //Обнулить счётчик глубины входа в функции...





	for (int i = 0; i < stringCount; i++) //Для каждой строки :
	{
		bool wasStringInComment = isStringInComment; //Была ли текущая строка в многострочном комментарии до их удаления

		string checkedString = programCode[i];

		//Удалить все комментарии из текущей строки...
			string erasedString = eraseCommentariesInString(checkedString, isStringInComment);


		//Запомнить номер текущей строки,если в ней был начат многострочный комментарий
			if (wasStringInComment == false && isStringInComment == true)
				unclosedCommentStringIndex = i;

		char current_c_str[MAX_STRING_LENGTH]; //C-string версия текущей проверяемой строки
		strcpy(current_c_str, checkedString.c_str());


		//Найти незакрытую строковую константу в строке...
		
			//Найти число настоящих кавычек в строке...
				int allQuotes = subStringinStringsRange(current_c_str, "\"", 0, strlen(current_c_str));
				int allFakeQuotes = subStringinStringsRange(current_c_str, "'\"'", 0, strlen(current_c_str));
				int allTrueQuotes = allQuotes - allFakeQuotes; 


			//Если число настоящих кавычек в строке нечётно...
			if (allTrueQuotes % 2 == 1)
			{
				error.errID = 1; //Считать,что строка содержит ошибочную константу
				error.errStringIND = i; //Записать номер строки с ошибкой
				return; //Прекратить проверку
			}





		//----------ПОИСК И СОХРАНЕНИЕ КОНСТАНТ В СТРОКЕ-------------


			bool isConstantInStringFound = false; //Найдена ли в проверяемой строке строковая константа

			string stringForChanging = erasedString; //Изменяемая копия текущей строки без комментариев
			string stringForAdding = findFirstStringConstantInString(stringForChanging,isConstantInStringFound);

			// Удалить из этой константы управляющие символы и спецификаторы формата,
			// Если в строке до неё используются функции ввода/вывода...
			string newConstant;
			
			if (programCode[i].find("printf") != string::npos || programCode[i].find("scanf") != string::npos)
				newConstant = eraseFormatAndCommandSymbols(stringForAdding, true);
			else
				newConstant = eraseFormatAndCommandSymbols(stringForAdding, false);
				


			while (isConstantInStringFound) //Пока в строке есть текстовые константы...
			{

				//Добавить константу в список для данной функции...
				currentFunction->addConstantAppearance(newConstant, i);

				//Найти следующую константу в строке,если такая есть
				stringForAdding = findFirstStringConstantInString(stringForChanging, isConstantInStringFound);
			}





		//---------------ПОИСК И ОПРЕДЕЛЕНИЕ ТЕКУЩЕЙ ФУНКЦИИ---------------


		//Определить глубину входа в функции и составные операторы...
			if (erasedString.find("{") != string::npos) //Инкрементировать счётчик глубины,если в строке открывается функция или составной оператор
				functionDepthMeter += 1;
			if (erasedString.find("}") != string::npos) //Декрементировать счётчик глубины,если в строке закрывается функция или составной оператор
				functionDepthMeter -= 1;

		



			//Если строка не находится внутри функций...
			if (functionDepthMeter == 0)
			{
				currentFunction->completeFunction(i); //Считать,что определение прошлой функции закончилось
				currentFunction = outside;

				//Если в строке обнаружен заголовок или определение функции...
				if (erasedString.find("(") != string::npos && erasedString.find(")") != string::npos &&
					(erasedString.find("int") == 0 || erasedString.find("void") == 0 || erasedString.find("char") == 0 ||
						erasedString.find("double") == 0 || erasedString.find("float") == 0 || erasedString.find("bool") == 0 ||
						erasedString.find("long") == 0 || erasedString.find("short") == 0 || erasedString.find("byte") == 0 ||
						erasedString.find("unsigned") == 0
						) )

				{


					//Определить имя этой функции...
					string functionName = getFunctionName(erasedString);

					


					//Добавить функцию в список,если она ещё не была найдена...
					{
							int foundFunctionIndex = -1; //Номер найденной функции в списке
							bool isFunctionFound = false;

							//Для каждой уже найденной функции...
							for (int j = 0; j < functionsCount; j++)
							{
								//Если имя новой функции совпадает с именем уже найденной
								if (functions[j].getFuncName() == functionName)
								{
									isFunctionFound = true; //Считать,что функция найдена среди имеющихся
									foundFunctionIndex = j; //Записать её номер
								}

							}

							if (isFunctionFound == false) //Если функции нет в списке найденных...
							{
								//Добавить её в конец списка,расширив его...
								functions[functionsCount].setName(functionName);
								functionsCount += 1;


								//Если в строке определение функции, а не заголовок...
								if (erasedString.find(";") == string::npos)
								{
									currentFunction = &(functions[functionsCount - 1]); //Считать новую функцию текущей
									currentFunction->setStartString(i + 1); //Считать,что функция начинается на следующей строке
								}
								//Иначе
								else
									currentFunction = outside; //Считать,что текущая строка не находится внутри функций

							}

							//Если функция есть в списке найденных и в строке определение,а не заголовок...
							if (isFunctionFound && erasedString.find(";") == string::npos)
							{
								//Если в строке определение функции, а не заголовок...
								if (erasedString.find(";") == string::npos)
								{
									currentFunction = &(functions[foundFunctionIndex]); //Считать эту функцию текущей
									currentFunction->setStartString(i + 1);	//Считать,что эта функция начинается на следующей строке
								}

							}
					}
				}

			}

	}

	
	//Вернуть ошибку о незакрытом комментарии,если к концу кода такой имеется

	if (isStringInComment == true)
	{
		error.errID = 2;
		error.errStringIND = unclosedCommentStringIndex;
	}
	

}


std::string getFunctionName(std::string codeString)
{
	using namespace std;

	//Если в строке есть определение или заголовок функции...
	if (codeString.find("(") != string::npos && codeString.find(")") != string::npos)
	{

		//Оставить в строке всё содержимое до параметров функции,исключая их
		string stringForDetectingName = codeString.substr(0, codeString.find("("));

		char redused_c_str[MAX_STRING_LENGTH];
		strcpy(redused_c_str, stringForDetectingName.c_str());

		//Разделить строку на отдельные лексемы,разделённые пробелами...
		char lastWord[MAX_STRING_LENGTH];
		char* wordPoint = strtok(redused_c_str, " ");

		while (wordPoint != NULL) //Пока в строке ещё есть лексемы...
		{
			strcpy(lastWord, wordPoint); //Записать последнее найденное слово
			wordPoint = strtok(NULL, " "); //Найти следующее слово
		}



		strcat(lastWord, "\0");
		return string (lastWord); //Вернуть полученную строку
	}
	else
		return codeString; //Вернуть саму строку,если в ней нет определения/заголовка функции
}

std::string eraseFormatAndCommandSymbols(std::string codeString, bool isInPrintOrScan)
{
	using namespace std;

	string newString = codeString; 

	//Удалять все управляющие символы из строки,пока такие есть...

		while (newString.find("\r") != string::npos)
			newString.erase(newString.find("\r"), 1);

		while (newString.find("\\r") != string::npos)
			newString.erase(newString.find("\\r"), 2);

		while (newString.find("\n") != string::npos)
			newString.erase(newString.find("\n"), 1);

		while (newString.find("\\n") != string::npos)
			newString.erase(newString.find("\\n"), 2);

		while (newString.find("\t") != string::npos)
			newString.erase(newString.find("\t"), 1);

		while (newString.find("\\t") != string::npos)
			newString.erase(newString.find("\\t"), 2);

		while (newString.find("\\v") != string::npos)
			newString.erase(newString.find("\\v"), 2);

		while (newString.find("\v") != string::npos)
			newString.erase(newString.find("\v"), 1);


	if (isInPrintOrScan) //Если подстрока принадлежит функции ввода/вывода данных...
	{
		//Удалить все спецификаторы формата,пока такие есть...

		while (newString.find("%с") != string::npos)
			newString.erase(newString.find("%с"), 2);

		while (newString.find("%d") != string::npos)
			newString.erase(newString.find("%d"), 2);

		while (newString.find("%i") != string::npos)
			newString.erase(newString.find("%i"), 2);

		while (newString.find("%e") != string::npos)
			newString.erase(newString.find("%e"), 2);

		while (newString.find("%f") != string::npos)
			newString.erase(newString.find("%f"), 2);

		while (newString.find("%o") != string::npos)
			newString.erase(newString.find("%o"), 2);

		while (newString.find("%s") != string::npos)
			newString.erase(newString.find("%s"), 2);

		while (newString.find("%u") != string::npos)
			newString.erase(newString.find("%u"), 2);

		while (newString.find("%x") != string::npos)
			newString.erase(newString.find("%x"), 2);

		while (newString.find("%X") != string::npos)
			newString.erase(newString.find("%X"), 2);

		while (newString.find("%p") != string::npos)
			newString.erase(newString.find("%p"), 2);

		while (newString.find("%n") != string::npos)
			newString.erase(newString.find("%n"), 2);

	}


	return newString;
}

std::string findFirstStringConstantInString(std::string & changableString,bool &isConstantInStringFound)
{
	using namespace std;

	string stringBeforeCutting = changableString; //Копия строки до удаления из неё констант

	int firstTrueQuoteIndex = -1; //Индекс в строке символа первой найденной кавычки,обрамляющей строковую константу
	int secondTrueQuoteIndex = -1; //Индекс второй такой кавычки в строке


	int currentPos = 0; //Индекс символа,с которого проверяется строка

	int foundQuoteIndex = stringBeforeCutting.find("\""); //Найти первую кавычку в строке...
	int foundFakeQuoteIndex = stringBeforeCutting.find("'\"'"); //Найти первую ложную кавычку в строке...

	

	while (foundQuoteIndex != string::npos) //Пока в строке есть кавычки...
	{
		//Если найдена ложная кавычка,начинать дальнейшую проверку со следующего за ней символа
		if (foundQuoteIndex == foundFakeQuoteIndex +1)
		{
			currentPos = foundFakeQuoteIndex + 2;
		}
		else //Если найдена истинная кавычка...
		{
			//Задать индекс первой из пары кавычек равным индексу найденной,если он не задан
			if (firstTrueQuoteIndex == -1)
			{
				firstTrueQuoteIndex = foundQuoteIndex; 
				currentPos = firstTrueQuoteIndex + 1; //Проверять строку после первой кавычки
			}

			//Иначе задать индекс второй из пары кавычек равным индексу найденной,если он не задан,но задан индекс первой
			else if (firstTrueQuoteIndex != -1 && secondTrueQuoteIndex == -1)
			{
				secondTrueQuoteIndex = foundQuoteIndex;
				currentPos = secondTrueQuoteIndex + 1; //Проверять строку после второй кавычки
			}



			//Если найдена пара кавычек,обрамляющих строковую константу...
			if (firstTrueQuoteIndex != -1 && secondTrueQuoteIndex != -1)
			{
				//Выделить строковую константу между двумя найденными кавычками...
				string addedString = stringBeforeCutting.substr(firstTrueQuoteIndex+1, secondTrueQuoteIndex -1 - firstTrueQuoteIndex);
				isConstantInStringFound = true; //Считать,что строковая константа найдена


				//Оставить в проверяемой строке только символы после конца найденной константы
				changableString = changableString.substr(secondTrueQuoteIndex + 1);

				return addedString;
			}
				
		


		}


		foundQuoteIndex = stringBeforeCutting.find("\"",currentPos); //Найти следующую кавычку в строке...
		foundFakeQuoteIndex = stringBeforeCutting.find("'\"'",currentPos); //Найти следующую ложную кавычку в строке...

		


	}

	isConstantInStringFound = false;
	return changableString; //Вернуть изначальную строку,если в ней не обнаружены строковые константы
}

std::string eraseCommentariesInString(std::string codeString, bool& isInComment)
{
	using namespace std;

	string changedString = codeString; //Копия строки для редактирования

	char current_c_str[MAX_STRING_LENGTH]; //C-string версия текущей проверяемой строки
	strcpy(current_c_str, codeString.c_str());




	//----------УДАЛЕНИЕ КОММЕНТАРИЕВ ИЗ ПРОВЕРЯЕМОЙ СТРОКИ----------


	int commStartIndex = changedString.find("/*"); //Найти индекс начала комментария в строке
	int commEndIndex = changedString.rfind("*/"); //Найти индекс конца комментария в строке


	//Не изменять строку,если она находится в пределах многострочного комментария и не содержит его конца...
		if (isInComment == true && commEndIndex == string::npos)
			return codeString;




	//Удаление цельного многострочного комментария из строки...

		//Если в строке есть начало и конец многострочного комментария:
	if (commStartIndex != string::npos && commEndIndex != string::npos)
	{
		bool isCommentStartInConst; //Проверить,находится ли начало комментария в пределах строковых констант
		isCommentStartInConst = isSubStringInStringConstant(current_c_str, strlen(current_c_str), commStartIndex, 2);

		bool isCommentEndInConst; //Проверить,находится ли конец комментария в пределах строковых констант
		isCommentEndInConst = isSubStringInStringConstant(current_c_str, strlen(current_c_str), commEndIndex, 2);


		//Если и начало,и конец не внутри строковой константы...
		if (isCommentStartInConst == false && isCommentEndInConst == false)
		{
			//Стереть из копии строки всё содержимое с начала комментария...
			string startOfString = changedString;
			startOfString.erase(commStartIndex);

			//Стереть из копии строки всё содержимое до конца комментария...
			string endOfString = changedString;
			endOfString.erase(0, commEndIndex + 2);


			changedString = startOfString + endOfString; //Склеить начало и конец строки
			strcpy(current_c_str, changedString.c_str());

			isInComment = false; //Считать,что закончился многострочный комментарий
		}

	}


	commStartIndex = changedString.find("/*"); //Найти индекс начала комментария в строке
	commEndIndex = changedString.rfind("*/"); //Найти индекс конца комментария в строке


	//Удаление однострочного комментария из строки...
	int lastCommIndex = changedString.rfind("//"); //Найти индекс комментария в строке

	//Если в строке есть однострочный комментарий:
	if (lastCommIndex != string::npos)
	{
		bool isCommentInConst; //Проверить,находится ли он в пределах строковых констант
		isCommentInConst = isSubStringInStringConstant(current_c_str, strlen(current_c_str), lastCommIndex, 2);

		if (isCommentInConst == false) //Если комментарий не внутри строковой константы...
		{
			changedString.erase(lastCommIndex); //Стереть из строки всё содержимое комментария
			strcpy(current_c_str, changedString.c_str());
		}

	}


	

	//Удаление начала многострочного комментария из строки...

		commStartIndex = changedString.find("/*"); //Найти индекс начала комментария в строке

		//Если в строке есть начало многострочного комментария:
		if (commStartIndex != string::npos)
		{
			bool isCommentInConst; //Проверить,находится ли он в пределах строковых констант
			isCommentInConst = isSubStringInStringConstant(current_c_str, strlen(current_c_str), commStartIndex, 2);

			if (isCommentInConst == false) //Если комментарий не внутри строковой константы...
			{
				changedString.erase(commStartIndex); //Стереть из строки всё содержимое комментария включительно
				strcpy(current_c_str, changedString.c_str());

				isInComment = true; //Считать,что начался многострочный комментарий
			}

		}


	//Удаление конца многострочного комментария из строки...


		commEndIndex = changedString.rfind("*/"); //Найти индекс конца комментария в строке

		//Если в строке есть конец многострочного комментария:
		if (commEndIndex != string::npos)
		{
			bool isCommentInConst; //Проверить,находится ли он в пределах строковых констант
			isCommentInConst = isSubStringInStringConstant(current_c_str, strlen(current_c_str), commEndIndex, 2);

			if (isCommentInConst == false) //Если конец комментарий не внутри строковой константы...
			{
				changedString.erase(0, commEndIndex + 2); //Стереть всё содержимое строки до конца комментария включительно
				strcpy(current_c_str, changedString.c_str());

				isInComment = false; //Считать,что закончился многострочный комментарий
			}

		}


	return changedString;


}

bool isSubStringInStringConstant(char* string, int stringLength, int subStringStart, int subStringLength)
{
	//Считать,что подстрока не в строковой константе,если передано неправильное значение длины строки или подстроки
	if (stringLength <= 0 || stringLength > MAX_STRING_LENGTH || subStringLength <= 0 || subStringLength > MAX_STRING_LENGTH)
		return false;

	//Считать,что подстрока не в строковой константе,если позиция начала подстроки ошибочна
	if (subStringStart < 0 || subStringStart > stringLength)
		return false;

	//Считать,что подстрока не в строковой константе,если размеры подстроки больше размера строки
		if (subStringStart + subStringLength > stringLength)
			return false;

	//Считать,что подстрока не в строковой константе,если переданный в параметрах размер строки больше настоящего
		if (stringLength > strlen(string))
			return false;

	
	//Число настоящих(не char '"') кавычек слева в строке от подстроки
		int leftQuoteNumber = subStringinStringsRange(string, "\"", 0, subStringStart);
		int leftFakeQuoteNumber = subStringinStringsRange(string, "'\"'", 0, subStringStart);
		int leftTrueQuoteNumber = leftQuoteNumber - leftFakeQuoteNumber;

	//Число настоящих(не char '"') кавычек справа в строке от подстроки
		int rightQuoteNumber =	   subStringinStringsRange(string, "\"", subStringStart + subStringLength, strlen(string));
		int rightFakeQuoteNumber = subStringinStringsRange(string, "'\"'", subStringStart + subStringLength, strlen(string));
		int rightTrueQuoteNumber = rightQuoteNumber - rightFakeQuoteNumber;


	//Считать,что подстрока в строковой константе,если число необрамлённых кавычек слева и справа нечётно
	if (leftTrueQuoteNumber % 2 == 1 && rightTrueQuoteNumber % 2 == 1)
		return true;
	else
		return false;
}

int subStringinStringsRange(char* string, const char* subString, int leftBorderIndex, int rightBorderIndex)
{
	if (rightBorderIndex < leftBorderIndex || leftBorderIndex<0 || leftBorderIndex>strlen(string) || rightBorderIndex<0 || rightBorderIndex>strlen(string)
		|| strcmp(subString, "") == 0 || strcmp(subString, "\0") == 0)
		return 0; //Считать,что вхождений нет,если переданы неправильные индексы границ или подстрока пуста

	//Найти количество вхождений подстроки в строку между скобками

	int subStringCounter = 0; //Считать,что в строке нет вхождений подстроки

	int length = rightBorderIndex - leftBorderIndex + 1; //Найти длину диапазона с заданными границами...

	char tempString[MAX_STRING_LENGTH] = "";
	strncpy(tempString, string + leftBorderIndex, length);	//Оставить в строке только часть исходной строки,находящуюся в указанном диапазоне

	while (strstr(tempString, subString) != NULL) //Пока вхождение подстроки во временную строку есть...
	{
		subStringCounter += 1; //...Увеличить счётчик вхождений подстроки в строку на единицу
		strcpy(tempString, strstr(tempString, subString) + strlen(subString));//...Оставить в строке все символы со следующего за вхождением подстроки
	}


	return subStringCounter;
}