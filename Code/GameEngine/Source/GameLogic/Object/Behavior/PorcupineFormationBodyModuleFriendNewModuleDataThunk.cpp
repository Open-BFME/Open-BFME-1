// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PorcupineFormationBodyModule::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class PorcupineFormationBodyModuleModuleData
{
public:
	PorcupineFormationBodyModuleModuleData();
	virtual ~PorcupineFormationBodyModuleModuleData();

private:
	unsigned char m_pad[0x60];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char PorcupineFormationBodyModuleFieldParse;

class PorcupineFormationBodyModule
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@PorcupineFormationBodyModule@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PorcupineFormationBodyModule::friend_newModuleData(INI *ini)
{
	PorcupineFormationBodyModuleModuleData *data = new PorcupineFormationBodyModuleModuleData;
	if (ini)
		ini->initFromINI(data, &PorcupineFormationBodyModuleFieldParse);
	return (ModuleData *)data;
}
