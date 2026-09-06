// cl: /EHsc /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include/Common /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME7: retail 0x006BAEE0 (87 bytes) is the fuzzy twin of the RenderObject particle
// createTemplate() (fx_particle_system_bulk.cpp, 0x005E1140): a module factory whose template
// allocation is 0x24 bytes with TWO retail subobject vtables (+0 and +8) installed over the
// shim-constructed base.  Address-tagged classes; the ctor shim resolves through autopin.
#include "fx_particle_system.h"
#include <memory.h>
#include <memory>

class Rva006BAEE0CtorShim {
public:
    void construct();
};

class Rva006BAEE0TemplateAllocation {
public:
    __forceinline Rva006BAEE0TemplateAllocation()
    {
        ((Rva006BAEE0CtorShim *)this)->construct();
        *(volatile unsigned int *)this = 0x0111caac;
        *(volatile unsigned int *)((unsigned char *)this + 8) = 0x0111ca98;
    }

private:
    unsigned char m_storage[0x24];
};

class Rva006BAEE0Template;

class Rva006BAEE0Factory {
public:
    virtual Rva006BAEE0Template *createTemplate() const;
};

Rva006BAEE0Template *Rva006BAEE0Factory::createTemplate() const
{
    return (Rva006BAEE0Template *)new Rva006BAEE0TemplateAllocation;
}
