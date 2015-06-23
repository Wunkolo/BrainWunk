#include "BrainWunk.hpp"

#include <iostream>
#include <algorithm>
#include <stdexcept>

BrainWunk::BrainWunk()
	:
	DataPtr(0)
{
	Data.resize(1, 0);
}

BrainWunk::~BrainWunk()
{
}

std::string BrainWunk::Evaluate(
	const std::string& Expression,
	int(*InputProc)(void))
{
	if( !Expression.length() )
	{
		return "Nothing to evaluate";
	}
	const static std::string Commands = "><+-.,[]";
	std::string Output;
	size_t ProgramCounter = Expression.find_first_of(Commands);
	while( ProgramCounter != std::string::npos )
	{
		switch( Expression[ProgramCounter] )
		{
		case '>': // Increment data pointer
		{
			++DataPtr;
			// Expand data array as necessary

			//Data.resize(std::max(DataPtr,Data.size()),0);
			while( Data.size() < DataPtr + 1 )
			{
				Data.push_back(0);
			}
			break;
		}
		case '<': // Decrement data pointer
		{
			if( DataPtr == 0 )
			{
				// Pointer Underflow
				return "";
			}
			--DataPtr;
			break;
		}
		case '+': // Increment byte at data pointer
		{
			++Data.at(DataPtr);
			break;
		}
		case '-': // Decrement byte at data pointer
		{
			--Data.at(DataPtr);
			break;
		}
		case '.': // Output byte at data pointer
		{
			Output += Data.at(DataPtr);
			break;
		}
		case ',': // Input byte at data pointer
		{
			// Get character
			// Todo
			break;
		}
		case '[':
		{
			Stack.push(ProgramCounter);
			if( Data.at(DataPtr) )
			{
				break;
			}
			size_t Balanace = 1;
			while( Balanace )
			{
				ProgramCounter++;
				if( ProgramCounter > Expression.length() )
				{
					// Expected a ]
					return "";
				}
				if( Expression[ProgramCounter] == '[' )
				{
					Balanace++;
				}
				else if( Expression[ProgramCounter] == ']' )
				{
					Balanace--;
				}
			}
			break;
		}
		case ']':
		{
			if( Data.at(DataPtr) )
			{
				ProgramCounter = Stack.top() - 1;
			}
			Stack.pop();
			break;
		}
		}
		ProgramCounter = Expression.find_first_of(Commands, ProgramCounter + 1);
	}
	if( Stack.size() )
	{
		// Expected a ] at end of program
		return "";
	}
	return Output;
}