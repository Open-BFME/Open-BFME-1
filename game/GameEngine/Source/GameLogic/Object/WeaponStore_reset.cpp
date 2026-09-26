// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// WeaponStore::reset (0x001E27D0): slot 4 of WeaponStore's table 0x010A13C8,
// the SubsystemInterface reset slot (init 1, loadIniFilesFromLegend 2,
// postProcessLoad 3, reset 4, update 5 -- WeaponStore::update is slot 5).
// Zero Hour's body without deleteAllDelayedDamage, and the override's
// successor is written back into the vector. resetWeaponTemplates is inlined
// and WeaponTemplate::reset is empty in BFME, which leaves retail's empty loop.

#define _STLP_NO_EXCEPTIONS 1

#include <vector>

typedef int Int;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponTemplate
{
public:
	virtual ~WeaponTemplate();

	void reset( void ) { }
	void deleteInstance( void ) { delete this; }

	WeaponTemplate *friend_clearNextTemplate( void ) { WeaponTemplate *ret = m_nextTemplate; m_nextTemplate = 0; return ret; }
	bool isOverride( void ) { return m_nextTemplate != 0; }

private:
	WeaponTemplate *m_nextTemplate;							///< this+0x04
};

typedef _STL::vector<WeaponTemplate *> WeaponTemplateVector;

class WeaponStore
{
public:
	virtual void reset();

protected:
	void resetWeaponTemplates( void )
	{
		for (Int i = 0; i < m_weaponTemplateVector.size(); i++)
		{
			WeaponTemplate* wt = m_weaponTemplateVector[i];
			wt->reset();
		}
	}

private:
	unsigned char m_unmodelled004[0x4];
	WeaponTemplateVector m_weaponTemplateVector;			///< this+0x08
};

// ?reset@WeaponStore@@UAEXXZ
void WeaponStore::reset()
{
	// clean up any overriddes.
	for (WeaponTemplateVector::iterator it = m_weaponTemplateVector.begin(); it != m_weaponTemplateVector.end(); ++it)
	{
		WeaponTemplate *wt = *it;
		if (wt->isOverride())
		{
			WeaponTemplate *override = wt;
			wt = wt->friend_clearNextTemplate();
			override->deleteInstance();
			*it = wt;
		}
	}

	resetWeaponTemplates();
}
