// ?fill@Rva00802550Owner@@QAEXPAVRva007FBEF0GameRecord@@PAD@Z
// partial score=0.88 date=2026-09-04
// cl: /GX- /GS
// jabba gamebrowser demangler fill @ 0x00802550 (227B).
// Seeds host/record fields, measure-fill 0x8023B0, allocate, append key,
// claim key-pointer table, loop bfmeAt + Rva007FBFB0 + append-or-null.
// Near-miss: same family residue as 0x801EC0 — MSVC schedules `add ebx,0x2B8`
// after claim pushes and drops the dead `mov ecx,[esi+4]` before bfmeAt
// (224 vs 227).

class BfmeSlotCZ
{
public:
	int *m_bfmePointer;
	int m_bfmeTag;
};

class BfmeVecCZ
{
public:
	BfmeSlotCZ *m_bfmeStart;
	int m_bfmeCount;
};

int * __stdcall bfmeAt( BfmeVecCZ *vector, int index );

class Rva007FBEF0GameRecord
{
public:
	bool Rva007FBFB0( const char *key, char *dest, unsigned int destSize );

	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	char m_key;
	char m_pad11[0x7F];
	int m_90;
	int m_94;
};

class Rva00800290Buffer
{
public:
	void allocate();
	char *m_ptr;
	int m_size;
};

class Rva00800460Arena
{
public:
	void *claim( int size, bool align );
	char *append( const char *text );

	char *m_base;
	unsigned m_cap;
	unsigned m_used;
};

class Rva00802550Owner
{
public:
	void fill( Rva007FBEF0GameRecord *rec, char *host );
	void measure( Rva007FBEF0GameRecord *rec );   // 0x008023B0

	void *m_00;
	char *m_host;
	int m_08;
	char m_0C[4];
	int m_10;
	int m_14;
	Rva00800460Arena m_arena;
	char *m_key;
	char **m_keys;
};

void Rva00802550Owner::fill( Rva007FBEF0GameRecord *rec, char *host )
{
	char buf[0x40];
	char *p;
	int count;
	int i;
	char *slot;

	m_host = host;
	m_08 = rec->m_0C;
	m_10 = rec->m_90;
	m_14 = rec->m_94;
	measure( rec );

	( (Rva00800290Buffer *)&m_arena )->allocate();
	m_key = m_arena.append( &rec->m_key );

	p = m_host;
	count = *(int *)( p + 0x2BC );
	p += 0x2B8;
	m_keys = (char **)m_arena.claim( count * 4, true );

	for( i = 0; i < count; i++ )
	{
		slot = (char *)bfmeAt( (BfmeVecCZ *)p, i );
		buf[0] = 0;
		if( !rec->Rva007FBFB0( slot, buf, 0x40 ) )
			m_keys[i] = 0;
		else
			m_keys[i] = m_arena.append( buf );
	}
}
