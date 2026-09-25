// cl: /DNDEBUG /MD /EHsc /Od /Ob2 /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: STLport basic_string<char> substring constructor
// basic_string(const basic_string &, size_type pos, size_type n,
// const allocator_type &), retail 0x00830780, 218 bytes.
//
// The constructor is the vendor/stlport/stl/_string.h text, instantiated
// unchanged. It calls _String_base::_M_throw_out_of_range through ILT 0x132CD
// and the char* forward-iterator _M_range_initialize through ILT 0x2648B,
// whose body at 0x004FA6F0 is that template instance.
//
// The game's copy of that _M_range_initialize differs from pristine 4.5.3 in
// spelling only: the length is `__l - __f` rather than distance(), and the
// terminator is stored directly rather than through _M_terminate_string().
// The /Od frame shows it: MSVC keeps the temporaries of an inline attempt it
// abandons, so the callee's body sets this constructor's frame size. With
// the pristine body the frame is 0x3C; with this one it is retail's 0x30. The
// same body also reproduces the 0x14 frame of the sibling size constructor
// at 0x00830860, where pristine 4.5.3 gives 0x24. The optimised retail body
// at 0x004FA6F0 computes l - f and ends with a direct zero store.

#include <string>

namespace _STL
{

template <> template <>
inline void basic_string<char, char_traits<char>, allocator<char> >::
	_M_range_initialize<char *>(char *__f, char *__l,
		const forward_iterator_tag &)
{
	difference_type __n = __l - __f;
	this->_M_allocate_block(__n + 1);
	this->_M_finish = uninitialized_copy(__f, __l, this->_M_start);
	*this->_M_finish = 0;
}

}

// ??0?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@ABV01@IIABV?$allocator@D@1@@Z
template _STL::basic_string<char, _STL::char_traits<char>,
	_STL::allocator<char> >::basic_string(
	const _STL::basic_string<char, _STL::char_traits<char>,
		_STL::allocator<char> > &,
	unsigned, unsigned, const _STL::allocator<char> &);
