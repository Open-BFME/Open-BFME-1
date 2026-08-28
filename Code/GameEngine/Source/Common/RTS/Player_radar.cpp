// cl: /DNDEBUG /MD /EHsc
// readable body of ?disableRadar@Player@@QAEXXZ: Code/GameEngine/Source/Common/RTS/Player.cpp
// readable body of ?enableRadar@Player@@QAEXXZ: Code/GameEngine/Source/Common/RTS/Player.cpp
// Open-BFME: the two halves of the player's radar switch,
//
//   0x000CC1C0  disableRadar  193 bytes
//   0x000CC2C0  enableRadar   186 bytes
//
// both the reference's bodies unchanged, down to hasRadar being inlined at
// each of the four places they ask it -- `if (m_radarDisabled &&
// m_disableProofRadarCount == 0) return FALSE; return m_radarCount > 0;`,
// which is the +0x60 byte, the +0x5C count and the +0x58 count in that order.
// The flag store sits between the two queries in both bodies, which is what
// makes the second one fold: the compiler knows what it just wrote.
//
// The MiscAudio slot each one copies is the interesting difference. An
// AudioEventRTS is 0x70 bytes -- the frame allocates exactly one -- and the
// online sound is the fourth of them at +0x150 with the offline sound the
// fifth at +0x1C0, where the reference has them sixth and seventh. Two entries
// ahead of them are gone in BFME, and Money::deposit's own MiscAudio offset is
// short by the same two, so it is the list that shrank rather than these
// members that moved. Which two is not something these bodies show, so
// everything before the online sound stays an opaque block.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &that);		// ILT 0x00047B27
	~AudioEventRTS();					// ILT 0x00026F35

	void setPlayerIndex(Int playerNdx);			// ILT 0x0003AC88

private:
	char m_bfme_body[0x70];					// sizeof(AudioEventRTS), the frame's whole local block
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MiscAudio.h
struct MiscAudio
{
	char m_bfme_head[0x150];				// the sounds ahead of these two
	AudioEventRTS m_radarOnlineSound;			// this+0x150
	AudioEventRTS m_radarOfflineSound;			// this+0x1C0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
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
	virtual UnsignedInt addAudioEvent(const AudioEventRTS *event) = 0;	// slot 17, vtable+0x44
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
	virtual const MiscAudio *getMiscAudio(void) const = 0;			// slot 73, vtable+0x124
};

extern AudioManager *TheAudio;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void disableRadar();
	void enableRadar();

	Bool hasRadar(void) const
	{
		if( m_radarDisabled && (m_disableProofRadarCount == 0) )
			return false;

		return m_radarCount > 0;
	}

	Bool okToPlayRadarEdgeSound(void);			// ILT 0x000141F0

	Int getPlayerIndex(void) const { return m_playerIndex; }

private:
	char m_slice_padA[0x24];				// retail this+0x00 .. +0x23, untouched
	Int m_playerIndex;					// this+0x24
	char m_slice_padB[0x58 - 0x28];				// this+0x28 .. +0x57, untouched
	Int m_radarCount;					// this+0x58
	Int m_disableProofRadarCount;				// this+0x5C
	Bool m_radarDisabled;					// this+0x60
};

void Player::disableRadar()
{
	Bool hadRadar = hasRadar();
	m_radarDisabled = true;

	if( hadRadar
		&& !hasRadar() && okToPlayRadarEdgeSound() )
	{
		// This player just lost radar, so play the "You lost Radar!" sound
		AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_radarOfflineSound;
		soundToPlay.setPlayerIndex(getPlayerIndex());
		TheAudio->addAudioEvent(&soundToPlay);
	}
}

void Player::enableRadar()
{
	Bool hadRadar = hasRadar();
	m_radarDisabled = false;

	if( !hadRadar && hasRadar() && okToPlayRadarEdgeSound() )
	{
		// This player just got radar, so play the "You have Radar!" sound
		AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_radarOnlineSound;
		soundToPlay.setPlayerIndex(getPlayerIndex());
		TheAudio->addAudioEvent(&soundToPlay);
	}
}
