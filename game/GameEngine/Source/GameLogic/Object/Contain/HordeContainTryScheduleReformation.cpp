// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: delayed HordeContain formation refresh, retail 0x0023F9A0,
// and its guarded caller, retail 0x0023FA50.

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

typedef bool Bool;
typedef unsigned int UnsignedInt;

class BfmeHordeMember
{
public:
	char m_head[ 0x31e ];
	Bool m_refreshBlocked;
};

class BfmeHordeOwnerInterface
{
public:
};

class BfmeHordeOwner
{
public:
	char m_head[ 0x1f8 ];
	BfmeHordeOwnerInterface *m_refreshInterface;
	char m_gap0[ 0x204 - 0x1fc ];
	BfmeHordeMember *m_member;
};

class BfmeHordeRefreshContextData
{
public:
	char m_head[ 0x28 ];
	int m_memberCount;
};

class BfmeHordeRefreshContext
{
public:
	char m_head[ 0x210 ];
	BfmeHordeRefreshContextData *m_data;
};

class BfmeHordeGlobalData
{
public:
	char m_head[ 0x3c ];
	UnsignedInt m_refreshThreshold;
};

// Retail's global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined once
// in game/GameEngine/Source/GameLogic/System/GameLogic.cpp.  This TU keeps its
// own BfmeHordeGlobalData view of the pointee and casts at the use.
class GameLogic;
extern GameLogic *TheGameLogic;

class BfmeHordeContainOwner
{
public:
	void bfmeTryScheduleReformation( BfmeHordeMember *member,
		BfmeHordeRefreshContext *context );

	char m_head[ 8 ];
	BfmeHordeOwner *m_owner;
	char m_gap0[ 0x1bc - 0x0c ];
	void *m_pendingRefresh;
	char m_gap1[ 0x1cc - 0x1c0 ];
	UnsignedInt m_refreshDelay;

	void rva0023fa50( void );
};

// The four callees this body reaches are all called in retail through the
// five-byte ILT thunks at RVA 0x00044774, 0x00024357, 0x00023727 and
// 0x0001798B, which the ledger owns as ?j_00044774@@YAXXZ,
// ?j_00024357@@YAXXZ, ?j_00023727@@YAXXZ and ?j_0001798b@@YAXXZ (the
// game/gen_small/thunks_*.cpp files).  The pins that gave the methods their
// descriptive names sit on those same thunk addresses, so the calls are
// respelled to the thunks themselves and dispatched through a member-pointer
// union: the receiver still arrives in ecx and no argument moves, so every
// call displacement stays where retail has it.
extern void j_00044774();
extern void j_00024357();
extern void j_00023727();
extern void j_0001798b();

typedef Bool (BfmeHordeMember::*BlocksFormationRefreshCall)();
typedef Bool (BfmeHordeOwnerInterface::*BlocksFormationRefreshCall2)();
typedef UnsignedInt (BfmeHordeOwner::*GetFormationRefreshValueCall)();
typedef void (BfmeHordeContainOwner::*RefreshFormationCall)();

void BfmeHordeContainOwner::bfmeTryScheduleReformation(
	BfmeHordeMember *member, BfmeHordeRefreshContext *context )
{
	union
	{
		void ( *raw )();
		BlocksFormationRefreshCall member;
	} memberBlocks;
	union
	{
		void ( *raw )();
		BlocksFormationRefreshCall2 member;
	} interfaceBlocks;
	union
	{
		void ( *raw )();
		GetFormationRefreshValueCall member;
	} refreshValue;
	union
	{
		void ( *raw )();
		RefreshFormationCall member;
	} refreshFormation;
	memberBlocks.raw = j_00044774;
	interfaceBlocks.raw = j_00024357;
	refreshValue.raw = j_00023727;
	refreshFormation.raw = j_0001798b;

	if ( m_refreshDelay != 0 )
		--m_refreshDelay;

	if ( m_refreshDelay > 0 )
		return;
	if ( context->m_data->m_memberCount <= 1 )
		return;
	if ( m_pendingRefresh != 0 )
		return;
	if ( ( member->*memberBlocks.member )() )
		return;
	if ( member->m_refreshBlocked )
		return;
	if ( m_owner->m_refreshInterface != 0
		&& ( m_owner->m_refreshInterface->*interfaceBlocks.member )() )
		return;

	BfmeHordeGlobalData *globalData =
		reinterpret_cast<BfmeHordeGlobalData *>(TheGameLogic);
	BfmeHordeOwner *owner = m_owner;
	UnsignedInt threshold = globalData->m_refreshThreshold;
	UnsignedInt value = ( owner->*refreshValue.member )();
	threshold -= 20;
	if ( value < threshold )
		( this->*refreshFormation.member )();
}

// Retail keeps the owner test after the ternary already proved it; the
// barrier stops MSVC 7.1 threading the first test into the second.
void BfmeHordeContainOwner::rva0023fa50( void )
{
	BfmeHordeOwner *owner = m_owner;
	BfmeHordeMember *member = owner ? owner->m_member : 0;
	_ReadWriteBarrier();
	if ( member && owner )
		bfmeTryScheduleReformation( member,
			(BfmeHordeRefreshContext *)owner );
}
