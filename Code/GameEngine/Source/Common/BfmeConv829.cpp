
class BfmeMgrF07
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
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
	virtual void* vfn26(void *key);
};
extern BfmeMgrF07 *g_mgr12F076C;

class BfmeSub210_4B0
{
public:
	void apply(float val, int one);
};

struct BfmeObj4B0
{
	unsigned char pad[0x210];
	BfmeSub210_4B0 *m_sub210;
};

void __stdcall bfmeApplyIntAsFloat4B0(void *key, int intArg)
{
	BfmeObj4B0 *obj = (BfmeObj4B0*)g_mgr12F076C->vfn26(key);
	if (obj && obj->m_sub210) {
		obj->m_sub210->apply((float)intArg, 1);
	}
}

void __cdecl bfmeStep1_250(void *arg);
void __cdecl bfmeStep2_250(void *arg);
void __cdecl bfmeStep3_250(void *arg);
void __cdecl bfmeStep4_250(void *arg);

void __cdecl bfmeCallAll250(void *arg)
{
	bfmeStep1_250(arg);
	bfmeStep2_250(arg);
	bfmeStep3_250(arg);
	bfmeStep4_250(arg);
}

struct BfmeThing79B
{
	void *m_val0;
	unsigned char pad[0x48 - 4];
	void *m_field48;
};

void __cdecl bfmeTarget861210(void *val0, void *b, const char *c);

void __cdecl bfmeForwardIfValid79B(BfmeThing79B *a, void *b, const char *c)
{
	if (a->m_field48 && c && *c) {
		bfmeTarget861210(a->m_val0, b, c);
	}
}

typedef void (__stdcall *ProcessValFn)(int val);
extern ProcessValFn g_processVal13596B8;

struct BfmeThingDA0
{
	unsigned char pad[0xb4c];
	int m_fieldB4C;
	int m_fieldB50;
	void step();
};

void BfmeThingDA0::step()
{
	if (m_fieldB50 <= 0 && m_fieldB4C != -1) {
		g_processVal13596B8(m_fieldB4C);
	}
	++m_fieldB50;
}

struct BfmeStr4BE
{
	char m_buf[1];
	void freeStr();
};

class BfmeFreeHelper
{
public:
	__declspec(dllimport) void doFree();
};

void BfmeStr4BE::freeStr()
{
	if (m_buf[0]) {
		((BfmeFreeHelper*)this)->doFree();
	}
}
