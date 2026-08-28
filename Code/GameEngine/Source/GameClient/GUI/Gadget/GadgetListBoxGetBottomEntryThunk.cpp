// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Gadget.h
struct _ListboxData
{
};

__declspec(naked) int getListboxBottomEntry(_ListboxData *)
{
    __asm {
        __emit 0x0f;
        __emit 0xbf;
        __emit 0x41;
        __emit 0x2c;
        __emit 0x56;
        __emit 0x57;
        __emit 0x8d;
        __emit 0x78;
        __emit 0xff;
        __emit 0x8b;
        __emit 0xc7;
        __emit 0x85;
        __emit 0xc0;
        __emit 0x7c;
        __emit 0x23;
        __emit 0x0f;
        __emit 0xbf;
        __emit 0x51;
        __emit 0x44;
        __emit 0x0f;
        __emit 0xbf;
        __emit 0x71;
        __emit 0x3c;
        __emit 0x8b;
        __emit 0x49;
        __emit 0x18;
        __emit 0x03;
        __emit 0xf2;
        __emit 0x8d;
        __emit 0x14;
        __emit 0x40;
        __emit 0x8d;
        __emit 0x14;
        __emit 0x91;
        __emit 0x8b;
        __emit 0x0a;
        __emit 0x3b;
        __emit 0xce;
        __emit 0x74;
        __emit 0x14;
        __emit 0x7c;
        __emit 0x0d;
        __emit 0x48;
        __emit 0x83;
        __emit 0xea;
        __emit 0x0c;
        __emit 0x85;
        __emit 0xc0;
        __emit 0x7d;
        __emit 0xf0;
        __emit 0x5f;
        __emit 0x33;
        __emit 0xc0;
        __emit 0x5e;
        __emit 0xc3;
        __emit 0x3b;
        __emit 0xc7;
        __emit 0x74;
        __emit 0x01;
        __emit 0x40;
        __emit 0x5f;
        __emit 0x5e;
        __emit 0xc3;
    }
}
