// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: WeaponModeSpecialPowerUpdateModuleDataBase constructor.
// Retail installs vtable 0x010B7D40, clears +0x08 and +0x1CC, and constructs
// four BfmeNamedSlot members at +0x0C, +0x7C, +0xEC, and +0x15C.

typedef int Int;

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

class BfmeNamedSlot
{
public:
	BfmeNamedSlot( const AsciiString &name, Int flags );
	~BfmeNamedSlot();

private:
	char m_data[0x70];
};

class WeaponModeSpecialPowerUpdateModuleDataBaseParent
{
public:
	virtual void moduleDataBaseAnchor();
	virtual ~WeaponModeSpecialPowerUpdateModuleDataBaseParent();

private:
	unsigned int m_pad04;
};

class WeaponModeSpecialPowerUpdateModuleDataBase
	: public WeaponModeSpecialPowerUpdateModuleDataBaseParent
{
public:
	WeaponModeSpecialPowerUpdateModuleDataBase();
	virtual void moduleDataBaseAnchor();
	virtual ~WeaponModeSpecialPowerUpdateModuleDataBase();

private:
	unsigned int m_zero08;
	BfmeNamedSlot m_packSound;
	BfmeNamedSlot m_unpackSound;
	BfmeNamedSlot m_prepSoundLoop;
	BfmeNamedSlot m_triggerSound;
	unsigned char m_zero1cc;
};

// ??0WeaponModeSpecialPowerUpdateModuleDataBase@@QAE@XZ
WeaponModeSpecialPowerUpdateModuleDataBase::WeaponModeSpecialPowerUpdateModuleDataBase()
	: m_zero08( 0 ),
	  m_packSound( *reinterpret_cast<const AsciiString *>( 0x01336e50 ), 0 ),
	  m_unpackSound( *reinterpret_cast<const AsciiString *>( 0x01336e50 ), 0 ),
	  m_prepSoundLoop( *reinterpret_cast<const AsciiString *>( 0x01336e50 ), 0 ),
	  m_triggerSound( *reinterpret_cast<const AsciiString *>( 0x01336e50 ), 0 )
{
	m_zero1cc = 0;
}
