// Twenty-three bodies that move ONE pointer between a held object and a field
// of another object, guarding on null.  They share this file because they
// share their layout: the field displacement in every one of them is drawn
// from the same two runs -- 0x3C/0x40/0x44/0x48/0x54 and
// 0xA0/0xA4/0xA8/0xAC/0xB0/0xB4/0xB8/0xBC -- that the null-checked forwarders
// in T1NullCheckedSlotTwoLookups.cpp read from, and the forwarded method is
// the same slot-2, one-argument virtual.
//
// SHAPE A -- 37 bytes, ten rows, WRITE INTO the field:
//
//     mov eax,[ecx] / test eax,eax / je null
//     lea ecx,[eax+0x14] / mov eax,[ecx] / call dword ptr [eax]
//     mov ecx,[esp+4] / mov [ecx+<OFF>],eax / ret 4
//     null: mov edx,[esp+4] / mov [edx+<OFF>],0 / ret 4
//
// SHAPE B -- 38 or 41 bytes, thirteen rows, READ OUT OF the field:
//
//     mov eax,[esp+8] / push esi / mov esi,ecx
//     mov ecx,[eax+<OFF>] / test ecx,ecx / je null
//     mov eax,[esp+8] / mov edx,[ecx] / push eax / call dword ptr [edx+8]
//     mov [esi],eax / pop esi / ret 8
//     null: xor eax,eax / mov [esi],eax / pop esi / ret 8
//
// WHAT SHAPE A SHOWS.  __thiscall, one dword parameter, no return value: the
// result of the call is not left in eax for a caller, it is stored through the
// parameter.  The receiver contributes exactly one dword, at offset 0, and it
// is a pointer -- null-checked, and on the non-null path advanced by a BARE
// `lea ecx,[eax+0x14]` with no second null test.  An unguarded adjustment
// inside a proven-non-null branch is a base-class upcast, not a pointer
// arithmetic expression the source wrote; +0x14 makes the pointee a class
// whose first subobject is 0x14 wide (a vptr and four dwords) with a second
// polymorphic base behind it.  `call [eax]` with nothing pushed is SLOT 0 of
// that second base, taking no arguments and returning the dword that gets
// stored.
//
// BOTH ARMS STORE, AND EACH RELOADS THE PARAMETER.  A single assignment fed by
// a conditional value would compute into one register and store once; two
// stores through two separately-reloaded copies of the same parameter is what
// a source with an assignment in EACH arm compiles to.  The null arm stores an
// immediate zero, so the else-arm value is a literal and not a second call.
//
// WHAT SHAPE B SHOWS.  __thiscall, TWO dword parameters.  The second parameter
// is dereferenced at the same <OFF> to get the pointer; the FIRST is re-pushed
// untouched as the single argument of the slot-2 virtual, and the result is
// stored at offset 0 of the receiver.  The null arm's zero goes through EAX
// (`xor eax,eax / mov [esi],eax`) rather than being stored as an immediate --
// that is the tell that separates it from shape A.  A value that reaches the
// store in a register in BOTH arms is one assignment fed by a conditional
// expression, with MSVC 7.1 duplicating the store and epilogue into each arm;
// spelling it as shape A's two assignments emits `mov dword ptr [esi],0` and
// misses by four bytes.
//
// IN BOTH SHAPES THE POINTER MUST BE NAMED IN A LOCAL.  Dereferencing the
// member twice in one expression makes MSVC 7.1 re-load it and shuffle
// registers; binding it once reproduces retail.  Same tell as the forwarder
// family next door, and for the same reason.
//
// SHAPE A HAS ONLY FIVE DISTINCT BODIES ACROSS ITS TEN ROWS -- 0x005C3FE0 and
// 0x005C5510 are byte-identical, as are 0x005C4070/0x005C56C0,
// 0x005C40A0/0x005C57A0, 0x005C40D0/0x005C5840 and 0x005C4270/0x005C5B20.
// Ten addresses is ten COMDATs, so they are ten functions: the same duplicate-
// translation-unit pattern the vtable-setter and range-loop families show.
// Each row therefore gets its own classes rather than being aliased.
//
// IDENTITY IS NOT RECOVERED.  No string, RTTI walk or known vftable reaches
// any of these bodies; every name is derived from the row's address.  The
// interfaces are shared declarations because nothing distinguishes them
// row-to-row -- only the field displacement varies, and that lives in the
// per-row class.

class T1SlotTwoTarget
{
public:
	virtual void s0();
	virtual void s1();
	virtual void *s2( void *a );
};

// The held object of shape A: 0x14 of first subobject, then a polymorphic
// second base whose slot 0 yields the pointer.

class T1SourceHead
{
public:
	virtual void h0();

	int m_pad[ 4 ];
};

class T1SourceTail
{
public:
	virtual T1SlotTwoTarget *g0();
};

class T1Source : public T1SourceHead, public T1SourceTail
{
};

// ------------------------------------------------------- shape A, write into

#define T1_CACHE_STORE( ROW, OFFSET )                                         \
	class T1Field_##ROW                                                       \
	{                                                                         \
	public:                                                                   \
		char m_pad[ OFFSET ];                                                 \
		T1SlotTwoTarget *m_target;                                            \
	};                                                                        \
	class T1Store_##ROW                                                       \
	{                                                                         \
	public:                                                                   \
		void fill( T1Field_##ROW *f );                                        \
                                                                              \
		T1Source *m_source;                                                   \
	};                                                                        \
	void T1Store_##ROW::fill( T1Field_##ROW *f )                              \
	{                                                                         \
		T1Source *source = m_source;                                          \
		if ( source )                                                         \
		{                                                                     \
			f->m_target = source->g0();                                       \
		}                                                                     \
		else                                                                  \
		{                                                                     \
			f->m_target = 0;                                                  \
		}                                                                     \
	}

T1_CACHE_STORE( 005C3FE0, 0x3c )
T1_CACHE_STORE( 005C4070, 0x40 )
T1_CACHE_STORE( 005C40A0, 0x44 )
T1_CACHE_STORE( 005C40D0, 0x48 )
T1_CACHE_STORE( 005C4270, 0x54 )
T1_CACHE_STORE( 005C5510, 0x3c )
T1_CACHE_STORE( 005C56C0, 0x40 )
T1_CACHE_STORE( 005C57A0, 0x44 )
T1_CACHE_STORE( 005C5840, 0x48 )
T1_CACHE_STORE( 005C5B20, 0x54 )

// ------------------------------------------------------- shape B, read out of

#define T1_CACHE_LOAD( ROW, OFFSET )                                          \
	class T1LoadField_##ROW                                                   \
	{                                                                         \
	public:                                                                   \
		char m_pad[ OFFSET ];                                                 \
		T1SlotTwoTarget *m_target;                                            \
	};                                                                        \
	class T1Load_##ROW                                                        \
	{                                                                         \
	public:                                                                   \
		void set( void *a, T1LoadField_##ROW *f );                            \
                                                                              \
		void *m_result;                                                       \
	};                                                                        \
	void T1Load_##ROW::set( void *a, T1LoadField_##ROW *f )                   \
	{                                                                         \
		T1SlotTwoTarget *target = f->m_target;                                \
		m_result = target ? target->s2( a ) : 0;                              \
	}

T1_CACHE_LOAD( 005C5480, 0x3c )
T1_CACHE_LOAD( 005C5540, 0xa0 )
T1_CACHE_LOAD( 005C5690, 0x40 )
T1_CACHE_LOAD( 005C56F0, 0xa4 )
T1_CACHE_LOAD( 005C5730, 0x44 )
T1_CACHE_LOAD( 005C57D0, 0xa8 )
T1_CACHE_LOAD( 005C5810, 0x48 )
T1_CACHE_LOAD( 005C5870, 0xac )
T1_CACHE_LOAD( 005C58B0, 0xb0 )
T1_CACHE_LOAD( 005C59C0, 0xb4 )
T1_CACHE_LOAD( 005C5AB0, 0xb8 )
T1_CACHE_LOAD( 005C5AF0, 0x54 )
T1_CACHE_LOAD( 005C5B50, 0xbc )
