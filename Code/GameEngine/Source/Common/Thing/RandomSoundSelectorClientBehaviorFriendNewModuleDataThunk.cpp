// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RandomSoundSelectorClientBehavior::friend_newModuleData factory, retail 0x0012BE60,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "RandomSoundSelectorClientBehavior".
//
// Retail allocates 0x1D4 bytes, which is sizeof(RandomSoundSelectorClientBehaviorModuleData) with its
// vptr, and calls the constructor through 0x0001F528.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class RandomSoundSelectorClientBehaviorModuleData
{
public:
	RandomSoundSelectorClientBehaviorModuleData();
	virtual ~RandomSoundSelectorClientBehaviorModuleData();

private:
	unsigned char m_pad[0x1D0];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char RandomSoundSelectorClientBehaviorFieldParse;

class RandomSoundSelectorClientBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@RandomSoundSelectorClientBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RandomSoundSelectorClientBehavior::friend_newModuleData(INI *ini)
{
	RandomSoundSelectorClientBehaviorModuleData *data = new RandomSoundSelectorClientBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &RandomSoundSelectorClientBehaviorFieldParse);
	return (ModuleData *)data;
}
