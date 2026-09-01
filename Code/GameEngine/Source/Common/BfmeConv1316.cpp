// Open-BFME5 conversions.

extern char g_bfmeInfoTKB[];
extern void *g_bfmeVftTKB[];

void __stdcall bfmeRegisterTKB(void *info);

class BfmeThingTKB
{
public:
	BfmeThingTKB();
	void *m_bfmeVft;
};

BfmeThingTKB::BfmeThingTKB()
{
	bfmeRegisterTKB(g_bfmeInfoTKB);
	m_bfmeVft = g_bfmeVftTKB;
}

void bfmeStepTKD(double d, int a);

void bfmeGoTKD(double d, int a)
{
	bfmeStepTKD(d, a);
}
