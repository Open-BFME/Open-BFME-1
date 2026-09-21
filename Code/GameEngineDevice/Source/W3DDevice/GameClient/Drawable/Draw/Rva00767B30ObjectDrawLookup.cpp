// cl: /DNDEBUG /MD /EHsc /O2 /ICode/Libraries/Source/WWVegas/WWLib
// Retail body at 0x00767B30, 248 bytes.
//
// The W3DModelDraw secondary vtable family (candidate tables 0x011223A0,
// 0x01122DD8, 0x011232C0, 0x01123C68, 0x01125600, 0x011259E0, 0x011264E0 --
// tools/vtable_lookup.py --target 0x00767B30) installs this body at slot 32
// (+0x80). It shares the exact -0x0C secondary-view adjustment, the slot46
// (+0xB8) lookup, the self+0x1F4 preferred-string check with its
// self-8+0xE0 fallback, and the slot31/slot5/release protocol with the two
// already-landed siblings in this same directory: slot 34
// (Rva007638E0ObjectDrawLookup.cpp, 0x007638E0) and slot 35
// (Gen_007639E0_ObjectDrawLookup.cpp, 0x007639E0). Unlike those two, this
// entry also fills a caller-supplied out parameter through the pinned
// callee reached by thunk j_0002E7B7 (-> retail dump 0x00763AC0), zeroing
// the out parameter up front and only calling out when slot5() returns
// nonzero; the fixed empty-string address 0x0107388B matches the constant
// already used by the slot-35 sibling.
//
// The address-derived class name records the body identity without
// claiming a semantic method name that the retail image does not prove.

#include "ascii_string.h"

class Rva00767B30Base
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

class Rva00767B30Result
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
    virtual Rva00767B30Result *slot31(const char *text, int zero);
};

extern void j_0002e7b7();

struct Rva00767B30OutCall
{
    int call(int slot5Result, void *outParam);
};

static int callOut(Rva00767B30Base *self, int slot5Result, void *outParam)
{
    typedef int (Rva00767B30OutCall::*Function)(int, void *);
    union { void (*raw)(); Function member; } function;
    function.raw = j_0002e7b7;
    return (reinterpret_cast<Rva00767B30OutCall *>(self)->*function.member)(slot5Result, outParam);
}

class Rva00767B30
{
public:
    int method(void *outParam);
};

int Rva00767B30::method(void *outParam)
{
    char *self = (char *)this;
    Rva00767B30Base *adjusted = (Rva00767B30Base *)(self - 0x0C);
    Rva00767B30Result *result = (Rva00767B30Result *)adjusted->slot46();
    *(void **)outParam = 0;
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
            char *base2 = *(char **)(self - 8);
            local.set(*(AsciiString *)(base2 + 0xE0));
        }
        text = (*(void **)&local) ? (const char *)(*(void **)&local) + 8 : (const char *)0x0107388B;

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

    if (slot5Result)
        return callOut(adjusted, slot5Result, outParam);

    return 0;
}
