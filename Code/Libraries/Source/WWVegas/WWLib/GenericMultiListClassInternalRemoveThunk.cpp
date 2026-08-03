// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class MultiListObjectClass;

class GenericMultiListClass
{
protected:
    bool Internal_Remove(MultiListObjectClass *obj);
};

// ?Internal_Remove@GenericMultiListClass@@IAE_NPAVMultiListObjectClass@@@Z
__declspec(naked) bool GenericMultiListClass::Internal_Remove(MultiListObjectClass *obj)
{
    __asm {
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x46
        __emit 0x04
        __emit 0x33
        __emit 0xd2
        __emit 0x85
        __emit 0xc0
        __emit 0x57
        __emit 0x74
        __emit 0x0f
        __emit 0x90
        __emit 0x39
        __emit 0x48
        __emit 0x10
        __emit 0x74
        __emit 0x10
        __emit 0x8b
        __emit 0xd0
        __emit 0x8b
        __emit 0x40
        __emit 0x08
        __emit 0x85
        __emit 0xc0
        __emit 0x75
        __emit 0xf2
        __emit 0x5f
        __emit 0x32
        __emit 0xc0
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x85
        __emit 0xd2
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x78
        __emit 0x04
        __emit 0x89
        __emit 0x79
        __emit 0x04
        __emit 0x8b
        __emit 0x48
        __emit 0x04
        __emit 0x8b
        __emit 0x38
        __emit 0x89
        __emit 0x39
        __emit 0x74
        __emit 0x18
        __emit 0x8b
        __emit 0x48
        __emit 0x08
        __emit 0x89
        __emit 0x4a
        __emit 0x08
        __emit 0x50
        __emit 0xb9
        __emit 0xd4
        __emit 0xec
        __emit 0x34
        __emit 0x01
        __emit 0xe8
        __emit 0x67
        __emit 0xfd
        __emit 0xff
        __emit 0xff
        __emit 0x5f
        __emit 0xb0
        __emit 0x01
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x8b
        __emit 0x50
        __emit 0x08
        __emit 0x50
        __emit 0xb9
        __emit 0xd4
        __emit 0xec
        __emit 0x34
        __emit 0x01
        __emit 0x89
        __emit 0x56
        __emit 0x04
        __emit 0xe8
        __emit 0x4f
        __emit 0xfd
        __emit 0xff
        __emit 0xff
        __emit 0x5f
        __emit 0xb0
        __emit 0x01
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}
