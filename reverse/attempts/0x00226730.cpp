// ?updateCount@Rva226730CountFlaggedOverrides@@QAEXXZ
// partial score=0.97 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

class Rva226730Override
{
public:
	Rva226730Override *getFinalOverride(void);

	unsigned long unknown;
	Rva226730Override *nextOverride;
	char gap[0xC4];
	unsigned char flags;
};

struct Rva226730ObjectHead
{
	virtual void unknown(void);
};

struct Rva226730Thing
{
	__forceinline bool isFlagged(void) const
	{
		Rva226730Override *value = templateValue;

		if (value != 0 && value->nextOverride != 0)
			value = value->nextOverride->getFinalOverride();

		return (value->flags & 2) != 0;
	}

	Rva226730Override *templateValue;
};

struct Rva226730Object : Rva226730ObjectHead, Rva226730Thing
{
};

struct Rva226730Node
{
	Rva226730Node *next;
	Rva226730Node *previous;
	Rva226730Object *object;
};

class Rva226730CountFlaggedOverrides
{
public:
	void updateCount(void);

private:
	char gap0[0x38];
	Rva226730Node *objects;
	char gap3C[0x28];
	int count;
};

void Rva226730CountFlaggedOverrides::updateCount(void)
{
	count = 0;
	Rva226730Node *node = objects->next;

	while (node != objects) {
		Rva226730Thing &thing = (Rva226730Thing &)*node->object;
		if (thing.isFlagged())
			++count;

		node = node->next;
	}
}
