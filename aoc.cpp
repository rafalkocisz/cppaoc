#include "aoc.h"

#if defined(AOC_TEST)
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#endif

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
#if defined(AOC_TEST) || defined(AOC_TEST_SOLUTION)
		throw runtime_error(message);
#else
		constexpr fmt::string_view panicMessageFormat = "`{}` panicked at {}({}:{}) with message: `{}`.";

		println(stderr,
		        panicMessageFormat,
		        sourceLocation.function_name(),
		        sourceLocation.file_name(),
		        sourceLocation.line(),
		        sourceLocation.column(),
		        message);

		exit(EXIT_FAILURE);
#endif
	}

	int PuzzleSolution::run(const string& puzzleInputFilePath)
	{
		processInput(puzzleInputFilePath);

		println("{}", answer1());
		println("{}", answer2());

		return EXIT_SUCCESS;
	}

	void PuzzleSolution::processInput(const string& puzzleInputFilePath)
	{
		input_ = loadPuzzleInput(puzzleInputFilePath);
	}
}

#if defined(AOC_TEST)

namespace aoc
{
	TEST_CASE("isInRange")
	{
		CHECK(isInRange(1, 1, 10) == true);
		CHECK(isInRange(5, 1, 10) == true);
		CHECK(isInRange(10, 1, 10) == true);
		CHECK(isInRange(0, 1, 10) == false);
		CHECK(isInRange(11, 1, 10) == false);
		CHECK(isInRange(-10, 1, 10) == false);
		CHECK(isInRange(20, 1, 10) == false);
		CHECK(isInRange(3, -1, 3) == true);
	}
}

#endif
