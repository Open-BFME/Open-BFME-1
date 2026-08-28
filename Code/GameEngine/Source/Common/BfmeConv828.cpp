
class BfmeMgr089_152
{
public:
	void reset();
};
extern BfmeMgr089_152 *g_mgr12F0898;

struct BfmeObj1024
{
	unsigned char pad[0x1d];
	char m_flag1D;
};
extern BfmeObj1024 *g_obj12F1024;

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
	virtual void vfn13();
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

struct BfmeThing152
{
	unsigned char pad[8];
	char m_flag8;
	void clear();
	void resetAll();
};

void BfmeThing152::resetAll()
{
	m_flag8 = 0;
	g_mgr12F0898->reset();
	clear();
	g_obj12F1024->m_flag1D = 1;
	g_mgr12F076C->vfn13();
}

struct BfmeCoord12
{
	float x, y, z;
};

class BfmeMgr160
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
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void vfn69(BfmeCoord12 *out);
	virtual void v70();
	virtual void v71();
	virtual void v72();
	virtual void v73();
	virtual void v74();
	virtual void v75();
	virtual void v76();
	virtual void v77();
	virtual void v78();
	virtual void v79();
	virtual void v80();
	virtual void v81();
	virtual void v82();
	virtual void v83();
	virtual void v84();
	virtual void v85();
	virtual void v86();
	virtual void v87();
	virtual void v88();
	virtual void v89();
	virtual void v90();
	virtual void v91();
	virtual void v92();
	virtual void v93();
	virtual void v94();
	virtual void v95();
	virtual void v96();
	virtual void v97();
	virtual void v98();
	virtual void v99();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void vfn106(BfmeCoord12 *pos, void *param);
};
extern BfmeMgr160 *g_mgr12F1600;

void __stdcall bfmeUpdatePosD70(void *param)
{
	BfmeCoord12 pos;
	g_mgr12F1600->vfn69(&pos);
	g_mgr12F1600->vfn106(&pos, param);
}

struct BfmeInfoE10
{
	unsigned char pad[8];
	int m_count;
};

class BfmeObjE10
{
public:
	void actionA(int code);
	void actionB(int code);
};

void __stdcall bfmeLookupAndActionE10(void *key, BfmeInfoE10 *info)
{
	BfmeObjE10 *obj = (BfmeObjE10*)g_mgr12F076C->vfn26(key);
	if (obj) {
		if (info->m_count > 0) {
			obj->actionA(0x17);
		} else {
			obj->actionB(0x17);
		}
	}
}

class BfmeSubVfn9E0
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
	virtual void vfn21();
};

class BfmeObj9E0
{
public:
	BfmeSubVfn9E0* findSub(int code);
};

void __stdcall bfmeLookupAndRun9E0(void *key)
{
	BfmeObj9E0 *obj = (BfmeObj9E0*)g_mgr12F076C->vfn26(key);
	if (obj) {
		BfmeSubVfn9E0 *sub = obj->findSub(0x2e);
		if (sub) {
			sub->vfn21();
		}
	}
}

struct BfmeNode2B0
{
	unsigned char pad[4];
	void *m_val4;
};

class BfmeMgr2B0
{
public:
	BfmeNode2B0* lookupByField(void *field10);
	void forwardVal(void *val4);
};

struct BfmeArg2B0
{
	unsigned char pad[0x10];
	unsigned char m_field10[1];
};

void __stdcall bfmeLookupAndForward2B0(BfmeArg2B0 *arg)
{
	BfmeNode2B0 *node = ((BfmeMgr2B0*)g_mgr12F0898)->lookupByField(&arg->m_field10);
	if (node) {
		((BfmeMgr2B0*)g_mgr12F0898)->forwardVal(node->m_val4);
	}
}
