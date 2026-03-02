/*
This is the header file for a simple implementation of a virtual machine in C. 
It defines the structure of the virtual machine, including its memory, registers, and instruction set. 
The virtual machine supports basic arithmetic operations, memory management, and control flow.

Author: Zane Francis
*/
#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MEMORY_SIZE 256
#define NUM_REGISTERS 8

// Define the instruction set
typedef enum{
    OP_HALT = 0,
    OP_LOAD,
    OP_PRINT,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_JMP,
    OP_JZ,
    OP_PUSH,
    OP_POP,
}Opcode;

// Define the structure of the virtual machine
typedef struct {
    uint8_t memory[MEMORY_SIZE];
    uint8_t registers[NUM_REGISTERS];
    uint16_t pc;
    uint8_t stack[MEMORY_SIZE];
    uint16_t sp;
    uint8_t running;
}VirtualMachine;

// Function properties
void vm_init(VirtualMachine *vm);
void vm_load_program(VirtualMachine *vm, uint8_t *program, size_t size);
void vm_execute(VirtualMachine *vm);
void vm_reset(VirtualMachine *vm);

#endif