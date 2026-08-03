// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift WeaponModeSpecialPowerUpdateModuleData dtor MASM to C++.
// Retail destroys the AsciiString member at this+0x1d0, then calls the
// non-inlined base destructor at 0x1bbe4 under the same SEH frame.

class AsciiString
{
public:
	~AsciiString();
};

class WeaponModeSpecialPowerUpdateModuleDataBase
{
public:
	virtual ~WeaponModeSpecialPowerUpdateModuleDataBase();

private:
	unsigned char m_pad[0x1cc];
};

class __declspec(novtable) WeaponModeSpecialPowerUpdateModuleData
	: public WeaponModeSpecialPowerUpdateModuleDataBase
{
public:
	virtual ~WeaponModeSpecialPowerUpdateModuleData();

private:
	AsciiString m_member;
};

// ??1WeaponModeSpecialPowerUpdateModuleData@@UAE@XZ
WeaponModeSpecialPowerUpdateModuleData::~WeaponModeSpecialPowerUpdateModuleData()
{
}
