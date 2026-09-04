// ?getSpecialObjectMax@SpecialAbilityUpdate@@QBEIXZ
// partial score=0.83 date=2026-09-04
// ?getSpecialObjectMax@SpecialAbilityUpdate@@QBEIXZ
// partial score=0.83 date=2026-09-04
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
	unsigned char m_unmodelled_1DC[ 0x20C - 0x1DC ];
	UnsignedInt m_maxSpecialObjects;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
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

	goto test_special;

return_max:
	return md->m_maxSpecialObjects;

test_special:
	if( tmpl->m_specialPowerType != SPECIAL_POWER_TYPE_27 )
		goto return_max;
	if( !target )
		goto return_max;
	if( target->isKindOf( KINDOF_6 ) )
		goto return_max;
	if( target->isKindOf( KINDOF_62 ) )
		goto return_max;
	return 0;
}
