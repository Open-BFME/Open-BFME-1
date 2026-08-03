// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class __declspec(novtable) ActiveCategoryStackClass
{
public:
    virtual ~ActiveCategoryStackClass();
};

// ??1ActiveCategoryStackClass@@UAE@XZ
__declspec(naked) ActiveCategoryStackClass::~ActiveCategoryStackClass()
{
    __asm {
        __emit 0x53
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x8b
        __emit 0x46
        __emit 0x04
        __emit 0x33
        __emit 0xdb
        __emit 0x3b
        __emit 0xc3
        __emit 0xc7
        __emit 0x06
        __emit 0x4c
        __emit 0xc4
        __emit 0x1b
        __emit 0x01
        __emit 0x74
        __emit 0x11
        __emit 0x38
        __emit 0x5e
        __emit 0x0d
        __emit 0x74
        __emit 0x0c
        __emit 0x50
        __emit 0xe8
        __emit 0x62
        __emit 0x2d
        __emit 0xd8
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x5e
        __emit 0x04
        __emit 0x88
        __emit 0x5e
        __emit 0x0d
        __emit 0x89
        __emit 0x5e
        __emit 0x08
        __emit 0x5e
        __emit 0x5b
        __emit 0xc3
    }
}
