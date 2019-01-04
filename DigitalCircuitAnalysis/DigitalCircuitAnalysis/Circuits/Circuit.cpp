/*********************************************************************************
* File: Circuit.cpp
* Author: Nicklaus Dahl
* Description: Implements the Circuit class
*********************************************************************************/

#include "Circuit.h"

typedef std::shared_ptr<Gate> GatePtr;

Circuit::Circuit()
{
	outputGates = std::vector<GatePtr>();
	circuitNetwork = std::vector<GatePtr>();
	inputGates = std::vector<GatePtr>();
}

// Since a circuit can have multiple output nodes, this computes the output
// of all of those nodes and returns them as a vector.
std::vector<bool> Circuit::Compute()
{
	std::vector<bool> result = std::vector<bool>();
	for (GatePtr outGate : outputGates)
	{
		result.push_back(outGate->Compute());
	}
	return result;
}

// Add an output node to the circuit.
void Circuit::AddOutput(GatePtr gate)
{
	outputGates.push_back(std::move(gate));
}

// Add an input node to the circuit.
void Circuit::AddInput(GatePtr gate)
{
	inputGates.push_back(std::move(gate));
}

// Add an intermediary node to the circuit network.
void Circuit::AddToNetwork(GatePtr gate)
{
	circuitNetwork.push_back(std::move(gate));
}

// Get all input nodes
std::vector<GatePtr>& Circuit::GetInputs()
{
	return this->inputGates;
}

// Get all output nodes
std::vector<GatePtr>& Circuit::GetOutputs()
{
	return this->outputGates;
}
