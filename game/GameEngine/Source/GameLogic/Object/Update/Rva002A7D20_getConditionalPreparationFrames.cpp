// cl: /DNDEBUG /MD
// Rva002A7D20::getConditionalPreparationFrames, retail 0x002A7D20 (105 bytes).
// Owner is the SpecialAbilityUpdate family by evidence, not by name: the module
// data at +4 is read at +0x1D8 (m_specialPowerTemplate) and +0x20C
// (m_preparationFrames), both witnessed by the SpecialAbilityUpdateModuleData
// FieldParse table at 0x00CC32F8, and +0xAC is m_targetID as in the landed
// SpecialAbilityUpdate::startFacing (0x002AA850).  The method name only
// describes the body.  The type test uses the Zero Hour getFO() chain written as
// a switch, as in the landed SpecialAbilityUpdate_apply.cpp neighbour at
// 0x002A7E90.
//
// Retail keeps one m_preparationFrames return block right after the null-target
// test and both kind tests branch back into it.  MSVC 7.1 merges identical
// memory-load returns into the last copy (the tail) before layout; the
// _ReadWriteBarrier() in the null-target arm (no instruction, no relocation)
// keeps that copy apart until codegen cross-jumping folds the other returns back
// into it.  docs/shape_levers.md: barrier intrinsics and duplicate return tails.

extern "C" void _ReadWriteBarrier( void );

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
	SpecialPowerType getSpecialPowerType( void ) const { return getFO()->m_type; }
	const SpecialPowerTemplate *getFO() const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }
	unsigned char m_unmodelled_08[ 0x14 - 8 ];
	SpecialPowerType m_type;
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
	unsigned char m_unmodelled_1DC[ 0x20C - 0x1DC ];
	UnsignedInt m_preparationFrames;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class Rva002A7D20
{
public:
	UnsignedInt getConditionalPreparationFrames() const;

private:
	unsigned int m_unmodelled_00;
	const SpecialAbilityUpdateModuleData *m_moduleData;
	unsigned char m_unmodelled_08[ 0xAC - 8 ];
	int m_targetID;
};

// ?getConditionalPreparationFrames@Rva002A7D20@@QBEIXZ
UnsignedInt Rva002A7D20::getConditionalPreparationFrames() const
{
	const SpecialAbilityUpdateModuleData *md = m_moduleData;
	const SpecialPowerTemplate *tmpl = md->m_specialPowerTemplate;
	Object *target = TheGameLogic->findObjectByID( m_targetID );

	switch( tmpl->getSpecialPowerType() )
	{
		case SPECIAL_POWER_TYPE_27:
			if( !target )
			{
				_ReadWriteBarrier();
				return md->m_preparationFrames;
			}
			if( target->isKindOf( KINDOF_6 ) || target->isKindOf( KINDOF_62 ) )
				return md->m_preparationFrames;
			return 0;
		default:
			return md->m_preparationFrames;
	}
}
