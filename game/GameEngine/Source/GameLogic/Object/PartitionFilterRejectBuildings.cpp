// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /MD /EHsc
// BFME PartitionFilterRejectBuildings layout overlay.  BFME's allow body omits
// the Zero Hour relationship comparison and resolves contained buildings via
// their apparent controlling player.

typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

class Player
{
public:
	unsigned char m_unreconstructed_00[0x2C];
	int m_difficulty;
};

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_next;
	Overridable *getFinalOverride();
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed_08[0xC8 - 0x08];
	volatile char m_kindOfStructureByte;
	unsigned char m_unreconstructed_C9[3];
	UnsignedInt m_kindOfWord1;
};

enum KindOfType
{
	KINDOF_FS_BASE_DEFENSE = 0x3F
};

class Thing
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	Bool isKindOf(KindOfType kind) const;
};

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual const Player *getApparentControllingPlayer(const Player *viewer) const;
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	Bool isAbleToAttack() const;

	unsigned char m_unreconstructed_08[0x1FC - 0x08];
	ContainModuleInterface *m_contain;
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) { }
	virtual ~PartitionFilter() { }

protected:
	PartitionFilter *m_next;
};

class PartitionFilterRejectBuildings : public PartitionFilter
{
protected:
	virtual Bool allow(Object *other);

private:
	const Object *m_self;
	Bool m_acquireEnemies;

public:
	PartitionFilterRejectBuildings(const Object *self);
};

PartitionFilterRejectBuildings::PartitionFilterRejectBuildings(const Object *self)
{
	m_self = self;
	m_acquireEnemies = false;
	if (self->getControllingPlayer() != 0
		&& *reinterpret_cast<volatile const int *>(reinterpret_cast<const char *>(m_self->getControllingPlayer()) + 0x2C) == 1)
	{
		m_acquireEnemies = true;
	}
}

Bool PartitionFilterRejectBuildings::allow(Object *other)
{
	ThingTemplate *templatePtr = other->m_template;
	if (templatePtr != 0 && templatePtr->m_next != 0)
		templatePtr = (ThingTemplate *)templatePtr->m_next->getFinalOverride();

	if ((templatePtr->m_kindOfStructureByte >> 7) == 0)
		return true;

	templatePtr = other->m_template;
	if (templatePtr != 0 && templatePtr->m_next != 0)
		templatePtr = (ThingTemplate *)templatePtr->m_next->getFinalOverride();
	if ((templatePtr->m_kindOfWord1 & 0x400000) != 0)
		return true;

	const Player *myPlayer = m_self->getControllingPlayer();
	if (myPlayer == 0)
		return false;

	ContainModuleInterface *contain = other->m_contain;
	const Player *otherPlayer = contain != 0
		? contain->getApparentControllingPlayer(myPlayer) : 0;
	if (otherPlayer == 0)
		otherPlayer = other->getControllingPlayer();
	if (otherPlayer == 0)
		return false;

	if (m_acquireEnemies)
		return true;
	if (other->isKindOf(KINDOF_FS_BASE_DEFENSE))
		return true;
	if (other->m_contain != 0 && other->isAbleToAttack())
		return true;
	return false;
}
