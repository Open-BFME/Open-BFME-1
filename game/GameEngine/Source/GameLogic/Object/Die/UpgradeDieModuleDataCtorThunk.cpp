// cl: /DNDEBUG /MD /EHsc
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.

// An intermediate DieModuleData base whose constructor is inlined -- it stores
// its own vptr at 0x00 and constructs the member at 0x08 through an out-of-line
// call, resolved by the existing pin for ??0InstantDeathDieMuxData@@QAE@XZ at
// 0x000071E4. This class then overwrites the vptr with its own and zeroes 0x34.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot() {}

private:
	unsigned char m_data[4];
};

class InstantDeathDieMuxData
{
public:
	InstantDeathDieMuxData();

private:
	unsigned char m_body[0x2c];				///< 0x08 .. 0x34
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleData : public Snapshot
{
public:
	DieModuleData() {}
	virtual ~DieModuleData() {}

	InstantDeathDieMuxData m_mux;			///< 0x08
};

class BFMERetailAsciiString
{
public:
	// UpgradeDie's upstream UpgradeToRemove field is an AsciiString. Retail
	// zero-initializes its four-byte storage in the ctor and releases it from
	// +0x34 in the dtor, so both lifecycle bodies share this view.
	BFMERetailAsciiString() : m_data( 0 ) {}
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	int m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeDie.h
class UpgradeDieModuleData : public DieModuleData
{
public:
	UpgradeDieModuleData();
	virtual ~UpgradeDieModuleData();

	virtual void moduleDataAnchor();

	BFMERetailAsciiString m_upgradeName;								///< 0x34
};

// ??0UpgradeDieModuleData@@QAE@XZ
UpgradeDieModuleData::UpgradeDieModuleData()
	: m_upgradeName()
{
}

// MSVC applies novtable to this out-of-line definition while retaining the
// ordinary declaration above for constructor vtable emission.
class __declspec(novtable) UpgradeDieModuleData;

// ??1UpgradeDieModuleData@@UAE@XZ
UpgradeDieModuleData::~UpgradeDieModuleData()
{
}
