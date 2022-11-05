#pragma once
#include "Header.h"

class constantInFunction
{
public:

	constantInFunction(); //Конструктор по-умолчанию
	constantInFunction(std::string, int); //Конструктор с параметрами:
	~constantInFunction(); //Деструктор


	std::string getName(); //Получить имя константы
	short getAppearanceCount(); //Получить число встреч константы в своей функции
	short getAppearingString(int index); //Получить номер строки,в которой константа встречается,из массива строк по индексу

	void addNewAppearance(int string); //Добавить встречу константы на определённой строке
	void setName(std::string _name);

private:

	std::string name; //Имя константы
	short appearingStrings[MAX_STRING_NUMBER]; //Строки,на которых имеется упоминание данной константы
	short countInFunction; //Счётчик того,сколько раз константа встречается за функцию
};




