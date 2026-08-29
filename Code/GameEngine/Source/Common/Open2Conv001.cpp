// Seven small bodies recovered from byte-true dumps. Identity is NOT recovered
// for any of them: every class, member and function name here is derived from
// the address it lives at, and only the shapes below are evidence.

// ---------------------------------------------------------------------------
// 0x0050FE20 -- release a global singleton and clear the slot.
//
//     mov ecx,[GLOBAL] / test ecx,ecx / je end / mov eax,[ecx] / push 1
//     call [eax] / mov [GLOBAL],0 / end: ret
//
// `push 1` through vtable slot 0 is the scalar deleting destructor, so the type
// is complete and polymorphic and the statement is a plain `delete`. The branch
// clears the store as well as the call, which is what puts the assignment
// inside the guard; MSVC then folds `delete`'s own null test into that guard.

class Gen012F496C
{
public:
	virtual ~Gen012F496C();
};

extern Gen012F496C *TheGen012F496C;

// @?Rva0050FE20@@YAXXZ 0x0050FE20
void Rva0050FE20( void )
{
	if( TheGen012F496C )
	{
		delete TheGen012F496C;
		TheGen012F496C = 0;
	}
}

// ---------------------------------------------------------------------------
// 0x0053ACD0 -- read the first byte of a range, or -1 when it is empty.
//
//     mov eax,[ecx+4] / mov edx,[eax+4] / push esi / mov esi,[eax]
//     add edx,esi / cmp esi,edx / pop esi / je empty
//     mov ecx,[eax] / movzx eax,byte [ecx] / ret / empty: or eax,-1 / ret
//
// The end pointer is COMPUTED (`add edx,esi`) rather than stored, so the range
// is {pointer, length} and the comparison is `begin() != end()`, not
// `length != 0`. The pointer is loaded twice -- once into esi for the compare,
// once into ecx for the dereference -- which is what calling `begin()` twice
// looks like; hoisting it into a local collapses the body to 22 bytes.

class Gen0053ACD0Range
{
public:
	unsigned char *begin( void ) const { return m_data; }
	unsigned char *end( void ) const { return m_data + m_size; }
	unsigned char *m_data;
	int m_size;
};

class Gen0053ACD0
{
public:
	int peek( void ) const;
	int m_pad;
	Gen0053ACD0Range *m_range;
};

// @?peek@Gen0053ACD0@@QBEHXZ 0x0053ACD0
int Gen0053ACD0::peek( void ) const
{
	if( m_range->begin() != m_range->end() )
		return *m_range->begin();
	return -1;
}

// ---------------------------------------------------------------------------
// 0x0053C800 -- __cdecl wrapper that forwards its second argument to a member
// of its first and hands the object back.
//
//     mov eax,[esp+8] / push esi / mov esi,[esp+8] / push eax / mov ecx,esi
//     call <REL32> / mov eax,esi / pop esi / ret
//
// `ret` with no immediate makes the wrapper __cdecl; the callee takes `this`
// in ecx and pops its own argument, so it is __thiscall with one argument.
// Returning the object in eax is what keeps esi live across the call.

class Open2C800Target
{
public:
	void assign( void *value );
};

// @?Rva0053C800@@YAPAVOpen2C800Target@@PAV1@PAX@Z 0x0053C800
Open2C800Target *Rva0053C800( Open2C800Target *target, void *value )
{
	target->assign( value );
	return target;
}

// ---------------------------------------------------------------------------
// 0x005381C0 -- forward both arguments plus a constant to the object held in
// the first member.
//
//     mov eax,[esp+8] / mov edx,[esp+4] / mov ecx,[ecx] / push eax / push edx
//     push 8 / call <REL32> / ret 8
//
// The stack accounting fixes the shape: this body pops 8 for its own two
// arguments and never adjusts esp after the call, so the callee pops the three
// it was pushed -- __thiscall on the pointer that `mov ecx,[ecx]` loaded out of
// offset 0. Arguments go out right to left, so the constant 8 is the FIRST
// parameter.

class Open2381C0Impl
{
public:
	void invoke( int kind, void *first, void *second );
};

class Open2381C0
{
public:
	void forward( void *first, void *second );
	Open2381C0Impl *m_impl;
};

// @?forward@Open2381C0@@QAEXPAX0@Z 0x005381C0
void Open2381C0::forward( void *first, void *second )
{
	m_impl->invoke( 8, first, second );
}
