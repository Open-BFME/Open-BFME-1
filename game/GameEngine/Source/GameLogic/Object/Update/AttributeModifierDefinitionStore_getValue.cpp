// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef bool Bool;
typedef int Int;
typedef float Real;

struct AttributeModifierValue;

class AttributeModifierValueRange
{
public:
	Bool findValue(unsigned int attribute, unsigned int *value) const;

private:
	AttributeModifierValue *m_first;
	AttributeModifierValue *m_last;
};

class AttributeModifierDefinition
{
public:
	AttributeModifierValueRange m_values;
};

class AttributeModifierDefinitionRange
{
public:
	unsigned int size() const { return m_end - m_begin; }
	AttributeModifierDefinition *operator[](Int index) const
	{
		return m_begin[index];
	}

	AttributeModifierDefinition **m_begin;
	AttributeModifierDefinition **m_end;
};

class AttributeModifierDefinitionStore
{
public:
	Bool getValue(Int modifierIndex, Int attribute, Real *value) const;

private:
	unsigned char m_unreconstructed00[8];
	AttributeModifierDefinitionRange m_definitions;
};

Bool AttributeModifierDefinitionStore::getValue(
	Int modifierIndex, Int attribute, Real *value) const
{
	if (modifierIndex < 0 ||
		static_cast<unsigned int>(modifierIndex) > m_definitions.size() - 1)
		return false;

	AttributeModifierDefinition **definitions = m_definitions.m_begin;
	if (definitions[modifierIndex] == 0)
		return false;

	// Retail evaluates the slot separately for the null check and dispatch.
	_ReadWriteBarrier();
	return definitions[modifierIndex]->m_values.findValue(
		static_cast<unsigned int>(attribute),
		reinterpret_cast<unsigned int *>(value));
}
