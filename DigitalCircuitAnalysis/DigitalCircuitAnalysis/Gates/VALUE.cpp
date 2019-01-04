/*********************************************************************************
* File: VALUE.cpp
* Author: Nicklaus Dahl
* Description: Implements the VALUE class.
*********************************************************************************/

#include "VALUE.h"

VALUE::VALUE(bool val)
{
	constVal = val;
}

bool VALUE::Compute()
{
	return constVal;
}

bool VALUE::Compute(Gate* startNode)
{
	return constVal;
}

bool VALUE::Compute(std::vector<bool> addtInputs)
{
	return constVal;
}

bool VALUE::Compute(Gate* startNode, std::vector<bool> addtInputs)
{
	return constVal;
}

int VALUE::GetCMOSCost(int numInputs)
{
	// Since this is just equivalent to a constant bool or wire input,
	// no transistors are involved.
	return 0;
}

// Override the assignment operator so that a boolean can be assigned directly
// to a VALUE object without having to call an additional method.
VALUE& VALUE::operator=(bool val)
{
	constVal = val;
	return *this;
}

// Override the assignment operator to copy the boolean value and not
// the whole object.
VALUE& VALUE::operator=(const VALUE& val)
{
	constVal = val.constVal;
	return *this;
}
