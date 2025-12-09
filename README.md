# Semantic Analyzer

A three-stage compiler for a custom signal processing language. The system performs lexical analysis, syntactic parsing, and code generation for programs written in a domain-specific language supporting signal types, complex numbers, and procedural declarations.

## Architecture

The compiler follows a traditional pipeline architecture:

1. **Lexer**: Tokenizes source code into lexemes, maintains symbol tables, and tracks identifiers with their attributes (SIGNAL, COMPLEX, INTEGER, FLOAT, BLOCKFLOAT, EXT).

2. **Parser**: Implements a recursive descent parser that builds an abstract syntax tree (AST) according to the grammar rules defined in `gramatics.md`. Validates syntactic correctness and reports errors.

3. **Generator**: Traverses the AST to generate target code output. Handles variable declarations, procedure definitions, and type mappings.

## Technologies

- **Language**: C++17
- **Build System**: CMake 3.5+
- **Architecture**: Modular library design with separate compilation units


## Building

### Prerequisites

- CMake 3.5 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)

### Local Development

```bash
mkdir build
cd build
cmake ..
make
```

The executable `GENERATOR_EXECUTABLE` will be generated in the `build/app/` directory.

### Production Build

For optimized production builds:

```bash
mkdir build-release
cd build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```

### Alternative Environments

**Debug build:**
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

**Cross-compilation:**
Set `CMAKE_TOOLCHAIN_FILE` to your toolchain configuration:
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/toolchain.cmake ..
```

## Usage

Run the executable and select a test file from the interactive menu:

```bash
./build/app/GENERATOR_EXECUTABLE
```

The application processes test files from the `tests/` directory, performs lexical analysis, parsing, and code generation. Output includes:
- Lexeme stream
- Symbol tables
- Abstract syntax tree
- Generated code listing (written to `output.txt`)
- Error reports (if any)

## Grammar

The language grammar is defined in `gramatics.md`. The language supports:
- Program declarations with procedure identifiers
- Nested procedure declarations with parameter lists
- Variable declarations with type attributes
- Signal, complex, and numeric type modifiers

## Error Handling

The compiler implements comprehensive error reporting through a centralized error logger. Errors are reported at each stage (lexical, syntactic, semantic) with line and column information.

