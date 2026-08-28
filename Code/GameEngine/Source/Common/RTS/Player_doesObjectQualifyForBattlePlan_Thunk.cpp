// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?doesObjectQualifyForBattlePlan@Player@@QBE_NPAVObject@@@Z: Code/GameEngine/Source/Common/RTS/Player.cpp
// Open-BFME5: Player::doesObjectQualifyForBattlePlan, retail 0x000C9AB0,
// zh_sweep packet 000c9ab0.
//
// The reference body unchanged. Three offsets separated it from retail when
// compiled inside Player.cpp, and each names something:
//
//  - m_battlePlanBonuses is at [this+0x70], not the vendored +0x5C.
//  - m_validKindOf is at +0x14 inside BattlePlanBonuses, not +0x18, so one of
//    the five scalars the reference declares ahead of it is absent in BFME.
//  - m_invalidKindOf is at +0x2C, not +0x28. A KindOfMaskType is 16 bytes here
//    -- BitFlags<116>, as Thing::isAnyKindOf's own matched row already fixes --
//    so the two masks are 0x18 apart with eight bytes between them that the
//    reference does not have.
//
// Only the offsets are proven, so the fields that account for them are carried
// as unnamed runs rather than guessed at. isAnyKindOf is inherited from Thing
// and called with no this-adjust, which puts Thing at offset 0 in Object.

typedef bool Bool;
typedef int Int;

enum { KINDOF_COUNT = 116 };

// 16 bytes, matching the BitFlags<116> that Thing::isAnyKindOf is matched
// against; only the width matters here.
template <int numBits>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
private:
	unsigned char m_bits[16];
};

typedef BitFlags<KINDOF_COUNT> KindOfMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isAnyKindOf( const KindOfMaskType &mask ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BattlePlanUpdate.h
class BattlePlanBonuses
{
public:
	unsigned char	m_unreconstructed_00[0x14];			///< vptr and four words
	KindOfMaskType	m_validKindOf;						///< +0x14
	unsigned char	m_unreconstructed_24[0x2C - 0x24];	///< eight bytes the reference does not have
	KindOfMaskType	m_invalidKindOf;					///< +0x2C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Bool doesObjectQualifyForBattlePlan( Object *obj ) const;

private:
	unsigned char m_unreconstructed_00[0x70];
	BattlePlanBonuses *m_battlePlanBonuses;				///< +0x70
};

// ?doesObjectQualifyForBattlePlan@Player@@QBE_NPAVObject@@@Z
Bool Player::doesObjectQualifyForBattlePlan( Object *obj ) const
{
	if( m_battlePlanBonuses && obj )
	{
		if( obj->isAnyKindOf( m_battlePlanBonuses->m_validKindOf ) )
		{
			if( !obj->isAnyKindOf( m_battlePlanBonuses->m_invalidKindOf ) )
			{
				return true;
			}
		}
	}
	return false;
}
