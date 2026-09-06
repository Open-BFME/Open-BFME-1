// Address-derived: 0.866 difflib match to the landed
// ?update@BfmeThingDTK@@QAEXXZ (Code/GameEngine/Source/Common/
// BfmeThingDTKUpdate.cpp). Identical field layout (+0xC config ptr, +0x10
// active flag, +0x14 start countdown, +0x24 periodic countdown), identical
// vtable+0x68 slot and identical bfmeTailDTK callee (ILT thunk 0x0001C75B),
// but two concrete differences prove this is a sibling body, not the same
// function: the start-countdown reset here is clamped to 15 (retail adds
// `if (m_startCountdown > 15) m_startCountdown = 15;` right after the reset,
// which BfmeThingDTK::update does not have), and the periodic-countdown
// reload constant is 10, not 25. Real class name not recovered.

struct Rva00168850Config
{
	unsigned char m_pad0[ 0x294 ];
	unsigned char m_enabled;
};

class Rva00168850DTK
{
public:
	virtual void slot00( void ) = 0; virtual void slot04( void ) = 0;
	virtual void slot08( void ) = 0; virtual void slot0C( void ) = 0;
	virtual void slot10( void ) = 0; virtual void slot14( void ) = 0;
	virtual void slot18( void ) = 0; virtual void slot1C( void ) = 0;
	virtual void slot20( void ) = 0; virtual void slot24( void ) = 0;
	virtual void slot28( void ) = 0; virtual void slot2C( void ) = 0;
	virtual void slot30( void ) = 0; virtual void slot34( void ) = 0;
	virtual void slot38( void ) = 0; virtual void slot3C( void ) = 0;
	virtual void slot40( void ) = 0; virtual void slot44( void ) = 0;
	virtual void slot48( void ) = 0; virtual void slot4C( void ) = 0;
	virtual void slot50( void ) = 0; virtual void slot54( void ) = 0;
	virtual void slot58( void ) = 0; virtual void slot5C( void ) = 0;
	virtual void slot60( void ) = 0; virtual void slot64( void ) = 0;
	virtual void slot68( void ) = 0;

	// ?updateVariant@Rva00168850DTK@@QAEXXZ
	void updateVariant( void );
	void bfmeTailDTK( void );

private:
	unsigned char m_pad4[ 8 ];
	Rva00168850Config *m_config;
	unsigned char m_active;
	unsigned char m_pad11[ 3 ];
	int m_startCountdown;
	unsigned char m_pad18[ 0x0C ];
	int m_periodicCountdown;
};

void Rva00168850DTK::updateVariant( void )
{
	if ( !m_config->m_enabled )
		return;

	if ( !m_active )
	{
		if ( --m_startCountdown <= 0 )
		{
			m_active = 1;
			m_periodicCountdown = 0;
		}
		if ( m_startCountdown > 15 )
			m_startCountdown = 15;
	}

	if ( --m_periodicCountdown < 1 )
	{
		bfmeTailDTK();
		if ( m_active )
			slot68();
		m_periodicCountdown = 10;
	}
}
