// cl: /DNDEBUG /MD /EHsc

class __declspec(novtable) ScriptGroup
{
protected:
    virtual ~ScriptGroup();
};

// ??1ScriptGroup@@MAE@XZ
__declspec(naked) ScriptGroup::~ScriptGroup()
{
    __asm {
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0xc7
        __emit 0x06
        __emit 0x44
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x8b
        __emit 0x7e
        __emit 0x08
        __emit 0x85
        __emit 0xff
        __emit 0x74
        __emit 0x16
        __emit 0x8b
        __emit 0x0f
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x07
        __emit 0x6a
        __emit 0x01
        __emit 0xe8
        __emit 0xca
        __emit 0xf9
        __emit 0xca
        __emit 0xff
        __emit 0x57
        __emit 0xe8
        __emit 0x3c
        __emit 0xf5
        __emit 0x52
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x8b
        __emit 0x76
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0x74
        __emit 0x16
        __emit 0x8b
        __emit 0x0e
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x07
        __emit 0x6a
        __emit 0x01
        __emit 0xe8
        __emit 0xae
        __emit 0xf6
        __emit 0xcc
        __emit 0xff
        __emit 0x56
        __emit 0xe8
        __emit 0x1f
        __emit 0xf5
        __emit 0x52
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x5f
        __emit 0x5e
        __emit 0xc3
    }
}
