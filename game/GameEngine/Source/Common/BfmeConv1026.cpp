// Open-BFME5 conversions.

// Matched callee rows (callees.py, via ILT): Rva000C4D80Manager::evaluate 0x000C4D80,
// AICommandInterface::aiDock 0x00154110, Object::setScriptStatus 0x001D01D0,
// Object::getControllingPlayer 0x001BE3F0, Rva2225E0Filter::accepts 0x003A04A0,
// GameLogic::destroyObject 0x0038B0C0, operator delete 0x00881EB0.
class Object;
class Player;
enum CommandSourceType { CMD_FROM_PLAYER_1026 = 0 };
enum ObjectScriptStatusBit { OBJECT_STATUS_BIT8_1026 = 8 };

class Rva000C4D80Manager
{
public:
	bool evaluate(Object *a, const Object *b, int c);
};
typedef Rva000C4D80Manager BfmeQ1026;

// The retail global at 0x012ED700 is EA's `ActionManager *TheActionManager`
// (see game/GameEngine/Source/Common/System/game_engine_subsystems.h). This TU
// previously spelled it ?g_bfmeQ1026@@3PAVBfmeQ1026@@A; it now references the
// one canonical spelling and reads through this TU-local view of the pointee.
class ActionManager;
extern ActionManager *TheActionManager;

class AICommandInterface
{
public:
	void aiDock(Object *a, CommandSourceType b);
};

class BfmeA1026
{
public:
	void bfmeGo1026A(int a, int b);

	char m_bfmePad[8];
	int m_bfmeKey;
	char m_bfmePad2[0x14];
	AICommandInterface m_bfmeList;
};

void BfmeA1026::bfmeGo1026A(int a, int b)
{
	if (((BfmeQ1026 *)TheActionManager)->evaluate((Object *)m_bfmeKey, (const Object *)a, b))
		m_bfmeList.aiDock((Object *)a, (CommandSourceType)b);
}

class Object
{
public:
	void setScriptStatus(ObjectScriptStatusBit bit, bool set);
	Player *getControllingPlayer() const;
};

class BfmeU1026
{
public:
	virtual void bfmeVU01026();
	virtual void bfmeVU11026();
	virtual void bfmeVU21026();
	virtual void bfmeVU31026();
	virtual void bfmeVU41026();
	virtual void bfmeVU51026();
	virtual void bfmeVU61026();
	virtual void bfmeVU71026();
	virtual void bfmeVU81026();
	virtual void bfmeVU91026();
	virtual void bfmeVU101026();
	virtual void bfmeVU111026();
	virtual void bfmeVU121026();
	virtual void bfmeVU131026();
	virtual void bfmeVU141026();
	virtual void bfmeVU151026();
	virtual void bfmeVU161026();
	virtual void bfmeVU171026();
	virtual void bfmeVU181026();
	virtual void bfmeVU191026();
	virtual void bfmeVU201026();
	virtual void bfmeVU211026();
	virtual void bfmeVU221026();
	virtual void bfmeVU231026();
	virtual void bfmeVU241026();
	virtual void bfmeVU251026();
	virtual Object *bfmeFind1026(int a);
};

// retail 0x012F076C: EA's ScriptEngine *TheScriptEngine, defined once in
// game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp. BfmeU1026 is
// this TU's local view of the pointee; cast at the use.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

void __stdcall bfmeGo1026B(int a, char b)
{
	Object *x = ((BfmeU1026 *)TheScriptEngine)->bfmeFind1026(a);

	if (x != 0)
		x->setScriptStatus((ObjectScriptStatusBit)8, b == 0);
}

// The 0x012F12CC singleton is DisplayStringManager *TheDisplayStringManager,
// defined once in DisplayStringManager.cpp.  This TU keeps its own view of
// the vtable and casts at the use.
class DisplayStringManager;

class BfmeReg1026
{
public:
	virtual void bfmeVR01026();
	virtual void bfmeVR11026();
	virtual void bfmeVR21026();
	virtual void bfmeVR31026();
	virtual void bfmeVR41026();
	virtual void bfmeVR51026();
	virtual void bfmeVR61026();
	virtual void bfmeVR71026();
	virtual void bfmeVR81026();
	virtual void bfmeVR91026();
	virtual void bfmeDrop1026(int h);
};

extern DisplayStringManager *TheDisplayStringManager;		// 0x012F12CC
static inline BfmeReg1026 *theDisplayStringManagerView()
{
	return (BfmeReg1026 *)TheDisplayStringManager;
}

class BfmeD1026
{
public:
	void *bfmeGo1026D(unsigned int f);

	char m_bfmePad[4];
	int m_bfmeH;
};

void *BfmeD1026::bfmeGo1026D(unsigned int f)
{
	if (m_bfmeH != 0) {
		theDisplayStringManagerView()->bfmeDrop1026(m_bfmeH);
		m_bfmeH = 0;
	}

	if ((f & 1) != 0)
		operator delete(this);

	return this;
}

class Rva2225E0Filter
{
public:
	bool accepts(Object *o, Player *p);
};

struct BfmeOwner1026
{
	char m_bfmePad[8];
	Rva2225E0Filter m_bfmeTab;
};


// Retail: 0x012F0898 is EA's GameLogic *TheGameLogic (see
// game/GameEngine/Source/GameLogic/System/GameLogic.cpp). This TU only needs
// its 0x012F0898-facing view, so declare the canonical symbol and cast.
class GameLogic
{
public:
	void destroyObject(Object *o);
};
extern GameLogic *TheGameLogic;

class BfmeF1026
{
public:
	void bfmeGo1026F(int h, int u1, int u2);
};

void BfmeF1026::bfmeGo1026F(int h, int u1, int u2)
{
	if (h == 0)
		return;

	BfmeOwner1026 *o = *(BfmeOwner1026 **)((char *)this - 0xc);
	Object *p = *(Object **)((char *)this - 8);

	if (o->m_bfmeTab.accepts((Object *)h, p->getControllingPlayer()))
		TheGameLogic->destroyObject((Object *)h);
}
