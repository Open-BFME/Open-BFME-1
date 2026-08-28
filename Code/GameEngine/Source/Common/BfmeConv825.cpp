
extern "C" const float bfmeConst1075350;

class BfmeBaseDF9
{
public:
	virtual void v0();
	virtual bool vfn1(void *a, void *b);
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void vfn6(void *a, void *b_sub38);
	unsigned char pad[0x58 - 4];
	float m_f58;
	void handleMatch(void *a, void *b);
	void checkAndDispatch(void *a, void *b);
};

void BfmeBaseDF9::checkAndDispatch(void *a, void *b)
{
	if (vfn1(a, b)) {
		handleMatch(a, b);
	}
	if (m_f58 > bfmeConst1075350) {
		vfn6(a, (char*)b + 0x38);
	}
}

class BfmeBaseD33
{
public:
	virtual void v0();
	virtual bool vfn1(void *a, void *b);
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void vfn6(void *a, void *b_sub38);
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void vfn13(void *a, void *b);
	unsigned char pad[0x5c - 4];
	float m_f5c;
	void checkAndDispatch(void *a, void *b);
};

void BfmeBaseD33::checkAndDispatch(void *a, void *b)
{
	if (b) {
		if (vfn1(a, b)) {
			vfn13(a, b);
		}
		if (m_f5c > bfmeConst1075350) {
			vfn6(a, (char*)b + 0x38);
		}
	}
}

class BfmeSub30_7F0
{
public:
	unsigned char pad[0x40];
	char m_flag40;
	void step1();
	void step2(void *arg);
	void notify(int a, int b);
};

struct BfmeThing7F0
{
	unsigned char pad[0x30];
	BfmeSub30_7F0 *m_sub30;
	void doUpdate(void *arg);
};

void BfmeThing7F0::doUpdate(void *arg)
{
	char old = m_sub30->m_flag40;
	m_sub30->m_flag40 = 0;
	m_sub30->step1();
	m_sub30->step2(arg);
	m_sub30->notify(7, 0x32);
	if (old)
		m_sub30->m_flag40 = 1;
}

class BfmeSubVfn1A6
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void vfn5();
	virtual void v6();
	virtual void v7();
	virtual void vfn8(int code);
	void step1();
	void notify(int code, void *val);
};

struct BfmeThing1A6
{
	unsigned char pad[0x30];
	BfmeSubVfn1A6 *m_sub30;
	unsigned char pad2[0x48 - 0x34];
	void *m_val48;
	void doAction(void *val, void *param2);
};

void BfmeThing1A6::doAction(void *val, void *param2)
{
	if (!val) {
		m_sub30->vfn5();
		m_val48 = param2;
		m_sub30->vfn8(0x2a);
	} else {
		m_sub30->step1();
		m_sub30->notify(0x2a, val);
	}
}
