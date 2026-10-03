enum AttitudeType {};

// Retail's call at 0x00030553 is AIUpdateInterface::setAttitude, reached
// through the 5-byte ILT thunk (body 0x0027DEF0); the body is the one
// AIGroup::setAttitude calls on each member AI, read from Object+0x204.
class AIUpdateInterface
{
public:
	void setAttitude(AttitudeType tude);
};

struct BfmeNodeRP
{
	unsigned char m_bfmeHead[0x204];
	AIUpdateInterface *m_bfmeSub;
};

class BfmeLookRP
{
public:
	virtual void bfmeSpareRP0();
	virtual void bfmeSpareRP1();
	virtual void bfmeSpareRP2();
	virtual void bfmeSpareRP3();
	virtual void bfmeSpareRP4();
	virtual void bfmeSpareRP5();
	virtual void bfmeSpareRP6();
	virtual void bfmeSpareRP7();
	virtual void bfmeSpareRP8();
	virtual void bfmeSpareRP9();
	virtual void bfmeSpareRP10();
	virtual void bfmeSpareRP11();
	virtual void bfmeSpareRP12();
	virtual void bfmeSpareRP13();
	virtual void bfmeSpareRP14();
	virtual void bfmeSpareRP15();
	virtual void bfmeSpareRP16();
	virtual void bfmeSpareRP17();
	virtual void bfmeSpareRP18();
	virtual void bfmeSpareRP19();
	virtual void bfmeSpareRP20();
	virtual void bfmeSpareRP21();
	virtual void bfmeSpareRP22();
	virtual void bfmeSpareRP23();
	virtual void bfmeSpareRP24();
	virtual void bfmeSpareRP25();
	virtual BfmeNodeRP *bfmeFindRP(void *key);
};

// Retail's global at 0x012F076C is the ScriptEngine singleton; this TU's
// view of it is BfmeLookRP, so cast at the use.
class ScriptEngine;

extern ScriptEngine *TheScriptEngine;

static inline BfmeLookRP *localLookRP() { return (BfmeLookRP *)TheScriptEngine; }

void __stdcall bfmeSendRP(void *key, void *what)
{
	BfmeNodeRP *node = localLookRP()->bfmeFindRP(key);
	if (node == 0)
		return;
	AIUpdateInterface *sub = node->m_bfmeSub;
	if (sub == 0)
		return;
	sub->setAttitude((AttitudeType)(int)what);
}
