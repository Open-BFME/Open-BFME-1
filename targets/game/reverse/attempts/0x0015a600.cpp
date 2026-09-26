// ?apply@Rva0015A600Bucket@@QAEHPBUCoord2D@@H@Z
// partial score=0.19 date=2026-09-16
// Open-BFME: address-derived bucket worker at retail 0x0015A600.

typedef float Real;
typedef int Int;

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
	unsigned char m_pad08[0x74 - 0x08];
	Int m_field74;
	unsigned char m_pad78[0x43C - 0x78];
	Int m_field43C;
	Int m_field440;
};

class Locomotor
{
public:
	unsigned char m_pad00[4];
	Overridable *m_template;
};

class AIUpdate
{
public:
	unsigned char m_pad00[0x1CC];
	Locomotor *m_currentLocomotor;
};

class Object
{
public:
	unsigned char m_pad00[4];
	Overridable *m_template;
	unsigned char m_pad08[0x204 - 0x08];
	AIUpdate *m_ai;
	unsigned char m_pad208[0x31C - 0x208];
	Int m_formationID;
	Real m_formationOffsetX;
	Real m_formationOffsetY;
};

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
	Object *m_items[1];
};

Int Rva0015A600Bucket::apply(const Coord2D *start, Int formationID)
{
	Int value[2];
	Int total = 0;
	Int index = 0;
	if (m_count > 0)
	{
		Coord2D offset;
		offset.x = start->x;
		offset.y = start->y;
		Object **item = m_items;
		do
		{
			Object *object = *item;
			Overridable *objectTemplate = object->m_template;
			if (objectTemplate && objectTemplate->m_nextOverride)
				objectTemplate = (Overridable *)objectTemplate->m_nextOverride->getFinalOverride();
			value[0] = objectTemplate->m_field440;
			TAiData *data = TheAI->m_aiData;

			objectTemplate = object->m_template;
			if (objectTemplate && objectTemplate->m_nextOverride)
				objectTemplate = (Overridable *)objectTemplate->m_nextOverride->getFinalOverride();

			offset.y = (value[0] * g_bfmeADL + total) * data->m_formationWidth + offset.y;
			offset.x = offset.x - objectTemplate->m_field43C * data->m_formationHeight * g_bfmeADL;

			object->m_formationID = formationID;
			Object *output = *item;
			AIUpdate *ai = output->m_ai;
			if (ai)
			{
				Locomotor *locomotor = ai->m_currentLocomotor;
				if (locomotor)
				{
					Overridable *locomotorTemplate = locomotor->m_template;
					if (locomotorTemplate && locomotorTemplate->m_nextOverride)
						locomotorTemplate = (Overridable *)locomotorTemplate->m_nextOverride->getFinalOverride();
					if (locomotorTemplate->m_field74 == 0)
					{
						offset.x *= g_bfmeADL;
						offset.y *= g_bfmeADL;
					}
				}
			}

			output->m_formationOffsetX = offset.x;
			output->m_formationOffsetY = offset.y;
			total += value[0];
			++index;
			++item;
		}
		while (index < m_count);
	}
	return index;
}
