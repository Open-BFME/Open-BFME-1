// ?d_001fecd0@@YAXXZ
// partial score=0.993 date=2026-09-30
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x001FECD0, 718 bytes: slot 4 of GettingBuiltBehavior's secondary
// vtable 0x010A45E0 (ILT 0x000015C8).  The subobject sits at owner+0x20, so
// this-0x20 is the module, this-0x1C its module data and this-0x18 the Object.
// The Bool argument skips the affordability check and the cost withdrawal; the
// body starts or resumes construction and plays the matching build loop.
// Residue (5 bytes at +0x234): retail loads ECX for Rva00087750Ref::operator=
// before pushing the source reference; this spelling pushes first.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

enum ObjectID
{
	INVALID_ID = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class Player;
class Object;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Overridable
{
public:
	__inline const Overridable *getFinalOverride() const;

	void *m_vtable;
	const Overridable *m_nextOverride;
};

__inline const Overridable *Overridable::getFinalOverride() const
{
	if (m_nextOverride != 0)
		return m_nextOverride->getFinalOverride();
	return this;
}

class ThingTemplate : public Overridable
{
public:
	Int calcTimeToBuild(const Player *player, Int buildIndex) const;
};

class ThingTemplateOverride
{
public:
	__forceinline operator const ThingTemplate *() const
	{
		const ThingTemplate *value = m_value;
		if (value == 0)
			return 0;
		return (const ThingTemplate *)value->getFinalOverride();
	}

private:
	const ThingTemplate *volatile m_value;
};

class ScoreKeeper
{
public:
	void addObjectBuilt(Object *object, Int count);
};

class Player
{
public:
	unsigned char m_unreconstructed00[0x348];
	ScoreKeeper m_scoreKeeper;
};

class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual Real rvaSlot05() = 0;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void setBuilder(const Object *builder);
	void setEffectivelyDead(Bool dead);
	void setStatusBit(Int status, Bool set);
	void notifyModelConditionChanged();

	__forceinline const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline const Coord3D *getPosition() const { return &m_position; }
	__forceinline Real getOrientation() const { return m_orientation; }
	__forceinline ObjectID getID() const { return m_id; }
	__forceinline BodyModuleInterface *getBodyModule() const { return m_body; }

	__forceinline void clearModelCondition110Bit20()
	{
		if ((m_modelCondition110Byte & 0x20) != 0)
		{
			m_modelCondition110 &= ~0x20U;
			notifyModelConditionChanged();
		}
	}

	__forceinline void clearModelCondition114Bit20000000()
	{
		if ((m_modelCondition114 & 0x20000000) != 0)
		{
			m_modelCondition114 &= ~0x20000000U;
			notifyModelConditionChanged();
		}
	}

	__forceinline void clearModelCondition114Bit08000000()
	{
		if ((m_modelCondition114 & 0x08000000) != 0)
		{
			m_modelCondition114 &= ~0x08000000U;
			notifyModelConditionChanged();
		}
	}

	__forceinline void setModelCondition118Bit10()
	{
		if ((m_modelCondition118 & 0x10) == 0)
		{
			m_modelCondition118 |= 0x10U;
			notifyModelConditionChanged();
		}
	}

	void *m_vtable;
	ThingTemplateOverride m_template;
	unsigned char m_unreconstructed08[0x38 - 0x08];
	Coord3D m_position;
	Real m_orientation;
	unsigned char m_unreconstructed48[0x74 - 0x48];
	ObjectID m_id;
	unsigned char m_unreconstructed78[0x110 - 0x78];
	union
	{
		UnsignedInt m_modelCondition110;
		unsigned char m_modelCondition110Byte;
	};
	UnsignedInt m_modelCondition114;
	UnsignedInt m_modelCondition118;
	unsigned char m_unreconstructed11C[0x200 - 0x11C];
	BodyModuleInterface *m_body;
	unsigned char m_unreconstructed204[0x220 - 0x204];
	Real m_field220;
	unsigned char m_unreconstructed224[0x342 - 0x224];
	Bool m_field342;
	unsigned char m_unreconstructed343;
	unsigned char m_privateStatus;
};

class BuildAssistant
{
	friend class GettingBuiltBehavior;

protected:
	Bool moveObjectsForConstruction(const ThingTemplate *whatToBuild,
		const Coord3D *pos, Real angle, Player *playerToBuild);
};

extern BuildAssistant *TheBuildAssistant;

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
};

class Rva00087750Ref
{
public:
	Rva00087750Ref() : m_ptr(0) {}
	~Rva00087750Ref()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	Rva00087750Ref &operator=(const Rva00087750Ref &rhs);

	Rva00087750Counted *m_ptr;
};

struct AudioEventInfoRef : public Rva00087750Ref
{
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventInfoRef &eventInfo, ObjectID ownerID);
	~AudioEventRTS();

private:
	unsigned char m_unreconstructed00[0x70];
};

class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual UnsignedInt addAudioEvent(const AudioEventRTS *eventToAdd);
	virtual void slot18();
	virtual void removeAudioEvent(UnsignedInt audioEvent);
};

extern AudioManager *TheAudio;

class ModuleData
{
public:
	virtual ~ModuleData();
};

class GettingBuiltBehaviorModuleData : public ModuleData
{
public:
	virtual ~GettingBuiltBehaviorModuleData();

	unsigned char m_gap0[4];
	AudioEventInfoRef m_ref0;
	AudioEventInfoRef m_ref1;
	AudioEventInfoRef m_ref2;
};

class GettingBuiltBehaviorDeepBase
{
public:
	virtual ~GettingBuiltBehaviorDeepBase();

protected:
	__forceinline const ModuleData *getModuleData() const { return m_moduleData; }
	__forceinline Object *getObject() const { return m_object; }

private:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class GettingBuiltBehaviorInterface1 { public: virtual void slot00() = 0; };
class GettingBuiltBehaviorInterface2 { public: virtual void slot00() = 0; };

class UpdateModule :
	public GettingBuiltBehaviorDeepBase,
	public GettingBuiltBehaviorInterface1,
	public GettingBuiltBehaviorInterface2
{
protected:
	void setWakeFrame(Object *object, UpdateSleepTime whenToWakeUp);

	UnsignedInt m_nextCallFrameAndPhase;
	Int m_indexInLogic;
	Int m_indexInUpdate;
};

class GettingBuiltBehaviorSecondaryInterface
{
public:
	virtual void rvaSlot00() = 0;
	virtual void rvaSlot01(Object *other) = 0;
	virtual void rvaSlot02() = 0;
	virtual void rvaSlot03(Object *other) = 0;
	virtual void rva001FECD0(Bool alreadyPaid) = 0;
	virtual Bool rvaSlot05() = 0;
	virtual Bool rvaSlot06(Player *player) = 0;
};

class Rva001FE6D0Owner
{
public:
	void withdrawPlayerCost();
};

class GettingBuiltBehavior :
	public UpdateModule,
	public GettingBuiltBehaviorSecondaryInterface
{
public:
	virtual void rva001FECD0(Bool alreadyPaid);

private:
	__forceinline const GettingBuiltBehaviorModuleData *getGettingBuiltBehaviorModuleData() const
	{
		return static_cast<const GettingBuiltBehaviorModuleData *>(getModuleData());
	}

	UnsignedInt m_audioHandle;
	UnsignedInt m_field28;
	UnsignedInt m_field2C;
	Bool m_field30;
	Bool m_field31;
	Bool m_field32;
	Bool m_field33;
	Bool m_field34;
	Bool m_field35;
	Bool m_field36;
	UnsignedInt m_field38;
};

// ?rva001FECD0@GettingBuiltBehavior@@UAEX_N@Z
void GettingBuiltBehavior::rva001FECD0(Bool alreadyPaid)
{
	Object *object = getObject();
	Player *player = object->getControllingPlayer();
	if (player == 0)
		return;

	if (!alreadyPaid && !rvaSlot06(player))
		return;

	m_field32 = true;
	if (!alreadyPaid)
		reinterpret_cast<Rva001FE6D0Owner *>(this)->withdrawPlayerCost();

	if (m_field2C == 0)
		m_field2C = object->getTemplate()->calcTimeToBuild(player, -1);

	m_field35 = (object->m_privateStatus & 1) != 0;
	if (m_field35)
	{
		Player *controller = object->getControllingPlayer();
		controller->m_scoreKeeper.addObjectBuilt(object, 1);
		object->m_field342 = false;
		TheBuildAssistant->moveObjectsForConstruction(object->getTemplate(),
			object->getPosition(), object->getOrientation(), player);
	}

	if (m_field36)
	{
		object->m_field220 = -1.0f;
	}
	else
	{
		if (m_field35)
			object->m_field220 = 0.0f;
		object->setStatusBit(2, true);
	}

	if (!m_field35 && !m_field36)
	{
		object->m_field220 = object->getBodyModule()->rvaSlot05() * 100.0f;
	}
	else
	{
		object->setEffectivelyDead(false);
		m_field33 = false;
	}

	if (m_field35 || (!m_field33 && !m_field36))
		object->setModelCondition118Bit10();

	m_field34 = false;
	object->clearModelCondition110Bit20();
	object->clearModelCondition114Bit20000000();
	object->clearModelCondition114Bit08000000();
	object->setBuilder(object);
	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);

	const GettingBuiltBehaviorModuleData *data = getGettingBuiltBehaviorModuleData();
	if (TheAudio != 0)
	{
		if (m_audioHandle >= 5)
			TheAudio->removeAudioEvent(m_audioHandle);

		AudioEventInfoRef sound;
		const AudioEventInfoRef *loop = m_field35 ? &data->m_ref2
			: (!m_field33 ? &data->m_ref0 : &data->m_ref1);
		if (loop->m_ptr != 0)
		{
			sound = *loop;
			if (sound.m_ptr != 0)
			{
				AudioEventRTS audioEvent(
					sound, object->getID());
				m_audioHandle = TheAudio->addAudioEvent(&audioEvent);
			}
		}
	}
}
