// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift WeaponFireSpecialAbilityUpdateModuleData dtor MASM to C++.
// Retail destroys the AsciiString member at this+0x254, then calls the
// non-inlined base destructor at 0x1980d under the same SEH frame.

class AsciiString
{
public:
	~AsciiString();
};

class WeaponFireSpecialAbilityUpdateModuleDataBase
{
public:
	virtual ~WeaponFireSpecialAbilityUpdateModuleDataBase();

private:
	unsigned char m_pad[0x250];
};

class __declspec(novtable) WeaponFireSpecialAbilityUpdateModuleData
	: public WeaponFireSpecialAbilityUpdateModuleDataBase
{
public:
	virtual ~WeaponFireSpecialAbilityUpdateModuleData();

private:
	AsciiString m_member;
};

// ??1WeaponFireSpecialAbilityUpdateModuleData@@UAE@XZ
WeaponFireSpecialAbilityUpdateModuleData::~WeaponFireSpecialAbilityUpdateModuleData()
{
}
