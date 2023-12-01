#ifndef AOC_H
#define AOC_H

#include <source_location>
#include <string>
#include <vector>

#define AOC_ASSERT(condition, message) \
	do \
	{ \
		if(!(condition)) \
		{ \
			aoc::panic(message); \
		} \
	} while(0)

namespace aoc
{
	std::vector<std::string> loadPuzzleInput(const std::string& puzzleInputFilePath);

	[[noreturn]] void panic(const std::string& message,
	                        const std::source_location sourceLocation=std::source_location::current());

	class PuzzleSolution
	{
	public:
		virtual ~PuzzleSolution() {}

	public:
		int run(const std::string& puzzleInputFilePath);

	protected:
		const std::vector<std::string>& input() const { return input_; }

	private:
		virtual void processInput(const std::string& puzzleInputFilePath);
		virtual int findAnswer1() = 0;
		virtual int findAnswer2() = 0;

	private:
		std::vector<std::string> input_;
	};
}

#endif
