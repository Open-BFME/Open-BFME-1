class AttributeModifierCategoryMask
{
public:
	unsigned int m_bits;
};

class AttributeModifierPoolUpdate
{
public:
	char m_unreconstructed[ 0x48 ];
	int m_values[ 8 ];

	int bfmeGetCountForCategoryMask(const AttributeModifierCategoryMask *mask) const;
};

int AttributeModifierPoolUpdate::bfmeGetCountForCategoryMask(
	const AttributeModifierCategoryMask *mask) const
{
	int index;
	for( index = 0; index < 7; ++index )
	{
		if( mask->m_bits & (1u << (index & 0x1F)) )
			goto found;
	}
	index = -1;

found:
	return m_values[index + 1];
}
