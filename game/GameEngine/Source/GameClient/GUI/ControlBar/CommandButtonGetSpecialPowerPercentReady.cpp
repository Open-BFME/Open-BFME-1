// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

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
