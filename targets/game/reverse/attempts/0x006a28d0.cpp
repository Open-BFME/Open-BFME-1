// ?xferAudioHandle@AudioManager@@UAEXPAVXfer@@PAI@Z
// partial score=0.918 date=2026-09-28
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System

// Open-BFME5: AudioManager::xferAudioHandle, retail 0x006A28D0, 502 bytes.
// The MilesAudioManager vtable at 0x0111C0C0 names this slot 82.  The three
// address-derived helper declarations below retain the retail call contracts
// without claiming identities that are not present in the ledger.

#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"

typedef unsigned int AudioHandle;
typedef unsigned char UnsignedByte;

#include "xfer.h"
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class AudioManagerMutex
{
public:
	__forceinline AudioManagerMutex(void *mutex)
	{
		m_held = 0;
		m_mutex = mutex;
		unsigned long status = WaitForSingleObject(m_mutex, 0xFFFFFFFFu);
		if (status != 0x102u)
			m_held = 1;
	}

	__forceinline ~AudioManagerMutex(void)
	{
		if (m_held)
		{
			ReleaseMutex(m_mutex);
			m_held = 0;
		}
	}

private:
	void *m_mutex;
	unsigned char m_held;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int extra);
	virtual ~AudioEventRTS();

	// These two fields are the only AudioEventRTS members this body observes.
	// Keep the intervening layout faithful to the proven 0x70-byte object while
	// leaving its ownership fields opaque to this caller.
	unsigned char m_pad004[8];
	unsigned int m_playingHandle;
	unsigned char m_pad010[0x45 - 0x10];
	unsigned char m_flag45;
	unsigned char m_pad046[0x70 - 0x46];
};

class Rva006AInfo
{
public:
	virtual ~Rva006AInfo();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
	char m_pad008[0x34 - 0x08];
	unsigned char m_flag34;
};

class AudioInfo006A28D0Ref {
public:
 AudioInfo006A28D0Ref() : ptr(0) {}
 __forceinline ~AudioInfo006A28D0Ref() { if (ptr) ptr->Release_Ref(); }
 Rva006AInfo *ptr;
};

class BfmeSeedTarget;

class BfmeSubAccept_0002C41C
{
public:
	void bfmeAccept(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0xC];
	void *m_bfmeField;
};

extern void j_00008549(void);
extern AsciiString TheBfmeCrateNameDefault;

#pragma comment(linker, "/alternatename:??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z=?j_00025306@@YAXXZ")
#pragma comment(linker, "/alternatename:??1AudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")

class MilesAudioManager { public: bool rva006A20D0(unsigned,void *,void *); };

class AudioManager
{
public:
#define AUDIO_SLOT(n) virtual void audioSlot##n();
	AUDIO_SLOT(00) AUDIO_SLOT(01) AUDIO_SLOT(02) AUDIO_SLOT(03)
	AUDIO_SLOT(04) AUDIO_SLOT(05) AUDIO_SLOT(06) AUDIO_SLOT(07)
	AUDIO_SLOT(08) AUDIO_SLOT(09) AUDIO_SLOT(10) AUDIO_SLOT(11)
	AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14) AUDIO_SLOT(15)
	AUDIO_SLOT(16) AUDIO_SLOT(17) AUDIO_SLOT(18) AUDIO_SLOT(19)
	AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22) AUDIO_SLOT(23)
	AUDIO_SLOT(24) AUDIO_SLOT(25) AUDIO_SLOT(26) AUDIO_SLOT(27)
	AUDIO_SLOT(28) AUDIO_SLOT(29) AUDIO_SLOT(30) AUDIO_SLOT(31)
	AUDIO_SLOT(32) AUDIO_SLOT(33) AUDIO_SLOT(34) AUDIO_SLOT(35)
	AUDIO_SLOT(36) AUDIO_SLOT(37) AUDIO_SLOT(38) AUDIO_SLOT(39)
	AUDIO_SLOT(40) AUDIO_SLOT(41) AUDIO_SLOT(42) AUDIO_SLOT(43)
	AUDIO_SLOT(44) AUDIO_SLOT(45) AUDIO_SLOT(46) AUDIO_SLOT(47)
	AUDIO_SLOT(48) AUDIO_SLOT(49) AUDIO_SLOT(50) AUDIO_SLOT(51)
	AUDIO_SLOT(52) AUDIO_SLOT(53) AUDIO_SLOT(54) AUDIO_SLOT(55)
	AUDIO_SLOT(56) AUDIO_SLOT(57) AUDIO_SLOT(58) AUDIO_SLOT(59)
	AUDIO_SLOT(60) AUDIO_SLOT(61) AUDIO_SLOT(62) AUDIO_SLOT(63)
	AUDIO_SLOT(64) AUDIO_SLOT(65) AUDIO_SLOT(66) AUDIO_SLOT(67)
	AUDIO_SLOT(68) AUDIO_SLOT(69) AUDIO_SLOT(70) AUDIO_SLOT(71)
	AUDIO_SLOT(72) AUDIO_SLOT(73) AUDIO_SLOT(74) AUDIO_SLOT(75)
	AUDIO_SLOT(76) AUDIO_SLOT(77) AUDIO_SLOT(78) AUDIO_SLOT(79)
	AUDIO_SLOT(80) AUDIO_SLOT(81)
#undef AUDIO_SLOT
	virtual void xferAudioHandle(Xfer *xfer, AudioHandle *handle);

private:
	char m_pad004[0x95c - 4];
	void *m_mutex;
};

void AudioManager::xferAudioHandle(Xfer *xfer, AudioHandle *handle)
{
	Xfer::Version version;
    version.data[0] = 1; version.data[1] = 1;
    *xfer == version;
	if (xfer->IsCRC())
		return;

	if (xfer->IsStoring())
	{
		AudioManagerMutex guard(m_mutex);
		bool accepted;
		AudioInfo006A28D0Ref info;
		AudioEventRTS *event;
		typedef bool (AudioManager::*Resolve)(AudioHandle, AudioEventRTS **, AudioInfo006A28D0Ref &);
        union { void (*address)(); Resolve method; } resolve;
        resolve.address = j_00008549;
        accepted = (this->*resolve.method)(*handle, &event, info);
        Rva006AInfo *infoValue = info.ptr;
        AudioEventRTS *eventValue = event;

		if (accepted)
		{
			if (eventValue == 0 || eventValue->m_flag45)
				accepted = false;
			if (infoValue != 0 && infoValue->m_flag34)
				accepted = false;
		}

		*xfer == accepted;
		if (accepted)
		{
			reinterpret_cast<BfmeSubAccept_0002C41C *>(eventValue)->bfmeAccept(
				reinterpret_cast<BfmeSeedTarget *>(xfer));
		}

	}
	else
	{
		AudioManagerMutex guard(m_mutex);
		bool hasEvent;
		*xfer == hasEvent;
		if (hasEvent)
		{
			AudioEventRTS event(TheBfmeCrateNameDefault, 0);
			reinterpret_cast<BfmeSubAccept_0002C41C *>(&event)->bfmeAccept(
				 reinterpret_cast<BfmeSeedTarget *>(xfer));
			*handle = event.m_playingHandle;
		}
		else
		{
			*handle = 1;
		}
	}
}
