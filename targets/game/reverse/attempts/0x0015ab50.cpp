// ?prepFollow@AIGroup@@QAEXW4CommandSourceType@@H@Z
// partial score=0.4 date=2026-09-19
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: AIGroup::prepFollow, retail 0x0015AB50, 2416 bytes.
//
// Identity is established by the exact groupFollowWaypointPathAsTeam and
// tryGroupSpecial callers through ILT 0x0002E636.  This first source pass is
// the banked semantic reconstruction; the retail body also contains the
// formation comparison/swap phase after the initial record fill.

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

class BfmeAIUpdateInterface
{
public:
	unsigned char m_unreconstructed_00[4];
	void *m_locomotor;
};

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

private:
	unsigned char m_unreconstructed_04[0x0c];
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
	BfmeAIUpdateInterface *getAIUpdateInterface(void);

private:
	virtual ~Object();
	const ThingTemplate *m_template;
	unsigned char m_unreconstructed_08[0x38 - 0x08];
	Coord3D m_position;
	unsigned char m_unreconstructed_44[0x204 - 0x44];
	void *m_ai;
};

#pragma comment(linker, "/alternatename:?getAIUpdateInterface@Object@@QAEPAVBfmeAIUpdateInterface@@XZ=?j_00021017@@YAXXZ")

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;
	BfmeListNodeBase *m_bfmePrev;
};

struct BfmeMemberNode : public BfmeListNodeBase
{
	Object *m_bfmeValue;
};

extern void j_00044dfa(void);

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
	void initialize(void);
	void computeCenter(float *out);
	void computeSlot(float *out, int selector);

	int m_columns;
	unsigned char m_unreconstructed_04[0x120 - 0x04];
	int m_memberCount;
	Object *m_members[37];
	unsigned char m_active;
	unsigned char m_unreconstructed_1b9[0x1bc - 0x1b9];
};

struct BfmePrepScratch
{
	unsigned char m_unreconstructed_00[0x10];
	float m_centerOffset[2];
	unsigned char m_unreconstructed_18[0x14];
	int m_formationID;
	unsigned char m_unreconstructed_30[4];
	float m_slotOffset[2];
	unsigned char m_unreconstructed_3c[0x1c];
};

struct BfmePrepFrame
{
	BfmePrepScratch m_scratch;
	BfmeFormationRecord m_records[12];
};

struct BfmeFormationTable
{
	unsigned char m_unreconstructed_00[0xb0];
	int m_defaultColumns;
};

#pragma comment(linker, "/alternatename:?initialize@BfmeFormationRecord@@QAEXXZ=?j_00044dfa@@YAXXZ")
#pragma comment(linker, "/alternatename:?computeCenter@BfmeFormationRecord@@QAEXPAM@Z=?j_00045818@@YAXXZ")
#pragma comment(linker, "/alternatename:?computeSlot@BfmeFormationRecord@@QAEXPAMH@Z=?j_0001fe74@@YAXXZ")

enum FormationID
{
	BFME_NO_FORMATION_ID = -1
};

class AI
{
public:
	FormationID getNextFormationID(void);
	unsigned char m_unreconstructed_00[0x14];
	BfmeFormationTable *m_aiData;
};

extern AI *TheAI;

#pragma comment(linker, "/alternatename:?getNextFormationID@AI@@QAE?AW4FormationID@@XZ=?j_00025743@@YAXXZ")

struct BfmeFormationUnitAI
{
	unsigned char m_unreconstructed_00[0x1cc];
	BfmeAIUpdateInterface *m_locomotor;
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

	AIGroup *group = this;
	__declspec(align(8)) BfmePrepFrame frame;
	frame.m_scratch.m_formationID = (int)TheAI->getNextFormationID();
	SimpleObjectIterator *nearFormation = new SimpleObjectIterator;
	SimpleObjectIterator *nearCenter = new SimpleObjectIterator;
	BfmeFormationRecord *records = frame.m_records;
	for (int i = 0; i < 12; ++i)
		records[i].initialize();

	int columns = TheAI->m_aiData->m_defaultColumns;
	if (columns < 2)
		columns = 2;
	if (columns > 6)
		columns = 6;
	for (int i = 0; i < 12; ++i)
		records[i].m_columns = columns;

	const float centerX = *(const float *)((const unsigned char *)group + 0x28);
	const float centerY = *(const float *)((const unsigned char *)group + 0x2c);
	for (BfmeListNodeBase *it = group->m_bfmeMembers->m_bfmeNext;
		it != group->m_bfmeMembers;
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

	int specialCount = 0;
	int recordCount = 0;
	for (Object *obj = nearCenter->first(); obj; obj = nearCenter->next())
	{
		BfmeAIUpdateInterface *update = obj->getAIUpdateInterface();
		if (update == 0 || update->m_locomotor == 0)
			continue;

		int footprint = bfmeFormationFootprint(obj);
		recordCount += footprint;

		const ThingTemplate *tmpl = obj->getTemplate();
		if (tmpl != 0)
		{
			int formationClass =
				*(const int *)((const unsigned char *)tmpl + 0x74);
			if (formationClass >= 4 && formationClass <= 6)
				++specialCount;
		}
	}

	int selectedRecords = (recordCount + columns - 1) / columns;
	if (selectedRecords > 12)
		selectedRecords = 12;

	int pass = 0;
	int recordIndex = 0;
	while (pass < 13)
	{
		for (Object *obj = nearFormation->first(); obj;
			obj = nearFormation->next())
		{
			BfmeFormationUnitAI *unitAI =
				(BfmeFormationUnitAI *)obj->getAI();
			if (unitAI == 0 || unitAI->m_locomotor == 0)
				continue;

			const ThingTemplate *tmpl = obj->getTemplate();
			if (tmpl == 0 || *(const int *)((const unsigned char *)tmpl + 0x74)
				!= pass)
				continue;

			BfmeFormationRecord &record = records[recordIndex];
			int slot = record.m_memberCount;
			*(unsigned int *)((unsigned char *)obj + 0x31c) = 0;
			if (slot < 36)
			{
				record.m_members[slot] = obj;
				++record.m_memberCount;
				record.m_active = 0;
			}

			++recordIndex;
			if (recordIndex >= selectedRecords)
				recordIndex = 0;
		}
		++pass;
	}

	frame.m_scratch.m_centerOffset[0] = 0.0f;
	frame.m_scratch.m_centerOffset[1] = 0.0f;
	frame.m_scratch.m_slotOffset[0] = 0.0f;
	frame.m_scratch.m_slotOffset[1] = 0.0f;
	if (selectedRecords > 0)
	{
		records[0].computeCenter(frame.m_scratch.m_centerOffset);
		if ((specialCount & 1) != 0)
		{
			frame.m_scratch.m_centerOffset[0] +=
				*(const float *)((const unsigned char *)TheAI->m_aiData + 0xa8);
			frame.m_scratch.m_centerOffset[1] += (float)pass;
		}
		else
		{
			frame.m_scratch.m_centerOffset[0] =
				-frame.m_scratch.m_centerOffset[0];
			frame.m_scratch.m_centerOffset[1] +=
				*(const float *)((const unsigned char *)TheAI->m_aiData + 0xa8);
		}

		for (int i = 0; i < selectedRecords; ++i)
		{
			records[i].computeSlot(frame.m_scratch.m_slotOffset,
				frame.m_scratch.m_formationID);
			for (Object *obj = nearFormation->first(); obj;
				obj = nearFormation->next())
			{
				if (*(unsigned int *)((unsigned char *)obj + 0x31c) != 0)
					continue;
				float *objectX = (float *)((unsigned char *)obj + 0x320);
				float *objectY = (float *)((unsigned char *)obj + 0x324);
				*objectX += frame.m_scratch.m_slotOffset[0];
				*objectY += frame.m_scratch.m_slotOffset[1];
			}
		}
	}

	delete nearFormation;
	delete nearCenter;
}
