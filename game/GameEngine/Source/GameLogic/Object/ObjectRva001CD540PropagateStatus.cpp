// ?rva001CD540@Object@@QAEXABV?$BitFlags@$0FG@@@_N@Z
// BFME Object status propagation helper, retail 0x001CD540 (294 bytes).
// The original method name is not recovered, so the rva name stays explicit.
// Object ownership is established by the matched AIPanicState::onExit caller
// through ILT 0x0002181E.  The three outgoing Object::setStatus calls establish
// the 86-bit status mask and Bool argument; the adjacent 0x001CD420 helper
// corroborates the containment path and class layout.
//
// The TU-local pointer overload is ABI-equivalent to the reference overload on
// x86 and is exposed under the reference spelling by /alternatename below.  Its
// top-level volatile qualifier is a source-level codegen lever: it makes VC7.1
// preserve retail's EDI/EBX incoming-argument allocation without changing any
// runtime operation.
// stlport

#define _STLP_NO_EXCEPTIONS 1

#include <list>

typedef bool Bool;
typedef int Int;

template <int NUMBITS>
class BitFlags
{
public:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<86> ObjectStatusMaskType;

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xd4 - 8];
	unsigned int m_flags;
};

enum KindOfType
{
	KINDOF_UNKNOWN = 0
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class Object;
typedef _STL::list<Object *> ObjectList;

class HordeContainInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0; virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0; virtual void slot42() = 0; virtual void slot43() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0; virtual void slot50() = 0; virtual void slot51() = 0;
	virtual void slot52() = 0; virtual void slot53() = 0; virtual void slot54() = 0; virtual void slot55() = 0;
	virtual void slot56() = 0; virtual void slot57() = 0; virtual void slot58() = 0;
	virtual const ObjectList *getContainedItemsList() const = 0;
};

class ContainModuleInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &flags, Bool set);
	void rva001CD540(const ObjectStatusMaskType &flags, Bool set);
	void rva001CD540(const ObjectStatusMaskType * volatile flags, Bool set);

	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad008[0x1fc - 8];
	ContainModuleInterface *m_contain;
	unsigned char m_pad200[0x214 - 0x200];
	Object *m_containedBy;
	unsigned char m_pad218[0x369 - 0x218];
	unsigned char m_flag369;
};

void Object::rva001CD540(const ObjectStatusMaskType * volatile flags, Bool set)
{
	if (m_flag369 != 0)
		return;

	ThingTemplate *thingTemplate = m_template;
	if (thingTemplate != 0 && thingTemplate->m_nextOverride != 0)
	{
		thingTemplate = const_cast<ThingTemplate *>(
			reinterpret_cast<const ThingTemplate *>(thingTemplate->m_nextOverride->getFinalOverride()));
	}

	Object *target;
	if (thingTemplate->m_flags & 0x1000)
		target = this;
	else
	{
		Object *container = m_containedBy;
		if (container == 0 || !reinterpret_cast<const Thing *>(container)->isKindOf((KindOfType)0x6c))
			target = 0;
		else
			target = container;
	}

	if (target != 0)
	{
		ContainModuleInterface *contain = target->m_contain;
		if (contain == 0)
			return;

		HordeContainInterface *horde = contain->getHordeContainInterface();
		if (horde == 0)
			return;

		ObjectList items = *horde->getContainedItemsList();
		const ObjectStatusMaskType *status = flags;
		Bool statusSet = set;
		for (ObjectList::iterator it = items.begin(); it != items.end(); ++it)
			(*it)->setStatus(*status, statusSet);

		target->setStatus(*status, statusSet);
	}
	else
	{
		setStatus(*flags, set);
	}
}

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?isKindOf@Thing@@QBE_NW4KindOfType@@@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva001CD540@Object@@QAEXABV?$BitFlags@$0FG@@@_N@Z=?rva001CD540@Object@@QAEXRBV?$BitFlags@$0FG@@@_N@Z")
