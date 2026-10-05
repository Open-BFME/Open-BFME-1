// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Drawable::startAmbientSound(BodyDamageType, Bool), retail 0x00417710, 681 bytes.
//
// Identity. Zero Hour's Drawable::startAmbientSound(dt, tod, onlyIfPermanent)
// is the source twin, with BFME-specific sound selection: stopAmbientSound()
// (both sound slots, TheAudio slot +0x4C on the playing handle), "if no
// DynamicAudioEventRTS yet, make one", setEventName(info->m_audioName),
// setAudioEventInfo(info), setDrawableID(getID()) and
// setPlayingHandle(TheAudio->addAudioEvent(&m_event)), all behind
// `!onlyIfPermanent || info->isPermanentSound()`. BFME drops the time of day
// and keeps TWO ambient slots (+0x144, +0x148), each fed from its own
// Rva00417710InfoRef getter. The callers close the chain:
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

enum DrawableID { INVALID_DRAWABLE_ID = 0 };


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

class BfmeHostQR { public: void Rva00417430AudioSelector(void *, int); };
class Rva000B3FA0Thing;
// ABI prefix view of the matched setter owner; the base expresses the zero-offset
// call conversion only, not recovered source inheritance. The called constructor
// owns initialization of all 0x70 bytes; this view adds no lifetime operations.
class Rva000B3FA0Owner { public: void bfmeSet(Rva000B3FA0Thing **); unsigned char prefix[0x18]; };

class Rva00417710InfoRef
{
public:
	Rva00417710InfoRef(BfmeHostQR *owner, BodyDamageType dt) { owner->Rva00417430AudioSelector(this, dt); }
	~Rva00417710InfoRef()
	{
		if (m_info)
			m_info->releaseRef();
	}

	AudioEventInfo *operator->() const { return m_info; }

	AudioEventInfo *m_info;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS : public Rva000B3FA0Owner
{
public:
	AudioEventRTS(const AsciiString &eventName, int timeOfDay);
	void setEventName(AsciiString name);
	void setDrawableID(DrawableID drawID);
	void setPlayingHandle(AudioHandle handle);


private:
	unsigned char m_body[0x70 - 0x18];
};

class DynamicAudioEventRTS
{
public:
	DynamicAudioEventRTS() : m_event(AsciiString::TheEmptyString, 0) { }
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

extern AudioManager *TheAudio;

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

	
	// 0x004175F0 writes its owning pointer through the first stack argument,
	// increments pointee+4, returns that argument in EAX, and ends RET8.
	// The caller destroys the returned holder. Its original type is unproven.
	Rva00417710InfoRef rva004175F0AmbientInfo(BodyDamageType dt); // ILT 0x000089FE

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

	Rva00417710InfoRef info((BfmeHostQR *)this, dt);
	Rva00417710InfoRef alternateInfo = rva004175F0AmbientInfo(dt);

	if (info.m_info)
	{
		if (!onlyIfPermanent || info->isPermanentSound())
		{
			if (m_ambientSound == 0)
				m_ambientSound = new DynamicAudioEventRTS;

			m_ambientSound->m_event.setEventName(info->m_audioName);
			m_ambientSound->m_event.bfmeSet((Rva000B3FA0Thing **)&info);
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
			m_ambientSoundAlternate->m_event.bfmeSet((Rva000B3FA0Thing **)&alternateInfo);
			m_ambientSoundAlternate->m_event.setDrawableID(getID());
			AudioHandle alternateHandle = TheAudio->addAudioEvent(&m_ambientSoundAlternate->m_event);
			m_ambientSoundAlternate->m_event.setPlayingHandle(alternateHandle);
		}
	}
}
