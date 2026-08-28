
class BfmeSub2B8_112
{
public:
	void send(void *a, int b30);
};

struct BfmeMgr112
{
	unsigned char pad[0x2b8];
	BfmeSub2B8_112 m_sub2B8;
};
extern BfmeMgr112 *g_mgr12F4B98;

void __stdcall bfmeSend112(void *a, int b)
{
	g_mgr12F4B98->m_sub2B8.send(a, b * 30);
}

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

void __cdecl bfmeHelperB20(void *obj, void *param);

void __stdcall bfmeLookupAndExecFBE(void *key, void *param)
{
	void *obj = g_mgr12F076C->vfn26(key);
	if (obj) {
		bfmeHelperB20(obj, param);
	}
}

class BfmeObjF3E
{
public:
	void sendCode(int code, void *param2);
};

void __stdcall bfmeLookupAndSend3E0(void *key, void *param2)
{
	BfmeObjF3E *obj = (BfmeObjF3E*)g_mgr12F076C->vfn26(key);
	if (obj) {
		obj->sendCode(0x20, param2);
	}
}

class BfmeMgrF14
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
	virtual void vfn38(void *obj);
	virtual void vfn39(void *obj);
};
extern BfmeMgrF14 *g_mgr12F148C;

void __stdcall bfmeLookupAndSend7B0(void *key)
{
	void *obj = g_mgr12F076C->vfn26(key);
	if (obj) {
		g_mgr12F148C->vfn38(obj);
	}
}

void __stdcall bfmeLookupAndSend7F0(void *key)
{
	void *obj = g_mgr12F076C->vfn26(key);
	if (obj) {
		g_mgr12F148C->vfn39(obj);
	}
}

class BfmeMgrF1D
{
public:
	void* registerObj(void *field);
};
extern BfmeMgrF1D *g_mgr12EF1D8;

class BfmeMgr089
{
public:
	void send(void *obj, void *param2);
};
extern BfmeMgr089 *g_mgr12F0898;

void __stdcall bfmeLookupAndSendDB0(void *key, void *param2)
{
	void *obj = g_mgr12EF1D8->registerObj(key);
	if (obj) {
		g_mgr12F0898->send(obj, param2);
	}
}
