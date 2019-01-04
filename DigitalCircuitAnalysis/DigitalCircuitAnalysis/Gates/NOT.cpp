/*********************************************************************************
* File: NOT.cpp
* Author: Nicklaus Dahl
* Description: Implements the NOT gate class.
*********************************************************************************/

#include "NOT.h"

bool NOT::Compute()
{
	if (linkedInputs.size() <= 0)
		return false; // No inputs
	// NOT should only ever take one input, so we will only ever compute
	// on the first linkedInput
	bool result = !linkedInputs[0]->Compute(this);
	latchedResult = result;
	return result;
}

bool NOT::Compute(Gate* startNode)
{
	if (startNode == this)
		return latchedResult;

	bool result = !linkedInputs[0]->Compute(startNode);
	latchedResult = result;
	return result;
}

bool NOT::Compute(std::vector<bool> addtInputs)
{
	bool result = false;
	if (linkedInputs.size() == 0)
	{
		if (addtInputs.size() == 0)
			return false; // no inputs
		result = !addtInputs[0];
	}
	else
	{
		result = !linkedInputs[0]->Compute(this);
	}
	latchedResult = result;
	return result;
}

bool NOT::Compute(Gate* startNode, std::vector<bool> addtInputs)
{
	if (startNode == this)
		return latchedResult;

	bool result = false;
	if (linkedInputs.size() == 0)
	{
		if (addtInputs.size() == 0)
			return false; // no inputs
		result = !addtInputs[0];
	}
	else
	{
		result = !linkedInputs[0]->Compute(startNode);
	}
	latchedResult = result;
	return result;
}

int NOT::GetCMOSCost(int numInputs)
{
	// A NOT gate is always just two transistors
	return 2;
}
