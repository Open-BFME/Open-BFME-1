// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: StructureBody::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureBody.h
class StructureBodyModuleData
{
public:
	StructureBodyModuleData();
	virtual ~StructureBodyModuleData();

private:
	unsigned char m_pad[0x58];
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

extern "C" void __cdecl StructureBodyFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureBody.h
class StructureBody
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@StructureBody@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StructureBody::friend_newModuleData(INI *ini)
{
	StructureBodyModuleData *data = new StructureBodyModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &StructureBodyFieldParse);
	return (ModuleData *)data;
}
