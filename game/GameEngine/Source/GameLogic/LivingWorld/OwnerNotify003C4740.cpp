// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include "ascii_string.h"
class Gen003BD8D0Built;
class Gen003BD7D0Node { public: Gen003BD8D0Built *build(); };
class Rva003BF540 { public: Gen003BD7D0Node *find(int); };
class Gen003C0110Result;
class Rva003BC9C0 { public: void run(Gen003C0110Result *, void *); };
class Gen003BF540Owner { public: bool consume(void *, Gen003BD8D0Built *, void *, void *); };
class LivingWorldRegion;
class LivingWorldRegionManager { public: LivingWorldRegion *rva003C8A50(const AsciiString &); };
struct Flag003C4740 { char m_00[0x18]; char m_18; };
class Gen003BD8D0Built { public: char m_00[0xec]; Flag003C4740 *m_EC; };
struct Holder003C4740 { char m_00[8]; Gen003BD8D0Built *m_08; };
class Glo012F1028Type {
public:
    void rva003C4740();
    void rva003C3F40();
    char m_00[0x28];
    Holder003C4740 *m_28;
    char m_2C[8];
    int m_34;
};
void Glo012F1028Type::rva003C4740() {
    if(m_34) {
        Gen003BD8D0Built *p=m_28->m_08;
        if(p) {
            rva003C3F40();
            Gen003BD7D0Node *owner=((Rva003BF540*)this)->find(m_34);
            if(!owner->build()) {
                ((Rva003BC9C0*)this)->run((Gen003C0110Result*)owner,p);
                return;
            }
            std::vector<AsciiString> names;
            char saved=p->m_EC->m_18;
            p->m_EC->m_18=1;
            if(((Gen003BF540Owner*)m_28)->consume(owner->build(),p,&names,0)) {
                if(owner->build()==p)
                    ((Rva003BC9C0*)this)->run((Gen003C0110Result*)owner,p);
                else {
                    for(unsigned i=1; i<names.size(); ++i) {
                        ((Rva003BC9C0*)this)->run((Gen003C0110Result*)owner,((LivingWorldRegionManager*)m_28)->rva003C8A50(names[i]));
                        names[i].~AsciiString();
                    }
                    names[0].~AsciiString();
                }
            }
            p=(Gen003BD8D0Built*)p->m_EC;
            ((Flag003C4740*)p)->m_18=saved;
        }
    }
}
