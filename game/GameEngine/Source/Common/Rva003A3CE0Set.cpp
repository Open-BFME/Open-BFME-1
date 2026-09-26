// cl: /O2 /Ob0

class Rva003A3CE0
{
	char m_lead[0x20];
	float m_value;

public:
	void set(float value);
};

void Rva003A3CE0::set(float value)
{
	m_value = value * (1.0f / 6.0f);
}
