// cl: /DNDEBUG /MD /EHsc /DWIN32 /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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
