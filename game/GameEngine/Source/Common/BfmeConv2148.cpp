class BfmeItemZB
{
public:
	unsigned char m_bfmeHeadZB[4];
	int m_bfme04ZB;
};

class BfmeNodeZB
{
public:
	virtual void bfmeCloseZB(int flag);

	int m_bfme04ZB;
	unsigned char m_bfmeMidZB[4];
	BfmeItemZB *m_bfme0CZB;
	unsigned char m_bfmeMid2ZB[0x28 - 0x10];
	unsigned int m_bfme28ZB;
	unsigned char m_bfmeMid3ZB[0x3c - 0x2c];
	BfmeNodeZB *m_bfme3CZB;
};

class Money
{
public:
	void deposit(unsigned int amount, bool flag);
};

class UpgradeTemplate;
class BfmeThingEL;
class ProductionEntry;

class Gen_000D2480
{
public:
	bool bfmeHasBit(const BfmeThingEL *thing) const;
};

class Player
{
public:
	void removeUpgrade(const UpgradeTemplate *upgradeTemplate);

	unsigned char m_bfmeHeadZB[0x48];
	Money m_bfmeMoneyZB;
};

// Retail Object::getControllingPlayer (0x001BE3F0): the pointer this body
// keeps at this-0x18 is the controlling Player, so it carries retail's names.
class Object
{
public:
	Player *getControllingPlayer() const;
};

class ProductionUpdate
{
protected:
	void removeFromProductionQueue(ProductionEntry *production);

	friend class BfmeHostZB;
};

class BfmeHostZB
{
public:
	void bfmeGiveZB(BfmeItemZB *item);

	unsigned char m_bfmeHeadZB[8];
	BfmeNodeZB *m_bfme08ZB;
};

void BfmeHostZB::bfmeGiveZB(BfmeItemZB *item)
{
	if (item == 0)
		return;

	Player *pl = (Player *)(*(Object **)((char *)this - 0x18))->getControllingPlayer();

	if (item->m_bfme04ZB == 0)
	{
		if (!((const Gen_000D2480 *)pl)->bfmeHasBit((const BfmeThingEL *)item))
			return;
	}

	BfmeNodeZB *n = m_bfme08ZB;

	while (n != 0)
	{
		if (n->m_bfme04ZB == 2 && n->m_bfme0CZB == item)
		{
			pl->m_bfmeMoneyZB.deposit(n->m_bfme28ZB, 1);
			((ProductionUpdate *)((char *)this - 0x20))->removeFromProductionQueue((ProductionEntry *)n);
			n->bfmeCloseZB(1);

			if (item->m_bfme04ZB == 0)
				pl->removeUpgrade((const UpgradeTemplate *)item);

			return;
		}

		n = n->m_bfme3CZB;
	}
}
