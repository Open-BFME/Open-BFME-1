// cl: /DNDEBUG /MD /EHsc

// Retail 0x00727030. Store 4 or 0 at +0x28 from a bool argument.

class Gen_00727030
{
public:
	void set(bool on);

private:
	unsigned char m_pad[0x28];
	int m_value;
};

// ?set@Gen_00727030@@QAEX_N@Z
void Gen_00727030::set(bool on)
{
	m_value = on ? 4 : 0;
}
