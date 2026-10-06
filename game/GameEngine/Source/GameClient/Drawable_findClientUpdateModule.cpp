// Drawable::findClientUpdateModule, retail 0x00415630 (55 bytes), reached
// through the ILT stub 0x00031D2C.
//
// Identity: every retail caller is a Zero Hour site that writes
// `(LaserUpdate*)draw->findClientUpdateModule( key_LaserUpdate )`:
// AssistedTargetingUpdate::makeFeedbackLaser, SpecialAbilityUpdate::initLaser,
// LaserFXNugget::doFXObj / doFXPos and W3DLaserDraw::doDrawModule.
// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/Drawable.cpp
//
// Zero Hour's loop never advances; BFME's walks the list.

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ClientUpdateModule
{
public:
	virtual void bfmeSpare000(void) = 0;
	virtual void bfmeSpare001(void) = 0;
	virtual void bfmeSpare002(void) = 0;
	virtual void bfmeSpare003(void) = 0;
	virtual NameKeyType getModuleNameKey(void) const = 0;	// vtable +0x10
};

class Drawable
{
public:
	ClientUpdateModule *findClientUpdateModule(NameKeyType key);

private:
	unsigned char m_unreconstructed_000[0x154];
	ClientUpdateModule **m_clientUpdateModules;	// +0x154
};

ClientUpdateModule *Drawable::findClientUpdateModule(NameKeyType key)
{
	ClientUpdateModule **clientModules = m_clientUpdateModules;

	if (clientModules != 0)
	{
		ClientUpdateModule *module = *clientModules;

		while (module != 0)
		{
			if (module->getModuleNameKey() == key)
				return *clientModules;

			module = clientModules[1];
			++clientModules;
		}
	}

	return 0;
}
