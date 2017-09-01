#include <iostream>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include <streambuf>
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

int main(int argc, char* argv[])
{
	// Parse arguments
	std::unordered_map<std::string, const char*> Args;

	for( size_t i = 1; i < static_cast<size_t>(argc); i++ )
	{
		if( argv[i][0] == '-' )
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

	!Args.count("v") || (std::cout << "BrainWunk:\n\t-Build Date: " << __DATE__ << ' ' << __TIME__ << std::endl);
	if( argc == 1 )
	{
		std::cout << "Usage: Brainwunk -(options) (arguments)" << std::endl;
		std::cout
			<< "\tVerbose output: \t-v\n"
			"\tEvaluate expression: \t-e \"(expression)\"\n"
			"\tEvaluate file: \t-f (filename)\n"
			"\tUse file as input stream: \t-if (filename)\n"
			"\tDump final memory: \t-d|dump\n"
			"\tInteractive mode:  \t-i"
			<< std::endl;
		return EXIT_FAILURE;
	}

	std::string Program;
	std::istream* InStream = &std::cin;
	std::ifstream fIn;
	if( Args.count("if") && Args.at("if") )
	{
		fIn.open(Args.at("if"));
		if( !fIn.good() )
		{
			std::cout << "Unable to open file for reading: " << Args.at("ifile") << std::endl;
			return EXIT_FAILURE;
		}
		InStream = &fIn;
	}

	if( Args.count("e") && Args.at("e") )
	{
		Program = Args.at("e");
	}

	if( Args.count("f") && Args.at("f") )
	{
		std::ifstream ProgramFile(Args.at("f"));
		if( ProgramFile.good() )
		{
			Program = std::string(
				std::istreambuf_iterator<char>(ProgramFile),
				std::istreambuf_iterator<char>());
		}
		else
		{
			std::cout << "Unable to open file for reading: " << Args.at("f") << std::endl;
			return EXIT_FAILURE;
		}
		ProgramFile.close();
	}

	BrainWunk Context;

	!Args.count("v")
		|| (std::cout << std::string(64, '-') << std::endl);

	if( Program.length() )
	{
		try
		{
			std::cout << Context.Evaluate(Program, InStream) << std::endl;
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
				std::cout << "Quitting..." << std::endl;
				break;
			}
			else if( Line == "reset"
				|| Line == "r" )
			{
				Context.Reset();
				std::cout << "Context reset" << std::endl;
			}
			else if( Line == "dump"
				|| Line == "d" )
			{
				std::cout << "Hex dump ["
					<< Context.GetData().size()
					<< " byte(s)]:" << std::endl;
				HexDump(Context.GetData());
				std::cout << std::endl;
			}
			else
			{
				try
				{
					std::string Output = Context.Evaluate(Line, InStream);
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