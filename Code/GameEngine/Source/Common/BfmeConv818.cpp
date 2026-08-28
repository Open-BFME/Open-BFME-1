
class BfmeSubED8
{
public:
	void process(void *val);
};

struct BfmeArgED8
{
	unsigned char pad[0x74];
	void *val74;
};

struct BfmeThingED8
{
	unsigned char pad[0x204];
	BfmeSubED8 sub;
	void doProcess(BfmeArgED8 *arg);
};

void BfmeThingED8::doProcess(BfmeArgED8 *arg)
{
	sub.process(arg->val74);
}

class BfmeSubD4C
{
public:
	bool fallback();
};

struct BfmeSub4_D4C
{
	unsigned char pad[0x25c];
	char m_flag25C;
};

struct BfmeThingD4C
{
	unsigned char pad[4];
	BfmeSub4_D4C *m_sub4;
	unsigned char pad2[0x24 - 0x8];
	int m_mode24;
	bool checkCondition();
};

bool BfmeThingD4C::checkCondition()
{
	if (m_sub4->m_flag25C && m_mode24 == 2)
		return false;
	return ((BfmeSubD4C*)this)->fallback();
}

class BfmeSub1CC_EC3
{
public:
	float query(void *val);
};

extern "C" const float bfmeConst1075350;

struct BfmeThingEC3
{
	unsigned char pad[8];
	void *m_val8;
	unsigned char pad2[0x1cc - 0xc];
	BfmeSub1CC_EC3 *m_sub1CC;
	float getVal();
};

float BfmeThingEC3::getVal()
{
	if (m_sub1CC)
		return m_sub1CC->query(m_val8);
	return bfmeConst1075350;
}

struct BfmeGlobalMgr12F0898
{
	unsigned char pad[0x3c];
	int m_frame3C;
};

extern BfmeGlobalMgr12F0898 *g_bfmeMgr12F0898;

struct BfmeSubDE0
{
	unsigned char pad[0x254];
	int m_val254;
};

struct BfmeThingDE0
{
	unsigned char pad[4];
	BfmeSubDE0 *m_sub4;
	unsigned char pad2[0x24];
	int m_val2C;
	void doInit();
	void updateFrame();
};

void BfmeThingDE0::updateFrame()
{
	doInit();
	m_val2C = m_sub4->m_val254 + g_bfmeMgr12F0898->m_frame3C;
}

class BfmeThingF9D
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
	virtual void v69();
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
	virtual char vfn_180();
	unsigned char pad[0x1f8];
	int m_frame1FC;
	unsigned char pad2[0x32a - 0x200];
	char m_flag32A;
	void checkAndMark();
};

void BfmeThingF9D::checkAndMark()
{
	if (vfn_180()) {
		m_frame1FC = g_bfmeMgr12F0898->m_frame3C;
		m_flag32A = 1;
	}
}
