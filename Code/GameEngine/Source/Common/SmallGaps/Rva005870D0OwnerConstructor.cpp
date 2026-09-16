// ??0Rva005870D0Owner@@QAE@HHHHHHH@Z
// Retail RVA 0x005870D0 has a seven-int constructor ABI, no calls, and a 79-byte boundary.
// The address-derived class name preserves the proven boundary without claiming an owner.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva005870D0Owner
{
public:
	Rva005870D0Owner(int a, int b, int c, int d, int e, int f, int g);

	int m_000;
	int m_004;
	int m_008;
	int m_00C;
	int m_010;
	int m_014;
	int m_018;
	int m_01C;
	int m_020;
	unsigned char m_024;
	int m_028;
	int m_02C;
	int m_030;
	int m_034;
	int m_038;
};

Rva005870D0Owner::Rva005870D0Owner(int a, int b, int c, int d, int e, int f,
	int g)
{
	m_000 = a;
	m_004 = b;
	m_008 = c;
	m_00C = d;
	_ReadWriteBarrier();
	m_010 = 0;
	m_014 = 0;
	m_018 = 0;
	m_01C = 0;
	m_020 = e;
	m_024 = 0;
	m_028 = 0;
	m_02C = 0;
	m_030 = 0;
	m_034 = f;
	m_038 = g;
}
