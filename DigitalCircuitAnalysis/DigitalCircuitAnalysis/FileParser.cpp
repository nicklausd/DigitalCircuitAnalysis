/*********************************************************************************
* File: FileParser.cpp
* Author: Nicklaus Dahl
* Description: Implements the FileParser class.
*********************************************************************************/

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include "FileParser.h"

FileParser::FileParser(const std::string& fileName)
{
	fileLines = std::vector<std::string>();
	std::ifstream inFile(fileName);
	if (inFile.is_open())
	{
		std::string currentLine;
		while (std::getline(inFile, currentLine))
		{
			fileLines.push_back(currentLine);
		}
	}
	// The format for an equation file is the following:
	// INPUTS: A B C D ...
	// A & B ...
	// Input and output names can be any alphanumeric tag as long as they start with a letter
	// Verify the first lines and that there are at least 2 lines:
	if (fileLines.size() < 2 || fileLines[0].substr(0, 8) != "INPUTS: ")
	{
		// TODO: probably throw some sort of exception telling the user that their file
		// does not have the correct formatting.
	}
}

Circuit FileParser::ParseToCircuit()
{
	// Typedef a couple of common long names
	typedef std::shared_ptr<Gate> GatePtr;
	typedef std::pair<std::string, GatePtr> IOPair;

	// Relates our input VALUE objects to their names so that the parser can easily
	// refer to specific inputs and link them in where necessary.
	std::map<std::string, GatePtr> inputs;
	
	// Use the boost library to split our INPUTS line into a series of tokens
	// that represent our input names.
	std::string inputsStr = fileLines[0].substr(8);
	std::vector<std::string> splitInputs;
	boost::split(splitInputs, inputsStr, [](char t) {return t == ' '; }, boost::token_compress_on);

	for (std::string inStr : splitInputs)
	{
		// Initialize each VALUE to 0 (false)
		inputs.insert(IOPair(inStr, std::make_shared<VALUE>(false)));
	}

	Circuit newCircuit;

	// Parse each line using the Shunting-yard algorithm. So far, this is only tested with
	// one output equation, but it is designed so that you can write multiple output lines
	// and get a result of multiple output nodes in the Circuit that can be evaluated independently.
	for (int i = 1; i < fileLines.size(); i++)
	{
		// First, tokenize our equation string
		typedef boost::tokenizer<>::iterator TokenIterator;
		boost::tokenizer<> t(fileLines[i]);
		std::vector<std::string> tokens;
		for (TokenIterator beg = t.begin(); beg != t.end(); beg++)
		{
			tokens.push_back(*beg);
		}
		// Now, use the Shunting-yard algorithm to parse our equation
		std::stack<std::string> opStack;
		std::stack<GatePtr> outStack;
		for (int i = 0; i < tokens.size(); i++)
		{
			// Check if token is one of our inputs
			if (inputs.find(tokens[i]) != inputs.end())
			{
				// If the top of the operator stack is a ~, we NOT this operand
				if (!opStack.empty() && opStack.top() == "~")
				{
					GatePtr newNot = std::make_shared<NOT>();
					newNot->AddLinkedInput(inputs[tokens[i]]);
					outStack.push(std::move(newNot));
				}
				else outStack.push(inputs[tokens[i]]);
			}
			else
			{
				// If it's not one of our inputs, it is an operator of some sort. Check first
				// if the operator stack is empty, and if not, we have some other checks to
				// make before adding the operator.
				if (!opStack.empty())
				{
					// If we have a left-parenthesis at the top of stack, just add
					// the operator.
					if (opStack.top() == "(")
					{
						opStack.push(tokens[i]);
					}
					// If we have a right parenthesis as our new token, pop all operators
					// on the stack until we've hit the opening parenthesis.
					else if (tokens[i] == ")")
					{
						while (opStack.top() != "(")
						{
							std::string topOp = opStack.top();
							opStack.pop();
							if (topOp == "&")
							{
								GatePtr newGate = std::make_shared<AND>();
								newGate->AddLinkedInput(outStack.top());
								outStack.pop();
								newGate->AddLinkedInput(outStack.top());
								outStack.pop();
								outStack.push(std::move(newGate));
							}
							else if (topOp == "|")
							{
								GatePtr newGate = std::make_shared<OR>();
								newGate->AddLinkedInput(outStack.top());
								outStack.pop();
								newGate->AddLinkedInput(outStack.top());
								outStack.pop();
								outStack.push(std::move(newGate));
							}
							else if (topOp == "^")
							{
								GatePtr newGate = std::make_shared<XOR>();
								newGate->AddLinkedInput(outStack.top());
								outStack.pop();
								newGate->AddLinkedInput(outStack.top());
								outStack.pop();
								outStack.push(std::move(newGate));
							}
						}
						// Check if there is a NOT on top of stack. If so, we want to NOT
						// the entire expression the parenthesis just created.
						if (!opStack.empty() && opStack.top() == "~")
						{
							GatePtr newNot = std::make_shared<NOT>();
							newNot->AddLinkedInput(outStack.top());
							outStack.pop();
							outStack.push(std::move(newNot));
						}
					}
					// Check if the new token is an operator with higher precedence than
					// the one currently on the stack.
					else if(OpHasPrecedence(tokens[i], opStack.top()))
					{
						// If so, simply push the new operator to the stack.
						opStack.push(tokens[i]);
					}
					// If the new operator does not have precedence, we need to pop and
					// evaluate until we hit a left parenthesis, until the stack is empty,
					// or until the operator has precedence over the top of stack operator.
					else
					{
						while (!opStack.empty() && (opStack.top() != "(" && !OpHasPrecedence(tokens[i], opStack.top())) )
						{
							std::string topOp = opStack.top();
							opStack.pop();
							if (topOp == "&")
							{
								GatePtr newGate = std::make_shared<AND>();
								newGate->AddLinkedInput(outStack.top());
								outStack.pop();
								newGate->AddLinkedInput(outStack.top());
								outStack.pop();
								outStack.push(std::move(newGate));
							}
							else if (topOp == "|")
							{
								GatePtr newGate = std::make_shared<OR>();
								newGate->AddLinkedInput(outStack.top());
								outStack.pop();
								newGate->AddLinkedInput(outStack.top());
								outStack.pop();
								outStack.push(std::move(newGate));
							}
							else if (topOp == "^")
							{
								GatePtr newGate = std::make_shared<XOR>();
								newGate->AddLinkedInput(outStack.top());
								outStack.pop();
								newGate->AddLinkedInput(outStack.top());
								outStack.pop();
								outStack.push(std::move(newGate));
							}
						}
						opStack.push(tokens[i]);
					}
				}
				// If the operator stack is empty, simply add the operator.
				else
				{
					opStack.push(tokens[i]);
				}
			}
		}
		// Now that the equation is parsed, resolve any remaining operators on the stack
		while (!opStack.empty())
		{
			std::string topOp = opStack.top();
			opStack.pop();
			if (topOp == "&")
			{
				GatePtr newGate = std::make_shared<AND>();
				newGate->AddLinkedInput(outStack.top());
				outStack.pop();
				newGate->AddLinkedInput(outStack.top());
				outStack.pop();
				outStack.push(std::move(newGate));
			}
			else if (topOp == "|")
			{
				GatePtr newGate = std::make_shared<OR>();
				newGate->AddLinkedInput(outStack.top());
				outStack.pop();
				newGate->AddLinkedInput(outStack.top());
				outStack.pop();
				outStack.push(std::move(newGate));
			}
			else if (topOp == "^")
			{
				GatePtr newGate = std::make_shared<XOR>();
				newGate->AddLinkedInput(outStack.top());
				outStack.pop();
				newGate->AddLinkedInput(outStack.top());
				outStack.pop();
				outStack.push(std::move(newGate));
			}
		}
		// For a well-formed equation, outStack should now only contain a single GatePtr.
		// This GatePtr will be an output for our new Circuit
		newCircuit.AddOutput(outStack.top());
	}

	// Set the inputs to the Circuit so they can be modified later.
	for (IOPair inPair : inputs)
	{
		newCircuit.AddInput(inPair.second);
	}

	return newCircuit;
}

// Checks if the input leftOp operator has precedence over rightOp during evaluation.
bool FileParser::OpHasPrecedence(std::string leftOp, std::string rightOp)
{
	int leftPrecedence = 0;
	int rightPrecedence = 0;
	if (leftOp == "|") leftPrecedence = 1;
	else if (leftOp == "&") leftPrecedence = 2;
	else if (leftOp == "^") leftPrecedence = 3;
	if (rightOp == "|") rightPrecedence = 1;
	else if (rightOp == "&") rightPrecedence = 2;
	else if (rightOp == "^") rightPrecedence = 3;
	return leftOp > rightOp;
}
