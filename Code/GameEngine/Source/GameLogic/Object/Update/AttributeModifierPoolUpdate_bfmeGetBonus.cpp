// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct AttributeModifierEntry
{
	UnsignedInt m_nameKey;
	UnsignedInt m_unused04;
	UnsignedInt m_expirationFrame;
	UnsignedInt m_unused0c;
};

class GameLogic
{
public:
	unsigned char m_unreconstructed[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class AttributeModifierDefinitionStore
{
public:
	Bool getValue(Int modifierIndex, Int attribute, Real *value) const;
};

extern AttributeModifierDefinitionStore *TheAttributeModifierDefinitionStore;

class AttributeModifierPoolUpdate
{
public:
	Bool bfmeGetBonus(Int attribute, Real *bonus);
	Bool bfmeGetAttributeModifierMultiplier(Int attribute, Real *multiplier);

private:
	Bool isModifierActive(UnsignedInt frame, const AttributeModifierEntry *entry) const;

	unsigned char m_unreconstructed00[0x20];
	AttributeModifierEntry *m_modifiersBegin;
	AttributeModifierEntry *m_modifiersEnd;
};

// The matched Object::getVisionRange caller proves this is the additive
// accumulator; the sibling at 0x00368C50 uses the same entries and multiplies.
Bool AttributeModifierPoolUpdate::bfmeGetBonus(Int attribute, Real *bonus)
{
	*bonus = 0.0f;
	Bool found = false;
	if (TheGameLogic == 0)
		return false;

	Real value;
	UnsignedInt frame = TheGameLogic->m_frame;
	for (AttributeModifierEntry *entry = m_modifiersBegin;
		entry != m_modifiersEnd;
		++entry)
	{
		if (isModifierActive(frame, entry))
		{
			value = 0.0f;
			if (TheAttributeModifierDefinitionStore->getValue(
				static_cast<Int>(entry->m_nameKey), attribute,
				&value))
			{
				found = true;
				*bonus += value;
			}
		}
	}
	return found;
}

// The exact Object wrapper at 0x001BFDD0 proves the multiplicative sibling's
// class and role even though its original retail method spelling is unknown.
Bool AttributeModifierPoolUpdate::bfmeGetAttributeModifierMultiplier(
	Int attribute, Real *multiplier)
{
	*multiplier = 1.0f;
	Bool found = false;
	if (TheGameLogic)
	{
		Real value;
		UnsignedInt frame = TheGameLogic->m_frame;
		for (AttributeModifierEntry *entry = m_modifiersBegin;
			entry != m_modifiersEnd;
			++entry)
		{
			if (isModifierActive(frame, entry))
			{
				value = 0.0f;
				if (TheAttributeModifierDefinitionStore->getValue(
					static_cast<Int>(entry->m_nameKey), attribute,
					&value))
				{
					found = true;
					*multiplier *= value;
				}
			}
		}
	}
	return found;
}
