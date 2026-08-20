// cl: /DNDEBUG /MD /EHsc

// Retail 0x00710D30. Unidentified thiscall float getter at +0x2E4.

class Gen_00710d30
{
public:
	float get(void) const;

private:
	unsigned char m_pad[0x2E4];
	float m_value;
};

// ?get@Gen_00710d30@@QBEMXZ
float Gen_00710d30::get(void) const
{
	return m_value;
}
