// cl: /DNDEBUG /MD
// readable body of ?getRadiusAndCenter@Pathfinder@@IAEXPBVObject@@AAHAA_N@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
//
// Retail 0x003DEE30: Pathfinder::getRadiusAndCenter.
// The BFME fork keeps the Zero Hour radius calculation but selects the
// permitted radius from the object's template flags and stores the output
// through the two reference arguments.

typedef int Int;
typedef float Real;
typedef bool Bool;

extern "C" __declspec(dllimport) double __cdecl floor( double );

__forceinline long fast_float2long_round( float value )
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))

extern const Real g_pathfindCellSize;
extern const Real g_pathfindDoubleCellSize;
extern const Real g_pathfindLevelLimit;
extern const Real g_pathfindCellCenterBias;

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride( void );

	BfmeOverridable *getFinalOverride( void )
	{
		if (m_override == 0) return this;
		return m_override->friend_getFinalOverride();
	}

	Int m_unknown00;
	BfmeOverridable *m_override;
	unsigned char m_pad08[0xc8 - 0x08];
	Int m_flagsC8;
	unsigned char m_padCC[0xd4 - 0xcc];
	Int m_flagsD4;
	unsigned char m_padD8[0x408 - 0xd8];
	Real m_level;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Int m_unknown00;
	BfmeOverridable *m_template;
	unsigned char m_pad08[0xbc - 0x08];
	Real m_boundingCircleRadius;

	BfmeOverridable *getTemplate( void ) const { return m_template; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
protected:
	void getRadiusAndCenter( const Object *obj, Int &radius, Bool &center );
};

void Pathfinder::getRadiusAndCenter( const Object *obj, Int &radius, Bool &center )
{
	Real diameter;
	Int maxRadius = 2;
	BfmeOverridable *t1 = obj->getTemplate();
	if ((t1 == 0 ? t1 : t1->getFinalOverride())->m_flagsC8 & 0x400) {
		maxRadius = 4;
	} else {
		BfmeOverridable *t2 = obj->getTemplate();
		if ((t2 == 0 ? t2 : t2->getFinalOverride())->m_flagsD4 & 0x1000) {
			maxRadius = 4;
		}
	}

	diameter = obj->m_boundingCircleRadius * 2.0f;
	if (diameter > g_pathfindCellSize && diameter < g_pathfindDoubleCellSize) {
		diameter = 20.0f;
	}

	if ((obj->getTemplate() == 0 ? obj->getTemplate() :
		obj->getTemplate()->getFinalOverride())->m_level > g_pathfindLevelLimit) {
		diameter = (obj->getTemplate() == 0 ? obj->getTemplate() :
		obj->getTemplate()->getFinalOverride())->m_level;
	}

	radius = REAL_TO_INT_FLOOR( diameter / 10.0f + g_pathfindCellCenterBias );
	center = false;
	if (radius == 0) radius++;
	if (radius & 1) {
		center = true;
	}
	radius /= 2;
	if (radius > maxRadius) {
		radius = maxRadius;
		center = true;
	}
}
