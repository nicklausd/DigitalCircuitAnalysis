/*********************************************************************************
* File: main.cpp
* Author: Nicklaus Dahl
* Description: File containing program entry point. Demonstrates operation of the
*    various classes in the program for evaluating digital circuits.
*********************************************************************************/

#include "LogicGates.h"
#include "Circuits/MUX2.h"
#include "Circuits/MUX4.h"
#include "FileParser.h"
#include <iostream>
#include <memory>
#include <vector>

int main()
{
	// Test a 2-input multiplexer, defined by the boolean equation
	// X=(A & ~S) | (B & S)

	// Typedef some helpful ptr names to make them shorter
	typedef std::shared_ptr<AND> ANDPtr;
	typedef std::shared_ptr<NOT> NOTPtr;
	typedef std::shared_ptr<OR> ORPtr;
	typedef std::shared_ptr<VALUE> VALPtr;
	typedef std::shared_ptr<Gate> GatePtr;

	// Set up our gates
	ANDPtr and1 = std::make_shared<AND>();
	ANDPtr and2 = std::make_shared<AND>();
	NOTPtr not1 = std::make_shared<NOT>();
	ORPtr or1 = std::make_shared<OR>();
	VALPtr A = std::make_shared<VALUE>(true);
	VALPtr B = std::make_shared<VALUE>(false);
	VALPtr S = std::make_shared<VALUE>(true);

	not1->AddLinkedInput(S);

	and1->AddLinkedInput(A);
	and1->AddLinkedInput(not1);

	and2->AddLinkedInput(B);
	and2->AddLinkedInput(S);

	or1->AddLinkedInput(and1);
	or1->AddLinkedInput(and2);

	std::cout << "2-input MUX output with A=1, B=0, S=1: " << or1->Compute() << std::endl;
	*S = false;
	std::cout << "2-input MUX output with A=1, B=0, S=0: " << or1->Compute() << std::endl;

	// Initialize a 2-input MUX based on a test class
	MUX2 testMux = MUX2(false, true, false);

	std::cout << "2-input MUX output with A=0, B=1, S=0: " << testMux.GetOutput() << std::endl;
	testMux.SetS(true);
	std::cout << "2-input MUX output with A=0, B=1, S=1: " << testMux.GetOutput() << std::endl;

	// Initialize a 4-input MUX based on a class inheriting from Circuit
	MUX4 testMux4 = MUX4(true, false, false, true, false, true);

	std::cout << "4-input MUX output with A=1, B=0, C=0, D=1, S1=0, S0=1: " << testMux4.Compute()[0] << std::endl;
	testMux4.SetSwitch(0, false);
	std::cout << "4-input MUX output with A=1, B=0, C=0, D=1, S1=0, S0=0: " << testMux4.Compute()[0] << std::endl;

	// Test the file parsing class
	FileParser newParser = FileParser("TestCircuit.txt");
	Circuit testCircuit = newParser.ParseToCircuit();

	std::vector<GatePtr> testInputs = testCircuit.GetInputs();

	std::cout << "Inputs of parsed test circuit: " << std::endl;
	for (int i = 0; i < testInputs.size(); i++)
	{
		std::cout << testInputs[i]->Compute() << std::endl;
	}

	std::cout << "Output of parsed test circuit: " << std::endl;
	std::cout << testCircuit.Compute()[0] << std::endl;

	// Change all inputs to 1 to ensure output does change when inputs change
	for (int i = 0; i < testInputs.size(); i++)
	{
		VALPtr valPtr = std::dynamic_pointer_cast<VALUE>(testInputs[i]);
		if (valPtr)
		{
			*valPtr = true;
		}
	}

	std::cout << "Output of parsed test circuit with all inputs set to 1: " << std::endl;
	std::cout << testCircuit.Compute()[0] << std::endl;

	system("PAUSE");
	return 0;
}
