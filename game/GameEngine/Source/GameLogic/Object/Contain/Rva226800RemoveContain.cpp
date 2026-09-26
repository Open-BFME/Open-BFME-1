// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: OpenContain removal helper at retail 0x00226800.
// The OpenContain constructor, its list insertion at 0x00226790, and its
// flagged-count refresh at 0x00226730 prove the complete-object offsets used
// here.  The primary vtable slot at +0x2C removes the list node, slot +0x54
// plays the unload sound, and slot +0x5C restores the removed object to the
// world.  The StealthUpdate string and the final onRemoving/onRemovedFrom
// callbacks prove that this body owns the containment removal sequence.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef bool Bool;
typedef unsigned int UnsignedInt;

template <int Bits>
class BitFlags
{
public:
	enum InitType
	{
		kInit = 0
	};

	BitFlags(InitType, int index)
	{
		m_bits.set(index);
	}

private:
	_STL::bitset<Bits> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

class Overridable
{
public:
	Overridable *getFinalOverride();

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed_008[0xC8 - 8];
	unsigned char m_kindOfAtC8[4];
	UnsignedInt m_kindOfAtCC;
};

class StealthUpdate
{
public:
	void receiveGrant(Bool active, UnsignedInt frames);
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};

class Object;

class ContainInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void onRemoving(Object *object) = 0;
};

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &status, Bool set);
	StealthUpdate *findUpdateModule(NameKeyType key);
	int getLayer() const;
	void setLayer(PathfindLayerEnum layer);
	void onRemovedFrom(Object *container);

	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_unreconstructed_008[0x8C];
	UnsignedInt m_status0;
	UnsignedInt m_status1;
	unsigned char m_unreconstructed_09C[0x160];
	ContainInterface *m_contain;
	unsigned char m_unreconstructed_200[0x10];
};

class Rva226800StatusObject
{
public:
	void setStatus(const ObjectStatusMaskType &status, Bool set);
};

class Rva226800Overridable
{
public:
	Rva226800Overridable *getFinalOverride();
};

class Rva226800NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class Rva226800LayerObject
{
public:
	void setLayer(PathfindLayerEnum layer);
};

class Rva226800RemoveContain
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void removeListNode(Object *object) = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void doUnloadSound() = 0;
	virtual void slot58() = 0;
	virtual void addOrRemoveObjFromWorld(Object *object, Bool add, Bool unused) = 0;

	void remove(Object *object, Bool exposeStealthUnits);

	Object *getObject() const
	{
		return m_object;
	}

private:
	void *m_moduleData;
	Object *m_object;
	unsigned char m_unreconstructed_00C[0x2C];
	UnsignedInt m_unreconstructed_038;
	UnsignedInt m_unreconstructed_03C;
	unsigned char m_unreconstructed_040[0x24];
	UnsignedInt m_stealthUnitsContained;
};

// ?remove@Rva226800RemoveContain@@QAEXPAVObject@@_N@Z
void Rva226800RemoveContain::remove(Object *object, Bool exposeStealthUnits)
{
	UnsignedInt objectStatus = object->m_status1;
	if ((objectStatus & 2) != 0)
	{
		ObjectStatusMaskType status(ObjectStatusMaskType::kInit, 65);
		((Rva226800StatusObject *)getObject())->setStatus(status, false);
	}

	removeListNode(object);

	ThingTemplate *thing = object->m_template;
	if (thing && thing->m_nextOverride)
		thing = (ThingTemplate *)((Rva226800Overridable *)thing->m_nextOverride)->getFinalOverride();

	UnsignedInt kindOf = thing->m_kindOfAtCC;
	if ((kindOf & 2) != 0)
	{
		--m_stealthUnitsContained;
		if (exposeStealthUnits)
		{
			static const NameKeyType key_StealthUpdate =
				((Rva226800NameKeyGenerator *)TheNameKeyGenerator)->nameToKey("StealthUpdate");
			StealthUpdate *stealth = object->findUpdateModule(key_StealthUpdate);
			if (stealth)
				stealth->receiveGrant(false, 1);
		}
	}

	ObjectStatusMaskType status(ObjectStatusMaskType::kInit, 62);
	((Rva226800StatusObject *)object)->setStatus(status, false);

	if ((object->m_status0 & 0x10000000) != 0)
		addOrRemoveObjFromWorld(object, true, false);

	((Rva226800LayerObject *)object)->setLayer((PathfindLayerEnum)getObject()->getLayer());
	doUnloadSound();

	Object *container = getObject();
	ContainInterface *contain = container->m_contain;
	if (contain)
		contain->onRemoving(object);

	object->onRemovedFrom(getObject());
}

#undef NAMEKEY
