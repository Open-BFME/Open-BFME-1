// stlport
// cl: /EHs-c-

#include <algorithm>
#include <vector>

// Compare a range of packed boolean values with a second packed range.
// ?bfmeBitIteratorEqual@@YA_NU?$_Bit_iter@_NPB_N@_STL@@00@Z
bool bfmeBitIteratorEqual(
	_STL::_Bit_const_iterator first,
	_STL::_Bit_const_iterator last,
	_STL::_Bit_const_iterator other)
{
	return _STL::equal(first, last, other);
}

// Compare two complete packed-boolean ranges.
// ?bfmeBitVectorEqual@@YA_NABV?$vector@_NV?$allocator@_N@_STL@@@_STL@@0@Z
bool bfmeBitVectorEqual(
	const _STL::vector<bool> &first,
	const _STL::vector<bool> &second)
{
	return first.size() == second.size() &&
		bfmeBitIteratorEqual(first.begin(), first.end(), second.begin());
}
