// Three __thiscall members that look a node up in a container held at offset 0,
// compare the result against that container's own end marker, and -- only when
// the node exists and carries a non-null pointer at +0x14 -- make ONE virtual
// call on it:
//
//     mov eax,[esp+4] / push esi / push eax / mov esi,ecx / call <REL32>
//     cmp eax,[esi] / pop esi / je .out
//     mov ecx,[eax+0x14] / test ecx,ecx / je .out
//
// Both guards are spelled as EARLY RETURNS, not as one `&&`: the `&&` form makes
// MSVC 7.1 park the loaded pointer in eax and pass the argument in ecx, adding a
// `mov eax,ecx` / `mov ecx,eax` pair retail does not have.
//     <push the remaining stack arguments> / mov edx,[ecx] / call [edx+SLOT]
//   .out: ret <N>
//
// WHAT THE BYTES SHOW.  ecx is unchanged at the call, so the lookup is a member
// of THIS class, and its one pushed argument is this member's first argument
// passed straight through.  Its result is compared against the dword at offset 0
// -- the same object the lookup was made in -- which is what an end/no-hit
// marker comparison looks like, and it is compared, not dereferenced, before the
// second test.  The second test dereferences +0x14 of the returned node, so the
// node carries a pointer there; `mov edx,[ecx] / call [edx+SLOT]` then makes it
// the receiver of a virtual call.
//
// THE THREE ROWS SHARE ONE OWNER.  All three reach the same lookup body at
// 0x003B9DC0 through the same incremental-link thunk and all three compare
// against offset 0, so they are three members of ONE class rather than three
// classes -- which is also why the lookup is declared once here.
//
// TWO AXES, BOTH READ DIRECTLY: the vtable SLOT in the `call [edx+K]` (4, 8 and
// 0xC) and the ARITY, which the trailing `ret N` fixes exactly -- 8, 8 and 0xC
// bytes of arguments, one of which is always the lookup key.  Slot 0xC takes two
// arguments and they are pushed in the retail order.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the lookup
// pin is address-derived and additive.

class Gen003BAD00Target
{
public:
	virtual void slot00();
	virtual void slot04( int a );
	virtual void slot08( int a );
	virtual void slot0C( int a, int b );
};

class Gen003B9DC0Node
{
public:
	char                m_pad00[ 0x14 ];
	Gen003BAD00Target * m_at14;
};

class Rva003BAD00Owner
{
public:
	Gen003B9DC0Node * find( int key );
	void notify04( int key, int a );
	void notify08( int key, int a );
	void notify0C( int key, int a, int b );
	Gen003B9DC0Node * m_at00;
};

void Rva003BAD00Owner::notify04( int key, int a )
{
	Gen003B9DC0Node *node = find( key );
	if( node == m_at00 )
		return;
	Gen003BAD00Target *t = node->m_at14;
	if( t == 0 )
		return;
	t->slot04( a );
}

void Rva003BAD00Owner::notify0C( int key, int a, int b )
{
	Gen003B9DC0Node *node = find( key );
	if( node == m_at00 )
		return;
	Gen003BAD00Target *t = node->m_at14;
	if( t == 0 )
		return;
	t->slot0C( a, b );
}

void Rva003BAD00Owner::notify08( int key, int a )
{
	Gen003B9DC0Node *node = find( key );
	if( node == m_at00 )
		return;
	Gen003BAD00Target *t = node->m_at14;
	if( t == 0 )
		return;
	t->slot08( a );
}
