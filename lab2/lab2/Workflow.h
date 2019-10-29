#pragma once
#include "ReadFile.h"
#include "SchemeValidator.h"
#include "SchemeParser.h"
class Workflow             // в конструкторе создает ReadFile в который передаЄтс€ название файла и ссылка на вектор строк в который нужно записать данные
{						   // после этого эти данные провер€ютс€ в валидаторе схем, затем проверенные данные передаютс€ в парсер схем, парсер схем создаЄт мапу 
public:					   // key = blockName   value = arguments  , а также создаЄт лист интов (последовательность выполнени€ блоков) 
	Workflow(std::string fileName , std::string in = "",std::string out= ""); // данные из парсера передаютс€ в конструктор схемы, в котором по мапе и листу создаЄтс€ лист блоков 
	~Workflow();
							// TODO  create implementation of block classes
private:
	std::vector<std::string>data;
	std::ifstream in;                          // streams to work with scheme
	std::ofstream out;                    
};

