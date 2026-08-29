// Open-BFME5 conversions.

struct BfmeO1145;

struct BfmeT1145
{
	char m_bfmePad[0x104];
	void (__stdcall *m_bfme104)(BfmeO1145 *o, int a, int b);
	char m_bfmePad2[0xa4];
	void (__stdcall *m_bfme1ac)(BfmeO1145 *o, int a);
};

struct BfmeO1145
{
	BfmeT1145 *m_bfmeTbl;
};

extern "C" BfmeO1145 *volatile g_bfmeO1145;
extern "C" void __cdecl bfmeTail1145(void);

void bfmeGo1145(void)
{
	BfmeO1145 *o;

	o = g_bfmeO1145;
	o->m_bfmeTbl->m_bfme104(o, 0, 0);
	o = g_bfmeO1145;
	o->m_bfmeTbl->m_bfme104(o, 1, 0);
	o = g_bfmeO1145;
	o->m_bfmeTbl->m_bfme104(o, 2, 0);
	o = g_bfmeO1145;
	o->m_bfmeTbl->m_bfme104(o, 3, 0);
	o = g_bfmeO1145;
	o->m_bfmeTbl->m_bfme104(o, 4, 0);
	o = g_bfmeO1145;
	o->m_bfmeTbl->m_bfme1ac(o, 0);
	bfmeTail1145();
}
