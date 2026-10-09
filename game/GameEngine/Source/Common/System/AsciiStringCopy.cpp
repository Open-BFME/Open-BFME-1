// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

class AsciiString;

// The retail thunk targets the matched 12-byte node copier at 0x006FA270.
struct GenNode_006fa270;
GenNode_006fa270 *gen_copy_006fa270(GenNode_006fa270 *first,
    GenNode_006fa270 *last, GenNode_006fa270 *result);

namespace _STL
{
struct random_access_iterator_tag {};

template <class In, class Out, class Distance>
Out __copy(In, In, Out, const random_access_iterator_tag &, Distance *);

template <class In, class Out, class Distance>
Out __copy(In first, In last, Out result, const random_access_iterator_tag &tag, Distance *n)
{
    // Keep the five-slot cdecl tail-call shape. The target reads only the
    // first three slots; iterator tag and distance remain caller-owned.
    typedef GenNode_006fa270 *(__cdecl *RetailCopyCall)(GenNode_006fa270 *,
        GenNode_006fa270 *, GenNode_006fa270 *,
        const random_access_iterator_tag &, int *);
    return (Out)((RetailCopyCall)gen_copy_006fa270)((GenNode_006fa270 *)first,
        (GenNode_006fa270 *)last, (GenNode_006fa270 *)result, tag, (int *)n);
}

template AsciiString *__copy<AsciiString *, AsciiString *, int>(AsciiString *, AsciiString *, AsciiString *, const random_access_iterator_tag &, int *);
}
