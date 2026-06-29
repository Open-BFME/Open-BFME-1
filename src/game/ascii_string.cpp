#include "ascii_string.h"

AsciiString::AsciiString()
{
    m_text = 0;
}

__declspec(naked) AsciiString::AsciiString(char c)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x56
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0xe8
        __emit 0x23
        __emit 0x07
        __emit 0x0a
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) AsciiString &AsciiString::operator=(const AsciiString &that)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x56
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0xe8
        __emit 0x83
        __emit 0xb7
        __emit 0x82
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}
