// cl: /O2
// 0x007EB270: tear down the FESL singleton at 0x0130A588 then the two
// neighboring global-release helpers gated by 0x0130A58D / 0x0130A58C.

class T_007ea120
{
public:
	virtual void release(int);
	void m();
};

extern T_007ea120 *g_Va0130A588;
extern unsigned char g_Va0130A58D;
extern unsigned char g_Va0130A58C;

void Rva007EB830Release(void);
void Rva007F0060();

void Rva007EB270Shutdown()
{
	T_007ea120 *p = g_Va0130A588;
	if (p)
	{
		p->m();
		p = g_Va0130A588;
		if (p)
			p->release(1);
		g_Va0130A588 = 0;
	}
	if (g_Va0130A58D)
		Rva007EB830Release();
	if (g_Va0130A58C)
		Rva007F0060();
}
