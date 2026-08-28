// cl: /DNDEBUG /MD /EHsc
// readable body of ??1RadiusDecal@@: Code/GameEngine/Source/GameClient/RadiusDecal.cpp

// RadiusDecal's destructor, retail 0x00458340 - thirty-four bytes identical to
// clear() at 0x00458310, which the linker did not fold. Spelled as a destructor
// with the same body rather than as a call to clear(), because a call is what
// retail does not have.
//
// The shadow behind +0x04 is released through its own vftable slot at +0x08 and
// only when it is there; the dword at +0x00 is cleared before the test, which
// is the scheduler filling the gap, and the flag at +0x08 is set true last.

class RadiusDecalShadow
{
public:
	virtual void _bfme_pad_00() = 0;
	virtual void _bfme_pad_04() = 0;
	virtual void release() = 0;				// +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecal
{
public:
	~RadiusDecal();

private:
	int m_unmodelled_00;					// +0x00
	RadiusDecalShadow *m_shadow;			// +0x04
	bool m_unmodelled_08;					// +0x08
};

// ??1RadiusDecal@@QAE@XZ
RadiusDecal::~RadiusDecal()
{
	m_unmodelled_00 = 0;

	if( m_shadow )
		m_shadow->release();

	m_shadow = 0;
	m_unmodelled_08 = true;
}
