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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char LargeGroupAudioUpdateFieldParse;

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
		ini->initFromINI(data, &LargeGroupAudioUpdateFieldParse);
	return (ModuleData *)data;
}
