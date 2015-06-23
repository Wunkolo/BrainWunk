#include <iostream>
#include <iomanip>
#include "BrainWunk.hpp"

int main(int argc, char* argv[])
{
	const char* const Program =
		",>,>,";

	BrainWunk Context;
	std::cout << "Running brainfuck program..." << std::endl;

	std::cout << std::string(64, '-') << std::endl;
	std::cout << Context.Evaluate(Program, &std::cin) << std::endl;
	std::cout << std::string(64, '-') << std::endl;

	std::cout << "Memory dump: " << std::endl;
	std::cout << std::hex << std::uppercase << std::setfill('0');
	for( uint8_t Byte : Context.GetData() )
	{
		std::cout << std::setw(2) << +Byte << ':';
	}

	std::cin.get();
	return 0;
}