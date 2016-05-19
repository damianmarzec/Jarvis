#pragma once
#include <iostream>
#include <vector>
#include <string>
class Debuger
{
public:
	static void showVectorValsUnsigned(std::string label, std::vector<unsigned>& v);
	static void showVectorValsDouble(std::string label, std::vector<double>& v);
};

