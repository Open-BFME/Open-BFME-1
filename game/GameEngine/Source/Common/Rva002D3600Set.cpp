// cl: /O2 /Ob0

class Rva002D3600
{
	unsigned m_00;

public:
	void set(unsigned, unsigned a, unsigned b);
};

void Rva002D3600::set(unsigned, unsigned a, unsigned b)
{
	m_00 = (1u << (a & 31)) | (1u << (b & 31));
}
