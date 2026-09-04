// ?getSpecialObjectMax@SpecialAbilityUpdate@@QBEIXZ
// partial score=0.8 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x002A7D20: SpecialAbilityUpdate::getSpecialObjectMax.  Returns the
// module-data dword at +0x20C unless the special-power type (template+0x14
// after the same one-level override walk getSpecialPowerType uses) is 0x27
// and the target object at this+0xAC is present and is neither kind 6 nor
// kind 0x62.

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
	unsigned char m_unmodelled_1DC[ 0x20C - 0x1DC ];
	UnsignedInt m_maxSpecialObjects;
};

class SpecialAbilityUpdate
{
public:
	UnsignedInt getSpecialObjectMax() const;

private:
	unsigned int m_unmodelled_00;
	const SpecialAbilityUpdateModuleData *m_moduleData;
	unsigned char m_unmodelled_08[ 0xAC - 8 ];
	int m_targetID;
};

// ?getSpecialObjectMax@SpecialAbilityUpdate@@QBEIXZ
UnsignedInt SpecialAbilityUpdate::getSpecialObjectMax() const
{
	int id = m_targetID;
	const SpecialAbilityUpdateModuleData *md = m_moduleData;
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
		return md->m_maxSpecialObjects;
	if( !target )
		return md->m_maxSpecialObjects;
	if( target->isKindOf( KINDOF_6 ) )
		return md->m_maxSpecialObjects;
	if( target->isKindOf( KINDOF_62 ) )
		return md->m_maxSpecialObjects;
	return 0;
}
