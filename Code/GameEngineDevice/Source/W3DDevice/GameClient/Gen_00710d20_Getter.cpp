// cl: /DNDEBUG /MD /EHsc

// Retail 0x00710D20. Unidentified thiscall dword getter at +0xF0.

class Gen_00710d20
{
public:
	int get(void) const;

private:
	unsigned char m_pad[0xF0];
	int m_value;
};

// ?get@Gen_00710d20@@QBEHXZ
int Gen_00710d20::get(void) const
{
	return m_value;
}
