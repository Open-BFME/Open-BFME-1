// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: Object::bfmePrepare, retail 0x001CC920, 408 bytes.
// The callers at 0x002875C0 and 0x00287670 both call Object::bfmePrepare(0x3F).
// The symbol at 0x0001F852 resolves to this retail body.

typedef bool Bool;
typedef unsigned int UnsignedInt;

#include <list>

class BfmeSubBIA
{
public:
	int ask();
};

struct BfmeThingAIA
{
	char m_padding00[4];
	BfmeSubBIA *m_sub;
	Bool bfmeAskAIA(int kind);
};

struct BfmeResolvedThing
{
	char m_padding00[0xd4];
	UnsignedInt m_flags;
};

struct BfmeModelConditionFlags
{
	UnsignedInt m_bits[10];

	void clear(int bit)
	{
		m_bits[(UnsignedInt)bit >> 5] &= ~(1u << (bit & 31));
	}
};

class Object;
typedef _STL::list<Object *> ContainedItemsList;

class BfmeHordeContainInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58();
	virtual const ContainedItemsList *getContainedItemsList() const;
};

class BfmeContainModule
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual BfmeHordeContainInterface *getHordeContainInterface();
};

class BfmeBlockVKP
{
public:
	unsigned char m_data[0x14];
};

class BfmeNotifyThunk
{
public:
	void notify(BfmeBlockVKP *block, int unused1, int unused2);
};

class BfmeUpdVKP
{
public:
	void bfmeUpdateVKP();
};

class Object
{
public:
	virtual void slot00();
	void bfmePrepare(int value);

	BfmeThingAIA *m_template;
	char m_padding008[0x80 - 0x08];
	BfmeNotifyThunk *m_drawable;
	char m_padding084[0x110 - 0x84];
	BfmeModelConditionFlags m_conditionFlags;
	char m_padding138[0x1fc - 0x138];
	BfmeContainModule *m_contain;
	char m_padding200[0x204 - 0x200];
	BfmeUpdVKP *m_ai;
	char m_padding208[0x214 - 0x208];
	Object *m_containedBy;
};

#pragma comment(linker, "/alternatename:?ask@BfmeSubBIA@@QAEHXZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeAskAIA@BfmeThingAIA@@QAE_NH@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?notify@BfmeNotifyThunk@@QAEXPAVBfmeBlockVKP@@HH@Z=?j_0001343f@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeUpdateVKP@BfmeUpdVKP@@QAEXXZ=?j_0003611a@@YAXXZ")

void Object::bfmePrepare(int value)
{
	BfmeThingAIA *thing = m_template;
	BfmeResolvedThing *resolved = (BfmeResolvedThing *)thing;
	if (thing != 0)
	{
		BfmeSubBIA *sub = thing->m_sub;
		if (sub != 0)
			resolved = (BfmeResolvedThing *)sub->ask();
	}
	Object *object = this;
	if ((resolved->m_flags & 0x1000) != 0)
	{
		object = this;
	}
	else
	{
		Object *containedBy = m_containedBy;
		if (containedBy == 0 || !((BfmeThingAIA *)containedBy)->bfmeAskAIA(0x6c))
			return;
		object = containedBy;
	}
	if (object == 0)
		return;
	BfmeContainModule *contain = object->m_contain;
	if (contain == 0)
		return;
	BfmeHordeContainInterface *horde = contain->getHordeContainInterface();
	if (horde == 0)
		return;
	const ContainedItemsList *list = horde->getContainedItemsList();
	ContainedItemsList objects(*list);
	for (ContainedItemsList::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		Object *member = *it;
		UnsignedInt memberFlags = ((volatile UnsignedInt *)member->m_conditionFlags.m_bits)[(UnsignedInt)value >> 5];
		if ((memberFlags & (1u << (value & 31))) != 0)
		{
			member->m_conditionFlags.clear(value);
			if (member->m_drawable != 0)
				member->m_drawable->notify((BfmeBlockVKP *)&member->m_conditionFlags, 0, 0);
			if (member->m_ai != 0)
				member->m_ai->bfmeUpdateVKP();
		}
	}
	UnsignedInt objectFlags = ((volatile UnsignedInt *)object->m_conditionFlags.m_bits)[(UnsignedInt)value >> 5];
	if ((objectFlags & (1u << (value & 31))) != 0)
	{
		object->m_conditionFlags.clear(value);
		if (object->m_drawable != 0)
			object->m_drawable->notify((BfmeBlockVKP *)&object->m_conditionFlags, 0, 0);
		if (object->m_ai != 0)
			object->m_ai->bfmeUpdateVKP();
	}
}
