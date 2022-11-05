#include <iostream>
#include "functionUsedInCode.h"
#include "constantInFunction.h"
#include "Header.h"
#pragma once




/*
Найти все строковые константы в коде
\param[in] programCode - код программы
\param[in] stringCount - число строк в коде программы
\param[in|out] functions - функции,обнаруженные в коде
\param[in|out] functionsCount - число обнаруженных в коде функций
\param[out] hasUnclosedComment - имеется ли в проверяемом коде незакрытый к концу комментарий
*/
void findConstantsInCode(std::string programCode[], int stringCount, functionUsedInCode functions[], functionUsedInCode* outside, int& functionsCount, errorInfo& error);

//void findConstantsInString(std::string codeString, functionUsedInCode functions[MAX_FUNCTIONS_NUMBER], functionUsedInCode& outside, bool& isInComment, bool& isOutside, int stringNumber,bool & containsUnclosedQuote);

//void addConstantAppearance(std::string constName, int stringIndex);



/*
Найти число вхождений подстроки в строку между символами с заданными индексами
\param[in] string - строка,в которой ищется подстрока
\param[in] subString - искомая подстрока
\param leftBorderIndex - индекс первого символа диапазона в строке
\param rightBorderIndex - индекс последнего символа диапазона в строке
\return число вхождений подстроки в строку в указанном диапазоне
*/
int subStringinStringsRange(char* string, const char* subString, int leftBorderIndex, int rightBorderIndex);

/*
Находится ли подстрока данной длины,начинающаяся с данного символа,в строковой константе (" два ")
\param[in] string-строка,в которой находится подстрока
\param[in] stringLength - длина искомой строки
\param[in] subStringStart - индекс(0..stringLength-1) начала подстроки в строке
\param[in] subStringLength - длина подстроки
*/
bool isSubStringInStringConstant(char* string, int stringLength, int subStringStart, int subStringLength);

/*
Удаляет многострочные и однострочные комментарии из строки
\param[in] codeString - строка кода,из которой удаляются комментарии
\param[in|out] isCommentOpened - находится ли строка в многострочном комментарии до (и после) обработки
*/
std::string eraseCommentariesInString(std::string codeString, bool& isInComment);

/*
Удаляет управляющие символы и спецификаторы ввода из строки
\param[in] codeString - строка,в которой происходит удаление
\param[in|out] isInPrintOrScan - принадлежит ли строка функциям ввода/вывода данных (scanf,printf)
*/
std::string eraseFormatAndCommandSymbols(std::string codeString, bool isInPrintOrScan);

/*
Возвращает имя функции,объявление/заголовок которой находится в указанной строке.Возвращает саму строку,если в ней нет функций.
\param[in] codeString - строка кода,в которой находится объявление/заголовок функции
*/
std::string getFunctionName(std::string codeString);

/*
Возвращает первую строковую константу,найденную в строке кода
\param[in|out] changableString - строка,в которой ведётся поиск
\param[out] isConstantInStringFound - найдена ли строковая константа в переданной строке
*/
std::string findFirstStringConstantInString(std::string& changableString, bool& isConstantInStringFound);