// cl: /DNDEBUG /MD /EHsc
// readable body of ?loadPostProcess@Drawable@@MAEXXZ: Code/GameEngine/Source/GameClient/Drawable.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
protected:
    virtual void loadPostProcess();
};

__declspec(naked) void Drawable::loadPostProcess()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 08Bh
        _emit 086h
        _emit 09Ch
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 00Ch
        _emit 083h
        _emit 0C0h
        _emit 008h
        _emit 050h
        _emit 08Dh
        _emit 04Eh
        _emit 0A0h
        _emit 0E8h
        _emit 015h
        _emit 041h
        _emit 0C2h
        _emit 0FFh
        _emit 08Bh
        _emit 086h
        _emit 05Ch
        _emit 003h
        _emit 000h
        _emit 000h
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 008h
        _emit 08Bh
        _emit 0C8h
        _emit 08Bh
        _emit 001h
        _emit 05Eh
        _emit 0FFh
        _emit 060h
        _emit 004h
        _emit 05Eh
        _emit 0C3h
    }
}
