// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Money::deposit, retail 0x000C8730, 202 bytes.
//
// The reference's body as far as the sound goes -- take the deposit sound out
// of MiscAudio, stamp the owning player on it, play it only when asked, then
// add the money -- and the deposit sound sits at MiscAudio+0x540, the
// thirteenth 0x70-byte entry, two slots ahead of where the reference has it,
// exactly as the radar sounds in Player_radar.cpp are.
//
// Where the reference then reaches for the owner's academy stats, BFME instead
// adds the amount into a global, and only when the money being deposited
// belongs to the local player: the +0x0C of ThePlayerList is getLocalPlayer
// and its +0x24 the player index, the same offset Player_radar.cpp reads.
// The global at 0x012ED63C is not identified -- nothing here says more than
// that it has a running total at +8 -- so it is modelled under a descriptive
// name rather than a guessed one.

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
	char m_bfme_body[0x70];					// sizeof(AudioEventRTS)
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MiscAudio.h
struct MiscAudio
{
	char m_bfme_head[0x540];				// the sounds ahead of this one
	AudioEventRTS m_moneyDepositSound;			// this+0x540
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
	Int getPlayerIndex(void) const { return m_playerIndex; }

private:
	char m_slice_pad[0x24];					// retail this+0x00 .. +0x23, untouched
	Int m_playerIndex;					// this+0x24
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getLocalPlayer(void) { return m_local; }

private:
	char m_slice_pad[0x0C];					// retail this+0x00 .. +0x0B, untouched
	Player *m_local;					// this+0x0C
};

extern PlayerList *ThePlayerList;

// Unidentified global at 0x012ED63C: a running total at +8 that only the local
// player's deposits reach.
class BfmeDepositTally
{
public:
	UnsignedInt m_bfme_head;
	UnsignedInt m_bfme_pad;
	UnsignedInt m_total;					// this+0x08
};

extern BfmeDepositTally *TheBfmeDepositTally;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Money.h
class Money
{
public:
	void deposit(UnsignedInt amountToDeposit, Bool playSound = true);

private:
	char m_slice_pad[4];					// retail this+0x00, the snapshot vptr
	UnsignedInt m_money;					// this+0x04
	Int m_playerIndex;					// this+0x08
};

void Money::deposit(UnsignedInt amountToDeposit, Bool playSound)
{
	if (amountToDeposit == 0)
		return;

	AudioEventRTS event = TheAudio->getMiscAudio()->m_moneyDepositSound;
	event.setPlayerIndex(m_playerIndex);

	// Play a sound
	if (playSound)
		TheAudio->addAudioEvent(&event);

	m_money += amountToDeposit;

	if (TheBfmeDepositTally != 0 && ThePlayerList != 0)
	{
		Player *localPlayer = ThePlayerList->getLocalPlayer();
		if (localPlayer != 0 && localPlayer->getPlayerIndex() == m_playerIndex)
		{
			TheBfmeDepositTally->m_total += amountToDeposit;
		}
	}
}
