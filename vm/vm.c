#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "loader/project.h"
#include "interpreter/interpreter.h"
#include "interpreter/frame.h"

int vm(int argc, char **argv)
{
#if GENERATE
    uint8_t test_set[] = {
        // Magic
        0xCA, 0xFE, 0xBA, 0xBE,
        // Version
        0x00, 0x00, 0x00, 0x01,
        // constpool Len
        0x00, 0x01,
        // constpool Projectname: "Base" Tag + Len + Val
        0x01, 0x00, 0x04, 0x42, 0x61, 0x73, 0x65,
        // Projectname index
        0x00, 0x00,
        // AVM Classes Len
        0x01,
        // constpool Len
        0x00, 0x0B,
        // constpool Classname: "Base" Tag + Len + Val
        0x01, 0x00, 0x04, 0x42, 0x61, 0x73, 0x65,
        // constpool Superclass: "Super" Tag + Len + Val
        0x01, 0x00, 0x05, 0x53, 0x75, 0x70, 0x65, 0x72,
        // constpool String: "Hello, world!" Tag + Len + Val
        0x01, 0x00, 0x0C, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64,
        // constpool String: Pointing to entry index 2
        0x02, 0x00, 0x02,
        // constpool String: "main"
        0x01, 0x00, 0x04, 0x6d, 0x61, 0x69, 0x6e,
        // constpool String: "IS-I"
        0x01, 0x00, 0x04, 0x49, 0x53, 0x2d, 0x49,
        // constpool Method
        0x03, 0x00, 0x00, 0x00, 0x07,
        // constpool nametype
        0x04, 0x00, 0x04, 0x00, 0x05,
        // constpool String: "code" Tag + Len + Val
        0x01, 0x00, 0x04, 0x63, 0x6f, 0x64, 0x65,
        // constpool String: "x" Tag + Len + Val
        0x01, 0x00, 0x01, 0x78,
        // constpool String: "y" Tag + Len + Val
        0x01, 0x00, 0x01, 0x79,
        // Flags
        0x00, 0x01,
        // Classname index
        0x00, 0x00,
        // Superclass index
        0x00, 0x01,
        // methods len
        0x00, 0x01,
        // methods Method Class + NaT + Attr Len + Attr Name
        0x00, 0x00, 0x00, 0x06, 0x00, 0x01, 0x00, 0x08,
        // Attr Data Len + Attr Data (Code)
        0x00, 0x00, 0x00, 0x08,
        AOP_NOP, AOP_ILOAD, 0x00, 0x09, AOP_ILOAD, 0x00, 0x0A, AOP_RETURN, //0x01, 0x03, 0x01, 0x05, 0x02
    };
    FILE *f;
    f = fopen("test.avm", "wb");
    uint32_t i;
    for (i=0;i<sizeof(test_set);i++) {
        putc(test_set[i], f);
#if DEBUG
       printf("0x%02x ", test_set[i]);
#endif
    }
    fclose(f);
#if DEBUG
    printf("\n\n");
#endif
#endif
    avm_interpreter *ai = avm_interpreter_make("test.avm");
    avm_interpreter_run(ai);
    avm_interpreter_free(ai);
    return 0;
}
