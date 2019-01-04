/*********************************************************************************
* File: Gate.cpp
* Author: Nicklaus Dahl
* Description: Implements the Gate class.
*********************************************************************************/

#include "Gate.h"

typedef std::shared_ptr<Gate> GatePtr;

Gate::Gate()
{
	// std::shared_ptr is used to ensure that multiple objects can claim
	// ownership of a Gate object so that the underlying Gate of the pointer
	// is not destroyed if some objects still need it. shared_ptr also handles
	// some amount of garbage collection automatically, so that we do not need
	// to remember to call delete or destructors manually.
	linkedInputs = std::vector<GatePtr>();
	linkedOutputs = std::vector<GatePtr>();
}

Gate::Gate(std::vector<GatePtr>& inputs, std::vector<GatePtr>& outputs)
{
	linkedInputs = std::vector<GatePtr>();
	linkedOutputs = std::vector<GatePtr>();

	for (int i = 0; i < inputs.size(); i++)
	{
		linkedInputs.push_back(GatePtr(inputs[i]));
	}
	for (int i = 0; i < outputs.size(); i++)
	{
		linkedOutputs.push_back(GatePtr(outputs[i]));
	}
}

void Gate::SetLinkedInputs(std::vector<GatePtr>& gates)
{
	linkedInputs = std::vector<GatePtr>();
	for (int i = 0; i < gates.size(); i++)
	{
		linkedInputs.push_back(GatePtr(gates[i]));
	}
}

std::vector<GatePtr>& Gate::GetLinkedInputs()
{
	return this->linkedInputs;
}

void Gate::SetLinkedOutputs(std::vector<GatePtr>& gates)
{
	linkedOutputs = std::vector<GatePtr>();

	for (int i = 0; i < gates.size(); i++)
	{
		linkedOutputs.push_back(GatePtr(gates[i]));
	}
}

std::vector<GatePtr>& Gate::GetLinkedOutputs()
{
	return this->linkedOutputs;
}

void Gate::AddLinkedInput(GatePtr gate)
{
	// Since we pass the shared_ptr by value, using std::move allows us
	// to transfer ownership of the copy of the shared_ptr made to the
	// vector so that we don't create another shared_ptr only to have one
	// be destroyed anyways.
	linkedInputs.push_back(std::move(gate));
}

void Gate::AddLinkedOutput(GatePtr gate)
{
	linkedOutputs.push_back(std::move(gate));
}
