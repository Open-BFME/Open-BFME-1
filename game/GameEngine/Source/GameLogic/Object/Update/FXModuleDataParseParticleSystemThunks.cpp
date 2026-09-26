// readable body of ?parseParticleSystem@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z: game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp
// readable body of ?parseParticleSystem@TransitionDamageFXModuleData@@: game/GameEngine/Source/GameLogic/Object/Damage/TransitionDamageFX.cpp
class INI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BoneFXUpdate.h
class BoneFXUpdateModuleData
{
public:
	static void parseParticleSystem(INI *ini, void *instance, void *store, const void *userData);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransitionDamageFX.h
class TransitionDamageFXModuleData
{
public:
	static void parseParticleSystem(INI *ini, void *instance, void *store, const void *userData);
};

class BoneFXParseParticleSystemShim
{
public:
	static void parseParticleSystem(INI *ini, void *instance, void *store, const void *userData);
};

class TransitionDamageFXParseParticleSystemShim
{
public:
	static void parseParticleSystem(INI *ini, void *instance, void *store, const void *userData);
};

void BoneFXUpdateModuleData::parseParticleSystem(INI *ini, void *instance, void *store, const void *userData)
{
	BoneFXParseParticleSystemShim::parseParticleSystem(ini, instance, store, userData);
}

void TransitionDamageFXModuleData::parseParticleSystem(INI *ini, void *instance, void *store, const void *userData)
{
	TransitionDamageFXParseParticleSystemShim::parseParticleSystem(ini, instance, store, userData);
}
