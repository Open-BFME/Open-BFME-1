// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Address-derived reconstruction.  This small method subtracts a requested
// amount from the count at +4, clamps it to zero, and clears the active flag
// at +0x2c when the count reaches zero.

class Rva005B42A0Countdown
{
public:
	void subtract( int amount );

private:
	int m_pad00;
	int m_count;
	char m_pad08[ 0x2C - 0x08 ];
	bool m_active;
};

void Rva005B42A0Countdown::subtract( int amount )
{
	if ( amount == 0 )
		m_count = 0;
	else if ( m_count & amount )
		m_count -= amount;

	if ( m_count < 0 )
		m_count = 0;
	if ( m_count == 0 )
		m_active = false;
}
