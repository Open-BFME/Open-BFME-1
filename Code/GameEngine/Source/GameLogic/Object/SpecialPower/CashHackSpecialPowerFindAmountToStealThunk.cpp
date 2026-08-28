// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CashHackSpecialPower.h
class CashHackSpecialPower
{
protected:
    int findAmountToSteal() const;
};

__declspec(naked) int CashHackSpecialPower::findAmountToSteal() const
{
    __asm {
        _emit 053h
        _emit 056h
        _emit 057h
        _emit 08Bh
        _emit 079h
        _emit 004h
        _emit 08Bh
        _emit 049h
        _emit 008h
        _emit 0E8h
        _emit 086h
        _emit 082h
        _emit 0DCh
        _emit 0FFh
        _emit 08Bh
        _emit 0D8h
        _emit 085h
        _emit 0DBh
        _emit 074h
        _emit 029h
        _emit 08Bh
        _emit 0B7h
        _emit 010h
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 03Bh
        _emit 0B7h
        _emit 014h
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 074h
        _emit 01Bh
        _emit 08Bh
        _emit 006h
        _emit 050h
        _emit 08Bh
        _emit 0CBh
        _emit 0E8h
        _emit 083h
        _emit 00Eh
        _emit 0DBh
        _emit 0FFh
        _emit 084h
        _emit 0C0h
        _emit 075h
        _emit 017h
        _emit 08Bh
        _emit 087h
        _emit 014h
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 083h
        _emit 0C6h
        _emit 008h
        _emit 03Bh
        _emit 0F0h
        _emit 075h
        _emit 0E5h
        _emit 08Bh
        _emit 087h
        _emit 01Ch
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 05Fh
        _emit 05Eh
        _emit 05Bh
        _emit 0C3h
        _emit 08Bh
        _emit 046h
        _emit 004h
        _emit 05Fh
        _emit 05Eh
        _emit 05Bh
        _emit 0C3h
    }
}
