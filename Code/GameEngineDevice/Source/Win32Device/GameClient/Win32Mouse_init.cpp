// cl: /DNDEBUG /MD /EHsc

// Win32Mouse::init, retail 0x006BC0A0. The base's init and then one flag at
// +0x4DA0 - a long way into a class whose front this file says nothing about.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/GameClient/Win32Mouse.h
class Win32Mouse
{
public:
	virtual void init( void );

	// A member, not a base method. This class declares a virtual, so a base with
	// no data of its own would sit at +0x04 behind the vftable pointer and the
	// call would go out with `this' adjusted; retail passes it unadjusted.
	void initDevice( void );

private:
	unsigned char m_unmodelled_04[ 0x4DA0 - 4 ];
	bool m_unmodelled_4DA0;					// +0x4DA0
};

// ?init@Win32Mouse@@UAEXXZ
void Win32Mouse::init( void )
{
	initDevice();

	m_unmodelled_4DA0 = true;
}
