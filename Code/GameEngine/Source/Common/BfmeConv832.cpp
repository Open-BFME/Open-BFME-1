class BfmeMgr418
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void vfn4(int zero);
	virtual void vfn5();
};
extern BfmeMgr418 *g_mgr12F4184;

void bfmeRunMgr418_6D0()
{
	if (g_mgr12F4184) {
		g_mgr12F4184->vfn4(0);
		g_mgr12F4184->vfn5();
	}
}

class BfmeMsgHandler
{
public:
	int defaultHandler(int msg, void *p2, void *p3);
	int checkMsg(int msg, void *p2, void *p3);
};

int BfmeMsgHandler::checkMsg(int msg, void *p2, void *p3)
{
	switch (msg) {
	case 0x4014:
	case 0x4030:
		return 1;
	default:
		return defaultHandler(msg, p2, p3);
	}
}

struct BfmeObj4B5
{
	unsigned char pad[0x59];
	char m_flag59;
};
extern BfmeObj4B5 *g_obj12F4B58;
extern void *g_obj12F495C;

class BfmeMgr19E
{
public:
	int notify();
};
extern BfmeMgr19E *g_mgr12F19E8;

void __stdcall bfmeCheckAndNotify940(void *param)
{
	if (g_obj12F4B58) {
		g_obj12F4B58->m_flag59 = 1;
	}
	if (g_obj12F495C) {
		g_mgr12F19E8->notify();
	}
}

class BfmeSubMap3B3
{
public:
	void** insert(void *key);
};

class BfmeMap3B3
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
	virtual void vfn10(void *val, void *key, int one);
	BfmeSubMap3B3 m_subMap;
	void put(void *val, void *key);
};

void BfmeMap3B3::put(void *val, void *key)
{
	vfn10(val, key, 1);
	void **entry = m_subMap.insert(key);
	*entry = val;
}

void __cdecl bfmeSendEventA11(void *p1, void *p2, void *p3, unsigned int code, int zero);
void __cdecl bfmeSendEventA19(void *p1, void *p2, void *p3, unsigned int code, int zero);

struct BfmeEventSrcA11
{
	void *m_p1;
	void *m_p2;
	unsigned char pad[5];
	unsigned char m_byteD;
	void trigger(void *p3);
	void triggerB(void *p3);
};

void BfmeEventSrcA11::trigger(void *p3)
{
	unsigned char *pByte = this ? &m_byteD : 0;
	unsigned int code = *pByte;
	bfmeSendEventA11(m_p1, m_p2, p3, code, 0);
}

void BfmeEventSrcA11::triggerB(void *p3)
{
	unsigned char *pByte = this ? &m_byteD : 0;
	unsigned int code = *pByte;
	bfmeSendEventA19(m_p1, m_p2, p3, code, 0);
}
