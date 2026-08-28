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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SquishCollideFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SquishCollide.h
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
		ini->initFromINI(data, &SquishCollideFieldParse);
	return (ModuleData *)data;
}
