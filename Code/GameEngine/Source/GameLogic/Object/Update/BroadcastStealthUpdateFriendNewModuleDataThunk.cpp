// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: BroadcastStealthUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class BroadcastStealthUpdateModuleData
{
public:
	BroadcastStealthUpdateModuleData();
	virtual ~BroadcastStealthUpdateModuleData();

private:
	unsigned char m_pad[0x90]; // vptr+0x90=0x94
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

extern "C" void __cdecl BroadcastStealthUpdateFieldParse(MultiIniFieldParse &parse);

class BroadcastStealthUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@BroadcastStealthUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BroadcastStealthUpdate::friend_newModuleData(INI *ini)
{
	BroadcastStealthUpdateModuleData *data = new BroadcastStealthUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &BroadcastStealthUpdateFieldParse);
	return (ModuleData *)data;
}
