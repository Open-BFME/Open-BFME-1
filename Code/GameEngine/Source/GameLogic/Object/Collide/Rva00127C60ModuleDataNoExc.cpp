// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME7: exceptions-off twin of the FireWeaponCollide module-data TU:
// retail 0x00127C60 (67 bytes) is the default constructor of a sibling
// module data with the same layout (the FireWeaponCollide one at 0x00852130
// is 79 bytes with the STLport try/catch kept), so the class carries an
// address-derived tag.
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

class INI;
class ModuleData;
class MultiIniFieldParse;

void *__cdecl operator new(unsigned int);

class ObjectStatusMaskType
{
public:
	ObjectStatusMaskType();
	void clear();

private:
	std::bitset<75> m_bits;
};

ObjectStatusMaskType::ObjectStatusMaskType()
{
}

void ObjectStatusMaskType::clear()
{
	m_bits.reset();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponCollide.h
class Rva00127C60ModuleData
{
public:
	Rva00127C60ModuleData();
	virtual ~Rva00127C60ModuleData();

private:
	unsigned int m_moduleTagNameKey;
	const void *m_collideWeaponTemplate;
	ObjectStatusMaskType m_requiredStatus;
	ObjectStatusMaskType m_forbiddenStatus;
	unsigned char m_fireOnce;
};

Rva00127C60ModuleData::Rva00127C60ModuleData()
{
	m_collideWeaponTemplate = 0;
	m_requiredStatus.clear();
	m_forbiddenStatus.clear();
	m_fireOnce = 0;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what, void (*parseTable)(MultiIniFieldParse &));
};

void FireWeaponCollideFieldParse(MultiIniFieldParse &);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponCollide.h
class FireWeaponCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FireWeaponCollide@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FireWeaponCollide::friend_newModuleData(INI *ini)
{
	Rva00127C60ModuleData *data = new Rva00127C60ModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &FireWeaponCollideFieldParse);
	return (ModuleData *)data;
}
