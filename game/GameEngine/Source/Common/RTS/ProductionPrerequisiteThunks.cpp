// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ??1ProductionPrerequisite@@QAE@XZ: game/GameEngine/Source/Common/RTS/ProductionPrerequisite.cpp

// The three five-byte bodies that forward ProductionPrerequisite's
// construct/destroy plumbing to a shim, each one a single tail jump:
//
//   0x00011D47  _STL::_Destroy<ProductionPrerequisite *>
//   0x0003AA26  _STL::_Construct<PP, PP>
//   0x0003ECC0  ProductionPrerequisite::~ProductionPrerequisite
//
// All three are `e9 <rel32>` and nothing else. They sat in three files that
// each re-declared ProductionPrerequisite, and between them could not say what
// the class is: the destructor's file gave it a destructor, the other two left
// it incomplete. One declaration holds it.
//
// WHAT THIS FILE MUST NOT CONTAIN is the shims these jump to. Merging the two
// shim implementations in here was tried and rejected by the bytes: with
// ProductionPrerequisiteConstructShim::construct and
// ProductionPrerequisiteDestroyShim::destroy defined in the same translation
// unit, MSVC inlines them into the forwarding templates instead of tail
// jumping, and the two five-byte rows come back as real bodies -- `8b 4c 24 04`
// where retail has `e9`. The shims live in ProductionPrerequisiteShims.cpp and
// are only DECLARED here.
//
// That is the getTemplate rule from ScoreKeeperCounters seen from the other
// side. There, a body big enough to spill an inline accessor forced the
// accessor onto the class whose symbol the spill needed; here, a body small
// enough to be nothing but a jump forces its callee OUT of the file, because a
// visible definition is an invitation the compiler accepts. In both cases what
// decides the file boundary is the compiler's inlining decision, not the
// subject matter.
//
// The visual twin PrereqUnitRecConstruct.cpp cannot join either, for reasons
// that have nothing to do with inlining: it defines the SAME template,
// _STL::_Construct<T, U>, with a different body forwarding to
// PrereqUnitRecConstructShim, and one translation unit cannot hold two
// definitions of one template. It also spells ProductionPrerequisite as a
// NAMESPACE containing struct PrereqUnitRec where this file spells it a class.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
public:
    ~ProductionPrerequisite();
};

class ProductionPrerequisiteDestructorShim
{
public:
    void destroy();
};

// ??1ProductionPrerequisite@@QAE@XZ
ProductionPrerequisite::~ProductionPrerequisite()
{
	((ProductionPrerequisiteDestructorShim *)this)->destroy();
}

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

template <class T, class U>
void _Construct(T *, const U &);

template <class T, class U>
void _Construct(T *p, const U &v)
{
    ProductionPrerequisiteConstructShim::construct((ProductionPrerequisite *)p, *(const ProductionPrerequisite *)&v);
}

// ??$_Construct@VProductionPrerequisite@@V1@@_STL@@YAXPAVProductionPrerequisite@@ABV1@@Z
template void _Construct<ProductionPrerequisite, ProductionPrerequisite>(ProductionPrerequisite *, const ProductionPrerequisite &);

template <class T>
void _Destroy(T, T);

template <class T>
void _Destroy(T first, T last)
{
    ProductionPrerequisiteDestroyShim::destroy((ProductionPrerequisite *)first, (ProductionPrerequisite *)last);
}

// ??$_Destroy@PAVProductionPrerequisite@@@_STL@@YAXPAVProductionPrerequisite@@0@Z
template void _Destroy<ProductionPrerequisite *>(ProductionPrerequisite *, ProductionPrerequisite *);

}
