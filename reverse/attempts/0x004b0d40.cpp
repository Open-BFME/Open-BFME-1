// ?d_004b0d40@@YAXXZ
// partial score=0.34 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// BFME retail 0x004B0D40, 979 bytes.
//
// The class name is the already landed owner spelling used by the adjacent
// clear/reset bodies.  The constructor at 0x004B18B0 installs vtable
// 0x010FD1D8; its seventh slot is the 0x00023D3F thunk into this body.  The
// function itself has no recovered retail spelling, hence the honest RVA
// method name below.

typedef float Real;

extern "C" long __ftol2( double value );
extern "C" void j_00006e83( void );
extern "C" double sin( double value );
extern "C" double cos( double value );

class GameWindow
{
public:
	int winSetSize( int width, int height );
	int winSetPosition( int x, int y );
	unsigned int _bfme_winSetStatus( unsigned int status );
	unsigned int winClearStatus( unsigned int status );
};

struct MenuScreenPoint
{
	Real x;
	Real y;
};

class MenuWindowManager
{
public:
	virtual void slot00( void );
	virtual void slot04( void );
	virtual void slot08( void );
	virtual void slot0c( void );
	virtual void slot10( void );
	virtual void slot14( void );
	virtual void slot18( void );
	virtual void slot1c( void );
	virtual void slot20( void );
	virtual void slot24( void );
	virtual void slot28( void );
	virtual MenuScreenPoint *getScreenPoint( void );
};

struct MenuTransform
{
	Real m_pad00[ 3 ];
	Real m_left;
	Real m_top;
	Real m_right;
	Real m_bottom;
};

struct MenuRecord
{
	char m_pad00[ 0x14 ];
	MenuTransform *m_transform;
};

struct MenuTree
{
	char m_bytes[ 12 ];
};

// This is the already-known STL tree helper at ILT 0x0046A10.  The generated
// thunk has an uninformative declaration, but the call site proves thiscall,
// two output-coordinate pointers, and a MenuRecord-like return value.
struct MenuTreeWithLookup
{
	MenuRecord *lookup( int *x, int *y );
	char m_bytes[ 12 ];
};

struct BfmeN1073;
extern "C" void __cdecl bfmeGo1073B( BfmeN1073 *value, Real x, Real y );

struct BfmeN1073
{
	char m_pad00[ 0x0c ];
	Real m_left;
	Real m_top;
	Real m_right;
	Real m_bottom;
};

extern MenuWindowManager *g_theWindowManager;

class Gen_004B1720
{
public:
	void rva004B0D40( void );

private:
	char m_pad00[ 8 ];
	unsigned char m_active;
	char m_pad09[ 3 ];
	GameWindow **m_windows;
	GameWindow **m_finish;
	GameWindow **m_end;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	Real m_3c;
	Real m_40;
	MenuTreeWithLookup m_tree;
};

static Real bfmeAt( const Real *address )
{
	return *address;
}

void Gen_004B1720::rva004B0D40( void )
{
	int count = (int)( m_finish - m_windows );
	if( count == 0 )
		return;

	j_00006e83();
	if( m_active == 0 )
		return;

	Real directionX = 0.0f;
	Real directionY = -1.0f;
	if( count > 1 )
	{
		double phase = (double)m_38;
		if( m_38 < 0 )
			phase += bfmeAt( (const Real *)0x01075358 );
		if( phase > bfmeAt( (const Real *)0x012B6624 ) )
			phase = bfmeAt( (const Real *)0x012B6624 );
		phase /= bfmeAt( (const Real *)0x012B6624 );
		phase = bfmeAt( (const Real *)0x01075334 ) - phase;
		Real sine = (Real)sin( phase );
		Real cosine = (Real)cos( phase );
		directionX = -sine;
		directionY = -cosine;
	}

	int *it = (int *)m_windows;
	int *finish = (int *)m_finish;
	Real minX = (Real)0x497423f0;
	Real minY = (Real)0x497423f0;
	Real maxX = 0.0f;
	Real maxY = 0.0f;
	MenuScreenPoint *screen = g_theWindowManager->getScreenPoint();

	while( it != finish )
	{
		GameWindow *window = *(GameWindow **)it;
		int width = (int)__ftol2( (double)( (Real)m_30 * directionX +
			(Real)m_34 * directionY ) );
		int height = (int)__ftol2( (double)( (Real)m_20 * directionX +
			(Real)m_24 * directionY ) );
		window->winSetSize( width, height );

		int x = (int)__ftol2( (double)screen->x );
		int y = (int)__ftol2( (double)screen->y );
		MenuRecord *record = m_tree.lookup( &x, &y );
		if( record != (MenuRecord *)&m_tree )
		{
			MenuTransform *transform = record->m_transform;
			if( transform != 0 )
			{
				BfmeN1073 *value = (BfmeN1073 *)((char *)transform + 8);
				bfmeGo1073B( value, (Real)x, (Real)y );
			}
		}

		window->winSetPosition( x - width / 2, y - height / 2 );
		if( directionX < m_3c )
			minX = directionX;
		if( directionY < m_3c )
			minY = directionY;
		if( (Real)m_38 < *(const Real *)0x010FD1A0 )
			window->_bfme_winSetStatus( 0x200 );
		else
			window->winClearStatus( 0x200 );

		++it;
	}

	if( (Real)m_38 >= bfmeAt( (const Real *)0x012B6624 ) )
		m_active = 0;
}
