// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

template <class T>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/prim_anim.h
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
