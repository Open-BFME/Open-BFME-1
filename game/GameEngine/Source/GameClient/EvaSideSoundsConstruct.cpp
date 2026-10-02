// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

struct EvaSideSounds;
class PSResponse;

namespace _STL
{
template <class T, class U>
void _Construct(T *p, const U &v)
{
    _Construct((PSResponse *)p, *(const PSResponse *)&v);
}

extern template void _Construct<PSResponse, PSResponse>(PSResponse *, const PSResponse &);
template void _Construct<EvaSideSounds, EvaSideSounds>(EvaSideSounds *, const EvaSideSounds &);
}
