// Five 56-byte broadcast loops: notify one optional held item, then notify
// every element of a begin/end pointer pair.  Retail, the offset-0 variant:
//
//     push ebx / mov ebx,[esp+8] / push esi / push edi / mov edi,ecx
//     mov ecx,[edi+<K>] / test ecx,ecx / je skip
//     mov eax,[ecx] / push ebx / call dword ptr [eax+0xC]
//     skip: mov esi,[edi+<K>+4] / cmp esi,[edi+<K>+8] / je done
//     loop: mov ecx,[esi] / mov edx,[ecx] / push ebx
//           call dword ptr [edx+0xC]
//           mov eax,[edi+<K>+8] / add esi,4 / cmp esi,eax / jne loop
//     done: pop edi / pop esi / pop ebx / ret 4
//
// WHAT THE BYTES SHOW.  `this` in ecx, one dword argument, `ret 4`:
// __thiscall.  Three consecutive members are read: a single pointer, then a
// pair that is compared to each other and walked forward four bytes at a time
// until they meet -- the STL-vector begin/end layout minus the capacity field,
// exactly as VectorNotifyLoops.cpp reads it two thousand bytes earlier in the
// same drawer.  The lone pointer is null-checked, the elements are not; both
// dispatch SLOT 3 of a polymorphic type and both are handed the same argument,
// loaded once into ebx before anything and re-pushed each time.  So the source
// is an optional first recipient followed by a container of the same
// interface -- the same broadcast, written twice.
//
// THE END POINTER IS RELOADED from [edi+K+8] on every iteration.  That is the
// compiler conceding the virtual call may modify the container, which it must
// assume for a member read through `this` across an opaque call; a local copy
// in the source would have been hoisted out.
//
// THE HELD POINTER MUST BE NAMED IN A LOCAL.  Written as
// `if ( m_first ) m_first->notify( a );` MSVC 7.1 loads it into EAX, tests
// eax, and copies to ecx -- `mov eax,[edi+4] / test eax,eax / je +8 /
// mov ecx,eax` where retail has `mov ecx,[edi+4] / test ecx,ecx / je +6`.
// Binding it once reproduces retail.  The same tell governs the null-checked
// forwarders and the cached accessors in this range; at offset 0 the two
// spellings happen to converge, so only the padded rows witness it.
//
// K IS THE ONLY OTHER AXIS: 0 for three rows, 4 for one, 8 for one.  The
// two-byte `mov edi,edi` versus three-byte `lea ecx,[ecx]` filler before the
// loop is not a source difference -- it is MSVC aligning the loop head to a
// 16-byte boundary within the COMDAT, and it falls out of K automatically.
//
// SEPARATE FUNCTIONS, NOT ALIASES: five addresses, five COMDATs.  The three
// K=0 rows are byte-identical, which is the duplicate-translation-unit pattern
// this range shows repeatedly, not evidence that they are one function.
//
// IDENTITY IS NOT RECOVERED.  Nothing names the container, the held item or
// the broadcast method; names are address-derived.

class T1NotifyItem
{
public:
	virtual void notifyPad0();
	virtual void notifyPad1();
	virtual void notifyPad2();
	virtual void notify( void *argument );
};

#define T1_HEAD_THEN_VECTOR_NOTIFY( NAME, PAD )                               \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void notifyAll( void *argument );                                     \
                                                                              \
		PAD                                                                   \
		T1NotifyItem *m_first;                                                \
		T1NotifyItem **m_begin;                                               \
		T1NotifyItem **m_end;                                                 \
	};                                                                        \
	void NAME::notifyAll( void *argument )                                    \
	{                                                                         \
		T1NotifyItem *first = m_first;                                        \
		if ( first )                                                          \
		{                                                                     \
			first->notify( argument );                                        \
		}                                                                     \
		for ( T1NotifyItem **it = m_begin; it != m_end; ++it )                \
		{                                                                     \
			( *it )->notify( argument );                                      \
		}                                                                     \
	}

T1_HEAD_THEN_VECTOR_NOTIFY( T1Broadcast_005C4140, )
T1_HEAD_THEN_VECTOR_NOTIFY( T1Broadcast_005C4220, )
T1_HEAD_THEN_VECTOR_NOTIFY( T1Broadcast_005C5930, )
T1_HEAD_THEN_VECTOR_NOTIFY( T1Broadcast_005C6D80, char m_pad[ 4 ]; )
T1_HEAD_THEN_VECTOR_NOTIFY( T1Broadcast_005C8710, char m_pad[ 8 ]; )
