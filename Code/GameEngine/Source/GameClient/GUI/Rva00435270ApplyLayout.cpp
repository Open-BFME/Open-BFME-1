// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME7: the 131-byte method at 0x00435270.  When the readiness test
// (0x00434690) passes the object refreshes itself (0x00435170) hands its four
// floats at +0x4C..+0x58 the value at +0x2C and a literal 1 to the six-argument
// setter (0x00433DC0) and then feeds three (index from to) integer pairs --
// (0 +0x50 +0x60) (1 +0x60 +0x68) (2 +0x68 +0x58) truncated from the floats --
// to the three-argument setter (0x00433900).  All callees are still dumps;
// names are address-derived.

typedef int Int;
typedef float Real;
typedef bool Bool;

#define TRUE true
#define FALSE false

#include "StringInline.h"

class Rva00435270Receiver
{
public:
	virtual void slot00( void );
	virtual void setState( UnicodeString text );
};

class BfmeAwakenLog
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
	virtual void slot2c( void );
	virtual void slot30( void );
	virtual void slot34( void );
	virtual BfmeAwakenLog *slot38( const char *text );
	virtual void slot3c( void );
	virtual void slot40( void );
	virtual void slot44( void );
	virtual void slot48( void );
	virtual BfmeAwakenLog *slot4c( Int value );
};

class BfmeAwakenDebug
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
	virtual void slot2c( void );
	virtual void slot30( void );
	virtual void slot34( void );
	virtual void slot38( void );
	virtual void slot3c( void );
	virtual void slot40( void );
	virtual void slot44( void );
	virtual void slot48( void );
	virtual void slot4c( void );
	virtual void slot50( void );
	virtual void slot54( void );
	virtual void slot58( void );
	virtual void slot5c( void );
	virtual void slot60( void );
	virtual void slot64( void );
	virtual void slot68( void );
	virtual BfmeAwakenLog *slot6c( Int first, Int second );
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void _bfme_debugRecordCallsite( Int kind );

class Rva00435270Layout
{
public:
	void apply( void );

private:
	bool isReady( void );
	void refresh( void );
	void setRect( Real left, Real top, Real right, Real bottom, Int owner, Int flag );
	void setRange( Int index, Int from, Int to );

	char m_unreconstructed00[ 0x08 ];
	Int m_unknown08;
	Int m_unknown0c;
	char m_unreconstructed10[ 0x04 ];
	Int m_state14;
	char m_unreconstructed18[ 0x04 ];
	Int m_timer1c;
	char m_unreconstructed20[ 0x04 ];
	Int m_count24;
	Int m_progress28;
	Int m_owner2C;
	char m_unreconstructed30[ 0x04 ];
	Rva00435270Receiver **m_receivers34;
	char m_unreconstructed38[ 0x04 ];
	Int m_cursor3C;
	char m_unreconstructed40[ 0x0C ];
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

// ?isReady@Rva00435270Layout@@AAE_NXZ
bool Rva00435270Layout::isReady( void )
{
	register Bool result = TRUE;
	switch( m_state14 )
	{
	case 0:
	{
		Int progress = m_progress28 += 0x12;
		if( progress >= 0xFF )
		{
			m_progress28 = 0xFF;
			m_state14 = 3;
		}
		break;
	}
	case 1:
	case 4:
		result = FALSE;
		break;
	case 2:
	{
		Int progress = m_progress28 -= 0x12;
		if( progress <= 0 )
		{
			m_state14 = result;
			result = FALSE;
			m_progress28 = 0;
			for( Int i = 0; i < m_count24; ++i )
				m_receivers34[i]->setState( UnicodeString() );
			m_cursor3C = 0;
		}
		break;
	}
	case 3:
	{
		volatile Int &progress = m_progress28;
		progress = 0xFF;
		Int elapsed = m_unknown0c - m_unknown08;
		if( (elapsed & ~7) == 0 )
		{
			Int timer = m_timer1c -= 0x21;
			if( timer <= 0 )
			{
				m_timer1c = 0;
				m_state14 = 2;
			}
		}
		break;
	}
	default:
		_bfme_debugRecordCallsite( result );
		TheBfmeAwakenDebug->slot60();
		TheBfmeAwakenDebug->slot6c( 0, 0 )
			->slot38( (const char *)0x010F3950 )
			->slot4c( result );
		return FALSE;
	}
	return result;
}
