#include "serial.h"
#include "crc32.c"

command_t *_command_;
uint8_t status_;
HANDLE hComm_;


/* ================== Serial functions ================== */

void initComPort(uint8_t portNo, uint32_t baudrate){
/*
    @Discreption
        This function will open the serial COM port, and initialize the COM port. The bytesize, stopbit ,and parity bit is defined in serial.h. If there is error occured when calling this function, this program will be terminated.
    
    @Input
        portNo: number of COM port
        baudrate: baudrate of remote device
    
    @Ouput
        none
*/
    
/* ------------------ Initialize COM port ------------------ */
    uint8_t port[10];
    uint8_t tmp[2];

    itoa(portNo, tmp, 10);
    strcat(port, "\\\\.\\COM");
    strcat(port, tmp);

    //Open the serial com port
    hComm_ = CreateFile(port,                          //friendly name
                       GENERIC_READ | GENERIC_WRITE,   // Read/Write Access
                       0,              // No Sharing, ports cant be shared
                       NULL,           // No Security
                       OPEN_EXISTING,  // Open existing port only
                       0 ,             // Non Overlapped I/O
                       NULL);          // Null for Comm Devices

    if (hComm_ == INVALID_HANDLE_VALUE){
        fprintf(stderr,"opening serial port failed 0x%X\n",GetLastError());
        exit(0);
    }
    else printf("Serial port opened, ");


    /* --------------- Set Device Control Block structure --------------- */
    DCB SerialParams = { 0 };  // Initializing DCB structure
    SerialParams.fRtsControl = 0x00;
    SerialParams.DCBlength = sizeof(SerialParams);
    SerialParams.BaudRate = baudrate;
    SerialParams.ByteSize = SERIAL_BYTESIZE;
    SerialParams.StopBits = SERIAL_STOPBITS;
    SerialParams.Parity = SERIAL_PARITY;
    printf("baudrate = %d\n", SerialParams.BaudRate);
   

    /* --------------- Set receive mask --------------- */
    status_ = SetCommMask(hComm_, EV_RXCHAR);
    if (!status_) {
        fprintf(stderr,"SetCommMask failed 0x%X\n",GetLastError());
        exit(0);
    }
    else printf("SetCommMask success\n");

    /* --------------- Set comm status --------------- */
    status_ = SetCommState(hComm_, &SerialParams);
    if (!status_) {
        fprintf(stderr,"SetCommState failed 0x%X\n",GetLastError());
        exit(0);
    }
    else printf("SetCommState success\n");

    /* --------------- Get the current settings --------------- */        
    status_ = GetCommState(hComm_, &SerialParams);
    if (!status_) {
        fprintf(stderr,"GetCommState failed 0x%X\n",GetLastError());
        exit(0);
    }
    else printf("GetCommState success\n");

    
    /* --------------- Set timeout structure --------------- */
    COMMTIMEOUTS timeouts = { 0 };        // Initializing COMMTIMEOUTS structure
    timeouts.ReadIntervalTimeout = 10;       // timeout between bytes
    timeouts.ReadTotalTimeoutConstant = 50;  // total timeout in one transaction
    
    status_ = SetCommTimeouts(hComm_, &timeouts);
    if (!status_) {
        fprintf(stderr,"SetCommTimeouts failed 0x%X\n",GetLastError());
        exit(0);
    }
    else printf("SetCommTimeouts success\n");

}

void printCommand(void){
/*
    @Discreption
        This function will print the command to terminal.
    
    @Input
        none
    
    @Ouput
        none
*/

/* ------------------ Print for debug ------------------ */
    printf("\ncommand length = %d\n", _command_->length);
    printf("command = \n");

    for(int i = 0; i<_command_->length; i++){
        printf("%X ", *(_command_->body + i));
    }
    printf("\n");

    return;
}

void transmit(void){
/*
    @Discreption
        This function will transmit the command in `_command_->body`. If there is an error occured while transmittion, this program will be terminate to protect the remote device.
    
    @Input
        none
    
    @Ouput
        none
*/

/* ------------------ Send Command ------------------ */
    uint8_t BytesWritten = 0;
        
    status_ = WriteFile(hComm_,         // Handle to the Serial port
                    _command_->body,    // Data to be written to the port
                    _command_->length,  // No of bytes to write
                    &BytesWritten,      // Bytes written
                    NULL);
    
    /* --------------- Check transmit status --------------- */
    if (!status_) {
        fprintf(stderr,"\nWriteFile failed 0x%X\n",GetLastError());
        printf("Number of bytes written to the serial port = %d\n", BytesWritten);
        exit(0);
    }
    else printf("\nNumber of bytes written to the serial port = %d\n", BytesWritten);
    
    return;
}

void receive(void){
/*
    @Discreption
        This function will receive the messages form the device, and move byte by byte to `rx_buffer` and the default buffer size depends on `RX_BUFFER_SIZE` defined in serial.h

        The terminate condition is receiving 0x0D (<CR> in ascii), or the `rx_buffer` is full.
    
    @Input
        none
    
    @Ouput
        none
*/

    /* --------------- Set rx buffer --------------- */
    uint8_t *rx_buffer = calloc(RX_BUFFER_SIZE, sizeof(uint8_t));
    
    /* ------------------ Receive Data ------------------ */
    uint32_t event_mask;    // Event mask to trigger
    // Setting WaitComm() Event
    status_ = WaitCommEvent(hComm_, &event_mask, NULL); //Wait for the character to be received

    /* --------------- Check receive status --------------- */
    if (!status_) {
        fprintf(stderr,"\nWaitCommEvent failed 0x%X\n",GetLastError());
        exit(0);
    }


    uint8_t rx_tmp;         // temperory Character
    uint16_t rx_ctr = 0;     // rx counter
    uint32_t BytesRead;     // Bytes read by ReadFile()

    /* --------------- Read data and store in a buffer --------------- */
    do{
        status_ = ReadFile(hComm_,          // Handle to the Serial port
                        &rx_tmp,            // read buffer 
                        sizeof(rx_tmp),     // Number of bytes to read
                        &BytesRead,         // Number of bytes read 
                        NULL);
        if (!status_) {
            fprintf(stderr,"\nReadFile failed 0x%X\n",GetLastError());
            exit(0);
        }
        else{
            rx_buffer[rx_ctr] = rx_tmp;
            rx_ctr++;
            // if ( rx_buffer[rx_ctr-1] == 0x0D ) break;
        }
    }
    while (BytesRead > 0 || rx_ctr >= RX_BUFFER_SIZE );
    // rx_ctr--; // Get Actual length of received data
    printf("\nNumber of bytes received = %d\n\n", rx_ctr);
    printf("Received messages = \n");
    
    /* ------------------ Print received data ------------------ */

    for (int i = 0; i < rx_ctr; i++){
        printf("%c", rx_buffer[i]);
    }
    
    return;
}

void closePort(void){
/*
    @Discreption
        This function will close the COM port which just opened by calling iniComPort().
    
    @Input
        none
    
    @Ouput
        none
*/
    
/* ------------------ Close COM port ------------------ */
    status_ = CloseHandle(hComm_);     //Closing the Serial Port
    if (!status_) fprintf(stderr,"\nClosing Serial port failed 0x%X\n",GetLastError());
    else  printf("\nSerial port closed\n");
    return ;
}


/* ================== Command generation functions ================== */

command_t* gen_command_hex(command_t* cmd, uint32_t cpn, size_t cpn_len){
/*
    @Discreption
        This function will split component into unit of bytes, and append it to command_body in command structure. And it will append component in MSB or LSB by "lsb" in command structure. If ctr_rst == 1, this function will set counter to 0
    
    @Input
        cmd: structure of command
        cpn: component which need to be appended to command, must less than 4 bytes
        cpn_len: length of component
    
    @Ouput
        cmd: structure of command
*/
    
    if (cmd->ctr_rst) cmd->ctr =0;
    if (cmd->lsb){
        for(int i=0; i<cpn_len; i++){
            *(cmd->body + cmd->ctr) = cpn >> 8*i;
            cmd->ctr++;
        }
    }
    else{        
        for(int i=cpn_len; i>0; i--){
            *(cmd->body + cmd->ctr) = cpn >> 8*(i-1);
            cmd->ctr++;
        }
    }    

    cmd->length += cpn_len;
    
    /* ----- for debug command use -----*/
    // for(int i = 0; i<cmd->length; i++){
    //     printf("%d = %X\n",i, *(cmd->body + i));
    // }

    return cmd;
}

command_t* gen_command_ascii(command_t* cmd, uint8_t* cpn, size_t cpn_len){
/*
    @Discreption
        This function will split component into unit of bytes, and append it to command_body in command structure. There is no MSB or LSB for ascii command. If ctr_rst == 1, this function will set counter to 0
    
    @Input
        cmd: structure of command
        cpn: component which need to be appended to command
        cpn_len: length of component
    
    @Ouput
        cmd: structure of command
*/
    
    if (cmd->ctr_rst) cmd->ctr =0;

    /* to eliminate "\0" in string */
    cpn_len -= 1;       

    for(int i=0; i<cpn_len; i++){
            *(cmd->body + cmd->ctr) = *(cpn+i);
            cmd->ctr++;
    }

    cmd->length += cpn_len;
    
    /* ----- for debug command use -----*/
    // for(int i = 0; i<cmd->length; i++){
    //     printf("%d = %X\n",i, *(cmd->body + i));
    // }

    return cmd;
}

command_t* gen_command_crc(command_t *_cmd){
/*
    @Discreption
        This function will calculate the crc32 for the command, and use gen_command_hex to append the crc code to the command
    
    @Input
        cmd: structure of command
    
    @Ouput
        cmd: structure of command
*/

    uint32_t crc = 0x00000000; 
    crc = crc32(crc, _cmd->body, _cmd->length);     // get CRC32 from command
    gen_command_hex(_cmd, crc, 4);
    return _cmd;
}

void gen_command_init(void){
/*
    @Discreption
        This function will create a memory space for command, and initialize the structure of command to zero
    
    @Input
        none
    
    @Ouput
        none
*/

    _command_ = (command_t*)malloc(sizeof(command_t));

    _command_->body = (uint8_t*)calloc(128, sizeof(uint8_t));
    _command_->length = 0;       // initial command length in byte
    _command_->lsb = 0;               // 0 = LSB, 1 = MSB
    _command_->ctr = 0;               // initial counter of command_body
    _command_->ctr_rst = 0;
    return;
}

void gen_command_clear(command_t* cmd){
/*
    @Discreption
        This function will free the memory space of command
    
    @Input
        none
    
    @Ouput
        none
*/

    free(cmd);
}
