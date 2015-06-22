#include <iostream>
#include "BrainWunk.hpp"

int main(int argc, char* argv[])
{
	const char* const Program =
		"+[>++++++++";

	//std::cout << "Running brainfuck program..." << std::endl;

	BrainWunk Context;
	std::cout << Context.Evaluate(Program) << std::endl;
	std::cin.get();
	return 0;
}