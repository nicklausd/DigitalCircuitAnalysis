/*********************************************************************************
* File: NOR.cpp
* Author: Nicklaus Dahl
* Description: Implements the NOR gate class.
*********************************************************************************/

#include "NOR.h"

bool NOR::Compute()
{
	if (linkedInputs.size() <= 0)
		return false; // No inputs
	bool result = linkedInputs[0]->Compute();
	for (int i = 1; i < linkedInputs.size(); i++)
	{
		result |= linkedInputs[i]->Compute(this);
	}
	result = !result;
	latchedResult = result;
	return result;
}

bool NOR::Compute(Gate* startNode)
{
	if (startNode == this)
		return latchedResult;

	if (linkedInputs.size() <= 0)
		return false; // No inputs
	bool result = linkedInputs[0]->Compute();
	for (int i = 1; i < linkedInputs.size(); i++)
	{
		result |= linkedInputs[i]->Compute(startNode);
	}
	result = !result;
	latchedResult = result;
	return result;
}

bool NOR::Compute(std::vector<bool> addtInputs)
{
	if (addtInputs.size() == 0 && linkedInputs.size() == 0)
		return false; // No inputs
	bool result = true;
	for (int i = 0; i < addtInputs.size(); i++)
	{
		result |= addtInputs[i];
	}
	for (int i = 0; i < linkedInputs.size(); i++)
	{
		result |= linkedInputs[i]->Compute(this);
	}
	result = !result;
	latchedResult = result;
	return result;
}

bool NOR::Compute(Gate* startNode, std::vector<bool> addtInputs)
{
	if (startNode == this)
		return latchedResult;

	if (addtInputs.size() == 0 && linkedInputs.size() == 0)
		return false; // No inputs
	bool result = true;
	for (int i = 0; i < addtInputs.size(); i++)
	{
		result |= addtInputs[i];
	}
	for (int i = 0; i < linkedInputs.size(); i++)
	{
		result |= linkedInputs[i]->Compute(startNode);
	}
	result = !result;
	latchedResult = result;
	return result;
}

int NOR::GetCMOSCost(int numInputs)
{
	// CMOS NOR requires two transistors per input
	return 2 * numInputs;
}
