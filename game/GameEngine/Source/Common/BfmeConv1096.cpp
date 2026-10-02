// Open-BFME5 conversions.

class BfmeS1096;

class BfmeR1096
{
public:
	void bfmeSet1096(int a);
	void bfmeAdj1096(int a);
	void bfmeUse1096(int a);
	void bfmeOn1096(BfmeS1096 *s);
	void bfmeOff1096(BfmeS1096 *s);
	char m_bfmePad[0x258];
	int m_bfme258;
	char m_bfmePad1[0x425];
	char m_bfme681;
};

class BfmeM1096
{
public:
	BfmeS1096 *bfmeMake1096(int a);
};

// Retail's global at 0x012EF1D8 is EA's `ThingFactory *TheThingFactory`; this
// TU keeps its own BfmeM1096 ABI view and casts at the use.
class ThingFactory;

extern ThingFactory *TheThingFactory;

class BfmeD1096
{
public:
	BfmeR1096 *bfmeLook1096(short *h);
};

class BfmeP1096
{
public:
	int bfmeFirst1096(int a, int b);
};

// 0x012ED748 is retail's PlayerList singleton (game/GameEngine/Source/Common/RTS/PlayerList.cpp
// defines `PlayerList *ThePlayerList`); only the address-derived lookups this TU
// spells are still unnamed, so the global keeps its real spelling and the reads are cast.
class PlayerList;

extern PlayerList *ThePlayerList;	// retail [0x012ED748]
// 0x012F076C is retail's ScriptEngine singleton (defined once in
// GameLogic/ScriptEngine/ScriptEngine.cpp). This TU reaches only the one
// method it calls through its own view, so the global keeps the canonical
// spelling and the view is taken by casting; bytes are unchanged.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

static inline BfmeP1096 *theScriptEngineP1096() { return (BfmeP1096 *)TheScriptEngine; }

void __stdcall bfmeGo1096A(int a, char b)
{
	a = theScriptEngineP1096()->bfmeFirst1096(a, 0);
	while ((short)a) {
		BfmeR1096 *r = ((BfmeD1096 *)ThePlayerList)->bfmeLook1096((short *)&a);

		if (r)
			r->m_bfme681 = b;
	}
}

void __stdcall bfmeGo1096B(int a, int b)
{
	a = theScriptEngineP1096()->bfmeFirst1096(a, 0);
	while ((short)a) {
		BfmeR1096 *r = ((BfmeD1096 *)ThePlayerList)->bfmeLook1096((short *)&a);

		if (r)
			r->bfmeSet1096(b - 1);
	}
}

void __stdcall bfmeGo1096C(int a, int b)
{
	a = theScriptEngineP1096()->bfmeFirst1096(a, 0);
	while ((short)a) {
		BfmeR1096 *r = ((BfmeD1096 *)ThePlayerList)->bfmeLook1096((short *)&a);

		if (r) {
			r->bfmeAdj1096(r->m_bfme258 + b);
			r->bfmeUse1096(r->m_bfme258);
		}
	}
}

void __stdcall bfmeGo1096D(int a, int b, char c)
{
	BfmeS1096 *s = ((BfmeM1096 *)TheThingFactory)->bfmeMake1096(b);

	if (!s)
		return;
	b = theScriptEngineP1096()->bfmeFirst1096(a + 0x10, 0);
	while ((short)b) {
		BfmeR1096 *r = ((BfmeD1096 *)ThePlayerList)->bfmeLook1096((short *)&b);

		if (r) {
			if (c)
				r->bfmeOn1096(s);
			else
				r->bfmeOff1096(s);
		}
	}
}
