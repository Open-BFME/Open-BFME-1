// Address-derived reconstruction of the 17-byte value/state setter at 0x007F5700.

class Rva007F5700ValueAndState
{
public:
	void setValue( int value );

private:
	char m_pad00[ 0x28 ];
	int m_value;
	int m_state;
};

void Rva007F5700ValueAndState::setValue( int value )
{
	m_value = value;
	m_state = 0;
}
