#include <iostream>
#include "constantInFunction.h"
#pragma once



/*
�������,����������� � ����
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

	std::string name = "-1"; //��� �������
	short startStringNumber = -1; //�����(0..126) ������ ���������� �������
	short endStringNumber = -1; //�����(0..126) ������ ����� ���������� �������
	bool isComplete = false; //�������� �� ������ ��� ������ (����� ��� ���,������ � �����)

	constantInFunction constants[MAX_CONSTANTS_IN_FUNCTION]; //���������
	short constantNumber = 0;

};

