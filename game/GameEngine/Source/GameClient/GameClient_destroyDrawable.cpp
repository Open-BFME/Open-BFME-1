// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: GameClient::destroyDrawable, retail 0x00431110 (134B).
// The BFME body clears the drawable modules, removes both object links and
// appends the drawable to GameClient's deferred-destruction list.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

class Drawable;
class Object;

class BfmeThingIK
{
public:
	void bfmeClearIK(void);
};

class Drawable
{
public:
	void removeFromList(Drawable **listHead);
	void friend_bindToObject(Object *object);
};

class BfmeDrawableWithID
{
public:
	unsigned int bfmeGetID(void);
};

class Object
{
public:
	void friend_bindToDrawable(Drawable *drawable);
};

class InGameUI
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void slot69() = 0;
	virtual void slot70() = 0;
	virtual void slot71() = 0;
	virtual void slot72() = 0;
	virtual void disregardDrawable(Drawable *drawable) = 0;
};

extern InGameUI *TheInGameUI;

class BfmeDrawableLookupTable
{
public:
	void bfmeErase(const unsigned int &id);
};

class GameClient
{
public:
	virtual void destroyDrawable(Drawable *drawable);

private:
	unsigned char m_beforeDrawableList[0x0c];
	Drawable *m_drawableList;
	BfmeDrawableLookupTable m_drawableLookup;
	unsigned char m_beforeDestroyList[0xcb];
	_STL::list<Drawable *> m_destroyList;
};

// ?destroyDrawable@GameClient@@UAEXPAVDrawable@@@Z
void GameClient::destroyDrawable(Drawable *draw)
{
	((BfmeThingIK *)draw)->bfmeClearIK();
	TheInGameUI->disregardDrawable(draw);
	draw->removeFromList(&m_drawableList);

	Object *object = *(Object **)((char *)draw + 0xfc);
	if (object != 0)
	{
		object->friend_bindToDrawable(0);
		draw->friend_bindToObject(0);
	}

	m_drawableLookup.bfmeErase(((BfmeDrawableWithID *)draw)->bfmeGetID());
	m_destroyList.push_back(draw);
}
