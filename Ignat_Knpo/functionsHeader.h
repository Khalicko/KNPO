#include <iostream>
#include "functionUsedInCode.h"
#include "constantInFunction.h"
#include "Header.h"
#pragma once




/*
����� ��� ��������� ��������� � ����
\param[in] programCode - ��� ���������
\param[in] stringCount - ����� ����� � ���� ���������
\param[in|out] functions - �������,������������ � ����
\param[in|out] functionsCount - ����� ������������ � ���� �������
\param[out] hasUnclosedComment - ������� �� � ����������� ���� ���������� � ����� �����������
*/
void findConstantsInCode(std::string programCode[], int stringCount, functionUsedInCode functions[], functionUsedInCode* outside, int& functionsCount, errorInfo& error);

//void findConstantsInString(std::string codeString, functionUsedInCode functions[MAX_FUNCTIONS_NUMBER], functionUsedInCode& outside, bool& isInComment, bool& isOutside, int stringNumber,bool & containsUnclosedQuote);

//void addConstantAppearance(std::string constName, int stringIndex);



/*
����� ����� ��������� ��������� � ������ ����� ��������� � ��������� ���������
\param[in] string - ������,� ������� ������ ���������
\param[in] subString - ������� ���������
\param leftBorderIndex - ������ ������� ������� ��������� � ������
\param rightBorderIndex - ������ ���������� ������� ��������� � ������
\return ����� ��������� ��������� � ������ � ��������� ���������
*/
int subStringinStringsRange(char* string, const char* subString, int leftBorderIndex, int rightBorderIndex);

/*
��������� �� ��������� ������ �����,������������ � ������� �������,� ��������� ��������� (" ��� ")
\param[in] string-������,� ������� ��������� ���������
\param[in] stringLength - ����� ������� ������
\param[in] subStringStart - ������(0..stringLength-1) ������ ��������� � ������
\param[in] subStringLength - ����� ���������
*/
bool isSubStringInStringConstant(char* string, int stringLength, int subStringStart, int subStringLength);

/*
������� ������������� � ������������ ����������� �� ������
\param[in] codeString - ������ ����,�� ������� ��������� �����������
\param[in|out] isCommentOpened - ��������� �� ������ � ������������� ����������� �� (� �����) ���������
*/
std::string eraseCommentariesInString(std::string codeString, bool& isInComment);

/*
������� ����������� ������� � ������������� ����� �� ������
\param[in] codeString - ������,� ������� ���������� ��������
\param[in|out] isInPrintOrScan - ����������� �� ������ �������� �����/������ ������ (scanf,printf)
*/
std::string eraseFormatAndCommandSymbols(std::string codeString, bool isInPrintOrScan);

/*
���������� ��� �������,����������/��������� ������� ��������� � ��������� ������.���������� ���� ������,���� � ��� ��� �������.
\param[in] codeString - ������ ����,� ������� ��������� ����������/��������� �������
*/
std::string getFunctionName(std::string codeString);

/*
���������� ������ ��������� ���������,��������� � ������ ����
\param[in|out] changableString - ������,� ������� ������ �����
\param[out] isConstantInStringFound - ������� �� ��������� ��������� � ���������� ������
*/
std::string findFirstStringConstantInString(std::string& changableString, bool& isConstantInStringFound);