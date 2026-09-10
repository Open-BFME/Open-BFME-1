// ?prepFollow@AIGroup@@QAEXW4CommandSourceType@@H@Z
// partial score=0.3 date=2026-09-09
// Research-only semantic attempt for the BFME AIGroup formation planner.
// Retail boundary: 0x0015AB50, 2416 bytes.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride(void) const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
};

class Object;

enum CommandSourceType { BFME_COMMAND_SOURCE };

class SimpleObjectIterator
{
public:
	SimpleObjectIterator();
	virtual ~SimpleObjectIterator();
	virtual Object *first();
	virtual Object *next();
	void insert(Object *obj, float numeric);
	void sort(int order);
};

class Object
{
public:
	const ThingTemplate *getTemplate(void) const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride)
			tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
		return tmpl;
	}

	float getPosX(void) const { return m_position.x; }
	float getPosY(void) const { return m_position.y; }
	void *getAI(void) { return m_ai; }

	private:
	virtual ~Object();
	const ThingTemplate *m_template;
	unsigned char m_unreconstructed_08[0x38 - 0x08];
	Coord3D m_position;
	unsigned char m_unreconstructed_44[0x204 - 0x44];
	void *m_ai;
};

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;
	BfmeListNodeBase *m_bfmePrev;
};

struct BfmeMemberNode : public BfmeListNodeBase
{
	Object *m_bfmeValue;
};

class AIGroup
{
public:
	void prepFollow(CommandSourceType cmdSource, int unused);

private:
	char m_bfmeHead[4];
	BfmeListNodeBase *m_bfmeMembers;
};

struct BfmeFormationRecord
{
	BfmeFormationRecord() : m_columns(0), m_memberCount(0), m_active(0) { }

	int m_columns;
	unsigned char m_unreconstructed_04[0x120 - 0x04];
	int m_memberCount;
	Object *m_members[37];
	unsigned char m_active;
	unsigned char m_unreconstructed_1b9[0x1bc - 0x1b9];
};

struct BfmeFormationTable
{
	unsigned char m_unreconstructed_00[0xb0];
	int m_defaultColumns;
};

struct BfmeAIFormationState
{
	unsigned char m_unreconstructed_00[0x14];
	BfmeFormationTable *m_formationTable;
};

extern BfmeAIFormationState *TheAI;

struct BfmeFormationUnitAI
{
	unsigned char m_unreconstructed_00[0x1cc];
	void *m_locomotor;
};

static int bfmeFormationFootprint(const Object *obj)
{
	const ThingTemplate *tmpl = obj->getTemplate();
	if (tmpl == 0)
		return 1;

	const unsigned char *raw = (const unsigned char *)tmpl;
	int width = *(const int *)(raw + 0x43c);
	int depth = *(const int *)(raw + 0x440);
	int footprint = width * depth;
	return footprint < 1 ? 1 : footprint;
}

void AIGroup::prepFollow(CommandSourceType cmdSource, int unused)
{
	(void)cmdSource;
	(void)unused;

	SimpleObjectIterator *nearCenter = new SimpleObjectIterator;
	SimpleObjectIterator *nearFormation = new SimpleObjectIterator;
	BfmeFormationRecord records[12];

	int columns = TheAI->m_formationTable->m_defaultColumns;
	if (columns < 2)
		columns = 2;
	if (columns > 6)
		columns = 6;
	for (int i = 0; i < 12; ++i)
		records[i].m_columns = columns;

	const float centerX = *(const float *)((const unsigned char *)this + 0x28);
	const float centerY = *(const float *)((const unsigned char *)this + 0x2c);
	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
		it != m_bfmeMembers;
		it = it->m_bfmeNext)
	{
		Object *obj = ((BfmeMemberNode *)it)->m_bfmeValue;
		if (obj == 0)
			continue;

		float dx = obj->getPosX() - centerX;
		float dy = obj->getPosY() - centerY;
		float distance = dx * dx + dy * dy;
		nearCenter->insert(obj, distance);
		nearFormation->insert(obj, distance);
		*(unsigned int *)((unsigned char *)obj + 0x31c) = 0;
	}

	nearCenter->sort(1);
	nearFormation->sort(1);

	int recordCount = 0;
	for (Object *obj = nearCenter->first(); obj; obj = nearCenter->next())
	{
		BfmeFormationUnitAI *unitAI =
			(BfmeFormationUnitAI *)obj->getAI();
		if (unitAI == 0 || unitAI->m_locomotor == 0)
			continue;

		int footprint = bfmeFormationFootprint(obj);
		if (footprint > 1)
			++recordCount;
	}

	int selectedRecords = (recordCount + columns - 1) / columns;
	if (selectedRecords < 1)
		selectedRecords = 1;
	if (selectedRecords > 12)
		selectedRecords = 12;

	int recordIndex = 0;
	for (Object *obj = nearFormation->first(); obj && recordIndex < selectedRecords;
		obj = nearFormation->next())
	{
		BfmeFormationUnitAI *unitAI =
			(BfmeFormationUnitAI *)obj->getAI();
		if (unitAI == 0 || unitAI->m_locomotor == 0)
			continue;

		BfmeFormationRecord &record = records[recordIndex];
		int slot = record.m_memberCount;
		if (slot >= 0 && slot < 36)
		{
			record.m_members[slot] = obj;
			++record.m_memberCount;
			*(unsigned int *)((unsigned char *)obj + 0x31c) =
				(unsigned int)recordIndex;
			*(float *)((unsigned char *)obj + 0x320) =
				(float)(slot % record.m_columns);
			*(float *)((unsigned char *)obj + 0x324) =
				(float)(slot / record.m_columns);
		}
		if (record.m_memberCount >= 36)
			++recordIndex;
	}

	delete nearFormation;
	delete nearCenter;
}
