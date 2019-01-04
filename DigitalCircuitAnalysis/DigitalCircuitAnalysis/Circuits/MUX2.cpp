/*********************************************************************************
* File: MUX2.cpp
* Author: Nicklaus Dahl
* Description: Implements the MUX2 class.
*********************************************************************************/

#include "MUX2.h"

MUX2::MUX2(bool a, bool b, bool s) /*: A(a), B(b), S(s)*/
{
	// Set up all gates needed to implement a 2-input MUX.
	A = std::make_shared<VALUE>(a);
	B = std::make_shared<VALUE>(b);
	S = std::make_shared<VALUE>(s);
	not1 = std::make_shared<NOT>();
	and1 = std::make_shared<AND>();
	and2 = std::make_shared<AND>();
	or1 = std::make_shared<OR>();

	not1->AddLinkedInput(S);

	and1->AddLinkedInput(A);
	and1->AddLinkedInput(not1);

	and2->AddLinkedInput(B);
	and2->AddLinkedInput(S);

	or1->AddLinkedInput(and1);
	or1->AddLinkedInput(and2);
}

// Get the current output of the MUX.
bool MUX2::GetOutput()
{
	return or1->Compute();
}

// Get the first input to the MUX
bool MUX2::GetA()
{
	return A->Compute();
}

// Set the value of the first input of the MUX
void MUX2::SetA(bool val)
{
	*A = val;
}

// Get the second input to the MUX
bool MUX2::GetB()
{
	return B->Compute();
}

// Set the value of the second input of the MUX
void MUX2::SetB(bool val)
{
	*B = val;
}

// Get the select bit
bool MUX2::GetS()
{
	return S->Compute();
}

// Set the select bit
void MUX2::SetS(bool val)
{
	*S = val;
}


