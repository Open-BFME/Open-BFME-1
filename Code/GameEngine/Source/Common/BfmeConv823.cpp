
class BfmeSub58_E80
{
public:
	bool execute(void *b, int zero);
};

struct BfmeThingE80
{
	unsigned char pad[0x58];
	BfmeSub58_E80 m_sub58;
	bool validate(void *a, void *b);
	bool checkAndExecute(void *a, void *b);
};

bool BfmeThingE80::checkAndExecute(void *a, void *b)
{
	if (!validate(a, b))
		return false;
	return m_sub58.execute(b, 0) ? true : false;
}

class BfmeSub58_ACF
{
public:
	bool run(void *b, void *a);
};

struct BfmeThingACF
{
	unsigned char pad[0x58];
	BfmeSub58_ACF *m_sub58;
	bool validate(void *a, void *b);
	bool checkAndRun(void *a, void *b);
};

bool BfmeThingACF::checkAndRun(void *a, void *b)
{
	if (validate(a, b) && m_sub58)
		return m_sub58->run(b, a);
	return false;
}

struct BfmeSub8_3E0
{
	unsigned char pad[0x90];
	int m_flags90;
};

class BfmeThing3E0
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
	virtual void vfn21(BfmeSub8_3E0 *obj);
	virtual void v22();
	virtual void vfn23(BfmeSub8_3E0 *obj);
	void *m_sub4;
	BfmeSub8_3E0 *m_obj8;
	unsigned char pad2[0x24 - 0xc];
	int m_mode24;
	void doInit();
	void process();
};

void BfmeThing3E0::process()
{
	doInit();
	void *sub = m_sub4;
	BfmeSub8_3E0 *obj = m_obj8;
	if (sub && m_mode24 == 1) {
		if (obj->m_flags90 & 0x10000)
			vfn21(obj);
		else
			vfn23(obj);
	}
}

class BfmeSubEntry960
{
public:
	int lookup(int *arg1, void **arg2);
};

struct BfmeThing960
{
	unsigned char pad[0x1e8];
	BfmeSubEntry960 *m_entries1E8[16];
	int getResult(int index);
};

int BfmeThing960::getResult(int index)
{
	BfmeSubEntry960 *entry = m_entries1E8[index];
	void *local[3];
	if (entry) {
		if (entry->lookup(&index, local) == 1)
			return index;
	}
	return 0;
}
