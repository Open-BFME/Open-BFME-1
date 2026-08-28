
class BfmeMgrF14_010
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
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void vfn58();
	void step1(int zero);
	unsigned char pad[0x12b0 - 4];
	char m_flag12B0;
};
extern BfmeMgrF14_010 *g_mgr12F148C;

class BfmeMgr4C5
{
public:
	void step2(int zero);
};
extern BfmeMgr4C5 *g_mgr12F4C5C;

class BfmeSub32A
{
public:
	void step3(int one);
};

class BfmeMgrD5E
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
	virtual BfmeSub32A* vfn13(int id);
};
extern BfmeMgrD5E *g_mgr12ED5EC;

class BfmeMgr33F_010
{
public:
	void step4();
};
extern BfmeMgr33F_010 *g_mgr12F33F8;

class BfmeMgr4C8
{
public:
	void step5();
};
extern BfmeMgr4C8 *g_mgr12F4C84;

void bfmeSequence010()
{
	g_mgr12F148C->step1(0);
	g_mgr12F4C5C->step2(0);
	BfmeSub32A *sub = g_mgr12ED5EC->vfn13(0x3eb);
	sub->step3(1);
	g_mgr12F148C->vfn58();
	g_mgr12F148C->m_flag12B0 = 0;
	g_mgr12F33F8->step4();
	g_mgr12F4C84->step5();
}

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
