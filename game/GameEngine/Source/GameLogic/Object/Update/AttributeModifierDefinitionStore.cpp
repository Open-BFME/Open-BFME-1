extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Object;

struct AttributeModifierValue
{
	unsigned int m_attribute;
	unsigned int m_value;
};

class AttributeModifierValueRange
{
public:
	bool findValue(unsigned int attribute, unsigned int *value) const;

private:
	AttributeModifierValue *m_first;
	AttributeModifierValue *m_last;
};

class AttributeModifierDefinition
{
public:
	AttributeModifierValueRange m_values;
	char m_unreconstructed08[ 0x0C ];
	int m_key;
	int m_value;

	int primaryValueFor(const Object *object) const;
	int secondaryValueFor(const Object *object) const;
};

class AttributeModifierDefinitionRange
{
public:
	unsigned int size(void) const { return m_end - m_begin; }
	AttributeModifierDefinition *operator[](int index) const { return m_begin[index]; }

	AttributeModifierDefinition **m_begin;
	AttributeModifierDefinition **m_end;
};

class AttributeModifierDefinitionStore
{
public:
	char m_unreconstructed[ 8 ];
	AttributeModifierDefinitionRange m_definitions;

	int indexOf(int key) const;
	int valueAt(int index) const;
	int primaryValueAt(int index, const Object *object) const;
	int secondaryValueAt(int index, const Object *object) const;
};

int AttributeModifierDefinitionStore::indexOf(int key) const
{
	AttributeModifierDefinition **cursor = m_definitions.m_begin;
	AttributeModifierDefinition **end = m_definitions.m_end;
	int index = 0;
	while( cursor != end )
	{
		if( (*cursor)->m_key == key )
			return index;
		++cursor;
		++index;
	}
	return -1;
}

int AttributeModifierDefinitionStore::valueAt(int index) const
{
	if( index < 0 || (unsigned int)index > m_definitions.size() - 1 )
		return 0;

	AttributeModifierDefinition *item = m_definitions[index];
	return item ? item->m_value : 0;
}

int AttributeModifierDefinitionStore::primaryValueAt(
	int index,
	const Object *object) const
{
	if( index < 0 || (unsigned int)index > m_definitions.size() - 1 )
		return 0;

	AttributeModifierDefinition *item = m_definitions[index];
	return item ? item->primaryValueFor(object) : 0;
}

int AttributeModifierDefinitionStore::secondaryValueAt(
	int index,
	const Object *object) const
{
	if( index < 0 || (unsigned int)index > m_definitions.size() - 1 )
		return 0;

	AttributeModifierDefinition *item = m_definitions[index];
	return item ? item->secondaryValueFor(object) : 0;
}
