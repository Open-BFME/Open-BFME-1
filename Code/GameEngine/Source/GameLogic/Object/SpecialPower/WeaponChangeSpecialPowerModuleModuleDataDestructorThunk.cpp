// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponChangeSpecialPowerModuleModuleData dtor. 2x BFMERetailAsciiString then base.

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

class WeaponChangeSpecialPowerModuleModuleDataBase
{
public:
	virtual ~WeaponChangeSpecialPowerModuleModuleDataBase();
private:
	unsigned char m_pad[0x218];
};

class __declspec(novtable) WeaponChangeSpecialPowerModuleModuleData : public WeaponChangeSpecialPowerModuleModuleDataBase
{
public:
	virtual ~WeaponChangeSpecialPowerModuleModuleData();
private:
	BFMERetailAsciiString m_0;
	BFMERetailAsciiString m_1;
};

// ??1WeaponChangeSpecialPowerModuleModuleData@@UAE@XZ
WeaponChangeSpecialPowerModuleModuleData::~WeaponChangeSpecialPowerModuleModuleData()
{
}
