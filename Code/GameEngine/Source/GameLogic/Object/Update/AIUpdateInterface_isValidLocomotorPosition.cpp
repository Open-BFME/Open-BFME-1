// cl: /DNDEBUG /MD /EHsc
// readable body of ?isValidLocomotorPosition@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

typedef bool Bool;
typedef unsigned int LocomotorSurfaceTypeMask;

struct Coord3D;

enum PathfindLayerEnum {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	int getLayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool validMovementPosition(const Coord3D *pos, PathfindLayerEnum layer,
		LocomotorSurfaceTypeMask validSurfaces, Object *obj);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder() const
	{
		return m_pathfinder;
	}

private:
	unsigned char m_unmodelled_000[ 0x0C ];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	virtual ~AIUpdateInterface();
	Bool isValidLocomotorPosition(const Coord3D *pos) const;
	Object *getObject() const
	{
		return m_object;
	}
	LocomotorSurfaceTypeMask getValidLocomotorSurfaces() const
	{
		return m_validLocomotorSurfaces;
	}

private:
	unsigned char m_unmodelled_004[ 4 ];
	Object *m_object;
	unsigned char m_unmodelled_00C[ 0x1B8 - 0x0C ];
	LocomotorSurfaceTypeMask m_validLocomotorSurfaces;
};

Bool AIUpdateInterface::isValidLocomotorPosition(const Coord3D *pos) const
{
	return TheAI->pathfinder()->validMovementPosition(
		pos,
		static_cast<PathfindLayerEnum>( getObject()->getLayer() ),
		getValidLocomotorSurfaces(),
		getObject());
}
