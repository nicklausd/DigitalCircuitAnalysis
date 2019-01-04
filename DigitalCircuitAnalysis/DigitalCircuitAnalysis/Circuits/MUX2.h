/*********************************************************************************
* File: MUX2.h
* Author: Nicklaus Dahl
* Description: Declares the MUX2 class. This class represents a 2-input
*    multiplexer circuit with inputs A and B and select signal S.
*********************************************************************************/

#pragma once
#include "../LogicGates.h"
#include <vector>

class MUX2
{
	std::shared_ptr<AND> and1;
	std::shared_ptr<AND> and2;
	std::shared_ptr<NOT> not1;
	std::shared_ptr<OR> or1;
	std::shared_ptr<VALUE> A;
	std::shared_ptr<VALUE> B;
	std::shared_ptr<VALUE> C;
	std::shared_ptr<VALUE> S;
public:
	MUX2(bool a, bool b, bool s);

	bool GetOutput();

	bool GetA();
	void SetA(bool val);
	bool GetB();
	void SetB(bool val);
	bool GetS();
	void SetS(bool val);
};
