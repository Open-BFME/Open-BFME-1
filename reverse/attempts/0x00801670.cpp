// ?measure@Rva00801670Owner@@QAEXPAVRva007FBEF0GameRecord@@@Z
// partial score=0.85 date=2026-09-04
// cl: /GX- /GS
// jabba gamebrowserdemangler.cpp measure @ 0x00801670 (203B).
// Near-miss: same family as 0x801EC0/0x802550 — register mirror (esi/edi vs
// ebx/ebp for rec/this), count kept in ebp via lea*[4] instead of spill+shl,
// and MSVC drops retail's dead mov ecx,[ebp+4] before bfmeAt (197 vs 203).

class Rva00800290Buffer
{
public:
	void addPadded( int size );
	void addString( const char *text );
};

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
	char *bfmeText();
	bool Rva007FBE80( const char *key, char *dest, unsigned destSize );
	char m_pad00[0x26];
	char m_str26;
	char m_pad27[0x7F];
	char m_strA6;
	char m_padA7[0x89];
	char m_str130;
};

class Rva00801670Owner
{
public:
	void measure( Rva007FBEF0GameRecord *rec );
	void *m_00;
	char *m_host;
	char m_08[8];
	Rva00800290Buffer m_buf;
};

void Rva00801670Owner::measure( Rva007FBEF0GameRecord *rec )
{
	char slot[0x40];
	int count;
	int i;
	char *p;

	m_buf.addString( &rec->m_str26 );
	m_buf.addString( &rec->m_strA6 );
	m_buf.addString( &rec->m_str130 );
	if( rec->bfmeText() )
		m_buf.addPadded( 0x28 );
	else
		m_buf.addPadded( 0x10 );

	p = m_host;
	count = *(int *)( p + 0x2AC );
	p += 0x2A8;
	m_buf.addPadded( count * 4 );
	for( i = 0; i < count; i++ )
	{
		slot[0] = 0;
		if( rec->Rva007FBE80( (char *)bfmeAt( (BfmeVecCZ *)p, i ), slot, 0x40 ) )
			m_buf.addString( slot );
	}
}
