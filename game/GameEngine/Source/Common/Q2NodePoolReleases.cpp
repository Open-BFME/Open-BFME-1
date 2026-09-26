// cl: /EHs-c-
// Seven 27-byte __thiscall members that run one no-argument member of their
// own object and then return a fixed-size block held at offset 0 to the
// STLport node allocator:
//
//   push esi / mov esi,ecx
//   call <CLEANUP>                     ; __thiscall on this, no arguments
//   mov esi,[esi] / test esi,esi / je done
//   push <SIZE> / push esi
//   call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
//   add esp,8
//  done:
//   pop esi / ret
//
// WHAT THE BYTES SHOW.  esi holds `this` across the first call, so that callee
// is __thiscall and takes no stack arguments -- nothing is pushed for it and
// nothing is cleaned after it.  The reload `mov esi,[esi]` proves the released
// pointer is the object's FIRST dword.  The second call pushes two dwords and
// cleans them with `add esp,8`, which is __cdecl, and it lands on 0x0082E5F0,
// which the ledger already carries as STLport's private static
// __node_alloc<true,0>::_M_deallocate(void *, unsigned int) -- so the second
// argument is a byte size and it is a COMPILE-TIME CONSTANT here, which means
// the block is one fixed-size node and not a grown buffer.  There is an
// explicit null test in front of it, unlike `delete`, because _M_deallocate
// does not tolerate null.
//
// TWO AXES: the cleanup callee and the node size.  They move together -- four
// (callee, size) pairs, 0x2C, 0x44, 0x24 and 0x1C -- which is what groups the
// seven rows into four classes.  19 of the 27 bytes are concrete; the two
// displacements are resolved from the ledger and from pins.
//
// WHAT THE BYTES DO NOT DECIDE.  Whether this is a destructor: it is a plain
// `ret` with no vptr store anywhere, so if it is one, its class is not
// polymorphic and has no base that does anything.  It is spelled as an
// ordinary member because a destructor would assert more.  The __node_alloc
// declaration here is the minimum that mangles to the ledger's name -- one
// private static, reached through a friend -- and says nothing about the rest
// of that template.  Nothing but the released pointer is visible in any of the
// four classes.
//
// THREE PAIRS OF ROWS SHARE A CLASS, in the sense that they call the same
// cleanup body with the same node size; they are two members of one class
// rather than two classes, since nothing about a non-virtual member forces
// them apart the way a constructor or a vtable would.
//
// IDENTITY IS NOT RECOVERED.  Every name but _M_deallocate is derived from an
// address.

class Q2NodeAlloc;

namespace _STL
{
template <bool __threads, int __inst>
class __node_alloc
{
	static void _M_deallocate( void *p, unsigned int n );
	friend class ::Q2NodeAlloc;
};
}

class Q2NodeAlloc
{
public:
	static void deallocate( void *p, unsigned int n )
	{
		_STL::__node_alloc< true, 0 >::_M_deallocate( p, n );
	}
};

#define Q2_NODE_POOL_RELEASE( NAME )                                      \
	void NAME::NAME##Release()                                            \
	{                                                                     \
		cleanup();                                                        \
		if ( m_node )                                                     \
			Q2NodeAlloc::deallocate( m_node, NAME##NodeSize );            \
	}

class Gen0013BF00Owner
{
public:
	void cleanup();									///< body 0x0013BF00
	void Rva0013C080();
	void Rva0013C110();
private:
	void *m_node;
};

class Gen0056D960Owner
{
public:
	void cleanup();									///< body 0x0056D960
	void Rva0056DE10();
private:
	void *m_node;
};

class Gen00627270Owner
{
public:
	void cleanup();									///< body 0x00627270
	void Rva00627340();
	void Rva00627590();
private:
	void *m_node;
};

class Gen0076AE50Owner
{
public:
	void cleanup();									///< body 0x0076AE50
	void Rva0076D530();
	void Rva0076F770();
private:
	void *m_node;
};

#undef Q2_NODE_POOL_RELEASE
#define Q2_NODE_POOL_RELEASE( OWNER, NAME, SIZE )                         \
	void OWNER::NAME()                                                    \
	{                                                                     \
		cleanup();                                                        \
		if ( m_node )                                                     \
			Q2NodeAlloc::deallocate( m_node, SIZE );                      \
	}

Q2_NODE_POOL_RELEASE( Gen0013BF00Owner, Rva0013C080, 0x2C )
Q2_NODE_POOL_RELEASE( Gen0013BF00Owner, Rva0013C110, 0x2C )
Q2_NODE_POOL_RELEASE( Gen0056D960Owner, Rva0056DE10, 0x44 )
Q2_NODE_POOL_RELEASE( Gen00627270Owner, Rva00627340, 0x24 )
Q2_NODE_POOL_RELEASE( Gen00627270Owner, Rva00627590, 0x24 )
Q2_NODE_POOL_RELEASE( Gen0076AE50Owner, Rva0076D530, 0x1C )
Q2_NODE_POOL_RELEASE( Gen0076AE50Owner, Rva0076F770, 0x1C )
