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
	volatile unsigned char m_15C;
	unsigned char m_pad15D[3];
	volatile int m_160;
	volatile int m_164;
	volatile float m_168;
	volatile int m_16C;
	volatile unsigned char m_170;
	unsigned char m_pad171[3];
	volatile int m_174;
	volatile int m_178;
	volatile float m_17C;
	volatile int m_180;
	volatile unsigned char m_184;
	unsigned char m_pad185[3];
	volatile int m_188;
	volatile int m_18C;
	volatile float m_190;
	volatile int m_194;
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
	int one = 1;
	int zero = 0;
	int defaultValue = 999;
	int mode = 2;
	*reinterpret_cast<unsigned int volatile *>(reinterpret_cast<unsigned char *>(this) + 0x160) = one;
	*reinterpret_cast<unsigned int volatile *>(reinterpret_cast<unsigned char *>(this) + 0x164) = one;
	*reinterpret_cast<unsigned char volatile *>(reinterpret_cast<unsigned char *>(this) + 0x170) = (unsigned char)one;
	*reinterpret_cast<unsigned char volatile *>(reinterpret_cast<unsigned char *>(this) + 0x184) = (unsigned char)one;
	*reinterpret_cast<unsigned char volatile *>(reinterpret_cast<unsigned char *>(this) + 0x15C) = (unsigned char)zero;
	*reinterpret_cast<unsigned int volatile *>(reinterpret_cast<unsigned char *>(this) + 0x16C) = zero;
	*reinterpret_cast<unsigned int volatile *>(reinterpret_cast<unsigned char *>(this) + 0x188) = defaultValue;
	*reinterpret_cast<unsigned int volatile *>(reinterpret_cast<unsigned char *>(this) + 0x18C) = defaultValue;
	*reinterpret_cast<char *volatile *>(this) = &W3DHordeModelDrawModuleData_vtbl;
	*reinterpret_cast<unsigned int volatile *>(reinterpret_cast<unsigned char *>(this) + 0x168) = 0x41700000;
	*reinterpret_cast<unsigned int volatile *>(reinterpret_cast<unsigned char *>(this) + 0x174) = mode;
	*reinterpret_cast<unsigned int volatile *>(reinterpret_cast<unsigned char *>(this) + 0x178) = mode;
	*reinterpret_cast<unsigned int volatile *>(reinterpret_cast<unsigned char *>(this) + 0x17C) = 0x41000000;
	*reinterpret_cast<unsigned int volatile *>(reinterpret_cast<unsigned char *>(this) + 0x180) = 0x32;
	*reinterpret_cast<unsigned int volatile *>(reinterpret_cast<unsigned char *>(this) + 0x190) = 0x3F000000;
	*reinterpret_cast<unsigned int volatile *>(reinterpret_cast<unsigned char *>(this) + 0x194) = 0x64;
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
