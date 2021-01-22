#include "parse.h"
#include <cstddef>
#include <endian.h>

std::vector<Instr> parse(std::string &code) {
	std::vector<size_t> stack;

	std::vector<Instr> instrs;
	for (int i = 0; i < code.size(); i++) {
		InstrKind kind;
		switch (code[i]) {
			case '+': kind = InstrKind::Plus; break;
			case '-': kind = InstrKind::Minus; break;
			case '>': kind = InstrKind::Right; break;
			case '<': kind = InstrKind::Left; break;
			case '.': kind = InstrKind::Out; break;
			case ',': kind = InstrKind::In; break;
			case '[': kind = InstrKind::LoopStart; break;
			case ']': kind = InstrKind::LoopEnd; break;
			default: continue;
		}

		if (code[i] == '+' || code[i] == '-' || code[i] == '>' || code[i] == '<') {
			auto first_char = code[i];

			int num_consecutive = 0;
			for (; i < code.size(); i++) {
				if (code[i] != first_char) break;
				num_consecutive++;
			}
			i--;

			instrs.push_back(Instr { kind, num_consecutive, 0 });
		} else if (code[i] == '[') {
			stack.push_back(instrs.size());

			instrs.push_back(Instr { kind, 1, 0 /* will be set later */ });
		} else if (code[i] == ']') {
			if (stack.size() == 0) throw "superfluous closing bracket";

			auto loop_start = stack[stack.size() - 1];
			stack.pop_back();

			instrs[loop_start].opposite_bracket = instrs.size();
			instrs.push_back(Instr { kind, 1, loop_start });
		} else {
			instrs.push_back(Instr { kind, 1, 0 });
		}
	}

	if (stack.size() > 0) throw "missing closing bracket";

	return instrs;
}