// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x001FEC30, 122 bytes.  The matched GettingBuiltBehavior constructor
// fixes Object at +0x08, its fourth interface at +0x20, the audio handle at
// +0x24, and the byte written here at +0x32.  The first indirect call is slot
// 5 of that real secondary interface; its retail target 0x001FE4A0 returns
// the same byte as [secondary-this+0x12].  The two direct calls are the matched
// Object model-condition notifier and ObjectStatusMask mutator; the final
// guarded call is AudioManager::removeAudioEvent, as independently established
// by this class's matched destructor.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef unsigned int UnsignedInt;
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

class Object
{
public:
	void notifyModelConditionChanged();
	void setStatus(const ObjectStatusMaskType &status, Bool set);

	__forceinline void rvaClearModelConditionBit68()
	{
		if ((m_modelConditionByte & 0x10) != 0)
		{
			m_modelConditionWord2 &= ~0x10U;
			notifyModelConditionChanged();
		}
	}

private:
	unsigned char m_unreconstructed00[0x118];
	union
	{
		UnsignedInt m_modelConditionWord2;
		unsigned char m_modelConditionByte;
	};
};

class GettingBuiltBehaviorDeepBase
{
public:
	virtual ~GettingBuiltBehaviorDeepBase();

protected:
	const void *m_moduleData;
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
	virtual void slot02() = 0;
	virtual void slot03() = 0;
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
	void rva001FEC30();

private:
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

void GettingBuiltBehavior::rva001FEC30()
{
	if (!rvaSlot05())
		return;

	Object *object = m_object;
	m_field32 = false;
	object->rvaClearModelConditionBit68();

	object->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit,
		OBJECT_STATUS_UNDER_CONSTRUCTION), false);

	if (TheAudio != 0)
	{
		TheAudio->removeAudioEvent(m_audioHandle);
		m_audioHandle = 1;
	}
}
