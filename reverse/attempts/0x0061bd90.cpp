// ??1LivingWorldSound@@UAE@XZ
// partial score=0.93 date=2026-09-08
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *addend );

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void LoadPostProcess() = 0;
	virtual const char *GetSnapshotName() = 0;
	virtual void DoXfer(class Xfer &xfer) = 0;

};

class Rva00087750Counted
{
public:
	virtual ~Rva00087750Counted();

	void Release_Ref()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
	unsigned char m_padding[0x7c];
	unsigned int m_playingHandle;
	unsigned int getPlayingHandle() const
	{
		return m_playingHandle;
	}
};

class SoundEvent
{
public:
	Rva00087750Counted *m_sound;

	__forceinline ~SoundEvent()
	{
		if (m_sound != 0)
			m_sound->Release_Ref();
	}
};

class Rva005A00B0AudioClient
{
public:
	virtual void bfmeSlot00VUQ();
	virtual void bfmeSlot01VUQ();
	virtual void bfmeSlot02VUQ();
	virtual void bfmeSlot03VUQ();
	virtual void bfmeSlot04VUQ();
	virtual void bfmeSlot05VUQ();
	virtual void bfmeSlot06VUQ();
	virtual void bfmeSlot07VUQ();
	virtual void bfmeSlot08VUQ();
	virtual void bfmeSlot09VUQ();
	virtual void bfmeSlot10VUQ();
	virtual void bfmeSlot11VUQ();
	virtual void bfmeSlot12VUQ();
	virtual void bfmeSlot13VUQ();
	virtual void bfmeSlot14VUQ();
	virtual void bfmeSlot15VUQ();
	virtual void bfmeSlot16VUQ();
	virtual void bfmeSlot17VUQ();
	virtual void bfmeSlot18VUQ();
	virtual void removeAudioEvent(unsigned int handle);
	virtual void bfmeSlot20VUQ();
	virtual void bfmeSlot21VUQ();
	virtual void bfmeSlot22VUQ();
	virtual void bfmeSlot23VUQ();
	virtual void bfmeSlot24VUQ();
	virtual void bfmeSlot25VUQ();
	virtual void bfmeSlot26VUQ();
	virtual void startAudio(int one, int two, int three);
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

class LivingWorldSound : public Snapshot
{
public:
	virtual ~LivingWorldSound();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);

	AsciiString m_name;
	unsigned char m_position[0xc];
	SoundEvent m_sound;
	unsigned int m_flags;
	unsigned char m_zoomRegion[0x10];
	int m_playState;
	bool m_shouldFade;
	bool m_isPlaying;
	bool m_hasPlayed;
};

LivingWorldSound::~LivingWorldSound()
{
	if (TheAudioClientUpdate != 0 && static_cast<unsigned int>(m_playState) >= 5)
	{
		if (m_sound.m_sound != 0 && m_sound.m_sound->getPlayingHandle() == 0)
			TheAudioClientUpdate->startAudio(1, 1, 0);
		else
			TheAudioClientUpdate->removeAudioEvent(m_playState);

		m_playState = 1;
	}
}
