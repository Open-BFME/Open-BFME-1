// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WoundArrowUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class WoundArrowUpdateModuleData
{
public:
	WoundArrowUpdateModuleData();
	virtual ~WoundArrowUpdateModuleData();

private:
	unsigned char m_pad[0x258];
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

// Retail pushes 0x004022C5, the matched ILT thunk to 0x0026DF80.
extern void j_000022c5(void);

class WoundArrowUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@WoundArrowUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WoundArrowUpdate::friend_newModuleData(INI *ini)
{
	WoundArrowUpdateModuleData *data = new WoundArrowUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, 
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(&j_000022c5));
	return (ModuleData *)data;
}
