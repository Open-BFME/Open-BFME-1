// cl: /DNDEBUG /MD /EHsc

void bfmeFreeBOG( void *block );
void __cdecl rva0058BED0Register( int id, int value );
extern int g_rva0058BED0ReadId;
extern int g_rva0058BED0NextId;

class Rva0058BF70Base
{
public:
	Rva0058BF70Base() : m_value( 0 ) {}
	virtual ~Rva0058BF70Base() {}
	virtual void slot1();
	virtual void slot2();

protected:
	int m_value;
};

class Rva0058BF70Owner : public Rva0058BF70Base
{
public:
	Rva0058BF70Owner( int value );
	virtual ~Rva0058BF70Owner();

private:
	bool  m_released;
	char  m_pad09[ 3 ];
	void *m_block;
	int   m_tail0;
	int   m_tail1;
};

Rva0058BF70Owner::Rva0058BF70Owner( int value ) :
	m_released( false ),
	m_block( (void *)g_rva0058BED0ReadId )
{
	++g_rva0058BED0NextId;
	m_tail0 = 0;
	m_tail1 = 0;
	if( g_rva0058BED0NextId >= 0xFFFF )
		g_rva0058BED0NextId = 0;

	rva0058BED0Register( (int)m_block, value );
}

Rva0058BF70Owner::~Rva0058BF70Owner()
{
	if( !m_released )
	{
		bfmeFreeBOG( m_block );
		m_released = true;
	}
}
