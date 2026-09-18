// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpecialEnemySenseUpdateModuleData dtor.
// Retail 67B SEH: release indexed handle @+0x8, base vtbl store. Handle destructor route 0x1A401 -> 0x39D550.

// Retail call 0x001258B8 passes owner+0x8 to ILT 0x0001A401
// -> 0x0039D550. That body reads/writes one four-byte pool index and
// releases its entry. The original C++ type and this member's role are unknown.
class Rva0039D550
{
public:
	~Rva0039D550();

private:
	unsigned int m_index;
};

class SpecialEnemySenseUpdateModuleDataBase
{
public:
	virtual ~SpecialEnemySenseUpdateModuleDataBase() {}

private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) SpecialEnemySenseUpdateModuleData
	: public SpecialEnemySenseUpdateModuleDataBase
{
public:
	virtual ~SpecialEnemySenseUpdateModuleData();

private:
	Rva0039D550 m_handle08;
};

// ??1SpecialEnemySenseUpdateModuleData@@UAE@XZ
SpecialEnemySenseUpdateModuleData::~SpecialEnemySenseUpdateModuleData()
{
}
