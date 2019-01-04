/*********************************************************************************
* File: XNOR.cpp
* Author: Nicklaus Dahl
* Description: Implements the XNOR gate class.
*********************************************************************************/

#include "XNOR.h"

bool XNOR::Compute()
{
	if (linkedInputs.size() <= 0)
		return false; // No inputs
	bool result = linkedInputs[0]->Compute();
	for (int i = 1; i < linkedInputs.size(); i++)
	{
		result ^= linkedInputs[i]->Compute(this);
	}
	result = !result;
	latchedResult = result;
	return result;
}

bool XNOR::Compute(Gate* startNode)
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
	result = !result;
	latchedResult = result;
	return result;
}

bool XNOR::Compute(std::vector<bool> addtInputs)
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
	result = !result;
	latchedResult = result;
	return result;
}

bool XNOR::Compute(Gate* startNode, std::vector<bool> addtInputs)
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
	result = !result;
	latchedResult = result;
	return result;
}

int XNOR::GetCMOSCost(int numInputs)
{
	// 2-input XNOR gates are typically implemented via 4 NOR gates,
	// and higher numbers of inputs are computed by cascading XOR gates
	// and inverting the output.
	int cost = 16;
	if (numInputs > 2)
		cost += (numInputs - 2) * 16 + 2;
	return cost;
}
