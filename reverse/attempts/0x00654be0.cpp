// ?find_last_of@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QBEIPBDII@Z
// partial score=0.78 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: STLport basic_string<char> search and substring members.

#include <string>

namespace _STL
{
template <>
basic_string<char, char_traits<char>, allocator<char> >
basic_string<char, char_traits<char>, allocator<char> >::substr(size_type position,
	size_type count) const
{
	const size_type length = (min)(count, size() - position);
	return basic_string<char, char_traits<char>, allocator<char> >(
		this->_M_start + position, this->_M_start + position + length);
}
}

template class _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >;
