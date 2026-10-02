// stlport
// Open-BFME5 conversions.

// The lookup below is GameLogic::findObjectByID; GameLogicObjectLookup.h holds
// the declaration (its body stays in Thing/GameLogicFindObjectByID.cpp).
#include "Thing/GameLogicObjectLookup.h"

class BfmeSrcUDB
{
public:
	float bfmeCallUDB(int a, int b);
};

extern BfmeSrcUDB *g_bfmeObjUDB;
extern const float g_rva01075350;

float __stdcall bfmeGoUDB(int a, int b)
{
	if (g_bfmeObjUDB)
		return g_bfmeObjUDB->bfmeCallUDB(a, b);
	return g_rva01075350;
}

class BfmeSrcUDC
{
public:
	void bfmeCloseUDC();
};

extern BfmeSrcUDC *g_bfmeObjUDC;

int bfmeGoUDC(void)
{
	if (g_bfmeObjUDC) {
		g_bfmeObjUDC->bfmeCloseUDC();
		g_bfmeObjUDC = 0;
	}
	return 1;
}

class BfmeSubUDD
{
public:
	void *bfmeFindUDD(int key);
};

class BfmeMgrUDD
{
public:
	char m_bfmePad[0x28];
	BfmeSubUDD *m_bfmeSub;
};

// Retail 0x012F1028 is EA's `LivingWorldLogic *TheLivingWorldLogic`, defined
// once in game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogic.cpp.
// BfmeMgrUDD above is this TU's own view of that address, so the read casts.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern char g_bfmeDefaultUDD[];

class BfmeThingUDD
{
public:
	void *bfmeGoUDD();
	char m_bfmePad[0x2c];
	int m_bfmeKey;
};

void *BfmeThingUDD::bfmeGoUDD()
{
	int k = m_bfmeKey;
	BfmeSubUDD *s = ((BfmeMgrUDD *)TheLivingWorldLogic)->m_bfmeSub;
	if (s)
		return s->bfmeFindUDD(k);
	return g_bfmeDefaultUDD;
}

class BfmeRecUDE
{
public:
	virtual void bfmeV0UDE() = 0;
	virtual void bfmeV1UDE() = 0;
	virtual void bfmeV2UDE() = 0;
	virtual void bfmeV3UDE() = 0;
	virtual void bfmeV4UDE() = 0;
	virtual void bfmeV5UDE() = 0;
	virtual void bfmeV6UDE() = 0;
	virtual void bfmeV7UDE() = 0;
	virtual void bfmeV8UDE() = 0;
	virtual void bfmeV9UDE() = 0;
	virtual void *bfmeGetUDE() = 0;
};

// Retail's global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined once
// in game/GameEngine/Source/GameLogic/System/GameLogic.cpp; Thing/GameLogicObjectLookup.h
// above already declares the real GameLogic view this TU calls through.
extern GameLogic *TheGameLogic;

class BfmeThingUDE
{
public:
	void *bfmeGoUDE();
	char m_bfmePad[0x60];
	int m_bfmeKey;
};

void *BfmeThingUDE::bfmeGoUDE()
{
	BfmeRecUDE *r = reinterpret_cast<BfmeRecUDE *>(
		TheGameLogic->findObjectByID(m_bfmeKey));
	if (r)
		return r->bfmeGetUDE();
	return 0;
}
