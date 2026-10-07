// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ArrowStormUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ArrowStormUpdateModuleData
{
public:
	ArrowStormUpdateModuleData();
	virtual ~ArrowStormUpdateModuleData();

private:
	unsigned char m_pad[0x268];
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

// The proc operand is ILT 0x0004119B -> 0x00118E80, the matched
// Rva00118E80::buildFieldParse (game/GameEngine/Source/Common/WideBuildFieldParse.cpp).
void j_0004119b();

class ArrowStormUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ArrowStormUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ArrowStormUpdate::friend_newModuleData(INI *ini)
{
	ArrowStormUpdateModuleData *data = new ArrowStormUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, 
			(void (__cdecl *)(MultiIniFieldParse &))j_0004119b);
	return (ModuleData *)data;
}
