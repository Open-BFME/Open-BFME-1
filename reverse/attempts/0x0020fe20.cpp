// ?updateBodyParticleSystems@ActiveBody@@UAEXXZ
// partial score=0.9 date=2026-09-10
// Complete real-C++ reconstruction; retained as a partial attempt because
// the BFME global layout is corrected but register/relocation layout remains.
struct BfmeActiveBodyParticleGlobalData
{
	unsigned char m_beforeParticleFields[0xab8];
	AsciiString m_autoFireParticleSmallPrefix;
	AsciiString m_autoFireParticleSmallSystem;
	Int m_autoFireParticleSmallMax;
	AsciiString m_autoFireParticleMediumPrefix;
	AsciiString m_autoFireParticleMediumSystem;
	Int m_autoFireParticleMediumMax;
	AsciiString m_autoFireParticleLargePrefix;
	AsciiString m_autoFireParticleLargeSystem;
	Int m_autoFireParticleLargeMax;
	AsciiString m_autoSmokeParticleSmallPrefix;
	AsciiString m_autoSmokeParticleSmallSystem;
	Int m_autoSmokeParticleSmallMax;
	AsciiString m_autoSmokeParticleMediumPrefix;
	AsciiString m_autoSmokeParticleMediumSystem;
	Int m_autoSmokeParticleMediumMax;
	AsciiString m_autoSmokeParticleLargePrefix;
	AsciiString m_autoSmokeParticleLargeSystem;
	Int m_autoSmokeParticleLargeMax;
	AsciiString m_autoAflameParticlePrefix;
	AsciiString m_autoAflameParticleSystem;
	Int m_autoAflameParticleMax;
};

#define BFME_ACTIVE_BODY_PARTICLE_GLOBAL \
	(*reinterpret_cast<const BfmeActiveBodyParticleGlobalData *>(TheWritableGlobalData))

void ActiveBody::updateBodyParticleSystems( void )
{
	static const ParticleSystemTemplate *fireSmallTemplate   = TheParticleSystemManager->findTemplate( BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleSmallSystem );
	static const ParticleSystemTemplate *fireMediumTemplate  = TheParticleSystemManager->findTemplate( BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleMediumSystem );
	static const ParticleSystemTemplate *fireLargeTemplate   = TheParticleSystemManager->findTemplate( BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleLargeSystem );
	static const ParticleSystemTemplate *smokeSmallTemplate  = TheParticleSystemManager->findTemplate( BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleSmallSystem );
	static const ParticleSystemTemplate *smokeMediumTemplate = TheParticleSystemManager->findTemplate( BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleMediumSystem );
	static const ParticleSystemTemplate *smokeLargeTemplate  = TheParticleSystemManager->findTemplate( BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleLargeSystem );
	static const ParticleSystemTemplate *aflameTemplate			 = TheParticleSystemManager->findTemplate( BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoAflameParticleSystem );
	Int countModifier;
	const ParticleSystemTemplate *fireSmall;
	const ParticleSystemTemplate *fireMedium;
	const ParticleSystemTemplate *fireLarge;
	const ParticleSystemTemplate *smokeSmall;
	const ParticleSystemTemplate *smokeMedium;
	const ParticleSystemTemplate *smokeLarge;

	//
	// when we're aflame, we use a slightly different set of particle systems that are
	// auto created that lends itself to more fire and bigger fire
	//
	if( getObject()->testStatus( OBJECT_STATUS_AFLAME ) )
	{

		fireSmall		= fireMediumTemplate;		// small fire becomes medium fire
		fireMedium	= fireLargeTemplate;		// medium fire becomes large fire
		fireLarge		= fireLargeTemplate;		// large fire stays large
		smokeSmall		= fireSmallTemplate;		// small smoke becomes small fire
		smokeMedium = fireSmallTemplate;		// medium smoke becomes small fire
		smokeLarge	= fireSmallTemplate;		// large smoke becomes small fire

		// we get to make more of them all too
		countModifier = 2;

	}  // end if
	else
	{

		// use regular templates
		fireSmall	= fireSmallTemplate;
		fireMedium	= fireMediumTemplate;
		fireLarge	= fireLargeTemplate;
		smokeSmall	= smokeSmallTemplate;
		smokeMedium = smokeMediumTemplate;
		smokeLarge	= smokeLargeTemplate;

		// we make just the normal amount of these
		countModifier = 1;

	}  // end else

	//
	// remove any particle systems we have currently in the list in favor of any new ones
	// that we're going to autopopulate ourselves with
	//
	deleteAllParticleSystems();

	//
	// create particle systems for the new body state
	//

	// small fire bones
	createParticleSystems( BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleSmallPrefix, 
													 fireSmall, BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleSmallMax * countModifier );

	// medium fire bones
	createParticleSystems( BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleMediumPrefix, 
													 fireMedium, BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleMediumMax * countModifier );

	// large fire bones
	createParticleSystems( BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleLargePrefix, 
													 fireLarge, BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleLargeMax * countModifier );

	// small smoke bones
	createParticleSystems( BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleSmallPrefix, 
													 smokeSmall, BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleSmallMax * countModifier );

	// medium smoke bones
	createParticleSystems( BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleMediumPrefix, 
													 smokeMedium, BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleMediumMax * countModifier );

	// large smoke bones
	createParticleSystems( BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleLargePrefix, 
													 smokeLarge, BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleLargeMax * countModifier );

	// actively on fire
	if( getObject()->testStatus( OBJECT_STATUS_AFLAME ) )
		createParticleSystems( BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoAflameParticlePrefix, 
															 aflameTemplate, BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoAflameParticleMax * countModifier );

}  // end updatebodyParticleSystems
