// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: ArrowStormUpdateModuleData ctor
// Base call, vtbl, zeros/ones at +0x254..+0x268.

class ArrowStormUpdateModuleDataBase
{
public:
	ArrowStormUpdateModuleDataBase();
	virtual void arrowStormModuleDataBaseAnchor();

private:
	unsigned char m_pad[0x250];
};

extern "C" char ArrowStormUpdateModuleData_vtbl;

class __declspec(novtable) ArrowStormUpdateModuleData
	: public ArrowStormUpdateModuleDataBase
{
public:
	ArrowStormUpdateModuleData();

private:
	unsigned int m_254;
	unsigned int m_258;
	unsigned int m_25c;
	unsigned int m_260;
	unsigned int m_264;
	unsigned char m_268;
};

// ??0ArrowStormUpdateModuleData@@QAE@XZ
ArrowStormUpdateModuleData::ArrowStormUpdateModuleData()
{
	*reinterpret_cast<char *volatile *>(this) =
		&ArrowStormUpdateModuleData_vtbl;
	*reinterpret_cast<unsigned int volatile *>(&m_254) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_25c) = 1;
	*reinterpret_cast<unsigned int volatile *>(&m_260) = 1;
	*reinterpret_cast<unsigned int volatile *>(&m_264) = 1;
	*reinterpret_cast<unsigned int volatile *>(&m_258) = 0;
	*reinterpret_cast<unsigned char volatile *>(&m_268) = 0;
}
