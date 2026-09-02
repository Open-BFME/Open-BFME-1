// cl: /DNDEBUG /MD

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct HordeContainTransform
{
	unsigned char unused_00[0x0C];
	float x;
	unsigned char unused_10[0x0C];
	float y;
	unsigned char unused_20[0x0C];
	float z;

	__forceinline HordeContainTransform( const HordeContainTransform &other )
		: x( other.x ), y( other.y ), z( other.z ) {}

	__forceinline void getTranslation( Coord3D *position ) const
	{
		position->x = x;
		position->y = y;
		position->z = z;
	}
};

struct HordeContainObject
{
	unsigned char unused_00[8];
	HordeContainTransform transform;
};

class Object
{
public:
	void setPosition( const Coord3D *position );
};

class Rva00248F40HordeContain
{
public:
	void setExitPosition( Object *object );
private:
	unsigned char unused_00[8];
	HordeContainObject *m_object;
};

class Rva0024B9B0HordeContain
{
public:
	void setExitPosition( Object *object );
private:
	unsigned char unused_00[8];
	HordeContainObject *m_object;
};

void Rva00248F40HordeContain::setExitPosition( Object *object )
{
	Coord3D position;
	HordeContainTransform transform( m_object->transform );
	transform.getTranslation( &position );
	object->setPosition( &position );
}

void Rva0024B9B0HordeContain::setExitPosition( Object *object )
{
	Coord3D position;
	HordeContainTransform transform( m_object->transform );
	transform.getTranslation( &position );
	object->setPosition( &position );
}
