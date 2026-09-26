// cl: /DNDEBUG /MD /EHsc
// Retail 0x000CBFA0: Player::addRadar(Bool). Neighbours removeRadar@0xCC0B0,
// disableRadar@0xCC1C0, enableRadar@0xCC2C0 in Player.cpp. ZH twin at
// GeneralsMD Player.cpp:3164. AudioEventRTS is 0x70 as in Money_deposit.cpp.

typedef int Int;
typedef bool Bool;

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &that);
	~AudioEventRTS();
	void setPlayerIndex(Int playerNdx);

private:
	char m_bfme_body[0x70];
};

struct MiscAudio
{
	char m_bfme_head[0x150];
	AudioEventRTS m_radarOnlineSound;
};

class AudioManager
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual unsigned int addAudioEvent(const AudioEventRTS *event) = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void slot69() = 0;
	virtual void slot70() = 0;
	virtual void slot71() = 0;
	virtual void slot72() = 0;
	virtual const MiscAudio *getMiscAudio(void) const = 0;
};

extern AudioManager *TheAudio;

// Player::addRadar is already claimed at 0x000FB3F0 by a naked thunk of a
// different body. Keep Player as the base so okToPlayRadarEdgeSound mangles
// to the matched ILT; the method itself lands under this address-derived type.
class Player
{
public:
	Bool okToPlayRadarEdgeSound(void);
	Int getPlayerIndex(void) const { return m_playerIndex; }
	Bool hasRadar(void) const
	{
		if (m_radarDisabled && (m_disableProofRadarCount == 0))
			return false;
		return m_radarCount > 0;
	}

	char m_pad00[0x24];
	Int m_playerIndex;
	char m_pad28[0x30];
	Int m_radarCount;
	Int m_disableProofRadarCount;
	Bool m_radarDisabled;
};

class Rva000CBFA0Player : public Player
{
public:
	void addRadar(Bool disableProof);
};

void Rva000CBFA0Player::addRadar(Bool disableProof)
{
	Bool hadRadar = hasRadar();
	++m_radarCount;
	if (disableProof)
		++m_disableProofRadarCount;
	if (!hadRadar && hasRadar() && okToPlayRadarEdgeSound())
	{
		AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_radarOnlineSound;
		soundToPlay.setPlayerIndex(getPlayerIndex());
		TheAudio->addAudioEvent(&soundToPlay);
	}
}
