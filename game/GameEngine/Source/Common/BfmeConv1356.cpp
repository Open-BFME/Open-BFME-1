// Open-BFME5 conversions.

extern "C" __declspec(dllimport) int __stdcall InterlockedDecrement(int *p);
extern "C" __declspec(dllimport) void __stdcall SysFreeString(void *p);
void __cdecl bfmeDelArrVGP(void *p);
void __cdecl bfmeDelVGP(void *p);

class BfmeThingVGP
{
public:
	int bfmeGoVGP();
	void *m_bfme00;
	void *m_bfme04;
	int m_bfme08;
};

int BfmeThingVGP::bfmeGoVGP()
{
	if (InterlockedDecrement(&m_bfme08) == 0)
	{
		if (this)
		{
			if (m_bfme00)
				SysFreeString(m_bfme00);
			if (m_bfme04)
				bfmeDelArrVGP(m_bfme04);
			bfmeDelVGP(this);
		}
		return 0;
	}
	return m_bfme08;
}
