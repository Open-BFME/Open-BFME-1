// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/weapon /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Open-BFME7: retail 0x003BDAE0 (73 bytes) is the twin of WeaponStore::findWeaponTemplatePrivate
// (Weapon.cpp, 0x001E42F0) on another template store: its pointer vector sits at +0x38 and the
// templates keep their name key at +8 instead of +0xC.  Address-tagged classes, same include set.
#include "PreRTS.h"
#include "Common/STLTypedefs.h"

class Rva003BDAE0Template
{
public:
	NameKeyType getNameKey() const { return m_nameKey; }
private:
	unsigned char m_unmodelled_00[ 8 ];
	NameKeyType m_nameKey;				// +0x08
};

class Rva003BDAE0Store
{
public:
	Rva003BDAE0Template *findTemplatePrivate( NameKeyType key ) const;
private:
	unsigned char m_unmodelled_00[ 0x38 ];
	std::vector<Rva003BDAE0Template *> m_templateVector;	// +0x38
};

Rva003BDAE0Template *Rva003BDAE0Store::findTemplatePrivate( NameKeyType key ) const
{
	for (Int i = 0; i < m_templateVector.size(); i++)
		if( m_templateVector[ i ]->getNameKey() == key )
			return m_templateVector[i];

	return NULL;
}
