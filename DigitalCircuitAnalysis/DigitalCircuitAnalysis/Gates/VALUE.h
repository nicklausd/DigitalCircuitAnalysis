/*********************************************************************************
* File: VALUE.h
* Author: Nicklaus Dahl
* Description: Declares the VALUE class. VALUE allows a single boolean value to
*    be stored as if it were a Gate so that it can be stored as a node in a
*    circuit network.
*********************************************************************************/

#pragma once
#include "Gate.h"

class VALUE : public Gate
{
	bool constVal;
public:
	VALUE(bool val);
	virtual bool Compute();
	virtual bool Compute(Gate* startNode);
	virtual bool Compute(std::vector<bool> addtInputs);
	virtual bool Compute(Gate* startNode, std::vector<bool> addtInputs);

	virtual int GetCMOSCost(int numInputs);

	VALUE& operator= (bool val);
	VALUE& operator= (const VALUE& val);
};
