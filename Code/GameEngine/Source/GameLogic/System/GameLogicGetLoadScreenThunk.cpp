// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class LoadScreen
{
};

class GameLogic
{
    LoadScreen *getLoadScreen(bool);
};

// ?getLoadScreen@GameLogic@@AAEPAVLoadScreen@@_N@Z
__declspec(naked) LoadScreen *GameLogic::getLoadScreen(bool)
{
    __asm {
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
        __emit 0x56
        __emit 0x68
        __emit 0x94
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x3f
        __emit 0x72
        __emit 0x1c
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x74
        __emit 0x16
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x4e
        __emit 0x33
        __emit 0x98
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x5c
        __emit 0xca
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0x48
        __emit 0xca
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
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
