// cl: /DNDEBUG /MD /EHsc
// Four 155-byte __thiscall destructors, all four byte-identical except for
// their EH-data DIR32 site and their two REL32 displacements: destroy every
// element a pointer vector owns, then release the block.  Retail:
//
//     push -1 / push <ehdata> / fs:[0] frame
//     edi = this ; [esp+8] = this
//     esi = [edi] ; cmp esi,[edi+4] ; EH state 0 ; je skip
//     loop: ecx = [esi] ; if (ecx) { eax=[ecx]; push 1; call [eax] }
//           esi += 4 ; cmp esi,[edi+4] ; jne loop        ; end RELOADED
//     skip: ecx = [edi] ; EH state -1 ; if (!ecx) return
//           eax = ((([edi+8] - ecx) >> 2) << 2)
//           if (eax > 0x80) { push ecx; call <operator delete> }
//           else            { push eax; push ecx; call <_M_deallocate> }
//
// WHAT THE BYTES SHOW.  `this` in ecx, plain `ret` with no count and no
// argument read: a destructor, not a deleting destructor -- no flag is tested
// and nothing frees `this`.
//
// THREE POINTERS AT 0, 4 AND 8, and the classic begin/end/capacity triple: 0
// and 4 drive the loop, 0 and 8 give the byte size.  The size is computed by
// dividing the pointer difference by four and multiplying it straight back,
// which is a POINTER SUBTRACTION scaled to bytes -- the element is four bytes
// wide and the capacity is a pointer, not a stored count.  The `0x80` split
// with one pushed dword on one arm and two on the other is STLport's
// `__node_alloc::deallocate` inlined at its own `_MAX_BYTES`, exactly as
// BigBlockReleases.cpp spells it; both callees are already-named ledger rows
// and need no pin.
//
// EACH ELEMENT IS `delete`d: null test, vftable load, `push 1`, `call [eax]`.
// That flag protocol is the MSVC scalar deleting destructor and nothing else
// emits it, so the element type declares a virtual destructor.  The END
// POINTER IS RELOADED every iteration -- the compiler conceding that an opaque
// virtual destructor may have touched the member.
//
// THE EH STATE IS WHAT SPLITS THIS INTO TWO CLASSES.  State 0 is entered
// before the loop and left at -1 before the release, so an exception thrown
// out of an element's destructor must unwind something whose action is the
// release itself.  A destructor body that runs at state 0 and whose state
// falls to -1 exactly where an INLINED destructor begins is a derived
// destructor followed by its base's: the three pointers and the release belong
// to a BASE whose destructor is inline, and the element loop is the derived
// class's own body.  Spelling the release inside the same destructor instead
// produces no state transition at all.
//
// ONE AXIS, AND IT IS EMPTY: the four rows differ only in where they sit.
// Four addresses, four COMDATs; byte-identical bodies in this drawer are the
// duplicate-translation-unit pattern, not evidence of one function.
//
// IDENTITY IS NOT RECOVERED.  Nothing names the element interface; every name
// here is derived from an address.

#include <new>

namespace _STL
{

template <bool __threads, int __inst>
class __node_alloc
{
	static void _M_deallocate( void *p, unsigned int n );

public:
	static void deallocate( void *p, unsigned int n )
	{
		if ( n > 128 )
			::operator delete( p );
		else
			_M_deallocate( p, n );
	}
};

}

class Y3OwnedElem
{
public:
	virtual ~Y3OwnedElem();
};

class Y3OwningVectorBase
{
public:
	~Y3OwningVectorBase()
	{
		if ( m_start )
			_STL::__node_alloc< true, 0 >::deallocate(
				m_start, ( m_cap - m_start ) * sizeof( Y3OwnedElem * ) );
	}

	Y3OwnedElem **m_start;
	Y3OwnedElem **m_finish;
	Y3OwnedElem **m_cap;
};

#define Y3_OWNING_VECTOR_DTOR( NAME )                                         \
	class NAME : public Y3OwningVectorBase                                    \
	{                                                                         \
	public:                                                                   \
		~NAME();                                                              \
	};                                                                        \
	NAME::~NAME()                                                             \
	{                                                                         \
		for ( Y3OwnedElem **it = m_start; it != m_finish; ++it )              \
			delete *it;                                                       \
	}

Y3_OWNING_VECTOR_DTOR( Rva005C67C0 )
Y3_OWNING_VECTOR_DTOR( Rva005C6890 )
Y3_OWNING_VECTOR_DTOR( Rva005C6970 )
Y3_OWNING_VECTOR_DTOR( Rva005C6A40 )
