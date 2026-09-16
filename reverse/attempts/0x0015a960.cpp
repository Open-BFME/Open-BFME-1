// ?process@Rva0015A960BucketOwner@@QAEXPBUCoord2D@@H@Z
// partial score=0.25 date=2026-09-16
// cl: /O2 /Ob0
// Open-BFME: address-derived owner for the retail bucket pass at 0x0015A960.

typedef float Real;
typedef int Int;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Coord2D
{
	Real x;
	Real y;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	unsigned char m_pad00[4];
	Overridable *m_nextOverride;
	unsigned char m_pad08[0x43C - 0x08];
	Int m_field43C;
	Int m_field440;
};

class Object
{
public:
	unsigned char m_pad00[4];
	Overridable *m_template;
};

// The 0x0015A560 call is the independently matched max-field helper.  Its
// object layout is the same bucket shape witnessed at this call site.
class Rva0015A560List
{
public:
	Int maxOverrideField43C() const;

	Int m_count;
	Object *m_items[6];
};

class TAiData
{
public:
	unsigned char m_pad00[0xA0];
	Real m_dataA0;
	Real m_dataA4;
};

class AI
{
public:
	unsigned char m_pad00[0x14];
	TAiData *m_aiData;
};

extern AI *TheAI;
extern Real g_bfmeADL;

class Rva0015A600BucketCall
{
public:
	void apply(const Coord2D *, Int);
};

extern void d_0015a600();
typedef void (Rva0015A600BucketCall::*Rva0015A600Apply)(const Coord2D *, Int);

class Rva0015A960BucketOwner
{
public:
	void process(const Coord2D *start, Int formationID);

	Int m_count;
	Int m_bucketCapacity;
	Rva0015A560List m_buckets[10];
	Int m_candidateCount;
	Object *m_candidates[1];
	unsigned char m_pad128[0x1B4 - 0x128];
	Int m_maxValue;
};

void Rva0015A960BucketOwner::process(const Coord2D *start, Int formationID)
{
	TAiData *initialData = TheAI->m_aiData;
	Real spacing = initialData->m_dataA4;
	Int count = m_count;
	spacing *= g_bfmeADL;
	Int total = 0;
	Int bucketTotal;
	Real maxOffset = (Real)m_maxValue * initialData->m_dataA0;

	if (count > 10)
		m_count = 10;
	Int index = 0;
	if (m_count > index)
	{
		Rva0015A560List *bucket = m_buckets;
		do
		{
			bucketTotal = 0;
			if (bucket->m_count > 0)
			{
				void **item = (void **)bucket->m_items;
				Int remaining = bucket->m_count;
				do
				{
					unsigned int *objectData = (unsigned int *)*item;
					++objectData;
					_ReadWriteBarrier();
					Overridable *objectTemplate = *(Overridable **)objectData;
					if (objectTemplate && objectTemplate->m_nextOverride)
						objectTemplate = (Overridable *)objectTemplate->m_nextOverride->getFinalOverride();
					bucketTotal += objectTemplate->m_field440;
					++item;
					--remaining;
				}
				while (remaining);
			}

			Coord2D offset;
			offset.x = start->x - total * TheAI->m_aiData->m_dataA4 + spacing;
			offset.y = start->y + (maxOffset - bucketTotal * TheAI->m_aiData->m_dataA0) * g_bfmeADL;

			union
			{
				void (*asFunction)(void);
				Rva0015A600Apply asMember;
			} apply;
			apply.asFunction = d_0015a600;
			(((Rva0015A600BucketCall *)bucket)->*apply.asMember)(&offset, formationID);
			total += bucket->maxOverrideField43C();
			++index;
			bucket = (Rva0015A560List *)((char *)bucket + 0x1C);
		}
		while (index < m_count);
	}
}
