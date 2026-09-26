// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DeletionUpdate::friend_newModuleData

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DeletionUpdate.h
class DeletionUpdateModuleData
{
public:
	DeletionUpdateModuleData();
	virtual ~DeletionUpdateModuleData();
private:
	unsigned int m_pad;
	unsigned int m_a;
	unsigned int m_b;
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

extern "C" void __cdecl DeletionUpdateFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DeletionUpdate.h
class DeletionUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

DeletionUpdateModuleData::DeletionUpdateModuleData()
{
	m_a = 0;
	m_b = 0;
}

// ?friend_newModuleData@DeletionUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DeletionUpdate::friend_newModuleData(INI *ini)
{
	DeletionUpdateModuleData *data = new DeletionUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &DeletionUpdateFieldParse);
	return (ModuleData *)data;
}
