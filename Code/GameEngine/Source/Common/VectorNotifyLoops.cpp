// The four byte-identical 40-byte loops at 0x005C0830, 0x005C08F0, 0x005C2690
// and 0x005C2760 -- the same drawer that holds NullCheckedForwarders.cpp and
// ReleasingAssigners.cpp.
//
//     push esi / push edi / mov edi,ecx / mov esi,[edi] / cmp esi,[edi+4]
//     je done / push ebx / mov ebx,[esp+0x10]
//     loop: mov ecx,[esi] / mov eax,[ecx] / push ebx / call dword ptr [eax+0xC]
//           mov eax,[edi+4] / add esi,4 / cmp esi,eax / jne loop
//     pop ebx / done: pop edi / pop esi / ret 4
//
// WHAT THE BYTES SHOW.  `this` in ecx, one dword argument, `ret 4`: __thiscall.
// The class's first two members are read as a pair and compared to each other,
// and the first is walked forward four bytes at a time until it equals the
// second -- a begin/end pointer pair over an array of dwords, which is the
// STL-vector layout minus the capacity field this body never touches.  Each
// element is dereferenced once for its vftable and once for the call, so the
// elements are pointers to a polymorphic type and the call is slot 3.  The
// argument is loaded once, before the loop, and re-pushed on every iteration:
// every element gets the same value.
//
// The end pointer is RELOADED from [edi+4] inside the loop rather than kept in a
// register.  That is not a missed optimisation -- it is the compiler conceding
// that the virtual call may modify the container, which is exactly what it must
// assume for a member read through `this` across an opaque call.  A local copy
// of the end pointer in the source would have been hoisted; the member access
// written directly in the loop condition produces this reload.
//
// `push ebx` sits INSIDE the non-empty branch and `pop ebx` immediately before
// the shared epilogue, so the empty-container path never saves it: /O2 shrink
// wrapping, which needs no help from the source.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Four distinct addresses; four broadcast
// helpers over four element interfaces that coincide because the dispatched slot
// and the argument count coincide.  Nothing here defeats inlining, so there is
// no per-translation-unit COMDAT reading to justify asserting they are one.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names the container or the
// broadcast method, so the names are address-derived.

class NotifyItem
{
public:
	virtual void notifyPad0();
	virtual void notifyPad1();
	virtual void notifyPad2();
	virtual void notify( void *argument );
};

#define BFME_VECTOR_NOTIFY_LOOP( NAME )                                       \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void notifyAll( void *argument );                                     \
                                                                              \
		NotifyItem **m_begin;                                                 \
		NotifyItem **m_end;                                                   \
	};                                                                        \
	void NAME::notifyAll( void *argument )                                    \
	{                                                                         \
		for ( NotifyItem **it = m_begin; it != m_end; ++it )                  \
		{                                                                     \
			( *it )->notify( argument );                                      \
		}                                                                     \
	}

BFME_VECTOR_NOTIFY_LOOP( Rva005C0830List )
BFME_VECTOR_NOTIFY_LOOP( Rva005C08F0List )
BFME_VECTOR_NOTIFY_LOOP( Rva005C2690List )
BFME_VECTOR_NOTIFY_LOOP( Rva005C2760List )

// Retail 0x005C2660: a separate opaque vector loop that dispatches slot 1.
// Its only recovered identity evidence is the address and the ILT at
// 0x00034A18, so the type and method retain the address token.
class Rva005C2660Item
{
public:
	virtual void slot00();
	virtual void slot01();
};

class Rva005C2660List
{
public:
	void dispatchAll();

	Rva005C2660Item **m_begin;
	Rva005C2660Item **m_end;
};

void Rva005C2660List::dispatchAll()
{
	for (Rva005C2660Item **it = m_begin; it != m_end; ++it)
	{
		(*it)->slot01();
	}
}
