/*********************************************************************************
* File: AND.h
* Author: Nicklaus Dahl
* Description: Declares the AND gate class.
*********************************************************************************/

#pragma once
#include "Gate.h"

class AND : public Gate
{
public:
	virtual bool Compute();
	virtual bool Compute(Gate* startNode);
	virtual bool Compute(std::vector<bool> addtInputs);
	virtual bool Compute(Gate* startNode, std::vector<bool> addtInputs);

	virtual int GetCMOSCost(int numInputs);
};
