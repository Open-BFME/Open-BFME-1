// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TransportAIUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class TransportAIUpdateModuleData
{
public:
	TransportAIUpdateModuleData();
	virtual ~TransportAIUpdateModuleData();

private:
	unsigned char m_pad[0x60];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char TransportAIUpdateFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransportAIUpdate.h
class TransportAIUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@TransportAIUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TransportAIUpdate::friend_newModuleData(INI *ini)
{
	TransportAIUpdateModuleData *data = new TransportAIUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &TransportAIUpdateFieldParse);
	return (ModuleData *)data;
}
