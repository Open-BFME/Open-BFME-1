// ?scanTurnRates@Rva0024D520@@QAE_NM@Z
// partial score=0.45 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc
// Carved body at retail RVA 0x0024D520 (160 B).  A this-relative accessor at
// this-0xC4 supplies a vtable whose slot 0x104 (index 65) returns a list-like
// container; each node's payload (at node+8) is an object walked through the
// pinned guarded-field getter at 0x001BE010 (class Rva001BE010::get, called
// twice per element) and Locomotor::getMaxTurnRate(Object*) at 0x001B5860,
// with the running turn rate normalized through normalizeAngle at 0x001056F0
// and compared against the global BfmeZeroRange at VA 0x01075350.
// Identity of the owning class/method is not proven (no caller, no vtable
// install site); every name below is address-derived.

typedef float Real;

struct Rva0024D520Node
{
	Rva0024D520Node *next;
	Rva0024D520Node *prev;
	void *payload;
};

struct Rva0024D520List
{
	Rva0024D520Node *head;
};

extern const float BfmeZeroRange;

class Rva0024D520Base
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
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64();
	virtual Rva0024D520List *getList();
};

class Rva001BE010
{
public:
	int get();
};

class Object;

class Locomotor
{
public:
	Real getMaxTurnRate(Object *obj) const;
};

Real normalizeAngle(Real angle);

class Rva0024D520
{
public:
	bool scanTurnRates(float threshold);
};

bool Rva0024D520::scanTurnRates(float threshold)
{
	Rva0024D520Base *base = (Rva0024D520Base *)((char *)this - 0xC4);
	Rva0024D520List *list = base->getList();

	Real lastTurnRate = 0.0f;

	for (Rva0024D520Node *node = list->head->next; node != list->head; node = node->next)
	{
		if (!(BfmeZeroRange > lastTurnRate))
			continue;

		Object *object = (Object *)node->payload;

		if (!((Rva001BE010 *)object)->get())
			continue;

		Locomotor *loco = (Locomotor *)((Rva001BE010 *)object)->get();
		lastTurnRate = loco->getMaxTurnRate(object);

		Real diff = normalizeAngle(threshold - lastTurnRate);
		if (diff < 0.0f)
			diff = -diff;

		if (diff >= threshold)
		{
			if (node->next == list->head)
				return false;
			continue;
		}
	}

	return true;
}
