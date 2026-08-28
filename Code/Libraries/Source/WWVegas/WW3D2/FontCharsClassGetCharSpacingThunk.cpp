// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
class FontCharsClass
{
public:
    int Get_Char_Spacing(unsigned short ch);
};

__declspec(naked) int FontCharsClass::Get_Char_Spacing(unsigned short)
{
    __asm {
        _emit 056h
        _emit 057h
        _emit 08Bh
        _emit 07Ch
        _emit 024h
        _emit 00Ch
        _emit 057h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 012h
        _emit 0FEh
        _emit 0FFh
        _emit 0FFh
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 045h
        _emit 066h
        _emit 08Bh
        _emit 048h
        _emit 002h
        _emit 066h
        _emit 085h
        _emit 0C9h
        _emit 074h
        _emit 03Ch
        _emit 066h
        _emit 081h
        _emit 0FFh
        _emit 001h
        _emit 00Eh
        _emit 072h
        _emit 007h
        _emit 066h
        _emit 081h
        _emit 0FFh
        _emit 03Ah
        _emit 00Eh
        _emit 076h
        _emit 00Eh
        _emit 066h
        _emit 081h
        _emit 0FFh
        _emit 03Fh
        _emit 00Eh
        _emit 072h
        _emit 015h
        _emit 066h
        _emit 081h
        _emit 0FFh
        _emit 05Bh
        _emit 00Eh
        _emit 077h
        _emit 00Eh
        _emit 00Fh
        _emit 0BFh
        _emit 040h
        _emit 004h
        _emit 00Fh
        _emit 0BFh
        _emit 0C9h
        _emit 05Fh
        _emit 003h
        _emit 0C1h
        _emit 05Eh
        _emit 0C2h
        _emit 004h
        _emit 000h
        _emit 008Bh
        _emit 056h
        _emit 038h
        _emit 00Fh
        _emit 0BFh
        _emit 0C1h
        _emit 08Bh
        _emit 04Eh
        _emit 034h
        _emit 02Bh
        _emit 0C2h
        _emit 05Fh
        _emit 02Bh
        _emit 0C1h
        _emit 05Eh
        _emit 0C2h
        _emit 004h
        _emit 000h
        _emit 05Fh
        _emit 033h
        _emit 0C0h
        _emit 05Eh
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
