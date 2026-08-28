// readable body of ?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z: Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp
// readable body of ?parseParticleSystem@TransitionDamageFXModuleData@@: Code/GameEngine/Source/GameLogic/Object/Damage/TransitionDamageFX.cpp
class INI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BoneFXUpdate.h
class BoneFXUpdateModuleData
{
public:
	static void parseParticleSystem(INI *, void *, void *, const void *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransitionDamageFX.h
class TransitionDamageFXModuleData
{
public:
	static void parseParticleSystem(INI *, void *, void *, const void *);
};

class BoneFXParseParticleSystemShim
{
public:
	static void parseParticleSystem(INI *, void *, void *, const void *);
};

class TransitionDamageFXParseParticleSystemShim
{
public:
	static void parseParticleSystem(INI *, void *, void *, const void *);
};

void BoneFXUpdateModuleData::parseParticleSystem(INI *a0, void *a1, void *a2, const void *a3)
{
	BoneFXParseParticleSystemShim::parseParticleSystem(a0, a1, a2, a3);
}

void TransitionDamageFXModuleData::parseParticleSystem(INI *a0, void *a1, void *a2, const void *a3)
{
	TransitionDamageFXParseParticleSystemShim::parseParticleSystem(a0, a1, a2, a3);
}
