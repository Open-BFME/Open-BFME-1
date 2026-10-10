// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

class W3DAnimationInfo;

// Retail's 00610AF0 body copies 16-byte intrusive-list nodes. Its authored
// address-derived provider takes the first three cdecl argument slots.
struct GenNode_00610af0;
GenNode_00610af0 *gen_copy_00610af0(GenNode_00610af0 *first,
    GenNode_00610af0 *last, GenNode_00610af0 *result);

namespace _STL
{
struct random_access_iterator_tag {};

template <class In, class Out, class Distance>
Out __copy(In, In, Out, const random_access_iterator_tag &, Distance *);

template <class In, class Out, class Distance>
Out __copy(In first, In last, Out result, const random_access_iterator_tag &tag, Distance *n)
{
    // Retain all five incoming slots for this five-byte ILT tail jump.
    typedef GenNode_00610af0 *(__cdecl *RetailCopyCall)(GenNode_00610af0 *,
        GenNode_00610af0 *, GenNode_00610af0 *,
        const random_access_iterator_tag &, int *);
    return (Out)((RetailCopyCall)gen_copy_00610af0)((GenNode_00610af0 *)first,
        (GenNode_00610af0 *)last, (GenNode_00610af0 *)result, tag, (int *)n);
}

template W3DAnimationInfo *__copy<W3DAnimationInfo *, W3DAnimationInfo *, int>(W3DAnimationInfo *, W3DAnimationInfo *, W3DAnimationInfo *, const random_access_iterator_tag &, int *);
}
