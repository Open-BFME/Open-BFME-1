# Adopt the registered Coord3D header in 19 units

Base: `220b0774a7f1763856dec6edbed7228d34c95c09`. Native scope: 27 existing rows and 148 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/Rva0073B290ViewGetRegion.cpp` | 1 | 4 |
| `game/GameEngine/Source/GameLogic/AI/Rva001775A0.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/Object/ObjectSetDisabledUntil.cpp` | 1 | 7 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedUseCommandButtonAbilityAtWaypoint_Thunk.cpp` | 1 | 7 |
| `game/GameEngine/Source/GameClient/LaserFXNuggetEffects.cpp` | 2 | 2 |
| `game/GameEngine/Source/GameLogic/AI/AIGuardInnerStateUpdate.cpp` | 1 | 10 |
| `game/GameEngine/Source/GameLogic/Object/FiringTrackerBFMEXfer.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain_xfer.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdFollowThruStateUpdate.cpp` | 1 | 17 |
| `game/GameEngine/Source/GameLogic/System/Rva00397350GlobalRallyPointFeedback.cpp` | 1 | 11 |
| `game/GameEngine/Source/GameLogic/AI/PathOptimizeGround.cpp` | 1 | 7 |
| `game/GameEngine/Source/GameLogic/AI/PathfinderRva003F1690.cpp` | 1 | 5 |
| `game/GameEngine/Source/GameClient/MessageStream/CommandTranslator_issueMoveToLocationCommand.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/Object/Contain/AODHordeContain_trackLargeUnit.cpp` | 4 | 5 |
| `game/GameEngine/Source/GameLogic/Object/Update/FloatUpdateUpdate.cpp` | 1 | 18 |
| `game/GameEngine/Source/Common/RTS/PlayerObjectWalk.cpp` | 3 | 3 |
| `game/GameEngine/Source/GameLogic/AI/AIWanderInPlaceState_update.cpp` | 1 | 3 |
| `game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate_doParticleSystemAtBone.cpp` | 1 | 27 |
| `game/GameEngine/Source/GameLogic/AI/AIWaypointPathStates.cpp` | 3 | 14 |
