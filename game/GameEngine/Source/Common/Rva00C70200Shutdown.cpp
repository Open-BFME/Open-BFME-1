// cl: /O2 /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
#include "unicode_string.h"
// Every entry is preceded by INT3 and ends in a tail JMP or RET then INT3.
// String destructor ILTs: D828 -> 5EE90; 3B304 -> 5EEA0.
extern AsciiString Rva00EF4B08Object; // retail VA 0x012F4B08
void Rva00C70200Shutdown() { Rva00EF4B08Object.~AsciiString(); }
extern AsciiString Rva00EF4B10Object; // retail VA 0x012F4B10
void Rva00C70210Shutdown() { Rva00EF4B10Object.~AsciiString(); }
extern AsciiString Rva00EF4B14Object; // retail VA 0x012F4B14
void Rva00C70220Shutdown() { Rva00EF4B14Object.~AsciiString(); }
extern AsciiString Rva00EF4B1CObject; // retail VA 0x012F4B1C
void Rva00C70230Shutdown() { Rva00EF4B1CObject.~AsciiString(); }
extern AsciiString Rva00EF4B24Object; // retail VA 0x012F4B24
void Rva00C70240Shutdown() { Rva00EF4B24Object.~AsciiString(); }
extern AsciiString Rva00EF4B2CObject; // retail VA 0x012F4B2C
void Rva00C70250Shutdown() { Rva00EF4B2CObject.~AsciiString(); }
extern AsciiString Rva00EF4B34Object; // retail VA 0x012F4B34
void Rva00C70260Shutdown() { Rva00EF4B34Object.~AsciiString(); }
extern AsciiString Rva00EF4B80Object; // retail VA 0x012F4B80
void Rva00C70270Shutdown() { Rva00EF4B80Object.~AsciiString(); }
extern AsciiString Rva00EF4B84Object; // retail VA 0x012F4B84
void Rva00C70280Shutdown() { Rva00EF4B84Object.~AsciiString(); }
extern AsciiString Rva00EF4B88Object; // retail VA 0x012F4B88
void Rva00C70290Shutdown() { Rva00EF4B88Object.~AsciiString(); }
extern UnicodeString Rva00EF4B90Object; // retail VA 0x012F4B90
void Rva00C702A0Shutdown() { Rva00EF4B90Object.~UnicodeString(); }
extern AsciiString Rva00EF4C00Object; // retail VA 0x012F4C00
void Rva00C702B0Shutdown() { Rva00EF4C00Object.~AsciiString(); }
extern AsciiString Rva00EF4C04Object; // retail VA 0x012F4C04
void Rva00C702C0Shutdown() { Rva00EF4C04Object.~AsciiString(); }
extern AsciiString Rva00EF4C0CObject; // retail VA 0x012F4C0C
void Rva00C702D0Shutdown() { Rva00EF4C0CObject.~AsciiString(); }
extern AsciiString Rva00EF4C28Object; // retail VA 0x012F4C28
void Rva00C702E0Shutdown() { Rva00EF4C28Object.~AsciiString(); }
extern AsciiString Rva00EF4BECObject; // retail VA 0x012F4BEC
void Rva00C702F0Shutdown() { Rva00EF4BECObject.~AsciiString(); }
extern AsciiString Rva00EF4BF0Object; // retail VA 0x012F4BF0
void Rva00C70300Shutdown() { Rva00EF4BF0Object.~AsciiString(); }
extern AsciiString Rva00EF4BF4Object; // retail VA 0x012F4BF4
void Rva00C70310Shutdown() { Rva00EF4BF4Object.~AsciiString(); }
extern AsciiString Rva00EF4BF8Object; // retail VA 0x012F4BF8
void Rva00C70320Shutdown() { Rva00EF4BF8Object.~AsciiString(); }
extern AsciiString Rva00EF4BACObject; // retail VA 0x012F4BAC
void Rva00C70330Shutdown() { Rva00EF4BACObject.~AsciiString(); }
extern AsciiString Rva00EF4BB4Object; // retail VA 0x012F4BB4
void Rva00C70340Shutdown() { Rva00EF4BB4Object.~AsciiString(); }
extern AsciiString Rva00EF4BBCObject; // retail VA 0x012F4BBC
void Rva00C70350Shutdown() { Rva00EF4BBCObject.~AsciiString(); }
extern AsciiString Rva00EF4BC0Object; // retail VA 0x012F4BC0
void Rva00C70360Shutdown() { Rva00EF4BC0Object.~AsciiString(); }
extern AsciiString Rva00EF4BC8Object; // retail VA 0x012F4BC8
void Rva00C70370Shutdown() { Rva00EF4BC8Object.~AsciiString(); }
extern AsciiString Rva00EF4BCCObject; // retail VA 0x012F4BCC
void Rva00C70380Shutdown() { Rva00EF4BCCObject.~AsciiString(); }
extern AsciiString Rva00EF4BD4Object; // retail VA 0x012F4BD4
void Rva00C70390Shutdown() { Rva00EF4BD4Object.~AsciiString(); }
extern AsciiString Rva00EF4BD8Object; // retail VA 0x012F4BD8
void Rva00C703A0Shutdown() { Rva00EF4BD8Object.~AsciiString(); }
extern AsciiString Rva00EF4C3CObject; // retail VA 0x012F4C3C
void Rva00C703C0Shutdown() { Rva00EF4C3CObject.~AsciiString(); }
extern AsciiString Rva00EF4C40Object; // retail VA 0x012F4C40
void Rva00C703D0Shutdown() { Rva00EF4C40Object.~AsciiString(); }
extern AsciiString Rva00EF4C44Object; // retail VA 0x012F4C44
void Rva00C703E0Shutdown() { Rva00EF4C44Object.~AsciiString(); }
extern AsciiString Rva00EF4C48Object; // retail VA 0x012F4C48
void Rva00C703F0Shutdown() { Rva00EF4C48Object.~AsciiString(); }
void Rva00C70400Shutdown() {  }
void Rva00C706F0Shutdown() {  }
void Rva00C70700Shutdown() {  }
void Rva00C70710Shutdown() {  }
void Rva00C70720Shutdown() {  }
void Rva00C70730Shutdown() {  }
void Rva00C70740Shutdown() {  }
void Rva00C70750Shutdown() {  }
void Rva00C70760Shutdown() {  }
void Rva00C70770Shutdown() {  }
void Rva00C70780Shutdown() {  }
void Rva00C70790Shutdown() {  }
void Rva00C707A0Shutdown() {  }
void Rva00C707B0Shutdown() {  }
void Rva00C707C0Shutdown() {  }
void Rva00C707D0Shutdown() {  }
void Rva00C707E0Shutdown() {  }
void Rva00C707F0Shutdown() {  }
void Rva00C70800Shutdown() {  }
void Rva00C70810Shutdown() {  }
