// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME widened WeaponTemplate::getAttackRange.  The source object and its
// position are part of the retail call, unlike the reference signature.

typedef int Int;
typedef float Real;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool bfmeGetBonus( Int which, Real *value ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponBonus
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponTemplate
{
private:
	Real bfmeRangeBase( const Object *source, const WeaponBonus &bonus,
		Real sourceZ ) const;

public:
	Real getAttackRange( const Object *source, const WeaponBonus &bonus,
		const Coord3D *sourcePos ) const;
};

Real WeaponTemplate::getAttackRange( const Object *source,
	const WeaponBonus &bonus, const Coord3D *sourcePos ) const
{
	// Retail reuses the now-dead source-position parameter slot for the range
	// temporary.  Keeping that lifetime explicit preserves the two stack slots
	// without introducing a frame or an assembly body.
	Real *rangeStorage = reinterpret_cast<Real *>( &sourcePos );
	*rangeStorage = bfmeRangeBase( source, bonus, -sourcePos->z );
	Real rangeBonus;
	rangeBonus = 0.0f;
	if( source )
	{
		if( source->bfmeGetBonus( 6, &rangeBonus ) )
			return ( rangeBonus + 1.0f ) * *rangeStorage;
	}
	return *rangeStorage;
}
