# Slot accessor at RVA 0x0048DE20 (92 bytes): AsciiString element type
Old: `?bfmeAtYJ@Gen_0048DE20@@QAEPAVAsciiStringYJ@@H@Z`
New: `?bfmeAtYJ@Gen_0048DE20@@QAEPAVAsciiString@@H@Z`

Only the element type changes; the address-derived owner and method names stay.
The element is a 4-byte object whose inline default constructor zeroes its one
pointer and whose destructor, registered by the local static's atexit helper,
is 0x00887940: retail's exported `?releaseBuffer@?$StringBase@D@@AAEXXZ`
(exports.csv), the body AsciiString's inline destructor calls (ascii_string.h).
The invented `AsciiStringYJ` destructor pin at 0x00887940 named nothing that
defines it, so the file could not link. The body still byte-matches.
