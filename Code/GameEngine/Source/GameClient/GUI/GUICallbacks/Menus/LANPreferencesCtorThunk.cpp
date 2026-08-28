// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class LANPreferences
{
public:
    LANPreferences();
};

// ??0LANPreferences@@
__declspec(naked) LANPreferences::LANPreferences()
{
    __asm {
        __emit 0x6a;
        __emit 0xff;
        __emit 0x68;
        __emit 0x58;
        __emit 0x53;
        __emit 0xff;
        __emit 0x00;
        __emit 0x64;
        __emit 0xa1;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x50;
        __emit 0x64;
        __emit 0x89;
        __emit 0x25;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x83;
        __emit 0xec;
        __emit 0x08;
        __emit 0x56;
        __emit 0x8b;
        __emit 0xf1;
        __emit 0x89;
        __emit 0x74;
        __emit 0x24;
        __emit 0x04;
        __emit 0xe8;
        __emit 0xf7;
        __emit 0x4c;
        __emit 0xfc;
        __emit 0xff;
        __emit 0x51;
        __emit 0x89;
        __emit 0x64;
        __emit 0x24;
        __emit 0x0c;
        __emit 0x8b;
        __emit 0xcc;
        __emit 0x68;
        __emit 0x20;
        __emit 0xc7;
        __emit 0x07;
        __emit 0x01;
        __emit 0xc7;
        __emit 0x44;
        __emit 0x24;
        __emit 0x1c;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0xc7;
        __emit 0x06;
        __emit 0xf8;
        __emit 0xc6;
        __emit 0x07;
        __emit 0x01;
        __emit 0xe8;
        __emit 0xfd;
        __emit 0x26;
        __emit 0x80;
        __emit 0x00;
        __emit 0x8b;
        __emit 0xce;
        __emit 0xe8;
        __emit 0x3e;
        __emit 0xde;
        __emit 0xf8;
        __emit 0xff;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x0c;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x64;
        __emit 0x89;
        __emit 0x0d;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x5e;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x14;
        __emit 0xc3;
    }
}
