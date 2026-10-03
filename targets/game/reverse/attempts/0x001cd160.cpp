// ?rva001CD160@Rva001CD160Owner@@QAEXABVRva001CD160Mask@@@Z
// partial score=1.0 date=2026-10-03
// BANK ONLY: opaque ABI views; no new pins or production identities.
// cl: /DNDEBUG /MD /EHsc
// stlport

#define _STLP_NO_EXCEPTIONS 1

#include <list>

typedef bool Bool;
typedef int Int;

#include <bitset>
class Rva001CD160Mask { public: Rva001CD160Mask() {} private: _STL::bitset<320> m_bits; };

class Rva00087A80View
{
public:
	virtual ~Rva00087A80View();
	const Rva00087A80View *rva00087A80() const;

	Rva00087A80View *m_nextOverride;
};

class Rva001CD160TemplateView : public Rva00087A80View
{
public:
	unsigned char m_pad08[0xd4 - 8];
	unsigned int m_flags;
};

enum Rva001CD160KindOrdinal
{
	Rva001CD160OrdinalZero = 0
};

class Rva000A2CF0View
{
public:
	Bool rva000A2CF0(Rva001CD160KindOrdinal kind) const;
};

class Rva001CD160Owner;
typedef _STL::list<Rva001CD160Owner *> Rva001CD160List;

class Rva001CD160SlotECView
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
	virtual const Rva001CD160List *slotEC() const = 0;
};

class Rva001CD160Slot68View
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual Rva001CD160SlotECView *slot68() = 0;
};

class Rva001CD160Owner
{
public:
	void rva001C7720(const Rva001CD160Mask&,const Rva001CD160Mask&);
	void rva001CD160(const Rva001CD160Mask &flags);

	void *m_vtable;								// +0x000
	Rva001CD160TemplateView *m_template;					// +0x004
	unsigned char m_pad008[0x1fc - 8];
	Rva001CD160Slot68View *m_contain;			// +0x1fc
	unsigned char m_pad200[0x214 - 0x200];
	Rva001CD160Owner *m_containedBy;						// +0x214
};

void Rva001CD160Owner::rva001CD160(const Rva001CD160Mask &flags)
{
	Rva001CD160TemplateView *thingTemplate = m_template;
	if (thingTemplate != 0 && thingTemplate->m_nextOverride != 0)
	{
		thingTemplate = const_cast<Rva001CD160TemplateView *>(
			reinterpret_cast<const Rva001CD160TemplateView *>(thingTemplate->m_nextOverride->rva00087A80()));
	}

	Rva001CD160Owner *target;
	if (thingTemplate->m_flags & 0x1000)
	{
		target = this;
	}
	else
	{
		Rva001CD160Owner *container = m_containedBy;
		if (container == 0 || !reinterpret_cast<const Rva000A2CF0View *>(container)->rva000A2CF0((Rva001CD160KindOrdinal)0x6c))
			return;
		target = container;
	}

	if (target == 0)
		return;

	Rva001CD160Slot68View *contain = target->m_contain;
	if (contain == 0)
		return;

	Rva001CD160SlotECView *horde = contain->slot68();
	if (horde == 0)
		return;

	Rva001CD160List items = *horde->slotEC();
	for (Rva001CD160List::iterator it = items.begin(); it != items.end(); ++it)
	{
		Rva001CD160Owner* item=*it;
        Rva001CD160Mask empty;
        item->rva001C7720(empty,flags);
	}

	{ Rva001CD160Mask empty;
    target->rva001C7720(empty,flags); }
}

