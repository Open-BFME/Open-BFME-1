// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: LargeGroupAudioUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class LargeGroupAudioUpdateModuleData
{
public:
	LargeGroupAudioUpdateModuleData();
	virtual ~LargeGroupAudioUpdateModuleData();

private:
	unsigned char m_pad[0x1c];
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

// Retail pushes the ILT stub 0x0000589E (?j_0000589e@@YAXXZ).
extern void j_0000589e(void);

class LargeGroupAudioUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@LargeGroupAudioUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *LargeGroupAudioUpdate::friend_newModuleData(INI *ini)
{
	LargeGroupAudioUpdateModuleData *data = new LargeGroupAudioUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))j_0000589e);
	return (ModuleData *)data;
}
