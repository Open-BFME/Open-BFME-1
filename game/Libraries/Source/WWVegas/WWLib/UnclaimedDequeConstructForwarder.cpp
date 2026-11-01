// cl: /DNDEBUG /MD /EHsc
// 0x009EE600 (13 bytes): an unreferenced __thiscall body alone in an
// int3-padded .text gap no ledger row covered. It reserves a one-byte
// default allocator on the stack, passes its address, and calls the
// out-of-line `_STL::deque<SightingInfo *>` allocator constructor (0x009EDFB0)
// on its own `this`, then returns:
//
//     push ecx / lea eax,[esp+3] / push eax / call deque(const allocator &) /
//     pop ecx / ret
//
// No call, ILT stub, table slot or dir32 name reaches it, so the caller's
// spelling is unknown; it is written as an in-place construction of a deque at
// offset 0 through MSVC's explicit constructor call (a placement new would add
// a null test retail lacks). IDENTITY IS NOT RECOVERED: owner and member names
// are address-derived. Only the declarations the call needs are given, so no
// STLport header is included and nothing is inlined.

class SightingInfo;

namespace _STL
{
template <class _Tp> class allocator
{
public:
	allocator() {}
};

template <class _Tp, class _Alloc> class deque
{
public:
	explicit deque(const _Alloc &__a = _Alloc());

private:
	char m_storage[0x28];
};
}

class Rva009EE600Owner
{
public:
	void construct();

private:
	_STL::deque<SightingInfo *, _STL::allocator<SightingInfo *> > m_queue;
};

// ?construct@Rva009EE600Owner@@QAEXXZ
void Rva009EE600Owner::construct()
{
	m_queue._STL::deque<SightingInfo *, _STL::allocator<SightingInfo *> >::deque();
}
