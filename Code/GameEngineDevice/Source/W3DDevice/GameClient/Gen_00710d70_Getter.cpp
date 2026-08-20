// cl: /DNDEBUG /MD /EHsc

// Retail 0x00710D70. Unidentified thiscall byte getter at +0xC4.

class Gen_00710d70
{
public:
	unsigned char get(void) const;

private:
	unsigned char m_pad[0xC4];
	unsigned char m_value;
};

// ?get@Gen_00710d70@@QBEEXZ
unsigned char Gen_00710d70::get(void) const
{
	return m_value;
}
