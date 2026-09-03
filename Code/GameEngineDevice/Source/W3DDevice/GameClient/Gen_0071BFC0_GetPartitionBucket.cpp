// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// readable body of ?getPartitionBucket@W3DTreeBuffer@@IBEHABUCoord3D@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBuffer.cpp
// BFME's W3DTreeBuffer partition grid is 50 by 50 (the ZH source uses 100).

#include "Lib/BaseType.h"

extern "C" __declspec(dllimport) double __cdecl floor(double);

#undef REAL_TO_INT_FLOOR
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTreeBuffer.h
class W3DTreeBuffer
{
protected:

	Int getPartitionBucket(const Coord3D &pos) const;

private:

	char m_pad00[0x1440];
	Region2D m_bounds;
};

Int W3DTreeBuffer::getPartitionBucket(const Coord3D &pos) const
{
	Real x = pos.x;
	Real y = pos.y;
	if (x<m_bounds.lo.x) x = m_bounds.lo.x;
	if (y<m_bounds.lo.y) y = m_bounds.lo.y;
	if (x>m_bounds.hi.x) x = m_bounds.hi.x;
	if (y>m_bounds.hi.y) y = m_bounds.hi.y;
	Real xRatio = (x/(m_bounds.hi.x-m_bounds.lo.x)) * (50-0.1f);
	Int xIndex = REAL_TO_INT_FLOOR(xRatio);
	Real yRatio = (y/(m_bounds.hi.y-m_bounds.lo.y)) * (50-0.1f);
	Int yIndex = REAL_TO_INT_FLOOR(yRatio);
	return yIndex*50 + xIndex;
}
