
class BfmeObjE65
{
public:
	void sendSignal(int code, int zero);
};

class BfmeMgr089_E5E
{
public:
	void forwardObj(void *obj);
};
extern BfmeMgr089_E5E *g_mgr12F0898;

class BfmeObjE61
{
public:
	void action4(void *p2, void *p3, void *p4, void *p5);
};

class BfmeObjNotify3F0
{
public:
	void notify(void *param, int flag);
};

class BfmeMgrD74
{
public:
	BfmeObjNotify3F0* getNext(short *pIter);
};
extern BfmeMgrD74 *g_mgr12ED748;

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

void __stdcall bfmeLookupAndSend650(void *key)
{
	BfmeObjE65 *obj = (BfmeObjE65*)g_mgr12F076C->vfn26(key);
	if (obj) {
		obj->sendSignal(8, 0);
	}
}

void __stdcall bfmeLookupAndForward5E0(void *key)
{
	void *obj = g_mgr12F076C->vfn26(key);
	if (obj) {
		g_mgr12F0898->forwardObj(obj);
	}
}

void __stdcall bfmeLookupAndAction610(void *key, void *p2, void *p3, void *p4, void *p5)
{
	BfmeObjE61 *obj = (BfmeObjE61*)g_mgr12F076C->vfn26(key);
	if (obj) {
		obj->action4(p2, p3, p4, p5);
	}
}

void __stdcall bfmeIterateAndNotify3F0(void *key, void *param)
{
	key = (void*)g_mgr12F076C->findSomething(key, 0);
	if ((unsigned short)(int)key != 0) {
		do {
			BfmeObjNotify3F0 *obj = g_mgr12ED748->getNext((short*)&key);
			if (obj) {
				obj->notify(param, 0);
			}
		} while (*(short*)&key != 0);
	}
}

void __stdcall bfmeIterateAndNotify510(void *key, void *param)
{
	key = (void*)g_mgr12F076C->findSomething(key, 0);
	if ((unsigned short)(int)key != 0) {
		do {
			BfmeObjNotify3F0 *obj = g_mgr12ED748->getNext((short*)&key);
			if (obj) {
				obj->notify(param, 1);
			}
		} while (*(short*)&key != 0);
	}
}
