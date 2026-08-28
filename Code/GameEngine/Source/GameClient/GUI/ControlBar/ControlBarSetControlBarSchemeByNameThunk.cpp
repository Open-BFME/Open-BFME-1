// cl: /DNDEBUG /MD /EHsc

class AsciiString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
    void setControlBarSchemeByName(const AsciiString &);
};

__declspec(naked) void ControlBar::setControlBarSchemeByName(const AsciiString &)
{
    __asm {
        __emit 0x51;
        __emit 0x56;
        __emit 0x8b;
        __emit 0xf1;
        __emit 0x8b;
        __emit 0x46;
        __emit 0x30;
        __emit 0x85;
        __emit 0xc0;
        __emit 0x74;
        __emit 0x34;
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x0c;
        __emit 0x51;
        __emit 0x89;
        __emit 0x64;
        __emit 0x24;
        __emit 0x08;
        __emit 0x8b;
        __emit 0xcc;
        __emit 0x50;
        __emit 0xe8;
        __emit 0xb4;
        __emit 0x7a;
        __emit 0x3e;
        __emit 0x00;
        __emit 0x8b;
        __emit 0x4e;
        __emit 0x30;
        __emit 0xe8;
        __emit 0xe2;
        __emit 0xa0;
        __emit 0xb6;
        __emit 0xff;
        __emit 0x8b;
        __emit 0x0d;
        __emit 0x2c;
        __emit 0xd6;
        __emit 0x2e;
        __emit 0x01;
        __emit 0x85;
        __emit 0xc9;
        __emit 0x74;
        __emit 0x0a;
        __emit 0xe8;
        __emit 0x28;
        __emit 0x3e;
        __emit 0xba;
        __emit 0xff;
        __emit 0x83;
        __emit 0xf8;
        __emit 0x01;
        __emit 0x74;
        __emit 0x07;
        __emit 0x8b;
        __emit 0xce;
        __emit 0xe8;
        __emit 0xa4;
        __emit 0x3d;
        __emit 0xba;
        __emit 0xff;
        __emit 0x5e;
        __emit 0x59;
        __emit 0xc2;
        __emit 0x04;
        __emit 0x00;
    }
}
