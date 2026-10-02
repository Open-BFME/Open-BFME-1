class BfmeThingAIA
{
public:
	bool bfmeAskAIA(int what);
};

class Player;
#define OBJECT_TU_MEMBERS Player *getControllingPlayer() const;
#include "../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

struct BfmeSlotAIA
{
	void *m_bfmeWant;
	BfmeThingAIA *m_bfmeHave;
};

int bfmeTryAIA(BfmeThingAIA *who, BfmeSlotAIA *slot)
{
	if (who == 0)
		return 1;
	if (slot->m_bfmeHave == 0 && who->bfmeAskAIA(0x7a) &&
		reinterpret_cast<Object *>(who)->getControllingPlayer() == slot->m_bfmeWant)
	{
		slot->m_bfmeHave = who;
		return 0;
	}
	return 1;
}
