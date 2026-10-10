// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

class W3DAnimationInfo;

namespace _STL
{
struct random_access_iterator_tag {};

template <class In, class Out, class Distance>
Out __copy(In, In, Out, const random_access_iterator_tag &, Distance *);

class W3DAnimationInfoCopyShim
{
public:
    static W3DAnimationInfo *copy(W3DAnimationInfo *first, W3DAnimationInfo *last, W3DAnimationInfo *result, const random_access_iterator_tag &, int *n);
};

template <class In, class Out, class Distance>
Out __copy(In first, In last, Out result, const random_access_iterator_tag &tag, Distance *n)
{
    return (Out)W3DAnimationInfoCopyShim::copy((W3DAnimationInfo *)first, (W3DAnimationInfo *)last, (W3DAnimationInfo *)result, tag, (int *)n);
}

template W3DAnimationInfo *__copy<W3DAnimationInfo *, W3DAnimationInfo *, int>(W3DAnimationInfo *, W3DAnimationInfo *, W3DAnimationInfo *, const random_access_iterator_tag &, int *);
}
