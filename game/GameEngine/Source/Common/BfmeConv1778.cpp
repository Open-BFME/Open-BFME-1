inline void * __cdecl operator new(unsigned int size, void *place) { return place; }

namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int size);
};

}

class BfmeInfoDB
{
public:
	unsigned char m_bfmeHeadDB[0x24];
	int m_bfmeIndexDB;
};

class BfmeItemDB
{
public:
	BfmeInfoDB *bfmeInfoDB(void);
};

class BfmeValDB
{
public:
	BfmeValDB(BfmeItemDB *item) { m_bfmeItemDB = item; }

	BfmeItemDB *m_bfmeItemDB;
};

class BfmeNodeDB
{
public:
	BfmeNodeDB *m_bfmeNextDB;
	BfmeNodeDB *m_bfmePrevDB;
	BfmeValDB m_bfmeValueDB;
};

class BfmeOwnDB
{
public:
	virtual void bfmeSlot000DB(void);
	virtual void bfmeSlot001DB(void);
	virtual void bfmeSlot002DB(void);
	virtual void bfmeSlot003DB(void);
	virtual void bfmeSlot004DB(void);
	virtual void bfmeSlot005DB(void);
	virtual void bfmeSlot006DB(void);
	virtual void bfmeSlot007DB(void);
	virtual void bfmeSlot008DB(void);
	virtual void bfmeSlot009DB(void);
	virtual void bfmeSlot010DB(void);
	virtual void bfmeSlot011DB(void);
	virtual void bfmeSlot012DB(void);
	virtual void bfmeSlot013DB(void);
	virtual void bfmeSlot014DB(void);
	virtual void bfmeSlot015DB(void);
	virtual void bfmeSlot016DB(void);
	virtual void bfmeSlot017DB(void);
	virtual void bfmeSlot018DB(void);
	virtual void bfmeSlot019DB(void);
	virtual void bfmeSlot020DB(void);
	virtual void bfmeSlot021DB(void);
	virtual void bfmeSlot022DB(void);
	virtual void bfmeSlot023DB(void);
	virtual void bfmeSlot024DB(void);
	virtual void bfmeSlot025DB(void);
	virtual void bfmeSlot026DB(void);
	virtual void bfmeSlot027DB(void);
	virtual void bfmeSlot028DB(void);
	virtual void bfmeSlot029DB(void);
	virtual void bfmeSlot030DB(void);
	virtual void bfmeSlot031DB(void);
	virtual void bfmeSlot032DB(void);
	virtual void bfmeSlot033DB(void);
	virtual void bfmeSlot034DB(void);
	virtual void bfmeSlot035DB(void);
	virtual void bfmeSlot036DB(void);
	virtual void bfmeSlot037DB(void);
	virtual void bfmeSlot038DB(void);
	virtual void bfmeSlot039DB(void);
	virtual void bfmeSlot040DB(void);
	virtual void bfmeSlot041DB(void);
	virtual void bfmeSlot042DB(void);
	virtual void bfmeSlot043DB(void);
	virtual void bfmeSlot044DB(void);
	virtual void bfmeSlot045DB(void);
	virtual void bfmeSlot046DB(void);
	virtual void bfmeSlot047DB(void);
	virtual void bfmeSlot048DB(void);
	virtual void bfmeSlot049DB(void);
	virtual void bfmeSlot050DB(void);
	virtual void bfmeSlot051DB(void);
	virtual void bfmeSlot052DB(void);
	virtual void bfmeSlot053DB(void);
	virtual void bfmeSlot054DB(void);
	virtual void bfmeSlot055DB(void);
	virtual void bfmeSlot056DB(void);
	virtual void bfmeSlot057DB(void);
	virtual void bfmeSlot058DB(void);
	virtual void bfmeSlot059DB(void);
	virtual void bfmeSlot060DB(void);
	virtual void bfmeSlot061DB(void);
	virtual void bfmeSlot062DB(void);
	virtual void bfmeSlot063DB(void);
	virtual void bfmeSlot064DB(void);
	virtual void bfmeSlot065DB(void);
	virtual void bfmeSlot066DB(void);
	virtual void bfmeSlot067DB(void);
	virtual void bfmeSlot068DB(void);
	virtual void bfmeSlot069DB(void);
	virtual void bfmeSlot070DB(void);
	virtual void bfmeSlot071DB(void);
	virtual void bfmeSlot072DB(void);
	virtual void bfmeSlot073DB(void);
	virtual void bfmeSlot074DB(void);
	virtual void bfmeSlot075DB(void);
	virtual void bfmeSlot076DB(void);
	virtual void bfmeSlot077DB(void);
	virtual void bfmeSlot078DB(void);
	virtual void bfmeSlot079DB(void);
	virtual void bfmeSlot080DB(void);
	virtual void bfmeSlot081DB(void);
	virtual void bfmeSlot082DB(void);
	virtual void bfmeSlot083DB(void);
	virtual void bfmeSlot084DB(void);
	virtual void bfmeSlot085DB(void);
	virtual void bfmeSlot086DB(void);
	virtual void bfmeSlot087DB(void);
	virtual void bfmeSlot088DB(void);
	virtual void bfmeSlot089DB(void);
	virtual void bfmeSlot090DB(void);
	virtual void bfmeSlot091DB(void);
	virtual void bfmeSlot092DB(void);
	virtual void bfmeSlot093DB(void);
	virtual void bfmeSlot094DB(void);
	virtual void bfmeSlot095DB(void);
	virtual void bfmeSlot096DB(void);
	virtual void bfmeSlot097DB(void);
	virtual void bfmeSlot098DB(void);
	virtual void bfmeSlot099DB(void);
	virtual void bfmeSlot100DB(void);
	virtual void bfmeSlot101DB(void);
	virtual void bfmeSlot102DB(void);
	virtual int bfmeRejectDB(class BfmeItemDB *item);

	void bfmeAddDB(BfmeItemDB *item);

	unsigned char m_bfmeHeadDB[0x1318];
	BfmeNodeDB *m_bfmeListsDB[1];
};

void BfmeOwnDB::bfmeAddDB(BfmeItemDB *item)
{
	if (item == 0)
		return;

	if (bfmeRejectDB(item) != 0)
		return;

	BfmeNodeDB *head = m_bfmeListsDB[item->bfmeInfoDB()->m_bfmeIndexDB];
	BfmeNodeDB *node = (BfmeNodeDB *)_STL::__new_alloc::allocate(0xc);

	new (&node->m_bfmeValueDB) BfmeValDB(item);

	BfmeNodeDB *prev = head->m_bfmePrevDB;

	node->m_bfmeNextDB = head;
	node->m_bfmePrevDB = prev;
	prev->m_bfmeNextDB = node;
	head->m_bfmePrevDB = node;
}
