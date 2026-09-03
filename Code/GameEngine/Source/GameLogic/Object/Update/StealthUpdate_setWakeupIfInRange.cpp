// Retail 0x002AC150: the StealthUpdate object-iteration callback.

typedef float Real;

extern "C" double sqrt( double value );

struct Coord3DBase
{
	Real x;
	Real y;
	Real z;
};

class Coord3D : public Coord3DBase
{
public:
	Coord3D( const Coord3D &that )
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}

	~Coord3D()
	{
	}

	void sub( const Coord3DBase *that )
	{
		x -= that->x;
		y -= that->y;
		z -= that->z;
	}

	Real length() const
	{
		return (Real)sqrt( x * x + y * y + z * z );
	}
};

class AIUpdateInterface
{
};


class Object
{
public:
	AIUpdateInterface *getAI() const
	{
		return *reinterpret_cast<AIUpdateInterface * const *>( reinterpret_cast<const char *>( this ) + 0x204 );
	}

	Real getVisionRange() const;

	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>( reinterpret_cast<const char *>( this ) + 0x38 );
	}
};

extern void j_00014b4b();
extern void j_0000da03();
typedef Real (__fastcall *VisionRangeCall)( const Object * );
typedef void (__fastcall *WakeUpCall)( AIUpdateInterface * );

// ?setWakeupIfInRange@@YAXPAVObject@@PAX@Z
int setWakeupIfInRange( Object *obj, void *userData )
{
	int result;
	Object *victim = reinterpret_cast<Object *>( userData );
	AIUpdateInterface *ai = obj->getAI();
	if ( !ai )
		goto done;

	{
	Real vision = ((VisionRangeCall)j_00014b4b)( obj );
	Coord3D srcpos = *obj->getPosition();
	Coord3D dstpos = *victim->getPosition();

	srcpos.sub( &dstpos );
	if ( srcpos.length() > vision )
		goto done;

	((WakeUpCall)j_0000da03)( ai );
	}

done:
	result = 1;
	return result;
}
