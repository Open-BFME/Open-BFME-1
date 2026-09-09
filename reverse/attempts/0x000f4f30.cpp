// ?updateState@Team@@QAEXXZ
// partial score=0.66 date=2026-09-09
// ?updateState@Team@@QAEXXZ
// Partial source candidate for Open-BFME5 Team::updateState at 0x000F4F30.
// This is a drop-in view/body fragment for the existing Team.cpp TU, not a
// claimed match.  The retail body has a 1280-byte boundary and a named call
// from TeamPrototype::updateState at 0x000F71C0.
//
// The view offsets below are independently read from the BFME constructor and
// the retail updateState body.  The strings use the real AsciiString/StringBase
// implementation already selected by Team.cpp; no GameSpyGroupRoom stand-in
// is involved.  The body intentionally leaves the retail team-events-list
// helper unresolved, which is one reason this candidate is partial.

// These declarations are already present in Team.cpp and are repeated here
// as the dependencies of the body fragment.  Keep them TU-local when applying
// this candidate; do not turn them into shared ABI declarations.
struct BfmeUpdateStateTemplateInfo
{
	unsigned char m_unmodelled_000[ 0x6c ];
	AsciiString m_scriptOnCreate;                         // +0x6c
	AsciiString m_eventsList;                             // +0x70
	AsciiString m_scriptOnIdle;                           // +0x74
	Int m_initialIdleSeconds;                             // +0x78
	AsciiString m_scriptOnEnemySighted;                   // +0x7c
	AsciiString m_scriptOnAllClear;                       // +0x80
	AsciiString m_scriptOnUnitDestroyed;                  // +0x84
	AsciiString m_scriptOnDestroyed;                      // +0x88
	Real m_destroyedThreshold;                             // +0x8c
};

struct BfmeUpdateStateTeamFields
{
	void *m_vptr;
	TeamPrototype *m_proto;                               // +0x04
	UnsignedInt m_id;                                     // +0x08
	void *m_memberListHead;                               // +0x0c
	unsigned char m_unmodelled_010[ 0x30 - 0x10 ];
	unsigned char m_enteredOrExited;                      // +0x30
	unsigned char m_active;                               // +0x31
	unsigned char m_created;                              // +0x32
	unsigned char m_eventsReady;                          // +0x33
	unsigned char m_checkEnemySighted;                    // +0x34
	unsigned char m_seeEnemy;                             // +0x35
	unsigned char m_prevSeeEnemy;                         // +0x36
	unsigned char m_wasIdle;                              // +0x37
	Int m_destroyThreshold;                               // +0x38
	Int m_curUnits;                                       // +0x3c
	unsigned char m_unmodelled_040[ 0xe4 - 0x40 ];
	unsigned char m_flagsE4[ 4 ];                         // +0xe4..+0xe7
};

static BfmeUpdateStateTemplateInfo *bfmeUpdateStateInfo( Team *team )
{
	BfmeUpdateStateTeamFields *fields = (BfmeUpdateStateTeamFields *)team;
	return (BfmeUpdateStateTemplateInfo *)((char *)fields->m_proto + 0x12c);
}

static BfmeDlinkIterator<BfmeObjectDlinkObject> bfmeUpdateStateMembers( Team *team )
{
	return ((BfmeTeamMemberListView *)team)->iterate();
}

// ?updateState@Team@@QAEXXZ
void Team::updateState( void )
{
	BfmeUpdateStateTeamFields *fields = (BfmeUpdateStateTeamFields *)this;
	fields->m_enteredOrExited = 0;
	if (!fields->m_proto || !fields->m_active)
		return;
	BfmeUpdateStateTemplateInfo *pInfo = bfmeUpdateStateInfo( this );

	if (fields->m_created && fields->m_flagsE4[ 3 ] == 0 && isIdle())
	{
		fields->m_created = 0;
		fields->m_eventsReady = 1;
		if (pInfo->m_scriptOnCreate.isNotEmpty())
			TheScriptEngine->runScript( pInfo->m_scriptOnCreate, this );

		if (pInfo->m_scriptOnDestroyed.isNotEmpty())
		{
			for (BfmeDlinkIterator<BfmeObjectDlinkObject> iter = bfmeUpdateStateMembers( this );
				!iter.done(); iter.advance())
				++fields->m_curUnits;
			fields->m_destroyThreshold = fields->m_curUnits -
				(fields->m_curUnits * pInfo->m_destroyedThreshold);
			if (fields->m_destroyThreshold > fields->m_curUnits - 1)
				fields->m_destroyThreshold = fields->m_curUnits - 1;
			if (fields->m_destroyThreshold < 0)
				fields->m_destroyThreshold = 0;
		}
	}

	if (fields->m_eventsReady && fields->m_checkEnemySighted)
	{
		fields->m_prevSeeEnemy = fields->m_seeEnemy;
		fields->m_seeEnemy = 0;
		Bool anyAliveInTeam = false;
		for (BfmeDlinkIterator<BfmeObjectDlinkObject> iter = bfmeUpdateStateMembers( this );
			!iter.done(); iter.advance())
		{
			Object *object = (Object *)iter.cur();
			if (object->isEffectivelyDead())
				continue;

			PartitionFilterRelationship filterTeam( object,
				PartitionFilterRelationship::ALLOW_ENEMIES );
			PartitionFilterAlive filterAlive;
			PartitionFilterSameMapStatus filterMapStatus( object );
			PartitionFilter *filters[] = { &filterTeam, &filterAlive, &filterMapStatus, NULL };
			Real visionRange = object->getVisionRange();
			anyAliveInTeam = true;
			if (ThePartitionManager->getClosestObject( object, visionRange, FROM_CENTER_2D, filters ))
			{
				fields->m_seeEnemy = 1;
				break;
			}
		}
		if (anyAliveInTeam && fields->m_prevSeeEnemy != fields->m_seeEnemy)
		{
			if (fields->m_seeEnemy)
				TheScriptEngine->runScript( pInfo->m_scriptOnEnemySighted, this );
			else
				TheScriptEngine->runScript( pInfo->m_scriptOnAllClear, this );
		}
	}

	if (pInfo->m_scriptOnDestroyed.isNotEmpty())
	{
		Int prevUnits = fields->m_curUnits;
		fields->m_curUnits = 0;
		for (BfmeDlinkIterator<BfmeObjectDlinkObject> iter = bfmeUpdateStateMembers( this );
			!iter.done(); iter.advance())
		{
			Object *object = (Object *)iter.cur();
			if (!object->isEffectivelyDead())
				++fields->m_curUnits;
		}
		if (fields->m_curUnits != prevUnits && fields->m_curUnits <= fields->m_destroyThreshold)
		{
			TheScriptEngine->runScript( pInfo->m_scriptOnDestroyed, this );
			fields->m_destroyThreshold = -1;
		}
	}

	if (pInfo->m_scriptOnIdle.isNotEmpty())
	{
		Bool isIdleNow = true;
		Bool anyAliveInTeam = false;
		for (BfmeDlinkIterator<BfmeObjectDlinkObject> iter = bfmeUpdateStateMembers( this );
			!iter.done(); iter.advance())
		{
			Object *object = (Object *)iter.cur();
			if (object->isEffectivelyDead())
				continue;
			AIUpdateInterface *ai = object->getAIUpdateInterface();
			if (!ai)
				continue;
			anyAliveInTeam = true;
			if (!ai->isIdle())
				isIdleNow = false;
		}
		if (anyAliveInTeam && isIdleNow && fields->m_wasIdle)
			TheScriptEngine->runScript( pInfo->m_scriptOnIdle, this );
		fields->m_wasIdle = isIdleNow;
	}
}
