// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

class SpecialPowerTemplate;

class SpecialPowerModuleInterface
{
public:
	virtual bool isModuleForPower(const SpecialPowerTemplate *power) const = 0;
	virtual bool isReady() const = 0;
	virtual float getPercentReady() const = 0;
};

class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
};

class CommandButton
{
public:
	float getSpecialPowerPercentReady(const Object *source) const;

private:
	char m_fields[0x34];
	const SpecialPowerTemplate *m_specialPower;
};

float CommandButton::getSpecialPowerPercentReady(const Object *source) const
{
	SpecialPowerModuleInterface *module = source->getSpecialPowerModule(m_specialPower);
	if (module == 0)
		return -1.0f;

	return module->getPercentReady();
}
