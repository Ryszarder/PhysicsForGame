#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>

std::string LoadFileAsString(std::string filename)
{
	
	std::stringstream fileSoFar;
	std::ifstream file(filename);

	if (file.is_open())
	{
		while (!file.eof())
		{
			std::string thisLine;
			std::getline(file, thisLine);
			fileSoFar << thisLine << std::endl;
		}
		return fileSoFar.str();
	}
	else
	{
		std::cout << "Error loading file: " << filename << std::endl;
		return "";
	}

}

float GetRandomFloat(float min, float max)
{
	min = ((float)rand() / (float)RAND_MAX);
	max = ((float)rand() / (float)RAND_MAX);
	return (min, max);
}