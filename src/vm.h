#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>
#include "structures.h"

class BrainfuckVm {
public:
	BrainfuckVm(std::vector<Instr> instrs, size_t tape_size);

	// Execute a single instruction (remember that an instruction may consist of several brainfuck
	// characters)
	void step();
	// Returns whether all instructions have been executed
	bool is_done() const;
	// Execute all instructions until the end is reached
	void run_to_end();

private:
	const std::vector<Instr> _instrs;
	size_t _instr_ptr;

	std::vector<uint8_t> _tape;
	size_t _tape_ptr;
};