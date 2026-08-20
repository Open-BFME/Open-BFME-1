// cl: /DNDEBUG /MD /EHsc

// Retail 0x006E9530. Unidentified thiscall byte getter at +0xD4.

class Gen_006e9530
{
public:
	unsigned char get(void) const;

private:
	unsigned char m_pad[0xD4];
	unsigned char m_value;
};

// ?get@Gen_006e9530@@QBEEXZ
unsigned char Gen_006e9530::get(void) const
{
	return m_value;
}
