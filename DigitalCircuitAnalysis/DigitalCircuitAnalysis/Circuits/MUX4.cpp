/*********************************************************************************
* File: MUX4.cpp
* Author: Nicklaus Dahl
* Description: Implements the MUX4 class.
*********************************************************************************/

#include "MUX4.h"

// The truth table for a 4-input MUX is:
// | S1  | S0  ||  O  |
// |  0  |  0  ||  A  |
// |  0  |  1  ||  B  |
// |  1  |  0  ||  C  |
// |  1  |  1  ||  D  |
// Where A, B, C, and D are the input values.
// This gives the function:
// O = (A & ~S1 & ~S0) | (B & ~S1 & S0) | (C & S1 & ~S0) | (D & S1 & S0)

MUX4::MUX4(bool a, bool b, bool c, bool d, bool sw1, bool sw0)
{
	// Set up VALUE objects for each input and select bit
	VALPtr A = std::make_shared<VALUE>(a);
	VALPtr B = std::make_shared<VALUE>(b);
	VALPtr C = std::make_shared<VALUE>(c);
	VALPtr D = std::make_shared<VALUE>(d);
	VALPtr S1 = std::make_shared<VALUE>(sw1);
	VALPtr S0 = std::make_shared<VALUE>(sw0);

	// We will need two NOT gates, four AND gates, and one OR gate.

	GatePtr not1 = std::make_shared<NOT>();
	GatePtr not2 = std::make_shared<NOT>();
	GatePtr and1 = std::make_shared<AND>();
	GatePtr and2 = std::make_shared<AND>();
	GatePtr and3 = std::make_shared<AND>();
	GatePtr and4 = std::make_shared<AND>();
	GatePtr or1 = std::make_shared<OR>();

	not1->AddLinkedInput(S1);
	not2->AddLinkedInput(S0);

	and1->AddLinkedInput(A);
	and1->AddLinkedInput(not1);
	and1->AddLinkedInput(not2);

	and2->AddLinkedInput(B);
	and2->AddLinkedInput(not1);
	and2->AddLinkedInput(S0);

	and3->AddLinkedInput(C);
	and3->AddLinkedInput(S1);
	and3->AddLinkedInput(not2);

	and4->AddLinkedInput(D);
	and4->AddLinkedInput(S1);
	and4->AddLinkedInput(S0);

	or1->AddLinkedInput(and1);
	or1->AddLinkedInput(and2);
	or1->AddLinkedInput(and3);
	or1->AddLinkedInput(and4);

	// Add each node to the parent class Circuit's vectors to store
	// the input, output, and network nodes.
	AddOutput(or1);
	AddInput(A);
	AddInput(B);
	AddInput(C);
	AddInput(D);
	AddInput(S1);
	AddInput(S0);
	AddToNetwork(not1);
	AddToNetwork(not2);
	AddToNetwork(and1);
	AddToNetwork(and2);
	AddToNetwork(and3);
	AddToNetwork(and4);

	// Add to internal vectors to easily modify in other functions.
	muxInputs.push_back(VALPtr(A));
	muxInputs.push_back(VALPtr(B));
	muxInputs.push_back(VALPtr(C));
	muxInputs.push_back(VALPtr(D));
	muxSwitches.push_back(VALPtr(S0));
	muxSwitches.push_back(VALPtr(S1));
}

// Same as MUX4(bool, bool, bool, bool, bool, bool) but accepts all arguments
// as VALUE objects.
MUX4::MUX4(VALUE a, VALUE b, VALUE c, VALUE d, VALUE sw1, VALUE sw0)
{
	VALPtr A = std::make_shared<VALUE>(a);
	VALPtr B = std::make_shared<VALUE>(b);
	VALPtr C = std::make_shared<VALUE>(c);
	VALPtr D = std::make_shared<VALUE>(d);
	VALPtr S1 = std::make_shared<VALUE>(sw1);
	VALPtr S0 = std::make_shared<VALUE>(sw0);

	// We will need two NOT gates, four AND gates, and one OR gate.

	GatePtr not1 = std::make_shared<NOT>();
	GatePtr not2 = std::make_shared<NOT>();
	GatePtr and1 = std::make_shared<AND>();
	GatePtr and2 = std::make_shared<AND>();
	GatePtr and3 = std::make_shared<AND>();
	GatePtr and4 = std::make_shared<AND>();
	GatePtr or1 = std::make_shared<OR>();

	not1->AddLinkedInput(S1);
	not2->AddLinkedInput(S0);

	and1->AddLinkedInput(A);
	and1->AddLinkedInput(not1);
	and1->AddLinkedInput(not2);

	and2->AddLinkedInput(B);
	and2->AddLinkedInput(not1);
	and2->AddLinkedInput(S0);

	and3->AddLinkedInput(C);
	and3->AddLinkedInput(S1);
	and3->AddLinkedInput(not2);

	and4->AddLinkedInput(D);
	and4->AddLinkedInput(S1);
	and4->AddLinkedInput(S0);

	or1->AddLinkedInput(and1);
	or1->AddLinkedInput(and2);
	or1->AddLinkedInput(and3);
	or1->AddLinkedInput(and4);

	AddOutput(or1);
	AddInput(A);
	AddInput(B);
	AddInput(C);
	AddInput(D);
	AddInput(S0);
	AddInput(S1);
	AddToNetwork(not1);
	AddToNetwork(not2);
	AddToNetwork(and1);
	AddToNetwork(and2);
	AddToNetwork(and3);
	AddToNetwork(and4);

	muxInputs.push_back(VALPtr(A));
	muxInputs.push_back(VALPtr(B));
	muxInputs.push_back(VALPtr(C));
	muxInputs.push_back(VALPtr(D));
	muxSwitches.push_back(VALPtr(S0));
	muxSwitches.push_back(VALPtr(S1));
}

// Set MUX input at the specified index to the specified bool value.
void MUX4::SetInput(int input, bool val)
{
	if (input > 3)
		return; // Probably better to throw an error but this will do for now

	*(muxInputs[input]) = val;
}

// Set MUX input at the specified index to the specified VALUE.
void MUX4::SetInput(int input, VALUE val)
{
	if (input > 3) return;
	*(muxInputs[input]) = val;
}

// Set specified select bit
void MUX4::SetSwitch(int sw, bool val)
{
	if (sw > 1) return;
	*(muxSwitches[sw]) = val;
}

// Set specified select bit
void MUX4::SetSwitch(int sw, VALUE val)
{
	if (sw > 1) return;
	*(muxSwitches[sw]) = val;
}
