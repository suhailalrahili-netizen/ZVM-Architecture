#include <stdbool.h>
#include "zvm.h"
#include "zvm_exception.h"

bool zxpt_fetch(zvm_vm_t* vm, uint8_t code)   {return false;}
bool zxpt_decode(zvm_vm_t* vm, uint8_t code)  {return false;}
bool zxpt_execute(zvm_vm_t* vm, uint8_t code) {return false;}
bool zxpt_invalid_register(zvm_vm_t* vm, uint8_t code) {return false;}
bool zxpt_bad_instruction(zvm_vm_t* vm, uint8_t code) {return false;}
bool zxpt_bad_memory_address(zvm_vm_t* vm, uint8_t code) {return false;}
bool zxpt_stack_overflow(zvm_vm_t* vm, uint8_t code) {return false;}
bool zxpt_stack_underflow(zvm_vm_t* vm, uint8_t code) {return false;}
bool zxpt_io_device_not_found(zvm_vm_t* vm, uint8_t code) {return false;}

const zvm_exception_entry_t exception_handlers [] = {
    ZVM_EXCEPTION_HANDLER_ENTRY(FETCH,   FETCH,   fetch,   "fetch instruction error")
    ZVM_EXCEPTION_HANDLER_ENTRY(DECODE,  DECODE,  decode,  "decode instruction error")
    ZVM_EXCEPTION_HANDLER_ENTRY(EXECUTE, EXECUTE, execute, "execution: bad instruction error")
    ZVM_EXCEPTION_HANDLER_ENTRY(EXECUTE, INVALID_REGISTER, invalid_register, "invalid register")
    ZVM_EXCEPTION_HANDLER_ENTRY(DECODE,  BAD_INSTRUCTION,  bad_instruction,  "decoding: bad instruction error")
    ZVM_EXCEPTION_HANDLER_ENTRY(EXECUTE,  BAD_MEMORY_ADDRESS,  bad_memory_address,  "bad memory address error")
    ZVM_EXCEPTION_HANDLER_ENTRY(EXECUTE,  STACK_OVERFLOW,  stack_overflow,  "stack overflow error")
    ZVM_EXCEPTION_HANDLER_ENTRY(EXECUTE,  STACK_UNDERFLOW,  stack_underflow,  "stack underflow error")
    ZVM_EXCEPTION_HANDLER_ENTRY(EXECUTE,  IO_DEVICE_NOT_FOUND,  io_device_not_found,  "io device not found")
};