# Serial

Using C language(WinAPI) to access serial port of PC

---------------------------------------------------------------
## Unreleased v1.XX (2022.XX.XX)
### New
### Changed 
### Discarded
### Removed
### Fixed
### Known Issues
### Notes
### Reference

---------------------------------------------------------------
## Unreleased v1.1 (2022.10.19)
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
