// ?updateBodyParticleSystems@ActiveBody@@UAEXXZ
// partial score=0.91 date=2026-09-12
// Improves the prior 0.90/136-diff bank (t=19min model=gpt-5.6-luna/max) with one
// additional confirmed fix; the GlobalData particle-field overlay offset (0xab8,
// i.e. field group starts at 0xab8/0xac4/0xad0/0xadc/0xae8/0xf4/0x100 relative to
// TheWritableGlobalData) is RE-VERIFIED correct against six independent retail
// relocation immediates (0xabc/0xac8/0xad4/0xae0/0xaec/0xaf8 for the *System field
// of each of the six fire/smoke groups) -- rule this out as a further lever.
//
// NEW: retail's compiled bit for OBJECT_STATUS_AFLAME is bit 10 (getStatusBits()
// dword & 0x400, seen as `test ah,4`) at BOTH call sites in this body, not bit 11
// as the vendored Zero Hour ObjectStatusTypes enum position implies (AFLAME is the
// 12th entry, 0-based index 11, which BitFlags::test() would read as bit 11/0x800).
// BFME's real enum has one fewer entry before AFLAME than this vendored ZH copy.
// Bypassing testStatus(OBJECT_STATUS_AFLAME) with a raw offset+mask read of the
// confirmed retail bit (see BFME_OBJECT_IS_AFLAME below) fixed both call sites and
// moved the first byte divergence from +0x63 to +0x22a (554) and cut the non-reloc
// diff from 136 to 124 of 828 bytes. Do not "fix" this by editing the vendored
// reference/ ObjectStatusTypes.h; it must stay pristine, and other status values in
// the same enum may or may not carry the same one-position drift -- unverified.
//
// REMAINING WALL (not a register/scheduling mirror): starting at +0x22a, retail
// dispatches deleteAllParticleSystems() and each of the six createParticleSystems()
// calls THROUGH A VTABLE at [this-0x10] (`add esi,-0x10` once, then `mov eax,[esi];
// call [eax+0x44]` for delete, `call [edx+0x40]` per create), i.e. these methods are
// virtual through a base interface at a -0x10 this-adjustment in retail, not the
// plain non-virtual ActiveBody member calls this source (and the vendored ZH
// ActiveBody.h, which declares both non-virtual) compiles to. Recovering ActiveBody's
// real multiple-inheritance layout and which base interface owns vtable slots 0x40/
// 0x44 is the next step; do not attempt further register-order or local-declaration
// variations on the tail, they cannot fix a direct-vs-virtual call shape.
// t=17min model=claude-sonnet-5
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

// BFME's compiled ObjectStatusTypes bit for AFLAME sits one position earlier than the
// vendored Zero Hour enum; read the raw retail-confirmed status word instead.
#define BFME_OBJECT_IS_AFLAME( obj ) \
	((*(const UnsignedInt *)((const unsigned char *)(obj) + 0x90) & 0x400u) != 0)

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
	if( BFME_OBJECT_IS_AFLAME( getObject() ) )
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
	if( BFME_OBJECT_IS_AFLAME( getObject() ) )
		createParticleSystems( BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoAflameParticlePrefix,
															 aflameTemplate, BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoAflameParticleMax * countModifier );

}  // end updatebodyParticleSystems
