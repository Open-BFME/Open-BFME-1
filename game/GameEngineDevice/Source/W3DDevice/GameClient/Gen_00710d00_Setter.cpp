// cl: /DNDEBUG /MD /EHsc

// Retail 0x00710D00. Unidentified thiscall dword setter at +0x134.

class Gen_00710d00
{
public:
	void set(int v);

private:
	unsigned char m_pad[0x134];
	int m_value;
};

// ?set@Gen_00710d00@@QAEXH@Z
void Gen_00710d00::set(int v)
{
	m_value = v;
}
