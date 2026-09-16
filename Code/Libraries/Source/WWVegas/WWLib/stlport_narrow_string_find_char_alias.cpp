// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the second retail copy of STLport basic_string<char>::find(char,
// size_type), at 0x00653990. The first copy is at 0x006542C0 in
// stlport_narrow_string_find_char.cpp and is 61 bytes, so this one takes an
// alias tag on the traits parameter to keep one name per address.
//
// Retail keeps two separate copies of the npos tail here, one reached by
// falling through the length guard and one reached by the jump the failed
// search takes. MSVC 7.1 cross-jumps two identical tails. A barrier intrinsic
// in only one arm still leaves the other jumping back into it, and the same
// intrinsic in both arms merges them again. Two DIFFERENT barrier intrinsics,
// one per arm, keep both copies, and neither emits an instruction or a
// relocation.

extern "C" void _WriteBarrier(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_WriteBarrier)
#pragma intrinsic(_ReadWriteBarrier)

#include <string>

struct Rva00653990CharTraits : public _STL::char_traits<char>
{
};

namespace _STL
{
template <>
basic_string<char, Rva00653990CharTraits, allocator<char> >::size_type
basic_string<char, Rva00653990CharTraits, allocator<char> >::find(char value,
	size_type position) const
{
	if (position >= size())
	{
		_WriteBarrier();
		return npos;
	}

	const_pointer result = _STL::find_if((const char *)this->_M_start + position,
		(const char *)this->_M_finish, _Eq_char_bound<char_traits<char> >(value));
	if (result != this->_M_finish)
		return result - this->_M_start;

	_ReadWriteBarrier();
	return npos;
}
}
