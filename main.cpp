#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "BrainWunk.hpp"

void HexDump(const std::vector<uint8_t>& Data)
{
	std::cout << std::hex << std::uppercase << std::setfill('0');

	for( uint8_t Byte : Data )
	{
		std::cout << std::setw(2) << +Byte << ':';
	}
}

//-hoot honk -v -i "poop doot" -a -b -c f
int main(int argc, char* argv[])
{
	if( argc == 1 )
	{
		std::cout << "Usage: Brainwunk -(options) (arguments)" << std::endl;
		std::cout
			<< "\tVerbose output: \t-v\n"
			"\tEvaluate expression: \t-e \"(expression)\"\n"
			"\tDump final memory: \t-d\n"
			<< std::endl;
		return EXIT_FAILURE;
	}

	const char* Program = nullptr;
	std::unordered_map<std::string, const char*> Args;

	for( size_t i = 1; i < static_cast<size_t>(argc); i++ )
	{
		if( argv[i][0] = '-' )
		{
			Args[argv[i] + 1] = nullptr;
			if( (i + 1) < argc )
			{
				if( argv[i + 1][0] != '-' )
				{
					Args[argv[i] + 1] = argv[i + 1];
					i++;
				}
			}
		}
		else
		{
			Args[argv[i]] = nullptr;
		}
	}

	// Evaluate an expression
	if( Args.count("eval") && Args.at("eval") )
	{
		!Args.count("v")
			|| (std::cout << "Running brainfuck expression" << std::endl);
		Program = Args.at("eval");
	}

	if( !Program )
	{
		std::cout << "No program to evaluate" << std::endl;
		return EXIT_FAILURE;
	}

	BrainWunk Context;

	!Args.count("v")
		|| (std::cout << std::string(64, '-') << std::endl);
	std::cout << Context.Evaluate(Program, &std::cin) << std::endl;
	!Args.count("v")
		|| (std::cout << std::string(64, '-') << std::endl);

	if( Args.count("d") )
	{
		std::cout << "Hex dump ["
			<< Context.GetData().size()
			<< " byte(s)]:" << std::endl;
		HexDump(Context.GetData());
	}
	return EXIT_SUCCESS;
}