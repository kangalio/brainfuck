#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include "vm.h"
#include "parse.h"

// Sigh, I miss Rust and its utility functions
std::string read_to_string(std::string path) {
	std::ifstream t(path);
	if (!t) {
		std::cout << "Error: couldn't read file \"" << path << "\"\n";
		exit(1);
	}
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}

void print_instructions(std::vector<Instr> &instrs) {
	for (int i = 0; i < instrs.size(); i++) {
		char symbol;
		switch (instrs[i].kind) {
			case InstrKind::Plus: symbol = '+'; break;
			case InstrKind::Minus: symbol = '-'; break;
			case InstrKind::Right: symbol = '>'; break;
			case InstrKind::Left: symbol = '<'; break;
			case InstrKind::Out: symbol = '.'; break;
			case InstrKind::In: symbol = ','; break;
			case InstrKind::LoopStart: symbol = '['; break;
			case InstrKind::LoopEnd: symbol = ']'; break;
		}

		std::cout << i << ": " << symbol;
		if (symbol == '+' || symbol == '-' || symbol == '>' || symbol == '<') {
			if (instrs[i].repeat != 1) {
				std::cout << " x" << instrs[i].repeat;
			}
		}
		if (symbol == '[' || symbol == ']') {
			std::cout << " -> " << instrs[i].opposite_bracket;
		}

		std::cout << "\n";
	}
}

int main(int argc, char **argv) {
	bool debug = false;
	char* path = nullptr;
	for (int i = 1; i < argc; i++) {
		if (std::strcmp(argv[i], "-d") == 0) {
			debug = true;
			continue;
		}

		if (path != nullptr) {
			std::cout << "Warning: ignoring superfluous input path \"" << path << "\"\n";
		}
		path = argv[i];
	}

	if (path == nullptr) {
		std::cout << "Usage: " << argv[0] << " [-d] <file_to_execute>\n";
		std::cout << "Flags:\n";
		std::cout << " -d: print debug information";
		return 0;
	}

	auto code = parse(read_to_string(path));
	if (debug) print_instructions(code);
	BrainfuckVm vm(code, 30000); // Memory size 30k is standard for brainfuck
	vm.run_to_end();
}
