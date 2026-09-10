// ?find_last_not_of@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QBEIPBDII@Z
// partial score=0.95 date=2026-09-10
// cl: /O2 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<char>::find_last_not_of(const char*, size_type,
// size_type).  Retail body: 0x00654BE0, 127 bytes.  The named
// parsePlayerKVPairs caller at 0x00659670 invokes this overload with the
// numeric-character set and the second-marker position; the retail prologue
// and reverse predicate are the same vendor algorithm.

#include <string>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

namespace _STL
{

template <>
basic_string<char, char_traits<char>, allocator<char> >::size_type
basic_string<char, char_traits<char>, allocator<char> >::find_last_not_of(
	const char *s, size_type pos, size_type n) const
{
	typedef char CharType;
	const size_type len = size();

	if (len < 1)
	{
		_ReadWriteBarrier();
		return npos;
	}
	else
	{
		const_iterator last = begin() + (min)(len - 1, pos) + 1;
		const_reverse_iterator rlast = const_reverse_iterator(last);
		const_reverse_iterator result =
			_STLP_STD::find_if(rlast, rend(),
				_Not_within_traits<char_traits<char> >(
					(const CharType *)s, (const CharType *)s + n));
		return result != rend() ? (result.base() - 1) - begin() : npos;
	}
}

}
