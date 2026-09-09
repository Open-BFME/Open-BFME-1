// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

// The two shims the forwarding thunks in ProductionPrerequisiteThunks.cpp jump
// to, and the only bodies in this family that do any work:
//
//   0x003A9010  34B  ProductionPrerequisiteDestroyShim::destroy
//   0x00784DB0  19B  ProductionPrerequisiteConstructShim::construct
//
// The dup_ rows at 0x003A7200 and 0x003A8560 are byte-identical copies of the
// destroy shim at other addresses; they ride with it, as they did before, and
// keep their address-derived names.
//
// The two files declared ProductionPrerequisite differently and each was
// right about its own half: the construct side needs a copy constructor,
// because its body is a placement new of one; the destroy side left the class
// incomplete, because its body never touches a ProductionPrerequisite -- it
// casts the range to a local stand-in with a virtual destructor and runs that.
// One declaration carries the copy constructor, and the destroy body is
// unaffected by the class being complete, which is the thing neither file could
// check on its own.
//
// They must stay OUT of the thunks file. With these two definitions visible,
// MSVC inlines them into the forwarding templates rather than tail jumping, and
// the two five-byte `e9` rows come back as real bodies. The boundary between
// this file and that one is the compiler's inlining decision, not the subject.

inline void *operator new(unsigned int, void *place) { return place; }

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
public:
    ProductionPrerequisite(const ProductionPrerequisite &);
};

class ProductionPrerequisiteRetailCopy
{
public:
    ProductionPrerequisiteRetailCopy(const ProductionPrerequisiteRetailCopy &);
};

namespace _STL
{

class ProductionPrerequisiteConstructShim
{
public:
    static void construct(ProductionPrerequisite *p, const ProductionPrerequisite &v);
};

class ProductionPrerequisiteDestroyShim
{
public:
    static void destroy(ProductionPrerequisite *first, ProductionPrerequisite *last);
};

// ?ProductionPrerequisiteConstructShim::construct present-unmatched
void ProductionPrerequisiteConstructShim::construct(ProductionPrerequisite *p, const ProductionPrerequisite &v)
{
    if (p)
        new (p) ProductionPrerequisiteRetailCopy(
            *(const ProductionPrerequisiteRetailCopy *)&v);
}

namespace
{
class LocalProductionPrerequisite
{
public:
    virtual ~LocalProductionPrerequisite();
private:
    unsigned char m_pad[0x18 - sizeof(void *)];
};

// ?LocalProductionPrerequisite::~LocalProductionPrerequisite present-unmatched
LocalProductionPrerequisite::~LocalProductionPrerequisite()
{
}
}

// ProductionPrerequisiteDestroyShim::destroy present-unmatched
// ?ProductionPrerequisiteDestroyShim::destroy present-unmatched
void ProductionPrerequisiteDestroyShim::destroy(ProductionPrerequisite *first, ProductionPrerequisite *last)
{
    LocalProductionPrerequisite *f = (LocalProductionPrerequisite *)first;
    LocalProductionPrerequisite *l = (LocalProductionPrerequisite *)last;
    for (; f != l; ++f)
        f->~LocalProductionPrerequisite();
}

}
