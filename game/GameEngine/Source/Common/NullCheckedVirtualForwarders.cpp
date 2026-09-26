// 15 small bodies that re-dispatch a virtual call only when the object they
// reach is non-null:
//
//     mov ecx,[ecx+<D>] / [mov ecx,[ecx]] / test ecx,ecx / je +N /
//     mov eax,[ecx] / jmp [eax+<SLOT>] / ret <N>
//
// Companion to VirtualCallForwarders.cpp, which lands the unguarded case; read
// its header for why the callee is spelled as a slot in a class of virtual
// members and nothing more.  The difference here is the guard: the object is
// tested and the tail jump skipped when it is null, and the `ret` on that path
// is what gives the argument count -- 4, 8 or 12 bytes, so one, two or three
// dwords -- which the tail jump then forwards unchanged.  Because the arity is
// visible, the dispatch target is declared once per arity rather than once for
// all of them.
//
// A body that loads the member and then dereferences it once more reaches the
// object through a holder whose first field is the pointer; one that does not
// holds the pointer directly.  Two reach it from a .data global instead of from
// `this`, and are still spelled as members: retail JUMPS to the callee rather
// than calling it, which needs the caller's arguments to already sit where the
// callee expects them, and only a __thiscall frame does that.
//
// The holder is named in a local before being dereferenced.  Written as one
// expression -- `if ( m_holder->m_first ) m_holder->m_first->v21( a )` -- MSVC
// 7.1 emits a three-byte-longer body that reloads through eax; naming it keeps
// everything in ecx, which is retail.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

class VDispatch1
{
public:
	virtual void v0( int );
	virtual void v1( int );
	virtual void v2( int );
	virtual void v3( int );
	virtual void v4( int );
	virtual void v5( int );
	virtual void v6( int );
	virtual void v7( int );
	virtual void v8( int );
	virtual void v9( int );
	virtual void v10( int );
	virtual void v11( int );
	virtual void v12( int );
	virtual void v13( int );
	virtual void v14( int );
	virtual void v15( int );
	virtual void v16( int );
	virtual void v17( int );
	virtual void v18( int );
	virtual void v19( int );
	virtual void v20( int );
	virtual void v21( int );
	virtual void v22( int );
	virtual void v23( int );
	virtual void v24( int );
	virtual void v25( int );
	virtual void v26( int );
	virtual void v27( int );
	virtual void v28( int );
	virtual void v29( int );
	virtual void v30( int );
	virtual void v31( int );
	virtual void v32( int );
	virtual void v33( int );
	virtual void v34( int );
	virtual void v35( int );
	virtual void v36( int );
	virtual void v37( int );
	virtual void v38( int );
	virtual void v39( int );
	virtual void v40( int );
	virtual void v41( int );
	virtual void v42( int );
	virtual void v43( int );
	virtual void v44( int );
	virtual void v45( int );
	virtual void v46( int );
	virtual void v47( int );
	virtual void v48( int );
	virtual void v49( int );
	virtual void v50( int );
	virtual void v51( int );
	virtual void v52( int );
	virtual void v53( int );
	virtual void v54( int );
	virtual void v55( int );
	virtual void v56( int );
	virtual void v57( int );
	virtual void v58( int );
	virtual void v59( int );
	virtual void v60( int );
	virtual void v61( int );
	virtual void v62( int );
	virtual void v63( int );
	virtual void v64( int );
	virtual void v65( int );
	virtual void v66( int );
	virtual void v67( int );
	virtual void v68( int );
	virtual void v69( int );
	virtual void v70( int );
	virtual void v71( int );
	virtual void v72( int );
	virtual void v73( int );
	virtual void v74( int );
	virtual void v75( int );
	virtual void v76( int );
	virtual void v77( int );
	virtual void v78( int );
	virtual void v79( int );
	virtual void v80( int );
	virtual void v81( int );
	virtual void v82( int );
	virtual void v83( int );
};

class VDispatch2
{
public:
	virtual void v0( int, int );
	virtual void v1( int, int );
	virtual void v2( int, int );
	virtual void v3( int, int );
	virtual void v4( int, int );
	virtual void v5( int, int );
	virtual void v6( int, int );
	virtual void v7( int, int );
	virtual void v8( int, int );
	virtual void v9( int, int );
	virtual void v10( int, int );
	virtual void v11( int, int );
	virtual void v12( int, int );
	virtual void v13( int, int );
	virtual void v14( int, int );
	virtual void v15( int, int );
	virtual void v16( int, int );
	virtual void v17( int, int );
	virtual void v18( int, int );
	virtual void v19( int, int );
	virtual void v20( int, int );
	virtual void v21( int, int );
	virtual void v22( int, int );
	virtual void v23( int, int );
	virtual void v24( int, int );
	virtual void v25( int, int );
	virtual void v26( int, int );
	virtual void v27( int, int );
	virtual void v28( int, int );
	virtual void v29( int, int );
	virtual void v30( int, int );
	virtual void v31( int, int );
	virtual void v32( int, int );
	virtual void v33( int, int );
	virtual void v34( int, int );
	virtual void v35( int, int );
	virtual void v36( int, int );
	virtual void v37( int, int );
	virtual void v38( int, int );
	virtual void v39( int, int );
	virtual void v40( int, int );
	virtual void v41( int, int );
	virtual void v42( int, int );
	virtual void v43( int, int );
	virtual void v44( int, int );
	virtual void v45( int, int );
	virtual void v46( int, int );
	virtual void v47( int, int );
	virtual void v48( int, int );
	virtual void v49( int, int );
	virtual void v50( int, int );
	virtual void v51( int, int );
	virtual void v52( int, int );
	virtual void v53( int, int );
	virtual void v54( int, int );
	virtual void v55( int, int );
	virtual void v56( int, int );
	virtual void v57( int, int );
	virtual void v58( int, int );
	virtual void v59( int, int );
	virtual void v60( int, int );
	virtual void v61( int, int );
	virtual void v62( int, int );
	virtual void v63( int, int );
	virtual void v64( int, int );
	virtual void v65( int, int );
	virtual void v66( int, int );
	virtual void v67( int, int );
	virtual void v68( int, int );
	virtual void v69( int, int );
	virtual void v70( int, int );
	virtual void v71( int, int );
	virtual void v72( int, int );
	virtual void v73( int, int );
	virtual void v74( int, int );
	virtual void v75( int, int );
	virtual void v76( int, int );
	virtual void v77( int, int );
	virtual void v78( int, int );
	virtual void v79( int, int );
	virtual void v80( int, int );
	virtual void v81( int, int );
	virtual void v82( int, int );
	virtual void v83( int, int );
};

class VDispatch3
{
public:
	virtual void v0( int, int, int );
	virtual void v1( int, int, int );
	virtual void v2( int, int, int );
	virtual void v3( int, int, int );
	virtual void v4( int, int, int );
	virtual void v5( int, int, int );
	virtual void v6( int, int, int );
	virtual void v7( int, int, int );
	virtual void v8( int, int, int );
	virtual void v9( int, int, int );
	virtual void v10( int, int, int );
	virtual void v11( int, int, int );
	virtual void v12( int, int, int );
	virtual void v13( int, int, int );
	virtual void v14( int, int, int );
	virtual void v15( int, int, int );
	virtual void v16( int, int, int );
	virtual void v17( int, int, int );
	virtual void v18( int, int, int );
	virtual void v19( int, int, int );
	virtual void v20( int, int, int );
	virtual void v21( int, int, int );
	virtual void v22( int, int, int );
	virtual void v23( int, int, int );
	virtual void v24( int, int, int );
	virtual void v25( int, int, int );
	virtual void v26( int, int, int );
	virtual void v27( int, int, int );
	virtual void v28( int, int, int );
	virtual void v29( int, int, int );
	virtual void v30( int, int, int );
	virtual void v31( int, int, int );
	virtual void v32( int, int, int );
	virtual void v33( int, int, int );
	virtual void v34( int, int, int );
	virtual void v35( int, int, int );
	virtual void v36( int, int, int );
	virtual void v37( int, int, int );
	virtual void v38( int, int, int );
	virtual void v39( int, int, int );
	virtual void v40( int, int, int );
	virtual void v41( int, int, int );
	virtual void v42( int, int, int );
	virtual void v43( int, int, int );
	virtual void v44( int, int, int );
	virtual void v45( int, int, int );
	virtual void v46( int, int, int );
	virtual void v47( int, int, int );
	virtual void v48( int, int, int );
	virtual void v49( int, int, int );
	virtual void v50( int, int, int );
	virtual void v51( int, int, int );
	virtual void v52( int, int, int );
	virtual void v53( int, int, int );
	virtual void v54( int, int, int );
	virtual void v55( int, int, int );
	virtual void v56( int, int, int );
	virtual void v57( int, int, int );
	virtual void v58( int, int, int );
	virtual void v59( int, int, int );
	virtual void v60( int, int, int );
	virtual void v61( int, int, int );
	virtual void v62( int, int, int );
	virtual void v63( int, int, int );
	virtual void v64( int, int, int );
	virtual void v65( int, int, int );
	virtual void v66( int, int, int );
	virtual void v67( int, int, int );
	virtual void v68( int, int, int );
	virtual void v69( int, int, int );
	virtual void v70( int, int, int );
	virtual void v71( int, int, int );
	virtual void v72( int, int, int );
	virtual void v73( int, int, int );
	virtual void v74( int, int, int );
	virtual void v75( int, int, int );
	virtual void v76( int, int, int );
	virtual void v77( int, int, int );
	virtual void v78( int, int, int );
	virtual void v79( int, int, int );
	virtual void v80( int, int, int );
	virtual void v81( int, int, int );
	virtual void v82( int, int, int );
	virtual void v83( int, int, int );
};

extern VDispatch1 *g_Va012ED668;

class Rva002EEA10GuardedVCall
{
public:
	void forward( int a0 );
};

void Rva002EEA10GuardedVCall::forward( int a0 )
{
	VDispatch1 *target = g_Va012ED668;
	if ( target != 0 )
		target->v83( a0 );
}

extern VDispatch3 *g_Va012F7014;

class Rva001A3190GuardedVCall
{
public:
	void forward( int a0, int a1, int a2 );
};

void Rva001A3190GuardedVCall::forward( int a0, int a1, int a2 )
{
	VDispatch3 *target = g_Va012F7014;
	if ( target != 0 )
		target->v29( a0, a1, a2 );
}

class Rva001BEEE0GuardedVCall
{
public:
	void forward( int a0 );

	char m_lead[ 0x200 ];
	VDispatch1 *m_target;
};

void Rva001BEEE0GuardedVCall::forward( int a0 )
{
	VDispatch1 *target = m_target;
	if ( target != 0 )
		target->v12( a0 );
}

class Rva001BEF00GuardedVCall
{
public:
	void forward( int a0 );

	char m_lead[ 0x200 ];
	VDispatch1 *m_target;
};

void Rva001BEF00GuardedVCall::forward( int a0 )
{
	VDispatch1 *target = m_target;
	if ( target != 0 )
		target->v13( a0 );
}

class Rva00761D00GuardedVCall
{
public:
	void forward( int a0 );

	char m_lead[ 0x1B0 ];
	VDispatch1 *m_target;
};

void Rva00761D00GuardedVCall::forward( int a0 )
{
	VDispatch1 *target = m_target;
	if ( target != 0 )
		target->v4( a0 );
}

struct HolderRva00413FF0GuardedVCall { VDispatch1 *m_first; };
class Rva00413FF0GuardedVCall
{
public:
	void forward( int a0 );

	char m_lead[ 0x150 ];
	HolderRva00413FF0GuardedVCall *m_holder;
};

void Rva00413FF0GuardedVCall::forward( int a0 )
{
	HolderRva00413FF0GuardedVCall *holder = m_holder;
	if ( holder->m_first != 0 )
		holder->m_first->v21( a0 );
}

struct HolderRva00414010GuardedVCall { VDispatch1 *m_first; };
class Rva00414010GuardedVCall
{
public:
	void forward( int a0 );

	char m_lead[ 0x150 ];
	HolderRva00414010GuardedVCall *m_holder;
};

void Rva00414010GuardedVCall::forward( int a0 )
{
	HolderRva00414010GuardedVCall *holder = m_holder;
	if ( holder->m_first != 0 )
		holder->m_first->v23( a0 );
}

struct HolderRva00414080GuardedVCall { VDispatch1 *m_first; };
class Rva00414080GuardedVCall
{
public:
	void forward( int a0 );

	char m_lead[ 0x150 ];
	HolderRva00414080GuardedVCall *m_holder;
};

void Rva00414080GuardedVCall::forward( int a0 )
{
	HolderRva00414080GuardedVCall *holder = m_holder;
	if ( holder->m_first != 0 )
		holder->m_first->v27( a0 );
}

struct HolderRva004140A0GuardedVCall { VDispatch1 *m_first; };
class Rva004140A0GuardedVCall
{
public:
	void forward( int a0 );

	char m_lead[ 0x150 ];
	HolderRva004140A0GuardedVCall *m_holder;
};

void Rva004140A0GuardedVCall::forward( int a0 )
{
	HolderRva004140A0GuardedVCall *holder = m_holder;
	if ( holder->m_first != 0 )
		holder->m_first->v28( a0 );
}

struct HolderRva004140C0GuardedVCall { VDispatch1 *m_first; };
class Rva004140C0GuardedVCall
{
public:
	void forward( int a0 );

	char m_lead[ 0x150 ];
	HolderRva004140C0GuardedVCall *m_holder;
};

void Rva004140C0GuardedVCall::forward( int a0 )
{
	HolderRva004140C0GuardedVCall *holder = m_holder;
	if ( holder->m_first != 0 )
		holder->m_first->v29( a0 );
}

struct HolderRva00414230GuardedVCall { VDispatch1 *m_first; };
class Rva00414230GuardedVCall
{
public:
	void forward( int a0 );

	char m_lead[ 0x150 ];
	HolderRva00414230GuardedVCall *m_holder;
};

void Rva00414230GuardedVCall::forward( int a0 )
{
	HolderRva00414230GuardedVCall *holder = m_holder;
	if ( holder->m_first != 0 )
		holder->m_first->v48( a0 );
}

struct HolderRva00413FD0GuardedVCall { VDispatch2 *m_first; };
class Rva00413FD0GuardedVCall
{
public:
	void forward( int a0, int a1 );

	char m_lead[ 0x150 ];
	HolderRva00413FD0GuardedVCall *m_holder;
};

void Rva00413FD0GuardedVCall::forward( int a0, int a1 )
{
	HolderRva00413FD0GuardedVCall *holder = m_holder;
	if ( holder->m_first != 0 )
		holder->m_first->v22( a0, a1 );
}

struct HolderRva004141A0GuardedVCall { VDispatch2 *m_first; };
class Rva004141A0GuardedVCall
{
public:
	void forward( int a0, int a1 );

	char m_lead[ 0x150 ];
	HolderRva004141A0GuardedVCall *m_holder;
};

void Rva004141A0GuardedVCall::forward( int a0, int a1 )
{
	HolderRva004141A0GuardedVCall *holder = m_holder;
	if ( holder->m_first != 0 )
		holder->m_first->v24( a0, a1 );
}

struct HolderRva00414250GuardedVCall { VDispatch2 *m_first; };
class Rva00414250GuardedVCall
{
public:
	void forward( int a0, int a1 );

	char m_lead[ 0x150 ];
	HolderRva00414250GuardedVCall *m_holder;
};

void Rva00414250GuardedVCall::forward( int a0, int a1 )
{
	HolderRva00414250GuardedVCall *holder = m_holder;
	if ( holder->m_first != 0 )
		holder->m_first->v49( a0, a1 );
}

struct HolderRva00414030GuardedVCall { VDispatch3 *m_first; };
class Rva00414030GuardedVCall
{
public:
	void forward( int a0, int a1, int a2 );

	char m_lead[ 0x150 ];
	HolderRva00414030GuardedVCall *m_holder;
};

void Rva00414030GuardedVCall::forward( int a0, int a1, int a2 )
{
	HolderRva00414030GuardedVCall *holder = m_holder;
	if ( holder->m_first != 0 )
		holder->m_first->v30( a0, a1, a2 );
}

