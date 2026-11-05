# Adopt the registered Coord3D header in 19 units

Base: `bb028c20600a8e3267bb57e13725ddf7fcf52729`. Native scope: 54 existing rows and 353 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameLogic/AI/AIAttackAimAtTargetState_onEnter_Bfme.cpp` | 1 | 20 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsTeamWanderPanic.cpp` | 2 | 11 |
| `game/GameEngine/Source/GameLogic/Pathfinder/PathfinderFindSafePathBfme.cpp` | 1 | 26 |
| `game/GameEngine/Source/GameClient/Drawable/Update/BeaconClientUpdateClientUpdate.cpp` | 8 | 16 |
| `game/GameEngine/Source/GameLogic/AI/AIMeleeReAcquireState_update.cpp` | 1 | 38 |
| `game/GameEngine/Source/GameLogic/AI/AIStateOnEnterBodies.cpp` | 5 | 23 |
| `game/GameEngine/Source/GameClient/DrawableCaptionAndAmbient.cpp` | 2 | 3 |
| `game/GameEngine/Source/GameLogic/Object/Contain/TransportContainOnRemoving.cpp` | 1 | 53 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva00270DF0RebuildPath.cpp` | 1 | 3 |
| `game/GameEngine/Source/GameLogic/Object/WeaponSet_getAbleToUseWeaponAgainstTarget.cpp` | 1 | 13 |
| `game/GameEngine/Source/GameClient/Drawable_drawConstructPercent.cpp` | 1 | 8 |
| `game/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetState_computePath_Bfme.cpp` | 2 | 14 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewBuildCameraTransformBfme.cpp` | 1 | 9 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_TeamRepairNearest_Rva00303670.cpp` | 1 | 43 |
| `game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior_projectileFireAtObjectOrPosition.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceHelpers.cpp` | 5 | 9 |
| `game/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdateSetStatus.cpp` | 1 | 28 |
| `game/GameEngine/Source/Common/RTS/TeamMemberQueries.cpp` | 6 | 11 |
| `game/GameEngine/Source/Common/System/recorder_strings.cpp` | 13 | 24 |
