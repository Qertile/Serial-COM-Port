#ifndef _SERIAL_H
#define _SERIAL_H

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#define GC(type) gen_command_##type

/* ------------------ Serial environment parameter ------------------ */

#define RX_BUFFER_SIZE  256
// #define COM_PORT "\\\\.\\COM6"
// #define SERIAL_BAUDRATE 9600
#define SERIAL_BYTESIZE 8
#define SERIAL_STOPBITS 1
#define SERIAL_PARITY   0


/* ------------------ Structure of Command ------------------ */
struct command{
    uint8_t *body;    // main command
    size_t  length;   // length of command
    uint8_t lsb;      // 1 = LSB, 0 = MSB
    uint8_t ctr;      // counter of command_body, n_th byte of command
    uint8_t ctr_rst;  // if 1 will reset the counter
};
typedef struct command command_t;


/* ------------------ Global variables ------------------ */
extern command_t *_command_;
extern uint8_t status_;
extern HANDLE hComm_;


/* ------------------ Serial functions ------------------ */
void initComPort(uint8_t portNo, uint32_t baudrate);
void printCommand(void);
void transmit(void);
void receive(uint8_t print_format);
void closePort(void);

/* ------------------ Command generation functions ------------------ */
void gen_command_clear(void);
void gen_command_init(void);
void gen_command_hex(uint32_t cpn, size_t cpn_len);
void gen_command_ascii(uint8_t* cpn, size_t cpn_len);
void gen_command_crc(void);

#endif
