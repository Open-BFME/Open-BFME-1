// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport
// Open-BFME5: ControlBar command availability helper.
// The BFME retail body uses the same helper as the Zero Hour twin, with the
// BFME containment and KindOf offsets supplied by the live headers.

#define Overridable BfmeHeaderOverridable
#include "PreRTS.h"
#undef Overridable

class ThingTemplate;
class Object;

struct ContainedItemNode
{
	ContainedItemNode *m_next;
	ContainedItemNode *m_prev;
	Object *m_item;
};

struct ContainedItemsList
{
	ContainedItemNode *m_node;
};

struct BfmeTemplateReference
{
	const ThingTemplate *m_overridable;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
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
	virtual void slot56() = 0; virtual void slot57() = 0; virtual void slot58() = 0; virtual void slot59() = 0;
	virtual void slot60() = 0; virtual void slot61() = 0; virtual void slot62() = 0; virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual const ContainedItemsList *getContainedItemsList() const = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const ThingTemplate *getTemplate() const
	{
		const volatile unsigned char *address = reinterpret_cast<const volatile unsigned char *>(this);
		address += 4;
		return *(const ThingTemplate *volatile *)address;
	}

	ContainModuleInterface *getContain() const
	{
		return *reinterpret_cast<ContainModuleInterface *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x1fc);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	Bool canRappel() const
	{
		return (m_kindof[1] & 0x800) != 0;
	}

private:
	UnsignedByte m_padding[0xc0];
	volatile UnsignedInt m_kindof[3];
};

static const UnsignedInt BFME_KINDOF_CAN_RAPPEL = 43;

static __declspec(noinline) Int getRappellerCount(Object *obj)
{
	Int num = 0;
	const ContainedItemsList *items = obj->getContain() ? obj->getContain()->getContainedItemsList() : NULL;
	if (items)
	{
		ContainedItemNode *sentinel = items->m_node;
		for (ContainedItemNode *it = sentinel->m_next; it != sentinel; it = it->m_next)
		{
			Object *member = it->m_item;
			const ThingTemplate *thingTemplate = member->getTemplate();
			if (thingTemplate != NULL && thingTemplate->m_nextOverride != NULL)
			{
				thingTemplate = (const ThingTemplate *)thingTemplate->m_nextOverride->getFinalOverride();
			}
			if (thingTemplate->canRappel())
			{
				++num;
			}
		}
	}
    return num;
}

__declspec(noinline) Int probe_getRappellerCount(Object *obj)
{
    return getRappellerCount(obj);
}
