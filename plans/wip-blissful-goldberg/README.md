# WIP parked from session blissful-goldberg (2026-09-24)

Reference material only. Nothing in this folder is compiled or claimed by the ledger.

## d_002fd9d0-scriptactions.patch

This is `git diff --binary` of a stopped conversion worktree, based on master `00d2fa28`. It holds nine
ScriptActions bodies from `Code/gen_asm/d_002fd9d0.asm` plus carved neighbours. `add_match` byte-verified
all nine in that worktree, but the adversarial name and pin review never ran.
Its commit hook failed name_regression with 10 descriptive-to-placeholder regressions (for example,
banked `doTeamRepairNearest` became `rva00303910`), so each rename needs evidence or a revert to the bank's name.
The patch also edits two landed sources (ScriptActionsNamedSetModelCondition.cpp and
ScriptActionsTeamSetModelCondition.cpp), deletes six `reverse/attempts` stashes, and adds three unverified pins:
`??1BfmeWideResult@@QAE@XZ` at 0x000C5FC0,
`vector<Object*>::_M_insert_overflow` at 0x0018B700, and `TerrainLogic::rva001A62D0` at 0x001A62D0.

The rows it added to `reverse/functions.csv` are:

    ?doDeploySiegeOnWaypoint@ScriptActions@@IAEXPAVParameter@@00@Z,,0x002FF0C0,704,Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsDeploySiege.cpp,matched,executeAction action 466 via ILT 0x00012085; template DEPLOY_SIEGE_ON_WAYPOINT; carved boundary ret 0Ch at +0x2BD; clean C++ with OVERRIDE<ThingTemplate> keeping the advance null guard
    ?doDeploySiegeNearTeam@ScriptActions@@IAEXPAVParameter@@00@Z,,0x002FF430,655,Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsDeploySiege.cpp,matched,executeAction action 467 via ILT 0x0003F576; template DEPLOY_SIEGE_NEAR_TEAM; carved boundary ret 0Ch at +0x28C; shares the deploy-siege member walk with 0x002FF0C0
    ?doDeployNamedSiegeOnWaypoint@ScriptActions@@IAEXPAVParameter@@00@Z,,0x002FEE90,448,Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsDeploySiege.cpp,matched,executeAction action 465 via ILT 0x00046F15; template DEPLOY_NAMED_SIEGE_ON_WAYPOINT; single-unit deploy-siege sibling of 0x002FF0C0
    ?applyModelCondition_002FDEF0@@YAXPAVObject@@H_N@Z,,0x002FDEF0,131,Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsNamedSetModelCondition.cpp,matched,TU-local UNIT/TEAM_SET_MODELCONDITION helper called by 0x002FDFB0 and 0x002FDFF0 with ESI=Object EAX=condition stack=Bool; jump table maps 1-4 to USER_1-4; reconstruction alias keeps the address
    ?doTeamPartialUseCommandButton@ScriptActions@@IAEXMABVAsciiString@@0@Z,,0x002FFB60,464,Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsTeamPartialUseCommandButton.cpp,matched,executeAction action 273 via ILT 0x000325E7; template TEAM_PARTIAL_USE_COMMANDBUTTON; ZH twin with BFME ceil rounding
    ?useCommandButtonOnNearestTemplate_002FDAC0@@YAXPAVObject@@PBVCommandButton@@PBVThingTemplate@@@Z,,0x002FDAC0,416,Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsNamedUseCommandButtonOnNearestObjectType.cpp,matched,TU-local helper shared by 0x002FDCD0 and 0x002FE110 with ESI=unit EDI=CommandButton stack=ThingTemplate; closest template object via Thing/ValidCommandButtonTarget/SameMapStatus filters; reconstruction alias keeps the address
    ?doNamedUseCommandButtonOnNearestObjectType@ScriptActions@@IAEXABVAsciiString@@00@Z,,0x002FDCD0,173,Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsNamedUseCommandButtonOnNearestObjectType.cpp,matched,executeAction action 429 via ILT 0x000413D0; template NAMED_USE_COMMANDBUTTON_ON_NEAREST_OBJECTTYPE; calls helper 0x002FDAC0
    ?doTeamGarrisonNearestBuilding@ScriptActions@@IAEXABVAsciiString@@@Z,,0x00302240,536,Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsTeamGarrisonNearestBuilding.cpp,matched,executeAction action 108 via ILT 0x00008A8F; template TEAM_GARRISON_NEAREST_BUILDING; ZH twin with BFME linked filter temporaries and refcounted query result
    ?rva00303910@ScriptActions@@IAEXABVAsciiString@@0@Z,,0x00303910,340,Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsRva00303910.cpp,matched,executeAction action 480 via ILT 0x000459B7 with two strings; template slot 480 has no internal name so the method keeps the address; dozers of team 1 repair the lowest-body structure of team 2

## Q1Receiver0134FAAC_refresh.draft.cpp.txt

This is an unverified draft of `Q1Receiver0134FAAC::refresh` at 0x009EFF50, a 3186-byte carved body. It never reached
add_match, so its match score is unknown. Probe it before relying on it. The rest of the cluster has since landed
on master, and so have its helper pins.
