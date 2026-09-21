// cl: /DNDEBUG /MD /EHsc

// Retail RVA 0x0024D520 has a 160-byte thiscall body with one float argument.
// The carved boundary proves the start and the ret 4 ending.
// The owner and method name remain unknown, so the source keeps the RVA in its name.

#include <math.h>

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

extern const Real BfmeZeroRange;

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

class Locomotor;

class Object
{
public:
	unsigned char m_leading[0x44];
	volatile Real m_field44;

	Real getField44() const
	{
		return m_field44;
	}
};

class Locomotor
{
public:
	Real getMaxTurnRate(Object *object) const;
};

Real normalizeAngle(Real angle);

class Rva0024D520
{
public:
	bool method(float threshold);
};

bool Rva0024D520::method(float threshold)
{
	Rva0024D520Base *base =
		(Rva0024D520Base *)((char *)this - 0xC4);
	Rva0024D520List *list = base->getList();

	Real lastTurnRate = 0.0f;
	Object *object;

	for (Rva0024D520Node *node = list->head->next;
		node != list->head;
		node = node->next)
	{
		object = (Object *)node->payload;

		if (lastTurnRate == BfmeZeroRange &&
			((Rva001BE010 *)object)->get())
		{
			Object *argument = object;
			lastTurnRate =
				((Locomotor *)((Rva001BE010 *)object)->get())->getMaxTurnRate(argument);
		}

		Real diff = normalizeAngle(threshold - object->getField44());
		diff = (Real)fabs(diff);

		if (diff > lastTurnRate)
			return false;
	}

	return true;
}
