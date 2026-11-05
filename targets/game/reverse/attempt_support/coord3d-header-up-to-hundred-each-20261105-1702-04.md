# Adopt the registered Coord3D header in 20 units

Base: `d99810b2eea20865167dff8f0ca1bdebda63e8d2`. Native scope: 35 existing rows and 376 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameClient/Drawable_drawIconUI_BFME.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsNamedTeam.cpp` | 10 | 13 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DeployStyleAIUpdate_setMyState_BFME.cpp` | 1 | 24 |
| `game/GameEngine/Source/GameLogic/Object/PartitionData_updateCellsTouched.cpp` | 1 | 13 |
| `game/GameEngine/Source/GameLogic/Object/Behavior/RampageBehaviorCtorThunk.cpp` | 2 | 12 |
| `game/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeployHordeSpecialPowerRva00265ED0.cpp` | 1 | 65 |
| `game/GameEngine/Source/GameLogic/Object/WeaponSetGetAbleToAttackSpecificObject.cpp` | 1 | 14 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawGetPristineBonePositionsForConditionState.cpp` | 1 | 30 |
| `game/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule_initiateIntentToDoSpecialPower.cpp` | 1 | 15 |
| `game/GameEngine/Source/GameLogic/AI/AIGuardInnerState_onEnter_Bfme.cpp` | 1 | 6 |
| `game/GameEngine/Source/GameLogic/Object/Update/HeightDieUpdate.cpp` | 1 | 12 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/TerrainTracksBfmeAddCap.cpp` | 2 | 13 |
| `game/GameEngine/Source/GameLogic/AI/AITNGuardMachineLookForInnerTarget.cpp` | 1 | 31 |
| `game/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorRva001FF360.cpp` | 1 | 18 |
| `game/GameEngine/Source/GameLogic/Object/Update/StateTransition002A32D0.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/AI/Rva001766F0State_update.cpp` | 1 | 13 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsTeamSighted_Rva00328020.cpp` | 1 | 41 |
| `game/GameEngine/Source/GameLogic/AI/AIChargeTargetState_update.cpp` | 2 | 12 |
| `game/GameEngine/Source/GameLogic/AI/AIFollowWaypointPathState_onEnter.cpp` | 1 | 17 |
| `game/GameEngine/Source/GameLogic/Map/TerrainLogicBridges.cpp` | 4 | 25 |
