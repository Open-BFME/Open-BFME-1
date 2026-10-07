// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: EnragedBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class EnragedBehaviorModuleData
{
public:
	EnragedBehaviorModuleData();
	virtual ~EnragedBehaviorModuleData();

private:
	unsigned char m_pad[0x28];
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

// The proc operand is ILT 0x0002A74D -> 0x00203C00, the matched
// ?Rva00203C00@@YAXPAVGen00850920@@@Z.
void j_0002a74d();

class EnragedBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@EnragedBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *EnragedBehavior::friend_newModuleData(INI *ini)
{
	EnragedBehaviorModuleData *data = new EnragedBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))j_0002a74d);
	return (ModuleData *)data;
}
