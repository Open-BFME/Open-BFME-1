// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: KeepObjectDie::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class KeepObjectDieModuleData
{
public:
	KeepObjectDieModuleData();
	virtual ~KeepObjectDieModuleData();

private:
	unsigned char m_pad[0x30];
};

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl KeepObjectDieFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/KeepObjectDie.h
class KeepObjectDie
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@KeepObjectDie@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *KeepObjectDie::friend_newModuleData(INI *ini)
{
	KeepObjectDieModuleData *data = new KeepObjectDieModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &KeepObjectDieFieldParse);
	return (ModuleData *)data;
}
