#include "zvm_io.h"

bool zfnio_keyboard(zvm_vm_t *vm,  uint8_t port, uint8_t operation,  uint8_t argc){
    if (operation == ZVM_IO_SERVICE_KEYBOARD_READ_CHARACTER) {
        int ch = getchar();
        if (ch == EOF) {
            ch = 0;
        }
        vm->io_devices[port]->O[0] = (uint8_t)ch;
    }
    return true;
}

bool zfnio_screen(zvm_vm_t *vm, uint8_t port, uint8_t operation,  uint8_t argc){
    uint8_t character = vm->io_devices[port]->I[0];
    printf("%c", character);
    return true;
}
