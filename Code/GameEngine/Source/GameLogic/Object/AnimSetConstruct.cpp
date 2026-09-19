// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

namespace GenericObjectCreationNugget
{
struct AnimSet;
}

namespace _STL
{
template <class T, class U>
void _Construct(T *, const U &);

class AnimSetConstructShim
{
public:
    static void construct(GenericObjectCreationNugget::AnimSet *p, const GenericObjectCreationNugget::AnimSet &v);
};

template <class T, class U>
void _Construct(T *p, const U &v)
{
    AnimSetConstructShim::construct((GenericObjectCreationNugget::AnimSet *)p, *(const GenericObjectCreationNugget::AnimSet *)&v);
}

template void _Construct<GenericObjectCreationNugget::AnimSet, GenericObjectCreationNugget::AnimSet>(GenericObjectCreationNugget::AnimSet *, const GenericObjectCreationNugget::AnimSet &);
}
