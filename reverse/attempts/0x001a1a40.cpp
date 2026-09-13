// ??0Rva001A1A40@@QAE@H@Z
// partial score=0.8 date=2026-09-12
// cl: /O2 /Ob0

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva001A1A40
{
public:
	Rva001A1A40(int value);

private:
	int m_0;
	int m_4;
	int m_8;
	int m_c;
	int m_10;
	int m_14;
	unsigned char m_18;
	unsigned char m_19[3];
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	unsigned char m_2c;
	unsigned char m_2d;
	unsigned short m_2e;
};

Rva001A1A40::Rva001A1A40(int value)
{
	m_10 = value;
	_ReadWriteBarrier();
	m_c = 0;
	m_14 = 0;
	m_18 = 0;
	m_28 = 1;
	m_2c = 1;
	m_2d = 1;
	m_2e = 0xffff;
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}
