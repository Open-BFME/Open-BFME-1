class RenderObjClass
{
public:
    virtual void Set_Force_Visible(int);
};

__declspec(naked) void RenderObjClass::Set_Force_Visible(int)
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 08Bh
        _emit 006h
        _emit 0FFh
        _emit 090h
        _emit 09Ch
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 08Bh
        _emit 0C8h
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 008h
        _emit 0F7h
        _emit 0D9h
        _emit 01Bh
        _emit 0C9h
        _emit 033h
        _emit 0D2h
        _emit 0F7h
        _emit 0D9h
        _emit 085h
        _emit 0C0h
        _emit 00Fh
        _emit 095h
        _emit 0C2h
        _emit 03Bh
        _emit 0D1h
        _emit 074h
        _emit 026h
        _emit 081h
        _emit 076h
        _emit 010h
        _emit 000h
        _emit 080h
        _emit 000h
        _emit 000h
        _emit 08Bh
        _emit 08Eh
        _emit 080h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 085h
        _emit 0C9h
        _emit 074h
        _emit 015h
        _emit 085h
        _emit 0C0h
        _emit 06Ah
        _emit 004h
        _emit 056h
        _emit 074h
        _emit 009h
        _emit 08Bh
        _emit 001h
        _emit 0FFh
        _emit 050h
        _emit 038h
        _emit 05Eh
        _emit 0C2h
        _emit 004h
        _emit 000h
        _emit 08Bh
        _emit 011h
        _emit 0FFh
        _emit 052h
        _emit 03Ch
        _emit 05Eh
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
