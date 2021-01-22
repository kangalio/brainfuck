# Simple Brainfuck interpreter

This project implements a simple optimizing interpreter of the esoteric
[Brainfuck language](https://en.wikipedia.org/wiki/Brainfuck),
invented by Urban Müller in 1993.

Please see the wikipedia page for an introduction to the language, in case you're not familiar
already.

This interpreter analyzes the code ahead of time and merges subsequent operations together into
single, more performant instructions.

## Running

No libraries are required, however the C++17 standard or higher is needed.

This program is compiled using CMake. An example compilation process, assuming Linux:
```sh
mkdir build
cd build
cmake ..
make -j6
```

Invoke the program with no parameters to get usage information. Invoke the program with a path to
a brainfuck file to execute it.

To get started, you can try out some of the supplied sample programs in the `samples/` folder.

## Code structure

- `main.cpp` - Input handling and general program flow
- `parse.cpp/.h` - Parse raw Brainfuck code into slightly-optimized instructions
- `vm.cpp/.h` - Execute Brainfuck instructions
- `structures.h` - Structs for the instructions

## Addressed rubric points

- [x] A variety of control structures are used in the project.
- [x] The project code is clearly organized into functions.
- [x] The project reads data from an external file or writes data to a file as part of the necessary operation of the program.
- [x] The project accepts input from a user as part of the necessary operation of the program.
- [x] The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
- [x] All class data members are explicitly specified as public, protected, or private.
- [x] All class members that are set to argument values are initialized through member initialization lists.
- [x] All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.
- [x] Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.