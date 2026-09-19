// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HorseHordeContain::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HorseHordeContainModuleData
{
public:
	HorseHordeContainModuleData();
	virtual ~HorseHordeContainModuleData();

private:
	unsigned char m_pad[0x2f0];
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

extern "C" void __cdecl HorseHordeContainFieldParse(MultiIniFieldParse &parse);

class HorseHordeContain
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@HorseHordeContain@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HorseHordeContain::friend_newModuleData(INI *ini)
{
	HorseHordeContainModuleData *data = new HorseHordeContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &HorseHordeContainFieldParse);
	return (ModuleData *)data;
}
