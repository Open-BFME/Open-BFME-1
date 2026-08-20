// cl: /DNDEBUG /MD /EHsc

// Retail 0x00710CF0. Unidentified thiscall byte getter at +0x18F4.

class Gen_00710cf0
{
public:
	unsigned char get(void) const;

private:
	unsigned char m_pad[0x18F4];
	unsigned char m_value;
};

// ?get@Gen_00710cf0@@QBEEXZ
unsigned char Gen_00710cf0::get(void) const
{
	return m_value;
}
