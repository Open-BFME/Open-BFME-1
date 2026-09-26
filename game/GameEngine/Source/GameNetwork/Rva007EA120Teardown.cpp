// cl: /O2
// 0x007EA120: FESL hub teardown -- notify(-205) then release(1) each nested
// service pointer and clear the flag bytes.

class Rva007EA120Rel
{
public:
	virtual void release(int n);
};

class T_007ea120
{
public:
	void notify(void *arg);
	void m();

private:
	char m_pad00[0x0C];
	Rva007EA120Rel *m_0C;
	char m_pad10[0x80];
	char m_90;
	char m_pad91[0x0F];
	char m_A0;
	char m_padA1[0x40];
	char m_E1;
	char m_padE2[0x1F];
	char m_101;
	char m_pad102[0x40];
	char m_142;
	char m_pad143[0xE1];
	int m_224;
	int m_228;
	int m_22C;
	char m_230;
	char m_pad231[3];
	Rva007EA120Rel *m_234;
	Rva007EA120Rel *m_238;
	Rva007EA120Rel *m_23C;
	Rva007EA120Rel *m_240;
	Rva007EA120Rel *m_244;
	char m_pad248[8];
	Rva007EA120Rel *m_250;
	Rva007EA120Rel *m_254;
	char m_pad258[0x10];
	Rva007EA120Rel *m_268;
	Rva007EA120Rel *m_26C;
	char m_pad270[0x10];
	Rva007EA120Rel *m_280;
	Rva007EA120Rel *m_284;
	Rva007EA120Rel *m_288;
	char m_pad28C[0x10];
	Rva007EA120Rel *m_29C;
	Rva007EA120Rel *m_2A0;
	Rva007EA120Rel *m_2A4;
	Rva007EA120Rel *m_2A8;
	char m_2AC;
};

void T_007ea120::m()
{
	int err = -205;
	notify(&err);

	if (m_2A4)
		m_2A4->release(1);
	m_2A4 = 0;
	if (m_2A8)
		m_2A8->release(1);
	m_2A8 = 0;
	if (m_29C)
		m_29C->release(1);
	m_29C = 0;
	if (m_280)
		m_280->release(1);
	m_280 = 0;
	if (m_240)
		m_240->release(1);
	m_240 = 0;
	if (m_23C)
		m_23C->release(1);
	m_23C = 0;
	if (m_238)
		m_238->release(1);
	m_238 = 0;
	if (m_234)
		m_234->release(1);
	m_234 = 0;
	if (m_244)
		m_244->release(1);
	m_244 = 0;
	if (m_254)
		m_254->release(1);
	m_254 = 0;
	if (m_26C)
		m_26C->release(1);
	m_26C = 0;
	if (m_288)
		m_288->release(1);
	m_288 = 0;
	if (m_2A0)
		m_2A0->release(1);
	m_2A0 = 0;
	if (m_284)
		m_284->release(1);
	m_284 = 0;
	if (m_268)
		m_268->release(1);
	m_268 = 0;
	if (m_250)
		m_250->release(1);
	m_250 = 0;
	if (m_0C)
		m_0C->release(1);
	m_0C = 0;

	m_224 = 0;
	m_228 = 0;
	m_22C = 0;
	m_90 = 0;
	m_A0 = 0;
	m_E1 = 0;
	m_101 = 0;
	m_142 = 0;
	m_2AC = 0;
	m_230 = 1;
}
