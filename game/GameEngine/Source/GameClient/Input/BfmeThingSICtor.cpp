// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ??0BfmeThingSI@@QAE@XZ
// Derived from Mouse: base ctor, then vptr, 0x1000-byte clear at +0x4E14,
// three dwords, a 0x640-byte global fill, then +0x5E20/+0x5E24.

#include <string.h>

#pragma intrinsic(memset)

class Mouse
{
public:
	Mouse();
	virtual ~Mouse();

private:
	char m_pad[0x4E14 - 4];
};

extern "C" int g_bfmeSITable[0x190];

class BfmeThingSI : public Mouse
{
public:
	BfmeThingSI();

private:
	int m_buf[0x400];
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	char m_e;
};

BfmeThingSI::BfmeThingSI()
{
	memset(m_buf, 0, sizeof(m_buf));
	m_a = 0;
	m_b = 0;
	m_c = 0;
	memset(g_bfmeSITable, 0, sizeof(g_bfmeSITable));
	m_d = 0;
	m_e = 0;
}
