// cl: /DNDEBUG /MD /EHsc

// DominateEnemySpecialPowerModuleData's constructor, retail 0x0025AC90.
//
// The base is SpecialAbilityUpdateModuleData, whose constructor the ledger
// already names at 0x002A5AA0. That corroborates the module itself:
// DominateEnemySpecialPower's constructor forwards to SpecialAbilityUpdate's,
// not to SpecialPowerModule's, and the data class follows the same line.
//
// The base runs to +0x254, where this class's three zeroed dwords sit. Retail
// writes them before its own vftable pointer, which is the scheduler moving one
// cleared register's three stores ahead of an independent immediate store.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdateModuleData
{
public:
	SpecialAbilityUpdateModuleData();

	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[ 0x254 - 4 ];
};

class DominateEnemySpecialPowerModuleData : public SpecialAbilityUpdateModuleData
{
public:
	DominateEnemySpecialPowerModuleData();

private:
	int m_unmodelled_254;					// +0x254
	int m_unmodelled_258;					// +0x258
	int m_unmodelled_25C;					// +0x25C
};

DominateEnemySpecialPowerModuleData::DominateEnemySpecialPowerModuleData()
	: m_unmodelled_254( 0 ), m_unmodelled_258( 0 ), m_unmodelled_25C( 0 )
{
}
