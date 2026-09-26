// cl: /DNDEBUG /MD /O2 /EHsc

// WeaponBonusSet::parseWeaponBonusSet (0x001E1C20) and the WeaponBonus::setField
// it inlines (0x001E0B00), out of Weapon.cpp because
// retail calls INI::scanPercentToReal (0x00852740) where Weapon.cpp's INI shim
// inlines it, and Weapon.cpp needs that shim's inline scanInt elsewhere.
//
// BFME's WeaponBonusSet is WeaponBonus[0x16] at offset 0 (no vtable), and a
// WeaponBonus has six fields, not Zero Hour's five: retail indexes
// this + (wb*6 + wf)*4, and TheWeaponBonusFieldNames (0x012AD50C) lists
// DAMAGE, RADIUS, RANGE, RATE_OF_FIRE, PRE_ATTACK, FIRING. The same layout
// is matched in WeaponBonusSet_bfmeApplyBonuses.cpp.

typedef int Int;
typedef float Real;
typedef const char *const *ConstCharPtrArray;

// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	static Int scanIndexList( const char *token, ConstCharPtrArray nameList );
	static Real scanPercentToReal( const char *token );
};

extern const char *TheWeaponBonusNames[];
extern const char *TheWeaponBonusFieldNames[];

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponBonus
{
public:
	enum Field
	{
		DAMAGE = 0,
		RADIUS,
		RANGE,
		RATE_OF_FIRE,
		PRE_ATTACK,
		FIRING,

		FIELD_COUNT
	};

	void setField( Field f, Real v );

private:
	Real m_field[FIELD_COUNT];
};

class WeaponBonusSet
{
public:
	void parseWeaponBonusSet( INI *ini );

private:
	WeaponBonus m_bonus[0x16];
};

// ?setField@WeaponBonus@@QAEXW4Field@1@M@Z
// Out of line in retail (0x001E0B00) and inlined into the parser below, so it
// is an ordinary member defined here, not Zero Hour's in-class inline.
void WeaponBonus::setField( Field f, Real v )
{
	m_field[f] = v;
}

// ?parseWeaponBonusSet@WeaponBonusSet@@QAEXPAVINI@@@Z
void WeaponBonusSet::parseWeaponBonusSet( INI *ini )
{
	Int wb = INI::scanIndexList( ini->getNextToken(), TheWeaponBonusNames );
	WeaponBonus::Field wf = (WeaponBonus::Field)INI::scanIndexList( ini->getNextToken(), TheWeaponBonusFieldNames );
	m_bonus[wb].setField( wf, INI::scanPercentToReal( ini->getNextToken() ) );
}
