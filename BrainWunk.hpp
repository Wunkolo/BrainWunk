#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <stack>

// Describes a Brainfuck context
// Data array expands only as needed.
//
class BrainWunk
{
public:
	BrainWunk();
	~BrainWunk();

	// Evaluates an expression and returns all output
	// Data array persists between expressions
	std::string Evaluate(const std::string& Expression);
private:

	size_t DataPtr;
	std::vector<uint8_t> Data;
	// Subroutine "return addresses"
	std::stack<size_t> Stack;
};