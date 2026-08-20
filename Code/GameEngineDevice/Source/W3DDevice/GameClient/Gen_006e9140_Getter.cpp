// cl: /DNDEBUG /MD /EHsc

// Retail 0x006E9140. Unidentified thiscall float getter at +0x17C.

class Gen_006e9140
{
public:
	float get(void) const;

private:
	unsigned char m_pad[0x17C];
	float m_value;
};

// ?get@Gen_006e9140@@QBEMXZ
float Gen_006e9140::get(void) const
{
	return m_value;
}
