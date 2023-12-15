#include "aoc.h"

#ifdef AOC_TEST
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#endif

#define FMT_HEADER_ONLY
#include "fmt/format.h"

#include <cassert>
#include <string>

using namespace fmt;
using namespace aoc;
using namespace std;

int floorOffset(char instruction)
{

	switch(instruction)
	{
		case '(': return 1;
		case ')': return -1;
	}

	panic(format("invalid instruction: '{}'", instruction));

	return 0;
}

int findFloor(const string& instructions)
{
	int floor = 0;

	for(char instruction : instructions)
		floor += floorOffset(instruction);

	return floor;
}

int findEnterTheBasementInstructionPosition(const string& instructions)
{
	int floor = 0;

	for(size_t i=0; i<instructions.size(); ++i)
	{
		floor += floorOffset(instructions[i]);

		if(floor == -1)
			return i + 1;
	}

	panic(format("no 'enter the basement' instruction found"));

	return -1;
}

#ifdef AOC_TEST

TEST_CASE("floorOffset")
{
	CHECK(floorOffset('(') == 1);
	CHECK(floorOffset(')') == -1);
	CHECK_THROWS_WITH_AS(floorOffset('-'), "invalid instruction: '-'", runtime_error);
	CHECK_THROWS_WITH_AS(floorOffset('\''), "invalid instruction: '''", runtime_error);
	CHECK_THROWS_WITH_AS(floorOffset(' '), "invalid instruction: ' '", runtime_error);
	CHECK_THROWS_WITH_AS(floorOffset('\t'), "invalid instruction: '\t'", runtime_error);
}

TEST_CASE("findFloor")
{
	CHECK(findFloor("") == 0);
	CHECK(findFloor("(())") == 0);
	CHECK(findFloor("()()") == 0);
	CHECK(findFloor("(((") == 3);
	CHECK(findFloor("(()(()(") == 3);
	CHECK(findFloor("))(((((") == 3);
	CHECK(findFloor("())") == -1);
	CHECK(findFloor("))(") == -1);
	CHECK(findFloor(")))") == -3);
	CHECK(findFloor(")())())") == -3);
	CHECK_THROWS_WITH_AS(findFloor("!(())"), "invalid instruction: '!'", runtime_error);
	CHECK_THROWS_WITH_AS(findFloor("((@))"), "invalid instruction: '@'", runtime_error);
	CHECK_THROWS_WITH_AS(findFloor(")())())#"), "invalid instruction: '#'", runtime_error);
}

TEST_CASE("findEnterTheBasementInstructionPosition")
{
	CHECK(findEnterTheBasementInstructionPosition(")") == 1);
	CHECK(findEnterTheBasementInstructionPosition("()())") == 5);
	CHECK_THROWS_WITH_AS(findEnterTheBasementInstructionPosition("_()())"), "invalid instruction: '_'", runtime_error);
	CHECK_THROWS_WITH_AS(findEnterTheBasementInstructionPosition("() ())"), "invalid instruction: ' '", runtime_error);
	CHECK_THROWS_WITH_AS(findEnterTheBasementInstructionPosition("((($"), "invalid instruction: '$'", runtime_error);
	CHECK_THROWS_WITH_AS(findEnterTheBasementInstructionPosition(""), "no 'enter the basement' instruction found", runtime_error);
	CHECK_THROWS_WITH_AS(findEnterTheBasementInstructionPosition("("), "no 'enter the basement' instruction found", runtime_error);
	CHECK_THROWS_WITH_AS(findEnterTheBasementInstructionPosition("(((())))"), "no 'enter the basement' instruction found", runtime_error);
}

#else

class NotQuiteLisp : public PuzzleSolution
{
private:
	int answer1() override;
	int answer2() override;
};

int NotQuiteLisp::answer1()
{
	AOC_ASSERT_MSG(input().size() == 1, "invalid size of the input: only one line expected");

	return findFloor(input()[0]);
}

int NotQuiteLisp::answer2()
{
	AOC_ASSERT_MSG(input().size() == 1, "invalid size of the input: only one line expected");

	return findEnterTheBasementInstructionPosition(input()[0]);
}

int main(int argc, char* argv[])
{
	return NotQuiteLisp().run((argc > 1) ? argv[1] : "201501.txt");
}

#endif
