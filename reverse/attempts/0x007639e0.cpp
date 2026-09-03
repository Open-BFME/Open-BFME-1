// ?d_007639e0@@YAXXZ
// partial score=0.97 date=2026-09-02
// candidate for retail 0x007639E0 (169B), currently ?d_007639e0@@YAXXZ
// cl: /DNDEBUG /MD /EHsc /O2
// W3DModelDraw-family instance method, thiscall(void), returns bool (eax=ebx).
// Adjusted-this (-0xC) virtual call at vtable slot 0xB8/4=46 yields an object
// (esi); if null, returns false. Otherwise builds a local AsciiString from
// *(this-8)+0xE4 via the pinned AsciiString::set(const AsciiString&)
// (0x00887C90), resolves its text (buffer+8, else default literal
// 0x0107388B), and calls esi's own vtable slot 0x7C/4=31 with (text, 0).
// If that yields a non-null object, calls its vtable slot 0x14/4=5 (the
// return value) and, when that is zero, decrements its refcount at +4 and
// releases via vtable slot 0 on hitting zero.

class AsciiString
{
public:
    AsciiString() : m_data(0) {}
    ~AsciiString();
    void set(const AsciiString &other);
    void *m_data;
};

class Gen07639E0Base
{
public:
    virtual void d000(); virtual void d001(); virtual void d002(); virtual void d003();
    virtual void d004(); virtual void d005(); virtual void d006(); virtual void d007();
    virtual void d008(); virtual void d009(); virtual void d010(); virtual void d011();
    virtual void d012(); virtual void d013(); virtual void d014(); virtual void d015();
    virtual void d016(); virtual void d017(); virtual void d018(); virtual void d019();
    virtual void d020(); virtual void d021(); virtual void d022(); virtual void d023();
    virtual void d024(); virtual void d025(); virtual void d026(); virtual void d027();
    virtual void d028(); virtual void d029(); virtual void d030(); virtual void d031();
    virtual void d032(); virtual void d033(); virtual void d034(); virtual void d035();
    virtual void d036(); virtual void d037(); virtual void d038(); virtual void d039();
    virtual void d040(); virtual void d041(); virtual void d042(); virtual void d043();
    virtual void d044(); virtual void d045();
    virtual void *slot46();
};

class Gen07639E0Result
{
public:
    virtual void release(); // slot 0
    virtual void d001(); virtual void d002(); virtual void d003(); virtual void d004();
    virtual int slot5();
    virtual void d006(); virtual void d007(); virtual void d008(); virtual void d009();
    virtual void d010(); virtual void d011(); virtual void d012(); virtual void d013();
    virtual void d014(); virtual void d015(); virtual void d016(); virtual void d017();
    virtual void d018(); virtual void d019(); virtual void d020(); virtual void d021();
    virtual void d022(); virtual void d023(); virtual void d024(); virtual void d025();
    virtual void d026(); virtual void d027(); virtual void d028(); virtual void d029();
    virtual void d030();
    virtual Gen07639E0Result *slot31(const char *text, int zero);
};

class Gen_007639E0
{
public:
    int method();
};

int Gen_007639E0::method()
{
    char *self = (char *)this;
    Gen07639E0Base *adjusted = (Gen07639E0Base *)(self - 0x0C);
    Gen07639E0Result *result = (Gen07639E0Result *)adjusted->slot46();
    int slot5Result = 0;

    if (result) {
        AsciiString local;
        local.set(*(AsciiString *)((char *)(*(void **)(self - 8)) + 0xE4));

        const char *text = local.m_data ? (const char *)local.m_data + 8 : (const char *)0x0107388B;

        result = result->slot31(text, 0);
        if (result) {
            slot5Result = result->slot5();
            if (!slot5Result) {
                if (--*(int *)((char *)result + 4) == 0)
                    result->release();
            }
        }
    }

    return slot5Result;
}
