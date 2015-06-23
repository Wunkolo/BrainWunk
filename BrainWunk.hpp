#pragma once
#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>
#include <stack>

// Describes a Brainfuck context
// Data array expands only as needed.
class BrainWunk
{
public:
	BrainWunk();
	~BrainWunk();

	// Evaluates an expression and returns all output
	// Data array persists between expressions
	// InputProc is called when buffered input is depleted of data
	std::string Evaluate(
		const std::string& Expression,
		std::istream* InputStream = &std::cin);

	// Add additional input data for
	void PushInput(const std::string& Input)
	{
		this->Input += Input;
	}

	const std::vector<uint8_t>& GetData() const
	{
		return this->Data;
	}

private:

	// Context Data
	size_t DataPtr;
	std::vector<uint8_t> Data;

	// Subroutine "return addresses"
	std::stack<size_t> Stack;

	// Buffered input data depleated by , commands
	std::string Input;
};