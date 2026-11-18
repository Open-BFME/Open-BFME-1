
#pragma once

// Existing BFME1 enum contract from inputs/reference/shims/sweep/GameLogic/AIStateMachine.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum AIStateType
{
	AI_IDLE,
	AI_MOVE_TO,																///< move to the GoalObject or GoalPosition
	AI_FOLLOW_WAYPOINT_PATH_AS_TEAM,					///< follow a waypoint path as a team
	AI_FOLLOW_WAYPOINT_PATH_AS_INDIVIDUALS,		///< follow a waypoint path
	AI_FOLLOW_WAYPOINT_PATH_AS_TEAM_EXACT,		///< follow a waypoint path as a team
	AI_FOLLOW_WAYPOINT_PATH_AS_INDIVIDUALS_EXACT,///< follow a waypoint path
	AI_FOLLOW_PATH,														///< follow a simple list of points
	AI_FOLLOW_EXITPRODUCTION_PATH,						///< the same, but only when exiting production facility
	AI_WAIT,
	AI_ATTACK_POSITION,												///< attempt to kill GoalPosition
	AI_ATTACK_OBJECT,													///< attempt to kill GoalObject
	AI_FORCE_ATTACK_OBJECT,										///< attempt to kill GoalObject, force fire on it.
	AI_ATTACK_AND_FOLLOW_OBJECT,							///< attempt to kill GoalObject, following it if necessary (and possible)
	AI_DEAD,
	AI_DOCK,																	///< dock with GoalObject, if GoalObject has a DockUpdate module
	AI_ENTER,																	///< move to GoalObject and "enter" it when close
	AI_GUARD,																	///< guard your current location
	AI_HUNT,																	///< seek and destroy behavior
	AI_WANDER,																///< Wander around following a waypoint path.
	AI_PANIC,																	///< Run around screaming following a waypoint path.
	AI_ATTACK_SQUAD,													///< Set the unit to attempt to kill all objects in goalSquad.
	AI_GUARD_TUNNEL_NETWORK,									///< Guard from inside a tunnel network.
	AI_GET_REPAIRED,													///< Get repaired at a repair depot
	AI_MOVE_OUT_OF_THE_WAY,										///< Move out of the way of another unit.
	AI_MOVE_AND_TIGHTEN,											///< Move in order to tighten up a formation.
	AI_MOVE_AND_EVACUATE,											///< Move to, then empty transport.
	AI_MOVE_AND_EVACUATE_AND_EXIT,						///< Move to, then empty transport.
	AI_MOVE_AND_DELETE,												///< Move to, then delete self.
	AI_ATTACK_AREA,														///< Attack units in an area.
	AI_HACK_INTERNET,													///< Hack internet for free money (no target required).
	AI_ATTACK_MOVE_TO,												///< Attack-move to a location
	AI_ATTACKFOLLOW_WAYPOINT_PATH_AS_INDIVIDUALS,	///< Attack-Follow down a waypoint path as individuals
	AI_ATTACKFOLLOW_WAYPOINT_PATH_AS_TEAM,				///< Attack-Follow down a waypoint path as a team
	AI_FACE_OBJECT,
	AI_FACE_POSITION,
	AI_RAPPEL_INTO,														/**< rappel from current pos down to target object.
																								if target is building, will enter and kill lots of folks.
																								if target is null, will rappel to ground. */
	AI_COMBATDROP,														/**< attempt to send AI_RAPPEL_INTO to contents. */
	AI_EXIT,																	///< exit the obj, waiting if necessary
	AI_PICK_UP_CRATE,													///< Pick up a crate created by a kill.  jba.
	AI_MOVE_AWAY_FROM_REPULSORS,							///< Civilians are running away from repulsors. (enemies or dead civs, usually) jba
	AI_WANDER_IN_PLACE,												///< Civilians just wander around a spot, rather than along a path.
	AI_BUSY,																	///< This is a state that things will be in when they are busy doing random stuff that doesn't require AI interaction.
	AI_EXIT_INSTANTLY,												///< exit this obj, without waiting -- do it in the onEnter! This frame!
	AI_GUARD_RETALIATE,												///< attacks attacker but with restrictions (hybrid of attack and guard).

	NUM_AI_STATES
};
