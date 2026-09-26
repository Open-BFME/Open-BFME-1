// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: TemporarilyDefectUpdate::friend_newModuleData

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class TemporarilyDefectUpdateModuleData
{
public:
	TemporarilyDefectUpdateModuleData();
	virtual ~TemporarilyDefectUpdateModuleData();
private:
	unsigned int m_pad;
	unsigned int m_field;
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

extern "C" void __cdecl TemporarilyDefectUpdateFieldParse(MultiIniFieldParse &parse);

class TemporarilyDefectUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

TemporarilyDefectUpdateModuleData::TemporarilyDefectUpdateModuleData()
{
	m_field = 0;
}

// ?friend_newModuleData@TemporarilyDefectUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TemporarilyDefectUpdate::friend_newModuleData(INI *ini)
{
	TemporarilyDefectUpdateModuleData *data = new TemporarilyDefectUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &TemporarilyDefectUpdateFieldParse);
	return (ModuleData *)data;
}
