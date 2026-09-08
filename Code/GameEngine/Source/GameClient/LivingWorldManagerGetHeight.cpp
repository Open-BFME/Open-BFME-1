// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

#include "lineseg.h"
#include "coltest.h"
#include "rendobj.h"

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class BfmeLivingWorldManager
{
public:
	Real rva006fe600( Coord3D point );

private:
	char m_unknown000[ 0x84 ];
	RenderObjClass *m_worldRenderObject;
};

extern const Real BfmeZeroRange;

Real BfmeLivingWorldManager::rva006fe600( Coord3D point )
{
	if( m_worldRenderObject )
	{
		LineSegClass line( Vector3( point.x, point.y, 1000.0f ),
									Vector3( point.x, point.y, -1000.0f ) );
		CastResultStruct result;
		result.ComputeContactPoint = true;
		RayCollisionTestClass ray( line, &result, 1, false, false );

		if( m_worldRenderObject->Cast_Ray( ray ) )
			return ray.Result->ContactPoint.Z;
	}

	return BfmeZeroRange;
}
