// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AISkirmishPlayer.h
class AISkirmishPlayer
{
protected:
    int getMyEnemyPlayerIndex(void);
};

__declspec(naked) int AISkirmishPlayer::getMyEnemyPlayerIndex(void)
{
    __asm {
        _emit 08Bh
        _emit 081h
        _emit 09Ch
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 004h
        _emit 08Bh
        _emit 040h
        _emit 024h
        _emit 0C3h
        _emit 08Bh
        _emit 00Dh
        _emit 048h
        _emit 0D7h
        _emit 02Eh
        _emit 001h
        _emit 08Bh
        _emit 041h
        _emit 010h
        _emit 056h
        _emit 033h
        _emit 0F6h
        _emit 085h
        _emit 0C0h
        _emit 07Eh
        _emit 01Dh
        _emit 08Bh
        _emit 0FFh
        _emit 056h
        _emit 0E8h
        _emit 05Ah
        _emit 0C7h
        _emit 0EDh
        _emit 0FFh
        _emit 08Bh
        _emit 048h
        _emit 02Ch
        _emit 085h
        _emit 0C9h
        _emit 074h
        _emit 00Eh
        _emit 08Bh
        _emit 00Dh
        _emit 048h
        _emit 0D7h
        _emit 02Eh
        _emit 001h
        _emit 08Bh
        _emit 041h
        _emit 010h
        _emit 046h
        _emit 03Bh
        _emit 0F0h
        _emit 07Ch
        _emit 0E5h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
    }
}
