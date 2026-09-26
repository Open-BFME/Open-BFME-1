// ?refresh@Rva00435270Layout@@AAEXXZ
// partial score=0.55 date=2026-09-10
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

#include <vector>
#include <algorithm>

extern const Real BfmeZeroRange;

// Retail stores the queued eight-byte records in the STLport vector whose
// erase body is already identified at 0x00434FA0.  The first dword is the
// wide-string value consumed by the receiver below; the second dword is
// intentionally opaque to this method.
struct Gen_t_00434fa0_p8cd
{
	int a[2];
};

typedef std::vector<Gen_t_00434fa0_p8cd> Rva00435270PendingVector;

template <typename T> class StringBase
{
	friend class Rva00435270UnicodeString;

private:
	StringBase( const StringBase<T> &other );
	void *m_data;
};

class Rva00435270UnicodeString : private StringBase<unsigned short>
{
public:
	Rva00435270UnicodeString( const Rva00435270UnicodeString &other )
		: StringBase<unsigned short>(
			*(const StringBase<unsigned short> *)&other )
	{
	}
};

class Rva00435270Receiver
{
public:
	virtual void receiverSlot00();
	virtual void consume( Rva00435270UnicodeString text );
};

class Rva00435270Layout
{
public:
	void apply( void );

private:
	bool isReady( void );
	void refresh( void );
	void setRect( Real left, Real top, Real right, Real bottom, Int owner, Int flag );
	void setRange( Int index, Int from, Int to );

	char m_unreconstructed00[ 8 ];
	char m_pendingStorage[ 0x0C ];
	char m_unreconstructed14[ 0x24 - 0x14 ];
	Int m_divisor24;
	char m_unreconstructed28[ 4 ];
	Int m_owner2C;
	Int m_count30;
	Rva00435270Receiver **m_receivers34;
	void **m_values38;
	Int m_cursor3C;
	char m_unreconstructed40[ 4 ];
	Real m_timer44;
	Real m_step48;
	Real m_left4C;
	Real m_top50;
	Real m_right54;
	Real m_bottom58;
	char m_unreconstructed5C[ 4 ];
	Real m_split60;
	char m_unreconstructed64[ 4 ];
	Real m_split68;
};

// ?refresh@Rva00435270Layout@@AAEXXZ
void Rva00435270Layout::refresh( void )
{
	Real &timer = m_timer44;
	if( timer > BfmeZeroRange )
	{
		timer -= m_step48;
		timer = std::max( timer, BfmeZeroRange );
		if( timer > BfmeZeroRange )
			return;
	}

	if( ((Rva00435270PendingVector *)m_pendingStorage)->empty() )
		return;

	Int index = m_cursor3C % m_divisor24;
	m_receivers34[ index ]->consume(
		*(const Rva00435270UnicodeString *)
			&((Rva00435270PendingVector *)m_pendingStorage)->operator[]( 0 ) );

	index = m_cursor3C % m_divisor24;
	Rva00435270Receiver *receiver = m_receivers34[ index ];
	m_values38[ index ] = *(void **)((char *)receiver + 4);
	((Rva00435270PendingVector *)m_pendingStorage)->erase(
		((Rva00435270PendingVector *)m_pendingStorage)->begin() );
	timer = (Real)m_count30;
	++m_cursor3C;
}

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
