/*********************************************************************************
* File: MUX4.h
* Author: Nicklaus Dahl
* Description: Declares the MUX4 class. This class represents a 4-input
*    multiplexer circuit with inputs A, B, C, and D, and select signals S1 and S0.
*    This is derived from the Circuit class to demonstrate how different Circuits
*    may be implemented using it.
*********************************************************************************/

#pragma once
#include "Circuit.h"

class MUX4 : public Circuit
{
	typedef std::shared_ptr<Gate> GatePtr;
	typedef std::shared_ptr<VALUE> VALPtr;
	std::vector<VALPtr> muxInputs;
	std::vector<VALPtr> muxSwitches;
public:
	MUX4(bool a, bool b, bool c, bool d, bool sw1, bool sw0);
	MUX4(VALUE a, VALUE b, VALUE c, VALUE d, VALUE sw1, VALUE sw0);

	void SetInput(int input, bool val);
	void SetInput(int input, VALUE val);
	void SetSwitch(int sw, bool val);
	void SetSwitch(int sw, VALUE val);
};
