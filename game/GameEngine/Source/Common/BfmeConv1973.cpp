// stlport
// The lookup callee is retail's real GameLogic::findObjectByID (0x0009A510,
// matched in GameLogicFindObjectByID.cpp); declare it through its own header
// rather than a stand-in class so the emitted call names that symbol.
#include "Thing/GameLogicObjectLookup.h"

class BfmeThingESK;

class BfmeSubESK
{
public:
	virtual void bfmeSlot00ESK();
	virtual void bfmeSlot01ESK();
	virtual void bfmeSlot02ESK();
	virtual void bfmeSlot03ESK();
	virtual void bfmeSlot04ESK();
	virtual void bfmeSlot05ESK();
	virtual void bfmeSlot06ESK();
	virtual void bfmeSlot07ESK();
	virtual void bfmeSlot08ESK();
	virtual void bfmeSlot09ESK();
	virtual void bfmeSlot10ESK();
	virtual void bfmeSlot11ESK();
	virtual void bfmeSlot12ESK();
	virtual void bfmeSlot13ESK();
	virtual void bfmeSlot14ESK();
	virtual void bfmeSlot15ESK();
	virtual void bfmeSlot16ESK();
	virtual void bfmeSlot17ESK();
	virtual void bfmeSlot18ESK();
	virtual void bfmeSlot19ESK();
	virtual void bfmeSlot20ESK();
	virtual void bfmeSlot21ESK();
	virtual void bfmeSlot22ESK();
	virtual void bfmeSlot23ESK();
	virtual void bfmeSlot24ESK();
	virtual void bfmeSlot25ESK();
	virtual void bfmeSlot26ESK();
	virtual void bfmeSlot27ESK();
	virtual void bfmeSlot28ESK();
	virtual void bfmeSlot29ESK();
	virtual void bfmeSlot30ESK();
	virtual void bfmeSlot31ESK();
	virtual void bfmeSlot32ESK();
	virtual char bfmeSlot33ESK(BfmeThingESK *thing, int mode);
};

class BfmeObjESK
{
public:
	unsigned char m_bfmeHeadESK[0x1fc];
	BfmeSubESK *m_bfmeSubESK;
};

class BfmeMsgESK
{
public:
	unsigned char m_bfmeHeadESK[8];
	int m_bfmeIdESK;
};

// Retail's GameLogic singleton at 0x012F0898; the one canonical spelling.
extern GameLogic *TheGameLogic;

__forceinline int bfmeReadyESK(BfmeObjESK *obj, BfmeThingESK *thing);

class BfmeHostESK
{
public:
	char bfmeAllowESK(BfmeMsgESK *msg, BfmeThingESK *thing);
	char bfmeCheckESK(BfmeMsgESK *msg, BfmeThingESK *thing);
};

char BfmeHostESK::bfmeAllowESK(BfmeMsgESK *msg, BfmeThingESK *thing)
{
	BfmeObjESK *obj = (BfmeObjESK *)TheGameLogic->findObjectByID(msg->m_bfmeIdESK);

	if (obj == 0 || thing == 0 || !bfmeCheckESK(msg, thing))
		return 0;

	return (char)bfmeReadyESK(obj, thing);
}

__forceinline int bfmeReadyESK(BfmeObjESK *obj, BfmeThingESK *thing)
{
	BfmeSubESK *sub = obj->m_bfmeSubESK;

	if (sub != 0 && sub->bfmeSlot33ESK(thing, 1) == 1)
		return 1;

	return 0;
}
