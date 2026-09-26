// cl: /O2 /Ob0

class Rva001E0D60
{
	char m_lead[0x530];
	unsigned char m_value;

public:
	float get();
};

float Rva001E0D60::get()
{
	return (float)m_value;
}
