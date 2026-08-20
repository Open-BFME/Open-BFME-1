// cl: /DNDEBUG /MD /EHsc

// Retail 0x00732480. Unidentified thiscall float getter at +0x18F8.

class Gen_00732480
{
public:
	float get(void) const;

private:
	unsigned char m_pad[0x18F8];
	float m_value;
};

// ?get@Gen_00732480@@QBEMXZ
float Gen_00732480::get(void) const
{
	return m_value;
}
