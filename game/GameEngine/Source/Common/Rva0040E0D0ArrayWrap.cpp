// cl: /O2 /Ob0

class BfmeSrcVMZ
{
public:
	virtual int v0();
	virtual int v1();
	virtual int v2();
	virtual int v3();
	virtual int v4();
	virtual int v5();
	virtual int v6();
	virtual int v7();
	virtual int v8();
	virtual int v9();
	virtual int v10();
	virtual unsigned v11();
	virtual unsigned v12();
};

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

class BfmeThingVMZ
{
public:
	void bfmeGo1VMZ(int a0, int i, int a2, int a3, int a4, int a5);
	void bfmeGo2VMZ(int a0, int i, int a2, int a3, int a4, int a5);
	char m_pad[0x64];
	BfmeElemVMZ m_arr[3];
};

void BfmeThingVMZ::bfmeGo1VMZ(int a0, int i, int a2, int a3, int a4, int a5)
{
	if (i < 3)
		m_arr[i].bfmeTailVMZ(this, a0, a2, a3, a4, a5, 1);
}

void BfmeThingVMZ::bfmeGo2VMZ(int a0, int i, int a2, int a3, int a4, int a5)
{
	if (i < 3)
		m_arr[i].bfmeTailVMZ(this, a0, a2, a3, a4, a5, 2);
}

void BfmeElemVMZ::bfmeTailVMZ(void *self, int a0, int a2, int a3, int a4, int a5, int k)
{
	BfmeSrcVMZ *o = (BfmeSrcVMZ *)self;
	m_a0 = a0;
	m_f0 = (float)o->v11() * *(float *)&a2;
	m_f1 = (float)o->v12() * *(float *)&a3;
	m_f2 = (float)o->v11() * *(float *)&a4;
	m_f3 = (float)o->v12() * *(float *)&a5;
	m_k = k;
}
