#include <bits/stdint-uintn.h>
#include <iostream>
#include "vm.h"

BrainfuckVm::BrainfuckVm(std::vector<Instr> instrs, size_t tape_size):
	_instrs(instrs),
	_instr_ptr(0),
	_tape(std::vector<uint8_t>(tape_size, 0)),
	_tape_ptr(0)
{}

void BrainfuckVm::step() {
	auto instr = _instrs[_instr_ptr];
	if (instr.kind == InstrKind::Plus) {
		_tape[_tape_ptr] += instr.repeat;
	} else if (instr.kind == InstrKind::Minus) {
		_tape[_tape_ptr] -= instr.repeat;
	} else if (instr.kind == InstrKind::Right) {
		_tape_ptr += instr.repeat;
		if (_tape_ptr == _tape.size()) _tape_ptr = 0;
	} else if (instr.kind == InstrKind::Left) {
		if (_tape_ptr < instr.repeat) _tape_ptr += _tape.size();
		_tape_ptr -= instr.repeat;
	} else if (instr.kind == InstrKind::Out) {
		std::cout << (char) _tape[_tape_ptr];
	} else if (instr.kind == InstrKind::In) {
		std::cin >> _tape[_tape_ptr];
	} else if (instr.kind == InstrKind::LoopStart) {
		if (_tape[_tape_ptr] == 0) _instr_ptr = instr.opposite_bracket;
	} else if (instr.kind == InstrKind::LoopEnd) {
		if (_tape[_tape_ptr] != 0) _instr_ptr = instr.opposite_bracket;
	} else {
		// Brainfuck ignores other chars
	}
	_instr_ptr++;
}

bool BrainfuckVm::is_done() {
	return _instr_ptr >= _instrs.size();
}

void BrainfuckVm::run_to_end() {
	while (!is_done()) step();
}