// cl: /DNDEBUG /MD /EHsc
// readable body of ??0PhysicsBehaviorModuleData@@QAE@XZ: game/GameEngine/Source/GameLogic/Object/Update/PhysicsUpdate.cpp

// PhysicsBehaviorModuleData default constructor (0x0029A090, 126 B). The
// factory 0x0011AA70 allocates 0x5C bytes and calls this; it installs the
// dedicated vtable 0x00CC0910. BFME's layout differs from the Zero Hour header
// PhysicsUpdate.cpp compiles against, so this TU keeps an offset-named view.
//
// The defaults are assigned in field order except the three integers at
// +0x18..+0x20, which come last. That order is what makes MSVC keep 1.3 and
// then 0 in ECX, 0.66 in EDX and 5 in ECX again while 0.33 stays immediate:
// each constant register lives from its first to its last store.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PhysicsUpdate.h
class PhysicsBehaviorModuleData
{
public:
	PhysicsBehaviorModuleData();

public:
	virtual ~PhysicsBehaviorModuleData();

private:
	unsigned int m_04;
	float m_firstHeight;
	float m_secondHeight;
	float m_firstPercentIndent;
	float m_secondPercentIndent;
	int m_shockStunnedTimeLow;
	int m_shockStunnedTimeHigh;
	int m_shockStandingTime;
	int m_bounceCount;
	float m_28;
	float m_2C;
	float m_30;
	float m_34;
	float m_38;
	float m_curveFlattenMinDist;
	bool m_tumbleRandomly;
	bool m_orientToFlightPath;
	bool m_ignoreTerrainHeight;
	float m_firstPercentHeight;
	float m_secondPercentHeight;
	float m_gravityMult;
	unsigned int m_groundHitFX;
	unsigned int m_groundBounceFX;
	bool m_allowBouncing;
	bool m_killWhenRestingOnGround;
};

PhysicsBehaviorModuleData::PhysicsBehaviorModuleData()
{
	m_firstHeight = 1.3f;
	m_secondHeight = 1.3f;
	m_firstPercentIndent = 0.33f;
	m_secondPercentIndent = 0.66f;
	m_bounceCount = 2;
	m_28 = 5.0f;
	m_2C = 1.3f;
	m_30 = 1.3f;
	m_34 = 0.33f;
	m_38 = 0.66f;
	m_curveFlattenMinDist = 0.0f;
	m_tumbleRandomly = false;
	m_orientToFlightPath = false;
	m_ignoreTerrainHeight = false;
	m_firstPercentHeight = 0.33f;
	m_secondPercentHeight = 0.66f;
	m_gravityMult = 1.0f;
	m_groundHitFX = 0;
	m_groundBounceFX = 0;
	m_allowBouncing = false;
	m_killWhenRestingOnGround = false;
	m_shockStunnedTimeLow = 5;
	m_shockStunnedTimeHigh = 10;
	m_shockStandingTime = 5;
}
