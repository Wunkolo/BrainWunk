#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <stack>

/*	Describes a Brainfuck context
	Expressions can be evaluated and data will
	persist between expressions. Input data used
	by the ',' command will first deplete the
	interal input buffer before resorting to the
	provided std::istream. If the istream is not
	specified and the Input buffer is empty,
	the command will leave everything unchanged.
	*/
class BrainWunk
{
public:
	BrainWunk();
	~BrainWunk();

	// Evaluates an expression and returns all output from the '.' command
	// InputStream is called when Input buffer is depleted
	std::string Evaluate(
		const std::string& Expression,
		std::istream* InputStream = nullptr);

	// A read-only copy of the context's memory.
	const std::vector<uint8_t>& GetData() const
	{
		return this->Data;
	}

	// Append additional input data for the ',' command to read from
	void PushInput(const std::string& Input);

	// Reset's context into an default state.
	void Reset();

private:

	// Context Data
	size_t DataPtr;
	std::vector<uint8_t> Data;

	// Subroutine return addresses
	std::stack<size_t> Stack;

	// Buffered input data depleated by ',' commands
	std::string Input;
};