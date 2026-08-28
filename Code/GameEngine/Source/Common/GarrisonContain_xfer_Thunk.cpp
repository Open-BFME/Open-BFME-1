// cl: /DNDEBUG /MD /EHsc
// readable body of ?xfer@GarrisonContain@@MAEXPAVXfer@@@Z: Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class Xfer;
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GarrisonContain.h
class GarrisonContain
{
protected:
	virtual void xfer(Xfer *);
};

// ?xfer@GarrisonContain@@MAEXPAVXfer@@@Z
__declspec(naked) void GarrisonContain::xfer(Xfer *)
{
	__asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xfb
        __emit 0x65
        __emit 0x05
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
        __emit 0x33
        __emit 0xc0
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x89
        __emit 0x46
        __emit 0x04
        __emit 0x89
        __emit 0x46
        __emit 0x08
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x89
        __emit 0x46
        __emit 0x0c
        __emit 0x6a
        __emit 0x64
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x89
        __emit 0x46
        __emit 0x10
        __emit 0xe8
        __emit 0x1a
        __emit 0xf6
        __emit 0xff
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
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
