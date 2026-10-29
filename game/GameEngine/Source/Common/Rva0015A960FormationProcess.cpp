// Retail [0x0015A960,0x0015AA76): 278 bytes, thiscall with two stack
// arguments (RET 8). The owner is unresolved, so its views keep
// address-derived names. Witnessed from the retail bytes: owner +0x00 bucket
// count (clamped to 10), +0x08 array of 0x1C-byte buckets {count, objects},
// +0x1B4 integer scale; TheAI's data block +0xA0/+0xA4 spacing floats; each
// object's override-walked template (+0x04, Overridable::getFinalOverride via
// ILT 0x000022BB) +0x440 integer. Per bucket it places a formation offset
// from the start point and hands it to the matched
// Rva0015A600Bucket::apply (0x0015A600, ILT 0x0004758C), then advances by
// the matched Rva0015A560List::maxOverrideField43C (0x0015A560, ILT
// 0x00049AB2). Both callees read the same bucket, so the apply view derives
// from the max view.
// The start point is read into a two-float local built by an inline
// constructor: that keeps both coordinates on the x87 stack (popped dead at
// the end) the way retail does; plain locals or a Coord2D copy do not.
// cl: /DNDEBUG /MD /O2 /I.
typedef float Real;
typedef int Int;

#include "game/Libraries/Include/Lib/Coord2D.h"

struct BucketStartPoint { Real x, y; BucketStartPoint(Real ax, Real ay) : x(ax), y(ay) {} };

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	const Overridable *finalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
	unsigned char m_pad00[4];
	Overridable *m_nextOverride;
	unsigned char m_pad08[0x440 - 0x08];
	Int m_field440;
};

template <class T> class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_obj)
			return 0;
		return (const T *)m_obj->finalOverride();
	}
	const Overridable *m_obj;
};

class Rva0015A960Object
{
public:
	unsigned char m_pad00[4];
	OVERRIDE<Overridable> m_template;
	const Overridable *getTemplate() const { return m_template.operator->(); }
};

class TAiData
{
public:
	unsigned char m_pad00[0xa0];
	Real m_dataA0;
	Real m_dataA4;
};

class AI
{
public:
	unsigned char m_pad00[0x14];
	TAiData *m_aiData;
	TAiData *getAiData() { return m_aiData; }
};
extern AI *TheAI;

class Rva0015A560List
{
public:
	Int maxOverrideField43C() const;
	Int m_count;
	Rva0015A960Object *m_items[6];
};

class Rva0015A600Bucket : public Rva0015A560List
{
public:
	Int apply(const Coord2D *offset, Int formationID);
};

class Rva0015A960BucketOwner
{
public:
	void process(const Coord2D *start, Int formationID);
	Int m_count;
	unsigned char m_pad04[4];
	Rva0015A600Bucket m_buckets[10];
	unsigned char m_pad120[0x1b4 - 0x120];
	Int m_maxValue;
};

void Rva0015A960BucketOwner::process(const Coord2D *start, Int formationID)
{
	Real halfSpacing = TheAI->getAiData()->m_dataA4 * 0.5f;
	Int count = m_count;
	Real maxOffset = m_maxValue * TheAI->getAiData()->m_dataA0;
	Int total = 0;
	if (count > 10)
		m_count = 10;
	for (Int i = 0; i < m_count; ++i)
	{
		Rva0015A600Bucket *bucket = &m_buckets[i];
		Int bucketTotal = 0;
		Int n = bucket->m_count;
		for (Int j = 0; j < n; ++j)
			bucketTotal += bucket->m_items[j]->getTemplate()->m_field440;
		BucketStartPoint pos(start->x, start->y);
		TAiData *data = TheAI->getAiData();
		Coord2D offset;
		offset.x = pos.x - total * data->m_dataA4 + halfSpacing;
		offset.y = pos.y + (maxOffset - bucketTotal * data->m_dataA0) * 0.5f;
		bucket->apply(&offset, formationID);
		total += bucket->maxOverrideField43C();
	}
}
