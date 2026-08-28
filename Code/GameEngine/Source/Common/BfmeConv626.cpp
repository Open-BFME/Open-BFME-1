class BfmeThingCNE
{
public:
	virtual void bfmeSpareCNE0();
	virtual void bfmeSpareCNE1();
	virtual void bfmeSpareCNE2();
	virtual void bfmeSpareCNE3();
	virtual void bfmeSpareCNE4();
	virtual void bfmeSpareCNE5();
	virtual void bfmeSpareCNE6();
	virtual void bfmeSpareCNE7();
	virtual void bfmeSpareCNE8();
	virtual void bfmeSpareCNE9();
	virtual void bfmeSpareCNE10();
	virtual void bfmeSpareCNE11();
	virtual void bfmeSpareCNE12();
	virtual void bfmeSpareCNE13();
	virtual void bfmeSpareCNE14();
	virtual void bfmeSpareCNE15();
	virtual void bfmeSpareCNE16();
	virtual void bfmeSpareCNE17();
	virtual void bfmeSpareCNE18();
	virtual void bfmeSpareCNE19();
	virtual void bfmeSpareCNE20();
	virtual void bfmeRunCNE(void *what);
	void bfmeGoCNE(void *what);
	unsigned char m_bfmeGap[0x90];
	unsigned int m_bfmeFlags;
	unsigned char m_bfmeGap2[0x1a4];
	void *m_bfmeCur;
};

void __stdcall bfmeLogCNE(int code, int level);

void BfmeThingCNE::bfmeGoCNE(void *what)
{
	if (what == 0)
		return;
	if (m_bfmeFlags & 0x20000000)
		return;
	if (what == m_bfmeCur)
		return;
	bfmeLogCNE(0x3d, 1);
	bfmeRunCNE(what);
}
