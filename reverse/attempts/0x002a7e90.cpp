// ?apply@SpecialAbilityUpdate@@QAEXXZ
// partial score=0.97 date=2026-09-04
// cl: /DNDEBUG /MD

enum SpecialPowerType { SPECIAL_POWER_TYPE_27 = 0x27 };
enum KindOfType { KINDOF_6 = 6, KINDOF_62 = 0x62 };
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride( void );
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_08[ 0x14 - 8 ];
	SpecialPowerType m_specialPowerType;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	bool isKindOf( KindOfType t ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID( int id );
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[ 0x1D8 ];
	const SpecialPowerTemplate *m_specialPowerTemplate;
	unsigned char m_unmodelled_1DC[ 0x210 - 0x1DC ];
	UnsignedInt m_field210;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
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
		UnsignedInt max = md->m_field210;
		m_fieldA8 = max;
		return;
	}
	if( target &&
		( target->isKindOf( KINDOF_6 ) || target->isKindOf( KINDOF_62 ) ) )
	{
		UnsignedInt max = md->m_field210;
		m_fieldA8 = max;
		return;
	}

	m_fieldA8 = 0;
}
