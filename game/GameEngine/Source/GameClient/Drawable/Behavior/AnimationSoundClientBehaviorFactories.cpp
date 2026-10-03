// cl: /DNDEBUG /MD /EHsc
// AnimationSoundClientBehavior factories: the retail allocations are
// 0x1c bytes for the instance (0x00121D20) and 0x18 for module data
// (0x00121DA0). Preserve these independent constructor ABI views.

class Module;
class Thing;
class INI;
class ModuleData;
class MultiIniFieldParse;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AnimationSoundClientBehaviorModuleData
{
public:
	AnimationSoundClientBehaviorModuleData();
	virtual ~AnimationSoundClientBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	unsigned char m_pad[0x14];
};

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

class AnimationSoundClientBehavior
{
public:
	AnimationSoundClientBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1c];
};

// ?friend_newModuleData@AnimationSoundClientBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AnimationSoundClientBehavior::friend_newModuleData(INI *ini)
{
	AnimationSoundClientBehaviorModuleData *data = new AnimationSoundClientBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &AnimationSoundClientBehaviorModuleData::buildFieldParse);
	return (ModuleData *)data;
}

// ?friend_newModuleInstance@AnimationSoundClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AnimationSoundClientBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new AnimationSoundClientBehavior(thing, data);
}
