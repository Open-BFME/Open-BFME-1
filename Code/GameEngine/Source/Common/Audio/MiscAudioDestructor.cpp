// cl: /DNDEBUG /MD /EHsc
// Real MiscAudio destructor at retail RVA 0x006952F0.
//
// MiscAudioConstructor.cpp establishes the BFME-specific object layout: 32
// embedded AudioEventRTS values, each 0x70 bytes, at offsets 0x00..0xD90.
// Retail INI table RVA0x00C83310 independently names every field offset.
// The existing generated scalar-deleting wrapper0x00699F00/30 calls this
// full556B body, whose last ret at0x0069551B ends at0x0069551C.
// The members use the existing scalar AudioEventRTS destructor at 0x000B31F0.

class AudioEventRTS
{
public:
	~AudioEventRTS();

private:
	void *m_vptr;
	unsigned char m_bfmeData[0x6C];
};

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

	~MiscAudio();
};

typedef char AudioEventSize70[(sizeof(AudioEventRTS) == 0x70) ? 1 : -1];
typedef char MiscAudioSizeE00[(sizeof(MiscAudio) == 0xE00) ? 1 : -1];

// ??1MiscAudio@@QAE@XZ
MiscAudio::~MiscAudio()
{
}
