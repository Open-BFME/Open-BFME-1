// ?d_00608480@@YAXXZ
// partial score=0.98 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc

// Rva00608FE0Element destructor, retail 0x00608480 (130 bytes).  The element
// is the 0x210-byte sound-upgrade record whose copy constructor and parser are
// recovered in the neighboring translation units.

struct Rva00606A80Item
{
	virtual void release( bool now );
	char m_audio[ 0x70 ];
};

struct Rva00606A80Member
{
	Rva00606A80Member( const Rva00606A80Member &other );
	Rva00606A80Item *m_items[ 0x6D ];
};

class AttributeModifierAuraUpdateModuleDataMemberB
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberB();

private:
	char m_body[ 0x0C ];
};

class RandomSoundSelectorMap
{
public:
	~RandomSoundSelectorMap();

private:
	char m_body[ 0x0C ];
};

class Rva00608FE0Element
{
public:
	~Rva00608FE0Element();

private:
	char m_pod0[ 0x30 ];
	AttributeModifierAuraUpdateModuleDataMemberB m_member30;
	AttributeModifierAuraUpdateModuleDataMemberB m_member3C;
	char m_member48[ 0x1B4 ];
	char m_member1FC[ 0x0C ];
	int m_field208;
	unsigned char m_field20C;
	char m_padding20D[ 3 ];
};

// ??1Rva00608FE0Element@@QAE@XZ
Rva00608FE0Element::~Rva00608FE0Element()
{
	reinterpret_cast<RandomSoundSelectorMap *>( m_member1FC )->~RandomSoundSelectorMap();
	Rva00606A80Item **items =
		reinterpret_cast<Rva00606A80Item **>( reinterpret_cast<char *>( this ) + 0x48 );
	for (int i = 0; i < 0x6D; ++i)
	{
		Rva00606A80Item *item = items[i];
		if (item != 0)
		{
			item->release(true);
			items[i] = 0;
		}
	}
}
