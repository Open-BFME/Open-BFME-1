// cl: /DNDEBUG /MD /EHsc
// readable body of ?onVeterancyLevelChanged@ActiveBody@@: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/ActiveBody.cpp
// Open-BFME: ActiveBody::onVeterancyLevelChanged, retail 0x0020E580, 520 bytes (jump table included).
//
// Identity: ActiveBody's constructor 0x00211A50 and destructor 0x0020F8E0
// install the primary vtable 0x010A78B0 and the body-interface vtable
// 0x010A7718 at +0x10.  Slot 11 of 0x010A7718 (ILT 0x00004129) is this body,
// directly ahead of setArmorSetFlag/clearArmorSetFlag (slots 12/13, which the
// body calls with the three armor-set bits) -- the Zero Hour position of
// onVeterancyLevelChanged in BodyModuleInterface.  setMaxHealth is slot 22.
//
// BFME deltas: two arguments (ret 8, no provideFeedback), the promotion sound
// is fetched by index from the template (103..105 for veteran/elite/heroic)
// behind a template null check.
//
// The method is a virtual of the body interface, which sits at +0x10 inside
// the module, so this points there: the module's object is this-0x08.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	static const AsciiString TheEmptyString;

private:
	char *m_data;
};

typedef int Int;
typedef bool Bool;
typedef float Real;
enum ObjectID { INVALID_ID = 0 };

enum VeterancyLevel
{
	LEVEL_REGULAR,
	LEVEL_VETERAN,
	LEVEL_ELITE,
	LEVEL_HEROIC,
};

enum ArmorSetType
{
	ARMORSET_VETERAN,
	ARMORSET_ELITE,
	ARMORSET_HERO,
};

enum MaxHealthChangeType
{
	SAME_CURRENTHEALTH,
	PRESERVE_RATIO,
};

enum
{
	BFME_SOUND_PROMOTED_VETERAN = 103,
	BFME_SOUND_PROMOTED_ELITE = 104,
	BFME_SOUND_PROMOTED_HERO = 105,
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName = AsciiString::TheEmptyString, ObjectID ownerID = INVALID_ID);	// ILT 0x00025306
	~AudioEventRTS();					// ILT 0x00026F35
	AudioEventRTS &operator=(const AudioEventRTS &right);	// ILT 0x0001F753

	void setObjectID(ObjectID id);				// ILT 0x00019A6A

private:
	unsigned char m_unmodelled_000[0x70];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const AudioEventRTS *getSound(Int index) const;		// ILT 0x0001BFD1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void unusedSlot05();
	virtual void unusedSlot06();
	virtual void unusedSlot07();
	virtual void unusedSlot08();
	virtual void unusedSlot09();
	virtual const ThingTemplate *getTemplate(void) const;	// vtable +0x28

	ObjectID getID(void) const { return m_id; }
	Object *getContainedBy(void) const { return m_containedBy; }

private:
	unsigned char m_unmodelled_004[0x74 - 0x04];
	ObjectID m_id;						// +0x74
	unsigned char m_unmodelled_078[0x214 - 0x78];
	Object *m_containedBy;					// +0x214
};

class Drawable
{
public:
	Object *getObject(void) const { return m_object; }

private:
	unsigned char m_unmodelled_000[0xfc];
	Object *m_object;					// +0xFC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void unusedSlot05();
	virtual void unusedSlot06();
	virtual void unusedSlot07();
	virtual void unusedSlot08();
	virtual void unusedSlot09();
	virtual void unusedSlot10();
	virtual void unusedSlot11();
	virtual void unusedSlot12();
	virtual void unusedSlot13();
	virtual void unusedSlot14();
	virtual void unusedSlot15();
	virtual void unusedSlot16();
	virtual void addAudioEvent(const AudioEventRTS *event);	// vtable +0x44
};

extern AudioManager *TheAudio;

class InGameUI
{
public:
	virtual void unusedSlot00(); virtual void unusedSlot01(); virtual void unusedSlot02(); virtual void unusedSlot03();
	virtual void unusedSlot04(); virtual void unusedSlot05(); virtual void unusedSlot06(); virtual void unusedSlot07();
	virtual void unusedSlot08(); virtual void unusedSlot09(); virtual void unusedSlot10(); virtual void unusedSlot11();
	virtual void unusedSlot12(); virtual void unusedSlot13(); virtual void unusedSlot14(); virtual void unusedSlot15();
	virtual void unusedSlot16(); virtual void unusedSlot17(); virtual void unusedSlot18(); virtual void unusedSlot19();
	virtual void unusedSlot20(); virtual void unusedSlot21(); virtual void unusedSlot22(); virtual void unusedSlot23();
	virtual void unusedSlot24(); virtual void unusedSlot25(); virtual void unusedSlot26(); virtual void unusedSlot27();
	virtual void unusedSlot28(); virtual void unusedSlot29(); virtual void unusedSlot30(); virtual void unusedSlot31();
	virtual void unusedSlot32(); virtual void unusedSlot33(); virtual void unusedSlot34(); virtual void unusedSlot35();
	virtual void unusedSlot36(); virtual void unusedSlot37(); virtual void unusedSlot38(); virtual void unusedSlot39();
	virtual void unusedSlot40(); virtual void unusedSlot41(); virtual void unusedSlot42(); virtual void unusedSlot43();
	virtual void unusedSlot44(); virtual void unusedSlot45(); virtual void unusedSlot46(); virtual void unusedSlot47();
	virtual void unusedSlot48(); virtual void unusedSlot49(); virtual void unusedSlot50(); virtual void unusedSlot51();
	virtual void unusedSlot52(); virtual void unusedSlot53(); virtual void unusedSlot54(); virtual void unusedSlot55();
	virtual void unusedSlot56(); virtual void unusedSlot57(); virtual void unusedSlot58(); virtual void unusedSlot59();
	virtual Int getSelectCount(void);			// vtable +0xF0
	virtual void unusedSlot61(); virtual void unusedSlot62(); virtual void unusedSlot63();
	virtual void unusedSlot64();
	virtual Drawable *getFirstSelectedDrawable(void);	// vtable +0x104
};

extern InGameUI *TheInGameUI;

class ControlBar
{
public:
	void markUIDirty(void) { m_UIDirty = true; }

private:
	unsigned char m_unmodelled_000[0x24];
	Bool m_UIDirty;						// +0x24
};

extern ControlBar *TheControlBar;

class GlobalData
{
public:
	unsigned char m_unmodelled_000[0xb98];
	Real m_healthBonus[4];					// +0xB98
};

extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ((const GlobalData *)TheWritableGlobalData)

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	unsigned char m_beforeObject[4];
	Object *m_object;					// module+0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class BodyModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10();
	virtual void onVeterancyLevelChanged(VeterancyLevel oldLevel, VeterancyLevel newLevel) = 0;	// +0x2C
	virtual void setArmorSetFlag(ArmorSetType ast) = 0;					// +0x30
	virtual void clearArmorSetFlag(ArmorSetType ast) = 0;					// +0x34
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21();
	virtual void setMaxHealth(Real maxHealth, MaxHealthChangeType healthChangeType) = 0;	// +0x58
};

class ActiveBody : public BehaviorModule, public BehaviorModuleInterface, public BodyModuleInterface
{
public:
	virtual void onVeterancyLevelChanged(VeterancyLevel oldLevel, VeterancyLevel newLevel);

protected:
	Object *getObject() { return m_object; }

private:
	unsigned char m_unmodelled_014[0x20 - 0x14];
	Real m_maxHealth;					// module+0x20
};

void ActiveBody::onVeterancyLevelChanged( VeterancyLevel oldLevel, VeterancyLevel newLevel )
{
	if (oldLevel == newLevel)
		return;

	if (oldLevel < newLevel)
	{
		const ThingTemplate *tmpl = getObject()->getTemplate();
		if (tmpl)
		{
			AudioEventRTS veterancyChanged;
			switch (newLevel)
			{
				case LEVEL_VETERAN:
					veterancyChanged = *tmpl->getSound(BFME_SOUND_PROMOTED_VETERAN);
					break;
				case LEVEL_ELITE:
					veterancyChanged = *tmpl->getSound(BFME_SOUND_PROMOTED_ELITE);
					break;
				case LEVEL_HEROIC:
					veterancyChanged = *tmpl->getSound(BFME_SOUND_PROMOTED_HERO);
					break;
			}

			veterancyChanged.setObjectID(getObject()->getID());
			TheAudio->addAudioEvent(&veterancyChanged);
		}

		//Also mark the UI dirty -- incase the object is selected or contained.
		Object *obj = getObject();
		Drawable *draw = TheInGameUI->getFirstSelectedDrawable();
		if( draw )
		{
			Object *checkOwner = draw->getObject();
			if( checkOwner == obj )
			{
				//Our selected object has been promoted!
				TheControlBar->markUIDirty();
			}
			else
			{
				const Object *containedBy = obj->getContainedBy();
				//But only if the contained by object is containing me!
				if( containedBy && TheInGameUI->getSelectCount() == 1 && checkOwner == containedBy )
					TheControlBar->markUIDirty();
			}
		}
	}

	Real oldBonus = TheGlobalData->m_healthBonus[oldLevel];
	Real newBonus = TheGlobalData->m_healthBonus[newLevel];
	Real mult = newBonus / oldBonus;

	// change the max
	setMaxHealth(m_maxHealth * mult, PRESERVE_RATIO );

	switch (newLevel)
	{
		case LEVEL_REGULAR:
			clearArmorSetFlag(ARMORSET_VETERAN);
			clearArmorSetFlag(ARMORSET_ELITE);
			clearArmorSetFlag(ARMORSET_HERO);
			break;
		case LEVEL_VETERAN:
			setArmorSetFlag(ARMORSET_VETERAN);
			clearArmorSetFlag(ARMORSET_ELITE);
			clearArmorSetFlag(ARMORSET_HERO);
			break;
		case LEVEL_ELITE:
			clearArmorSetFlag(ARMORSET_VETERAN);
			setArmorSetFlag(ARMORSET_ELITE);
			clearArmorSetFlag(ARMORSET_HERO);
			break;
		case LEVEL_HEROIC:
			clearArmorSetFlag(ARMORSET_VETERAN);
			clearArmorSetFlag(ARMORSET_ELITE);
			setArmorSetFlag(ARMORSET_HERO);
			break;
	}
}
