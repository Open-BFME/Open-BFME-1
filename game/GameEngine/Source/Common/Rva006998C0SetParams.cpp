// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Dual clamp floats + int params; flag +0xc4; stdcall 6x2 refresh.

void __stdcall refreshPair(int a, int b);

class Rva006998C0Owner
{
public:
	void setParams(float a, float b, int c, int d, int e);

	char m_pad0[0x9c];
	float m_f9c; // +0x9c
	char m_pad1[0xac - 0xa0];
	float m_fac; // +0xac
	float m_fb0; // +0xb0
	int m_b4;    // +0xb4
	int m_b8;    // +0xb8
	int m_bc;    // +0xbc
	int m_c0;    // +0xc0
	unsigned char m_c4; // +0xc4
};

void Rva006998C0Owner::setParams(float a, float b, int c, int d, int e)
{
	float va;
	if (a < 0.0f)
		va = 0.0f;
	else if (a > 1.0f)
		va = 1.0f;
	else
		va = a;
	m_fac = va;

	float vb;
	if (b < 0.0f)
		vb = 0.0f;
	else if (b > 1.0f)
		vb = 1.0f;
	else
		vb = b;
	m_fb0 = vb;
	m_f9c = va;

	m_b4 = c;
	m_b8 = d;
	m_bc = e;
	m_c0 = 0;
	m_c4 = 1;

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 2; ++j)
			refreshPair(i, j);
	}
}
