// ?initialize@Rva0058D930Initializer@@QAEXXZ
// partial score=0.45 date=2026-09-02
// cl: /O2 /Ob1

struct Rva0058D930Record
{
	__forceinline Rva0058D930Record( void *end ) :
		m_end( end ),
		m_zero( 0 ),
		m_first( -1 ),
		m_second( -1 ),
		m_third( -1 ),
		m_flagA( false ),
		m_flagB( false )
	{
	}

	void *m_end;
	int   m_zero;
	int   m_first;
	int   m_second;
	int   m_third;
	bool  m_flagA;
	bool  m_flagB;
};

void __cdecl rva0058D930InitializeRange( void *begin, char *state, Rva0058D930Record *record );

class Rva0058D930Initializer
{
public:
	void initialize();

private:
	bool  m_active;
	char  m_pad01[ 3 ];
	void *m_end;
	char  m_range[ 0x198 ];
	char  m_state;
};

void Rva0058D930Initializer::initialize()
{
	Rva0058D930Record record( m_end );
	m_active = false;
	m_state = 0;
	rva0058D930InitializeRange( m_range, &m_state, &record );
}
