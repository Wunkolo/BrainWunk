#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <stack>

// Disable throw(const char*) warning
#pragma warning(disable : 4290)

class BrainWunk
{
public:
	BrainWunk();
	~BrainWunk();
	std::string Evaluate(
		const std::string& Expression,
		std::istream* InputStream = nullptr
	) throw(const char*);

	const std::vector<std::uint8_t>& GetData() const
	{
		return this->Data;
	}

	void PushInput(const std::string& Input);

	void Reset();

private:

	std::size_t DataPtr;
	std::vector<std::uint8_t> Data;

	std::stack<std::size_t> Stack;

	std::string Input;
};
