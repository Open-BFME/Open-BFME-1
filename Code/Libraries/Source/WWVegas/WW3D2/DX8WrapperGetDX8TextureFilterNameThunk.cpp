// cl: /DNDEBUG /MD /EHsc

class DX8Wrapper
{
public:
    static const char* Get_DX8_Texture_Filter_Name(unsigned value);
};

__declspec(naked) const char* DX8Wrapper::Get_DX8_Texture_Filter_Name(unsigned)
{
    __asm {
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 004h
        _emit 048h
        _emit 083h
        _emit 0F8h
        _emit 007h
        _emit 077h
        _emit 037h
        _emit 0FFh
        _emit 024h
        _emit 085h
        _emit 008h
        _emit 02Fh
        _emit 0D0h
        _emit 000h
        _emit 0B8h
        _emit 080h
        _emit 09Eh
        _emit 013h
        _emit 001h
        _emit 0C3h
        _emit 0B8h
        _emit 06Ch
        _emit 09Eh
        _emit 013h
        _emit 001h
        _emit 0C3h
        _emit 0B8h
        _emit 054h
        _emit 09Eh
        _emit 013h
        _emit 001h
        _emit 0C3h
        _emit 0B8h
        _emit 03Ch
        _emit 09Eh
        _emit 013h
        _emit 001h
        _emit 0C3h
        _emit 0B8h
        _emit 024h
        _emit 09Eh
        _emit 013h
        _emit 001h
        _emit 0C3h
        _emit 0B8h
        _emit 010h
        _emit 09Eh
        _emit 013h
        _emit 001h
        _emit 0C3h
        _emit 0B8h
        _emit 0FCh
        _emit 09Dh
        _emit 013h
        _emit 001h
        _emit 0C3h
        _emit 0B8h
        _emit 0E8h
        _emit 09Dh
        _emit 013h
        _emit 001h
        _emit 0C3h
        _emit 0B8h
        _emit 034h
        _emit 002h
        _emit 008h
        _emit 001h
        _emit 0C3h
    }
}
