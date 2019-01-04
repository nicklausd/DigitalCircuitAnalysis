/*********************************************************************************
* File: AND.cpp
* Author: Nicklaus Dahl
* Description: Implements the AND gate class.
*********************************************************************************/

#include "AND.h"

bool AND::Compute()
{
	if (linkedInputs.size() <= 0)
		return false; // No inputs
	bool result = linkedInputs[0]->Compute();
	// AND all inputs together.
	for (int i = 1; i < linkedInputs.size(); i++)
	{
		result &= linkedInputs[i]->Compute(this);
	}
	// Ensure we update the latched state for when feedback is used.
	latchedResult = result;
	return result;
}

bool AND::Compute(Gate* startNode)
{
	// Check if this node is the original node so that we do not encounter
	// infinite recursion. Allows feedback circuits to work properly.
	if (startNode == this)
		return latchedResult;

	if (linkedInputs.size() <= 0)
		return false; // No inputs
	bool result = linkedInputs[0]->Compute();
	for (int i = 1; i < linkedInputs.size(); i++)
	{
		result &= linkedInputs[i]->Compute(startNode);
	}
	latchedResult = result;
	return result;
}

bool AND::Compute(std::vector<bool> addtInputs)
{
	if (addtInputs.size() == 0 && linkedInputs.size() == 0)
		return false; // No inputs
	bool result = true;
	for (int i = 0; i < addtInputs.size(); i++)
	{
		result &= addtInputs[i];
	}
	for (int i = 0; i < linkedInputs.size(); i++)
	{
		result &= linkedInputs[i]->Compute(this);
	}
	latchedResult = result;
	return result;
}

bool AND::Compute(Gate* startNode, std::vector<bool> addtInputs)
{
	if (startNode == this)
		return latchedResult;

	if (addtInputs.size() == 0 && linkedInputs.size() == 0)
		return false; // No inputs
	bool result = true;
	for (int i = 0; i < addtInputs.size(); i++)
	{
		result &= addtInputs[i];
	}
	for (int i = 0; i < linkedInputs.size(); i++)
	{
		result &= linkedInputs[i]->Compute(startNode);
	}
	latchedResult = result;
	return result;
}

int AND::GetCMOSCost(int numInputs)
{
	// CMOS NAND requires two transistors per input, and the NOT
	// at the output requires two more transistors.
	return 2 * numInputs + 2;
}
