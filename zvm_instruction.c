#include <stdio.h>
#include "zvm_instruction.h"
#include "zvm.h"
#include <assert.h>

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(add)
    vm->cpu.R[output] = vm->cpu.R[left] + vm->cpu.R[right];
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(sub)
    vm->cpu.R[output] = vm->cpu.R[left] - vm->cpu.R[right];
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(ldi)
    vm->cpu.R[left] = right;
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(str)
    vm->program.data[right] = vm->cpu.R[left];
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(ldm)
    vm->cpu.R[left] = vm->program.data[right];
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(lda)
    uint8_t address = vm->cpu.R[left];
    if(!zvm_is_address(address)){
        zvm_raise(vm, EXECUTE, BAD_MEMORY_ADDRESS)
        return false;
    }
    vm->cpu.R[right] = vm->program.data[address];
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(sta)
    uint8_t address = vm->cpu.R[left];
    if(!zvm_is_address(address)){
        zvm_raise(vm, EXECUTE, BAD_MEMORY_ADDRESS)
        return false;
    }
    vm->program.data[address] = vm->cpu.R[right];
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(push)
    uint8_t value;
    if(vm->cpu.SP >= ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1){
        zvm_raise(vm, EXECUTE, STACK_OVERFLOW)
        return false;
    }
    vm->cpu.SP++;
    value = vm->cpu.R[left];
    vm->program.stack[(ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1) - vm->cpu.SP] = value;
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(pop)
    uint8_t value;
    if(vm->cpu.SP < 0){
        zvm_raise(vm, EXECUTE, STACK_UNDERFLOW)
        return false;
    }
    value = vm->program.stack[(ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1) - vm->cpu.SP];
    vm->cpu.SP--;
    vm->cpu.R[left] = value;
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(inc)
    vm->cpu.R[left]++;
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(dec)
    vm->cpu.R[left]--;
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(out)
    uint8_t port = vm->cpu.R[left];
    uint8_t function = vm->cpu.R[right];
    uint8_t argc = vm->cpu.R[output];

    if(port >= ZVM_IO_MAX_DEVICES){
        zvm_raise(vm, EXECUTE, BAD_INSTRUCTION);
        return false;
    }
    if(vm->io_devices[port] == NULL){
        zvm_raise(vm, EXECUTE, IO_DEVICE_NOT_FOUND);
        return false;
    }
    assert(vm->io_devices[port]->type == ZVM_IO_DEVICE_TYPE_OUT || vm->io_devices[port]->type == ZVM_IO_DEVICE_TYPE_INOUT);
    assert(argc <= 4);
    if(argc > 0){
        for(uint8_t i = 0; i < argc; i++){
            vm->io_devices[port]->I[i] = zvm_stack_pop(vm);
        }
    }
    return vm->io_devices[port]->processor(vm, port, function, argc);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(in)
    uint8_t port = vm->cpu.R[left];
    uint8_t function = vm->cpu.R[right];
    uint8_t argc = vm->cpu.R[output];

    if(port >= ZVM_IO_MAX_DEVICES){
        zvm_raise(vm, EXECUTE, BAD_INSTRUCTION);
        return false;
    }
    if(vm->io_devices[port] == NULL){
        zvm_raise(vm, EXECUTE, IO_DEVICE_NOT_FOUND);
        return false;
    }
    assert(vm->io_devices[port]->type == ZVM_IO_DEVICE_TYPE_IN || vm->io_devices[port]->type == ZVM_IO_DEVICE_TYPE_INOUT);
    assert(argc <= 4);
    if(argc > 0){
        for(uint8_t i = 0; i < argc; i++){
            vm->io_devices[port]->I[i] = zvm_stack_pop(vm);
        }
    }
    bool result = vm->io_devices[port]->processor(vm, port, function, argc);
    if (!result) return false;

    if(vm->cpu.SP >= ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1){
        zvm_raise(vm, EXECUTE, STACK_OVERFLOW)
        return false;
    }
    vm->cpu.SP++;
    uint8_t read_value = vm->io_devices[port]->O[0];
    vm->program.stack[(ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1) - vm->cpu.SP] = read_value;
ZVM_INSTRUCTION_HANDLER_FUNCTION_END
