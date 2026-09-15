// cl: /DNDEBUG /MD /EHsc
// Rva00608FE0Element destructor, retail 0x00608480 (130 bytes).
// The caller at 0x006089C0 names this 0x210-byte sound-upgrade record.
// Its member order explains the retail exception-state sequence: the map
// destructs first, the 109-item array follows, and the two 0x0C-byte members
// destruct last.

class AttributeModifierAuraUpdateModuleDataMemberB
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberB();

private:
	char m_body[0x0C];
};

class RandomSoundSelectorMap
{
public:
	~RandomSoundSelectorMap();

private:
	char m_body[0x0C];
};

class Rva00608FE0Item
{
public:
	virtual void release(bool now);
};

class Rva00608FE0Items
{
public:
	~Rva00608FE0Items()
	{
		for (int i = 0; i < 0x6D; ++i)
		{
			Rva00608FE0Item *item = m_items[i];
			if (item != 0)
			{
				item->release(true);
				m_items[i] = 0;
			}
		}
	}

private:
	Rva00608FE0Item *m_items[0x6D];
};

class Rva00608FE0Element
{
public:
	~Rva00608FE0Element();

private:
	char m_pod0[0x30];
	AttributeModifierAuraUpdateModuleDataMemberB m_member30;
	AttributeModifierAuraUpdateModuleDataMemberB m_member3C;
	Rva00608FE0Items m_member48;
	RandomSoundSelectorMap m_member1FC;
	int m_field208;
	unsigned char m_field20C;
	char m_padding20D[3];
};

// ??1Rva00608FE0Element@@QAE@XZ
Rva00608FE0Element::~Rva00608FE0Element()
{
}
