#include <iostream>
#include "constantInFunction.h"
#pragma once



/*
Функция,встреченная в коде
*/
class functionUsedInCode
{
public:

	functionUsedInCode();
	functionUsedInCode(std::string _name, int _startStringNumber);
	~functionUsedInCode();



	void completeFunction(int);

	std::string getFuncName();
	short getConstantNumber();
	constantInFunction* getConstant(int);
	bool getCompletionState();

	void setName(std::string _name);
	void setStartString(short stringNumber);

	void addConstantAppearance(std::string _name, int stringIndex);


private:

	std::string name = "-1"; //Имя функции
	short startStringNumber = -1; //Номер(0..126) строки объявления функции
	short endStringNumber = -1; //Номер(0..126) строки конца объявления функции
	bool isComplete = false; //Является ли полной без ошибок (имеет все имя,начало и конец)

	constantInFunction constants[MAX_CONSTANTS_IN_FUNCTION]; //Константы
	short constantNumber = 0;

};

