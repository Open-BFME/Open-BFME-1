// ?apply@Rva00077ce0@@QAEXH@Z
// partial score=0.5752 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /Od /Ob0
// stlport
// Decoded 0x00077CE0; unsigned keys and copied key-pointer value.

#include <map>
#include <set>

struct ModifierRecord
{
    char pad_00[0x18];
    int op;
    char pad_1c[4];
    int value;
    int *dest;
    char pad_28[8];
    int processed;
};

class BfmeTreeYN;
class BfmeTreeYK;
BfmeTreeYN *bfmeTreeYN();
BfmeTreeYK *bfmeTreeYK();

class Rva00077C70Receiver
{
public:
    void method(int key);
};
class Rva00077ce0
{
public:
    void apply(int key);
};

// ?apply@Rva00077ce0@@QAEXH@Z
void Rva00077ce0::apply(int key)
{
    __asm {
        push eax
        mov eax, 0CFCECDCCh
    rva00077ce0Marker:
        mov eax, OFFSET rva00077ce0Marker
        mov eax, 0
        mov eax, 0
        mov eax, 0CFCECDCCh
        pop eax
    }
    typedef _STL::set<unsigned int> Set;
    typedef _STL::map<unsigned int, ModifierRecord *> Map;
    Set::iterator range1first = ((Set *)bfmeTreeYN())->find(reinterpret_cast<const unsigned int &>(key));
    if (range1first == ((Set *)bfmeTreeYN())->end())
    {
        Map::iterator range2first = ((Map *)bfmeTreeYK())->find(reinterpret_cast<const unsigned int &>(key));
        if (range2first != ((Map *)bfmeTreeYK())->end())
        {
            Map::value_type range2second(*range2first);
            ModifierRecord *rec = range2second.second;
            if (rec->processed == 0)
            {
                switch (rec->op)
                {
                case 0: *rec->dest = rec->value; break;
                case 1: *rec->dest = *rec->dest + rec->value; break;
                case 2: *rec->dest = *rec->dest - rec->value; break;
                }
                rec->processed = 1;
            }
            else
            {
                bool flag = false;
                ((Rva00077C70Receiver *)&flag)->method(key);
            }
        }
    }
    __asm {
        push eax
        mov eax, 0CFCECDCCh
        mov eax, OFFSET rva00077ce0Marker
        mov eax, 0
        mov eax, 0
        mov eax, 0CECDCCCBh
        pop eax
    }
}
