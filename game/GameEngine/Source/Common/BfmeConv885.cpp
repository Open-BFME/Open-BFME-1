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

extern BfmeGlobAEUA *g_bfmeAEUA;

// 0x012ED748 is retail's PlayerList singleton (game/GameEngine/Source/Common/RTS/PlayerList.cpp
// defines `PlayerList *ThePlayerList`); only the address-derived lookup this TU spells
// is still unnamed, so the global keeps its real spelling and the read is cast.
class PlayerList;

extern PlayerList *ThePlayerList;	// retail [0x012ED748]

void __stdcall bfmeGoEUAa(int id, void *ctx)
{
	id = g_bfmeAEUA->bfmeFirstEUA(id, 0);
	while ((unsigned short)id)
	{
		BfmeItemEUA *it = ((BfmeGlobBEUA *)ThePlayerList)->bfmeLookEUA(&id);
		if (it)
			it->bfmeRunEUAa(ctx);
	}
}

void __stdcall bfmeGoEUAb(int id, void *ctx)
{
	id = g_bfmeAEUA->bfmeFirstEUA(id, 0);
	while ((unsigned short)id)
	{
		BfmeItemEUA *it = ((BfmeGlobBEUA *)ThePlayerList)->bfmeLookEUA(&id);
		if (it)
			it->bfmeRunEUAb(ctx);
	}
}

void __stdcall bfmeGoEUAc(int id, void *ctx)
{
	id = g_bfmeAEUA->bfmeFirstEUA(id, 0);
	while ((unsigned short)id)
	{
		BfmeItemEUA *it = ((BfmeGlobBEUA *)ThePlayerList)->bfmeLookEUA(&id);
		if (it)
			it->bfmeRunEUAc(ctx);
	}
}

void __stdcall bfmeGoEUAd(int id, void *ctx)
{
	id = g_bfmeAEUA->bfmeFirstEUA(id, 0);
	while ((unsigned short)id)
	{
		BfmeItemEUA *it = ((BfmeGlobBEUA *)ThePlayerList)->bfmeLookEUA(&id);
		if (it)
			it->bfmeRunEUAd(ctx);
	}
}

void __stdcall bfmeGoEUAe(int id, void *ctx)
{
	id = g_bfmeAEUA->bfmeFirstEUA(id, 0);
	while ((unsigned short)id)
	{
		BfmeItemEUA *it = ((BfmeGlobBEUA *)ThePlayerList)->bfmeLookEUA(&id);
		if (it)
			it->bfmeRunEUAe(ctx);
	}
}

