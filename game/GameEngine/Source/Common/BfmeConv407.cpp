// retail pushes 0x00432155, the 5-byte ILT thunk ?j_00032155@@YAXXZ (matched,
// game/gen_small/gthunks_055.cpp) that routes to RVA 0x002EFCD0; take its address.
extern void j_00032155();

class BfmeSubAKC
{
public:
	virtual void bfmeSpareAKCa0();
	virtual void bfmeSpareAKCa1();
	virtual void bfmeSpareAKCa2();
	virtual void bfmeSpareAKCa3();
	virtual void bfmeSpareAKCa4();
	virtual void bfmeSpareAKCa5();
	virtual void bfmeSpareAKCa6();
	virtual void bfmeSpareAKCa7();
	virtual void bfmeSpareAKCa8();
	virtual void bfmeSpareAKCa9();
	virtual void bfmeSpareAKCa10();
	virtual void bfmeSpareAKCa11();
	virtual void bfmeSpareAKCa12();
	virtual void bfmeSpareAKCa13();
	virtual void bfmeSpareAKCa14();
	virtual void bfmeSpareAKCa15();
	virtual void bfmeSpareAKCa16();
	virtual void bfmeSpareAKCa17();
	virtual void bfmeSpareAKCa18();
	virtual void bfmeSpareAKCa19();
	virtual void bfmeSpareAKCa20();
	virtual void bfmeSpareAKCa21();
	virtual void bfmeSpareAKCa22();
	virtual void bfmeSpareAKCa23();
	virtual void bfmeSpareAKCa24();
	virtual void bfmeSpareAKCa25();
	virtual void bfmeSpareAKCa26();
	virtual void bfmeSpareAKCa27();
	virtual void bfmeSpareAKCa28();
	virtual void bfmeSpareAKCa29();
	virtual void bfmeSpareAKCa30();
	virtual void bfmeSpareAKCa31();
	virtual void bfmeSpareAKCa32();
	virtual void bfmeSpareAKCa33();
	virtual void bfmeSpareAKCa34();
	virtual void bfmeSpareAKCa35();
	virtual void bfmeSpareAKCa36();
	virtual void bfmeSpareAKCa37();
	virtual void bfmeSpareAKCa38();
	virtual void bfmeSpareAKCa39();
	virtual void bfmeSpareAKCa40();
	virtual void bfmeSpareAKCa41();
	virtual void bfmeSpareAKCa42();
	virtual void bfmeSpareAKCa43();
	virtual void bfmeSpareAKCa44();
	virtual void bfmeSpareAKCa45();
	virtual void bfmeSpareAKCa46();
	virtual void bfmeSpareAKCa47();
	virtual void bfmeSpareAKCa48();
	virtual void bfmeSpareAKCa49();
	virtual void bfmeSpareAKCa50();
	virtual void bfmeSpareAKCa51();
	virtual void bfmeSpareAKCa52();
	virtual void bfmeSpareAKCa53();
	virtual void bfmeSpareAKCa54();
	virtual void bfmeSpareAKCa55();
	virtual void bfmeSpareAKCa56();
	virtual void bfmeSpareAKCa57();
	virtual void bfmeSpareAKCa58();
	virtual void bfmeSpareAKCa59();
	virtual void bfmeSpareAKCa60();
	virtual void bfmeSpareAKCa61();
	virtual void bfmeSpareAKCa62();
	virtual void bfmeSendAKC(void *cb, int one, int two);
	virtual int bfmeAskAKC(int what);
};

struct BfmeNodeAKC
{
	unsigned char m_bfmeHead[0x1fc];
	BfmeSubAKC *m_bfmeSub;
};

class BfmeLookAKC
{
public:
	virtual void bfmeSpareAKCb0();
	virtual void bfmeSpareAKCb1();
	virtual void bfmeSpareAKCb2();
	virtual void bfmeSpareAKCb3();
	virtual void bfmeSpareAKCb4();
	virtual void bfmeSpareAKCb5();
	virtual void bfmeSpareAKCb6();
	virtual void bfmeSpareAKCb7();
	virtual void bfmeSpareAKCb8();
	virtual void bfmeSpareAKCb9();
	virtual void bfmeSpareAKCb10();
	virtual void bfmeSpareAKCb11();
	virtual void bfmeSpareAKCb12();
	virtual void bfmeSpareAKCb13();
	virtual void bfmeSpareAKCb14();
	virtual void bfmeSpareAKCb15();
	virtual void bfmeSpareAKCb16();
	virtual void bfmeSpareAKCb17();
	virtual void bfmeSpareAKCb18();
	virtual void bfmeSpareAKCb19();
	virtual void bfmeSpareAKCb20();
	virtual void bfmeSpareAKCb21();
	virtual void bfmeSpareAKCb22();
	virtual void bfmeSpareAKCb23();
	virtual void bfmeSpareAKCb24();
	virtual void bfmeSpareAKCb25();
	virtual BfmeNodeAKC *bfmeFindAKC(void *key);
};

// 0x012F076C is the game's ScriptEngine *TheScriptEngine, defined once in
// ScriptEngine.cpp; this TU sees only the one vtable slot.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

static __forceinline BfmeLookAKC *bfmeScriptEngine(void)
{
	return (BfmeLookAKC *)TheScriptEngine;
}

void __stdcall bfmeGoAKC(void *key, void *spare)
{
	BfmeNodeAKC *node = bfmeScriptEngine()->bfmeFindAKC(key);
	if (node == 0)
		return;
	BfmeSubAKC *sub = node->m_bfmeSub;
	if (sub != 0 && sub->bfmeAskAKC(0) != 0)
		sub->bfmeSendAKC((void *)&j_00032155, 0, 3);
}
