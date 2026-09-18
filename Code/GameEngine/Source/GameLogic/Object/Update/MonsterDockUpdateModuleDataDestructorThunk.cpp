// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: MonsterDockUpdateModuleData dtor.
// Retail 67B SEH: release indexed handle @+0x10, base vtbl store. Handle destructor route 0x1A401 -> 0x39D550.

// Retail call 0x002CDDB8 passes owner+0x10 to ILT 0x0001A401
// -> 0x0039D550. That body reads/writes one four-byte pool index and
// releases its entry. The original C++ type and this member's role are unknown.
class Rva0039D550
{
public:
	~Rva0039D550();

private:
	unsigned int m_index;
};

class MonsterDockUpdateModuleDataBase
{
public:
	virtual ~MonsterDockUpdateModuleDataBase() {}

private:
	unsigned char m_pad[0xc];
};

class __declspec(novtable) MonsterDockUpdateModuleData
	: public MonsterDockUpdateModuleDataBase
{
public:
	virtual ~MonsterDockUpdateModuleData();

private:
	Rva0039D550 m_handle10;
};

// ??1MonsterDockUpdateModuleData@@UAE@XZ
MonsterDockUpdateModuleData::~MonsterDockUpdateModuleData()
{
}
