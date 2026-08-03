// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the exact retail destructor into a C++ thunk.

class __declspec(novtable) W3DQuadrupedDrawModuleData
{
public:
    virtual ~W3DQuadrupedDrawModuleData();
};

// ??1W3DQuadrupedDrawModuleData@@UAE@XZ
__declspec(naked) W3DQuadrupedDrawModuleData::~W3DQuadrupedDrawModuleData()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x78
        __emit 0x9b
        __emit 0x04
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
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x68
        __emit 0x28
        __emit 0xd8
        __emit 0x40
        __emit 0x00
        __emit 0x6a
        __emit 0x04
        __emit 0x6a
        __emit 0x04
        __emit 0x8d
        __emit 0x86
        __emit 0x5c
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xcc
        __emit 0x6d
        __emit 0x33
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x65
        __emit 0xc7
        __emit 0x96
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}
