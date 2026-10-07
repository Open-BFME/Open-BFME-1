// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SquishCollide::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SquishCollideModuleData
{
public:
	SquishCollideModuleData();
	virtual ~SquishCollideModuleData();

private:
	unsigned char m_pad[0x4];
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

// The proc retail passes is VA 0x004173DC, the ILT stub ?j_000173dc@@YAXXZ (jumps to the
// one-byte no-op builder at 0x00122E80, shared with HordeMemberCollide).
extern void j_000173dc();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SquishCollide.h
class SquishCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SquishCollide@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SquishCollide::friend_newModuleData(INI *ini)
{
	SquishCollideModuleData *data = new SquishCollideModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))&j_000173dc);
	return (ModuleData *)data;
}
