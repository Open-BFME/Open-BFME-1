// ?visit@Rva001A4DD0GridCount@@QAEXPBUCoord3D@@MPAURva001A4DD0Result@@EH@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "Lib/BaseType.h"
#include "GameLogic/PolygonTrigger.h"

struct Rva001A4DD0Result { int count; PolygonTrigger *trigger; };

extern "C" __declspec(dllimport) double floor(double);
extern "C" __declspec(dllimport) double ceil(double);

#undef REAL_TO_INT_FLOOR
#define REAL_TO_INT_FLOOR(x) fast_float2long_round((Real)floor((double)(x)))
#undef REAL_TO_INT_CEIL
#define REAL_TO_INT_CEIL(x) fast_float2long_round((Real)ceil((double)(x)))

struct Rva001A4DD0Record
{
	Coord3D position;
	int key;
	int field10;
	int field14;
	unsigned char hidden;
	char pad19[0x13];
	unsigned char flag2c;
	unsigned char flag2d;
	short next;
};

class Rva001A4DD0GridCount
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void getExtent(Region3D *bounds);
	void visit(const Coord3D *position, Real radius, Rva001A4DD0Result *payload,
		unsigned char filter, int mode);

private:
	char pad04[0x558];
	Rva001A4DD0Record *m_begin;
	Rva001A4DD0Record *m_end;
	char pad564[4];
	short m_cells[50 * 50];
};

// Retail 0x001A4DD0 is 835 bytes through ret 0x14 at 0x001A5110;
// the former 829-byte dump stopped before add esp,0x4c at 0x001A510D.
// Caller 0x001A6370 passes center, radius, {count, trigger}, and two filters.
// Receiver layout is witnessed by this body and the landed grid scans at
// 0x001A4A00, 0x001A51F0 and 0x001A55E0: extent slot +0x28, record range
// +0x55C/+0x560, 0x30-byte records, and 50x50 short cell heads at +0x568.
// The ZH W3DTreeBuffer::unitMoved grid scan is a structural relative only;
// the owner's identity is not established. Keep the address-derived name.
// Call 0x0004AB6F routes to PolygonTrigger::pointInTrigger at 0x0018F8A0.
// Preserve the indexed key test separately from the retained record pointer:
// it produces retail's pointer materialization and later scratch allocation.
void Rva001A4DD0GridCount::visit(const Coord3D *position, Real radius,
	Rva001A4DD0Result *payload, unsigned char filter, int mode)
{
	int count = m_end - m_begin;
	if (count == 0)
		return;

	radius += 7.0f;
	Region3D bounds;
	getExtent(&bounds);

	Real x = position->x - radius;
	Real y = position->y - radius;
	if (x < bounds.lo.x) x = bounds.lo.x;
	if (y < bounds.lo.y) y = bounds.lo.y;
	if (x > bounds.hi.x) x = bounds.hi.x;
	if (y > bounds.hi.y) y = bounds.hi.y;
	Real xRatio = (x - bounds.lo.x) / (bounds.hi.x - bounds.lo.x);
	// Retail scales by 49.9, a 50-cell grid; Zero Hour's grid was 100 cells (99.9).
	int xMin = REAL_TO_INT_FLOOR(xRatio * (50 - 0.1f));
	Real yRatio = (y - bounds.lo.y) / (bounds.hi.y - bounds.lo.y);
	int yMin = REAL_TO_INT_FLOOR(yRatio * (50 - 0.1f));

	x = position->x + radius;
	y = position->y + radius;
	if (x < bounds.lo.x) x = bounds.lo.x;
	if (y < bounds.lo.y) y = bounds.lo.y;
	if (x > bounds.hi.x) x = bounds.hi.x;
	if (y > bounds.hi.y) y = bounds.hi.y;
	Real xMaxRatio = (x - bounds.lo.x) / (bounds.hi.x - bounds.lo.x);
	int xMax = REAL_TO_INT_CEIL(xMaxRatio * (50 - 0.1f));
	Real yMaxRatio = (y - bounds.lo.y) / (bounds.hi.y - bounds.lo.y);
	int yMax = REAL_TO_INT_CEIL(yMaxRatio * (50 - 0.1f));

	for (int xIndex = xMin; xIndex < xMax; ++xIndex)
	{
		for (int yIndex = yMin; yIndex < yMax; ++yIndex)
		{
			int entry = m_cells[xIndex + 50 * yIndex];
			while (entry != -1)
			{
				if (entry < 0 || entry >= count)
					break;
				Rva001A4DD0Record *record = m_begin + entry;
				if (m_begin[entry].key == 0)
					goto nextRecord;
				if (filter && record->hidden)
					goto nextRecord;
				if (mode == 1)
				{
					if (record->flag2c)
						goto checkDistance;
					goto nextRecord;
				}
				if (mode == 2 && !record->flag2d)
					goto nextRecord;
			checkDistance:
				{
					Coord3D delta;
					delta.set(record->position.x, record->position.y, record->position.z);
					delta.sub(position);
					if (radius * radius > delta.lengthSqr())
					{
						ICoord3D point;
						point.x = (int)record->position.x;
						point.y = (int)record->position.y;
						point.z = (int)record->position.z;
						if (payload->trigger->pointInTrigger(point)) ++payload->count;
					}
				}
			nextRecord:
				entry = record->next;
			}
		}
	}
}
