// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x0018BDD0: collect ObjectIDs from a contain-module helper into a
// vector at this+4. Neighbour of compact/visitAll. Identity is RVA-derived
// because the contain vtable slot is not independently named.

#include <vector>
#include <list>

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object
{
public:
	unsigned char m_pad[0x74];
	ObjectID m_id;
	ObjectID getID() const { return m_id; }
};

class BfmeContainListSink
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5c() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual BfmeContainListSink *ask68() = 0;
	virtual void slot6c() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7c() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8c() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9c() = 0;
	virtual void slota0() = 0;
	virtual void slota4() = 0;
	virtual void slota8() = 0;
	virtual void slota0c() = 0;
	virtual void slotb0() = 0;
	virtual void slotb4() = 0;
	virtual void slotb8() = 0;
	virtual void slotbc() = 0;
	virtual void slotc0() = 0;
	virtual void slotc4() = 0;
	virtual void slotc8() = 0;
	virtual void slotcc() = 0;
	virtual void slotd0() = 0;
	virtual void slotd4() = 0;
	virtual void slotd8() = 0;
	virtual void slotdc() = 0;
	virtual void slote0() = 0;
	virtual void slote4() = 0;
	virtual void slote8() = 0;
	virtual void slote0c() = 0;
	virtual void fillList(_STL::list<Object *> *out) = 0;
};

class BfmeContainOwner
{
public:
	unsigned char m_pad[0x1fc];
	BfmeContainListSink *m_contain;
};

class Rva0018BDD0
{
public:
	void collect(BfmeContainOwner *owner, bool clearFirst);

private:
	void *m_vptr;
	_STL::vector<ObjectID> m_ids;
};

// ?collect@Rva0018BDD0@@QAEXPAVBfmeContainOwner@@_N@Z
void Rva0018BDD0::collect(BfmeContainOwner *owner, bool clearFirst)
{
	if (owner == 0)
		return;

	if (clearFirst)
		m_ids.clear();

	BfmeContainListSink *contain = owner->m_contain;
	if (contain == 0)
		return;

	BfmeContainListSink *sink = contain->ask68();
	if (sink == 0)
		return;

	_STL::list<Object *> items;
	sink->fillList(&items);

	for (_STL::list<Object *>::iterator it = items.begin(); it != items.end(); ++it)
	{
		Object *obj = *it;
		if (obj)
			m_ids.push_back(obj->getID());
	}
}
