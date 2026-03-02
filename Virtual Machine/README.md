# Simple Virtual Machine in C

## Overview
A lightweight, educational virtual machine implementation in C that supports basic arithmetic operations, memory management, control flow, and stack operations. This VM executes bytecode instructions and provides a foundation for understanding how processors work.

## Features

### Instruction Set
- **LOAD** - Load a value into a register
- **ADD** - Add two registers and store result
- **SUB** - Subtract two registers and store result
- **MUL** - Multiply two registers and store result
- **DIV** - Divide two registers and store result (with zero-check)
- **PRINT** - Print the value of a register
- **PUSH** - Push a register value onto the stack
- **POP** - Pop a value from the stack into a register
- **JMP** - Unconditional jump to an address
- **JZ** - Jump if zero (conditional jump)
- **HALT** - Stop execution

### Architecture
- **Memory**: 256 bytes of addressable memory
- **Registers**: 8 general-purpose registers (8-bit each)
- **Stack**: Grows downward from high memory addresses
- **Program Counter (PC)**: 16-bit address for larger programs
- **Stack Pointer (SP)**: Tracks stack position

## Compilation

### Using GCC
```bash
gcc -o Virtual_Machine.exe "Virtual Machine.c"
```

### Using Makefile
```bash
make        # Compile
make run    # Compile and run
make clean  # Remove build artifacts
```

## Running

### Directly
```bash
.\Virtual_Machine.exe
```

### With Output Redirection
```bash
.\Virtual_Machine.exe 2>&1
```

## Example Program

The included `main()` function demonstrates a simple program:
```
LOAD R0, 5      # Load 5 into register 0
LOAD R1, 3      # Load 3 into register 1
ADD R0, R1, R2  # Add them, store in R2
PRINT R2        # Print result (8)
HALT            # Stop
```

## Bytecode Format

Each instruction is encoded as bytes:
```
[OPCODE] [OPERAND1] [OPERAND2] [OPERAND3]
```

### Examples:
- `LOAD R0, 42` → `[OP_LOAD, 0, 42]`
- `ADD R0, R1, R2` → `[OP_ADD, 0, 1, 2]`
- `JMP 0x0A` → `[OP_JMP, 0x00, 0x0A]` (two-byte address)

## Safety Features
- Register bounds checking
- Stack overflow/underflow detection
- Address validation for jumps
- Division by zero protection
- Unknown opcode handling

## Author
Zane Francis

## Future Enhancements
- More complex data types
- Subroutines and call stack
- Memory protection
- Interrupt handling
- Debugger interface
