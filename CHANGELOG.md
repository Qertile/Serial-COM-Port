# Serial

Using C language(WinAPI) to access serial port of PC

---------------------------------------------------------------
## Unreleased v1.1.2 (####.##.##)
### New
### Changed 
### Discarded
### Removed
### Fixed
### Known Issues
### Notes
### Reference

---------------------------------------------------------------
## Serial v1.2.0 (2023.01.11)
### Removed
- remove `_command_` argument in all GC()

---------------------------------------------------------------
## Serial v1.1.2 (2023.01.11)
### New
- selectable print receive format (hex/ascii)
- receive(1) = print ascii, else = print hex

---------------------------------------------------------------
## Serial v1.1.1 (2023.01.03)
### Changed 
- change print hex in `receive()`
### Removed
- remove `cpn_len`-1 in GC(ascii), now how many words is how many bytes input

---------------------------------------------------------------
## Serial v1.1 (2022.10.19)
### New
- update README.md
### Changed
- change `ReadIntervalTimeout` to 50 ms, and ReadTotalTimeoutConstant to 500 ms
### Discarded
- The 0x0D terminate in `ReadFile()`

---------------------------------------------------------------
## Serial v1.0 (2022.10.17)
### New
- add README.md
### Known Issues
- Need add more description in GC(ascii)
- Some device may have 0x0D in reply messages, can't use 0x0D as terminate condition while reading messages

---------------------------------------------------------------
## Serial v1.0 (2022.10.13)
### Notes
- v1.0 == v0.14

---------------------------------------------------------------
## Serial v0.14 (2022.10.13)
### New
- set rx timeout

---------------------------------------------------------------
## Serial v0.13 (2022.10.13)
### New
- add gen_command_crc() for CRC32
- add comment to all functions
### Changed 
- change gen_command_free() to gen_command_clear()
### Known Issues
- Some USB dongle may get error 0x57 at SetCommMask


---------------------------------------------------------------
## Serial v0.12 (2022.10.13)
### New
- can let user customize command
### Changed 
- merge gen_cmd.h into serial.h
- merge gen_cmd.c into serial.c

---------------------------------------------------------------
## Serial v0.11 (2022.10.12)
### New
- put number of port as param into initComPort() 
- add stderr fprintf to each return status
### Fixed
- Fixed all bugs in v0.10
### Notes
- DO NOT redefine a global variable in functions.
### Reference
- [SetCommState function (winbase.h)](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-setcommstate)
- [System Error Codes](https://learn.microsoft.com/zh-tw/windows/win32/debug/system-error-codes--0-499-)
- [CreateFileA function (fileapi.h)](https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea)

---------------------------------------------------------------
## Serial v0.10 (2022.10.09 - 2022.10.10)
### New
- modulize the serial_v0.9.c to serial.h and serial.c
### Changed 
- change command_body to body in command_t
- change command_len to length in command_t
### Note
- use extern to define global variable in .h file
- don't use send() as function name, there is another function called send() in "windows.h"

---------------------------------------------------------------
## Serial v0.9 (2022.10.09)
### Changed 
- move serial param and `rx_buffer_size` to #define
### Removed
- x.x.Txx is for TRX-U
- x.x.Axx is for APRS
- x.x.Xxx is for X-band
- before 0.7 is for X-band
- e.g.  
    - 0.8.X01 is version 01 for Xband using v 0.8 serial test
    - 0.8.T03 is version 03 for TRX-U using v 0.8 serial test

---------------------------------------------------------------
## Serial v0.8.T03 (2022.06.02)
### Known Issue
- ascii string will lead to error code in `gen_command`

---------------------------------------------------------------
## Serial v0.8.T02 (2022.06.02)
### Fixed
- Program will freeze when `rx_buffer` is larger then received
### Notes
X.X.2 is for TRX-U

---------------------------------------------------------------
## Serial v0.8.T01 (2022.06.01)
### New
- header and command
### Discarded
- TRX-U doesn't need CRC
### Known Issues
- Program will freeze when `rx_buffer` is larger then received number

---------------------------------------------------------------
## Serial v0.8 (2022.04.20)
### New
### Changed 
- count command_len in gen_command()
### Deprecated
### Removed
### Fixed
### Known Issues
### Notes
### Reference

---------------------------------------------------------------
## Serial v0.7.X02 (2022.04.20)
### Changed
- declare command as plain command
### Notes
- Also no reply from X-Band.

---------------------------------------------------------------
## Serial v0.7.X01 (2022.04.20)
### Changed
- change to MSB
### Notes
- Also no reply from X-Band.

---------------------------------------------------------------
## Serial v0.7.A01 (2022.03.24)
### New
### Changed
- Calculate CRC first then change to LSB
### Deprecated
### Removed
### Fixed
### Known Issues
### Notes
- Accroding to EnduroSat document(email) this is not correct way
### Reference

---------------------------------------------------------------

## Serial v0.7 (2022.03.23)
### New
- SetCommState()
- Some print for error handling (GetLastError())
### Changed
### Deprecated
### Removed
### Fixed
- Now can successfully open COM port
- Now can successfully set comm state
- Now can successfully change baudrate (verified by logic analyzer)
### Known Issues
### Notes
- Accroding to EnduroSat document, the command is correct
### Reference
[CreatFile() Error:5](https://blog.csdn.net/qq_37376568/article/details/96741297)

---------------------------------------------------------------
## Serial v0.6 (2022.03.14)
### New
- setting Rx and receiving data

### Changed
### Deprecated
### Removed
### Fixed
### Known Issues
- By logic analyzer, found cannot change baudrate
- Opening COM port failed (hComm failed)
- Doesn't have SetCommState()
- Set comm state failed
### Notes
- Test with Xband transmitter in this version
- Perform test on laptop in this version
- Successfully received data from transmitter (not correct data, but can receive)
- Command can not be received by Xband transmitter
<img src="./figures/螢幕擷取畫面 2022-03-14 183208.png"/>

### Reference
[Serial port programming using Win32 API (Windows)](https://aticleworld.com/serial-port-programming-using-win32-api/)

---------------------------------------------------------------
## Serial v0.5 (2022.03.01)
### New
- append 0 to multiplier of 16

### Changed
### Deprecated
### Removed
### Fixed
### Known Issues
### Notes
- Successfully transmit and received by logic analyzer
<img src="./figures/螢幕擷取畫面 2022-03-01 131907.png"/>

### Reference
---------------------------------------------------------------

## Serial v0.4 (2022.02.27)
### New
- struct command_t

### Changed
- getting_command() -> gen_command()
- gen_command() is using struct command_t now
- gen_command() is not only has fixed input(header,id ... etc.), now is modulelized
- Can put crc into gen_command()

### Deprecated
### Removed
### Fixed
### Known Issues
- The first byte of data seems not able to be received by logic 
### Notes
- If use #define the type will be int by default
- Successfully transmit and received by logic analyzer
<img src="./figures/螢幕擷取畫面 2022-02-28 002314.png"/>

### Reference
[鏈結串列](https://qertile.medium.com/%E9%8F%88%E7%B5%90%E4%B8%B2%E5%88%97-8b53bea07388)

[資料結構](https://qertile.medium.com/%E8%B3%87%E6%96%99%E7%B5%90%E6%A7%8B-4fd20b91ac91)


---------------------------------------------------------------
## Serial v0.3 (2022.02.27)
### New
- Can choose command generated as MSB or LSB
- Can generate crc32
- crc32.c and crc32()
- debug.c

### Changed
- getting_command() adding new parameter "lsb" to decide the command will be generated as MSB or LSB
### Deprecated
### Removed
### Fixed
### Known Issues
### Notes
    Not test on physical RS485 and logical analyzer in this version.
### Reference
[crc32.c](https://opensource.apple.com/source/xnu/xnu-1456.1.26/bsd/libkern/crc32.c.auto.html)


---------------------------------------------------------------
## Serial v0.2 (2022.02.26)
### New
- create command presets
- send commands to logic analyzer
- getting_command()

### Changed
### Deprecated
### Removed
### Fixed
### Known Issues
- The first byte of data seems not able to be received by logic analyzer
### Notes
- If array is pass in/out as parameter, it will be seen as a pointer.
- It will return size of pointer while using sizeof(), not size of array.
- So it will need another parameter to represent size of array.
- Commands in this version is for testing, not able to use.

<img src="./figures/螢幕擷取畫面 2022-02-26 223039.png"/>

### Reference
[如何在 C 語言中獲取陣列的大小](https://www.delftstack.com/zh-tw/howto/c/c-length-of-array/)

[Converting an int into a 4 byte char array (C)](https://stackoverflow.com/questions/3784263/converting-an-int-into-a-4-byte-char-array-c)


---------------------------------------------------------------
## Serial v0.1 (2022.02.26)
### New
- hComm
- SerialParams
- WriteFIle
### Changed
### Deprecated
### Removed
### Fixed
### Known Issues
- The first byte of data seems not able to be received by logic analyzer

### Notes    
- Can successfully use COM6 to send data

<img src="./figures/螢幕擷取畫面 2022-02-26 172611.png"/>

### Reference
 [Serial Port Programming using Win32 API](https://www.xanthium.in/Serial-Port-Programming-using-Win32-API)

 [Serial port programming using Win32 API (Windows)](https://aticleworld.com/serial-port-programming-using-win32-api/)

