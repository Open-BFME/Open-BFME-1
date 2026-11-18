# Scalar alias contracts: cohort 125

One task replaces one consumer file's grouped private primitive typedefs
with the existing EA/BFME1 contract. Individual typedefs are not counted as
separate tasks. Only exact primitive spellings already present in both the
native BFME1 Precompiled/PreRTS.h and the EA BaseType.h qualify. Char remains
char, unsigned types remain unsigned, and no 64-bit/platform modernization is
inferred. Original provider headers are preserved. The narrow shared header
contains only the nine original scalar typedefs, without macros or runtime code.

Actual original source filenames compile into explicit private ordinary and Z7
controls before any edit. After adoption the normal build passes. Its complete
ordinary runtime inventory equals the actual pre-edit object: code, data,
definitions, relocations, raw directives, weak references and aliases. A fresh
actual-source ordinary object also equals the normal build object. All original
complete class contracts and all original enums remain identical in actual
Z7 records. Real-header traces and opened-input hashes are retained.

Additional private functions bind pointers to each adopted alias and return its
sizeof. Complete witness symbol names and bodies must remain identical, proving
primitive type identity and size even for aliases that contribute no runtime
instructions. A negative control changes unused Int from int to unsigned int:
ordinary runtime remains identical, but the exact primitive witness rejects it.
Witness code exists only in explicit diagnostic outputs. It is not game source,
retail identity evidence or authored-byte progress. CPP files included by other
CPPs are excluded unless all parent/namespace contexts are independently proven.

This source consistency work adds no newly reconstructed function bytes and
makes no crash, RAM/leak, FPS, multicore or runtime-start claim. No verifier,
baseline, pin, EH label or alias is weakened or manually altered. Linking is
separate; absent dependency receipts remain UNKNOWN for provider freshness.

|Task|Consumer|Grouped aliases|Rows|Retained row bytes|
|---|---|---|---:|---:|
|1897|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_Rva002F22A0TeamHomeGroup.cpp`|Bool, Int, UnsignedInt|1|266|
|1898|`game/GameEngine/Source/GameNetwork/LANAPIOnPlayerList.cpp`|Int, UnsignedInt, Bool|1|238|
|1899|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doSkirmishAttackNearestGroupWithValue.cpp`|Bool, Int, UnsignedInt|1|183|
|1900|`game/GameEngine/Source/Common/RecorderCopyReplayRva00099A40.cpp`|Int, UnsignedInt, Bool|1|771|
|1901|`game/GameEngine/Source/GameLogic/Object/Update/WeaponModeSpecialPowerUpdateRva002B2E60.cpp`|Int, UnsignedInt, Bool|1|191|
|1902|`game/GameEngine/Source/Common/RTS/Team_countObjects.cpp`|Int, UnsignedInt, Bool|1|120|
|1903|`game/GameEngine/Source/GameLogic/AI/AIGroup_groupDoSpecialPowerAtLocation.cpp`|Bool, UnsignedInt, Real|1|187|
|1904|`game/GameEngine/Source/Common/Rva000D4360Owner.cpp`|Int, UnsignedInt, Bool|1|116|
|1905|`game/GameEngine/Source/Common/Rva0018C480Xfer.cpp`|Bool, Int, UnsignedByte|1|343|
|1906|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeApproachTargetState_onExit.cpp`|Bool, Real, Int|1|174|
|1907|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doMoveCameraAlongSplinePath.cpp`|Bool, Real, Int|1|135|
|1908|`game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogicRva006BE890.cpp`|Real, Int, Bool|1|239|
|1909|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCameraModFinalMoveToBfme.cpp`|Real, Int, Bool|1|228|
|1910|`game/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdate_doAngleFX.cpp`|Real, Bool, Int|1|164|
|1911|`game/GameEngine/Source/GameClient/GUI/Shell/ShellMenuScheme_set.cpp`|Int, UnsignedInt, UnsignedShort, Bool|1|262|
|1912|`game/GameEngine/Source/Common/RTS/Player_canBuild.cpp`|Bool, Int, UnsignedShort|1|303|
|1913|`game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineRva003D7680.cpp`|Int, Bool, Real|1|666|
|1914|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferRva007331F0.cpp`|Bool, Int, Real|1|444|
|1915|`game/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorRva001FEC30.cpp`|Int, UnsignedInt, Bool|1|122|
|1916|`game/GameEngine/Source/Common/RTS/Rva000D74B0Map_xfer.cpp`|Bool, UnsignedInt, UnsignedShort, UnsignedByte|1|269|
|1917|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCameraModFinalZoomBfme.cpp`|Real, Int, Bool|1|322|
|1918|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doSetupCamera.cpp`|Bool, Int, Real|1|207|
|1919|`game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/W3DPushButtonDrawNumber00794B70.cpp`|Int, UnsignedInt, Real|1|359|
|1920|`game/GameEngine/Source/Common/System/SaveGame/GameState_missionSave_Thunk.cpp`|Int, Bool, Char|1|311|
|1921|`game/GameEngine/Source/GameLogic/AI/AIGroup_groupDoSpecialPowerAtObject.cpp`|UnsignedInt, Real, Bool|1|520|
|1922|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsPlayerHasNOrFewerBases.cpp`|Bool, Real, UnsignedInt|1|281|
|1923|`game/GameEngine/Source/Common/System/XferCoord3DVector.cpp`|UnsignedByte, UnsignedInt, UnsignedShort, Bool|1|303|
|1924|`game/GameEngine/Source/GameLogic/ScriptEngine/ScoreKeeperXferObjectCountMap.cpp`|Int, UnsignedShort, UnsignedByte|1|332|
|1925|`game/GameEngine/Source/Common/TerrainTypes_findTerrain.cpp`|Int, UnsignedInt, UnsignedShort, Bool|1|246|
|1926|`game/GameEngine/Source/Common/System/XferBoolVector.cpp`|UnsignedByte, UnsignedInt, UnsignedShort, Bool|1|316|
|1927|`game/GameEngine/Source/Common/RTS/ShroudManagerImpl008FBD00.cpp`|Real, Int, UnsignedInt|1|1252|
|1928|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate_chooseLocomotorSetExplicit.cpp`|Bool, Int, UnsignedInt|1|144|
|1929|`game/GameEngine/Source/GameLogic/Object/ObjectOnRemovedFrom.cpp`|Int, Bool, UnsignedInt|1|247|
|1930|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamSetModelConditionForDuration.cpp`|Bool, Int, Real|1|358|
|1931|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_checkTarget.cpp`|Int, UnsignedInt, Bool|1|123|
|1932|`game/GameEngine/Source/GameLogic/AI/AIAttackState_xfer.cpp`|UnsignedByte, UnsignedInt, Bool|1|372|
|1933|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/MapSelectorTooltip.cpp`|Int, UnsignedInt, Real|1|267|
|1934|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdateCancelDock.cpp`|UnsignedInt, Int, Bool|1|346|
|1935|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBuffer_clearAllTrees.cpp`|Int, Real, UnsignedByte|1|214|
|1936|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamCaptureNearestUnownedFactionUnit.cpp`|Bool, UnsignedInt, Real|1|286|
|1937|`game/GameEngine/Source/GameLogic/Object/Locomotor_rva001BC560.cpp`|Bool, Int, Real|1|210|
|1938|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_findClosestObject.cpp`|Bool, Int, UnsignedInt, Real|1|385|
|1939|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_transferObjectName.cpp`|Int, UnsignedShort, Bool|1|180|
|1940|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/ParseAnimation.cpp`|Real, UnsignedInt, Bool|1|361|
|1941|`game/GameEngine/Source/Common/RTS/Rva000C4D80.cpp`|Bool, Int, UnsignedByte|1|195|
|1942|`game/GameEngine/Source/Common/RTS/Player_setRankLevel.cpp`|Int, Real, Bool|1|471|
|1943|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doMoveCameraTo.cpp`|Bool, Int, Real|1|186|
|1944|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLaserDrawModuleDataConstructor.cpp`|Int, UnsignedInt, Real|1|115|
|1945|`game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineRva003D79C0.cpp`|Int, Bool, Real|1|566|
|1946|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadQuickmatchEnumPlayersCallback.cpp`|Int, Bool, UnsignedInt|1|312|
|1947|`game/GameEngine/Source/GameLogic/Object/Update/Rva00287290Update.cpp`|Bool, UnsignedInt, Int|1|125|
|1948|`game/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorRva001FE7C0.cpp`|Int, Bool, Real, UnsignedInt|1|178|
|1949|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewPitchCameraBfme.cpp`|Real, Int, Bool|1|176|
|1950|`game/GameEngine/Source/GameLogic/Object/AttackNugget_create_Thunk.cpp`|Int, Real, Bool|1|334|
|1951|`game/GameEngine/Source/Common/BfmeSinkBOE_bfmeDoBOE.cpp`|Int, Real, UnsignedByte|1|657|
|1952|`game/GameEngineDevice/Source/W3DDevice/GameClient/ScreenBWFilterPostRender.cpp`|Int, Real, Bool|1|665|
|1953|`game/GameEngine/Source/GameClient/GameTextManager_parseMapStringFile.cpp`|Bool, Int, Char|1|660|
|1954|`game/GameEngine/Source/Common/System/XferObjectIDVector.cpp`|UnsignedByte, UnsignedInt, Bool|1|294|
|1955|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCameraModFinalLookTowardBfme.cpp`|Real, Int, Bool|1|528|
|1956|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerHandleQMMatch.cpp`|Int, Bool, UnsignedInt|1|653|
|1957|`game/GameEngine/Source/GameLogic/Object/ObjectRva001D02C0.cpp`|Int, Real, UnsignedInt|1|362|
|1958|`game/GameEngine/Source/Common/Rva0023C9C0.cpp`|Bool, UnsignedInt, UnsignedShort|1|179|
|1959|`game/GameEngine/Source/GameClient/GameTextManager_parseStringFile.cpp`|Bool, Int, Char|1|587|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
