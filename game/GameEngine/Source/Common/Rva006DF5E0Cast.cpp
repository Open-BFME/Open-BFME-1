// cl: /O2 /Ob0

class Rva006DF5E0
{
	char m_lead[0x18];
	unsigned char m_value;

public:
	float get();
};

float Rva006DF5E0::get()
{
	return (float)m_value;
}
