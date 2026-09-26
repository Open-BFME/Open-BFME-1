class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	char m_name[ 4 ];
};

struct Coord3D
{
	float x;
	float y;
	float z;

	void zero( void )
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

struct RayEffectData
{
	RayEffectData( void ) {}
	~RayEffectData( void ) {}

	const void *draw;
	Coord3D startLoc;
	Coord3D endLoc;
};

class RayEffectSystem : public SubsystemInterface
{
public:
	RayEffectSystem( void );
	virtual ~RayEffectSystem( void );
	virtual void init( void );

private:
	RayEffectData m_effectData[ 128 ];
};

void RayEffectSystem::init( void )
{
	for ( int i = 0; i < 128; ++i )
	{
		m_effectData[ i ].draw = 0;
		m_effectData[ i ].startLoc.zero();
		m_effectData[ i ].endLoc.zero();
	}
}

RayEffectSystem::RayEffectSystem( void )
{
	init();
}
