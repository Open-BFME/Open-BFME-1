// cl: /O2 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// STLport 4.5.3 basic_string<char>::find(char, size_type), retail
// 0x006542C0, 61 bytes. parsePlayerKVPairs calls find_first_of(char, pos);
// STLport's header forwards that overload to this find body.

#include <string>

namespace _STL
{

template <>
basic_string<char, char_traits<char>, allocator<char> >::size_type
basic_string<char, char_traits<char>, allocator<char> >::find(
	char c, size_type pos) const
{
	if (pos >= size())
		return npos;
	else
	{
		const const_pointer result = _STLP_STD::find_if(
			(const char *)this->_M_start + pos,
				(const char *)this->_M_finish,
				_Eq_char_bound<char_traits<char> >(c));
		return result != this->_M_finish ? result - this->_M_start : npos;
	}
}

}
