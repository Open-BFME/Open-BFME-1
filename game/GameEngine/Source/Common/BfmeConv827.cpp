
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
// 0x012F076C is retail's ScriptEngine singleton (defined once in
// GameLogic/ScriptEngine/ScriptEngine.cpp). This TU reaches only the slot it
// calls through its own vtable view, so the global keeps the canonical
// spelling and the view is taken by casting; bytes are unchanged.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

static inline BfmeMgrF07 *mgr12F076C() { return (BfmeMgrF07 *)TheScriptEngine; }

void __cdecl bfmeHelperB20(void *obj, void *param);

void __stdcall bfmeLookupAndExecFBE(void *key, void *param)
{
	void *obj = mgr12F076C()->vfn26(key);
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
	BfmeObjF3E *obj = (BfmeObjF3E*)mgr12F076C()->vfn26(key);
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
class InGameUI;
extern InGameUI *TheInGameUI;

void __stdcall bfmeLookupAndSend7B0(void *key)
{
	void *obj = mgr12F076C()->vfn26(key);
	if (obj) {
		reinterpret_cast<BfmeMgrF14 *>(TheInGameUI)->vfn38(obj);
	}
}

void __stdcall bfmeLookupAndSend7F0(void *key)
{
	void *obj = mgr12F076C()->vfn26(key);
	if (obj) {
		reinterpret_cast<BfmeMgrF14 *>(TheInGameUI)->vfn39(obj);
	}
}

class BfmeMgrF1D
{
public:
	void* registerObj(void *field);
};
class ThingFactory;
// TU-local view of the retail singleton's registerObj entry point.
extern ThingFactory *TheThingFactory;
static inline BfmeMgrF1D *localTheThingFactory() { return (BfmeMgrF1D *)TheThingFactory; }

class BfmeMgr089
{
public:
	void send(void *obj, void *param2);
};
class GameLogic;
extern GameLogic *TheGameLogic;

void __stdcall bfmeLookupAndSendDB0(void *key, void *param2)
{
	void *obj = localTheThingFactory()->registerObj(key);
	if (obj) {
		((BfmeMgr089 *)TheGameLogic)->send(obj, param2);
	}
}
