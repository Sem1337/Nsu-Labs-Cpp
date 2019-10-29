#pragma once
#include "ReadFile.h"
#include "SchemeValidator.h"
#include "SchemeParser.h"
class Workflow             // � ������������ ������� ReadFile � ������� ��������� �������� ����� � ������ �� ������ ����� � ������� ����� �������� ������
{						   // ����� ����� ��� ������ ����������� � ���������� ����, ����� ����������� ������ ���������� � ������ ����, ������ ���� ������ ���� 
public:					   // key = blockName   value = arguments  , � ����� ������ ���� ����� (������������������ ���������� ������) 
	Workflow(std::string fileName , std::string in = "",std::string out= ""); // ������ �� ������� ���������� � ����������� �����, � ������� �� ���� � ����� �������� ���� ������ 
	~Workflow();
							// TODO  create implementation of block classes
private:
	std::vector<std::string>data;
	std::ifstream in;                          // streams to work with scheme
	std::ofstream out;                    
};

