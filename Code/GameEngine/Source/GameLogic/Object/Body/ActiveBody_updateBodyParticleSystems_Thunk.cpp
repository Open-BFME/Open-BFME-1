// Lane 20 scratch: real-C++ reconstruction of ActiveBody::updateBodyParticleSystems.
// This TU models BFME's three-subobject ActiveBody ABI locally; root integrates only
// after the body and identity are independently verified.
// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

class AsciiString
{
public:
	unsigned int m_value;
};

class ParticleSystemTemplate {};

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
};

extern ParticleSystemManager *TheParticleSystemManager;
extern void *TheWritableGlobalData;

class Object
{
public:
	unsigned char m_opaque[0x90];
	UnsignedInt m_status;
};

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();
	virtual void behaviorModuleSlot01();
	virtual void behaviorModuleSlot02();
	virtual void behaviorModuleSlot03();
	virtual void behaviorModuleSlot04();
	virtual void behaviorModuleSlot05();
	virtual void behaviorModuleSlot06();
	virtual void behaviorModuleSlot07();
	virtual void behaviorModuleSlot08();
	virtual void behaviorModuleSlot09();
	virtual void behaviorModuleSlot10();
	virtual void behaviorModuleSlot11();
	virtual void behaviorModuleSlot12();
	virtual void behaviorModuleSlot13();
	virtual void behaviorModuleSlot14();
	virtual void behaviorModuleSlot15();

protected:
	unsigned char m_beforeObject[4];
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void updateBodyParticleSystems();
};

class Rva0020FE20ActiveBodyInterface : public BehaviorModule,
	public BehaviorModuleInterface,
	public BodyModuleInterface
{
public:
	virtual void updateBodyParticleSystems();

protected:
	virtual void createParticleSystems(const AsciiString &boneBaseName,
		const ParticleSystemTemplate *systemTemplate, Int maxSystems);
	virtual void deleteAllParticleSystems();

	Object *getObject() { return m_object; }
};

struct Rva0020FE20ParticleGlobalData
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
	(*reinterpret_cast<const Rva0020FE20ParticleGlobalData *>(TheWritableGlobalData))

#define BFME_OBJECT_IS_AFLAME(obj) \
	((*(const UnsignedInt *)((const unsigned char *)(obj) + 0x90) & 0x400u) != 0)

// ?updateBodyParticleSystems@ActiveBody@@UAEXXZ
void Rva0020FE20ActiveBodyInterface::updateBodyParticleSystems(void)
{
	static const ParticleSystemTemplate *fireSmallTemplate = TheParticleSystemManager->findTemplate(BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleSmallSystem);
	static const ParticleSystemTemplate *fireMediumTemplate = TheParticleSystemManager->findTemplate(BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleMediumSystem);
	static const ParticleSystemTemplate *fireLargeTemplate = TheParticleSystemManager->findTemplate(BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleLargeSystem);
	static const ParticleSystemTemplate *smokeSmallTemplate = TheParticleSystemManager->findTemplate(BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleSmallSystem);
	static const ParticleSystemTemplate *smokeMediumTemplate = TheParticleSystemManager->findTemplate(BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleMediumSystem);
	static const ParticleSystemTemplate *smokeLargeTemplate = TheParticleSystemManager->findTemplate(BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleLargeSystem);
	static const ParticleSystemTemplate *aflameTemplate = TheParticleSystemManager->findTemplate(BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoAflameParticleSystem);
	Int countModifier;
	const ParticleSystemTemplate *fireSmall;
	const ParticleSystemTemplate *fireMedium;
	const ParticleSystemTemplate *fireLarge;
	const ParticleSystemTemplate *smokeSmall;
	const ParticleSystemTemplate *smokeMedium;
	const ParticleSystemTemplate *smokeLarge;

	if (BFME_OBJECT_IS_AFLAME(getObject()))
	{
		fireSmall = fireMediumTemplate;
		fireMedium = fireLargeTemplate;
		fireLarge = fireLargeTemplate;
		smokeSmall = fireSmallTemplate;
		smokeMedium = fireSmallTemplate;
		smokeLarge = fireSmallTemplate;
		countModifier = 2;
	}
	else
	{
		fireSmall = fireSmallTemplate;
		fireMedium = fireMediumTemplate;
		fireLarge = fireLargeTemplate;
		smokeSmall = smokeSmallTemplate;
		smokeMedium = smokeMediumTemplate;
		smokeLarge = smokeLargeTemplate;
		countModifier = 1;
	}

	deleteAllParticleSystems();

	createParticleSystems(BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleSmallPrefix,
		fireSmall, BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleSmallMax * countModifier);
	createParticleSystems(BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleMediumPrefix,
		fireMedium, BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleMediumMax * countModifier);
	createParticleSystems(BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleLargePrefix,
		fireLarge, BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoFireParticleLargeMax * countModifier);
	createParticleSystems(BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleSmallPrefix,
		smokeSmall, BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleSmallMax * countModifier);
	createParticleSystems(BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleMediumPrefix,
		smokeMedium, BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleMediumMax * countModifier);
	createParticleSystems(BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleLargePrefix,
		smokeLarge, BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoSmokeParticleLargeMax * countModifier);

	if (BFME_OBJECT_IS_AFLAME(getObject()))
		createParticleSystems(BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoAflameParticlePrefix,
			aflameTemplate, BFME_ACTIVE_BODY_PARTICLE_GLOBAL.m_autoAflameParticleMax * countModifier);
}
