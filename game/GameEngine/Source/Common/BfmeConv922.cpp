// Open-BFME5 conversions.

// Retail global at 0x012F0898 is GameLogic *TheGameLogic (defined once in
// game_logic.cpp). This TU reads it through a local view type, so keep the
// view and cast at the use; the global itself uses the canonical spelling.
struct BfmeState922A
{
	char m_bfmePad[0x10c];
	int m_bfmeMode;
};
class GameLogic;
extern GameLogic *TheGameLogic;

class BfmeTail922A
{
public:
	char bfmeTail922A();
};

// Retail's load in bfmeGo922A is 0x012F1028: the global BfmeConv2113.cpp
// defines; this TU keeps its own view type and casts at the use.
class Glo012F1028Type;
extern Glo012F1028Type *Glo012F1028;

char bfmeGo922A(void)
{
	if (reinterpret_cast<BfmeState922A *>(TheGameLogic)->m_bfmeMode != 6)
		return 0;
	return reinterpret_cast<BfmeTail922A *>(Glo012F1028)->bfmeTail922A();
}

class BfmeGlob922D
{
public:
	virtual void bfmeSlot922D00();
	virtual void bfmeSlot922D01();
	virtual void bfmeSlot922D02();
	virtual void bfmeSlot922D03();
	virtual void bfmeSlot922D04();
	virtual void bfmeSlot922D05();
	virtual void bfmeSlot922D06();
	virtual void bfmeSlot922D07();
	virtual void bfmeSlot922D08();
	virtual void bfmeSlot922D09();
	virtual void bfmeSlot922D10();
	virtual void bfmeSlot922D11();
	virtual void bfmeSlot922D12();
	virtual void bfmeSlot922D13();
	virtual void bfmeSlot922D14();
	virtual void bfmeSlot922D15();
	virtual void bfmeSlot922D16();
	virtual void bfmeSlot922D17();
	virtual void bfmeSlot922D18();
	virtual void bfmeSlot922D19();
	virtual void bfmeSlot922D20();
	virtual void bfmeSlot922D21();
	virtual void bfmeSlot922D22();
	virtual void bfmeSlot922D23();
	virtual void bfmeSlot922D24();
	virtual void bfmeSlot922D25();
	virtual void bfmeVirt922D(void *a);
};

// 0x012F076C is the game's ScriptEngine *TheScriptEngine, defined once in
// ScriptEngine.cpp; this TU sees only one vtable slot.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

char __stdcall bfmeGo922D(void *a, void *b, void *c)
{
	if (a && c)
		((BfmeGlob922D *)TheScriptEngine)->bfmeVirt922D(a);
	return 0;
}

class BfmeTail922F
{
public:
	void bfmeCall922F(void *a, int f);
};

struct BfmeS922F
{
	char m_bfmePad[0x20];
	BfmeTail922F m_bfmeTail;
};

struct BfmeO922F
{
	char m_bfmePad[0x204];
	BfmeS922F *m_bfmeS;
};

class BfmeThing922F
{
public:
	void bfmeGo922F(void *a);
};

void BfmeThing922F::bfmeGo922F(void *a)
{
	BfmeO922F *o = *(BfmeO922F **)((char *)this - 0x18);
	BfmeS922F *s = o->m_bfmeS;
	if (s)
		s->m_bfmeTail.bfmeCall922F(a, 2);
}

struct BfmeArg922G
{
	char m_bfmePad[0x74];
	void *m_bfmeVal;
};

class BfmeSub922G
{
public:
	void bfmeCall922G(void **p);
};

class BfmeThing922G
{
public:
	void bfmeGo922G(BfmeArg922G *a);
	char m_bfmePad[0x24];
	BfmeSub922G m_bfmeSub;
};

void BfmeThing922G::bfmeGo922G(BfmeArg922G *a)
{
	if (a) {
		void *p = a->m_bfmeVal;
		m_bfmeSub.bfmeCall922G(&p);
	}
}
