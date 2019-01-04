/*********************************************************************************
* File: OR.cpp
* Author: Nicklaus Dahl
* Description: Implements the OR gate class.
*********************************************************************************/

#include "OR.h"

bool OR::Compute()
{
	if (linkedInputs.size() <= 0)
		return false; // No inputs
	bool result = linkedInputs[0]->Compute();
	for (int i = 1; i < linkedInputs.size(); i++)
	{
		result |= linkedInputs[i]->Compute(this);
	}
	latchedResult = result;
	return result;
}

bool OR::Compute(Gate* startNode)
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
	latchedResult = result;
	return result;
}

bool OR::Compute(std::vector<bool> addtInputs)
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
	latchedResult = result;
	return result;
}

bool OR::Compute(Gate* startNode, std::vector<bool> addtInputs)
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
	latchedResult = result;
	return result;
}

int OR::GetCMOSCost(int numInputs)
{
	// CMOS NOR requires two transistors per input, and the NOT
	// at the output requires an additional two transistors.
	return 2 * numInputs + 2;
}
