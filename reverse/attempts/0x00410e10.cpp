// ?bfmeGo10E@BfmeObj10E@@QAEXHPAUBfmeOut10E@@@Z
// partial score=0.88 date=2026-09-02
// cl: /O2 /Ob0

extern float g_bfmeK10A;
extern float g_bfmeK10B;
extern float g_bfmeK10C;
extern float g_bfmeK10D;

class BfmeU10E;

class BfmeSrc10E
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
	virtual bool virt130();
	virtual void v77();
	virtual void v78();
	virtual void v79();
	virtual void v80();
	virtual void v81();
	virtual void v82();
	virtual void v83();
	virtual BfmeU10E *virt150();
};

class BfmeU10E
{
public:
	char m_00[0x474];
	volatile float m_474;
};

class BfmeHold10E
{
public:
	char m_00[0x204];
	BfmeSrc10E *m_204;
};

struct BfmeOut10E
{
	int m_00;
	float m_04;
};

class BfmeObj10E
{
public:
	void bfmeGo10E(int, BfmeOut10E *out);
	char m_00[0xFC];
	BfmeHold10E *m_FC;
	char m_100[0x3C];
	volatile float m_13C;
};

void BfmeObj10E::bfmeGo10E(int, BfmeOut10E *out)
{
	BfmeHold10E *h = m_FC;
	if (!h)
		return;
	BfmeSrc10E *s = h->m_204;
	if (!s)
		return;
	if (!s->virt130())
		return;
	BfmeU10E *u = s->virt150();
	float t = u->m_474 * g_bfmeK10A;
	float w = m_13C * g_bfmeK10B;
	t = t * g_bfmeK10C + w;
	if (g_bfmeK10D < t && g_bfmeK10B < t)
		t = g_bfmeK10B;
	else if (t < g_bfmeK10D)
		t = g_bfmeK10D;
	m_13C = t;
	out->m_04 = t;
}
