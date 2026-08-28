// ?friend_newModuleData@FireWeaponCollide@@SAPAVModuleData@@PAVINI@@@Z
// partial score=0.82 date=2026-08-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (*proc)(MultiIniFieldParse &));
};

class ModuleData
{
};

void *operator new(unsigned int bytes);

struct FireWeaponCollideMask
{
	__forceinline FireWeaponCollideMask *constructStorage(void)
	{
		words[0] = 0;
		words[1] = 0;
		words[2] = 0;
		return this;
	}

	__forceinline void clear(void)
	{
		words[0] = 0;
		words[1] = 0;
		words[2] = 0;
	}

	volatile unsigned int words[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponCollide.h
class FireWeaponCollideModuleData : public ModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &);

	void * volatile m_vtable;				// +0x00
	unsigned int m_unused04;				// +0x04
	unsigned int m_unused08;				// +0x08
	FireWeaponCollideMask m_requiredStatus;		// +0x0C
	FireWeaponCollideMask m_forbiddenStatus;		// +0x18
	unsigned char m_fireOnce;				// +0x24
	unsigned char m_padding[3];
};

class FireWeaponCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FireWeaponCollide@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FireWeaponCollide::friend_newModuleData(INI *ini)
{
	void *memory = ::operator new(sizeof(FireWeaponCollideModuleData));
	FireWeaponCollideModuleData *data;

	if (memory)
	{
		FireWeaponCollideModuleData *object =
			(FireWeaponCollideModuleData *)memory;

		object->m_vtable = (void *)0x0108EB50;

		FireWeaponCollideMask *required = &object->m_requiredStatus;
		required = required->constructStorage();
		FireWeaponCollideMask *forbidden = &object->m_forbiddenStatus;
		forbidden = forbidden->constructStorage();

		object->m_unused08 = 0;
		required->clear();
		forbidden->clear();
		object->m_fireOnce = 0;
		data = object;
	}
	else
	{
		data = 0;
	}

	if (ini)
		ini->initFromINIMultiProc(data,
			(void (*)(MultiIniFieldParse &))0x0043ABC0);

	return data;
}
