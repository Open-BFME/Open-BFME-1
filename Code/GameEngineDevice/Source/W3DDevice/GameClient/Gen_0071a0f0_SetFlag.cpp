// cl: /DNDEBUG /MD /EHsc

// Retail 0x0071A0F0. m_28 = (v != 0) ? 4 : 0.

class Gen_0071a0f0
{
public:
	void set(unsigned char v);

private:
	unsigned char m_pad[0x28];
	int m_28;
};

// ?set@Gen_0071a0f0@@QAEXE@Z
void Gen_0071a0f0::set(unsigned char v)
{
	m_28 = v ? 4 : 0;
}
