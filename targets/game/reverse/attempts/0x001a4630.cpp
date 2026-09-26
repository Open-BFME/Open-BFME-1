// ?queryPointImplAt001A4630@TerrainLogic@@QAEXPBUCoord3D@@MPAURva001A62D0TerrainQueryResult@@_N2@Z
// partial score=0.99 date=2026-09-26
// cl: /Igame/GameEngine/Include /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/GameEngine/Source/Common/System /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

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

struct Rva001A31D0Point
{
	Coord3D m_position;
	Int m_tag;
};

class Rva001A31D0Candidate
{
public:
	void consider(Rva001A31D0Point *candidate, Rva001A31D0Point *query);
};

struct Rva001A62D0TerrainQueryResult
{
	Coord3D m_position;
	Int m_word0C;
	Real m_bestDistanceSquared;
	Coord3D *m_result;
};

class TerrainLogic
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
		Bool secondConstraint);

private:
	char m_unreconstructed_004[0x558];
	Rva001A4630Record *m_recordsBegin;
	Rva001A4630Record *m_recordsEnd;
	Int m_unreconstructed_564;
	Short m_partition[100 * 100];
};

// ?queryPointImplAt001A4630@TerrainLogic@@QAEXPBUCoord3D@@MPAURva001A62D0TerrainQueryResult@@_N2@Z
__declspec(noinline) void TerrainLogic::queryPointImplAt001A4630(
	const Coord3D *position, Real radius,
	Rva001A62D0TerrainQueryResult *result, Bool firstConstraint,
	Bool secondConstraint)
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
	Int xIndex = REAL_TO_INT_FLOOR(((x - bounds.lo.x) / (bounds.hi.x - bounds.lo.x)) * (100 - 0.1f));
	Int yIndex = REAL_TO_INT_FLOOR(((y - bounds.lo.y) / (bounds.hi.y - bounds.lo.y)) * (100 - 0.1f));

	x = position->x + radius;
	y = position->y + radius;
	if (x < bounds.lo.x) x = bounds.lo.x;
	if (y < bounds.lo.y) y = bounds.lo.y;
	if (x > bounds.hi.x) x = bounds.hi.x;
	if (y > bounds.hi.y) y = bounds.hi.y;
	Int xMax = REAL_TO_INT_CEIL(((x - bounds.lo.x) / (bounds.hi.x - bounds.lo.x)) * (100 - 0.1f));
	Int yMax = REAL_TO_INT_CEIL(((y - bounds.lo.y) / (bounds.hi.y - bounds.lo.y)) * (100 - 0.1f));

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
				Int occupied = record.m_occupied;
				if (occupied != 0)
				{
					Int secondConstraintValue =
						*reinterpret_cast<const Int *>(&secondConstraint);
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
					delta.set(record.m_position.x, record.m_position.y,
						record.m_position.z);
					delta.sub(position);
					if (radius * radius > delta.lengthSqr())
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
