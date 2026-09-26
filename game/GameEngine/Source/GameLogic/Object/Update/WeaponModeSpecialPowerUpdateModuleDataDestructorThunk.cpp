// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponModeSpecialPowerUpdateModuleData dtor.
// SEH: BFMERetailAsciiString @+0x1d0 then base dtor pin 0x1bbe4.

// Retail destroys this member with a direct call to
// StringBase<char>::releaseBuffer (0x00887940) -- the member is a retail
// AsciiString, not the WWLib Buffer whose own destructor is the 40-byte
// body at 0x009E1E30, so name it the way the other lifted ModuleData
// destructors already do.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	unsigned char m_pad[4];
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
	BFMERetailAsciiString m_buffer;
};

// ??1WeaponModeSpecialPowerUpdateModuleData@@UAE@XZ
WeaponModeSpecialPowerUpdateModuleData::~WeaponModeSpecialPowerUpdateModuleData()
{
}
