// cl: /DNDEBUG /MD /EHsc
// readable body: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

template <class T>
inline const T &max( const T &left, const T &right )
{
	return left > right ? left : right;
}

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum KindOfType
{
	KINDOF_AIRCRAFT = 0x0C
};

class Thing
{
public:
	Bool bfmeIsKindOf( KindOfType type ) const;
	Bool isSignificantlyAboveTerrain() const;
};

class Object : public Thing
{
};

class Locomotor
{
public:
	Real getPreferredHeight() const { return m_preferredHeight; }

private:
	unsigned char m_unmodelled_00[ 0x44 ];
	Real m_preferredHeight;
};

class StateMachine
{
public:
	void bfmeSetGoalPosition( const Coord3D *position );
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void getExtent( Region3D *extent );
};

class GlobalData
{
public:
	unsigned char m_unmodelled_00[ 0x1BC ];
	Real m_partitionCellSize;
};

extern GlobalData *TheWritableGlobalData;
extern TerrainLogic *TheTerrainLogic;

class AIUpdateInterface
{
public:
	void setGoalPositionClipped( const Coord3D *position, CommandSourceType cmdSource );

private:
	unsigned char m_unmodelled_00[ 8 ];
	Object *m_object;
	unsigned char m_unmodelled_0C[ 0x30 - 0x0C ];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[ 0x1CC - 0x34 ];
	Locomotor *m_curLocomotor;
};

void AIUpdateInterface::setGoalPositionClipped( const Coord3D *position, CommandSourceType cmdSource )
{
	if( position )
	{
		Coord3D clipped = *position;
		if( cmdSource == CMD_FROM_PLAYER )
		{
			Real fudge = TheWritableGlobalData->m_partitionCellSize * 0.5f;
			Object *object = m_object;
			if( object->bfmeIsKindOf( KINDOF_AIRCRAFT ) &&
				object->isSignificantlyAboveTerrain() && m_curLocomotor )
			{
				fudge = max( fudge, m_curLocomotor->getPreferredHeight() );
			}

			Region3D mapRegion;
			TheTerrainLogic->getExtent( &mapRegion );
			if( clipped.x < mapRegion.lo.x + fudge )
				clipped.x = mapRegion.lo.x + fudge;
			if( clipped.x > mapRegion.hi.x - fudge )
				clipped.x = mapRegion.hi.x - fudge;
			if( clipped.y < mapRegion.lo.y + fudge )
				clipped.y = mapRegion.lo.y + fudge;
			if( clipped.y > mapRegion.hi.y - fudge )
				clipped.y = mapRegion.hi.y - fudge;
		}
		m_stateMachine->bfmeSetGoalPosition( &clipped );
	}
	else
	{
		m_stateMachine->bfmeSetGoalPosition( 0 );
	}
}
