// The call at 0x0000A5DD is the 5-byte ILT thunk that jumps to the body at
// 0x00154330, which the ledger owns as
// ?aiExit@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z (game/
// GameEngine/Source/GameLogic/AI/AICommandInterfaceObjectCommands.cpp). Every
// retail caller reaches it as Object+0x204 (the AIUpdateInterface) +0x20, so
// this TU takes the same view of the block at +0x20; the two stack arguments
// are the pointer and the command source the retail call site pushes.
#include "../GameLogic/command_source_type.h"

class Object;

class AICommandInterface
{
public:
	void aiExit(Object *objectToExit, CommandSourceType cmdSource);
};

struct BfmeSubRQ
{
	unsigned char m_bfmeHead[0x20];
	AICommandInterface m_bfmeInner;
};

struct BfmeNodeRQ
{
	unsigned char m_bfmeHead[0x204];
	BfmeSubRQ *m_bfmeSub;
};

class BfmeLookRQ
{
public:
	virtual void bfmeSpareRQ0();
	virtual void bfmeSpareRQ1();
	virtual void bfmeSpareRQ2();
	virtual void bfmeSpareRQ3();
	virtual void bfmeSpareRQ4();
	virtual void bfmeSpareRQ5();
	virtual void bfmeSpareRQ6();
	virtual void bfmeSpareRQ7();
	virtual void bfmeSpareRQ8();
	virtual void bfmeSpareRQ9();
	virtual void bfmeSpareRQ10();
	virtual void bfmeSpareRQ11();
	virtual void bfmeSpareRQ12();
	virtual void bfmeSpareRQ13();
	virtual void bfmeSpareRQ14();
	virtual void bfmeSpareRQ15();
	virtual void bfmeSpareRQ16();
	virtual void bfmeSpareRQ17();
	virtual void bfmeSpareRQ18();
	virtual void bfmeSpareRQ19();
	virtual void bfmeSpareRQ20();
	virtual void bfmeSpareRQ21();
	virtual void bfmeSpareRQ22();
	virtual void bfmeSpareRQ23();
	virtual void bfmeSpareRQ24();
	virtual void bfmeSpareRQ25();
	virtual BfmeNodeRQ *bfmeFindRQ(void *key);
};

// Retail's global at 0x012F076C is the ScriptEngine singleton; this TU's
// view of it is BfmeLookRQ, so cast at the use.
class ScriptEngine;

extern ScriptEngine *TheScriptEngine;

static inline BfmeLookRQ *localLookRQ() { return (BfmeLookRQ *)TheScriptEngine; }

void __stdcall bfmeResetRQ(void *key)
{
	BfmeNodeRQ *node = localLookRQ()->bfmeFindRQ(key);
	if (node == 0)
		return;
	BfmeSubRQ *sub = node->m_bfmeSub;
	if (sub == 0)
		return;
	sub->m_bfmeInner.aiExit((Object *)0, (CommandSourceType)1);
}
