class BfmeThingAIA;
struct BfmeSlotAIA;
typedef int ObjectID;

int bfmeTryAIA(BfmeThingAIA *who, BfmeSlotAIA *slot);

class BfmeFoundXF
{
public:
	void *m_bfmePadXF[0x1d];
	ObjectID m_bfmeTagXF;
};

struct BfmeSlotXF
{
	void *m_bfmeWantXF;
	BfmeFoundXF *m_bfmeHaveXF;
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheBfmeGameLogic;

typedef void (*ObjectIterateFunc)(Object *, void *);

class Player
{
public:
	void iterateObjects(ObjectIterateFunc routine, void *state) const;
};

class BfmeOwnerXF
{
public:
	Object *bfmeFindXF();

	unsigned char m_bfmeHeadXF[0x63c];
	ObjectID volatile m_bfmeTagXF;
};

Object *BfmeOwnerXF::bfmeFindXF()
{
	if (m_bfmeTagXF == 0)
	{
		BfmeSlotXF slot;

		slot.m_bfmeWantXF = this;
		slot.m_bfmeHaveXF = 0;
		((Player *)this)->iterateObjects((ObjectIterateFunc)bfmeTryAIA, &slot);

		if (slot.m_bfmeHaveXF != 0)
			m_bfmeTagXF = slot.m_bfmeHaveXF->m_bfmeTagXF;
	}

	return TheBfmeGameLogic->findObjectByID(m_bfmeTagXF);
}
