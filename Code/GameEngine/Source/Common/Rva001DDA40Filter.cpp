// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /MD /EHsc
// Address-derived filter at retail0x001DDA40; named ownership is unproven.
// The target reads the BFME ThingTemplate kind mask at +0xC8/+0xCC and the
// Object contain module at +0x1FC directly.  The reference implementation's
// relationship comparison is absent from this BFME body; ownership is used
// only to resolve an apparent controller for a contained building.

typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

class Player;

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

class Rva001DDA40Filter
{
protected:
	virtual Bool allow(Object *other);

private:
	unsigned char m_unreconstructed_04[0x08 - 0x04];
	const Object *m_self;
	Bool m_allowFlag0c;
};

Bool Rva001DDA40Filter::allow(Object *other)
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

	if (m_allowFlag0c)
		return true;
	if (other->isKindOf(KINDOF_FS_BASE_DEFENSE))
		return true;
	if (other->m_contain != 0 && other->isAbleToAttack())
		return true;
	return false;
}
