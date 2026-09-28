// ?prepFollow@AIGroup@@QAEXW4CommandSourceType@@H@Z
// partial score=0.6 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: AIGroup::prepFollow, retail 0x0015AB50, 2416 bytes.
//
// Identity: exact matched callers groupFollowWaypointPathAsTeam 0x00155A80
// and tryGroupSpecial 0x001599A0 through ILT 0x0002E636.  Complete
// reconstruction of the whole retail algorithm (2425 B compiled, shape 0.915):
//   1 formation id, two SimpleObjectIterators, twelve 0x1BC records whose
//     inline set() clamps +4 into [2,6] (Rva0015A530::set inlined);
//   2 member walk: both iterators get dist^2 to +0x28, formation id cleared,
//     footprint = template+0x43C * template+0x440 summed, a counter of
//     locomotor-template+0x74 in [4,6] that retail keeps in memory but never
//     reads (volatile here only to keep the store; retail emits inc [mem]);
//   3 early out on an empty iterator, sort(1) both, record count =
//     ceil(total / (6 * columns)) capped at 12 unless exactly 1;
//   4 thirteen passes deal units by locomotor-template+0x74 round robin;
//   5 per record computeSize (sret) and a two-sided offset walk, then
//     computeSlot(&pos, formationID);
//   6 project the lead unit onto the +0x1C -> +0x28 line, then pairwise swap
//     formation offsets (up to 6 retries per unit) with the static helper
//     0x0015A2D0 compiled in this TU: VC7.1 gives it the private
//     eax/ecx/edx register ABI exactly as retail when its parameters are
//     declared (start, end, pt) -- NOT reachable through an extern decl;
//   7 pick the max-x / min-y offset and shift every offset by it.
// Frame: retail 0x1540, ours 0x1538 (records at +0x78, retail +0x80).  The
// Coord3D copy of the lead position explains retail's dead slot at +0x74;
// one more dead dword (retail +0x40, next to the 0x38 Coord2D slot) is
// still missing.
#include <math.h>

typedef int Int;
typedef float Real;
typedef bool Bool;

enum FormationID { NO_FORMATION_ID = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

struct Coord2D
{
	Real x, y;
	Real length( void ) const { return (Real)sqrt( x*x + y*y ); }
	void normalize( void )
	{
		Real len = length();
		if( len != 0 )
		{
			x /= len;
			y /= len;
		}
	}
};

struct Coord3D
{
	Real x, y, z;
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride( void ) const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
public:
	Overridable *m_nextOverride;
};

template <class T> class OVERRIDE
{
public:
	const T *operator->( void ) const
	{
		if (!m_overridable)
			return 0;
		return (T*) m_overridable->getFinalOverride();
	}
	operator const T*( ) const { return operator->(); }
private:
	const T *m_overridable;
};

class ThingTemplate : public Overridable
{
public:
	char m_unreconstructed_08[0x43C - 0x08];
	Int m_bfme43C;
	Int m_bfme440;
};

class LocomotorTemplate : public Overridable
{
public:
	char m_unreconstructed_08[0x74 - 0x08];
	Int m_bfme74;
};

class Locomotor
{
public:
	const LocomotorTemplate *getTemplate() const { return m_template; }
private:
	char m_unreconstructed_00[0x04];
	OVERRIDE<LocomotorTemplate> m_template;
};

class AIUpdateInterface
{
public:
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
private:
	char m_unreconstructed_00[0x1CC];
	Locomotor *m_curLocomotor;
};

class Rva001BE010
{
public:
	Int get();
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_cachedPos; }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	Locomotor *rva001BE010() { return (Locomotor *)((Rva001BE010 *)this)->get(); }
	void setFormationID(FormationID id) { m_formationID = id; }
	void setFormationOffset(const Coord2D& offset) { m_formationOffset = offset; }
	void getFormationOffset(Coord2D* offset) const { *offset = m_formationOffset; }
private:
	virtual ~Object();
	OVERRIDE<ThingTemplate> m_template;
	char m_unreconstructed_08[0x38 - 0x08];
	Coord3D m_cachedPos;
	char m_unreconstructed_44[0x204 - 0x44];
	AIUpdateInterface *m_ai;
	char m_unreconstructed_208[0x31C - 0x208];
	FormationID m_formationID;
	Coord2D m_formationOffset;
};

class SimpleObjectIterator
{
public:
	SimpleObjectIterator();
	virtual ~SimpleObjectIterator();
	virtual Object *first();
	virtual Object *next();
	void insert(Object *obj, Real numeric);
	void sort(Int order);
	Int getCount() { return m_clumpCount; }
private:
	void *m_firstClump;
	void *m_curClump;
	Int m_clumpCount;
};

class AIData
{
public:
	char m_unreconstructed_00[0xA0];
	Real m_bfmeA0;
	Real m_bfmeA4;
	Real m_bfmeA8;
	char m_unreconstructed_AC[0xB0 - 0xAC];
	Int m_bfmeB0;
};

class AI
{
public:
	FormationID getNextFormationID(void);
	const AIData *getAiData() { return m_aiData; }
private:
	char m_unreconstructed_00[0x14];
	AIData *m_aiData;
};

extern AI *TheAI;

#pragma comment(linker, "/alternatename:?getNextFormationID@AI@@QAE?AW4FormationID@@XZ=?j_00025743@@YAXXZ")

struct Rva0015AAC0Size
{
	Rva0015AAC0Size() {}
	Rva0015AAC0Size(const Rva0015AAC0Size &that) : x(that.x), y(that.y) {}
	Real x;
	Real y;
};

class BfmeFormationRecord
{
public:
	BfmeFormationRecord();
	Rva0015AAC0Size computeSize();
	void computeSlot(const Coord2D *pos, FormationID id);
	void set(Int x)
	{
		if (x < 2)
			x = 2;
		else if (x > 6)
			x = 6;
		m_columns = x;
	}
	void add(Object *obj)
	{
		if (m_memberCount < 36)
		{
			m_members[m_memberCount] = obj;
			m_memberCount++;
			m_active = false;
		}
	}
private:
	Int m_bucketCount;
	Int m_columns;
	char m_buckets[0x120 - 0x08];
	Int m_memberCount;
	Object *m_members[36];
	Int m_1b4;
	Bool m_active;
};

#pragma comment(linker, "/alternatename:??0BfmeFormationRecord@@QAE@XZ=?j_00044dfa@@YAXXZ")
#pragma comment(linker, "/alternatename:?computeSize@BfmeFormationRecord@@QAE?AURva0015AAC0Size@@XZ=?j_00045818@@YAXXZ")
#pragma comment(linker, "/alternatename:?computeSlot@BfmeFormationRecord@@QAEXPBUCoord2D@@W4FormationID@@@Z=?j_0001fe74@@YAXXZ")

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
	void prepFollow(CommandSourceType cmdSource, Int unused);
private:
	char m_bfmeHead[0x04];
	BfmeListNodeBase *m_bfmeMembers;
	char m_unreconstructed_08[0x14];		// +0x08
	Coord2D m_lineStart1C;						// +0x1C
	char m_unreconstructed_24[0x04];		// +0x24
	Coord2D m_lineEnd28;						// +0x28
};

static void rotateIntoFrame(const Coord2D *start, const Coord2D *end, Coord2D *pt)
{
	Coord2D dir;
	dir.x = end->x;
	dir.y = end->y;
	dir.x -= start->x;
	dir.y -= start->y;
	dir.normalize();
	dir.y = -dir.y;
	Coord2D perp;
	perp.x = -dir.y;
	perp.y = dir.x;
	Real px = pt->x;
	dir.x *= px;
	dir.y *= px;
	Real py = pt->y;
	perp.x *= py;
	perp.y *= py;
	Coord2D result;
	result.x = perp.x + dir.x;
	result.y = perp.y + dir.y;
	*pt = result;
}

enum { MAX_RECORDS = 12, NUM_PASSES = 13 };

void AIGroup::prepFollow(CommandSourceType cmdSource, Int unused)
{
	FormationID formationID = TheAI->getNextFormationID();
	SimpleObjectIterator *iter = new SimpleObjectIterator;
	SimpleObjectIterator *iter2 = new SimpleObjectIterator;
	Int columns = TheAI->getAiData()->m_bfmeB0 * 2;
	Int maxPerRecord = columns * 6;
	BfmeFormationRecord records[MAX_RECORDS];
	Int i;
	for (i = 0; i < MAX_RECORDS; ++i)
		records[i].set(columns);

	Int total = 0;
	volatile Int flyers = 0;
	BfmeListNodeBase *it;
	for (it = m_bfmeMembers->m_bfmeNext; it != m_bfmeMembers; it = it->m_bfmeNext)
	{
		Object *obj = ((BfmeMemberNode *)it)->m_bfmeValue;
		Real dx = obj->getPosition()->x - m_lineEnd28.x;
		Real dy = obj->getPosition()->y - m_lineEnd28.y;
		iter->insert(obj, dx*dx + dy*dy);
		dx = obj->getPosition()->x - m_lineEnd28.x;
		dy = obj->getPosition()->y - m_lineEnd28.y;
		iter2->insert(obj, dx*dx + dy*dy);
		obj->setFormationID(NO_FORMATION_ID);
		Int width = obj->getTemplate()->m_bfme43C;
		Int footprint = obj->getTemplate()->m_bfme440 * width;
		if (footprint < 1)
			footprint = 1;
		total += footprint;
		Int kind = obj->rva001BE010()->getTemplate()->m_bfme74;
		if (kind >= 4 && kind <= 6)
			flyers++;
	}

	if (iter->getCount() == 0)
	{
		delete iter;
		delete iter2;
		return;
	}

	iter->sort(1);
	iter2->sort(1);

	Int numRecords = (total + maxPerRecord - 1) / maxPerRecord;
	if (numRecords != 1 && numRecords > MAX_RECORDS)
		numRecords = MAX_RECORDS;

	Int recordIndex = 0;
	Int pass;
	for (pass = 0; pass < NUM_PASSES; ++pass)
	{
		for (Object *obj = iter->first(); obj; obj = iter->next())
		{
			AIUpdateInterface *ai = obj->getAIUpdateInterface();
			if (ai == 0 || ai->getCurLocomotor() == 0)
				continue;
			if (ai->getCurLocomotor()->getTemplate()->m_bfme74 != pass)
				continue;
			obj->setFormationID(NO_FORMATION_ID);
			records[recordIndex].add(obj);
			recordIndex++;
			if (recordIndex >= numRecords)
				recordIndex = 0;
		}
	}

	Real evenEdge = 0.0f;
	Real oddEdge = 0.0f;
	for (i = 0; i < numRecords; ++i)
	{
		Rva0015AAC0Size size = records[i].computeSize();
		Coord2D pos;
		if (i & 1)
		{
			pos.y = TheAI->getAiData()->m_bfmeA8 * 0.5f;
			pos.x = oddEdge;
			oddEdge += size.x + TheAI->getAiData()->m_bfmeA8;
		}
		else
		{
			pos.y = -size.y - TheAI->getAiData()->m_bfmeA8 * 0.5f;
			pos.x = evenEdge;
			evenEdge += size.x + TheAI->getAiData()->m_bfmeA8;
		}
		if (numRecords == 1)
			pos.y = size.y * -0.5f;
		records[i].computeSlot(&pos, formationID);
	}

	if (iter->first() == 0)
	{
		delete iter;
		delete iter2;
		return;
	}

	Coord3D front = *iter->first()->getPosition();

	Real originX = m_lineStart1C.x;
	const Coord2D *start = &m_lineStart1C;
	Real originY = start->y;
	const Coord2D *end = &m_lineEnd28;
	Coord2D dir;
	dir.x = end->x;
	dir.y = end->y;
	dir.x -= start->x;
	dir.y -= start->y;
	dir.normalize();
	Real spacing = TheAI->getAiData()->m_bfmeA4 * 0.5f;
	Coord2D offset;
	offset.x = spacing * dir.x;
	offset.y = spacing * dir.y;
	Real proj = (front.y - start->y) * dir.y + (front.x - start->x) * dir.x;
	Coord2D along;
	along.x = dir.x * proj;
	along.y = dir.y * proj;
	Coord2D shift;
	shift.x = offset.x + along.x;
	shift.y = offset.y + along.y;
	front.x = originX + shift.x;
	front.y = originY + shift.y;

	for (Object *obj = iter->first(); obj; obj = iter->next())
	{
		Int tries = 6;
		Bool swapped;
		do
		{
			swapped = false;
			AIUpdateInterface *ai = obj->getAIUpdateInterface();
			if (ai == 0 || ai->getCurLocomotor() == 0)
				break;
			tries--;
			Coord2D myRel;
			myRel.x = obj->getPosition()->x - front.x;
			myRel.y = obj->getPosition()->y - front.y;
			Coord2D myOffset;
			obj->getFormationOffset(&myOffset);
			rotateIntoFrame(start, end, &myRel);
			Bool found = false;
			Real myDy = fabs(myOffset.y - myRel.y);
			Real myDx = fabs(myOffset.x - myRel.x);
			for (Object *other = iter2->first(); other; other = iter2->next())
			{
				if (other == obj)
				{
					found = true;
					continue;
				}
				if (!found)
					continue;
				AIUpdateInterface *otherAI = other->getAIUpdateInterface();
				if (otherAI == 0)
					continue;
				Locomotor *otherLoco = otherAI->getCurLocomotor();
				if (otherLoco == 0)
					continue;
				if (ai->getCurLocomotor()->getTemplate()->m_bfme74 != otherLoco->getTemplate()->m_bfme74)
					continue;
				Coord2D otherRel;
				otherRel.x = other->getPosition()->x - front.x;
				otherRel.y = other->getPosition()->y - front.y;
				Coord2D otherOffset;
				other->getFormationOffset(&otherOffset);
				rotateIntoFrame(start, end, &otherRel);
				Real otherDx = fabs(otherOffset.x - otherRel.x);
				Real myToOtherDy = fabs(otherOffset.y - myRel.y);
				Real myToOtherDx = fabs(otherOffset.x - myRel.x);
				Real otherToMyDx = fabs(myOffset.x - otherRel.x);
				Real gain = (myDx + myDy) - (myToOtherDx + myToOtherDy);
				if (gain < 0.0f)
					continue;
				Real otherToMyDy = fabs(myOffset.y - otherRel.y);
				Real swappedCost = (otherToMyDy + myToOtherDy) * 2.0f
					+ fabs(myToOtherDx - otherToMyDx) * 0.25f + otherToMyDx + myToOtherDx;
				Real otherDy = fabs(otherOffset.y - otherRel.y);
				Real currentCost = (otherDy + myDy) * 2.0f
					+ fabs(myDx - otherDx) * 0.25f + otherDx + myDx;
				if (currentCost + gain * 0.3f > swappedCost)
				{
					Coord2D temp;
					obj->getFormationOffset(&temp);
					obj->setFormationOffset(otherOffset);
					other->setFormationOffset(temp);
					swapped = true;
					break;
				}
			}
		} while (swapped && tries > 0);
	}

	Object *best = 0;
	Real bestY = 1.0e9f;
	Real bestX = -1.0e9f;
	Object *obj;
	for (obj = iter->first(); obj; obj = iter->next())
	{
		Coord2D off;
		obj->getFormationOffset(&off);
		if (off.y < 0.0f)
			continue;
		if (off.x < bestX)
			continue;
		if (off.x == bestX && off.y > bestY)
			continue;
		bestY = off.y;
		bestX = off.x;
		best = obj;
	}

	Real adjustY = 0.0f;
	Real adjustX = 0.0f;
	if (best)
	{
		Coord2D bestOffset;
		best->getFormationOffset(&bestOffset);
		if (best->getTemplate()->m_bfme440 > 1)
		{
			adjustY = TheAI->getAiData()->m_bfmeA0 * 0.25f - bestOffset.y;
			if (bestOffset.y == 0.0f)
				adjustY = 0.0f;
			adjustX = -bestOffset.x - TheAI->getAiData()->m_bfmeA4 * 0.25f;
		}
		else
		{
			adjustY = -bestOffset.y;
		}
	}

	for (obj = iter->first(); obj; obj = iter->next())
	{
		Coord2D off;
		obj->getFormationOffset(&off);
		off.y += adjustY;
		off.x += adjustX;
		obj->setFormationOffset(off);
	}

	delete iter;
	delete iter2;
}
