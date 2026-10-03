// cl: /Od /Gy
// Open-BFME5 conversions.

class BfmeVecV17
{
public:
	void bfmeResizeV17(unsigned n, int v);
};

class BfmeStrVME
{
public:
	void bfmeResizeVME(unsigned n, char c);
};

class BfmeThingSVA
{
public:
	void bfmeOneSVA(int a);
	void bfmeTwoSVA(int a);
};

void BfmeThingSVA::bfmeOneSVA(int a)
{
	char m_bfmeScratch[0x24];
	((BfmeVecV17 *)this)->bfmeResizeV17(a, 0);
}

void BfmeThingSVA::bfmeTwoSVA(int a)
{
	char m_bfmeScratch[0x10];
	((BfmeStrVME *)this)->bfmeResizeVME(a, 0);
}
