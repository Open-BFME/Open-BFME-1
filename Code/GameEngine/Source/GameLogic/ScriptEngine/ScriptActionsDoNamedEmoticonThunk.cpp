// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
    void doNamedEmoticon(const AsciiString &, const AsciiString &, float);
};

__declspec(naked) void ScriptActions::doNamedEmoticon(const AsciiString &, const AsciiString &, float)
{
    __asm {
        __emit 0x8b;
        __emit 0x0d;
        __emit 0x6c;
        __emit 0x07;
        __emit 0x2f;
        __emit 0x01;
        __emit 0x8b;
        __emit 0x54;
        __emit 0x24;
        __emit 0x04;
        __emit 0x8b;
        __emit 0x01;
        __emit 0x52;
        __emit 0xff;
        __emit 0x50;
        __emit 0x68;
        __emit 0x85;
        __emit 0xc0;
        __emit 0x74;
        __emit 0x2b;
        __emit 0x8b;
        __emit 0x10;
        __emit 0x56;
        __emit 0x8b;
        __emit 0xc8;
        __emit 0xff;
        __emit 0x52;
        __emit 0x28;
        __emit 0x8b;
        __emit 0xf0;
        __emit 0x85;
        __emit 0xf6;
        __emit 0x74;
        __emit 0x1c;
        __emit 0xd9;
        __emit 0x44;
        __emit 0x24;
        __emit 0x10;
        __emit 0xd8;
        __emit 0x0d;
        __emit 0x44;
        __emit 0x53;
        __emit 0x07;
        __emit 0x01;
        __emit 0xe8;
        __emit 0x17;
        __emit 0x69;
        __emit 0x70;
        __emit 0x00;
        __emit 0x50;
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x10;
        __emit 0x50;
        __emit 0x8b;
        __emit 0xce;
        __emit 0xe8;
        __emit 0x0e;
        __emit 0x15;
        __emit 0xd1;
        __emit 0xff;
        __emit 0x5e;
        __emit 0xc2;
        __emit 0x0c;
        __emit 0x00;
    }
}
