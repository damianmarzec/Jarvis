#include "stdafx.h"
#include "Debuger.h"
#include <iostream>
#include <vector>
#include <string>

void Debuger::showVectorValsUnsigned(std::string label, std::vector<unsigned> &v)
{
	std::cout << label << " - (size:" << v.size() << ")" << std::endl;
	for (unsigned i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl <<  "--/-----------" << std::endl;
}

void Debuger::showVectorValsDouble(std::string label, std::vector<double> &v)
{
	std::cout << label << " - (size:" << v.size() << ")" << std::endl;
	for (unsigned i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl <<  "--/-----------" << std::endl;
}
