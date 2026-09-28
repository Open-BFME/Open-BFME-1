// ?d_00417710@@YAXXZ
// partial score=0.953 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Drawable::startAmbientSound(BodyDamageType, Bool), retail 0x00417710, 681 bytes.
//
// Identity. Zero Hour's Drawable::startAmbientSound(dt, tod, onlyIfPermanent)
// is this body's twin statement by statement: an inlined stopAmbientSound()
// (both sound slots, TheAudio slot +0x4C on the playing handle), "if no
// DynamicAudioEventRTS yet, make one", setEventName(info->m_audioName),
// setAudioEventInfo(info), setDrawableID(getID()) and
// setPlayingHandle(TheAudio->addAudioEvent(&m_event)), all behind
// `!onlyIfPermanent || info->isPermanentSound()`. BFME drops the time of day
// and keeps TWO ambient slots (+0x144, +0x148), each fed from its own
// AudioEventInfoRef getter. The callers close the chain:
//   - enableAmbientSound's twin at 0x00417CB0 tail-jumps (ILT 0x000294B5,
//     pinned ?startAmbientSound@Drawable@@AAEX_N@Z) to 0x00417A70, which is
//     ZH startAmbientSound(Bool): both enabled flags, stopAmbientSound()
//     (0x00411BE0, the same two removeAudioEvent calls inlined here), the
//     object's damage state, then this body through ILT 0x0002CB79;
//   - Drawable::setCustomSoundAmbientInfo (0x0041AD20) inlines the same
//     startAmbientSound(Bool) and calls this body with onlyIfPermanent 0.
// Layout witnesses: +0x100 m_id (Drawable::setID, getID), +0x144/+0x148 the
// ambient slots (setID, setCustomSoundAmbientInfo), DynamicAudioEventRTS
// (0x74 bytes, vftable 0x01082DE0, m_event at +4 through the two-argument
// AudioEventRTS constructor) as INI::parseDynamicAudioEventRTS builds it.
//
// The two getters (0x00417430: custom info at +0x10C unless rubble; 0x004175F0:
// the template's sound for the damage state with ZH's pristine fallback) carry
// address-derived names: their own identities are not recovered.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *value);

#include "ascii_string.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt AudioHandle;

enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE
};

enum ObjectID { INVALID_ID = 0 };
enum DrawableID { INVALID_DRAWABLE_ID = 0 };

// AsciiString::TheEmptyString at 0x01336E50.
extern const AsciiString Rva01336E50EmptyString;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventInfo.h
// BFME makes it ref counted (+4) with a virtual deleting destructor; only the
// fields this body reads are spelled out.
class AudioEventInfo
{
public:
	virtual ~AudioEventInfo();

	void releaseRef()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	Bool isPermanentSound() const
	{
		return m_soundType == 0 || m_soundType == 3 || (m_control & 1);
	}

	long m_refCount;				// +0x04
	AsciiString m_audioName;			// +0x08
	unsigned char m_pad0c[0x3c - 0x0c];
	UnsignedInt m_control;				// +0x3C
	unsigned char m_pad40[0x84 - 0x40];
	UnsignedInt m_soundType;			// +0x84
};

class AudioEventInfoRef
{
public:
	~AudioEventInfoRef()
	{
		if (m_info)
			m_info->releaseRef();
	}

	AudioEventInfo *operator->() const { return m_info; }

	AudioEventInfo *m_info;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, ObjectID ownerID);
	void setEventName(AsciiString name);
	void setDrawableID(DrawableID drawID);
	void setPlayingHandle(AudioHandle handle);

	// Retail 0x000B3FA0 (ledgered as Rva000B3FA0Owner::bfmeSet) through ILT
	// 0x0000B4E7: sets m_eventInfo at +0x08 when the info's name matches.
	void setAudioEventInfo(const AudioEventInfoRef &info) const;

private:
	void *m_vtbl;
	unsigned char m_body[0x70 - 4];
};

class DynamicAudioEventRTS
{
public:
	DynamicAudioEventRTS() : m_event(Rva01336E50EmptyString, INVALID_ID) { }
	virtual ~DynamicAudioEventRTS();

	AudioEventRTS m_event;
	AudioHandle getPlayingHandle() const { return *(const AudioHandle *)((const char *)&m_event + 0x0c); }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40();
	virtual AudioHandle addAudioEvent(const AudioEventRTS *eventToAdd);	// +0x44
	virtual void v48();
	virtual void removeAudioEvent(AudioHandle audioEvent);			// +0x4C
};

struct Rva005A00B0AudioClient;
extern Rva005A00B0AudioClient *TheAudioClientUpdate;	// TheAudio, 0x012ED668
#define TheAudio ((AudioManager *)TheAudioClientUpdate)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
protected:
	// protected in ZH's Drawable.h, as the (dt, tod, onlyIfPermanent) overload
	void startAmbientSound(BodyDamageType dt, Bool onlyIfPermanent);

public:

	void stopAmbientSound()
	{
		if (m_ambientSound)
			TheAudio->removeAudioEvent(m_ambientSound->getPlayingHandle());
		if (m_ambientSoundAlternate)
			TheAudio->removeAudioEvent(m_ambientSoundAlternate->getPlayingHandle());
	}

	DrawableID getID() const { return m_id; }

	AudioEventInfoRef rva00417430AmbientInfo(BodyDamageType dt);	// ILT 0x0001B77F
	AudioEventInfoRef rva004175F0AmbientInfo(BodyDamageType dt);	// ILT 0x000089FE

private:
	unsigned char m_pad000[0x100];
	DrawableID m_id;						// +0x100
	unsigned char m_pad104[0x144 - 0x104];
	DynamicAudioEventRTS *m_ambientSound;				// +0x144
	DynamicAudioEventRTS *m_ambientSoundAlternate;			// +0x148
};

// ?startAmbientSound@Drawable@@IAEXW4BodyDamageType@@_N@Z
void Drawable::startAmbientSound(BodyDamageType dt, Bool onlyIfPermanent)
{
	stopAmbientSound();

	AudioEventInfoRef info = rva00417430AmbientInfo(dt);
	AudioEventInfoRef alternateInfo = rva004175F0AmbientInfo(dt);

	if (info.m_info)
	{
		if (!onlyIfPermanent || info->isPermanentSound())
		{
			if (m_ambientSound == 0)
				m_ambientSound = new DynamicAudioEventRTS;

			m_ambientSound->m_event.setEventName(info->m_audioName);
			m_ambientSound->m_event.setAudioEventInfo(info);
			m_ambientSound->m_event.setDrawableID(getID());
			m_ambientSound->m_event.setPlayingHandle(TheAudio->addAudioEvent(&m_ambientSound->m_event));
		}
	}

	if (alternateInfo.m_info)
	{
		if (!onlyIfPermanent || alternateInfo->isPermanentSound())
		{
			if (m_ambientSoundAlternate == 0)
				m_ambientSoundAlternate = new DynamicAudioEventRTS;

			m_ambientSoundAlternate->m_event.setEventName(alternateInfo->m_audioName);
			m_ambientSoundAlternate->m_event.setAudioEventInfo(alternateInfo);
			m_ambientSoundAlternate->m_event.setDrawableID(getID());
			m_ambientSoundAlternate->m_event.setPlayingHandle(TheAudio->addAudioEvent(&m_ambientSoundAlternate->m_event));
		}
	}
}
