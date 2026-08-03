// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

// Open-BFME5: SwayClientUpdate::getModuleNameKey lifted from the standard
// module macro; the standalone TU preserves its inline static NameKey body.

enum NameKeyType
{
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

inline NameKeyType NAMEKEY(const char *name)
{
	return TheNameKeyGenerator->nameToKey(name);
}

class SwayClientUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SwayClientUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType SwayClientUpdate::getModuleNameKey() const
{
	static NameKeyType nk = NAMEKEY("SwayClientUpdate");
	return nk;
}
