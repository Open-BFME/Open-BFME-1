// cl: /DNDEBUG /MD /EHsc

// Retail 0x00725B20. Unidentified thiscall float getter at +0x170C4.

class Gen_00725b20
{
public:
	float get(void) const;

private:
	unsigned char m_pad[0x170C4];
	float m_value;
};

// ?get@Gen_00725b20@@QBEMXZ
float Gen_00725b20::get(void) const
{
	return m_value;
}
