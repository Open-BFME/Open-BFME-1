// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

struct AttributeModifierEntry
{
	unsigned int m_key;
	unsigned int m_unused;
	unsigned int m_limit;
};

struct AttributeModifierDefinitionFlags
{
	int getSingleBit() const
	{
		for( int index = 0; index < 7; ++index )
		{
			if( m_bits & ( 1 << ( index & 31 ) ) )
				return index;
		}

		return -1;
	}

	unsigned int m_bits;
};

struct AttributeModifierDefinition
{
	char m_unused[ 12 ];
	AttributeModifierDefinitionFlags m_flags;
};

struct AttributeModifierDefinitionStore
{
	AttributeModifierDefinition *findDefinition( unsigned int key );
};

extern AttributeModifierDefinitionStore *TheAttributeModifierDefinitionStore;

class AttributeModifierPoolUpdate
{
private:
	bool isModifierActive( unsigned int frame,
		const AttributeModifierEntry *entry ) const;

	char m_unused[ 0x30 ];
	unsigned int m_activationFrames[ 7 ];
};

bool AttributeModifierPoolUpdate::isModifierActive( unsigned int frame,
	const AttributeModifierEntry *entry ) const
{
	int index = TheAttributeModifierDefinitionStore->findDefinition( entry->m_key )
		->m_flags.getSingleBit();

	bool belowLimit = frame < entry->m_limit;
	bool atOrBelowThreshold =
		index >= 0 && frame <= m_activationFrames[ index ];
	if( belowLimit && !atOrBelowThreshold )
		return true;

	return false;
}
