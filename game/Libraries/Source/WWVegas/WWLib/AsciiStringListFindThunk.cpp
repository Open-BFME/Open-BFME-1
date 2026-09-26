// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

class AsciiString;

namespace _STL
{
    template <class T>
    struct _Nonconst_traits;

    template <class T, class Traits>
    struct _List_iterator
    {
    };

    struct input_iterator_tag;

    template <class Iterator, class T>
    Iterator __bfme_find_impl(Iterator, Iterator, const T &, const input_iterator_tag &);

    template <class Iterator, class T>
    Iterator __find(Iterator first, Iterator last, const T &value, const input_iterator_tag &tag)
    {
		return __bfme_find_impl(first, last, value, tag);
    }

    template _List_iterator<AsciiString, _Nonconst_traits<AsciiString> > __find<_List_iterator<AsciiString, _Nonconst_traits<AsciiString> >, AsciiString>(_List_iterator<AsciiString, _Nonconst_traits<AsciiString> >, _List_iterator<AsciiString, _Nonconst_traits<AsciiString> >, const AsciiString &, const input_iterator_tag &);
}
