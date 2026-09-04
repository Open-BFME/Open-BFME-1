// ?bfmeApplyMemberFormationState@BfmeHordeContainOwner@@QAEXPAVObject@@@Z
// partial score=0.94 date=2026-09-03
// ?bfmeApplyMemberFormationState@BfmeHordeContainOwner@@QAEXPAVObject@@@Z
// partial score=0.9 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME5: HordeContain member formation-pose transition, retail 0x0023D910.

typedef bool Bool;
typedef unsigned int UnsignedInt;

#define BFME_SLOT( N ) virtual int bfmeSlot##N( void ) = 0

class BfmeHordeMemberInterface
{
public:
	BFME_SLOT( 00 ); BFME_SLOT( 01 ); BFME_SLOT( 02 ); BFME_SLOT( 03 );
	BFME_SLOT( 04 ); BFME_SLOT( 05 ); BFME_SLOT( 06 ); BFME_SLOT( 07 );
	BFME_SLOT( 08 ); BFME_SLOT( 09 ); BFME_SLOT( 10 ); BFME_SLOT( 11 );
	virtual void bfmeLeaveFormationPose( int pose ) = 0;
	virtual void bfmeEnterFormationPose( int pose ) = 0;
};

class Object
{
public:
	void notifyModelConditionChanged( void );

	char m_bfmeHead[ 0x12c ];
	UnsignedInt m_bfmeModelConditionFlags;
	char m_bfmeGap[ 0x200 - 0x130 ];
	BfmeHordeMemberInterface *m_bfmeMemberInterface;
};

static __forceinline void bfmeSetFormationPoseFlag( Object *member,
	UnsignedInt &flags, UnsignedInt &bit )
{
	if ( ( bit & flags ) == 0 )
	{
		member->m_bfmeModelConditionFlags = ( flags |= bit );
		bit = flags;
		member->notifyModelConditionChanged();
	}
}

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
	virtual Bool bfmeIsFormationPosed( void ) = 0;
};

#undef BFME_SLOT

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

void BfmeHordeContainOwner::bfmeApplyMemberFormationState( Object *member )
{
	UnsignedInt poseBit;
	UnsignedInt flags;

	if ( member == 0 )
		return;
	if ( bfmeView()->bfmeIsFormationPosed() )
	{
		member->m_bfmeMemberInterface->bfmeEnterFormationPose( 5 );

		flags = member->m_bfmeModelConditionFlags;
		if ( flags & 0x00100000 )
		{
			flags &= ~0x00100000;
			member->m_bfmeModelConditionFlags = flags;
			member->notifyModelConditionChanged();
		}

		poseBit = 0x00080000;
	}
	else
	{
		member->m_bfmeMemberInterface->bfmeLeaveFormationPose( 5 );

		flags = member->m_bfmeModelConditionFlags;
		if ( flags & 0x00080000 )
		{
			flags &= ~0x00080000;
			member->m_bfmeModelConditionFlags = flags;
			member->notifyModelConditionChanged();
		}

		poseBit = 0x00100000;
	}

	flags = member->m_bfmeModelConditionFlags;
	bfmeSetFormationPoseFlag( member, flags, poseBit );
}
