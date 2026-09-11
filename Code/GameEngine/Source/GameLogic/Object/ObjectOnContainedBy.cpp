// BFME 1.03 Object::onContainedBy at RVA 0x001CB9F0.
//
// The canonical Object.cpp declaration and the named OpenContain and
// TunnelTracker callers establish the identity.  BFME's Object and contain
// layouts differ from the available Generals headers, so this focused view
// preserves the retail fields and the virtual getStatus slot used here.
// cl: /DNDEBUG /MD /GX- /O2 /Ob2

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 3
};

class Object;

struct ContainmentStatus
{
	UnsignedInt m_bits[3];
};

template <Int NUMBITS>
class BitFlags;

typedef BitFlags<86> ObjectStatusMaskType;

class ContainModuleInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6c();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7c();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8c();
	virtual void slot90(); virtual void slot94(); virtual void slot98();
	virtual ContainmentStatus getStatus(const Object *object) const;
};

class ThingTemplate
{
public:
	void *m_vtable;
	ThingTemplate *m_nextOverride;
	unsigned char m_pad08[0xc4];
	UnsignedInt m_kindOfAtCC;

	ThingTemplate *getFinalOverride();
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;

class Object
{
public:
	void onContainedBy(Object *containedBy);
	void clearStatus(ObjectStatusTypes status);
	void setStatus(const ObjectStatusMaskType &status, Bool set);
	ContainModuleInterface *getContain() const { return m_contain; }

	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad008[0x1f4];
	ContainModuleInterface *m_contain;
	unsigned char m_pad200[0x14];
	Object *m_containedBy;
	unsigned char m_pad218[4];
	UnsignedInt m_containedByFrame;
	unsigned char m_pad220[0x125];
	unsigned char m_containedFlags;
};

// ?onContainedBy@Object@@QAEXPAV1@@Z
void Object::onContainedBy(Object *containedBy)
{
	ContainModuleInterface *contain;
	ThingTemplate *thing = m_template;
	if (thing && thing->m_nextOverride)
		thing = thing->m_nextOverride->getFinalOverride();

	if ((thing->m_kindOfAtCC & 0x00400000) != 0)
	{
		m_containedFlags &= ~1;
		clearStatus(OBJECT_STATUS_UNDER_CONSTRUCTION);
	}
	else
	{
		contain = containedBy ? containedBy->getContain() : 0;
		if (contain && (contain->getStatus(this).m_bits[0] & 8) != 0)
			m_containedFlags |= 1;
		else
			m_containedFlags &= ~1;

		if (contain)
			setStatus(reinterpret_cast<const ObjectStatusMaskType &>(
				contain->getStatus(this)), true);
	}

	m_containedBy = containedBy;
	m_containedByFrame = TheBfmeGameLogic->m_frame;
}
