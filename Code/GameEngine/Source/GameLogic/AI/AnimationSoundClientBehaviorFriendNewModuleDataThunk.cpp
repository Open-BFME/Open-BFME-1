// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AnimationSoundClientBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AnimationSoundClientBehaviorModuleData
{
public:
	AnimationSoundClientBehaviorModuleData();
	virtual ~AnimationSoundClientBehaviorModuleData();

private:
	unsigned char m_pad[0x14];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char AnimationSoundClientBehaviorFieldParse;

class AnimationSoundClientBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@AnimationSoundClientBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AnimationSoundClientBehavior::friend_newModuleData(INI *ini)
{
	AnimationSoundClientBehaviorModuleData *data = new AnimationSoundClientBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &AnimationSoundClientBehaviorFieldParse);
	return (ModuleData *)data;
}
