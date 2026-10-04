// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern void j_00018f43();

class Rva005CCA10Particle
{
public:
	virtual void release( int flags );

	unsigned char m_unreconstructed_004[ 0x38 ];
	Rva005CCA10Particle *m_systemNext;
};

class Rva005CCA10ParticleSystem
{
public:
	bool update( void );
};

bool Rva005CCA10ParticleSystem::update( void )
{
	Rva005CCA10Particle *particle = *(Rva005CCA10Particle **)( (unsigned char *)this + 0xa0 );
	typedef bool (Rva005CCA10Particle::*Fn)( void );
	union { void (*fn)(); Fn call; } u = { j_00018f43 };
	if ( particle != 0 ) {
		do {
			Rva005CCA10Particle *next = particle->m_systemNext;
			if ( !( particle->*u.call )() ) {
				particle->release( 1 );
			}
			particle = next;
		} while ( particle != 0 );
	}

	if ( *(bool *)( (unsigned char *)this + 0x1a8 ) &&
		*(Rva005CCA10Particle **)( (unsigned char *)this + 0xa0 ) == 0 ) {
		return false;
	}
	if ( !*(bool *)( (unsigned char *)this + 0x1a6 ) ) {
		unsigned int lifetime = *(unsigned int *)( (unsigned char *)this + 0x12c );
		if ( lifetime != 0 ) {
			*(unsigned int *)( (unsigned char *)this + 0x12c ) = lifetime - 1;
		}
		if ( *(unsigned int *)( (unsigned char *)this + 0xa8 ) == 0 &&
			*(unsigned int *)( (unsigned char *)this + 0x12c ) == 0 ) {
			return false;
		}
	}
	return true;
}
