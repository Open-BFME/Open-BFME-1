// ?apply@SpecialAbilityUpdate@@QAEXXZ
// partial score=0.97 date=2026-09-04
// ?apply@SpecialAbilityUpdate@@QAEXXZ
// partial score=0.8 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x002A7E90: stores module-data+0x210 into this+0xA8 unless the
// special-power type is 0x27 and the target is missing or neither kind 6
// nor kind 0x62.

enum SpecialPowerType { SPECIAL_POWER_TYPE_27 = 0x27 };
enum KindOfType { KINDOF_6 = 6, KINDOF_62 = 0x62 };
typedef unsigned int UnsignedInt;

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride( void );
	Overridable *m_nextOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_08[ 0x14 - 8 ];
	SpecialPowerType m_specialPowerType;
};

class Thing
{
public:
	bool isKindOf( KindOfType t ) const;
};

class Object : public Thing
{
};

class GameLogic
{
public:
	Object *findObjectByID( int id );
};

extern GameLogic *TheGameLogic;

class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[ 0x1D8 ];
	const SpecialPowerTemplate *m_specialPowerTemplate;
	unsigned char m_unmodelled_1DC[ 0x210 - 0x1DC ];
	volatile UnsignedInt m_field210;
};

class SpecialAbilityUpdate
{
public:
	void apply();

private:
	unsigned int m_unmodelled_00;
	const SpecialAbilityUpdateModuleData *m_moduleData;
	unsigned char m_unmodelled_08[ 0xA8 - 8 ];
	UnsignedInt m_fieldA8;
	int m_targetID;
};

// ?apply@SpecialAbilityUpdate@@QAEXXZ
void SpecialAbilityUpdate::apply()
{
	int id = m_targetID;
	const SpecialAbilityUpdateModuleData *md = m_moduleData;
	const UnsignedInt *maxField = &md->m_field210;
	const SpecialPowerTemplate *tmpl = md->m_specialPowerTemplate;
	Object *target = TheGameLogic->findObjectByID( id );

	Overridable *o = tmpl->m_nextOverride;
	if( o )
	{
		if( o->m_nextOverride )
			o = o->m_nextOverride->friend_getFinalOverride();
		tmpl = (const SpecialPowerTemplate *)o;
	}

	if( tmpl->m_specialPowerType != SPECIAL_POWER_TYPE_27 )
	{
		m_fieldA8 = *maxField;
		return;
	}
	if( !target )
		goto store_zero;
	if( target->isKindOf( KINDOF_6 ) )
		goto store_field;
	if( target->isKindOf( KINDOF_62 ) )
		goto store_field;
	goto store_zero;

	store_field:
		UnsignedInt max = *maxField;
		m_fieldA8 = max;
	return;

store_zero:
	m_fieldA8 = 0;
}
