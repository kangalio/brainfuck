#pragma once
#include <array>
#include <bits/stdint-uintn.h>
#include <string>
#include <vector>
#include "structures.h"

class BrainfuckVm {
public:
	BrainfuckVm(std::vector<Instr> instrs, size_t tape_size);

	void step();
	void run_to_end();

private:
	const std::vector<Instr> _instrs;
	size_t _instr_ptr;

	std::vector<uint8_t> _tape;
	size_t _tape_ptr;
};