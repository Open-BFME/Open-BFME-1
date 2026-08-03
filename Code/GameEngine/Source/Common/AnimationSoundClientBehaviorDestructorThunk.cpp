// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class __declspec(novtable) AnimationSoundClientBehavior
{
public:
    virtual ~AnimationSoundClientBehavior();
};

// ??1AnimationSoundClientBehavior@@UAE@XZ
__declspec(naked) AnimationSoundClientBehavior::~AnimationSoundClientBehavior()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x68
        __emit 0xd5
        __emit 0x03
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
        __emit 0xc7
        __emit 0x06
        __emit 0xa0
        __emit 0x55
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x0c
        __emit 0x94
        __emit 0x55
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0xd0
        __emit 0x10
        __emit 0x2f
        __emit 0x01
        __emit 0x85
        __emit 0xc9
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x06
        __emit 0x56
        __emit 0xe8
        __emit 0xe3
        __emit 0x8b
        __emit 0xa0
        __emit 0xff
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
        __emit 0xc7
        __emit 0x06
        __emit 0xb8
        __emit 0xac
        __emit 0x08
        __emit 0x01
        __emit 0xe8
        __emit 0x31
        __emit 0x6d
        __emit 0xa2
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
