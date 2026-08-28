// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/prim_anim.h
class PrimitiveAnimationChannelClass
{
public:
    const PrimitiveAnimationChannelClass<T> &operator=(const PrimitiveAnimationChannelClass<T> &);
};

class PrimitiveAnimationChannelFloatAssignShim
{
public:
    const PrimitiveAnimationChannelFloatAssignShim &assign(const PrimitiveAnimationChannelFloatAssignShim &);
};

template <class T>
const PrimitiveAnimationChannelClass<T> &PrimitiveAnimationChannelClass<T>::operator=(
    const PrimitiveAnimationChannelClass<T> &other)
{
    return *(const PrimitiveAnimationChannelClass<T> *)
        &((PrimitiveAnimationChannelFloatAssignShim *)this)->assign(
            *(const PrimitiveAnimationChannelFloatAssignShim *)&other);
}

template const PrimitiveAnimationChannelClass<float> &PrimitiveAnimationChannelClass<float>::operator=(
    const PrimitiveAnimationChannelClass<float> &);
