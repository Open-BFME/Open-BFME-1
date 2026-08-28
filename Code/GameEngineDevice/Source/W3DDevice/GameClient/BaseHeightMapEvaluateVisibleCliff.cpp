// cl: /DNDEBUG /MD /EHsc
// readable body of ?evaluateAsVisibleCliff@BaseHeightMapRenderObjClass@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp

#include <math.h>

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned short UnsignedShort;

#define MAP_XY_FACTOR (10.0f)
#define MAP_HEIGHT_SCALE (0.625f)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class WorldHeightMap
{
public:
	UnsignedShort getHeight( Int xIndex, Int yIndex ) const
	{
		Int ndx = xIndex + m_width * yIndex;
		if (ndx >= 0 && ndx < m_dataSize && m_data != 0)
			return m_data[ndx];
		return 0;
	}

private:
	unsigned char m_unreconstructed_00[0x08];
	Int m_width;
	unsigned char m_unreconstructed_0c[0x14];
	Int m_dataSize;
	UnsignedShort *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h
class BaseHeightMapRenderObjClass
{
public:
	Bool evaluateAsVisibleCliff( Int xIndex, Int yIndex, Real valuesGreaterThanRad );

private:
	unsigned char m_unreconstructed[0x2ff4];
	WorldHeightMap *m_map;
};

Bool BaseHeightMapRenderObjClass::evaluateAsVisibleCliff( Int xIndex, Int yIndex, Real valuesGreaterThanRad )
{
	static const Real distance[4] =
	{
		0.0f,
		1.0f * MAP_XY_FACTOR,
		sqrt(2.0f) * MAP_XY_FACTOR,
		1.0f * MAP_XY_FACTOR,
	};

	UnsignedShort bytes[4] =
	{
		m_map->getHeight( xIndex + 0, yIndex + 0 ),
		m_map->getHeight( xIndex + 1, yIndex + 0 ),
		m_map->getHeight( xIndex + 1, yIndex + 1 ),
		m_map->getHeight( xIndex + 0, yIndex + 1 ),
	};

	Real heights[4] =
	{
		((Real) (bytes[0])) * MAP_HEIGHT_SCALE,
		((Real) (bytes[1])) * MAP_HEIGHT_SCALE,
		((Real) (bytes[2])) * MAP_HEIGHT_SCALE,
		((Real) (bytes[3])) * MAP_HEIGHT_SCALE,
	};

	Bool anyImpassable = false;
	for (Int i = 1; i < 4 && !anyImpassable; ++i)
	{
		if (fabs((heights[i] - heights[0]) / distance[i]) > valuesGreaterThanRad)
			anyImpassable = true;
	}

	return anyImpassable;
}
