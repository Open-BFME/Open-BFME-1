// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME WeaponTemplate::getAttackRange core: the ZH unbonused range
// (m_attackRange * bonus RANGE - UNDERSIZE, clamped at zero) plus a BFME
// height cutoff at +0x52C, then the source's attribute-modifier range bonus.

#include <math.h>

typedef int Int;
typedef float Real;
typedef bool Bool;

extern float g_bfmeOffsetDF;			// retail 0x01098AD4
extern const float BfmeZeroRange;		// retail 0x01075350

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool getAttributeModifierBonus( Int which, Real *value ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponBonus
{
public:
	enum Field
	{
		DAMAGE = 0,
		RADIUS,
		RANGE
	};
	Real getField( Field f ) const { return m_field[f]; }

private:
	Real m_field[6];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponTemplate
{
private:
	Real bfmeRangeBase( const Object *source, const WeaponBonus &bonus,
		Real heightDifference ) const;

	Real unbonusedRange( const WeaponBonus &bonus, Real heightDifference ) const
	{
		Real range = m_attackRange * bonus.getField( WeaponBonus::RANGE ) - g_bfmeOffsetDF;
		if( m_bfmeMaxHeightDifference052C > BfmeZeroRange
			&& fabs( heightDifference ) > m_bfmeMaxHeightDifference052C )
			range = 0.0f;
		else if( range < BfmeZeroRange )
			range = 0.0f;
		return range;
	}

	char m_pad0[0x14];
	Real m_attackRange;						// +0x14
	char m_pad18[0x52C - 0x18];
	Real m_bfmeMaxHeightDifference052C;		// +0x52C
};

Real WeaponTemplate::bfmeRangeBase( const Object *source,
	const WeaponBonus &bonus, Real heightDifference ) const
{
	Real result = unbonusedRange( bonus, heightDifference );
	Real rangeBonus = 0.0f;
	if( source && source->getAttributeModifierBonus( 6, &rangeBonus ) )
		result *= rangeBonus + 1.0f;
	return result;
}
