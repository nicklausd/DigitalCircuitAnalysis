/*********************************************************************************
* File: FileParser.h
* Author: Nicklaus Dahl
* Description: Declares the FileParser class. Allows a digital circuit equation to
*    be read in from a file and easily be converted into an equation.
*********************************************************************************/

#pragma once
#include <string>
#include "Circuits/Circuit.h"

class FileParser
{
	std::vector<std::string> fileLines;
	bool OpHasPrecedence(std::string leftOp, std::string rightOp);
public:
	FileParser(const std::string& fileName);
	Circuit ParseToCircuit();
};
