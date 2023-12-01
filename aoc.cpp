#include "aoc.h"

#define FMT_HEADER_ONLY
#include "fmt/format.h"

#include <cstdlib>
#include <fstream>

using namespace fmt;
using namespace std;

namespace aoc
{
	vector<string> loadPuzzleInput(const string& puzzleInputFilePath) 
	{
		ifstream fileStream{puzzleInputFilePath};

		if(!fileStream.is_open())
			panic(format("unable to open input file: \"{}\"", puzzleInputFilePath));

		vector<string> input;
		string line;

		while(getline(fileStream, line))
			input.push_back(line);

		return input;
	}

	[[noreturn]] void panic(const string& message,
	                        source_location sourceLocation)
	{
#ifndef AOC_TEST
		constexpr fmt::string_view panicMessageFormat = "`{}` panicked at {}({}:{}) with message: `{}`.";

		println(stderr,
		        panicMessageFormat,
		        sourceLocation.function_name(),
		        sourceLocation.file_name(),
		        sourceLocation.line(),
		        sourceLocation.column(),
		        message);

		exit(EXIT_FAILURE);
#else
		throw std::runtime_error(message);
#endif
	}

	int PuzzleSolution::run(const std::string& puzzleInputFilePath)
	{
		processInput(puzzleInputFilePath);

		println("{}", findAnswer1());
		println("{}", findAnswer2());

		return EXIT_SUCCESS;
	}

	void PuzzleSolution::processInput(const std::string& puzzleInputFilePath)
	{
		input_ = loadPuzzleInput(puzzleInputFilePath);
	}
}
