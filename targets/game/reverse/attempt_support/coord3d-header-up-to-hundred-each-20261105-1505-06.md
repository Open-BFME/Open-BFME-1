# Adopt the registered Coord3D header in 20 units

Base: `e02ff6970974ceb4eefe84fda5bb0d58f3a5c42c`. Native scope: 45 existing rows and 529 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameClient/System/ParticleSystem_generateParticleInfo_BFME.cpp` | 1 | 14 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplaySetTimeOfDayLights.cpp` | 2 | 13 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva0077C390Parse.cpp` | 1 | 13 |
| `game/GameEngine/Source/GameLogic/Object/Update/DynamicShroudClearingRangeUpdateUpdate.cpp` | 1 | 7 |
| `game/GameEngine/Source/GameLogic/AI/AIRampageState_onEnter_Bfme.cpp` | 1 | 6 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsNamedUnitMovement.cpp` | 4 | 8 |
| `game/GameEngine/Source/GameLogic/Object/Contain/TransportContain_isSpecificRiderFreeToExit_Thunk.cpp` | 1 | 4 |
| `game/GameEngine/Source/GameClient/LivingWorld.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/Map/TerrainLogicBuildBeacons.cpp` | 2 | 61 |
| `game/GameEngine/Source/GameLogic/AI/AIGuardOuterState_update_Bfme.cpp` | 1 | 4 |
| `game/GameEngine/Source/GameLogic/AI/Rva0016AEE0WeaponRangePosition.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdAIUpdate_privateFollowPathAppend.cpp` | 2 | 11 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewRotateCameraOneFrameBfme.cpp` | 1 | 13 |
| `game/GameEngine/Source/GameLogic/Object/ObjectSpecialPowers.cpp` | 3 | 3 |
| `game/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDeadBehaviorOnDie.cpp` | 1 | 14 |
| `game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldSoundCopyCtor.cpp` | 2 | 14 |
| `game/GameEngine/Source/GameLogic/AI/AITNGuardReturnState_onEnter_Bfme.cpp` | 1 | 17 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/Rva002FA7C0ScriptAction.cpp` | 1 | 16 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00347E60.cpp` | 17 | 303 |
| `game/GameEngine/Source/GameNetwork/NetGameCommandMsg_constructGameMessage.cpp` | 1 | 5 |
