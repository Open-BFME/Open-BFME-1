// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Address-derived body at retail 0x002381C0.  The owner is not named by a
// caller or complete class record in the current evidence.
#include <list>

class AsciiString;
class ThingTemplate;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

#define TheThingFactory (*(ThingFactory **)0x012EF1D8)

typedef _STL::list<int> Rva002381C0List;

// Retail dispatches through vtable slot 0xf0.  This interface is declaration-
// only; no object or vtable is emitted by this translation unit.
class Rva002381C0Owner
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
	virtual void slot59() = 0;
	virtual void populate(Rva002381C0List *items) = 0;

	bool matchesTemplate(const ThingTemplate *expected);
};

bool Rva002381C0Owner::matchesTemplate(const ThingTemplate *expected)
{
	bool result = false;
	Rva002381C0List items;
	populate(&items);
	if (items.size() < 1)
		return result;

	char *holder = *(char **)((char *)this - 0xe0);
	holder += 0x248;
	const ThingTemplate *found = TheThingFactory->findTemplate(
		*(AsciiString *)holder);
	if (found != 0 && expected == found)
		result = true;
	return result;
}
