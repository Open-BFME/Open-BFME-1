// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include/Common /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib

#include "FXParticleSystem/fx_particle_system.h"

class BfmeParticleSystemLink
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer( Xfer &xfer );
};

class Y3NotifyTail_005CBB30
{
public:
	void notifyAll( void *argument );
};

class BfmeSeedTarget;
void bfmeHandOver_0000240A( BfmeSeedTarget *target, void *item );
void BfmeParticleSystemXferHandle( Xfer &xfer, void *value );
void BfmeParticleSystemXferMatrix( Xfer &xfer, void *value );
void bfmeHandOver_0000C9B4( BfmeSeedTarget *target, void *item );
void bfmeHandOver_00001A50( BfmeSeedTarget *target, void *item );

class Particle
{
public:
	virtual void release( int flags );
};

class BfmeParticleEmissionHelper
{
public:
	Particle *createParticle( int particleNumber, int particleCount );
};

class ParticleSystem : public FXParticleSystem::ParticleSystemInfo
{
public:
	virtual void DoXfer( Xfer &xfer );
	virtual void slot04();
	virtual Particle *addParticle( Particle *source, int priority, bool forceCreate );
};

// ?DoXfer@ParticleSystem@@UAEXAAVXfer@@@Z
void ParticleSystem::DoXfer( Xfer &xfer )
{
	unsigned int particleCount;
	int priority;
	Particle *particle;

	FXParticleSystem::ParticleSystemInfo::DoXfer( xfer );
	if ( xfer.IsCRC() ) {
		return;
	}

	Xfer::Version version;
	version.data[ 0 ] = 1;
	version.data[ 1 ] = 2;
	xfer == version;

	BfmeParticleSystemLink *link = *(BfmeParticleSystemLink **)( (unsigned char *)this + 0x1b0 );
	if ( link != 0 ) {
		link->xfer( xfer );
	}

	((Y3NotifyTail_005CBB30 *)( (unsigned char *)this + 0x1b4 ))->notifyAll( (void *)&xfer );
	bfmeHandOver_0000240A( (BfmeSeedTarget *)&xfer, (unsigned char *)this + 0xac );
	BfmeParticleSystemXferHandle( xfer, (unsigned char *)this + 0xb4 );
	bfmeHandOver_0000C9B4( (BfmeSeedTarget *)&xfer, (unsigned char *)this + 0xb8 );

	xfer == *(bool *)( (unsigned char *)this + 0x1a4 );
	BfmeParticleSystemXferMatrix( xfer, (unsigned char *)this + 0xc0 );
	xfer == *(bool *)( (unsigned char *)this + 0x1a5 );
	BfmeParticleSystemXferMatrix( xfer, (unsigned char *)this + 0xf0 );
	xfer == *(unsigned int *)( (unsigned char *)this + 0x120 );
	xfer == *(unsigned int *)( (unsigned char *)this + 0x124 );
	xfer == *(unsigned int *)( (unsigned char *)this + 0x128 );
	xfer == *(unsigned int *)( (unsigned char *)this + 0x12c );
	xfer == *(unsigned int *)( (unsigned char *)this + 0x130 );
	xfer == *(bool *)( (unsigned char *)this + 0x1a6 );
	xfer == *(float *)( (unsigned char *)this + 0x184 );
	xfer == *(bool *)( (unsigned char *)this + 0x1a7 );

	if ( version.data[ 1 ] >= 2 ) {
		xfer == *(AsciiString *)( (unsigned char *)this + 0xbc );
		xfer == *(bool *)( (unsigned char *)this + 0x1ab );
		xfer == *(bool *)( (unsigned char *)this + 0x1ac );
	}
	xfer == *(Coord3DBase *)( (unsigned char *)this + 0x134 );
	xfer == *(float *)( (unsigned char *)this + 0x140 );
	xfer == *(float *)( (unsigned char *)this + 0x144 );
	xfer == *(float *)( (unsigned char *)this + 0x180 );
	xfer == *(float *)( (unsigned char *)this + 0x188 );
	xfer == *(bool *)( (unsigned char *)this + 0x198 );
	bfmeHandOver_00001A50( (BfmeSeedTarget *)&xfer, (unsigned char *)this + 0x18c );
	xfer == *(Coord3DBase *)( (unsigned char *)this + 0x148 );
	xfer == *(Coord3DBase *)( (unsigned char *)this + 0x154 );
	xfer == *(bool *)( (unsigned char *)this + 0x1a9 );
	bfmeHandOver_0000240A( (BfmeSeedTarget *)&xfer, (unsigned char *)this + 0x16c );
	bfmeHandOver_0000240A( (BfmeSeedTarget *)&xfer, (unsigned char *)this + 0x17c );

	particleCount = *(unsigned int *)( (unsigned char *)this + 0xa8 );
	xfer == particleCount;

	if ( xfer.IsStoring() ) {
		particle = *(Particle **)( (unsigned char *)this + 0xa0 );
		while ( particle != 0 ) {
			xfer == *(Snapshot *)particle;
			particle = *(Particle **)( (unsigned char *)particle + 0x3c );
		}
	} else {
		priority = *(int *)( (unsigned char *)this + 0x7c );
		particle = ((BfmeParticleEmissionHelper *)this)->createParticle( 0, 1 );
		for ( unsigned int i = 0; i < particleCount; ++i ) {
			Particle *copy = addParticle( particle, priority, true );
			xfer == *(Snapshot *)copy;
		}
		if ( particle != 0 ) {
			particle->release( 1 );
		}
	}
}
