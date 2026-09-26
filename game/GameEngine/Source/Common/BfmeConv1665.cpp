// Open-BFME5 conversions.

void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *block);

class TextureBaseClass
{
public:
	void Release_Ref();
};

class BfmeElemVVE
{
public:
	BfmeElemVVE() : m_bfme00( 0 ) {}
	~BfmeElemVVE();
	BfmeElemVVE &operator =( const BfmeElemVVE & that )
	{
		if ( that.m_bfme00 != 0 )
			++*(unsigned short *)( (char *)that.m_bfme00 + 4 );
		if ( m_bfme00 != 0 )
			m_bfme00->Release_Ref();
		m_bfme00 = that.m_bfme00;
		return *this;
	}

	TextureBaseClass *m_bfme00;
};

class BfmeBaseVVE
{
public:
	BfmeBaseVVE() : m_bfmeRefs( 1 ) {}
	~BfmeBaseVVE() { }
	virtual void bfmeSlot0VVE();
	int m_bfmeRefs;
};

class BfmeOwnVVE : public BfmeBaseVVE
{
public:
	BfmeOwnVVE( const BfmeOwnVVE & that );
	~BfmeOwnVVE();
	BfmeElemVVE *m_bfme08;
	BfmeElemVVE *m_bfme0C;
	int m_bfme10;
	int m_bfme14;
};

BfmeOwnVVE::BfmeOwnVVE( const BfmeOwnVVE & that )
	: m_bfme10( that.m_bfme10 ), m_bfme14( that.m_bfme14 )
{
	if ( m_bfme14 == 0 )
	{
		m_bfme08 = new BfmeElemVVE[ m_bfme10 ];
		m_bfme0C = m_bfme08;
	}
	else
	{
		m_bfme08 = (BfmeElemVVE *)::operator new[](
			m_bfme10 * sizeof( BfmeElemVVE ) + m_bfme14 );
		m_bfme0C = (BfmeElemVVE *)(
			( (unsigned int)m_bfme08 + m_bfme14 - 1 ) &
			~(unsigned int)( m_bfme14 - 1 ) );
	}
	for ( int index = 0; index < m_bfme10; ++index )
		m_bfme0C[ index ] = that.m_bfme0C[ index ];
}

BfmeOwnVVE::~BfmeOwnVVE()
{
	delete [] m_bfme08;
}
