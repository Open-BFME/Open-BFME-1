// ?endPreparation@SpecialAbilityUpdate@@QAEXXZ
// partial score=0.98 date=2026-09-04
// ?endPreparation@SpecialAbilityUpdate@@QAEXXZ
// partial score=0.98 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: SpecialAbilityUpdate::endPreparation, retail 0x002A7670.
// The BFME build uses the ten-word model-condition view for the two masks in
// this method.  The special-power switch is kept after the flag update, as in
// the retail body; its three cases all share the special-object cleanup call.

#define _STLP_NO_EXCEPTIONS 1
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef unsigned int AudioHandle;

enum SpecialPowerType { };

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

template<int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };

	BitFlags() { }
	BitFlags(BogusInitType, int bit) { m_bits.set(bit); }
	void set(int bit) { m_bits.set(bit); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;
typedef BitFlags<320> ModelConditionFlags;

class Overridable;
class SpecialAbilityUpdate;

typedef void (__fastcall *SpecialAbilityCleanupCall)(SpecialAbilityUpdate *);

extern void j_000434c3();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setStatus(const ObjectStatusMaskType &, Bool set = true);
	void clearAndSetModelConditionFlags(const ModelConditionFlags &clear,
		const ModelConditionFlags &set);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();

	AudioHandle getPlayingHandle() const
	{
		return *reinterpret_cast<const AudioHandle *>(
			reinterpret_cast<const unsigned char *>(this) + 0x0c);
	}

private:
	unsigned char m_data[0x6c];
};

class ClientSubsystem
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void removeAudioEvent(AudioHandle event);
};

extern ClientSubsystem *TheAudioClientUpdate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	Overridable *friend_getFinalOverride();
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	SpecialPowerType getSpecialPowerType() const { return m_specialPowerType; }

	public:
	unsigned char m_unmodelled_08[0x0c];
	volatile SpecialPowerType m_specialPowerType;
};

static __forceinline int readSpecialPowerType(
	const SpecialPowerTemplate *specialPowerTemplate)
{
	return (int)specialPowerTemplate->m_specialPowerType;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[0x1d8];
	const SpecialPowerTemplate *m_specialPowerTemplate;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate
{
public:
	void endPreparation();
	Object *getObject() const { return m_object; }

private:
	void *m_vtable;
	SpecialAbilityUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled_00c[0x28];
	AudioEventRTS m_prepSoundLoop;
};

// ?endPreparation@SpecialAbilityUpdate@@QAEXXZ
void SpecialAbilityUpdate::endPreparation()
{
	getObject()->setStatus(
		ObjectStatusMaskType(ObjectStatusMaskType::kInit, 24), false);
	TheAudioClientUpdate->removeAudioEvent(m_prepSoundLoop.getPlayingHandle());

	ModelConditionFlags clear(ModelConditionFlags::kInit, 94);
	ModelConditionFlags set;
	getObject()->clearAndSetModelConditionFlags(clear, set);

	const SpecialPowerTemplate *specialPowerTemplate =
		m_moduleData->m_specialPowerTemplate;
	Overridable *overrideTemplate = specialPowerTemplate->m_nextOverride;
	if (overrideTemplate)
	{
		if (overrideTemplate->m_nextOverride)
			overrideTemplate =
				overrideTemplate->m_nextOverride->friend_getFinalOverride();
		specialPowerTemplate = (const SpecialPowerTemplate *)overrideTemplate;
	}
	switch (specialPowerTemplate->m_specialPowerType)
	{
	case (SpecialPowerType)0x15:
	case (SpecialPowerType)0x1a:
	case (SpecialPowerType)0x1d:
		((SpecialAbilityCleanupCall)j_000434c3)(this);
		break;
	}
}
