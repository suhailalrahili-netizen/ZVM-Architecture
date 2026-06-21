#ifndef __ZVM_PROGRAM_H__
#define __ZVM_PROGRAM_H__

#define ZVM_PROGRAM_DEFAULT_DATA_SEGMENT_SIZE   64
#define ZVM_PROGRAM_DEFAULT_CODE_SEGMENT_SIZE   128
#define ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE  64

#define zvm_is_address(v)  ((v) < ZVM_PROGRAM_DEFAULT_DATA_SEGMENT_SIZE)
#define zvm_is_stack_address zvm_is_address

typedef struct zvm_program_t zvm_program_t;
typedef struct zvm_instruction_t zvm_instruction_t;

struct zvm_program_t{
    uint8_t data[ZVM_PROGRAM_DEFAULT_DATA_SEGMENT_SIZE];
    uint8_t stack[ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE];
    zvm_instruction_t instructions[ZVM_PROGRAM_DEFAULT_CODE_SEGMENT_SIZE];

    int8_t data_count;
    int8_t instructions_count;
    int8_t stack_counts;
};

#endif