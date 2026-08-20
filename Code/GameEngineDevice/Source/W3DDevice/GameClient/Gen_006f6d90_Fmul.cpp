// cl: /DNDEBUG /MD /EHsc

// Retail 0x006F6D90. return m_B4 * m_B0.

class Gen_006f6d90
{
public:
	float product(void) const;

private:
	unsigned char m_pad[0xB0];
	float m_b0;
	float m_b4;
};

// ?product@Gen_006f6d90@@QBEMXZ
float Gen_006f6d90::product(void) const
{
	return m_b4 * m_b0;
}
