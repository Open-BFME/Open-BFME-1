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

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl W3DQuadrupedDrawFieldParse(MultiIniFieldParse &parse);

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
		ini->initFromINIMultiProc(data, &W3DQuadrupedDrawFieldParse);
	return (ModuleData *)data;
}
