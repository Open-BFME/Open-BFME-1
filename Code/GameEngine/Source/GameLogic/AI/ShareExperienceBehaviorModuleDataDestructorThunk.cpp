// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ShareExperienceBehaviorModuleData dtor.
// Retail 67B SEH: release indexed handle @+0x14, base vtbl store. Handle destructor route 0x1A401 -> 0x39D550.

// Retail call 0x002059E8 passes owner+0x14 to ILT 0x0001A401
// -> 0x0039D550. That body reads/writes one four-byte pool index and
// releases its entry. The original C++ type and this member's role are unknown.
class Rva0039D550
{
public:
	~Rva0039D550();

private:
	unsigned int m_index;
};

class ShareExperienceBehaviorModuleDataBase
{
public:
	virtual ~ShareExperienceBehaviorModuleDataBase() {}

private:
	unsigned char m_pad[0x10];
};

class __declspec(novtable) ShareExperienceBehaviorModuleData
	: public ShareExperienceBehaviorModuleDataBase
{
public:
	virtual ~ShareExperienceBehaviorModuleData();

private:
	Rva0039D550 m_handle14;
};

// ??1ShareExperienceBehaviorModuleData@@UAE@XZ
ShareExperienceBehaviorModuleData::~ShareExperienceBehaviorModuleData()
{
}
