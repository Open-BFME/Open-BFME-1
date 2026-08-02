// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

enum NameKeyType
{
    NAMEKEY_DUMMY
};

class DataChunkOutput
{
public:
    void writeNameKey(NameKeyType key);
};

// ?writeNameKey@DataChunkOutput@@QAEXW4NameKeyType@@@Z
__declspec(naked) void DataChunkOutput::writeNameKey(NameKeyType key)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x78
        __emit 0xcb
        __emit 0xff
        __emit 0x00
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
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0x51
        __emit 0x8b
        __emit 0x0d
        __emit 0x00
        __emit 0xd6
        __emit 0x2e
        __emit 0x01
        __emit 0xe8
        __emit 0x4c
        __emit 0xa9
        __emit 0xf3
        __emit 0xff
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x18
        __emit 0x52
        __emit 0x8d
        __emit 0x4e
        __emit 0x08
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x61
        __emit 0xa7
        __emit 0xf3
        __emit 0xff
        __emit 0xc1
        __emit 0xe0
        __emit 0x08
        __emit 0x83
        __emit 0xc8
        __emit 0x03
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x46
        __emit 0x04
        __emit 0x50
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x6a
        __emit 0x04
        __emit 0x51
        __emit 0xff
        __emit 0x15
        __emit 0xf4
        __emit 0x93
        __emit 0x35
        __emit 0x01
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0xcc
        __emit 0x35
        __emit 0x78
        __emit 0x00
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
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}
