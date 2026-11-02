// cl: /O2 /EHsc /MD

// BFME keeps the attack-priority table behind a pointer.  These local layout
// facades preserve the retail STL03 offsets while giving the recovered public
// method its canonical class and signature.
typedef int Int;

class ThingTemplate
{
public:
	ThingTemplate *getFinalOverride(void);

	Int m_unreconstructed_00;
	ThingTemplate *m_nextOverride;
};

struct BfmeAttackPriorityNode
{
	unsigned char m_unreconstructed_00[0x14];
	Int m_priority;
};

class BfmeAttackPriorityMap
{
public:
	void bfmeFind(BfmeAttackPriorityNode **found,
		const ThingTemplate **thingTemplate);

	BfmeAttackPriorityNode *m_end;
	Int m_size;
};

class AttackPriorityInfo
{
public:
	Int getPriority(const ThingTemplate *thingTemplate) const;

private:
	void *m_snapshotVtable;
	void *m_name;
	Int m_defaultPriority;
	BfmeAttackPriorityMap *m_priorityMap;
};

// getFinalOverride is reached through ILT 0x000022BB (body 0x00087A80, matched as
// Overridable::getFinalOverride); the ledger defines that ILT as ?j_000022bb@@YAXXZ,
// so the call names it through a member pointer.
extern void j_000022bb(void);

Int AttackPriorityInfo::getPriority(const ThingTemplate *thingTemplate) const
{
	Int priority = m_defaultPriority;

	if (thingTemplate)
	{
		const ThingTemplate *resolved = thingTemplate;
		union { void (*raw)(void); ThingTemplate *(ThingTemplate::*member)(); } finalOverride;
		finalOverride.raw = j_000022bb;
		if (thingTemplate->m_nextOverride)
			resolved = (thingTemplate->m_nextOverride->*finalOverride.member)();

		BfmeAttackPriorityMap *priorityMap = m_priorityMap;
		thingTemplate = resolved;

		if (priorityMap && priorityMap->m_size)
		{
			BfmeAttackPriorityNode *found;
			priorityMap->bfmeFind(&found, &thingTemplate);

			if (found == priorityMap->m_end)
				return priority;

			priority = found->m_priority;
		}
	}

	return priority;
}
