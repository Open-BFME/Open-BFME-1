// ?rva001CD160@Object@@QAEXABV?$BitFlags@$0BEA@@@@Z
// Address-derived Object method; the m_contain offset and 332-byte boundary
// are recorded in targets/game/reverse/identity_evidence/001cd160-exact-mask-propagation-bank.md.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmekindof /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE

#include <list>
#include "Common/BitFlags.h"

#define OBJECT_TU_MEMBERS \
	void rva001CD160(const BitFlags<320> &flags); \
	void clearAndSetModelConditionFlags(const BitFlags<320> &clear, \
		const BitFlags<320> &set);
#include "object.h"

typedef _STL::list<Object *> ObjectList;

class Rva001CD160OverrideView
{
public:
	virtual ~Rva001CD160OverrideView();
	const Rva001CD160OverrideView *rva00087A80() const;
	Rva001CD160OverrideView *m_nextOverride;
};

class Rva001CD160TemplateView : public Rva001CD160OverrideView
{
public:
	unsigned char m_pad08[0xd4 - 8];
	unsigned int m_flags;
};

class Rva001CD160ThingView
{
public:
	Bool rva000A2CF0(int kind) const;
};

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

extern void j_000022bb();
extern void j_0003251f();

void Object::rva001CD160(const BitFlags<320> &flags)
{
	typedef const Rva001CD160OverrideView *(Rva001CD160OverrideView::*FinalOverrideFn)() const;
	union { void (*fn)(); FinalOverrideFn call; } finalOverride = { j_000022bb };

	Rva001CD160TemplateView *thingTemplate =
		reinterpret_cast<Rva001CD160TemplateView *>(m_template);
	if (thingTemplate != 0 && thingTemplate->m_nextOverride != 0)
	{
		thingTemplate = const_cast<Rva001CD160TemplateView *>(
			reinterpret_cast<const Rva001CD160TemplateView *>(
				(thingTemplate->m_nextOverride->*finalOverride.call)()));
	}

	Object *target;
	if (thingTemplate->m_flags & 0x1000)
	{
		target = this;
	}
	else
	{
		Object *container = m_containedBy;
		typedef Bool (Rva001CD160ThingView::*IsKindOfFn)(int) const;
		union { void (*fn)(); IsKindOfFn call; } isKindOf = { j_0003251f };
		if (container == 0 ||
			!(reinterpret_cast<const Rva001CD160ThingView *>(container)->*isKindOf.call)(0x6c))
			return;
		target = container;
	}

	if (target == 0)
		return;

	ContainModuleInterface *contain = target->m_contain;
	if (contain == 0)
		return;

	HordeContainInterface *horde = contain->getHordeContainInterface();
	if (horde == 0)
		return;

	ObjectList items = *horde->getContainedItemsList();
	for (ObjectList::iterator it = items.begin(); it != items.end(); ++it)
	{
		Object *item = *it;
		BitFlags<320> empty;
		item->clearAndSetModelConditionFlags(empty, flags);
	}

	{
		BitFlags<320> empty;
		target->clearAndSetModelConditionFlags(empty, flags);
	}
}
