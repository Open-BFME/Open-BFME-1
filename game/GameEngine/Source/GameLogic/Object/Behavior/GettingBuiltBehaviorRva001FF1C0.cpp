// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x001FF1C0, 321 bytes: slot 3 of GettingBuiltBehavior's secondary
// vtable 0x010A45E0 (slot 1 is the matched rva001FF360, slot 5 the byte getter
// at 0x001FE4A0).  The subobject sits at owner+0x20, so this-0x1C and this-0x18
// are the module data and Object.  When slot 5 reports false and the module
// names no worker, it kills `other` if that is the worker building this
// object (m_builderID / m_producerID / m_id cross-check); otherwise it ends
// construction.  Either path then drops the build sound, as rva001FEC30 does.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

template <Int NUMBITS>
class BitFlags
{
public:
	enum InitTag { kInit };

	__forceinline BitFlags(InitTag, Int index)
	{
		m_bits.set(index);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE,
	OBJECT_STATUS_DESTROYED,
	OBJECT_STATUS_UNDER_CONSTRUCTION
};

enum KindOfType
{
	KINDOF_RVA001FF1C0_KEEPS_DRAWABLE_QUIET = 0x88
};

enum DamageType
{
	DAMAGE_RVA001FF1C0_WORKER = 8
};

enum DeathType
{
	DEATH_RVA001FF1C0_WORKER = 0x16
};

typedef Int ObjectID;

template <typename T>
struct StringData
{
	Int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T>
class StringBase
{
friend class AsciiString;

private:
	StringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	Bool isEmpty() const { return !m_data || m_data->m_length == 0; }
};

class Rva00414930
{
public:
	void broadcast();
};

class Bfme5WalkOwner
{
public:
	void bfmeNotifyAll();
};

class Thing
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
	virtual Rva00414930 *rvaSlot10();

	Bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
public:
	void notifyModelConditionChanged();
	void setStatus(const ObjectStatusMaskType &status, Bool set);
	void kill(DamageType damageType, DeathType deathType);

	__forceinline ObjectID getID() const { return m_id; }
	__forceinline ObjectID getProducerID() const { return m_producerID; }
	__forceinline ObjectID getBuilderID() const { return m_builderID; }

	__forceinline void clearModelCondition118Bit04()
	{
		if ((m_modelCondition118Byte & 0x04) != 0)
		{
			m_modelCondition118 &= ~0x04U;
			notifyModelConditionChanged();
		}
	}

	__forceinline void clearModelCondition118Bit10()
	{
		if ((m_modelCondition118Byte & 0x10) != 0)
		{
			m_modelCondition118 &= ~0x10U;
			notifyModelConditionChanged();
		}
	}

	unsigned char m_unreconstructed04[0x74 - 0x04];
	ObjectID m_id;
	ObjectID m_producerID;
	ObjectID m_builderID;
	unsigned char m_unreconstructed80[0x118 - 0x80];
	union
	{
		UnsignedInt m_modelCondition118;
		unsigned char m_modelCondition118Byte;
	};
	unsigned char m_unreconstructed11C[0x220 - 0x11C];
	Real m_field220;
};

class ModuleData
{
public:
	virtual ~ModuleData();
};

class GettingBuiltBehaviorModuleData : public ModuleData
{
public:
	virtual ~GettingBuiltBehaviorModuleData();

	unsigned char m_unreconstructed04[0x14 - 0x04];
	AsciiString m_workerName;
};

class GettingBuiltBehaviorDeepBase
{
public:
	virtual ~GettingBuiltBehaviorDeepBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class GettingBuiltBehaviorInterface1
{
public:
	virtual void slot00() = 0;
};

class GettingBuiltBehaviorInterface2
{
public:
	virtual void slot00() = 0;
};

class GettingBuiltBehaviorUpdateModule :
	public GettingBuiltBehaviorDeepBase,
	public GettingBuiltBehaviorInterface1,
	public GettingBuiltBehaviorInterface2
{
protected:
	UnsignedInt m_nextCallFrameAndPhase;
	Int m_indexInLogic;
	Int m_indexInUpdate;
};

class GettingBuiltBehaviorSecondaryInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void rvaSlot02() = 0;
	virtual void rva001FF1C0(Object *other) = 0;
	virtual void slot04() = 0;
	virtual Bool rvaSlot05() = 0;
};

class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18();
	virtual void removeAudioEvent(UnsignedInt audioEvent);
};

extern AudioManager *TheAudio;

class GettingBuiltBehavior :
	public GettingBuiltBehaviorUpdateModule,
	public GettingBuiltBehaviorSecondaryInterface
{
public:
	virtual void rva001FF1C0(Object *other);

private:
	__forceinline const GettingBuiltBehaviorModuleData *getGettingBuiltBehaviorModuleData() const
	{
		return static_cast<const GettingBuiltBehaviorModuleData *>(m_moduleData);
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

// ?rva001FF1C0@GettingBuiltBehavior@@UAEXPAVObject@@@Z
void GettingBuiltBehavior::rva001FF1C0(Object *other)
{
	const GettingBuiltBehaviorModuleData *data = getGettingBuiltBehaviorModuleData();
	Object *object = m_object;

	if (!rvaSlot05())
	{
		if (!data->m_workerName.isEmpty())
			return;

		if (object && other
			&& object->getBuilderID() == other->getID()
			&& other->getProducerID() == object->getID()
			&& other->getID() != object->getID())
			other->kill(DAMAGE_RVA001FF1C0_WORKER, DEATH_RVA001FF1C0_WORKER);
	}
	else
	{
		m_field32 = false;
		object->m_field220 = -1.0f;
		if (m_field33 && !object->isKindOf(KINDOF_RVA001FF1C0_KEEPS_DRAWABLE_QUIET)
			&& object->rvaSlot10())
			object->rvaSlot10()->broadcast();

		object->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit,
			OBJECT_STATUS_UNDER_CONSTRUCTION), false);
		object->clearModelCondition118Bit04();
		object->clearModelCondition118Bit10();
		reinterpret_cast<Bfme5WalkOwner *>(object)->bfmeNotifyAll();
		rvaSlot02();
	}

	if (TheAudio != 0 && m_audioHandle >= 5)
	{
		TheAudio->removeAudioEvent(m_audioHandle);
		m_audioHandle = 1;
	}
	m_field35 = false;
}
