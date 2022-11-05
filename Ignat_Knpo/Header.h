const int MAX_STRING_NUMBER = 127; //Максимальное число строк в коде
const int MAX_STRING_LENGTH = 255; //Максимальная длина строки
const int MAX_FUNCTIONS_NUMBER = 16; //Максимальное число найденных в коде функций
const int MAX_CONSTANTS_IN_FUNCTION = 64; //Максимальное число строковых констант в одной функции
#include <iostream>
#pragma once


/*
Структура для всех ошибок в коде проверяемой программы
Хранит тип ошибки и строку с ошибкой
*/
struct errorInfo
{
	int errID = -1;
	int errStringIND = -1;
	
};
