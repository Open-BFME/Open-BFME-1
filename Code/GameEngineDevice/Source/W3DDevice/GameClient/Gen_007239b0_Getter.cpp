// cl: /DNDEBUG /MD /EHsc

// Retail 0x007239B0. Unidentified thiscall byte getter at +0x273.

class Gen_007239b0
{
public:
	unsigned char get(void) const;

private:
	unsigned char m_pad[0x273];
	unsigned char m_value;
};

// ?get@Gen_007239b0@@QBEEXZ
unsigned char Gen_007239b0::get(void) const
{
	return m_value;
}
