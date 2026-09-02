// ?bfmeApplyMemberFormationState@BfmeHordeContainOwner@@QAEXPAVObject@@@Z
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the horde-container hook that puts one member into or out of its
// formation pose, retail 0x0023D910.
//
// A null member returns at once. Otherwise one query on the container's own
// interface subobject -- the eleventh base at this+0xE4, the same adjustment the
// HordeContain destructor and the AOD large-unit hook both record -- picks the
// arm, and each arm makes the same call with the same argument through the
// member's interface at Object+0x200, differing only in the vtable slot. Retail
// hoists both the interface load and the `push 5` above the branch, which is
// what writing the two arms with the identical call shape produces.
//
// Each arm then clears the OTHER arm's model-condition bit and names its own,
// and the tail sets that bit if it is not already set. All three edits to the
// word at Object+0x12c go through Object::notifyModelConditionChanged, the same
// clear-and-notify idiom as the five 36-byte bodies in
// S3ModelConditionFlagClears.cpp; only bits 0x00080000 and 0x00100000 are ever
// touched, so nothing else about that word is knowable from these bytes.

typedef bool Bool;
typedef unsigned int UnsignedInt;

#define BFME_SLOT( N ) virtual int bfmeSlot##N( void ) = 0

class BfmeHordeMemberInterface
{
public:
	BFME_SLOT( 00 ); BFME_SLOT( 01 ); BFME_SLOT( 02 ); BFME_SLOT( 03 );
	BFME_SLOT( 04 ); BFME_SLOT( 05 ); BFME_SLOT( 06 ); BFME_SLOT( 07 );
	BFME_SLOT( 08 ); BFME_SLOT( 09 ); BFME_SLOT( 10 ); BFME_SLOT( 11 );
	virtual void bfmeLeaveFormationPose( int pose ) = 0;			///< slot 12
	virtual void bfmeEnterFormationPose( int pose ) = 0;			///< slot 13
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void notifyModelConditionChanged( void );						///< ILT 0x0002191D

	char m_bfmeHead[ 0x12c ];
	UnsignedInt m_bfmeModelConditionFlags;							///< retail this+0x12c
	char m_bfmeGap[ 0x200 - 0x130 ];
	BfmeHordeMemberInterface *m_bfmeMemberInterface;				///< retail this+0x200
};

class BfmeHordeContainView
{
public:
	BFME_SLOT( 00 ); BFME_SLOT( 01 ); BFME_SLOT( 02 ); BFME_SLOT( 03 );
	BFME_SLOT( 04 ); BFME_SLOT( 05 ); BFME_SLOT( 06 ); BFME_SLOT( 07 );
	BFME_SLOT( 08 ); BFME_SLOT( 09 ); BFME_SLOT( 10 ); BFME_SLOT( 11 );
	BFME_SLOT( 12 ); BFME_SLOT( 13 ); BFME_SLOT( 14 ); BFME_SLOT( 15 );
	BFME_SLOT( 16 ); BFME_SLOT( 17 ); BFME_SLOT( 18 ); BFME_SLOT( 19 );
	BFME_SLOT( 20 ); BFME_SLOT( 21 ); BFME_SLOT( 22 ); BFME_SLOT( 23 );
	BFME_SLOT( 24 ); BFME_SLOT( 25 ); BFME_SLOT( 26 ); BFME_SLOT( 27 );
	BFME_SLOT( 28 ); BFME_SLOT( 29 ); BFME_SLOT( 30 ); BFME_SLOT( 31 );
	BFME_SLOT( 32 ); BFME_SLOT( 33 ); BFME_SLOT( 34 ); BFME_SLOT( 35 );
	BFME_SLOT( 36 ); BFME_SLOT( 37 ); BFME_SLOT( 38 ); BFME_SLOT( 39 );
	BFME_SLOT( 40 ); BFME_SLOT( 41 ); BFME_SLOT( 42 ); BFME_SLOT( 43 );
	BFME_SLOT( 44 ); BFME_SLOT( 45 ); BFME_SLOT( 46 ); BFME_SLOT( 47 );
	BFME_SLOT( 48 ); BFME_SLOT( 49 ); BFME_SLOT( 50 ); BFME_SLOT( 51 );
	BFME_SLOT( 52 ); BFME_SLOT( 53 );
	virtual Bool bfmeIsFormationPosed( void ) = 0;					///< slot 54
};

class BfmeHordeContainOwner
{
public:
	void bfmeApplyMemberFormationState( Object *member );

private:
	BfmeHordeContainView *bfmeView( void )
	{
		return (BfmeHordeContainView *)( (char *)this + 0xe4 );
	}
};

// ?bfmeApplyMemberFormationState@BfmeHordeContainOwner@@QAEXPAVObject@@@Z
void BfmeHordeContainOwner::bfmeApplyMemberFormationState( Object *member )
{
	if ( member == 0 )
		return;

	UnsignedInt poseBit;

	if ( bfmeView()->bfmeIsFormationPosed() )
	{
		member->m_bfmeMemberInterface->bfmeEnterFormationPose( 5 );

		if ( member->m_bfmeModelConditionFlags & 0x00100000 )
		{
			member->m_bfmeModelConditionFlags &= ~0x00100000;
			member->notifyModelConditionChanged();
		}

		poseBit = 0x00080000;
	}
	else
	{
		member->m_bfmeMemberInterface->bfmeLeaveFormationPose( 5 );

		if ( member->m_bfmeModelConditionFlags & 0x00080000 )
		{
			member->m_bfmeModelConditionFlags &= ~0x00080000;
			member->notifyModelConditionChanged();
		}

		poseBit = 0x00100000;
	}

	if ( ( member->m_bfmeModelConditionFlags & poseBit ) == 0 )
	{
		member->m_bfmeModelConditionFlags |= poseBit;
		member->notifyModelConditionChanged();
	}
}
