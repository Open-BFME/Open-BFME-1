// ?fill@Rva008023B0Owner@@QAEXPAVRva007FBEF0GameRecord@@@Z
// partial score=0.85 date=2026-09-04
// cl: /GS
// jabba gamebrowser fill @ 0x008023B0 (155B).

class Rva00800290Buffer
{
public:
	void addPadded( int size );
	void addString( const char *text );
};

struct BfmeSlotCZ
{
	int *m_bfmePointer;
	int m_bfmeTag;
};

struct BfmeVecCZ
{
	BfmeSlotCZ *m_bfmeStart;
	int m_bfmeCount;
};

int *__stdcall bfmeAt( BfmeVecCZ *vector, int index );

class Rva007FBEF0GameRecord
{
public:
	bool Rva007FBFB0( const char *key, char *dest, unsigned int destSize );

	char m_pad[0x10];
	char m_key;
};

class Rva008023B0Owner
{
public:
	void fill( Rva007FBEF0GameRecord *rec );

	void *m_00;
	char *m_inner;
	char m_pad08[0x10];
	Rva00800290Buffer m_buf;
};

void Rva008023B0Owner::fill( Rva007FBEF0GameRecord *rec )
{
	char buf[0x40];

	m_buf.addString( &rec->m_key );

	{
		char *p = m_inner;
		int n = *(int *)( p + 0x2BC );
		m_buf.addPadded( n * 4 );
		p += 0x2B8;

		for( int i = 0; i < n; i++ )
		{
			int *slot = bfmeAt( (BfmeVecCZ *)p, i );
			buf[0] = 0;
			if( rec->Rva007FBFB0( (const char *)slot, buf, 0x40 ) )
				m_buf.addString( buf );
		}
	}
}
