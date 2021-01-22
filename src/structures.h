#pragma once
#include <cstddef>

enum class InstrKind {
	Plus,
	Minus,
	Right,
	Left,
	Out,
	In,
	LoopStart,
	LoopEnd
};

struct Instr {
	InstrKind kind;
	// Only used in Plus, Minus, Right, and Left, otherwise 1
	int repeat;
	// Only applies to Loop and End, otherwise 0
	size_t opposite_bracket;
};