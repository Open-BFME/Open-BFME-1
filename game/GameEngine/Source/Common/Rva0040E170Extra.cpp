// cl: /O2 /Ob0

extern float g_bfmeDefaultBU;

class BfmeElemVMZ
{
public:
	void bfmeTailVMZ(void *self, int a0, int a2, int a3, int a4, int a5, int k);
	int m_a0;
	float m_f0;
	float m_f1;
	float m_f2;
	float m_f3;
	int m_k;
};

class BfmeThingE170
{
public:
	void bfmeGo3E170(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
	char m_pad[0x64];
	BfmeElemVMZ m_arr[3];
	char m_ac[0x60];
	int m_10C;
	int m_110;
	int m_114;
	float m_118;
	float m_11C;
	BfmeElemVMZ m_extra;
};

void BfmeThingE170::bfmeGo3E170(int a0, int a1, int a2, int a3, int a4, int a5, int a6)
{
	m_extra.bfmeTailVMZ(this, a0, a1, a2, a3, a4, 1);
	float f = g_bfmeDefaultBU / (float)a6;
	m_10C = a5;
	m_114 = a6;
	m_11C = 1.0f;
	m_118 = f;
}
