// cl: /O2 /MD /EHs-c-

class Rva00881BE0Class
{
public:
	unsigned char m_value;
	int m_state;

	void update( int amount, bool absolute );
};

void Rva00881BE0Class::update( int amount, bool absolute )
{
	if ( !absolute )
	{
		amount += m_value;
	}

	if ( amount < 0 )
	{
		amount = 0;
	}
	else if ( amount > 255 )
	{
		amount = 255;
	}

	m_value = (unsigned char)amount;

	if ( m_value == 128 )
	{
		m_state = 0;
	}
	else
	{
		m_state = (m_value > 128) ? 1 : 2;
	}
}
