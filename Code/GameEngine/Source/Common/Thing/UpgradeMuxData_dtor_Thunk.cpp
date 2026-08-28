// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: UpgradeMuxData::~UpgradeMuxData, retail 0x0058C4C0,
// zh_sweep packet 0058c4c0.
//
// The destructor is entirely implicit -- four members destroyed in reverse
// order with the EH state stepping 2, 1, 0, -1 -- and compiled inside
// ModuleFactory.cpp the shape was already exact. Only the stride was wrong:
// retail destroys members at [this+0x0C], +0x08, +0x04 and +0x00, where the
// vendored class destroys them at +0x24, +0x18, +0x0C and +0x00.
//
// So BFME's four upgrade-name lists are four-byte objects, not the reference's
// four twelve-byte std::vector<AsciiString>. All four destructor calls go to
// the same body, 0x008881D0, which this ledger already records as the wide
// string destructor -- ??1UnicodeString@@QAE@XZ and ??1?$StringBase@G@@AAE@XZ
// both pin there, along with UnicodeString::releaseBuffer and clear.
//
// That is as far as the bytes go: four members, four bytes each, one shared
// destructor body whose recorded name is UnicodeString's. Whether BFME really
// stores these upgrade names as wide strings or as some other four-byte handle
// that folds onto the same code is not settled here, so the member names are
// kept from the reference and only the type is taken from the call target.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	~UnicodeString();										///< body 0x008881D0

private:
	void *m_data;
};

class UpgradeMuxData
{
public:
	~UpgradeMuxData();

	UnicodeString m_triggerUpgradeNames;					///< +0x00
	UnicodeString m_activationUpgradeNames;					///< +0x04
	UnicodeString m_conflictingUpgradeNames;				///< +0x08
	UnicodeString m_removalUpgradeNames;					///< +0x0C
};

// ??1UpgradeMuxData@@QAE@XZ
UpgradeMuxData::~UpgradeMuxData()
{
}
