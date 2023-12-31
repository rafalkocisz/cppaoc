#ifndef AOC_H
#define AOC_H

#include <source_location>
#include <string>
#include <vector>

#define AOC_FUNCTIONIZE(a, b) \
	a(b)

#define AOC_STRINGIZE(a) \
	#a

#define AOC_TO_STRING(expression) \
	AOC_FUNCTIONIZE(AOC_STRINGIZE, expression)

#define AOC_ASSERT(condition) \
	do \
	{ \
		if(!(condition)) \
		{ \
			aoc::panic("assertion failed with condition '" AOC_TO_STRING(condition) "'"); \
		} \
	} while(0)

#define AOC_ASSERT_MSG(condition, message) \
	do \
	{ \
		if(!(condition)) \
		{ \
			aoc::panic(message); \
		} \
	} while(0)

#define AOC_NUM_ELEMENTS(array) \
	(sizeof(array) / sizeof(*(array)))

namespace aoc
{
	template<class T>
	bool isInRange(const T& value,
	               const T& rangeStart,
	               const T& rangeEnd)
	{
		return (value >= rangeStart) && (value <= rangeEnd);
	}

	std::vector<std::string> loadPuzzleInput(const std::string& puzzleInputFilePath);

	[[noreturn]]
	void panic(const std::string& message,
	           const std::source_location sourceLocation=std::source_location::current());

	class PuzzleSolution
	{
	public:
		virtual ~PuzzleSolution() {}

	public:
		int run(const std::string& puzzleInputFilePath);

	protected:
		const std::vector<std::string>& input() const { return input_; }

	protected:
		virtual void processInput(const std::string& puzzleInputFilePath);

	private:
		virtual int answer1() = 0;
		virtual int answer2() = 0;

	private:
		std::vector<std::string> input_;
	};
}

#endif
