// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the 131-byte method at 0x00435270.  When the readiness test
// (0x00434690) passes the object refreshes itself (0x00435170) hands its four
// floats at +0x4C..+0x58 the value at +0x2C and a literal 1 to the six-argument
// setter (0x00433DC0) and then feeds three (index from to) integer pairs --
// (0 +0x50 +0x60) (1 +0x60 +0x68) (2 +0x68 +0x58) truncated from the floats --
// to the three-argument setter (0x00433900).  All callees are still dumps;
// names are address-derived.

typedef int Int;
typedef float Real;

class Rva00435270Layout
{
public:
	void apply( void );

private:
	bool isReady( void );
	void refresh( void );
	void setRect( Real left, Real top, Real right, Real bottom, Int owner, Int flag );
	void setRange( Int index, Int from, Int to );

	char m_unreconstructed00[ 0x2C ];
	Int m_owner2C;
	char m_unreconstructed30[ 0x4C - 0x30 ];
	Real m_left4C;
	Real m_top50;
	Real m_right54;
	Real m_bottom58;
	char m_unreconstructed5C[ 4 ];
	Real m_split60;
	char m_unreconstructed64[ 4 ];
	Real m_split68;
};

// ?apply@Rva00435270Layout@@QAEXXZ
void Rva00435270Layout::apply( void )
{
	if( !isReady() )
		return;
	refresh();
	setRect( m_left4C, m_top50, m_right54, m_bottom58, m_owner2C, 1 );
	setRange( 0, (Int)m_top50, (Int)m_split60 );
	setRange( 1, (Int)m_split60, (Int)m_split68 );
	setRange( 2, (Int)m_split68, (Int)m_bottom58 );
}
