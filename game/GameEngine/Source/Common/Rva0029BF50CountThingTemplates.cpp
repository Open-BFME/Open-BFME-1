// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0029BF50 is a thiscall counter over the same virtual chain family
// as the matched 0x0029BF00 walk.  Its node kind-1 payload is compared through
// the existing ThingTemplate::isEquivalentTo ILT at 0x0003E80B.  The owner is
// intentionally address-derived: the retail bytes prove the raw slot ABI and
// node fields, but not a unique published class name.

typedef int Int;
typedef bool Bool;

class ThingTemplate
{
public:
	Bool isEquivalentTo(const ThingTemplate *) const;
};

static __forceinline Bool rva0029BF50Equivalent(ThingTemplate *thing,
	ThingTemplate *candidate)
{
	return thing->isEquivalentTo(candidate);
}

class Rva0029BF50Item
{
public:
	unsigned char m_unreconstructed_000[4];
	Int m_kind;
	ThingTemplate *m_template;
};

class Rva0029BF50
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual Rva0029BF50Item *firstItem();
	virtual Rva0029BF50Item *nextItem(Rva0029BF50Item *);

	Int countEquivalent(void *thing);
};

// ?countEquivalent@Rva0029BF50@@QAEHPAX@Z
Int Rva0029BF50::countEquivalent(void *thing)
{
	Rva0029BF50Item *item;
	Int count = 0;
	item = firstItem();
	while (item != 0)
	{
		if (item->m_kind == 1 &&
			rva0029BF50Equivalent((ThingTemplate *)thing, item->m_template))
			++count;
		item = nextItem(item);
	}
	return count;
}
