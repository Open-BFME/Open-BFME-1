// cl: /DNDEBUG /MD /EHsc

// Retail 0x00710CE0. Unidentified thiscall dword getter at +0x330.

class Gen_00710ce0
{
public:
	int get(void) const;

private:
	unsigned char m_pad[0x330];
	int m_value;
};

// ?get@Gen_00710ce0@@QBEHXZ
int Gen_00710ce0::get(void) const
{
	return m_value;
}
