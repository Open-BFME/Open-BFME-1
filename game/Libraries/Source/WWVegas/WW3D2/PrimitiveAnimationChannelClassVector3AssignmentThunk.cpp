// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

class Vector3;

template <class T>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/prim_anim.h
class PrimitiveAnimationChannelClass
{
public:
    const PrimitiveAnimationChannelClass<T> &operator=(const PrimitiveAnimationChannelClass<T> &);
};

class PrimitiveAnimationChannelVector3AssignShim
{
public:
    const PrimitiveAnimationChannelVector3AssignShim &assign(const PrimitiveAnimationChannelVector3AssignShim &);
};

template <class T>
const PrimitiveAnimationChannelClass<T> &PrimitiveAnimationChannelClass<T>::operator=(
    const PrimitiveAnimationChannelClass<T> &other)
{
    return *(const PrimitiveAnimationChannelClass<T> *)
        &((PrimitiveAnimationChannelVector3AssignShim *)this)->assign(
            *(const PrimitiveAnimationChannelVector3AssignShim *)&other);
}

template const PrimitiveAnimationChannelClass<Vector3> &PrimitiveAnimationChannelClass<Vector3>::operator=(
    const PrimitiveAnimationChannelClass<Vector3> &);
