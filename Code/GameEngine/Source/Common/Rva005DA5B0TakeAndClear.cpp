// Retail 0x005DA5B0 is a nine-byte load-and-clear helper reached through the
// generated thunk at ILT 0x000219BD.  No caller proves a semantic owner, so
// the address-derived class records the first field and its reset behavior.

class Rva005DA5B0
{
public:
	int take( void );

private:
	int m_value;
};

int Rva005DA5B0::take( void )
{
	int old_value = m_value;
	m_value = 0;
	return old_value;
}
