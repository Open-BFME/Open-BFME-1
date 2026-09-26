// cl: /DNDEBUG /MD /EHsc

// Retail 0x006FD030. m_E8 = -g; if (v) m_E8 = -1.0f.

float g_006fd030;

class Gen_006fd030
{
public:
	void set(unsigned char v);

private:
	unsigned char m_pad[0xE8];
	float m_e8;
};

// ?set@Gen_006fd030@@QAEXE@Z
void Gen_006fd030::set(unsigned char v)
{
	m_e8 = -g_006fd030;
	if (v)
		m_e8 = -1.0f;
}
