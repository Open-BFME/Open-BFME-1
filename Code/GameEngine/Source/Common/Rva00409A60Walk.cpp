// cl: /O2 /Ob0

class BfmeSrc9A
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual bool virt0C();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void virt28(char *);
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void virt78(int *);
};

class BfmeElem9A
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void virt0C(BfmeSrc9A *);
	char m_04[0x40];
};

extern int g_bfmeGlob9A;

class BfmeObj9A
{
public:
	void bfmeGo9A(BfmeSrc9A *src);
	char m_00[4];
	int m_04;
	BfmeElem9A m_arr[1];
};

void BfmeObj9A::bfmeGo9A(BfmeSrc9A *src)
{
	char f[2];
	f[0] = 1;
	f[1] = 1;
	src->virt28(f);
	if (src->virt0C())
		return;
	int n = 6;
	src->virt78(&n);
	g_bfmeGlob9A = m_04;
	for (int i = 0; i < n; i++)
		m_arr[i].virt0C(src);
	g_bfmeGlob9A = 0;
}
