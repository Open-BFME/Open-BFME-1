// cl: /DNDEBUG /MD /EHsc /DWIN32 /D_STLP_USE_STATIC_LIB /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Probe for the retail LocomotorStore override-cleanup body at 0x001B7160.

#include <map>

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Overridable
{
public:
	virtual ~Overridable() {}

	Overridable *m_nextOverride;
	bool m_isOverride;

	Overridable *deleteOverrides()
	{
		if (m_isOverride) {
			delete this;
			return 0;
		}
		if (m_nextOverride)
			m_nextOverride = m_nextOverride->deleteOverrides();
		return this;
	}
};

class LocomotorTemplate : public Overridable {};

class LocomotorStore
{
public:
	virtual void init() {}
	virtual void reset();

private:
	int m_subsystemPadding;
	std::map<NameKeyType, LocomotorTemplate *> m_locomotorTemplates;
};

void LocomotorStore::reset()
{
	std::map<NameKeyType, LocomotorTemplate *>::iterator it;
	for (it = m_locomotorTemplates.begin(); it != m_locomotorTemplates.end(); ) {
		Overridable *locoTemp = it->second->deleteOverrides();
		if (!locoTemp)
			m_locomotorTemplates.erase(it++);
		else
			++it;
	}
}
