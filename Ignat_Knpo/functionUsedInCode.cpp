#include "functionUsedInCode.h"

functionUsedInCode::functionUsedInCode()
{
	this->name = "defaultFunctionName";
	this->startStringNumber = -1;
	this->endStringNumber = -1;
	this->isComplete = false;

	this->constantNumber = 0;
}

functionUsedInCode::functionUsedInCode(std::string _name, int _startStringNumber)
{
	this->name = _name;
	this->endStringNumber = -1;
	this->constantNumber = 0;

	if (_startStringNumber >= 0 && _startStringNumber <= MAX_STRING_NUMBER)
		this->startStringNumber = _startStringNumber;
	else
		this->startStringNumber = -1;
}

functionUsedInCode::~functionUsedInCode()
{
}




void functionUsedInCode::completeFunction(int _endStringNumber)
{
	if (_endStringNumber > 0 && _endStringNumber <MAX_STRING_NUMBER && _endStringNumber > this->startStringNumber)
	{
		this->endStringNumber = _endStringNumber;
		this->isComplete = true;
	}
}







/*
Получить имя функции
*/
std::string functionUsedInCode::getFuncName() 
{
	return this->name;
}

/*
Получить общее число имеющихся констант в функции
*/
short functionUsedInCode::getConstantNumber() 
{
	return this->constantNumber;
}


/*
Получить указатель на нужную константу по её номеру
\param[in] _index - индекс константы из всего массива в функции
*/
constantInFunction* functionUsedInCode::getConstant(int _index) 
{
	if (_index <= MAX_CONSTANTS_IN_FUNCTION && _index <= this->constantNumber)
		return &(this->constants[_index]);
	else
		return new constantInFunction;
}

/*
Получить статус полноты функции-имеет ли имя,начало и конец
*/
bool functionUsedInCode::getCompletionState()
{
	return this->isComplete;
}

/*
Задать имя функции
\param[in] name - имя,задаваемое функции
*/
void functionUsedInCode::setName(std::string _name)
{
	this->name = _name;
}

/*
Задать номер строки объявления функции
*/
void functionUsedInCode::setStartString(short stringNumber)
{
	this->startStringNumber = stringNumber;
}



/*
Добавить для данной функции встречу константы на определённой строке
\param[in] _name - имя константы
\param[in] stringIndex - номер строки,в которой найдена константа
*/
void functionUsedInCode::addConstantAppearance(std::string _name, int stringIndex)
{
	int ConstantNumber = this->constantNumber;
	bool isSameConstFound = false;
	for (int i = 0; i < ConstantNumber; i++)
	{
		if (this->getConstant(i)->getName() == _name) //Если данная константа уже найдена в функции:
		{
			isSameConstFound = true;
			int constsAppearanceCount = this->getConstant(i)->getAppearanceCount();
			this->getConstant(i)->addNewAppearance(stringIndex);
		}


	}

	if (isSameConstFound == false) //Если встречается константа,которой ещё не было в функции:
	{
		this->getConstant(constantNumber)->setName(_name);
		this->getConstant(ConstantNumber)->addNewAppearance(stringIndex);
		this->constantNumber += 1;
	}

}