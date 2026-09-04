// ?fill@Rva00801EC0Owner@@QAEXPAVRva007FBEF0GameRecord@@@Z
// partial score=0.82 date=2026-09-04
// cl: /GX- /GS
// jabba gamebrowser demangler record fill @ 0x00801EC0 (199B).
// Near-miss: MSVC schedules `add ebp,0x2B0` after claim setup and drops the
// dead `mov ecx,[esi+4]` before bfmeAt; otherwise measure/allocate/claim/append.

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
	bool Rva007FBF40( const char *key, char *dest, unsigned int destSize );

	int m_lid;
	int m_gid;
	void *m_msg;
	char m_ugid[0x25];
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

class Rva00801EC0Owner
{
public:
	void measure( Rva007FBEF0GameRecord *rec );
	void fill( Rva007FBEF0GameRecord *rec );

	void *m_00;
	char *m_host;
	char m_08[0x14];
	Rva00800460Arena m_arena;
	char m_28[0x10];
	char **m_keys;
	char m_3c[0x30];
	char *m_ugid;
};

void Rva00801EC0Owner::fill( Rva007FBEF0GameRecord *rec )
{
	char *p;
	int count;
	int i;
	char buf[0x40];
	char *key;

	measure( rec );

	( (Rva00800290Buffer *)&m_arena )->allocate();

	p = m_host;
	count = *(int *)( p + 0x2B4 );
	p += 0x2B0;
	m_keys = (char **)m_arena.claim( count * 4, true );

	for( i = 0; i < count; i++ )
	{
		key = (char *)bfmeAt( (BfmeVecCZ *)p, i );
		buf[0] = 0;
		if( !rec->Rva007FBF40( key, buf, 0x40 ) )
			m_keys[i] = 0;
		else
			m_keys[i] = m_arena.append( buf );
	}

	m_ugid = m_arena.append( rec->m_ugid );
}
