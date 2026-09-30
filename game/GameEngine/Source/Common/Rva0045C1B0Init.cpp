// cl: /O2 /Ob0

extern "C" const void *bfmeVftSnapshot[];
#pragma comment(linker, "/alternatename:_bfmeVftSnapshot=??_7Snapshot@@6B@")

class Rva0045C1B0
{
	unsigned m_vt;
	int m_zero;

public:
	void apply();
};

void Rva0045C1B0::apply()
{
	m_zero = 0;
	m_vt = (unsigned)bfmeVftSnapshot;
}
