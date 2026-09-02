// cl: /DNDEBUG /MD /EHsc

// Address-derived reconstruction of the small state dispatcher beside
// SiegeDeploySpecialPower.  The retail body groups states 0/1 and 2/3.

class Rva00266EB0SiegeDeployBase
{
public:
	void transition( int value );
};

class Rva00266EB0SiegeDeployStateDispatch
{
public:
	void dispatch();

private:
	unsigned char m_lead[ 0x14 ];
	unsigned int m_state;
	unsigned char m_gap[ 0x34 ];
	unsigned char m_finished;
};

void Rva00266EB0SiegeDeployStateDispatch::dispatch()
{
	switch ( m_state )
	{
		case 0:
		case 1:
			( (Rva00266EB0SiegeDeployBase *)( (char *)this - 0x24 ) )->transition( 0 );
			break;
		case 2:
		case 3:
			m_finished = 1;
			break;
	}
}
