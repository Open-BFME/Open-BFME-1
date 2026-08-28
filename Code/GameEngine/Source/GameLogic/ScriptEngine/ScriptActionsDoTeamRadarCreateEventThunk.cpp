// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class AsciiString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
    void doTeamRadarCreateEvent(const AsciiString &teamName, int eventType);
};

// ?doTeamRadarCreateEvent@ScriptActions@@IAEXABVAsciiString@@H@Z
__declspec(naked) void ScriptActions::doTeamRadarCreateEvent(const AsciiString &teamName, int eventType)
{
    __asm {
        __emit 0x83
        __emit 0xec
        __emit 0x10
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x56
        __emit 0x6a
        __emit 0x00
        __emit 0x51
        __emit 0x89
        __emit 0x64
        __emit 0x24
        __emit 0x0c
        __emit 0x8b
        __emit 0xcc
        __emit 0x50
        __emit 0xe8
        __emit 0x09
        __emit 0x3a
        __emit 0x59
        __emit 0x00
        __emit 0x8b
        __emit 0x0d
        __emit 0x6c
        __emit 0x07
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xff
        __emit 0x52
        __emit 0x44
        __emit 0x8b
        __emit 0xf0
        __emit 0x85
        __emit 0xf6
        __emit 0x74
        __emit 0x31
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x87
        __emit 0x23
        __emit 0xd1
        __emit 0xff
        __emit 0x84
        __emit 0xc0
        __emit 0x74
        __emit 0x26
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x7f
        __emit 0x00
        __emit 0xd3
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0x68
        __emit 0x00
        __emit 0x00
        __emit 0x80
        __emit 0x40
        __emit 0x51
        __emit 0x8b
        __emit 0x0d
        __emit 0xe4
        __emit 0xf0
        __emit 0x2e
        __emit 0x01
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x10
        __emit 0x52
        __emit 0xe8
        __emit 0xf5
        __emit 0x49
        __emit 0xd1
        __emit 0xff
        __emit 0x5e
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}
