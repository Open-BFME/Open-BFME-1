
typedef float Real;
typedef int Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class AIUpdateInterface;
class TerrainLogic;
class GameLogic;

class Thing
{
public:
	Real bfmeRelativeAngleTo( const Coord3D *point ) const;
	Real getOrientation() const
	{
		return *reinterpret_cast<const Real *>(reinterpret_cast<const char *>(this) + 0x44);
	}
	void setPosition( const Coord3D *position );
};

class Object : public Thing
{
public:
	UnsignedInt getObjectStatus() const
	{
		return *reinterpret_cast<const UnsignedInt *>(reinterpret_cast<const char *>(this) + 0x94);
	}

	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x38);
	}

	AIUpdateInterface *getAI() const
	{
		return *reinterpret_cast<AIUpdateInterface *const *>(reinterpret_cast<const char *>(this) + 0x204);
	}

	void bfmeRecordTransform( UnsignedInt flags );
	Int getLayer() const;
};

enum CommandSourceType
{
	BFME_COMMAND_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiMoveToPosition( const Coord3D *position, CommandSourceType commandSource );
};

class AIUpdateInterface
{
public:
	void ignoreObstacle( Object *object );
};

class BfmeOpenScatterTerrainLogic
{
public:
	virtual void slot0( void ) = 0;
	virtual void slot1( void ) = 0;
	virtual void slot2( void ) = 0;
	virtual void slot3( void ) = 0;
	virtual void slot4( void ) = 0;
	virtual void slot5( void ) = 0;
	virtual void slot6( void ) = 0;
	virtual Real getLayerHeight( Real x, Real y, Int layer, Coord3D *normal, Bool clip ) = 0;
};

extern Real GetGameLogicRandomValueReal( Real low, Real high, char *file, int line );
extern Real Cos( Real angle );
extern Real Sin( Real angle );
extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;

class OpenContain
{
protected:
	void scatterToNearbyPosition( Object *rider );
};

void OpenContain::scatterToNearbyPosition( Object *rider )
{
	Object *theContainer = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) + 0x08);
	register Object *theRider = rider;
	Real angle;

#line 906 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\OpenContain.cpp"
	angle = GetGameLogicRandomValueReal( 0.0f, 2.0f * 3.14159265358979323846f,
		__FILE__, __LINE__ );

	if( (theRider->getObjectStatus() & 0x10000000) == 0 )
	{
		angle = theContainer->getOrientation() + theContainer->bfmeRelativeAngleTo( theRider->getPosition() );
	}

	Real minRadius = *reinterpret_cast<const Real *>(reinterpret_cast<const char *>(theContainer) + 0xBC);
	Real maxRadius = minRadius + minRadius / 2.0f;
	const Coord3D *containerPosition = theContainer->getPosition();

#line 921 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\OpenContain.cpp"
	Real dist = GetGameLogicRandomValueReal( minRadius, maxRadius, __FILE__, __LINE__ );

	Coord3D pos;
	pos.x = dist * Cos( angle ) + containerPosition->x;
	pos.y = dist * Sin( angle ) + containerPosition->y;
	pos.z = reinterpret_cast<BfmeOpenScatterTerrainLogic *>(TheTerrainLogic)->getLayerHeight(
		pos.x, pos.y, theContainer->getLayer(), 0, 1 );

	AIUpdateInterface *ai = theRider->getAI();
	if( ai )
	{
		if( (theRider->getObjectStatus() & 0x10000000) != 0 )
		{
			theRider->setPosition( theContainer->getPosition() );
			theRider->bfmeRecordTransform(
				*reinterpret_cast<const UnsignedInt *>(reinterpret_cast<const char *>(TheGameLogic) + 0x3C) );
			theRider->setPosition( theContainer->getPosition() );
		}

		ai->ignoreObstacle( theContainer );
		reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(ai) + 0x20)->aiMoveToPosition(
			&pos, BFME_COMMAND_FROM_AI );
	}
	else
	{
		theRider->setPosition( &pos );
	}
}
