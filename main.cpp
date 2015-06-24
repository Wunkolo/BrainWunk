#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "BrainWunk.hpp"

#define PS1 "~> "

void HexDump(const std::vector<uint8_t>& Data)
{
	std::cout << std::hex << std::uppercase << std::setfill('0');

	for( std::vector<uint8_t>::const_iterator it = Data.cbegin();
		it != Data.cend();
		it++ )
	{
		std::cout << std::setw(2) << +(*it) << (it + 1 == Data.end() ? ' ' : ':');
	}
}

//-hoot honk -v -i "poop doot" -a -b -c f
int main(int argc, char* argv[])
{
	std::cout << "BrainWunk:\n\t-Build Date: "__TIMESTAMP__ << std::endl;
	if( argc == 1 )
	{
		std::cout << "Usage: Brainwunk -(options) (arguments)" << std::endl;
		std::cout
			<< "\tVerbose output: \t-v\n"
			"\tEvaluate expression: \t-e \"(expression)\"\n"
			"\tDump final memory: \t-d\n"
			"\tInteractive mode:  \t-i"
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
			if( (i + 1) < static_cast<size_t>(argc) )
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
	if( Args.count("eval") && Args.at("eval") )
	{
		!Args.count("v")
			|| (std::cout << "Running brainfuck expression" << std::endl);
		Program = Args.at("eval");
	}

	BrainWunk Context;

	!Args.count("v")
		|| (std::cout << std::string(64, '-') << std::endl);

	if( Program )
	{
		try
		{
			std::cout << Context.Evaluate(Program, &std::cin) << std::endl;
		}
		catch( const char* e )
		{
			std::cout << " Error evaluating expression: " << e << std::endl;
		}
	}

	!Args.count("v")
		|| (std::cout << std::string(64, '-') << std::endl);

	// Interactive mode
	if( Args.count("i") )
	{
		std::string Line;
		std::cout << PS1;
		while( std::getline(std::cin, Line) )
		{
			if( Line == "quit"
				|| Line == "q" )
			{
				break;
			}
			else if( Line == "reset"
				|| Line == "r" )
			{
				Context.Reset();
			}
			else if( Line == "dump"
				|| Line == "d" )
			{
				HexDump(Context.GetData());
				std::cout << std::endl;
			}
			else
			{
				try
				{
					std::string Output = Context.Evaluate(Line, &std::cin);
					if( Output.length() ) // Only print when there is output
					{
						std::cout << Output << std::endl;
					}
				}
				catch( const char* e )
				{
					std::cout << " Error evaluating expression: " << e << std::endl;
				}
			}
			std::cout << PS1;
		}
	}

	if( Args.count("d") )
	{
		std::cout << "Hex dump ["
			<< Context.GetData().size()
			<< " byte(s)]:" << std::endl;
		HexDump(Context.GetData());
	}

	return EXIT_SUCCESS;
}