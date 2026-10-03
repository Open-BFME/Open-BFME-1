// ?queryPointImplAt001A4630@Rva001A4630TerrainRecordQuery@@QAEXPBUCoord3D@@MPAURva001A62D0TerrainQueryResult@@_NH@Z
// cl: /Igame/GameEngine/Include /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/GameEngine/Source/Common/System /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Retail 0x001A4630: 777 bytes ending in ret 0x14. The matched 0x001A62D0
// wrapper calls this on TheTerrainLogic. This address-derived receiver view
// describes only the witnessed vptr and +0x55C record vector / +0x568 grid.
// The final argument is read as a full Int and compared with both 1 and 2;
// the older wrapper pin's Bool spelling is not used as a source type here.
// Callback: ILT 0x0004846E -> 0x001A31D0 Rva001A31D0Candidate::consider.
// Re-reading the indexed occupied member retains retail's address allocation.

#include "Lib/BaseType.h"

extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" __declspec(dllimport) double __cdecl ceil(double);

#undef REAL_TO_INT_FLOOR
#undef REAL_TO_INT_CEIL
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))
#define REAL_TO_INT_CEIL(x) (fast_float2long_round((Real)ceil((double)(x))))

struct Rva001A4630Record
{
	Coord3D m_position;
	Int m_occupied;
	char m_unreconstructed_010[8];
	Bool m_flag18;
	char m_unreconstructed_019[0x13];
	Bool m_flag2c;
	Bool m_flag2d;
	Short m_next;
};

struct Rva001A4630Region
{
	Coord3D lo;
	Coord3D hi;
};

struct Rva001A31D0Point;

class Rva001A31D0Candidate
{
public:
	void consider(Rva001A31D0Point *candidate, Rva001A31D0Point *query);
};

struct Rva001A62D0TerrainQueryResult;

class Rva001A4630TerrainRecordQuery
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void getMaximumPathfindExtent(Rva001A4630Region *extent) const;
	void queryPointImplAt001A4630(const Coord3D *position, Real radius,
		Rva001A62D0TerrainQueryResult *result, Bool firstConstraint,
		Int secondConstraint);

private:
	char m_unreconstructed_004[0x558];
	Rva001A4630Record *m_recordsBegin;
	Rva001A4630Record *m_recordsEnd;
	Int m_unreconstructed_564;
	Short m_partition[100 * 100];
};

// ?queryPointImplAt001A4630@Rva001A4630TerrainRecordQuery@@QAEXPBUCoord3D@@MPAURva001A62D0TerrainQueryResult@@_NH@Z
__declspec(noinline) void Rva001A4630TerrainRecordQuery::queryPointImplAt001A4630(
	const Coord3D *position, Real radius,
	Rva001A62D0TerrainQueryResult *result, Bool firstConstraint,
	Int secondConstraint)
{
	Int numRecords = m_recordsEnd - m_recordsBegin;
	if (numRecords == 0)
		return;

	radius += 7.0f;
	Rva001A4630Region bounds;
	getMaximumPathfindExtent(&bounds);

	Real x = position->x - radius;
	Real y = position->y - radius;
	if (x < bounds.lo.x) x = bounds.lo.x;
	if (y < bounds.lo.y) y = bounds.lo.y;
	if (x > bounds.hi.x) x = bounds.hi.x;
	if (y > bounds.hi.y) y = bounds.hi.y;
	// Retail scales by 49.9, a 50-cell grid; Zero Hour's grid was 100 cells (99.9).
	Int xIndex = REAL_TO_INT_FLOOR(((x - bounds.lo.x) / (bounds.hi.x - bounds.lo.x)) * (50 - 0.1f));
	Int yIndex = REAL_TO_INT_FLOOR(((y - bounds.lo.y) / (bounds.hi.y - bounds.lo.y)) * (50 - 0.1f));

	x = position->x + radius;
	y = position->y + radius;
	if (x < bounds.lo.x) x = bounds.lo.x;
	if (y < bounds.lo.y) y = bounds.lo.y;
	if (x > bounds.hi.x) x = bounds.hi.x;
	if (y > bounds.hi.y) y = bounds.hi.y;
	Int xMax = REAL_TO_INT_CEIL(((x - bounds.lo.x) / (bounds.hi.x - bounds.lo.x)) * (50 - 0.1f));
	Int yMax = REAL_TO_INT_CEIL(((y - bounds.lo.y) / (bounds.hi.y - bounds.lo.y)) * (50 - 0.1f));

	for (Int i = xIndex; i < xMax; ++i)
	{
		for (Int j = yIndex; j < yMax; ++j)
		{
			Int recordIndex = m_partition[i + 50 * j];
			while (recordIndex != -1)
			{
				if (recordIndex < 0 || recordIndex >= numRecords)
					break;
				Rva001A4630Record &record = m_recordsBegin[recordIndex];
				Int occupied = m_recordsBegin[recordIndex].m_occupied;
				if (occupied != 0)
				{
					Int secondConstraintValue = secondConstraint;
					if (firstConstraint && record.m_flag18)
						goto next_record;
					if (secondConstraintValue == 1)
					{
						if (record.m_flag2c)
							goto candidate_record;
						goto next_record;
					}
					if (secondConstraintValue == 2)
					{
						if (!record.m_flag2d)
						goto next_record;
				}

			candidate_record:
				Coord3D delta;
					delta.x = record.m_position.x;
					delta.y = record.m_position.y;
					delta.z = record.m_position.z;
					delta.sub(position);
					if (radius * radius >
						delta.x * delta.x + delta.y * delta.y + delta.z * delta.z)
					{
						Rva001A31D0Candidate *best =
							reinterpret_cast<Rva001A31D0Candidate *>(result);
						best->consider(
							reinterpret_cast<Rva001A31D0Point *>(&record),
							reinterpret_cast<Rva001A31D0Point *>(
								const_cast<Coord3D *>(position)));
					}
				}

next_record:
				recordIndex = record.m_next;
			}
		}
	}
}
