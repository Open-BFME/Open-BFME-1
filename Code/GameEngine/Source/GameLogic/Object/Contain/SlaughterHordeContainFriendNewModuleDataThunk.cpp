// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SlaughterHordeContain::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SlaughterHordeContainModuleData
{
public:
	SlaughterHordeContainModuleData();
	virtual ~SlaughterHordeContainModuleData();

private:
	unsigned char m_pad[0x314];
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

extern "C" void __cdecl SlaughterHordeContainFieldParse(MultiIniFieldParse &parse);

class SlaughterHordeContain
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SlaughterHordeContain@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SlaughterHordeContain::friend_newModuleData(INI *ini)
{
	SlaughterHordeContainModuleData *data = new SlaughterHordeContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &SlaughterHordeContainFieldParse);
	return (ModuleData *)data;
}
