// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ReflectDamage::friend_newModuleData factory, retail 0x0011E980,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "ReflectDamage".
//
// Retail allocates 0x14 bytes, which is sizeof(ReflectDamageModuleData) with its
// vptr, and calls the constructor through 0x0003E4A5.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ReflectDamageModuleData
{
public:
	ReflectDamageModuleData();
	virtual ~ReflectDamageModuleData();

private:
	unsigned char m_pad[0x10];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ReflectDamageFieldParse;

class ReflectDamage
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ReflectDamage@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ReflectDamage::friend_newModuleData(INI *ini)
{
	ReflectDamageModuleData *data = new ReflectDamageModuleData;
	if (ini)
		ini->initFromINI(data, &ReflectDamageFieldParse);
	return (ModuleData *)data;
}
