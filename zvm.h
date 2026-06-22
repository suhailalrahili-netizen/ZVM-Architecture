#ifndef __ZVM_H__
#define __ZVM_H__

#include <stdint.h>
#include "zvm_exception.h"
#include "zvm_instruction.h"
#include "zvm_program.h"
#include "zvm_io.h"

#define ZVM_RX_REGISTERS_COUNT 4


typedef struct zvm_vm_t zvm_vm_t;
typedef struct zvm_cpu_t zvm_cpu_t;
typedef struct zvm_io_device_t zvm_io_device_t;

struct zvm_cpu_t{
    uint8_t IP;
    zvm_instruction_t* IR;
    uint8_t R[ZVM_RX_REGISTERS_COUNT];
    uint32_t OUTPUT;
    uint8_t FLAGS;

    uint8_t *DR;
    zvm_instruction_t *CR;
    uint8_t *SR;

    int8_t SP;
};

#define ZVM_IO_MAX_DEVICES 4

struct zvm_vm_t{
    bool has_exception;
    int8_t exception_type;
    int8_t exception_code;

    zvm_cpu_t cpu;
    zvm_program_t program;
    zvm_io_device_t* io_devices[ZVM_IO_MAX_DEVICES];
};

uint8_t zvm_stack_pop(zvm_vm_t *vm);

#endif
