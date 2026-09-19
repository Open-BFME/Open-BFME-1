// ??0W3DHordeModelDrawModuleData@@QAE@XZ
// partial score=0.82 date=2026-08-31
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DHordeModelDraw::friend_newModuleData factory, retail 0x006BFC60,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "W3DHordeModelDraw".
//
// Retail allocates 0x198 bytes, which is sizeof(W3DHordeModelDrawModuleData) with its
// vptr, and calls the constructor through 0x00037187.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class W3DHordeModelDrawModuleDataBase
{
public:
	W3DHordeModelDrawModuleDataBase();
	virtual ~W3DHordeModelDrawModuleDataBase();

private:
	unsigned char m_basePad[0x158];
};

class __declspec(novtable) W3DHordeModelDrawModuleData : public W3DHordeModelDrawModuleDataBase
{
public:
	W3DHordeModelDrawModuleData();
	virtual ~W3DHordeModelDrawModuleData();

private:
	unsigned char m_15C;
	unsigned char m_pad15D[3];
	int m_160;
	int m_164;
	float m_168;
	int m_16C;
	unsigned char m_170;
	unsigned char m_pad171[3];
	int m_174;
	int m_178;
	float m_17C;
	int m_180;
	unsigned char m_184;
	unsigned char m_pad185[3];
	int m_188;
	int m_18C;
	float m_190;
	int m_194;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char W3DHordeModelDrawFieldParse;
extern "C" char W3DHordeModelDrawModuleData_vtbl;

W3DHordeModelDrawModuleData::W3DHordeModelDrawModuleData()
{
	m_15C = 0;
	m_160 = 1;
	m_164 = 1;
	*reinterpret_cast<char **>(this) = &W3DHordeModelDrawModuleData_vtbl;
	m_168 = 15.0f;
	m_16C = 0;
	m_170 = 1;
	m_174 = 2;
	m_178 = 2;
	m_17C = 8.0f;
	m_180 = 50;
	m_184 = 1;
	m_188 = 999;
	m_18C = 999;
	m_190 = 0.5f;
	m_194 = 100;
}

class W3DHordeModelDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DHordeModelDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DHordeModelDraw::friend_newModuleData(INI *ini)
{
	W3DHordeModelDrawModuleData *data = new W3DHordeModelDrawModuleData;
	if (ini)
		ini->initFromINI(data, &W3DHordeModelDrawFieldParse);
	return (ModuleData *)data;
}
