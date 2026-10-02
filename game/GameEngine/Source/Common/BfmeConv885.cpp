struct BfmeItemEUA
{

	void bfmeRunEUAa(void *ctx);
	void bfmeRunEUAb(void *ctx);
	void bfmeRunEUAc(void *ctx);
	void bfmeRunEUAd(void *ctx);
	void bfmeRunEUAe(void *ctx);
};

class BfmeGlobAEUA
{
public:
	int bfmeFirstEUA(int id, int z);
};

class BfmeGlobBEUA
{
public:
	BfmeItemEUA *bfmeLookEUA(int *id);
};

// 0x012F076C is retail's ScriptEngine singleton (defined once in
// GameLogic/ScriptEngine/ScriptEngine.cpp). This TU reaches only the one
// method it calls through its own view, so the global keeps the canonical
// spelling and the view is taken by casting; bytes are unchanged.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

static inline BfmeGlobAEUA *theScriptEngineAEUA() { return (BfmeGlobAEUA *)TheScriptEngine; }

// 0x012ED748 is retail's PlayerList singleton (game/GameEngine/Source/Common/RTS/PlayerList.cpp
// defines `PlayerList *ThePlayerList`); only the address-derived lookup this TU spells
// is still unnamed, so the global keeps its real spelling and the read is cast.
class PlayerList;

extern PlayerList *ThePlayerList;	// retail [0x012ED748]

void __stdcall bfmeGoEUAa(int id, void *ctx)
{
	id = theScriptEngineAEUA()->bfmeFirstEUA(id, 0);
	while ((unsigned short)id)
	{
		BfmeItemEUA *it = ((BfmeGlobBEUA *)ThePlayerList)->bfmeLookEUA(&id);
		if (it)
			it->bfmeRunEUAa(ctx);
	}
}

void __stdcall bfmeGoEUAb(int id, void *ctx)
{
	id = theScriptEngineAEUA()->bfmeFirstEUA(id, 0);
	while ((unsigned short)id)
	{
		BfmeItemEUA *it = ((BfmeGlobBEUA *)ThePlayerList)->bfmeLookEUA(&id);
		if (it)
			it->bfmeRunEUAb(ctx);
	}
}

void __stdcall bfmeGoEUAc(int id, void *ctx)
{
	id = theScriptEngineAEUA()->bfmeFirstEUA(id, 0);
	while ((unsigned short)id)
	{
		BfmeItemEUA *it = ((BfmeGlobBEUA *)ThePlayerList)->bfmeLookEUA(&id);
		if (it)
			it->bfmeRunEUAc(ctx);
	}
}

void __stdcall bfmeGoEUAd(int id, void *ctx)
{
	id = theScriptEngineAEUA()->bfmeFirstEUA(id, 0);
	while ((unsigned short)id)
	{
		BfmeItemEUA *it = ((BfmeGlobBEUA *)ThePlayerList)->bfmeLookEUA(&id);
		if (it)
			it->bfmeRunEUAd(ctx);
	}
}

void __stdcall bfmeGoEUAe(int id, void *ctx)
{
	id = theScriptEngineAEUA()->bfmeFirstEUA(id, 0);
	while ((unsigned short)id)
	{
		BfmeItemEUA *it = ((BfmeGlobBEUA *)ThePlayerList)->bfmeLookEUA(&id);
		if (it)
			it->bfmeRunEUAe(ctx);
	}
}

