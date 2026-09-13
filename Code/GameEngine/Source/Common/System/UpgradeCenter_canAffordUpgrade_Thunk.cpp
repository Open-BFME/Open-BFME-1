// cl: /DNDEBUG /MD /EHsc
// readable body of ?canAffordUpgrade@UpgradeCenter@@QBE_NPAVPlayer@@PBVUpgradeTemplate@@_N@Z: Code/GameEngine/Source/Common/System/Upgrade.cpp
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class Player;
class UpgradeTemplate;
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeCenter
{
public:
	bool canAffordUpgrade(Player *, const UpgradeTemplate *, bool) const;
};

// ?canAffordUpgrade@UpgradeCenter@@QBE_NPAVPlayer@@PBVUpgradeTemplate@@_N@Z
__declspec(naked) bool UpgradeCenter::canAffordUpgrade(Player *, const UpgradeTemplate *, bool) const
{
	__asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xc0
        __emit 0x56
        __emit 0x74
        __emit 0x41
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x39
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0x70
        __emit 0x4c
        __emit 0x52
        __emit 0x50
        __emit 0xe8
        __emit 0x48
        __emit 0x49
        __emit 0xf3
        __emit 0xff
        __emit 0x3b
        __emit 0xf0
        __emit 0x73
        __emit 0x2d
        __emit 0x8a
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x84
        __emit 0xc0
        __emit 0x74
        __emit 0x1f
        __emit 0x51
        __emit 0x89
        __emit 0x64
        __emit 0x24
        __emit 0x18
        __emit 0x8b
        __emit 0xcc
        __emit 0x68
        __emit 0x80
        __emit 0x8d
        __emit 0x08
        __emit 0x01
        __emit 0xe8
        __emit 0x14
        __emit 0xdc
        __emit 0x77
        __emit 0x00
        __emit 0xa1
        __emit 0x8c
        __emit 0x14
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x08
        __emit 0x50
        __emit 0xff
        __emit 0x51
        __emit 0x30
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x32
        __emit 0xc0
        __emit 0x5e
        __emit 0xc2
        __emit 0x10
        __emit 0x00
        __emit 0xb0
        __emit 0x01
        __emit 0x5e
        __emit 0xc2
        __emit 0x10
        __emit 0x00
	}
}
