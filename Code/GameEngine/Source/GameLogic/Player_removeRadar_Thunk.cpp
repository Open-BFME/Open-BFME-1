// cl: /DNDEBUG /MD /EHsc
// readable body of ?removeRadar@Player@@QAEX_N@Z: Code/GameEngine/Source/Common/RTS/Player.cpp

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &other);
	virtual ~AudioEventRTS();
	void setPlayerIndex(int playerIndex);

private:
	// Retail's audio event is a 0x70-byte polymorphic value type.
	char m_retailData[0x6c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MiscAudio.h
class MiscAudio
{
public:
	char m_retailPrefix[0x1c0];
	AudioEventRTS m_radarOfflineSound;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
#define AUDIO_SLOT(number) virtual void vfn##number();
	AUDIO_SLOT(00) AUDIO_SLOT(01) AUDIO_SLOT(02) AUDIO_SLOT(03)
	AUDIO_SLOT(04) AUDIO_SLOT(05) AUDIO_SLOT(06) AUDIO_SLOT(07)
	AUDIO_SLOT(08) AUDIO_SLOT(09) AUDIO_SLOT(10) AUDIO_SLOT(11)
	AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14) AUDIO_SLOT(15)
	AUDIO_SLOT(16)
	virtual void addAudioEvent(AudioEventRTS *event);
	AUDIO_SLOT(18) AUDIO_SLOT(19) AUDIO_SLOT(20) AUDIO_SLOT(21)
	AUDIO_SLOT(22) AUDIO_SLOT(23) AUDIO_SLOT(24) AUDIO_SLOT(25)
	AUDIO_SLOT(26) AUDIO_SLOT(27) AUDIO_SLOT(28) AUDIO_SLOT(29)
	AUDIO_SLOT(30) AUDIO_SLOT(31) AUDIO_SLOT(32) AUDIO_SLOT(33)
	AUDIO_SLOT(34) AUDIO_SLOT(35) AUDIO_SLOT(36) AUDIO_SLOT(37)
	AUDIO_SLOT(38) AUDIO_SLOT(39) AUDIO_SLOT(40) AUDIO_SLOT(41)
	AUDIO_SLOT(42) AUDIO_SLOT(43) AUDIO_SLOT(44) AUDIO_SLOT(45)
	AUDIO_SLOT(46) AUDIO_SLOT(47) AUDIO_SLOT(48) AUDIO_SLOT(49)
	AUDIO_SLOT(50) AUDIO_SLOT(51) AUDIO_SLOT(52) AUDIO_SLOT(53)
	AUDIO_SLOT(54) AUDIO_SLOT(55) AUDIO_SLOT(56) AUDIO_SLOT(57)
	AUDIO_SLOT(58) AUDIO_SLOT(59) AUDIO_SLOT(60) AUDIO_SLOT(61)
	AUDIO_SLOT(62) AUDIO_SLOT(63) AUDIO_SLOT(64) AUDIO_SLOT(65)
	AUDIO_SLOT(66) AUDIO_SLOT(67) AUDIO_SLOT(68) AUDIO_SLOT(69)
	AUDIO_SLOT(70) AUDIO_SLOT(71) AUDIO_SLOT(72)
	virtual MiscAudio *getMiscAudio();
#undef AUDIO_SLOT
};

extern AudioManager *TheAudio;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void removeRadar(Bool disableProof);
	Bool okToPlayRadarEdgeSound();

private:
	int getPlayerIndex() const
	{
		return m_playerIndex;
	}

	Bool hasRadar() const
	{
		if (m_radarDisabled && m_disableProofRadarCount == 0)
			return false;
		return m_radarCount > 0;
	}

	char m_retailPrefix[0x24];
	int m_playerIndex;
	char m_beforeRadar[0x30];
	int m_radarCount;
	int m_disableProofRadarCount;
	Bool m_radarDisabled;
};

void Player::removeRadar(Bool disableProof)
{
	Bool hadRadar = hasRadar();

	--m_radarCount;
	if (disableProof)
		--m_disableProofRadarCount;

	if (hadRadar && !hasRadar() && okToPlayRadarEdgeSound())
	{
		AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_radarOfflineSound;
		soundToPlay.setPlayerIndex(getPlayerIndex());
		TheAudio->addAudioEvent(&soundToPlay);
	}
}
