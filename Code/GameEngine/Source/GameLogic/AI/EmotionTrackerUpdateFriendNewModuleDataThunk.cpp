// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: EmotionTrackerUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class EmotionTrackerUpdateModuleData
{
public:
	EmotionTrackerUpdateModuleData();
	virtual ~EmotionTrackerUpdateModuleData();

private:
	unsigned char m_pad[0x38];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char EmotionTrackerUpdateFieldParse;

class EmotionTrackerUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@EmotionTrackerUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *EmotionTrackerUpdate::friend_newModuleData(INI *ini)
{
	EmotionTrackerUpdateModuleData *data = new EmotionTrackerUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &EmotionTrackerUpdateFieldParse);
	return (ModuleData *)data;
}
