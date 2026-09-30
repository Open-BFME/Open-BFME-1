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
	Bool bfmeBlocksFormationRefresh( void );

	char m_head[ 0x31e ];
	Bool m_refreshBlocked;
};

class BfmeHordeOwnerInterface
{
public:
	Bool bfmeBlocksFormationRefresh( void );
};

class BfmeHordeOwner
{
public:
	UnsignedInt bfmeGetFormationRefreshValue( void );

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

extern BfmeHordeGlobalData *TheBfmeHordeGlobalData;

class BfmeHordeContainOwner
{
public:
	void bfmeTryScheduleReformation( BfmeHordeMember *member,
		BfmeHordeRefreshContext *context );
	void bfmeRefreshFormation( void );

	char m_head[ 8 ];
	BfmeHordeOwner *m_owner;
	char m_gap0[ 0x1bc - 0x0c ];
	void *m_pendingRefresh;
	char m_gap1[ 0x1cc - 0x1c0 ];
	UnsignedInt m_refreshDelay;

	void rva0023fa50( void );
};

void BfmeHordeContainOwner::bfmeTryScheduleReformation(
	BfmeHordeMember *member, BfmeHordeRefreshContext *context )
{
	if ( m_refreshDelay != 0 )
		--m_refreshDelay;

	if ( m_refreshDelay > 0 )
		return;
	if ( context->m_data->m_memberCount <= 1 )
		return;
	if ( m_pendingRefresh != 0 )
		return;
	if ( member->bfmeBlocksFormationRefresh() )
		return;
	if ( member->m_refreshBlocked )
		return;
	if ( m_owner->m_refreshInterface != 0
		&& m_owner->m_refreshInterface->bfmeBlocksFormationRefresh() )
		return;

	BfmeHordeGlobalData *globalData = TheBfmeHordeGlobalData;
	BfmeHordeOwner *owner = m_owner;
	UnsignedInt threshold = globalData->m_refreshThreshold;
	UnsignedInt refreshValue = owner->bfmeGetFormationRefreshValue();
	threshold -= 20;
	if ( refreshValue < threshold )
		bfmeRefreshFormation();
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
