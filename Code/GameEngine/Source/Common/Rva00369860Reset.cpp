#include <string.h>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

template <typename T>
const T &AttributeModifierMin(const T &left, const T &right)
{
	return right < left ? right : left;
}

class AttributeModifierCategoryMask
{
public:
	unsigned int m_bits;
};

class AttributeModifierPoolUpdate
{
public:
	int bfmeGetCountForCategoryMask(
		const AttributeModifierCategoryMask *mask) const;
};

class AttributeModifierDefinition;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
	friend class AttributeModifierDefinition;

private:
	AttributeModifierPoolUpdate *bfmeFindAttributeModifierPoolUpdate(void) const;
};

class AttributeModifierIntPair
{
public:
	int m_first;
	int m_second;
};

class AttributeModifierIntPairRange
{
public:
	__forceinline void clear(void) { erase(m_begin, m_end); }

private:
	__forceinline AttributeModifierIntPair *erase(
		AttributeModifierIntPair *first, AttributeModifierIntPair *last)
	{
		int count = m_end - last;
		AttributeModifierIntPair *output = first;
		while( count > 0 )
		{
			*output = *last;
			++last;
			++output;
			--count;
		}
		m_end = output;
		return first;
	}

	AttributeModifierIntPair *m_begin;
	AttributeModifierIntPair *m_end;
	AttributeModifierIntPair *m_capacity;
};

class AttributeModifierDefinition
{
public:
	AttributeModifierIntPairRange m_pairs;
	AttributeModifierCategoryMask m_mask;
	char m_unreconstructed10[ 4 ];
	int m_mode;
	int m_field18;
	int m_firstValues[ 10 ];
	int m_secondValues[ 10 ];
	int m_primaryValues[ 3 ];
	int m_secondaryValues[ 3 ];
	char m_unreconstructed84[ 8 ];
	bool m_flag8C;

	void reset(int mode);
	int primaryValueFor(const Object *object) const;
	int secondaryValueFor(const Object *object) const;
};

void AttributeModifierDefinition::reset(int mode)
{
	m_mode = mode;
	m_field18 = 0;
	m_pairs.clear();
	memset(m_firstValues, 0, sizeof(m_firstValues));
	memset(m_secondValues, 0, sizeof(m_secondValues));
	m_flag8C = false;
	// Keep the flag store ahead of the saved-register restore, as in retail.
	_ReadWriteBarrier();
	m_primaryValues[0] = 0;
	m_secondaryValues[0] = 0;
	m_primaryValues[1] = 0;
	m_secondaryValues[1] = 0;
	m_primaryValues[2] = 0;
	m_secondaryValues[2] = 0;
}

int AttributeModifierDefinition::primaryValueFor(const Object *object) const
{
	if( !m_flag8C || object == 0 )
		return m_primaryValues[0];

	AttributeModifierPoolUpdate *values =
		object->bfmeFindAttributeModifierPoolUpdate();
	if( values == 0 )
		return m_primaryValues[0];

	int index = values->bfmeGetCountForCategoryMask(&m_mask) - 1;
	index = AttributeModifierMin(index, 2);
	return index >= 0 ? m_primaryValues[index] : m_primaryValues[0];
}

int AttributeModifierDefinition::secondaryValueFor(const Object *object) const
{
	if( !m_flag8C || object == 0 )
		return m_secondaryValues[0];

	AttributeModifierPoolUpdate *values =
		object->bfmeFindAttributeModifierPoolUpdate();
	if( values == 0 )
		return m_secondaryValues[0];

	int index = values->bfmeGetCountForCategoryMask(&m_mask) - 1;
	index = AttributeModifierMin(index, 2);
	return index >= 0 ? m_secondaryValues[index] : m_secondaryValues[0];
}
