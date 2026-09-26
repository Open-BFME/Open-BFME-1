// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

class AsciiString;

namespace _STL
{
struct random_access_iterator_tag {};

template <class In, class Out, class Distance>
Out __copy(In, In, Out, const random_access_iterator_tag &, Distance *);

class AsciiStringCopyShim
{
public:
    static AsciiString *copy(AsciiString *first, AsciiString *last, AsciiString *result, const random_access_iterator_tag &, int *n);
};

template <class In, class Out, class Distance>
Out __copy(In first, In last, Out result, const random_access_iterator_tag &tag, Distance *n)
{
    return (Out)AsciiStringCopyShim::copy((AsciiString *)first, (AsciiString *)last, (AsciiString *)result, tag, (int *)n);
}

template AsciiString *__copy<AsciiString *, AsciiString *, int>(AsciiString *, AsciiString *, AsciiString *, const random_access_iterator_tag &, int *);
}
