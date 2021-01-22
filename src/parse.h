#pragma once
#include <vector>
#include <string>
#include "structures.h"

// Parse a Brainfuck code string into a list of instructions
// Subsequent increments/decrements/pointer moves are condensed into single instructions
std::vector<Instr> parse(std::string &code);