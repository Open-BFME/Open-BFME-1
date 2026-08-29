// Four more bodies recovered from byte-true dumps.  Identity is NOT recovered:
// class, member and function names are address-derived, and padding virtuals
// exist only to place the slot each body calls.

// ---------------------------------------------------------------------------
// 0x00715D80 -- two flag tests with a poke in between.
//
//     test byte [ecx+0x110],1 / jne yes / mov eax,[ecx+4] / test eax,eax / je
//     mov ecx,[eax+4] / test ecx,ecx / je / call <REL32>
//     test byte [eax+0xc8],0x20 / jne yes / xor eax,eax / ret / yes: mov eax,1
//
// The owner pointer is read ONCE into eax and the second flag test reads
// through it whether or not the guarded call ran -- retail dereferences a
// pointer it has just tested for null.  That is a redundant guard in the
// source, not a compiler artifact; nothing else produces a `je` into a
// dereference of the register the branch just found to be zero.

class Open2715D80Owner;

class Open2715D80Inner
{
public:
	Open2715D80Owner *poke( void );
};

class Open2715D80Owner
{
public:
	char m_pad[4];
	Open2715D80Inner *m_inner;
	char m_pad2[0xc0];
	unsigned char m_flags;
};

class Rva00715D80
{
public:
	int query( void ) const;
	char m_pad[4];
	Open2715D80Owner *m_owner;
	char m_pad2[0x108];
	unsigned char m_gate;
};

// @?query@Rva00715D80@@QBEHXZ 0x00715D80
int Rva00715D80::query( void ) const
{
	if( ( m_gate & 1 ) == 0 )
	{
		Open2715D80Owner *owner = m_owner;
		if( owner && owner->m_inner )
			owner = owner->m_inner->poke();
		if( ( owner->m_flags & 0x20 ) == 0 )
			return 0;
	}
	return 1;
}

// ---------------------------------------------------------------------------
// 0x007110F0 -- unpack a three-dword record into one global's member call, then
// poke a second global.  Both globals are tested; the second test is INSIDE the
// first, so the flush only happens when the submit did.

class Open2Triple5
{
public:
	int m_x;
	int m_y;
	int m_z;
};

class Open27110F0Sink
{
public:
	void submit( int which, int x, int y, int z );
};

class Open27110F0Flusher
{
public:
	void flush( void );
};

extern Open27110F0Sink *TheOpen27110F0Sink;
extern Open27110F0Flusher *TheOpen27110F0Flusher;

// @?Rva007110F0@@YGXPAVOpen2Triple5@@@Z 0x007110F0
void __stdcall Rva007110F0( const Open2Triple5 *record )
{
	if( TheOpen27110F0Sink )
	{
		TheOpen27110F0Sink->submit( 0, record->m_x, record->m_y, record->m_z );
		if( TheOpen27110F0Flusher )
			TheOpen27110F0Flusher->flush();
	}
}

// ---------------------------------------------------------------------------
// 0x0071B4B0 -- release three arrays, latch a flag, and empty a circular list.
//
// The three releases call `??_V` (operator delete[]), not `??3`, so all three
// members are ARRAY allocations.  Each clear is emitted after the next load,
// which is MSVC sinking a store past a load it can prove independent -- the
// plain `delete[] p; p = 0;` spelling, not a helper.
//
// The list at +0x44 is reached through a materialised address (`add esi,0x44`)
// and its head is RE-READ before each of the three resets, so the source walks
// through the member each time rather than holding it in a local.

class Open2Node
{
public:
	void *m_owner;
	Open2Node *m_next;
	Open2Node *m_prev;
	Open2Node *m_tail;
};

class Open2List
{
public:
	void drop( Open2Node *node );
	Open2Node *m_head;
	int m_count;
};

class Rva0071B4B0
{
public:
	void reset( void );
	char m_pad[0x18];
	void *m_bufferA;
	char m_pad2[0x19];
	unsigned char m_ready;
	char m_pad3[2];
	void *m_bufferB;
	void *m_bufferC;
	char m_pad4[4];
	Open2List m_list;
};

// @?reset@Rva0071B4B0@@QAEXXZ 0x0071B4B0
void Rva0071B4B0::reset( void )
{
	if( m_bufferA )
		delete[] (char *)m_bufferA;
	m_bufferA = 0;
	if( m_bufferB )
		delete[] (char *)m_bufferB;
	m_bufferB = 0;
	if( m_bufferC )
		delete[] (char *)m_bufferC;
	m_bufferC = 0;
	m_ready = 1;

	Open2List *list = &m_list;
	if( list->m_count != 0 )
	{
		list->drop( list->m_head->m_next );
		list->m_head->m_prev = list->m_head;
		list->m_head->m_next = 0;
		list->m_head->m_tail = list->m_head;
		list->m_count = 0;
	}
}
