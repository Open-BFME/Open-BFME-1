// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// stlport
// Open-BFME7: the 131-byte method at 0x00435270.  When the readiness test
// (0x00434690) passes the object refreshes itself (0x00435170) hands its four
// floats at +0x4C..+0x58 the value at +0x2C and a literal 1 to the six-argument
// setter (0x00433DC0) and then feeds three (index from to) integer pairs --
// (0 +0x50 +0x60) (1 +0x60 +0x68) (2 +0x68 +0x58) truncated from the floats --
// to the three-argument setter (0x00433900).  All callees are still dumps;
// names are address-derived.

#include "../../../Include/Common/ScalarTypes.h"



#define TRUE true
#define FALSE false

#include "StringInline.h"
#include <vector>

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct Gen_t_00434fa0_p8cd
{
	Int a[2];
	Gen_t_00434fa0_p8cd();
	Gen_t_00434fa0_p8cd(const Gen_t_00434fa0_p8cd &);
	~Gen_t_00434fa0_p8cd();
	Gen_t_00434fa0_p8cd &operator=(const Gen_t_00434fa0_p8cd &);
};

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

extern void *g_Rva00F36E5C; // VA 01336E5C debug manager cell (data_rows.csv owner)
#define TheBfmeAwakenDebug (static_cast<BfmeAwakenDebug *>(g_Rva00F36E5C))
extern void _bfme_debugRecordCallsite( Int kind );
extern void j_0001ce9f();
extern void j_00007356();

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
	std::vector<Gen_t_00434fa0_p8cd> m_pending08;
	Int m_state14;
	char m_unreconstructed18[ 0x04 ];
	Int m_timer1c;
	char m_unreconstructed20[ 0x04 ];
	Int m_count24;
	Int m_progress28;
	Int m_owner2C;
	Int m_count30;
	Rva00435270Receiver **m_receivers34;
	Int *m_values38;
	Int m_cursor3C;
	Int m_unreconstructed40;
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

// ?apply@Rva00435270Layout@@QAEXXZ
void Rva00435270Layout::apply( void )
{
	if( !isReady() )
		return;
	union { void (*entry)(); void (Rva00435270Layout::*member)(); } refreshCall;
	refreshCall.entry = j_0001ce9f;
	(this->*refreshCall.member)();
	union { void (*entry)(); void (Rva00435270Layout::*member)(Real, Real, Real, Real, Int, Int); } setRectCall;
	setRectCall.entry = j_00007356;
	(this->*setRectCall.member)(m_left4C, m_top50, m_right54, m_bottom58, m_owner2C, 1);
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
		Int elapsed = (char *)m_pending08.end() - (char *)m_pending08.begin();
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
			->slot38( "Unrecognized SubTitleRenderState!" )
			->slot4c( result );
		return FALSE;
	}
	return result;
}

// Retail 0x00435170: the matched apply() caller reaches this through ILT
// 0x0001CE9F. RET at +0xC2 and following INT3 prove the 195-byte extent.
inline const Real &boundedTimer(const Real &value, const Real &zero)
{
	return zero > value ? zero : value;
}

void Rva00435270Layout::refresh()
{
	Real &timer = m_timer44;
	if (timer > 0.0f || m_pending08.size() != 0)
	{
		const Real zero = 0.0f;
		timer -= m_step48;
		// Retail rounds the subtraction into the float member, then compares
		// by loading zero and reading the member again. This compiler-only
		// barrier prevents VC7.1 retaining the extended-precision x87 result.
		_ReadWriteBarrier();
		timer = boundedTimer(timer, zero);
		if (timer == 0.0f && m_pending08.size() > 0)
		{
			m_receivers34[m_cursor3C % m_count24]->setState(
				*(const UnicodeString *)&m_pending08[0]);
			m_values38[m_cursor3C % m_count24] = m_pending08[0].a[1];
			m_pending08.erase(m_pending08.begin());
			Real delay = (Real)m_count30;
			Int next = m_cursor3C + 1;
			timer = delay;
			m_cursor3C = next;
		}
	}
}
