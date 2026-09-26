// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: SpecialDisguiseUpdateModuleData ctor
// Retail after base: vtbl, +0x25c, +0x260, +0x254(byte), +0x258, +0x264, +0x268(byte).
// Volatile stores preserve order under MSVC 7.1.

class SpecialDisguiseUpdateModuleDataBase
{
public:
	SpecialDisguiseUpdateModuleDataBase();
	virtual void specialDisguiseModuleDataBaseAnchor();

private:
	unsigned char m_pad[0x250];
};

extern "C" char SpecialDisguiseUpdateModuleData_vtbl;

class __declspec(novtable) SpecialDisguiseUpdateModuleData
	: public SpecialDisguiseUpdateModuleDataBase
{
public:
	SpecialDisguiseUpdateModuleData();

private:
	unsigned char m_254;
	unsigned char m_pad255[3];
	unsigned int m_258;
	unsigned int m_25c;
	unsigned int m_260;
	unsigned int m_264;
	unsigned char m_268;
};

// ??0SpecialDisguiseUpdateModuleData@@QAE@XZ
SpecialDisguiseUpdateModuleData::SpecialDisguiseUpdateModuleData()
{
	*reinterpret_cast<char *volatile *>(this) =
		&SpecialDisguiseUpdateModuleData_vtbl;
	*reinterpret_cast<unsigned int volatile *>(&m_25c) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_260) = 0;
	*reinterpret_cast<unsigned char volatile *>(&m_254) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_258) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_264) = 0;
	*reinterpret_cast<unsigned char volatile *>(&m_268) = 0;
}
