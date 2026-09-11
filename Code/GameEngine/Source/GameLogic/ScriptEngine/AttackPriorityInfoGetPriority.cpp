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

Int AttackPriorityInfo::getPriority(const ThingTemplate *thingTemplate) const
{
	Int priority = m_defaultPriority;

	if (thingTemplate)
	{
		const ThingTemplate *resolved = thingTemplate;
		if (thingTemplate->m_nextOverride)
			resolved = thingTemplate->m_nextOverride->getFinalOverride();

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
