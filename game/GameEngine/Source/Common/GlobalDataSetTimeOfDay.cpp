// GlobalData::setTimeOfDay, retail 0x00082AA0 (298 bytes).
//
// Identity: the Zero Hour twin, GeneralsMD Common/GlobalData.cpp
// `Bool GlobalData::setTimeOfDay( TimeOfDay tod )`: the same
// TIME_OF_DAY_FIRST..TIME_OF_DAY_COUNT guard, the store to m_timeOfDay
// (GlobalData+0x218, field_names), and the MAX_GLOBAL_LIGHTS (3) copy of
// m_terrainLighting[tod][i] into the per-light ambient/diffuse/lightPos
// arrays. The GlobalData constructor (0x00084510) and W3DTerrainLogic::loadMap
// reach it through ILT 0x0000BA64. Evidence:
// targets/game/reverse/identity_evidence/00082aa0-globaldata-settimeofday.md
//
// GlobalData.h is not in this tree; the class is spelled locally around the
// members the retail body touches, at the offsets the matched constructor's
// view (GlobalDataConstructor.cpp) records. BFME's TimeOfDay has six names
// (NONE MORNING AFTERNOON EVENING NIGHT INTERPOLATE, name table 0x012A9FE0),
// so TIME_OF_DAY_COUNT is 6 and m_terrainLighting is [6][3].

typedef float Real;
typedef int Int;
typedef bool Bool;
#define TRUE 1
#define FALSE 0

enum TimeOfDay
{
	TIME_OF_DAY_INVALID = 0,
	TIME_OF_DAY_FIRST = 1,
	TIME_OF_DAY_MORNING = TIME_OF_DAY_FIRST,
	TIME_OF_DAY_AFTERNOON,
	TIME_OF_DAY_EVENING,
	TIME_OF_DAY_NIGHT,
	TIME_OF_DAY_INTERPOLATE,

	TIME_OF_DAY_COUNT					// keep this last
};

enum { MAX_GLOBAL_LIGHTS = 3 };

struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	Bool setTimeOfDay( TimeOfDay tod );

	struct TerrainLighting
	{
		RGBColor ambient;
		RGBColor diffuse;
		Coord3D lightPos;
	};

	char m_unreconstructed_0000[0x218];
	TimeOfDay m_timeOfDay;									///< +0x218
	char m_unreconstructed_021c[0x224 - 0x21c];
	TerrainLighting m_terrainLighting[TIME_OF_DAY_COUNT][MAX_GLOBAL_LIGHTS];	///< +0x224
	char m_unreconstructed_04ac[0x9bc - 0x4ac];
	RGBColor m_terrainAmbient[MAX_GLOBAL_LIGHTS];			///< +0x9bc
	RGBColor m_terrainDiffuse[MAX_GLOBAL_LIGHTS];			///< +0x9e0
	Coord3D m_terrainLightPos[MAX_GLOBAL_LIGHTS];			///< +0xa04
};

// ?setTimeOfDay@GlobalData@@QAE_NW4TimeOfDay@@@Z
Bool GlobalData::setTimeOfDay( TimeOfDay tod )
{
	if( tod >= TIME_OF_DAY_COUNT || tod < TIME_OF_DAY_FIRST )
	{
		return FALSE;
	}

	m_timeOfDay = tod;
	for (Int i=0; i<MAX_GLOBAL_LIGHTS; i++)
	{	m_terrainAmbient[i] = m_terrainLighting[ tod ][i].ambient;
		m_terrainDiffuse[i] = m_terrainLighting[ tod ][i].diffuse;
		m_terrainLightPos[i] = m_terrainLighting[ tod ][i].lightPos;
	}

	return TRUE;

}
