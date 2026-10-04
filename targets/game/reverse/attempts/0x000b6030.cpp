// ?parseAmbientAudioProperties_000B6030@@YAXPAVDict@@PBVRva00416FA0Receiver@@PAVRva00087BD0@@PA_NPAVRva000B6030DynamicInfoRef@@3@Z
// partial score=0.9662 date=2026-10-04
// Banked near-match: 976/976 bytes, 33 differing non-relocation bytes.
// This is experimental evidence, NOT a matched production implementation.
// RVA000B6030 is a cdecl parser with Dict, drawable receiver, template receiver,
// force-off output, dynamic-info-reference output, and enabled output.
// The receiver roles are independently established by the original caller at
// RVA001D0610; older ThingTemplate-labelled RVA00416FA0 rows are NOT identity proof.
// Physical audio views below avoid dereferencing the incompatible ZH layouts.
// Reuse native DynamicAudioEventInfo/Dict/StaticNameKey/AsciiString declarations.
// Remaining provider identity work and final branch mismatch are documented in
// targets/game/reverse/identity_evidence/0x000b6030-ambient-parser-bank.md.
// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib

#include "Common/DynamicAudioEventInfo.h"
#include "Common/Dict.h"

template <> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }

extern const StaticNameKey TheKey_objectSoundAmbient;
extern const StaticNameKey TheKey_objectSoundAmbientCustomized;
extern const StaticNameKey TheKey_objectSoundAmbientEnabled;
extern const StaticNameKey TheKey_objectSoundAmbientLooping;
extern const StaticNameKey TheKey_objectSoundAmbientMinVolume;
extern const StaticNameKey TheKey_objectSoundAmbientVolume;
extern const StaticNameKey TheKey_objectSoundAmbientMinRange;
extern const StaticNameKey TheKey_objectSoundAmbientMaxRange;
extern const StaticNameKey TheKey_objectSoundAmbientPriority;

class Rva000B6030Info
{
public:
	virtual ~Rva000B6030Info();
	Bool isPermanentSound() const;
	long m_refCount;
};

class Rva000B6030DynamicInfo : public Rva000B6030Info
{
public:
	Rva000B6030DynamicInfo(const Rva000B6030Info *baseInfo, Int extra);
	void overrideLoopFlag(Bool value) { reinterpret_cast<DynamicAudioEventInfo *>(this)->overrideLoopFlag(value); }
	void overrideVolume(Real value) { reinterpret_cast<DynamicAudioEventInfo *>(this)->overrideVolume(value); }
	void overrideMinVolume(Real value) { reinterpret_cast<DynamicAudioEventInfo *>(this)->overrideMinVolume(value); }
	void overrideMinRange(Real value) { reinterpret_cast<DynamicAudioEventInfo *>(this)->overrideMinRange(value); }
	void overrideMaxRange(Real value) { reinterpret_cast<DynamicAudioEventInfo *>(this)->overrideMaxRange(value); }
	void overridePriority(AudioPriority value) { reinterpret_cast<DynamicAudioEventInfo *>(this)->overridePriority(value); }
private:
	char m_body[0xA4 - 8];
};

class Rva000B6030InfoRef
{
public:
	Rva000B6030InfoRef() : m_ptr(0) {}
	~Rva000B6030InfoRef();
	Rva000B6030InfoRef &operator=(const Rva000B6030InfoRef &other);
	Rva000B6030Info *m_ptr;
};

// The caller's output slot: released inline on entry, assigned out of line.
class Rva000B6030DynamicInfoRef
{
public:
	void release()
	{
		if (m_ptr)
		{
			Rva000B6030Info *p = m_ptr;
			if (InterlockedDecrement(&p->m_refCount) <= 0)
				delete p;
			m_ptr = 0;
		}
	}
	void assign(Rva000B6030DynamicInfo *info);
	Rva000B6030DynamicInfo *m_ptr;
};

class Rva000B6030Event
{
public:
	virtual ~Rva000B6030Event();
	void *m_filenameToLoad;
	Rva000B6030InfoRef m_eventInfo;		///< +0x08
};

class Rva00416FA0Receiver
{
public:
	const Rva000B6030Event *getSound(Int index) const;
};

class Rva00087BD0
{
public:
	Rva000B6030Event *get(int i);
};

class Rva000B6030AudioManager
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
	virtual Rva000B6030InfoRef findRva000B6030Info(const AsciiString &eventName) const;
};

class AudioManager;
extern AudioManager *TheAudio;


__declspec(noinline) Rva000B6030InfoRef::~Rva000B6030InfoRef()
{
    if (m_ptr) {
        Rva000B6030Info *p = m_ptr;
        if (InterlockedDecrement(&p->m_refCount) <= 0) delete p;
    }
}
__declspec(noinline) Rva000B6030InfoRef &Rva000B6030InfoRef::operator=(const Rva000B6030InfoRef &other)
{
    if (this != &other) {
        if (other.m_ptr) InterlockedIncrement(&other.m_ptr->m_refCount);
        if (m_ptr) {
            Rva000B6030Info *p = m_ptr;
            if (InterlockedDecrement(&p->m_refCount) <= 0) delete p;
        }
        m_ptr = other.m_ptr;
    }
    return *this;
}
void __cdecl parseAmbientAudioProperties_000B6030(Dict *properties, const Rva00416FA0Receiver *drawableReceiver,
	Rva00087BD0 *templateReceiver, Bool *forceOff, Rva000B6030DynamicInfoRef *audioToModify, Bool *soundEnabled)
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

		Rva000B6030InfoRef baseInfo = reinterpret_cast<Rva000B6030AudioManager *>(TheAudio)->findRva000B6030Info(valStr);
		if (baseInfo.m_ptr != 0)
			audioToModify->assign(new Rva000B6030DynamicInfo(baseInfo.m_ptr, 0));
	}

	if (!*forceOff)
	{
		Bool valBool = properties->getBool(TheKey_objectSoundAmbientCustomized.key(), &exists);
		if (exists && valBool)
		{
			if (audioToModify->m_ptr == 0)
			{
				Rva000B6030InfoRef baseInfo;
				if (drawableReceiver == 0 && templateReceiver == 0)
					return;
				const Rva000B6030Event *sound = drawableReceiver ? drawableReceiver->getSound(0x57) : templateReceiver->get(0x57);
				if (sound)
				{
					baseInfo = sound->m_eventInfo;
					if (baseInfo.m_ptr != 0)
						audioToModify->assign(new Rva000B6030DynamicInfo(baseInfo.m_ptr, 0));
				}
			}

			if (audioToModify->m_ptr != 0)
			{
				valBool = properties->getBool(TheKey_objectSoundAmbientLooping.key(), &exists);
				if (exists)
					audioToModify->m_ptr->overrideLoopFlag(valBool);

				Real valReal = properties->getReal(TheKey_objectSoundAmbientMinVolume.key(), &exists);
				if (exists)
					audioToModify->m_ptr->overrideMinVolume(valReal);

				valReal = properties->getReal(TheKey_objectSoundAmbientVolume.key(), &exists);
				if (exists)
					audioToModify->m_ptr->overrideVolume(valReal);

				valReal = properties->getReal(TheKey_objectSoundAmbientMinRange.key(), &exists);
				if (exists)
					audioToModify->m_ptr->overrideMinRange(valReal);

				valReal = properties->getReal(TheKey_objectSoundAmbientMaxRange.key(), &exists);
				if (exists)
					audioToModify->m_ptr->overrideMaxRange(valReal);

				Int valInt = properties->getInt(TheKey_objectSoundAmbientPriority.key(), &exists);
				if (exists)
					audioToModify->m_ptr->overridePriority((AudioPriority)valInt);
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
			Rva000B6030InfoRef baseInfo;
			const Rva000B6030Event *sound = !drawableReceiver ? (templateReceiver ? templateReceiver->get(0x57) : 0) : drawableReceiver->getSound(0x57);
			if (sound)
				baseInfo = sound->m_eventInfo;
			if (baseInfo.m_ptr != 0)
				*soundEnabled = baseInfo.m_ptr->isPermanentSound();
			else
				*soundEnabled = true;
		}
	}
}
