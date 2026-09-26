// cl: /DNDEBUG /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WWLib
// Retail body at 0x007638E0, 194 bytes.
//
// The W3DModelDraw secondary table at 0x01123C68 sends slot 34 through
// j_000340C7 to this body.  The entry receives the secondary view, so the
// primary W3DModelDraw view starts 0x0C bytes earlier.
//
// The address-derived class name records the body identity without claiming
// a semantic method name that the retail image does not prove.

// Assignment0x887C90 and release0x887940 are shared string helpers; their
// UnicodeString ledger alias does not require a local UnicodeString class.
// Use the existing narrow-string header for the name passed to slot31.
#include "ascii_string.h"

class Rva007638E0Base
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

class Rva007638E0Result
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
    virtual Rva007638E0Result *slot31(const char *text, int zero);
};

class Rva007638E0
{
public:
    int method();
};

int Rva007638E0::method()
{
    char *self = (char *)this;
    Rva007638E0Base *adjusted = (Rva007638E0Base *)(self - 0x0C);
    Rva007638E0Result *result = (Rva007638E0Result *)adjusted->slot46();
    int slot5Result = 0;
    if (result)
    {
        const char *text;
        AsciiString local;
        AsciiString *preferred = (AsciiString *)(self + 0x1F4);
        if ((*(void **)preferred) != 0 &&
            *(unsigned short *)((char *)(*(void **)preferred) + 4) != 0)
            local.set(*preferred);
        else
        {
            self = (char *)*(void **)(self - 8);
            local.set(*(AsciiString *)(self + 0xE0));
        }
        text = (*(void **)&local) ? (const char *)(*(void **)&local) + 8 : "";
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
