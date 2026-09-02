// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: clean C++ FireWeaponCollide module-data factory.
// stlport

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

class FireWeaponCollideModuleData
{
public:
	FireWeaponCollideModuleData();
	virtual ~FireWeaponCollideModuleData();

private:
	unsigned int m_moduleTagNameKey;
	const void *m_collideWeaponTemplate;
	ObjectStatusMaskType m_requiredStatus;
	ObjectStatusMaskType m_forbiddenStatus;
	unsigned char m_fireOnce;
};

FireWeaponCollideModuleData::FireWeaponCollideModuleData()
{
	m_collideWeaponTemplate = 0;
	m_requiredStatus.clear();
	m_forbiddenStatus.clear();
	m_fireOnce = 0;
}

class INI
{
public:
	void initFromINIMultiProc(void *what, void (*parseTable)(MultiIniFieldParse &));
};

void FireWeaponCollideFieldParse(MultiIniFieldParse &);

class FireWeaponCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FireWeaponCollide@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FireWeaponCollide::friend_newModuleData(INI *ini)
{
	FireWeaponCollideModuleData *data = new FireWeaponCollideModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &FireWeaponCollideFieldParse);
	return (ModuleData *)data;
}
