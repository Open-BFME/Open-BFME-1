// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

enum DisabledType
{
	DISABLED_UNMANNED = 3
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 3,
	OBJECT_STATUS_MARCH_OF_DEATH = 78
};

template <int BitCount>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum InitType { kInit };

	BitFlags() {}

	BitFlags(InitType, Int bit)
	{
		m_bits.set(bit);
	}

	Bool test(Int bit) const { return m_bits.test(bit); }
	void set(Int bit) { m_bits.set(bit); }

private:
	_STL::bitset<BitCount> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

enum ModelConditionFlagType
{
	MODELCONDITION_PACKING_TYPE_2 = 94
};

typedef BitFlags<288> ModelConditionFlags;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setProducer(const Object *producer);
	void setDisabled(DisabledType type);
	void notifyModelConditionChanged(void);
	void setStatus(const ObjectStatusMaskType &status, Bool set);
	void setModelConditionState(ModelConditionFlagType state);

	unsigned char m_unmodelled_000[0x110];
	ModelConditionFlags m_modelConditionFlags;
};

// ?setModelConditionState@Object@@ present-unmatched
inline void Object::setModelConditionState(ModelConditionFlagType state)
{
	if (!m_modelConditionFlags.test(state))
	{
		m_modelConditionFlags.set(state);
		notifyModelConditionChanged();
	}
}

class CastleBehavior
{
public:
	void prepareOwnedObjectForUnpack(Object *object);

private:
	unsigned char m_unmodelled_000[8];
	Object *m_object;
};

// The helper is called by CastleBehavior's owned-object classifier at
// 0x00373415 before it unpacks the object.
// ?prepareOwnedObjectForUnpack@CastleBehavior@@QAEXPAVObject@@@Z
void CastleBehavior::prepareOwnedObjectForUnpack(Object *object)
{
	object->setProducer(m_object);
	object->setDisabled(DISABLED_UNMANNED);

	object->setModelConditionState(MODELCONDITION_PACKING_TYPE_2);

	object->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit,
		OBJECT_STATUS_UNDER_CONSTRUCTION), true);
	object->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit,
		OBJECT_STATUS_MARCH_OF_DEATH), true);
}
