// cl: /DNDEBUG /MD /EHsc /O2
// Retail body at 0x007639E0, 169 bytes.
//
// The W3DModelDraw secondary table at 0x01123C68 sends slot 35 through
// j_0004981E to this body. The entry receives the secondary view, so the
// primary W3DModelDraw view starts 0x0C bytes earlier.
//
// The address-derived class name avoids claiming a method name that the
// retail image does not prove. The local string view uses the ledger's
// UnicodeString spelling for the one-pointer copy body at 0x00887C90.

class BFMERetailAsciiString
{
public:
    void releaseBuffer();
};

class UnicodeString
{
public:
    UnicodeString() : m_data(0) {}
    ~UnicodeString() { ((BFMERetailAsciiString *)this)->releaseBuffer(); }
    void set(const UnicodeString &other);
    void *m_data;
};

class Gen_007639E0Base
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
    virtual void d044(); virtual void d045(); virtual void *slot46();
};

class Gen_007639E0Result
{
public:
    virtual void release();
    virtual void d001(); virtual void d002(); virtual void d003(); virtual void d004();
    virtual int slot5();
    virtual void d006(); virtual void d007(); virtual void d008(); virtual void d009();
    virtual void d010(); virtual void d011(); virtual void d012(); virtual void d013();
    virtual void d014(); virtual void d015(); virtual void d016(); virtual void d017();
    virtual void d018(); virtual void d019(); virtual void d020(); virtual void d021();
    virtual void d022(); virtual void d023(); virtual void d024(); virtual void d025();
    virtual void d026(); virtual void d027(); virtual void d028(); virtual void d029();
    virtual void d030();
    virtual Gen_007639E0Result *slot31(const char *text, int zero);
};

class Gen_007639E0
{
public:
    int method();
};

int Gen_007639E0::method()
{
    char *self = (char *)this;
    Gen_007639E0Base *adjusted = (Gen_007639E0Base *)(self - 0x0C);
    Gen_007639E0Result *result = (Gen_007639E0Result *)adjusted->slot46();
    int slot5Result = 0;
    if (result)
    {
        const char *text;
        UnicodeString local;
        self = (char *)*(void **)(self - 8);
        local.set(*(UnicodeString *)(self + 0xE4));
        text = local.m_data ? (const char *)local.m_data + 8 : (const char *)0x0107388B;
        result = result->slot31(text, 0);
        if (result)
        {
            slot5Result = result->slot5();
            if (!slot5Result)
            {
                if (--*(int *)((char *)result + 4) == 0)
                    result->release();
            }
        }
    }
    return slot5Result;
}
