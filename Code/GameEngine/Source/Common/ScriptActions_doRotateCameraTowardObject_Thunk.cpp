// cl: /DNDEBUG /MD /EHsc
// readable body of ?doRotateCameraTowardObject@ScriptActions@@IAEXABVAsciiString@@MMMM@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class AsciiString;
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doRotateCameraTowardObject(const AsciiString &, float, float, float, float);
};

// ?doRotateCameraTowardObject@ScriptActions@@IAEXABVAsciiString@@MMMM@Z
__declspec(naked) void ScriptActions::doRotateCameraTowardObject(const AsciiString &, float, float, float, float)
{
	__asm {
        __emit 0x8b
        __emit 0x0d
        __emit 0x6c
        __emit 0x07
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x01
        __emit 0x56
        __emit 0x52
        __emit 0xff
        __emit 0x50
        __emit 0x68
        __emit 0x8b
        __emit 0xf0
        __emit 0x85
        __emit 0xf6
        __emit 0x74
        __emit 0x5b
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0xd8
        __emit 0x0d
        __emit 0x68
        __emit 0x5c
        __emit 0x07
        __emit 0x01
        __emit 0x53
        __emit 0x57
        __emit 0x8b
        __emit 0x3d
        __emit 0x00
        __emit 0x16
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x1f
        __emit 0x50
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x04
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x28
        __emit 0xd8
        __emit 0x0d
        __emit 0x68
        __emit 0x5c
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x1c
        __emit 0x24
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x24
        __emit 0xd8
        __emit 0x0d
        __emit 0x68
        __emit 0x5c
        __emit 0x07
        __emit 0x01
        __emit 0xe8
        __emit 0x85
        __emit 0x8d
        __emit 0x70
        __emit 0x00
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0xd8
        __emit 0x0d
        __emit 0x68
        __emit 0x5c
        __emit 0x07
        __emit 0x01
        __emit 0x50
        __emit 0xe8
        __emit 0x75
        __emit 0x8d
        __emit 0x70
        __emit 0x00
        __emit 0x8b
        __emit 0x4e
        __emit 0x74
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xff
        __emit 0x93
        __emit 0xcc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5b
        __emit 0x5e
        __emit 0xc2
        __emit 0x18
        __emit 0x00
	}
}
