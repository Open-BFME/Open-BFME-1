// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PlayerHealSpecialPower module-data constructor.
//
// The named friend_newModuleData factory at retail 0x00121480 allocates 0x238
// bytes and calls this constructor.  The shared SpecialPower module-data base
// occupies the first 0x210 bytes.  Retail then initializes the scalar healing
// parameters and the six-word object filter at +0x218.

class BfmeSpecialPowerModuleDataBase
{
public:
	BfmeSpecialPowerModuleDataBase();
	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[ 0x210 - 4 ];
};

struct PlayerHealObjectFilter
{
	unsigned int m_words[ 6 ];

	PlayerHealObjectFilter()
	{
		for ( int i = 0; i != 6; ++i )
			m_words[ i ] = 0;
	}

	void clear()
	{
		for ( int i = 0; i != 6; ++i )
			m_words[ i ] = 0;
	}
};

class PlayerHealSpecialPowerModuleData : public BfmeSpecialPowerModuleDataBase
{
public:
	PlayerHealSpecialPowerModuleData();

private:
	unsigned int m_healAmount;       // +0x210
	float m_healRadius;               // +0x214
	PlayerHealObjectFilter m_filter;  // +0x218
	unsigned int m_affectsAllies;     // +0x230
	unsigned int m_affectsSelf;       // +0x234
};

// ??0PlayerHealSpecialPowerModuleData@@QAE@XZ
PlayerHealSpecialPowerModuleData::PlayerHealSpecialPowerModuleData()
{
	m_healAmount = 0;
	m_healRadius = 100.0f;
	m_filter.clear();
	m_affectsAllies = 0;
	m_affectsSelf = 0;
}
