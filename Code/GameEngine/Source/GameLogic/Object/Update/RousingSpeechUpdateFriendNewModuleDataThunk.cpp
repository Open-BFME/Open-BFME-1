// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RousingSpeechUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class RousingSpeechUpdateModuleData
{
public:
	RousingSpeechUpdateModuleData();
	virtual ~RousingSpeechUpdateModuleData();

private:
	unsigned char m_pad[0x280];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char RousingSpeechUpdateFieldParse;

class RousingSpeechUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@RousingSpeechUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RousingSpeechUpdate::friend_newModuleData(INI *ini)
{
	RousingSpeechUpdateModuleData *data = new RousingSpeechUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &RousingSpeechUpdateFieldParse);
	return (ModuleData *)data;
}
