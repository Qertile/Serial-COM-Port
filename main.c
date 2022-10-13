#include "serial.h"
#include "serial.c"

/* ================== Example commands ================== */

#define HEADER  "NCU+"
#define STATUS  "STATUS=?"
#define BEACON  0x9487
#define FOOTER  0x0D0A       // "CRLF" in ascii


/* ================== Example codes ================== */
int main (void){

    /* ------------------ Initialize Serial COM Port ------------------ */
    initComPort(5, 9600);    // (port number, baudrate)
    

    /* ------------------ Set Commands ------------------ */
    GC(init)();
    GC(ascii)(_command_, HEADER, 5);
    GC(ascii)(_command_, STATUS, 9);
    // GC(hex)(_command_, BEACON, 2);
    // GC(crc)(_command_);
    GC(hex)(_command_, FOOTER, 2);

    /* ------------------ Print Commands ------------------ */
    printCommand();
    
    /* ------------------ Transmit Commands ------------------ */
    transmit();
    
    /* ------------------ Receive Messages ------------------ */
    receive();

    /* ------------------ Free Memory Space ------------------ */
    GC(clear)(_command_);

    /* ------------------ Close COM Port ------------------ */
    closePort();

    return 0;
}