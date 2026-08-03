// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class __declspec(novtable) DebugIONet
{
public:
    virtual ~DebugIONet();
};

// ??1DebugIONet@@UAE@XZ
__declspec(naked) DebugIONet::~DebugIONet()
{
    __asm {
        __emit 0x55
        __emit 0x8b
        __emit 0xec
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x98
        __emit 0x6b
        __emit 0x05
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x89
        __emit 0x75
        __emit 0xf0
        __emit 0xc7
        __emit 0x06
        __emit 0x9c
        __emit 0x5c
        __emit 0x13
        __emit 0x01
        __emit 0xc7
        __emit 0x45
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8a
        __emit 0x46
        __emit 0x04
        __emit 0x84
        __emit 0xc0
        __emit 0x74
        __emit 0x06
        __emit 0xff
        __emit 0x15
        __emit 0x44
        __emit 0x8d
        __emit 0x35
        __emit 0x01
        __emit 0xc7
        __emit 0x45
        __emit 0xfc
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0x8b
        __emit 0x4d
        __emit 0xf4
        __emit 0xc7
        __emit 0x06
        __emit 0x44
        __emit 0x50
        __emit 0x13
        __emit 0x01
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xe5
        __emit 0x5d
        __emit 0xc3
    }
}
