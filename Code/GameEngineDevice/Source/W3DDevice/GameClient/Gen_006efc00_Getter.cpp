// cl: /DNDEBUG /MD /EHsc

// Retail 0x006EFC00. Unidentified thiscall byte getter at +0x178.

class Gen_006efc00
{
public:
	unsigned char get(void) const;

private:
	unsigned char m_pad[0x178];
	unsigned char m_value;
};

// ?get@Gen_006efc00@@QBEEXZ
unsigned char Gen_006efc00::get(void) const
{
	return m_value;
}
