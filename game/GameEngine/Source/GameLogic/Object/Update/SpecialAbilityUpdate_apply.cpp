// cl: /DNDEBUG /MD
// SpecialAbilityUpdate::rva002A7E90, retail 0x002A7E90 (141 bytes).
// Method identity unproven (Zero Hour has no match; sole caller is the
// anonymous 0x002AA9D0); owner from module data +0x210 PersistentPrepTime.
// The type test reads the template through the Zero Hour getFO() chain: the
// const friend_getFinalOverride inlines the non-const one once and only the
// recursive step stays a call (ILT 0x00048C61 -> 0x00097880), as in the landed
// SpecialAbilityUpdate::endPreparation at 0x002A7670.  The switch on
// getSpecialPowerType() is the Zero Hour idiom for this class and is what gives
// retail's ECX/EDX transfers of m_persistentPrepFrames.

enum SpecialPowerType { SPECIAL_POWER_TYPE_27 = 0x27 };
enum KindOfType { KINDOF_6 = 6, KINDOF_62 = 0x62 };
typedef unsigned int UnsignedInt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride( void )
	{
		if( m_nextOverride )
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	const Overridable *friend_getFinalOverride( void ) const
	{
		if( m_nextOverride )
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	SpecialPowerType getSpecialPowerType( void ) const { return getFO()->m_specialPowerType; }
	const SpecialPowerTemplate *getFO() const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }
	unsigned char m_unmodelled_08[ 0x14 - 8 ];
	SpecialPowerType m_specialPowerType;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	bool isKindOf( KindOfType t ) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID( int id );
};

extern GameLogic *TheGameLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[ 0x1D8 ];
	const SpecialPowerTemplate *m_specialPowerTemplate;
	unsigned char m_unmodelled_1DC[ 0x210 - 0x1DC ];
	UnsignedInt m_persistentPrepFrames;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate
{
public:
	void rva002A7E90();

private:
	unsigned int m_unmodelled_00;
	const SpecialAbilityUpdateModuleData *m_moduleData;
	unsigned char m_unmodelled_08[ 0xA8 - 8 ];
	UnsignedInt m_fieldA8;
	int m_targetID;
};

// ?rva002A7E90@SpecialAbilityUpdate@@QAEXXZ
void SpecialAbilityUpdate::rva002A7E90()
{
	const SpecialAbilityUpdateModuleData *md = m_moduleData;
	const SpecialPowerTemplate *tmpl = md->m_specialPowerTemplate;
	Object *target = TheGameLogic->findObjectByID( m_targetID );

	switch( tmpl->getSpecialPowerType() )
	{
		case SPECIAL_POWER_TYPE_27:
			if( target && ( target->isKindOf( KINDOF_6 ) || target->isKindOf( KINDOF_62 ) ) )
				m_fieldA8 = md->m_persistentPrepFrames;
			else
				m_fieldA8 = 0;
			break;
		default:
			m_fieldA8 = md->m_persistentPrepFrames;
			break;
	}
}
