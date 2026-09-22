// ?unlinkChain@Rva009A36F0Owner@@QAEXPAVRva009A36F0Thing@@@Z
// partial score=0.53 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
//
// Retail RVA 0x009A3630 (190 bytes). Pinned identity (reverse/symbols.csv):
// ?unlinkChain@Rva009A36F0Owner@@QAEXPAVRva009A36F0Thing@@@Z -- address-derived
// direct pin for the still-dump chain-unlinker Rva009A36F0Owner::apply calls
// in its else branch (Code/GameEngine/Source/Common/Rva009A36F0Owner.cpp).
//
// thing->+0x20 is the head of a work queue of anchor records; each anchor's
// +8 gives the payload node to detach.  Per node, retail unlinks it from two
// intrusive backlink/next lists (+0x14/+0x18 and +0x20/+0x24, same
// pointer-to-pointer backlink idiom as the landed
// Rva009A3300HashTableRemove.cpp), removes it from the 0x493-bucket hash
// table keyed by its own +8/+0xc fields, then unlinks it from a THIRD
// backlink/next list at +0x2c/+0x30 -- this one belongs to Owner itself
// (freeHead at +0xae04, cursor at +0xae0c, both ahead of the embedded hash
// table at +0xae10) -- and finally pushes the node onto Owner's free list.

// pinned callee: ?remove@Rva009A3300HashTable@@QAEXPAURva009A3300Node@@@Z
struct Rva009A3300Node
{
	char m_pad0[8];
	unsigned int m_key0;
	unsigned int m_key1;
	char m_pad10[0x1c];
};

class Rva009A3300HashTable
{
public:
	void remove( Rva009A3300Node *entry );
};

class Rva009A36F0Thing
{
public:
	char m_unreconstructed_00[0x20];
	void *m_queueHead;          // +0x20
};

class Rva009A36F0Owner
{
public:
	void unlinkChain( Rva009A36F0Thing *thing );

	char m_unreconstructed_00[0xae04];
	void *m_freeHead;                    // +0xae04
	char m_unreconstructed_ae08[4];
	void *m_cursor;                       // +0xae0c
};

void Rva009A36F0Owner::unlinkChain( Rva009A36F0Thing *thing )
{
	while ( thing->m_queueHead )
	{
		char *anchor = (char *)thing->m_queueHead;
		char *node = *(char **)( anchor + 8 );

		void *nextA = *(void **)( node + 0x18 );
		if ( nextA )
			*(void **)nextA = *(void **)( node + 0x14 );
		void *backlinkA = *(void **)( node + 0x14 );
		nextA = *(void **)( node + 0x18 );
		*(void **)backlinkA = nextA;
		*(void **)( node + 0x14 ) = 0;

		void *nextB = *(void **)( node + 0x24 );
		if ( nextB )
			*(void **)nextB = *(void **)( node + 0x20 );
		void *backlinkB = *(void **)( node + 0x20 );
		nextB = *(void **)( node + 0x24 );
		*(void **)backlinkB = nextB;

		unsigned int keyA = *(unsigned int *)( node + 8 );
		unsigned int keyB = *(unsigned int *)( node + 0xc );
		Rva009A3300Node key;
		key.m_key0 = keyA;
		*(void **)( node + 0x20 ) = 0;
		key.m_key1 = keyB;
		( (Rva009A3300HashTable *)( (char *)this + 0xae10 ) )->remove( &key );

		if ( m_cursor == node )
			m_cursor = *(void **)( node + 0x30 );

		void *nextC = *(void **)( node + 0x30 );
		if ( nextC )
			*(void **)( (char *)nextC + 0x2c ) = *(void **)( node + 0x2c );
		*(void **)( *(void **)( node + 0x2c ) ) = *(void **)( node + 0x30 );
		*(void **)( node + 0x2c ) = 0;

		*(void **)( node + 0x30 ) = m_freeHead;
		m_freeHead = node;
	}
}
