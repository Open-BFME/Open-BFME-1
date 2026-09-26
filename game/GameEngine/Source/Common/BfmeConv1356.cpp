// Open-BFME5 conversions.

__declspec(dllimport) int __stdcall bfmeLockVGP(int *p);
__declspec(dllimport) void __stdcall bfmeReleaseVGP(void *p);
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
	if (bfmeLockVGP(&m_bfme08) == 0)
	{
		if (this)
		{
			if (m_bfme00)
				bfmeReleaseVGP(m_bfme00);
			if (m_bfme04)
				bfmeDelArrVGP(m_bfme04);
			bfmeDelVGP(this);
		}
		return 0;
	}
	return m_bfme08;
}
