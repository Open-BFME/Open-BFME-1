// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/part_buf.h
class ParticleBufferClass {
public:
    class TextureHandleClass {};
    TextureHandleClass Get_Texture() const;
};

// ?Get_Texture@ParticleBufferClass@@QBE?AVTextureHandleClass@1@XZ
__declspec(naked) ParticleBufferClass::TextureHandleClass ParticleBufferClass::Get_Texture() const
{
    __asm {
        __emit 0x51
        __emit 0x8b
        __emit 0xc1
        __emit 0x8b
        __emit 0x88
        __emit 0x08
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xc9
        __emit 0x56
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x11
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x0c
        __emit 0x56
        __emit 0xe8
        __emit 0xb0
        __emit 0x98
        __emit 0xf8
        __emit 0xff
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x59
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x8b
        __emit 0x88
        __emit 0x10
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x11
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x0c
        __emit 0x56
        __emit 0xe8
        __emit 0x25
        __emit 0x5d
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x59
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x8b
        __emit 0x80
        __emit 0x0c
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x13
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x0c
        __emit 0x56
        __emit 0x8b
        __emit 0xc8
        __emit 0xe8
        __emit 0xc8
        __emit 0x70
        __emit 0xfd
        __emit 0xff
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x59
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xc7
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5e
        __emit 0x59
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}
