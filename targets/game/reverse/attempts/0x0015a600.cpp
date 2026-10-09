// ?apply@Rva0015A600Bucket@@QAEHPBUCoord2D@@H@Z
// partial score=0.9545 date=2026-10-09
// cl: /I.

typedef float Real;
typedef int Int;

#include "game/Libraries/Include/Lib/Coord2D.h"

class Overridable
{
public:
    const Overridable *getFinalOverride() const;
    Overridable *&m_nextOverride() { return *(Overridable **)((char *)this + 4); }
    Int &m_field74() { return *(Int *)((char *)this + 0x74); }
    Int &m_field43C() { return *(Int *)((char *)this + 0x43C); }
    Int &m_field440() { return *(Int *)((char *)this + 0x440); }
};

class Locomotor
{
public:
	unsigned char m_pad00[4];
	Overridable *m_template;
};

// Layout view of the AI interface reached through Object.
class AIUpdate
{
public:
	unsigned char m_pad00[0x1CC];
	Locomotor *m_currentLocomotor;
};

#define OBJECT_TU_MEMBERS \
    Int &m_formationID() { return *(Int *)((char *)this + 0x31C); } \
    Real &m_formationOffsetX() { return *(Real *)((char *)this + 0x320); } \
    Real &m_formationOffsetY() { return *(Real *)((char *)this + 0x324); } \
    void setFormationID(Int formationID) { m_formationID() = formationID; } \
    void setFormationOffset(const Coord2D &offset) { *(Coord2D *)&m_formationOffsetX() = offset; }
#include "game/GameEngine/Source/GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

class TAiData
{
public:
	unsigned char m_pad00[0xA0];
	Real m_formationWidth;
	Real m_formationHeight;
};

class AI
{
public:
	unsigned char m_pad00[0x14];
	TAiData *m_aiData;
};

extern AI *TheAI;
extern Real g_bfmeADL;

class Rva0015A600Bucket
{
public:
	Int apply(const Coord2D *start, Int formationID);

	Int m_count;
	Object *m_items[6];
};

Int Rva0015A600Bucket::apply(const Coord2D *start, Int formationID)
{
	Int total;
	Int index;
	total = index = 0;
	if (m_count > 0)
	{
		Object **item = m_items;
		do
		{
			Coord2D offset = *start;
			Object *object = *item;
			Overridable *objectTemplate = (Overridable *)object->m_template;
			if (objectTemplate && objectTemplate->m_nextOverride())
				objectTemplate = (Overridable *)objectTemplate->m_nextOverride()->getFinalOverride();
			Int value = objectTemplate->m_field440();
			TAiData *data = TheAI->m_aiData;

			offset.y = (value * 0.5f + total) * data->m_formationWidth + offset.y;

			objectTemplate = (Overridable *)object->m_template;
			if (objectTemplate && objectTemplate->m_nextOverride())
				objectTemplate = (Overridable *)objectTemplate->m_nextOverride()->getFinalOverride();

			offset.x = offset.x - objectTemplate->m_field43C() * data->m_formationHeight * 0.5f;

			object->setFormationID(formationID);
			Object *output = *item;
			AIUpdate *ai = (AIUpdate *)output->m_ai;
			if (ai)
			{
				Locomotor *locomotor = ai->m_currentLocomotor;
				if (locomotor)
				{
					Overridable *locomotorTemplate = locomotor->m_template;
					if (locomotorTemplate && locomotorTemplate->m_nextOverride())
						locomotorTemplate = (Overridable *)locomotorTemplate->m_nextOverride()->getFinalOverride();
					if (locomotorTemplate->m_field74() == 0)
					{
						offset.x *= 0.5f;
						offset.y *= 0.5f;
					}
				}
			}

			output->setFormationOffset(offset);
			total += value;
			++index;
			++item;
		}
		while (index < m_count);
	}
	return index;
}
