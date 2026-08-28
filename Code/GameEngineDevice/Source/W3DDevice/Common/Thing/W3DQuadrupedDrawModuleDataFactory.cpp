// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DQuadrupedDraw::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class W3DQuadrupedDrawModuleData
{
public:
	W3DQuadrupedDrawModuleData();
	virtual ~W3DQuadrupedDrawModuleData();

private:
	unsigned char m_pad[0x168];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char W3DQuadrupedDrawFieldParse;

class W3DQuadrupedDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DQuadrupedDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DQuadrupedDraw::friend_newModuleData(INI *ini)
{
	W3DQuadrupedDrawModuleData *data = new W3DQuadrupedDrawModuleData;
	if (ini)
		ini->initFromINI(data, &W3DQuadrupedDrawFieldParse);
	return (ModuleData *)data;
}
