// cl: /O2 /Ob0

class Rva001DD090
{
	char m_lead[8];
	unsigned short m_value;
	unsigned char m_flag;

public:
	unsigned get();
};

unsigned Rva001DD090::get()
{
	unsigned value = m_value;
	if (!m_flag)
		value = ~value;
	return value;
}
