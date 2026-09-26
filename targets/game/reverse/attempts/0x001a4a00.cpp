// ?scan@Rva001A4A00RecordGridScan@@QAEXPBUCoord3D@@MPAVBfmeHostEZ@@_NH@Z
// partial score=0.987 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include <vector>
#include "Lib/BaseType.h"

extern "C" __declspec(dllimport) double BfmeFloorER(double);
extern "C" __declspec(dllimport) double bfmeMathVE(double);

#undef REAL_TO_INT_FLOOR
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)BfmeFloorER((double)(x))))
#undef REAL_TO_INT_CEIL
#define REAL_TO_INT_CEIL(x) (fast_float2long_round((Real)bfmeMathVE((double)(x))))

struct BfmeNodeEZ
{
	Coord3D m_bfmePosEZ;
	int m_bfmeTagEZ;
};

struct BfmeVec2EZ
{
	float x;
	float y;
};

class BfmeHostEZ
{
public:
	void bfmeConsiderEZ(BfmeNodeEZ *n, const BfmeVec2EZ *p);
};

struct Rva001A4A00Record
{
	Coord3D m_bfmePosEZ;
	int m_bfmeTagEZ;
	char m_pad10[8];
	bool m_skip18;
	char m_pad19[0x13];
	bool m_flag2c;
	bool m_flag2d;
	short m_next2e;
};

class Rva001A4A00RecordGridScan
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
	void scan(const Coord3D *pos, Real radius, BfmeHostEZ *host, bool skip, int filter);

private:
	char m_pad04[0x558];
	std::vector<Rva001A4A00Record> m_records;
	short m_areaPartition[50 * 50];
};

// ?scan@Rva001A4A00RecordGridScan@@QAEXPBUCoord3D@@MPAVBfmeHostEZ@@_NH@Z
void Rva001A4A00RecordGridScan::scan(const Coord3D *pos, Real radius, BfmeHostEZ *host, bool skip, int filter)
{
	int count = m_records.size();
	if (!count)
		return;

	radius += *(const Real *)0x0109C34C;
	Region3D bounds;
	getExtent(&bounds);
	Real x = pos->x - radius;
	Real y = pos->y - radius;
	if (x < bounds.lo.x) x = bounds.lo.x;
	if (y < bounds.lo.y) y = bounds.lo.y;
	if (x > bounds.hi.x) x = bounds.hi.x;
	if (y > bounds.hi.y) y = bounds.hi.y;
	Real xRatio = (x - bounds.lo.x) / (bounds.hi.x - bounds.lo.x);
	int xIndex = REAL_TO_INT_FLOOR(xRatio * *(const Real *)0x0109C348);
	Real yRatio = (y - bounds.lo.y) / (bounds.hi.y - bounds.lo.y);
	int yIndex = REAL_TO_INT_FLOOR(yRatio * *(const Real *)0x0109C348);

	x = pos->x + radius;
	y = pos->y + radius;
	if (x < bounds.lo.x) x = bounds.lo.x;
	if (y < bounds.lo.y) y = bounds.lo.y;
	if (x > bounds.hi.x) x = bounds.hi.x;
	if (y > bounds.hi.y) y = bounds.hi.y;
	Real xMaxRatio = (x - bounds.lo.x) / (bounds.hi.x - bounds.lo.x);
	int xMax = REAL_TO_INT_CEIL(xMaxRatio * *(const Real *)0x0109C348);
	Real yMaxRatio = (y - bounds.lo.y) / (bounds.hi.y - bounds.lo.y);
	int yMax = REAL_TO_INT_CEIL(yMaxRatio * *(const Real *)0x0109C348);

	for (int i = xIndex; i < xMax; ++i) {
		for (int j = yIndex; j < yMax; ++j) {
			int index = m_areaPartition[i + 50*j];
			while (index != -1) {
				if (index < 0 || index >= count)
					break;
				Rva001A4A00Record *record = &m_records[index];
				if (record->m_bfmeTagEZ && (!skip || !record->m_skip18)) {
					if (filter == 1) {
						if (record->m_flag2c) goto checkRecord;
						goto nextRecord;
					}
					if (filter == 2 && !record->m_flag2d) goto nextRecord;
				checkRecord:
					Coord3D delta;
					delta.set(record->m_bfmePosEZ.x,
						record->m_bfmePosEZ.y, record->m_bfmePosEZ.z);
					delta.sub(pos);
					if (radius*radius > delta.lengthSqr())
						host->bfmeConsiderEZ((BfmeNodeEZ *)record, (const BfmeVec2EZ *)pos);
				}
			nextRecord:
				index = record->m_next2e;
			}
		}
	}
}
