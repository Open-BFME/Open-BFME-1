// cl: /DNDEBUG /MD /EHsc

// Retail 0x00725B30. Unidentified thiscall byte getter at +0x170B8.

class Gen_00725b30
{
public:
	unsigned char get(void) const;

private:
	unsigned char m_pad[0x170B8];
	unsigned char m_value;
};

// ?get@Gen_00725b30@@QBEEXZ
unsigned char Gen_00725b30::get(void) const
{
	return m_value;
}
