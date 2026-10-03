// ?scan@Rva001A4A00RecordGridScan@@QAEXPBUCoord3D@@MPAVBfmeHostEZ@@_NH@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Retail 0x001A4A00: 777-byte record-grid query ending in ret 0x14.
// Caller 0x001A6320 reaches this through ILT 0x00002400. Record/vector/grid
// offsets are read from retail; the unknown owner stays address-derived.
// ILT 0x00031345 calls the matched 0x001A3280 BfmeHostEZ::bfmeConsiderEZ.
// Query coordinates use the native Coord3D operations. The indexed tag read
// must remain separate from the retained record pointer for retail allocation.
#include <vector>
#include "Lib/BaseType.h"

extern "C" __declspec(dllimport) double floor(double);
extern "C" __declspec(dllimport) double ceil(double);

#undef REAL_TO_INT_FLOOR
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))
#undef REAL_TO_INT_CEIL
#define REAL_TO_INT_CEIL(x) (fast_float2long_round((Real)ceil((double)(x))))

class BfmeNodeEZ;
class BfmeVec2EZ;

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

	radius += 7.0f;
	Region3D bounds;
	getExtent(&bounds);
	Real x = pos->x - radius;
	Real y = pos->y - radius;
	if (x < bounds.lo.x) x = bounds.lo.x;
	if (y < bounds.lo.y) y = bounds.lo.y;
	if (x > bounds.hi.x) x = bounds.hi.x;
	if (y > bounds.hi.y) y = bounds.hi.y;
	Real xRatio = (x - bounds.lo.x) / (bounds.hi.x - bounds.lo.x);
	// Retail scales by 49.9, a 50-cell grid; Zero Hour's grid was 100 cells (99.9).
	int xIndex = REAL_TO_INT_FLOOR(xRatio * (50 - 0.1f));
	Real yRatio = (y - bounds.lo.y) / (bounds.hi.y - bounds.lo.y);
	int yIndex = REAL_TO_INT_FLOOR(yRatio * (50 - 0.1f));

	x = pos->x + radius;
	y = pos->y + radius;
	if (x < bounds.lo.x) x = bounds.lo.x;
	if (y < bounds.lo.y) y = bounds.lo.y;
	if (x > bounds.hi.x) x = bounds.hi.x;
	if (y > bounds.hi.y) y = bounds.hi.y;
	Real xMaxRatio = (x - bounds.lo.x) / (bounds.hi.x - bounds.lo.x);
	int xMax = REAL_TO_INT_CEIL(xMaxRatio * (50 - 0.1f));
	Real yMaxRatio = (y - bounds.lo.y) / (bounds.hi.y - bounds.lo.y);
	int yMax = REAL_TO_INT_CEIL(yMaxRatio * (50 - 0.1f));

	for (int i = xIndex; i < xMax; ++i) {
		for (int j = yIndex; j < yMax; ++j) {
			int index = m_areaPartition[i + 50*j];
			while (index != -1) {
				if (index < 0 || index >= count)
					break;
				Rva001A4A00Record *record = &m_records[index];
				if (m_records[index].m_bfmeTagEZ && (!skip || !record->m_skip18)) {
					if (filter == 1) {
						if (record->m_flag2c) goto checkRecord;
						goto nextRecord;
					}
					if (filter == 2 && !record->m_flag2d) goto nextRecord;
				checkRecord:
					Coord3D delta;
					delta.x = record->m_bfmePosEZ.x;
					delta.y = record->m_bfmePosEZ.y;
					delta.z = record->m_bfmePosEZ.z;
					delta.sub(pos);
					if (radius*radius >
						delta.x*delta.x + delta.y*delta.y + delta.z*delta.z)
						host->bfmeConsiderEZ((BfmeNodeEZ *)record, (const BfmeVec2EZ *)pos);
				}
			nextRecord:
				index = record->m_next2e;
			}
		}
	}
}
