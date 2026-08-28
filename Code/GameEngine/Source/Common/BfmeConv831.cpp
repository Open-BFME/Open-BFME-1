
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
	int findSomething(void *key, int zero);
};
extern BfmeMgrF07 *g_mgr12F076C;

class BfmeLinkedObj
{
public:
	void link(BfmeLinkedObj *other, int zero);
};

class BfmeLinkedObjBE
{
public:
	void notifyOther(BfmeLinkedObjBE *other, void *p3);
};

struct BfmeObjAF0_2
{
	unsigned char pad[0x230];
	void *m_sub230;
};

class BfmeMgrD74_Linked
{
public:
	BfmeLinkedObj* findObj(int id);
	BfmeLinkedObjBE* findObjBE(int id);
	BfmeObjAF0_2* findObjAF(int id);
};
extern BfmeMgrD74_Linked *g_mgr12ED748;

void __stdcall bfmeLinkObjectsA70(void *k1, void *k2)
{
	int id2 = g_mgr12F076C->findSomething(k2, 0);
	int id1 = g_mgr12F076C->findSomething(k1, 0);
	BfmeLinkedObj *obj2 = g_mgr12ED748->findObj(id2);
	BfmeLinkedObj *obj1 = g_mgr12ED748->findObj(id1);
	if (obj2 && obj1) {
		obj2->link(obj1, 0);
	}
}

void __stdcall bfmeNotifyLinkedBE0(void *k1, void *p3, void *k2)
{
	int id2 = g_mgr12F076C->findSomething(k2, 0);
	int id1 = g_mgr12F076C->findSomething(k1, 0);
	BfmeLinkedObjBE *obj2 = (BfmeLinkedObjBE*)g_mgr12ED748->findObj(id2);
	BfmeLinkedObjBE *obj1 = (BfmeLinkedObjBE*)g_mgr12ED748->findObj(id1);
	if (obj2 && obj1) {
		obj1->notifyOther(obj2, p3);
	}
}

class BfmeObjVfnAF0
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
	virtual void vfn20(void *sub);
};

void __cdecl bfmeHelper760(void *obj, int zero);

void __stdcall bfmeAttachSubAF0(void *k1, void *k2)
{
	BfmeObjVfnAF0 *obj1 = (BfmeObjVfnAF0*)g_mgr12F076C->vfn26(k1);
	int id2 = g_mgr12F076C->findSomething(k2, 0);
	BfmeObjAF0_2 *obj2 = (BfmeObjAF0_2*)g_mgr12ED748->findObj(id2);
	if (obj1 && obj2 && obj2->m_sub230) {
		obj1->vfn20(obj2->m_sub230);
		bfmeHelper760(obj1, 0);
	}
}

class BfmeMgr160_D20
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
	virtual bool vfn44(int code);
	virtual void v45();
	virtual bool vfn46(int code);
};
extern BfmeMgr160_D20 *g_mgr12F1600;

void __stdcall bfmeCheckBoolsD20(bool b1, bool b2)
{
	if (g_mgr12F1600->vfn46(2)) {
		int code = b2 ? (b1 ? 11 : 12) : (b1 ? 9 : 10);
		if (!g_mgr12F1600->vfn44(code)) {
			g_mgr12F1600->vfn46(0);
		}
	}
}

class BfmeObj720
{
public:
	unsigned char pad[0x144];
	int m_field144;
};

class BfmeMgr33F
{
public:
	BfmeObj720* findObj(void *key);
};
extern BfmeMgr33F *g_mgr12F33F8;

void __stdcall bfmeCalculateAndStore720(void *key, int val)
{
	BfmeObj720 *obj = g_mgr12F33F8->findObj(key);
	if (obj) {
		int v = (val * 30) / 10;
		if (v % 2 == 1) {
			v++;
		}
		obj->m_field144 = v;
	}
}
