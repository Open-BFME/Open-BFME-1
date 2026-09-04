// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef bool Bool;

struct AttributeModifierValue
{
	unsigned int m_attribute;
	unsigned int m_value;
};

class AttributeModifierValueRange
{
public:
	Bool findValue( unsigned int attribute, unsigned int *value ) const;

private:
	AttributeModifierValue *m_first;
	AttributeModifierValue *m_last;
};

Bool AttributeModifierValueRange::findValue(
	unsigned int attribute,
	unsigned int *value ) const
{
	for( AttributeModifierValue *entry = m_first; entry != m_last; ++entry )
	{
		if( entry->m_attribute == attribute )
		{
			*value = entry->m_value;
			return 1;
		}
	}

	return 0;
}
