#pragma once
#include "Header.h"

class constantInFunction
{
public:

	constantInFunction(); //����������� ��-���������
	constantInFunction(std::string, int); //����������� � �����������:
	~constantInFunction(); //����������


	std::string getName(); //�������� ��� ���������
	short getAppearanceCount(); //�������� ����� ������ ��������� � ����� �������
	short getAppearingString(int index); //�������� ����� ������,� ������� ��������� �����������,�� ������� ����� �� �������

	void addNewAppearance(int string); //�������� ������� ��������� �� ����������� ������
	void setName(std::string _name);

private:

	std::string name; //��� ���������
	short appearingStrings[MAX_STRING_NUMBER]; //������,�� ������� ������� ���������� ������ ���������
	short countInFunction; //������� ����,������� ��� ��������� ����������� �� �������
};




