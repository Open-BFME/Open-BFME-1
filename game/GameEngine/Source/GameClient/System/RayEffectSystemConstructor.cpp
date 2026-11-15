class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	char m_name[ 4 ];
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

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

private:
	RayEffectData m_effectData[ 128 ];
};

RayEffectSystem::RayEffectSystem( void )
{
	// retail inlines the init() loop here; init() itself is owned by RayEffect.cpp
	for ( int i = 0; i < 128; ++i )
	{
		m_effectData[ i ].draw = 0;
		{ Coord3D *const position = &m_effectData[ i ].startLoc; position->x = 0.0f; position->y = 0.0f; position->z = 0.0f; }
		{ Coord3D *const position = &m_effectData[ i ].endLoc; position->x = 0.0f; position->y = 0.0f; position->z = 0.0f; }
	}
}
