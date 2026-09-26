// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// BFME retail 0x001CD300, 225 bytes.
//
// The generated boundary is an Object-layout method.  Its source-level name
// is not recovered: the bytes prove the Object receiver, the override-aware
// template test, and the contained-by fallback, but no direct named caller
// reaches this entry.  Keep the method address-derived and keep the two
// stack arguments as raw Int values.
// stlport

#include <list>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *m_nextOverride;
	Overridable *getFinalOverride();
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed08[0xc8 - 0x08];
	UnsignedInt m_kindOf[4];
};

enum KindOfType
{
	KINDOF_RVA001CD300 = 0x6c
};

class Thing
{
public:
	virtual ~Thing();
	ThingTemplate *m_template;
	Bool isKindOf(KindOfType kind) const;
};

class Object;
class BfmeThingVKP;

class HordeContainInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual const _STL::list<Object *> &slot59() = 0;
};

class ContainModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

class Object : public Thing
{
public:
	void rva001CD300(Int first, Int second);

	char m_unreconstructed08[0x1fc - 0x08];
	ContainModuleInterface *m_contain;
	char m_unreconstructed200[0x214 - 0x200];
	Object *m_containedBy;
};

class BfmeThingVKP
{
public:
	void bfmeSetVKP(Int, Int);
};

extern void j_000095ed();

typedef void (BfmeThingVKP::*BfmeSetVKPCall)(Int, Int);

union BfmeSetVKPCallBits
{
	void (*freeFunction)();
	BfmeSetVKPCall memberFunction;
};

void Object::rva001CD300(Int first, Int second)
{
	ThingTemplate *thingTemplate = m_template;
	if (thingTemplate != 0 && thingTemplate->m_nextOverride != 0)
		thingTemplate = (ThingTemplate *)thingTemplate->m_nextOverride->getFinalOverride();

	Object *self = this;
	BfmeThingVKP *target;
	if ((thingTemplate->m_kindOf[3] & 0x1000) == 0)
	{
		self = m_containedBy;
		if (self == 0 || !self->isKindOf(KINDOF_RVA001CD300))
			return;
		target = (BfmeThingVKP *)self;
	}
	else
		target = (BfmeThingVKP *)self;
	if (target == 0)
		return;

	ContainModuleInterface *contain = ((Object *)target)->m_contain;
	if (contain == 0)
		return;
	HordeContainInterface *horde = contain->getHordeContainInterface();
	if (horde == 0)
		return;

	const _STL::list<Object *> &source = horde->slot59();
	_STL::list<Object *> members(source);
	_STL::list<Object *>::iterator iterator = members.begin();
	BfmeSetVKPCallBits setCall;
	setCall.freeFunction = j_000095ed;
	while (iterator != members.end())
	{
		BfmeThingVKP *member = (BfmeThingVKP *)*iterator;
		(member->*setCall.memberFunction)(first, second);
		++iterator;
	}
	BfmeThingVKP *thingSelf = target;
	(thingSelf->*setCall.memberFunction)(first, second);
}
