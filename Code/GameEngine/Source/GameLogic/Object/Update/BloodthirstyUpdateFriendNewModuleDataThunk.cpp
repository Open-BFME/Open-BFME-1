// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BloodthirstyUpdate::friend_newModuleData factory, retail 0x00114030,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "BloodthirstyUpdate".
//
// Retail allocates 0xF0 bytes, which is sizeof(BloodthirstyUpdateModuleData) with its
// vptr, and calls the constructor through 0x0001C684.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class BloodthirstyUpdateModuleData
{
public:
	BloodthirstyUpdateModuleData();
	virtual ~BloodthirstyUpdateModuleData();

private:
	unsigned char m_pad[0xEC];
};

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl BloodthirstyUpdateFieldParse(MultiIniFieldParse &parse);

class BloodthirstyUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@BloodthirstyUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BloodthirstyUpdate::friend_newModuleData(INI *ini)
{
	BloodthirstyUpdateModuleData *data = new BloodthirstyUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &BloodthirstyUpdateFieldParse);
	return (ModuleData *)data;
}
