// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

enum DisabledType
{
	DISABLED_UNMANNED = 3
};

enum ModelConditionFlagType
{
	MODELCONDITION_PACKING_TYPE_2 = 94
};

template <int BitCount>
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
	void clear(Int bit) { m_bits.reset(bit); }

private:
	_STL::bitset<BitCount> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;
typedef BitFlags<288> ModelConditionFlags;

class Object
{
public:
	void setProducer(const Object *producer);
	Bool clearDisabled(DisabledType type);
	void notifyModelConditionChanged(void);
	void setStatus(const ObjectStatusMaskType &status, Bool set);

	unsigned char m_pad000[0x110];
	ModelConditionFlags m_modelConditionFlags;
};

class Gen_003711C0
{
public:
	void reset(Object *object);
};

inline void clearPackingCondition(Object *object)
{
	if (object->m_modelConditionFlags.test(MODELCONDITION_PACKING_TYPE_2))
	{
		object->m_modelConditionFlags.clear(MODELCONDITION_PACKING_TYPE_2);
		object->notifyModelConditionChanged();
	}
}

void Gen_003711C0::reset(Object *object)
{
	object->setProducer(0);
	object->clearDisabled(DISABLED_UNMANNED);
	clearPackingCondition(object);
	object->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit,
		3), false);
	object->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit,
		78), false);
	{
		ObjectStatusMaskType status(ObjectStatusMaskType::kInit, 5);
		object->setStatus(status, false);
	}
}
