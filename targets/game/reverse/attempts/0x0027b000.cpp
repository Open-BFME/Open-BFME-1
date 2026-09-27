// ?d_0027b000@@YAXXZ
// partial score=0.39 date=2026-09-27
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Retail RVA 0x0027B000, 738 bytes. Sweep around a center point looking for
// a radius clear of KINDOF structures: steps the radius by the owner limit
// and the angle by a spacing derived from 2*pi, testing each sample against
// every iterated object, and writes the first clear sample to the out point.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"

#include "Common/BitFlags.h"

class PartitionFilter
{
public:
	virtual ~PartitionFilter() {}
};
extern "C" float __cdecl sinf(float value);
extern "C" float __cdecl cosf(float value);

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_position;
	char m_pad44[0xC0 - 0x44];
	float m_bfmeRadius;
};

typedef BitFlags<192> BfmeSweepKindOfMask;

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(
		const BfmeSweepKindOfMask &mustBeSet,
		const BfmeSweepKindOfMask &mustBeClear);
	~PartitionFilterAcceptByKindOf()
	{
		*(unsigned int *)this = 0x01083B5C;
	}
};

struct Rva0027B000Entry
{
	Object *object;
	unsigned distanceBits;
};

struct Rva009F39F0Payload
{
	_STL::vector<Rva0027B000Entry> entries;
	Rva0027B000Entry *current;
	int references;
};

struct BfmeWideResult
{
	Rva009F39F0Payload *value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);
	~BfmeWideResult();
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int a, float b, int c, int d, int e);
};

extern BfmeWideForwardC *ThePartitionManager;
extern const float g_rva001B5860TwoPi;
extern float g_bfmeDefaultBU; // retail 0x01075334, 1.0f
extern float g_bfmeDirectionWeight1285; // retail 0x01075C74, 10.0f
#define BFME_AIUPDATE_SLOT(n) virtual void bfmeUnused##n();
class AIUpdateInterface
{
public:
	BFME_AIUPDATE_SLOT(000); BFME_AIUPDATE_SLOT(001); BFME_AIUPDATE_SLOT(002); BFME_AIUPDATE_SLOT(003);
	virtual bool dup_0027b000(float a, float b, const Coord3D *center, Object *d, Object *e, Object *f, Object *g, Object *h);
	char m_pad04[4];
	Object *m_bfmeObject; // +0x08: vtable +0, pad +4
};

bool AIUpdateInterface::dup_0027b000(float a, float b, const Coord3D *center, Object *d, Object *e, Object *f, Object *g, Object *h)
{
	Object *object = m_bfmeObject;
	float limit;
	if (object == 0)
		return false;
	float candidate = object->m_bfmeRadius;
	if (candidate >= g_bfmeDirectionWeight1285)
		limit = candidate;
	else
		limit = 10.0f;
	PartitionFilterAcceptByKindOf filter(*(const BfmeSweepKindOfMask *)&a, *(const BfmeSweepKindOfMask *)&KINDOFMASK_NONE);
	BfmeWideResult iterator = ThePartitionManager->bfmeForwardWideC((int)center, b, 0, (int)&filter, 1);
	float radius = limit;
	if (radius >= b && radius <= b)
		return false;
	float step = g_bfmeDefaultBU / limit;
	do
	{
		float angle = -3.1415927f;
		float spacing = g_rva001B5860TwoPi / (radius * g_rva001B5860TwoPi * step);
		{
			float x = center->x + sinf(angle) * radius;
			float y = center->y + cosf(angle) * radius;
			float z = center->z;
			Rva009F39F0Payload *payload = iterator.value;
			Rva0027B000Entry *finish = payload->entries.end();
			Rva0027B000Entry *cursor = payload->current;
			bool blocked = false;
			while (cursor != finish)
			{
				Object *candidate = cursor->object;
				cursor += 1;
				payload->current = cursor;
				if (candidate == 0)
					continue;
				float need = candidate->m_bfmeRadius + limit;
				float dx = candidate->m_position.x - x;
				float dy = candidate->m_position.y - y;
				if (need * need > dx * dx + dy * dy)
				{
					blocked = true;
					break;
				}
			}
			if (!blocked)
			{
				d->m_position.x = x;
				d->m_position.y = y;
				d->m_position.z = z;
				return true;
			}
			angle += spacing;
		} while (angle < 3.1415927f && angle != 3.1415927f);
		radius += limit;
	} while (radius < b && radius != b);
	return false;
}
