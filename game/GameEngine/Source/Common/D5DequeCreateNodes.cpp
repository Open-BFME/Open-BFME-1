// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: sixteen copies of STLport's _Deque_base<T>::_M_create_nodes,
// found by byte signature -- 43-byte dumps opening
// `56 8b 74 24 08 57 8b 7c 24 10`. Each carried nothing but machine bytes.
//
// The function walks the map between two node pointers and hangs one buffer off
// each. STLport sizes that buffer at 128 bytes or one element, whichever is
// larger, and because the size is a compile-time constant the allocator's own
// small/large branch folds away: the six bodies whose element divides into 128
// call the node pool with 0x80, the ten wider ones call the block allocator with
// the element size itself. That constant is the only axis and it is the only
// immediate in each body.
//
// Identity is not recovered. The 0x80 bodies only prove their element divides
// 128, so they are modelled four bytes wide; the wider ones take the size their
// own immediate names. Both are named for the address of the row they serve.

namespace _STL
{
void *__cdecl nodeAllocate(unsigned int bytes);
void *__cdecl blockAllocate(unsigned int bytes);

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class _Deque_base
{
protected:
	void _M_create_nodes( Type **start, Type **finish );
};

template <class Type, class Allocator>
void _Deque_base<Type, Allocator>::_M_create_nodes( Type **start, Type **finish )
{
	const unsigned int count = sizeof( Type ) < 128 ? 128 / sizeof( Type ) : 1;
	const unsigned int bytes = count * sizeof( Type );

	for ( Type **cur = start; cur < finish; ++cur )
	{
		if ( bytes > 128 )
			*cur = (Type *)blockAllocate( bytes );
		else
			*cur = (Type *)nodeAllocate( bytes );
	}
}

struct D5Elem00088020 { char m_body[ 0x4 ]; };
struct D5Elem00351D80 { char m_body[ 0x4 ]; };
struct D5Elem00351E00 { char m_body[ 0x4 ]; };
struct D5Elem00352230 { char m_body[ 0x4 ]; };
struct D5Elem003522B0 { char m_body[ 0x4 ]; };
struct D5Elem00368120 { char m_body[ 0x4 ]; };
struct D5Elem0063B4F0 { char m_body[ 0x2B8 ]; };
struct D5Elem0063B570 { char m_body[ 0x864 ]; };
struct D5Elem006404F0 { char m_body[ 0x4 ]; };
struct D5Elem006444D0 { char m_body[ 0x194 ]; };
struct D5Elem00644550 { char m_body[ 0x330 ]; };
struct D5Elem006445D0 { char m_body[ 0x4 ]; };
struct D5Elem00652710 { char m_body[ 0x210 ]; };
struct D5Elem00652790 { char m_body[ 0x1F0 ]; };
struct D5Elem00698AD0 { char m_body[ 0x4 ]; };
struct D5Elem009ED110 { char m_body[ 0x4 ]; };

template class _Deque_base<D5Elem00088020, allocator<D5Elem00088020> >;
template class _Deque_base<D5Elem00351D80, allocator<D5Elem00351D80> >;
template class _Deque_base<D5Elem00351E00, allocator<D5Elem00351E00> >;
template class _Deque_base<D5Elem00352230, allocator<D5Elem00352230> >;
template class _Deque_base<D5Elem003522B0, allocator<D5Elem003522B0> >;
template class _Deque_base<D5Elem00368120, allocator<D5Elem00368120> >;
template class _Deque_base<D5Elem0063B4F0, allocator<D5Elem0063B4F0> >;
template class _Deque_base<D5Elem0063B570, allocator<D5Elem0063B570> >;
template class _Deque_base<D5Elem006404F0, allocator<D5Elem006404F0> >;
template class _Deque_base<D5Elem006444D0, allocator<D5Elem006444D0> >;
template class _Deque_base<D5Elem00644550, allocator<D5Elem00644550> >;
template class _Deque_base<D5Elem006445D0, allocator<D5Elem006445D0> >;
template class _Deque_base<D5Elem00652710, allocator<D5Elem00652710> >;
template class _Deque_base<D5Elem00652790, allocator<D5Elem00652790> >;
template class _Deque_base<D5Elem00698AD0, allocator<D5Elem00698AD0> >;
template class _Deque_base<D5Elem009ED110, allocator<D5Elem009ED110> >;
}
