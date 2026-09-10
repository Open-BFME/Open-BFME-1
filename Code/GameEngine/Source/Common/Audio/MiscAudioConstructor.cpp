// cl: /DNDEBUG /MD /EHsc

// Retail 0x00694E60 is MiscAudio::MiscAudio(), the constructor selected by
// AudioManager::AudioManager() before it loads MiscAudio.ini.  The BFME
// MiscAudio layout is the 32-entry retail INI table at RVA0x00C83310
// recorded in reverse/field_names.csv (NoCanDo+3F0; CrateSalvage+930):
// the first 26 entries retain the ZH fields and the final six are BFME audio
// additions.  Each entry is an embedded 0x70-byte AudioEventRTS and is
// initialized with the shared empty name and extra value zero.

class AsciiString
{
public:
	static const AsciiString TheEmptyString;
};

// This embedded-member view stores the vptr explicitly and uses the scalar
// destructor spelling owned at RVA 0x000B31F0 (ILT 0x00026F35). Its complete
// owner has a virtual destructor; this TU only makes direct subobject cleanup
// calls and emits no vtable. The historical UAE pin names another body.
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int extra);
	~AudioEventRTS();

private:
	void *m_vptr;
	unsigned char m_bfmeData[0x6c];
};

// The retail extra-argument calls use ILT0x00025306 to the already
// matched full AudioEventRTS constructor at0x000B2CC0 (159 bytes).

struct MiscAudio
{
	AudioEventRTS m_radarHarvesterUnderAttackSound;
	AudioEventRTS m_radarStructureUnderAttackSound;
	AudioEventRTS m_radarInfiltrationSound;
	AudioEventRTS m_radarOnlineSound;
	AudioEventRTS m_radarOfflineSound;
	AudioEventRTS m_defectorTimerTickSound;
	AudioEventRTS m_defectorTimerDingSound;
	AudioEventRTS m_allCheerSound;
	AudioEventRTS m_battleCrySound;
	AudioEventRTS m_noCanDoSound;
	AudioEventRTS m_stealthDiscoveredSound;
	AudioEventRTS m_stealthNeutralizedSound;
	AudioEventRTS m_moneyDepositSound;
	AudioEventRTS m_moneyWithdrawSound;
	AudioEventRTS m_buildingDisabled;
	AudioEventRTS m_buildingReenabled;
	AudioEventRTS m_vehicleDisabled;
	AudioEventRTS m_vehicleReenabled;
	AudioEventRTS m_splatterVehiclePilotsBrain;
	AudioEventRTS m_crateHeal;
	AudioEventRTS m_crateShroud;
	AudioEventRTS m_crateSalvage;
	AudioEventRTS m_crateFreeUnit;
	AudioEventRTS m_crateMoney;
	AudioEventRTS m_unitPromoted;
	AudioEventRTS m_repairSparks;
	AudioEventRTS m_enterCloseCombat;
	AudioEventRTS m_exitCloseCombat;
	AudioEventRTS m_incomingChatNotification;
	AudioEventRTS m_enabledHotKeyPressed;
	AudioEventRTS m_disabledHotKeyPressed;
	AudioEventRTS m_lowLODShellMusic;

	MiscAudio();
};

// ??0MiscAudio@@QAE@XZ
MiscAudio::MiscAudio()
	: m_radarHarvesterUnderAttackSound(AsciiString::TheEmptyString, 0)
	, m_radarStructureUnderAttackSound(AsciiString::TheEmptyString, 0)
	, m_radarInfiltrationSound(AsciiString::TheEmptyString, 0)
	, m_radarOnlineSound(AsciiString::TheEmptyString, 0)
	, m_radarOfflineSound(AsciiString::TheEmptyString, 0)
	, m_defectorTimerTickSound(AsciiString::TheEmptyString, 0)
	, m_defectorTimerDingSound(AsciiString::TheEmptyString, 0)
	, m_allCheerSound(AsciiString::TheEmptyString, 0)
	, m_battleCrySound(AsciiString::TheEmptyString, 0)
	, m_noCanDoSound(AsciiString::TheEmptyString, 0)
	, m_stealthDiscoveredSound(AsciiString::TheEmptyString, 0)
	, m_stealthNeutralizedSound(AsciiString::TheEmptyString, 0)
	, m_moneyDepositSound(AsciiString::TheEmptyString, 0)
	, m_moneyWithdrawSound(AsciiString::TheEmptyString, 0)
	, m_buildingDisabled(AsciiString::TheEmptyString, 0)
	, m_buildingReenabled(AsciiString::TheEmptyString, 0)
	, m_vehicleDisabled(AsciiString::TheEmptyString, 0)
	, m_vehicleReenabled(AsciiString::TheEmptyString, 0)
	, m_splatterVehiclePilotsBrain(AsciiString::TheEmptyString, 0)
	, m_crateHeal(AsciiString::TheEmptyString, 0)
	, m_crateShroud(AsciiString::TheEmptyString, 0)
	, m_crateSalvage(AsciiString::TheEmptyString, 0)
	, m_crateFreeUnit(AsciiString::TheEmptyString, 0)
	, m_crateMoney(AsciiString::TheEmptyString, 0)
	, m_unitPromoted(AsciiString::TheEmptyString, 0)
	, m_repairSparks(AsciiString::TheEmptyString, 0)
	, m_enterCloseCombat(AsciiString::TheEmptyString, 0)
	, m_exitCloseCombat(AsciiString::TheEmptyString, 0)
	, m_incomingChatNotification(AsciiString::TheEmptyString, 0)
	, m_enabledHotKeyPressed(AsciiString::TheEmptyString, 0)
	, m_disabledHotKeyPressed(AsciiString::TheEmptyString, 0)
	, m_lowLODShellMusic(AsciiString::TheEmptyString, 0)
{
}
