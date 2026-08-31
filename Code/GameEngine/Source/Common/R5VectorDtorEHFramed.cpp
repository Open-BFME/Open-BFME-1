// cl: -GX
// stlport
//
// Open-BFME5: eight STLport vector<T> destructors WITH the exception frame
// that R4VectorDtorWideElems.cpp's `-GX-` removes.  Same source shape, same
// two axes -- element stride and element destructor -- and the only
// difference between the two files is the flag.
//
// vector derives from _Vector_base, whose deallocation is the unwind action
// if an element destructor throws, so with EH ON the body carries the three
// push fs:[0] frame and two EH-state stores: 0 across the destroy loop and
// -1 once the elements are gone and only the buffer is left to free.  That
// pairing is the whole difference; nothing about the source changes.
//
// THE FLAG LINE HERE IS THE WHOLE FLAG LIST, NOT AN ADDITION TO A DEFAULT.
// Spelling it `/DNDEBUG /MD /EHsc` instead compiles the same source against
// the DLL CRT, and STLport then routes the deallocation through an imported
// operator delete -- one indirect call in place of retail's `cmp eax,0x80`
// dispatch between operator delete and the node allocator.  Same C++, a
// different allocator, and 40 bytes of difference.
//
// The 0x1F0 body at 0x006073F0 is the one the ModelConditionSoundSelector
// thunk TU reaches, through the ILT slot at 0x000241AE under that module's
// member-class name; the body itself is the vector destructor and is claimed
// as one here.
//
// IDENTITY IS NOT RECOVERED.  Each element type is named for its destructor's
// ILT slot, and `char m_body[SIZE]` carries the stride and nothing else.

#include <vector>

#define R5_EH_ELEM( T, SZ )                                                   \
	struct T                                                                  \
	{                                                                         \
		char m_body[ SZ ];                                                    \
		T();                                                                  \
		T( const T & );                                                       \
		~T();                                                                 \
		T &operator=( const T & );                                            \
	};                                                                        \
	template class _STL::vector<T >;
R5_EH_ELEM( Gen0004A1C4, 0xBC )		// 171B at 0x0013BFA0
R5_EH_ELEM( Gen0002306F, 0x128 )		// 171B at 0x0013C640
R5_EH_ELEM( Gen00043699, 0x88 )		// 169B at 0x0039EA90
R5_EH_ELEM( Gen000075EF, 0x1F0 )		// 171B at 0x006073F0
R5_EH_ELEM( Gen00034158, 0x210 )		// 169B at 0x00608C60
R5_EH_ELEM( Gen00026F35, 0x78 )		// 165B at 0x006A3930
R5_EH_ELEM( Gen0002A8BA, 0x2C )		// 163B at 0x00774130
R5_EH_ELEM( Gen001439F0, 0x24 )		// 166B at 0x001439F0, element dtor ILT 0x0003B8FE

template class _STL::vector<_STL::vector<int> >;

struct BfmeDtorMemberBElement
{
	char *m_begin;
	char *m_end;
	char *m_capacity;

	~BfmeDtorMemberBElement()
	{
		const unsigned int allocation_size = m_capacity - m_begin;
		if (m_begin != 0) {
			_STL::allocator<char>().deallocate(m_begin, allocation_size);
		}
	}
};

template class _STL::vector<BfmeDtorMemberBElement>;
