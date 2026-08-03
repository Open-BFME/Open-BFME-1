// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class __declspec(novtable) TransportContainModuleData
{
public:
    virtual ~TransportContainModuleData();
};

// ??1TransportContainModuleData@@UAE@XZ
__declspec(naked) TransportContainModuleData::~TransportContainModuleData()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x98
        __emit 0xce
        __emit 0x00
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
        __emit 0x8d
        __emit 0x8e
        __emit 0x74
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xb0
        __emit 0xa3
        __emit 0x66
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
        __emit 0x42
        __emit 0xa1
        __emit 0xe1
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
