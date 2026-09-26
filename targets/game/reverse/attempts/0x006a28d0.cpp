// ?d_006a28d0@@YAXXZ
// partial score=0.48 date=2026-09-17
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline

// Open-BFME5: AudioManager::xferAudioHandle, retail 0x006A28D0, 502 bytes.
// The MilesAudioManager vtable at 0x0111C0C0 names this slot 82.  The three
// address-derived helper declarations below retain the retail call contracts
// without claiming identities that are not present in the ledger.

#define _STLP_NO_EXCEPTIONS 1
#include "StringInline.h"

typedef unsigned int AudioHandle;
typedef unsigned char UnsignedByte;

struct XferVersion
{
	XferVersion(UnsignedByte version, UnsignedByte currentVersion) :
		m_version(version), m_currentVersion(currentVersion)
	{
	}

	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion &version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(bool &value);
};

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
		if (WaitForSingleObject(m_mutex, 0xFFFFFFFFu) != 0x102u)
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
	XferVersion version(1, 1);
	xfer->xferVersion(version);
	if (xfer->IsCRC())
		return;

	if (xfer->IsStoring())
	{
		AudioManagerMutex guard(m_mutex);
		bool accepted;
		register Rva006AInfo *info = 0;
		register AudioEventRTS *event;
		typedef bool (AudioManager::*Resolve)(AudioHandle, AudioEventRTS **,
			Rva006AInfo **);
		union ResolveBits
		{
			void (*freeFunction)(void);
			Resolve memberFunction;
		} resolve;
		resolve.freeFunction = j_00008549;
		accepted = (this->*resolve.memberFunction)(*handle, &event, &info);

		if (accepted)
		{
			if (event != 0 && event->m_flag45)
				accepted = false;
			if (info != 0 && info->m_flag34)
				accepted = false;
		}

		xfer->xferBool(accepted);
		if (accepted)
		{
			reinterpret_cast<BfmeSubAccept_0002C41C *>(event)->bfmeAccept(
				reinterpret_cast<BfmeSeedTarget *>(xfer));
		}
		if (info != 0)
			info->Release_Ref();
	}
	else
	{
		AudioManagerMutex guard(m_mutex);
		bool hasEvent = false;
		xfer->xferBool(hasEvent);
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
