const int MAX_STRING_NUMBER = 127; //������������ ����� ����� � ����
const int MAX_STRING_LENGTH = 255; //������������ ����� ������
const int MAX_FUNCTIONS_NUMBER = 16; //������������ ����� ��������� � ���� �������
const int MAX_CONSTANTS_IN_FUNCTION = 64; //������������ ����� ��������� �������� � ����� �������
#include <iostream>
#pragma once


/*
��������� ��� ���� ������ � ���� ����������� ���������
������ ��� ������ � ������ � �������
*/
struct errorInfo
{
	int errID = -1;
	int errStringIND = -1;
	
};
