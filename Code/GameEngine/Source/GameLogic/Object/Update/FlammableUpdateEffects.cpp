// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: the two FlammableUpdate methods that act on a burning object.
//
//   ?startBurningSound@  0x00293520, 113 bytes
//   ?doAflameDamage@     0x00293800,  72 bytes
//
// One starts the loop of burning audio and keeps its handle; the other applies a
// tick of flame damage. They are the two halves of what being on fire does, and
// between them they had three classes declared twice, each time as the slice one
// body happened to need:
//
//   FlammableUpdate            the module data at +0x04 and the object at +0x08
//                              in both, then the audio handle at +0x34 in one and
//                              the ignition source at +0x48 in the other, neither
//                              knowing the other field exists.
//   FlammableUpdateModuleData  the aflame damage amount at +0x14 in one, the
//                              burning sound's name at +0x18 in the other -- two
//                              adjacent INI fields, described as two disjoint
//                              classes that each began with a different pad.
//   Object                     thirteen virtual slots ending at attemptDamage on
//                              vtable+0x34 in one, and no virtuals at all with
//                              the id at +0x74 in the other.
//
// That id at +0x74 is the same offset AIGroup::getAllIDs and AIPlayer::findDozer
// reach in the other lanes, so the vptr the sound body left out is not in doubt.
//
// The third method in this family, tryToIgnite at 0x00293990, is still a naked
// machine-byte dump and is deliberately left where it is: merging a dump buys
// nothing and would only hide a real body's worth of work still to do.

typedef unsigned int UnsignedInt;

enum DamageType
{
	DAMAGE_FLAME = 6
};

enum DeathType
{
	DEATH_BURNED = 3
};

enum ObjectID
{
	OBJECT_ID_UNUSED = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo
{
public:
	DamageInfo();

	unsigned char m_pad00[8];
	int m_sourceID;					// +0x08
	unsigned char m_pad0C[4];
	int m_damageType;				// +0x10
	unsigned char m_pad14[4];
	int m_deathType;				// +0x18
	float m_amount;					// +0x1C
	unsigned char m_pad20[0x3c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void attemptDamage(DamageInfo *info);	// vtable +0x34

	ObjectID getID() const
	{
		return m_id;
	}

private:
	unsigned char m_pad04[0x74 - 4];
	ObjectID m_id;					// +0x74
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString& eventName, ObjectID ownerID);
	// Non-virtual local view: retail encodes the ILT at 0x00026F35, which the
	// ledger names ??1AudioEventRTS@@QAE@XZ for the body at 0x000B31F0. The vptr
	// the virtual spelling added is folded back into the padding so the layout is
	// unchanged.
	~AudioEventRTS();

private:
	unsigned char m_pad[0x70];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual UnsignedInt addAudioEvent(const AudioEventRTS *event);
};

extern AudioManager *TheAudio;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlammableUpdate.h
class FlammableUpdateModuleData
{
private:
	unsigned char m_pad00[8];
	unsigned int m_burnedDelay;
	unsigned int m_aflameDuration;
	unsigned int m_aflameDamageDelay;

public:
	int m_aflameDamageAmount;			// +0x14
	AsciiString m_burningSoundName;			// +0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlammableUpdate.h
class FlammableUpdate
{
public:
	void doAflameDamage();

protected:
	const FlammableUpdateModuleData *getFlammableUpdateModuleData() const
	{
		return m_moduleData;
	}

	Object *getObject() const
	{
		return m_object;
	}

	void startBurningSound();

private:
	virtual void unused();
	const FlammableUpdateModuleData *m_moduleData;	// +0x04
	Object *m_object;				// +0x08
	unsigned char m_pad0C[0x34 - 0x0C];
	UnsignedInt m_audioHandle;			// +0x34
	unsigned char m_pad38[0x48 - 0x38];
	int m_sourceID;					// +0x48
};

// ?startBurningSound@FlammableUpdate@@IAEXXZ
void FlammableUpdate::startBurningSound()
{
    const FlammableUpdateModuleData *data = getFlammableUpdateModuleData();

    AudioEventRTS audio(data->m_burningSoundName, getObject()->getID());
    m_audioHandle = TheAudio->addAudioEvent(&audio);
}

// ?doAflameDamage@FlammableUpdate@@QAEXXZ
// The Zero Hour body at FlammableUpdate.cpp:226 with BFME's DamageInfo field
// offsets -- source id at input+4, damage type at +0xC, death type at +0x14,
// amount at +0x18 -- and DAMAGE_FLAME 6 / DEATH_BURNED 3.
void FlammableUpdate::doAflameDamage()
{
	const FlammableUpdateModuleData *data = m_moduleData;
	Object *obj = m_object;
	DamageInfo info;
	info.m_amount = (float)data->m_aflameDamageAmount;
	info.m_sourceID = m_sourceID;
	info.m_damageType = DAMAGE_FLAME;
	info.m_deathType = DEATH_BURNED;
	obj->attemptDamage(&info);
}
