// ?parseAmbientAudioProperties_000B6030@@YAXPAVDict@@PBVThingTemplate@@PAVRva00087BD0@@PA_NPAVDynamicAudioEventInfoRef@@3@Z
// partial score=0.51 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

template <> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
template <> inline StringBase<char>::~StringBase() { releaseBuffer(); }

typedef long Long;
typedef int Int;
typedef bool Bool;
typedef float Real;

extern "C" __declspec(dllimport) Long __stdcall InterlockedDecrement(Long volatile *addend);

enum NameKeyType { NAMEKEY_INVALID = 0 };

class StaticNameKey
{
public:
	NameKeyType key() const;
private:
	NameKeyType m_key;
	const char *m_name;
};

extern const StaticNameKey TheKey_objectSoundAmbient;
extern const StaticNameKey TheKey_objectSoundAmbientCustomized;
extern const StaticNameKey TheKey_objectSoundAmbientEnabled;
extern const StaticNameKey TheKey_objectSoundAmbientLooping;
extern const StaticNameKey TheKey_objectSoundAmbientVolume;
extern const StaticNameKey TheKey_objectSoundAmbientMinVolume;
extern const StaticNameKey TheKey_objectSoundAmbientMinRange;
extern const StaticNameKey TheKey_objectSoundAmbientMaxRange;
extern const StaticNameKey TheKey_objectSoundAmbientPriority;

class Dict
{
public:
	Bool getBool(NameKeyType key, Bool *exists) const;
	Int getInt(NameKeyType key, Bool *exists) const;
	Real getReal(NameKeyType key, Bool *exists) const;
	AsciiString getAsciiString(NameKeyType key, Bool *exists) const;
private:
	void *m_data;
};

class AudioEventInfo
{
public:
	virtual ~AudioEventInfo();
	Bool isPermanentSound() const;
	Long m_refCount;
};

class DynamicAudioEventInfo : public AudioEventInfo
{
public:
	DynamicAudioEventInfo(const AudioEventInfo *baseInfo, Int extra);
	void overrideLoopFlag(Bool newLoopFlag);
	void overrideVolume(Real newVolume);
	void overrideMinVolume(Real newMinVolume);
	void overrideMinRange(Real newMinRange);
	void overrideMaxRange(Real newMaxRange);
	void overridePriority(Int newPriority);
private:
	char m_body[0xA4 - 8];
};

class AudioEventInfoRef
{
public:
	AudioEventInfoRef() : m_ptr(0) {}
	~AudioEventInfoRef();
	AudioEventInfoRef &operator=(const AudioEventInfoRef &other);
	AudioEventInfo *m_ptr;
};

// The caller's output slot: released inline on entry, assigned out of line.
class DynamicAudioEventInfoRef
{
public:
	void release()
	{
		if (m_ptr)
		{
			AudioEventInfo *p = m_ptr;
			if (InterlockedDecrement(&p->m_refCount) <= 0)
				delete p;
		}
		m_ptr = 0;
	}
	void assign(DynamicAudioEventInfo *info);
	DynamicAudioEventInfo *m_ptr;
};

class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();
	void *m_filenameToLoad;
	AudioEventInfoRef m_eventInfo;		///< +0x08
};

class ThingTemplate
{
public:
	const AudioEventRTS *getSound(Int index) const;
};

class Rva00087BD0
{
public:
	AudioEventRTS *get(int i);
};

class AudioManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
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
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual AudioEventInfoRef findAudioEventInfo(const AsciiString &eventName) const;
};

extern AudioManager *TheAudio;

void __cdecl parseAmbientAudioProperties_000B6030(Dict *properties, const ThingTemplate *tmpl,
	Rva00087BD0 *soundOwner, Bool *forceOff, DynamicAudioEventInfoRef *audioToModify, Bool *soundEnabled)
{
	*forceOff = false;
	audioToModify->release();
	*soundEnabled = false;

	if (TheAudio == 0 || properties == 0)
		return;

	Bool soundEnabledExists;
	*soundEnabled = properties->getBool(TheKey_objectSoundAmbientEnabled.key(), &soundEnabledExists);

	Bool exists;
	AsciiString valStr = properties->getAsciiString(TheKey_objectSoundAmbient.key(), &exists);
	if (exists)
	{
		if (valStr.isEmpty())
		{
			*forceOff = true;
			*soundEnabled = false;
			return;
		}

		AudioEventInfoRef baseInfo = TheAudio->findAudioEventInfo(valStr);
		if (baseInfo.m_ptr != 0)
			audioToModify->assign(new DynamicAudioEventInfo(baseInfo.m_ptr, 0));
	}

	if (!*forceOff)
	{
		Bool valBool = properties->getBool(TheKey_objectSoundAmbientCustomized.key(), &exists);
		if (exists && valBool)
		{
			if (audioToModify->m_ptr == 0)
			{
				AudioEventInfoRef baseInfo;
				if (tmpl == 0 && soundOwner == 0)
					return;
				const AudioEventRTS *sound = tmpl ? tmpl->getSound(0x57) : soundOwner->get(0x57);
				if (sound)
				{
					baseInfo = sound->m_eventInfo;
					if (baseInfo.m_ptr != 0)
						audioToModify->assign(new DynamicAudioEventInfo(baseInfo.m_ptr, 0));
				}
			}

			if (audioToModify->m_ptr != 0)
			{
				valBool = properties->getBool(TheKey_objectSoundAmbientLooping.key(), &exists);
				if (exists)
					audioToModify->m_ptr->overrideLoopFlag(valBool);

				Real valReal = properties->getReal(TheKey_objectSoundAmbientVolume.key(), &exists);
				if (exists)
					audioToModify->m_ptr->overrideVolume(valReal);

				valReal = properties->getReal(TheKey_objectSoundAmbientMinVolume.key(), &exists);
				if (exists)
					audioToModify->m_ptr->overrideMinVolume(valReal);

				valReal = properties->getReal(TheKey_objectSoundAmbientMinRange.key(), &exists);
				if (exists)
					audioToModify->m_ptr->overrideMinRange(valReal);

				valReal = properties->getReal(TheKey_objectSoundAmbientMaxRange.key(), &exists);
				if (exists)
					audioToModify->m_ptr->overrideMaxRange(valReal);

				Int valInt = properties->getInt(TheKey_objectSoundAmbientPriority.key(), &exists);
				if (exists)
					audioToModify->m_ptr->overridePriority(valInt);
			}
		}
	}

	if (!soundEnabledExists)
	{
		if (audioToModify->m_ptr != 0)
		{
			*soundEnabled = audioToModify->m_ptr->isPermanentSound();
		}
		else
		{
			AudioEventInfoRef baseInfo;
			const AudioEventRTS *sound = !tmpl ? (soundOwner ? soundOwner->get(0x57) : 0) : tmpl->getSound(0x57);
			if (sound)
				baseInfo = sound->m_eventInfo;
			if (baseInfo.m_ptr != 0)
				*soundEnabled = baseInfo.m_ptr->isPermanentSound();
			else
				*soundEnabled = true;
		}
	}
}
