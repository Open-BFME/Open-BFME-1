// cl: /DNDEBUG /MD /EHsc
// readable body of ?attemptDamage@Object@@QAEXPAVDamageInfo@@@Z: Code/GameEngine/Source/GameLogic/Object/Object.cpp
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class DamageInfo;
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void attemptDamage(DamageInfo *);
};

// ?attemptDamage@Object@@QAEXPAVDamageInfo@@@Z
__declspec(naked) void Object::attemptDamage(DamageInfo *)
{
	__asm {
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0xf6
        __emit 0x86
        __emit 0x44
        __emit 0x03
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0x57
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x0c
        __emit 0x75
        __emit 0x18
        __emit 0x8b
        __emit 0x8e
        __emit 0x00
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x05
        __emit 0x8b
        __emit 0x01
        __emit 0x57
        __emit 0xff
        __emit 0x10
        __emit 0xf6
        __emit 0x86
        __emit 0x44
        __emit 0x03
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0x74
        __emit 0x10
        __emit 0xd9
        __emit 0x47
        __emit 0x3c
        __emit 0xd8
        __emit 0x1d
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x41
        __emit 0x75
        __emit 0x08
        __emit 0x57
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x4a
        __emit 0x44
        __emit 0xe4
        __emit 0xff
        __emit 0x8b
        __emit 0x16
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x52
        __emit 0x28
        __emit 0x8b
        __emit 0xf8
        __emit 0x85
        __emit 0xff
        __emit 0x74
        __emit 0x19
        __emit 0x8a
        __emit 0x87
        __emit 0xac
        __emit 0x03
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc0
        __emit 0x74
        __emit 0x0f
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x72
        __emit 0xc5
        __emit 0xe5
        __emit 0xff
        __emit 0x50
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0xaf
        __emit 0x7a
        __emit 0xe6
        __emit 0xff
        __emit 0x5f
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
	}
}
