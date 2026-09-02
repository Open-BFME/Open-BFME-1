// ?find@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QBEIDI@Z
// partial score=0.82 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: STLport basic_string<char>::find(char, size_type).

#include <string>

namespace _STL
{
template <>
basic_string<char, char_traits<char>, allocator<char> >::size_type
basic_string<char, char_traits<char>, allocator<char> >::find(char value,
	size_type position) const
{
	if (position >= size())
		return npos;

	const_pointer result = _STL::find_if((const char *)this->_M_start + position,
		(const char *)this->_M_finish, _Eq_char_bound<char_traits<char> >(value));
	if (result != this->_M_finish)
		return result - this->_M_start;
	return npos;
}
}

template class _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >;
