// ?visit@Rva001A55E0GridVisitByte@@QAEXPBUCoord3D@@MPBEEH@Z
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
#include "Lib/BaseType.h"

extern "C" __declspec(dllimport) double floor(double);
extern "C" __declspec(dllimport) double ceil(double);

#undef REAL_TO_INT_FLOOR
#define REAL_TO_INT_FLOOR(x) fast_float2long_round((Real)floor((double)(x)))
#undef REAL_TO_INT_CEIL
#define REAL_TO_INT_CEIL(x) fast_float2long_round((Real)ceil((double)(x)))

struct Rva001A55E0Record
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

class Rva001A55E0GridVisitByte
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
	void visit(const Coord3D *position, Real radius, const unsigned char *payload,
		unsigned char filter, int mode);

private:
	char pad04[0x558];
	Rva001A55E0Record *m_begin;
	Rva001A55E0Record *m_end;
	char pad564[4];
	short m_cells[50 * 50];
};

class Rva001A55E0Visual
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
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void notify(int key, unsigned char payload);
};

class TerrainVisual;
extern TerrainVisual *TheTerrainVisual;

// Retail 0x001A55E0: 801 bytes through ret 0x14. Matched 0x001A6520
// takes a byte by value and passes its address plus two zero filters through
// ILT 0x00002C39. The receiver remains an address-derived terrain grid view.
// Visual vtable slot +0xA8 receives the record key and zero-extended byte.
// Capture the key through the indexed vector expression once, then retain
// it through the distance test; this preserves retail's EDX allocation.
void Rva001A55E0GridVisitByte::visit(const Coord3D *position, Real radius,
	const unsigned char *payload, unsigned char filter, int mode)
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
				Rva001A55E0Record *record = m_begin + entry;
				int key = m_begin[entry].key;
				if (key == 0)
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
					delta.x = record->position.x;
					delta.y = record->position.y;
					delta.z = record->position.z;
					delta.sub(position);
					if (radius * radius > delta.x * delta.x + delta.y * delta.y + delta.z * delta.z)
					{
						Rva001A55E0Visual *visual = (Rva001A55E0Visual *)TheTerrainVisual;
						visual->notify(key, *payload);
					}
				}
			nextRecord:
				entry = record->next;
			}
		}
	}
}
