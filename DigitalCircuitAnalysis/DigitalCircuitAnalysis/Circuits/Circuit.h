/*********************************************************************************
* File: Circuit.h
* Author: Nicklaus Dahl
* Description: Declares the Circuit class.
*********************************************************************************/

#pragma once
#include <vector>
#include <memory>
#include "../LogicGates.h"

class Circuit
{
protected:
	typedef std::shared_ptr<Gate> GatePtr;
	std::vector<GatePtr> outputGates;
	std::vector<GatePtr> circuitNetwork;
	std::vector<GatePtr> inputGates;
public:
	Circuit();

	virtual std::vector<bool> Compute();

	void AddOutput(GatePtr gate);
	void AddInput(GatePtr gate);
	void AddToNetwork(GatePtr gate);

	std::vector<GatePtr>& GetInputs();
	std::vector<GatePtr>& GetOutputs();
};
