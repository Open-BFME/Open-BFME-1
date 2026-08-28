// 24 forty-six-byte __thiscall constructors with one shape:
//
//     push ecx / push esi / push ecx / mov esi,ecx / mov [esp+8],esp /
//     mov ecx,esp / push <offset literal> /
//     call ??0?$StringBase@D@@AAE@PBD@Z / mov eax,[esp+0x10] / push eax /
//     mov ecx,esi / call <base constructor> / mov [esi],<offset vftable> /
//     mov eax,esi / pop esi / pop ecx / ret 4
//
// WHAT THE BODY IS.  A four-byte temporary is built on the stack from a string
// literal by `StringBase<char>`'s private constructor -- the one already landed
// at 0x00888BC0 in Code/Libraries/Source/WWVegas/WWLib/string_base.cpp -- and
// then the object's single dword argument and that temporary are handed to a
// base constructor, after which the derived vftable is written and `this`
// returned.  The vftable store landing AFTER the call is what makes the callee
// a base constructor rather than an ordinary member: a base constructor writes
// the same slot and the derived class's write has to come second.  Nothing
// destroys the temporary, which is MSVC 7.1 destroying by-value class
// parameters in the callee.
//
// WHAT THE LITERAL IS.  Every one of the 24 literals is a state class name --
// AIDockApproachState, AIHarvestApproachSiteState, SupplyTruckIdleState and so
// on -- and the base constructor takes (machine, name).  That is Zero Hour's
// `State( StateMachine *machine, AsciiString name )` and the idiom its
// subclasses use verbatim:
//
//     AIBusyState( StateMachine *machine ) : State( machine, "AIBusyState" ) {}
//
// so each of these bodies is a state subclass naming ITSELF to its base.
//
// THE NAMES HERE ARE STILL ADDRESS-DERIVED, AND DELIBERATELY.  The literal is
// what the constructor passes, not provably what the class is called: Zero
// Hour's own AIMoveAwayFromRepulsorsState passes "AIMoveAwayFromRepulsors",
// short of its class name, so the two are not the same fact.  The image carries
// no RTTI to settle it either -- it is built /GR-, and the dword ahead of each
// of these vftables is not a complete-object locator.  The literals are in the
// source where they belong and the build re-reads each against the retail bytes
// at the address it references, so promoting these rows is a mechanical repoint
// once the class names are recovered from somewhere that actually witnesses
// them.
//
// 2 distinct base constructors, 24 bodies.  Each base is reached through an
// incremental-link thunk and is pinned in `reverse/symbols.csv` at that thunk's
// address, which is what the retail displacement encodes; the bodies they jump
// to are 0x000A19E0 and 0x0014F280.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text ) : m_string( text ) {}

	StringBase<char> m_string;
};

class Rva000A19E0StateBase
{
public:
	Rva000A19E0StateBase( void *machine, AsciiString name );

	virtual void stateBaseAnchor();
};

class Rva0014F280StateBase
{
public:
	Rva0014F280StateBase( void *machine, AsciiString name );

	virtual void stateBaseAnchor();
};

#define BFME_STATE_SELF_NAMING_CTOR( NAME, BASE, TEXT )                       \
	class NAME : public BASE                                                  \
	{                                                                         \
	public:                                                                   \
		NAME( void *machine );                                                \
	};                                                                        \
	NAME::NAME( void *machine ) : BASE( machine, AsciiString( TEXT ) ) {}

BFME_STATE_SELF_NAMING_CTOR( Rva0014F380State, Rva0014F280StateBase, "AIDockApproachState" )
BFME_STATE_SELF_NAMING_CTOR( Rva0014F490State, Rva0014F280StateBase, "AIDockApproachState" )
BFME_STATE_SELF_NAMING_CTOR( Rva0014F510State, Rva0014F280StateBase, "AIDockMoveToEntryState" )
BFME_STATE_SELF_NAMING_CTOR( Rva0014F590State, Rva0014F280StateBase, "AIDockMoveToDockState" )
BFME_STATE_SELF_NAMING_CTOR( Rva0014F610State, Rva0014F280StateBase, "AIDockMoveToRallyState" )
BFME_STATE_SELF_NAMING_CTOR( Rva0014F690State, Rva0014F280StateBase, "AIDockMoveToExitState" )
BFME_STATE_SELF_NAMING_CTOR( Rva0015CE80State, Rva000A19E0StateBase, "AIGuardIdleState" )
BFME_STATE_SELF_NAMING_CTOR( Rva0015FD00State, Rva0014F280StateBase, "AIHarvestApproachSiteState" )
BFME_STATE_SELF_NAMING_CTOR( Rva00170F30State, Rva000A19E0StateBase, "AIStartAttackObjState" )
BFME_STATE_SELF_NAMING_CTOR( Rva00171250State, Rva000A19E0StateBase, "AIWaitUntilFinishedFiringState" )
BFME_STATE_SELF_NAMING_CTOR( Rva001714E0State, Rva000A19E0StateBase, "AIHordeEnterState" )
BFME_STATE_SELF_NAMING_CTOR( Rva00171540State, Rva000A19E0StateBase, "AIHordeExitState" )
BFME_STATE_SELF_NAMING_CTOR( Rva00171930State, Rva000A19E0StateBase, "AICowerState" )
BFME_STATE_SELF_NAMING_CTOR( Rva001719A0State, Rva000A19E0StateBase, "AIQuarrelState" )
BFME_STATE_SELF_NAMING_CTOR( Rva0018ACA0State, Rva000A19E0StateBase, "AITNGuardIdleState" )
BFME_STATE_SELF_NAMING_CTOR( Rva002B77F0State, Rva000A19E0StateBase, "DozerPrimaryGoingHomeState" )
BFME_STATE_SELF_NAMING_CTOR( Rva002C6100State, Rva000A19E0StateBase, "SupplyTruckWantsToPickUpOrDeliverBoxesState" )
BFME_STATE_SELF_NAMING_CTOR( Rva002C6170State, Rva000A19E0StateBase, "RegroupingState" )
BFME_STATE_SELF_NAMING_CTOR( Rva002C61F0State, Rva000A19E0StateBase, "DockingState" )
BFME_STATE_SELF_NAMING_CTOR( Rva002C6260State, Rva000A19E0StateBase, "HarvestingState" )
BFME_STATE_SELF_NAMING_CTOR( Rva002C62D0State, Rva000A19E0StateBase, "SupplyTruckBusyState" )
BFME_STATE_SELF_NAMING_CTOR( Rva002C63A0State, Rva000A19E0StateBase, "SupplyTruckIdleState" )
BFME_STATE_SELF_NAMING_CTOR( Rva002C9180State, Rva000A19E0StateBase, "ActAsDozerState" )
BFME_STATE_SELF_NAMING_CTOR( Rva002C91F0State, Rva000A19E0StateBase, "ActAsSupplyTruckState" )
