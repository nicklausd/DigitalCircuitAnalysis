/*********************************************************************************
* File: Gate.h
* Author: Nicklaus Dahl
* Description: Declares the Gate class.
*********************************************************************************/

#pragma once
#include <memory>
#include <vector>

class Gate
{
protected:
	typedef std::shared_ptr<Gate> GatePtr;
	std::vector<GatePtr> linkedInputs;
	std::vector<GatePtr> linkedOutputs;
	bool latchedResult = false;
public:
	Gate();
	Gate(std::vector<GatePtr>& inputs, std::vector<GatePtr>& outputs);

	virtual bool Compute() = 0;
	virtual bool Compute(Gate* startNode) = 0;
	virtual bool Compute(std::vector<bool> addtInputs) = 0;
	virtual bool Compute(Gate* startNode, std::vector<bool> addtInputs) = 0;

	virtual int GetCMOSCost(int numInputs) = 0;

	void SetLinkedInputs(std::vector<GatePtr>& gates);
	void AddLinkedInput(GatePtr gate);
	std::vector<GatePtr>& GetLinkedInputs();

	void SetLinkedOutputs(std::vector<GatePtr>& gates);
	void AddLinkedOutput(GatePtr gate);
	std::vector<GatePtr>& GetLinkedOutputs();
};
