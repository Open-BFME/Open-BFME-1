// cl: /DNDEBUG /MD /EHsc

// Retail 0x002264F0 is the OpenContain virtual at vtable slot 23.  BFME keeps
// an unused third parameter on the virtual call.  The method updates the world
// state of the object and repeats the update for riders that it does not enclose.

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Drawable
{
public:
	void rva00411DD0(Bool hidden);
};

class Object;

class Pathfinder
{
public:
	void addObjectToPathfindMap(Object *object);
	void removeObjectFromPathfindMap(Object *object);
};

class AI
{
private:
	unsigned char m_padding[0x0C];

public:
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

class BfmeThingXV
{
public:
	void bfmeStopXV();
};

struct ContainedItemNode
{
	ContainedItemNode *m_next;
	ContainedItemNode *m_previous;
	Object *m_object;
};

struct ContainedItemIterator
{
	ContainedItemNode *m_node;

	Object *operator*() const { return m_node->m_object; }
	ContainedItemIterator &operator++()
	{
		m_node = m_node->m_next;
		return *this;
	}
	bool operator!=(const ContainedItemIterator &other) const
	{
		return m_node != other.m_node;
	}
};

struct ContainedItemsList
{
	ContainedItemNode *m_node;

	ContainedItemIterator begin() const
	{
		ContainedItemIterator it = {m_node->m_next};
		return it;
	}

	ContainedItemIterator end() const
	{
		ContainedItemIterator it = {m_node};
		return it;
	}
};

class ContainInterface
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual void slot68() = 0; virtual void slot6C() = 0;
	virtual void slot70() = 0; virtual void slot74() = 0;
	virtual void slot78() = 0; virtual void slot7C() = 0;
	virtual void slot80() = 0; virtual void slot84() = 0;
	virtual void slot88() = 0; virtual void slot8C() = 0;
	virtual void slot90() = 0; virtual void slot94() = 0;
	virtual void slot98() = 0; virtual void slot9C() = 0;
	virtual void slotA0() = 0; virtual void slotA4() = 0;
	virtual void slotA8() = 0; virtual void slotAC() = 0;
	virtual void slotB0() = 0; virtual void slotB4() = 0;
	virtual void slotB8() = 0; virtual void slotBC() = 0;
	virtual void slotC0() = 0; virtual void slotC4() = 0;
	virtual void slotC8() = 0; virtual void slotCC() = 0;
	virtual void slotD0() = 0; virtual void slotD4() = 0;
	virtual void slotD8() = 0; virtual void slotDC() = 0;
	virtual void slotE0() = 0; virtual void slotE4() = 0;
	virtual void slotE8() = 0; virtual void slotEC() = 0;
	virtual void slotF0() = 0; virtual void slotF4() = 0;
	virtual void slotF8() = 0; virtual void slotFC() = 0;
	virtual void getContainCount(Bool countRiders) const = 0;
	virtual const ContainedItemsList *getContainedItemsList() const = 0;
};

class Object
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual Drawable *getDrawable() const = 0;

	void rva001CA2E0();
	void leaveGroup();

	unsigned char m_padding94[0x90];
	UnsignedInt m_status94;
	unsigned char m_padding98[0x164];
	ContainInterface *m_contain;
};

class OpenContain
{
protected:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void addOrRemoveObjFromWorld(Object *object, Bool add, Bool unused);
};

// ?addOrRemoveObjFromWorld@OpenContain@@MAEXPAVObject@@_N1@Z
void OpenContain::addOrRemoveObjFromWorld(Object *obj, Bool add, Bool unused)
{
	if (add)
	{
		obj->rva001CA2E0();

		if (obj->getDrawable())
			obj->getDrawable()->rva00411DD0(false);

		TheAI->m_pathfinder->addObjectToPathfindMap(obj);
	}
	else
	{
		obj->leaveGroup();
		((BfmeThingXV *)obj)->bfmeStopXV();

		if (obj->getDrawable())
			obj->getDrawable()->rva00411DD0(true);

		TheAI->m_pathfinder->removeObjectFromPathfindMap(obj);
	}

	ContainInterface *contain = obj->m_contain;
	if (contain)
	{
		const ContainedItemsList *items = contain->getContainedItemsList();
		if (items)
		{
			for (ContainedItemIterator it = items->begin();
				it != items->end(); ++it)
			{
				Object *contained = *it;
				if ((contained->m_status94 & 0x10000000) != 0)
					addOrRemoveObjFromWorld(contained, add, false);
			}
		}
	}
}
