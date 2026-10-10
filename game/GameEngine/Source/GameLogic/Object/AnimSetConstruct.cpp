// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

namespace GenericObjectCreationNugget
{
struct AnimSet;
}

struct Gen_t_00754b20_k4;
struct Gen_t_00754b20_p12cd;

namespace _STL
{
template <class First, class Second> struct pair;

template <class T, class U>
void _Construct(T *, const U &);

// The full retail ILT at 0x0000DDAF jumps to the existing _Construct
// specialization at 0x00754B20: two caller-owned pointer slots, cdecl.
template <>
void _Construct<pair<const Gen_t_00754b20_k4, Gen_t_00754b20_p12cd>,
    pair<const Gen_t_00754b20_k4, Gen_t_00754b20_p12cd> >(
    pair<const Gen_t_00754b20_k4, Gen_t_00754b20_p12cd> *,
    const pair<const Gen_t_00754b20_k4, Gen_t_00754b20_p12cd> &);

template <class T, class U>
void _Construct(T *p, const U &v)
{
    _Construct((pair<const Gen_t_00754b20_k4, Gen_t_00754b20_p12cd> *)p,
        *(const pair<const Gen_t_00754b20_k4, Gen_t_00754b20_p12cd> *)&v);
}

template void _Construct<GenericObjectCreationNugget::AnimSet, GenericObjectCreationNugget::AnimSet>(GenericObjectCreationNugget::AnimSet *, const GenericObjectCreationNugget::AnimSet &);
}
