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
�������� ��� �������
*/
std::string functionUsedInCode::getFuncName() 
{
	return this->name;
}

/*
�������� ����� ����� ��������� �������� � �������
*/
short functionUsedInCode::getConstantNumber() 
{
	return this->constantNumber;
}


/*
�������� ��������� �� ������ ��������� �� � ������
\param[in] _index - ������ ��������� �� ����� ������� � �������
*/
constantInFunction* functionUsedInCode::getConstant(int _index) 
{
	if (_index <= MAX_CONSTANTS_IN_FUNCTION && _index <= this->constantNumber)
		return &(this->constants[_index]);
	else
		return new constantInFunction;
}

/*
�������� ������ ������� �������-����� �� ���,������ � �����
*/
bool functionUsedInCode::getCompletionState()
{
	return this->isComplete;
}

/*
������ ��� �������
\param[in] name - ���,���������� �������
*/
void functionUsedInCode::setName(std::string _name)
{
	this->name = _name;
}

/*
������ ����� ������ ���������� �������
*/
void functionUsedInCode::setStartString(short stringNumber)
{
	this->startStringNumber = stringNumber;
}



/*
�������� ��� ������ ������� ������� ��������� �� ����������� ������
\param[in] _name - ��� ���������
\param[in] stringIndex - ����� ������,� ������� ������� ���������
*/
void functionUsedInCode::addConstantAppearance(std::string _name, int stringIndex)
{
	int ConstantNumber = this->constantNumber;
	bool isSameConstFound = false;
	for (int i = 0; i < ConstantNumber; i++)
	{
		if (this->getConstant(i)->getName() == _name) //���� ������ ��������� ��� ������� � �������:
		{
			isSameConstFound = true;
			int constsAppearanceCount = this->getConstant(i)->getAppearanceCount();
			this->getConstant(i)->addNewAppearance(stringIndex);
		}


	}

	if (isSameConstFound == false) //���� ����������� ���������,������� ��� �� ���� � �������:
	{
		this->getConstant(constantNumber)->setName(_name);
		this->getConstant(ConstantNumber)->addNewAppearance(stringIndex);
		this->constantNumber += 1;
	}

}