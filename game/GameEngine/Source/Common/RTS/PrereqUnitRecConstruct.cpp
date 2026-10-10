// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

namespace ProductionPrerequisite
{
struct PrereqUnitRec;
}

struct Gen_t_00582750_k4;
struct Gen_t_00582750_p12cd;

namespace _STL
{
template <class First, class Second> struct pair;

template <class T, class U>
void _Construct(T *, const U &);

// Retail ILT 0x00028957 jumps to the existing address-qualified pair
// _Construct at 0x00582750: cdecl with two caller-owned pointer arguments.
template <>
void _Construct<pair<const Gen_t_00582750_k4, Gen_t_00582750_p12cd>,
    pair<const Gen_t_00582750_k4, Gen_t_00582750_p12cd> >(
    pair<const Gen_t_00582750_k4, Gen_t_00582750_p12cd> *,
    const pair<const Gen_t_00582750_k4, Gen_t_00582750_p12cd> &);

template <class T, class U>
void _Construct(T *p, const U &v)
{
    _Construct((pair<const Gen_t_00582750_k4, Gen_t_00582750_p12cd> *)p,
        *(const pair<const Gen_t_00582750_k4, Gen_t_00582750_p12cd> *)&v);
}

template void _Construct<ProductionPrerequisite::PrereqUnitRec, ProductionPrerequisite::PrereqUnitRec>(ProductionPrerequisite::PrereqUnitRec *, const ProductionPrerequisite::PrereqUnitRec &);
}
