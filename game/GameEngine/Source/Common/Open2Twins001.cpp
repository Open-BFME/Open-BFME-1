// cl: /DNDEBUG /MD /EHsc
//
// Seven bodies landed as relocation-blind twins of C++ this tree already
// builds.  Each was found by normalising every gen_asm dump and every landed
// body with relocation slots blanked and matching the two: a dump whose
// normalised bytes equal a landed body differs from it in NOTHING but the
// globals and callees it names, so the source that produced one produces the
// other once those names are substituted.
//
// The four guard walks below are twins of
// game/GameEngine/Source/GameLogic/AI/AIGroup_groupGuardPosition.cpp
// (0x00156840) and differ from it in exactly one slot each: the command
// interface they call.  The three notice senders are twins of
// game/GameEngine/Source/Common/BfmeConv424.cpp (0x0051B360) and differ in
// exactly one slot each: the string literal they send.

struct Coord3D;

#include "../../Include/Common/Enums/GuardMode.h"
#include "../GameLogic/command_source_type.h"

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;
	BfmeListNodeBase *m_bfmePrev;
};


// ---------------------------------------------------------------------------
// 0x00156070 -- guard walk through the command interface at ILT 0x00013D68.

class Open2Commands156070
{
public:
	void aiGuardPosition( const Coord3D *pos, ::GuardMode mode,
			::CommandSourceType cmdSource );
};

class Open2GroupAI156070
{
public:
	char m_head[ 0x20 ];
	Open2Commands156070 m_commands;
};

class Open2Member156070
{
public:
	char m_head[ 0x204 ];
	Open2GroupAI156070 *m_ai;
};

struct Open2MemberNode156070 : public BfmeListNodeBase
{
	Open2Member156070 *m_value;
};

class Team;

// Retail TEAM_ATTACK_TEAM: the matched ScriptActions::doAttack (0x002F2840) calls this body
// as groupAttackTeam (identity_evidence/00156070-aigroup-groupattackteam-matched-caller.md).
class AIGroup
{
public:
	void groupAttackTeam( const Team *team, int maxShotsToFire, ::CommandSourceType cmdSource );

private:
	char m_head[ 4 ];
	BfmeListNodeBase *m_memberList;
};

// @?groupAttackTeam@AIGroup@@QAEXPBVTeam@@HW4CommandSourceType@@@Z 0x00156070
void AIGroup::groupAttackTeam( const Team *team, int maxShotsToFire, ::CommandSourceType cmdSource )
{
	if( !team )
		return;

	for( BfmeListNodeBase *it = m_memberList->m_bfmeNext;
			it != m_memberList;
			it = it->m_bfmeNext )
	{
		Open2GroupAI156070 *ai = ( (Open2MemberNode156070 *)it )->m_value->m_ai;

		if( ai )
			ai->m_commands.aiGuardPosition( (const Coord3D *)team, (::GuardMode)maxShotsToFire,
					cmdSource );
	}
}

// ---------------------------------------------------------------------------
// 0x001568A0 -- guard walk through the command interface at ILT 0x00014FDD.

class Open2Commands1568A0
{
public:
	void aiGuardPosition( const Coord3D *pos, ::GuardMode mode,
			::CommandSourceType cmdSource );
};

class Open2GroupAI1568A0
{
public:
	char m_head[ 0x20 ];
	Open2Commands1568A0 m_commands;
};

class Open2Member1568A0
{
public:
	char m_head[ 0x204 ];
	Open2GroupAI1568A0 *m_ai;
};

struct Open2MemberNode1568A0 : public BfmeListNodeBase
{
	Open2Member1568A0 *m_value;
};

class Open2Group1568A0
{
public:
	enum GuardMode { OPEN2_GUARD_MODE };
	enum CommandSourceType { OPEN2_COMMAND_SOURCE };

	void groupGuardPosition( const Coord3D *pos, GuardMode mode,
			CommandSourceType cmdSource );

private:
	char m_head[ 4 ];
	BfmeListNodeBase *m_members;
};

// @?groupGuardPosition@Open2Group1568A0@@QAEXPBUCoord3D@@W4GuardMode@1@W4CommandSourceType@1@@Z 0x001568A0
void Open2Group1568A0::groupGuardPosition( const Coord3D *pos, GuardMode mode,
		CommandSourceType cmdSource )
{
	if( !pos )
		return;

	for( BfmeListNodeBase *it = m_members->m_bfmeNext;
			it != m_members;
			it = it->m_bfmeNext )
	{
		Open2GroupAI1568A0 *ai = ( (Open2MemberNode1568A0 *)it )->m_value->m_ai;

		if( ai )
			ai->m_commands.aiGuardPosition( pos, (::GuardMode)mode,
					(::CommandSourceType)cmdSource );
	}
}

// ---------------------------------------------------------------------------
// 0x00156900 -- guard walk through the command interface at ILT 0x0000F47F.

class Open2Commands156900
{
public:
	void aiGuardPosition( const Coord3D *pos, ::GuardMode mode,
			::CommandSourceType cmdSource );
};

class Open2GroupAI156900
{
public:
	char m_head[ 0x20 ];
	Open2Commands156900 m_commands;
};

class Open2Member156900
{
public:
	char m_head[ 0x204 ];
	Open2GroupAI156900 *m_ai;
};

struct Open2MemberNode156900 : public BfmeListNodeBase
{
	Open2Member156900 *m_value;
};

class Open2Group156900
{
public:
	enum GuardMode { OPEN2_GUARD_MODE };
	enum CommandSourceType { OPEN2_COMMAND_SOURCE };

	void groupGuardPosition( const Coord3D *pos, GuardMode mode,
			CommandSourceType cmdSource );

private:
	char m_head[ 4 ];
	BfmeListNodeBase *m_members;
};

// @?groupGuardPosition@Open2Group156900@@QAEXPBUCoord3D@@W4GuardMode@1@W4CommandSourceType@1@@Z 0x00156900
void Open2Group156900::groupGuardPosition( const Coord3D *pos, GuardMode mode,
		CommandSourceType cmdSource )
{
	if( !pos )
		return;

	for( BfmeListNodeBase *it = m_members->m_bfmeNext;
			it != m_members;
			it = it->m_bfmeNext )
	{
		Open2GroupAI156900 *ai = ( (Open2MemberNode156900 *)it )->m_value->m_ai;

		if( ai )
			ai->m_commands.aiGuardPosition( pos, (::GuardMode)mode,
					(::CommandSourceType)cmdSource );
	}
}

// ---------------------------------------------------------------------------
// 0x00156960 -- guard walk through the command interface at ILT 0x000171C0.

class Open2Commands156960
{
public:
	void aiGuardPosition( const Coord3D *pos, ::GuardMode mode,
			::CommandSourceType cmdSource );
};

class Open2GroupAI156960
{
public:
	char m_head[ 0x20 ];
	Open2Commands156960 m_commands;
};

class Open2Member156960
{
public:
	char m_head[ 0x204 ];
	Open2GroupAI156960 *m_ai;
};

struct Open2MemberNode156960 : public BfmeListNodeBase
{
	Open2Member156960 *m_value;
};

class Open2Group156960
{
public:
	enum GuardMode { OPEN2_GUARD_MODE };
	enum CommandSourceType { OPEN2_COMMAND_SOURCE };

	void groupGuardPosition( const Coord3D *pos, GuardMode mode,
			CommandSourceType cmdSource );

private:
	char m_head[ 4 ];
	BfmeListNodeBase *m_members;
};

// @?groupGuardPosition@Open2Group156960@@QAEXPBUCoord3D@@W4GuardMode@1@W4CommandSourceType@1@@Z 0x00156960
void Open2Group156960::groupGuardPosition( const Coord3D *pos, GuardMode mode,
		CommandSourceType cmdSource )
{
	if( !pos )
		return;

	for( BfmeListNodeBase *it = m_members->m_bfmeNext;
			it != m_members;
			it = it->m_bfmeNext )
	{
		Open2GroupAI156960 *ai = ( (Open2MemberNode156960 *)it )->m_value->m_ai;

		if( ai )
			ai->m_commands.aiGuardPosition( pos, (::GuardMode)mode,
					(::CommandSourceType)cmdSource );
	}
}

// ---------------------------------------------------------------------------
// The notice senders.  Everything but the literal is shared with 0x0051B360.

extern "C" __declspec(dllimport) int __cdecl _snprintf( char *buffer,
	int count, const char *format, ... );

int AptLivingWorldWindowIndex( int low, int high );
extern int g_aptLivingWorldWindowIndex;

class Open2WindowManager
{
public:
	void unidentified_00015235( int movie, const char *function, int argumentCount,
		const void *argument, int unused1, int unused2, int unused3, int unused4 );
};

// The one retail global at 0x012F19E8 is the window manager.  The three notice
// senders below only need its unidentified_00015235 entry, so they reach the
// global through the Open2WindowManager view above, cast at each use.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;	///< retail [0x012F19E8]

// @?Open2SendNotice51B050@@YAXH@Z 0x0051B050
void Open2SendNotice51B050( int what )
{
	char text[ 16 ];
	_snprintf( text, 16, "%d", what );

	((Open2WindowManager *)g_rva012F19E8WindowManager)->unidentified_00015235(
		AptLivingWorldWindowIndex( g_aptLivingWorldWindowIndex, g_aptLivingWorldWindowIndex ),
		"DestroyRegionPopup", 1, text, 0, 0, 0, 0 );
}

// @?Open2SendNotice51B0C0@@YAXH@Z 0x0051B0C0
void Open2SendNotice51B0C0( int what )
{
	char text[ 16 ];
	_snprintf( text, 16, "%d", what );

	((Open2WindowManager *)g_rva012F19E8WindowManager)->unidentified_00015235(
		AptLivingWorldWindowIndex( g_aptLivingWorldWindowIndex, g_aptLivingWorldWindowIndex ),
		"CloseRegionPopup", 1, text, 0, 0, 0, 0 );
}

// @?Open2SendNotice51B2F0@@YAXH@Z 0x0051B2F0
void Open2SendNotice51B2F0( int what )
{
	char text[ 16 ];
	_snprintf( text, 16, "%d", what );

	((Open2WindowManager *)g_rva012F19E8WindowManager)->unidentified_00015235(
		AptLivingWorldWindowIndex( g_aptLivingWorldWindowIndex, g_aptLivingWorldWindowIndex ),
		"DestroyRegionConqueredNotice", 1, text, 0, 0, 0, 0 );
}
