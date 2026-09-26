class ThingTemplate;

class BfmeSubBIA
{
public:
	int ask();
	void *m_00;
	BfmeSubBIA *m_04;
};

class AttackPriorityInfo
{
public:
	int getPriority(const ThingTemplate *object) const;
};

struct Rva0014B880Candidate
{
	void *m_00;
	BfmeSubBIA *m_04;
};

struct Rva0014B880Context
{
	int m_00;
	AttackPriorityInfo *m_04;
};

void __cdecl rva0014b880PriorityMaximum(Rva0014B880Candidate *candidate,
	Rva0014B880Context *context)
{
	BfmeSubBIA *override = candidate->m_04;
	if (override && override->m_04)
		override = (BfmeSubBIA *)override->m_04->ask();
	int priority = context->m_04->getPriority((ThingTemplate *)override);
	if (priority > context->m_00)
		context->m_00 = priority;
}
