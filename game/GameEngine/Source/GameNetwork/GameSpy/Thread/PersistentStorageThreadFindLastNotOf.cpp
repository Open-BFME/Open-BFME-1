// cl: /O2 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<char>::find_last_not_of specialization used by
// GameSpyPSMessageQueueInterface::parsePlayerKVPairs.

#include <string>

extern "C" void _WriteBarrier(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_WriteBarrier)
#pragma intrinsic(_ReadWriteBarrier)

namespace _STL
{

static __forceinline unsigned int BfmeFindLastNotOfNpos()
{
	_WriteBarrier();
	return ~0U;
}

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

	const_iterator last = begin() + (min)(len - 1, pos) + 1;
	const_reverse_iterator rlast = const_reverse_iterator(last);
	const_reverse_iterator result = _STLP_STD::find_if(rlast, rend(),
			_Not_within_traits<char_traits<char> >(
				(const CharType *)s, (const CharType *)s + n));

	return result != rend()
		? (result.base() - 1) - begin()
		: BfmeFindLastNotOfNpos();
}

}
