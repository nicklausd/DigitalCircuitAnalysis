/*********************************************************************************
* File: XOR.cpp
* Author: Nicklaus Dahl
* Description: Implements the XOR gate class.
*********************************************************************************/

#include "XOR.h"

bool XOR::Compute()
{
	if (linkedInputs.size() <= 0)
		return false; // No inputs
	bool result = linkedInputs[0]->Compute();
	for (int i = 1; i < linkedInputs.size(); i++)
	{
		result ^= linkedInputs[i]->Compute(this);
	}
	latchedResult = result;
	return result;
}

bool XOR::Compute(Gate* startNode)
{
	if (startNode == this)
		return latchedResult;

	if (linkedInputs.size() <= 0)
		return false; // No inputs
	bool result = linkedInputs[0]->Compute();
	for (int i = 1; i < linkedInputs.size(); i++)
	{
		result ^= linkedInputs[i]->Compute(startNode);
	}
	latchedResult = result;
	return result;
}

bool XOR::Compute(std::vector<bool> addtInputs)
{
	if (addtInputs.size() == 0 && linkedInputs.size() == 0)
		return false; // No inputs
	bool result = false;
	for (int i = 0; i < addtInputs.size(); i++)
	{
		result ^= addtInputs[i];
	}
	for (int i = 0; i < linkedInputs.size(); i++)
	{
		result ^= linkedInputs[i]->Compute(this);
	}
	latchedResult = result;
	return result;
}

bool XOR::Compute(Gate* startNode, std::vector<bool> addtInputs)
{
	if (startNode == this)
		return latchedResult;

	if (addtInputs.size() == 0 && linkedInputs.size() == 0)
		return false; // No inputs
	bool result = false;
	for (int i = 0; i < addtInputs.size(); i++)
	{
		result ^= addtInputs[i];
	}
	for (int i = 0; i < linkedInputs.size(); i++)
	{
		result ^= linkedInputs[i]->Compute(startNode);
	}
	latchedResult = result;
	return result;
}

int XOR::GetCMOSCost(int numInputs)
{
	// 2-input XOR gates are typically implemented via 4 NAND gates,
	// and higher numbers of inputs are computed by cascading XOR gates.
	return 16 + (numInputs - 2) * 16;
}