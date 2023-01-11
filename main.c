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
    initComPort(3, 9600);    // (port number, baudrate)
    

    /* ------------------ Set Commands ------------------ */
    GC(init)();
    GC(ascii)(HEADER, 4);
    GC(ascii)(STATUS, 8);
    // GC(hex)(BEACON, 2);
    // GC(crc)();
    GC(hex)(FOOTER, 2);

    /* ------------------ Print Commands ------------------ */
    printCommand();
    
    /* ------------------ Transmit Commands ------------------ */
    transmit();
    
    /* ------------------ Receive Messages ------------------ */
    receive(1);

    /* ------------------ Free Memory Space ------------------ */
    GC(clear)();

    /* ------------------ Close COM Port ------------------ */
    closePort();

    return 0;
}