// Retail's global at 0x012F0898 is `GameLogic *TheGameLogic`, defined once in
// GameLogic/System/GameLogic.cpp.  This TU calls the matched
// destroyObject on it.
class GameLogic;
extern GameLogic *TheGameLogic;

class BfmeThingBTC;

// retail ILT 0x00023D30 -> 0x001CBAE0 is the matched Object::onRemovedFrom row
// and ILT 0x0001D0DE -> 0x0038B0C0 the matched GameLogic::destroyObject row
class Object
{
public:
	void onRemovedFrom(Object *removedFrom);
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

class BfmeThingBTC
{
public:
	unsigned char m_bfmeHead[0x214];
	void *m_bfmeOwner;
};

void bfmeGoBTC(BfmeThingBTC *what)
{
	((Object *)what)->onRemovedFrom((Object *)what->m_bfmeOwner);
	TheGameLogic->destroyObject((Object *)what);
}
