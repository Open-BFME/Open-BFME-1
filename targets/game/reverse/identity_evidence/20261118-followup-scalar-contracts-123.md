# Scalar alias contracts: cohort 123

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
|1776|`game/GameEngine/Source/GameLogic/Object/Update/SpecialDisguiseUpdateChangeVisualDisguise.cpp`|Bool, Int, UnsignedInt, Real|1|390|
|1777|`game/GameEngine/Source/GameLogic/Object/LocomotorHandleBehaviorZ.cpp`|Bool, Real, Int, UnsignedInt, UnsignedByte|1|1615|
|1778|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdSwoopStateOnEnter.cpp`|Bool, Int, UnsignedInt, Real|1|1057|
|1779|`game/GameEngine/Source/GameLogic/AI/AIAttackAimAtTargetState_onEnter_Bfme.cpp`|Int, UnsignedInt, Bool, Real|1|523|
|1780|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_onExit.cpp`|UnsignedInt, Bool, Int, Real|1|814|
|1781|`game/GameEngine/Source/Common/RTS/PlayerInit.cpp`|Int, UnsignedInt, Bool, Real|1|2056|
|1782|`game/GameEngine/Source/GameLogic/Object/Update/LargeGroupBonusUpdate_update.cpp`|Bool, Int, Real, UnsignedInt|1|818|
|1783|`game/GameEngine/Source/GameClient/DrawableConstructor.cpp`|Int, UnsignedInt, Bool, Real|1|2484|
|1784|`game/GameEngine/Source/GameClient/System/ParticleConstructor.cpp`|UnsignedInt, Int, Real, Bool|1|1044|
|1785|`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior_update.cpp`|Int, UnsignedInt, Real, Bool|1|1733|
|1786|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate_construct.cpp`|Bool, Int, UnsignedInt, Real|1|561|
|1787|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate_construct.cpp`|Bool, Int, UnsignedInt, Real|1|593|
|1788|`game/GameEngine/Source/GameLogic/Object/Update/CommandButtonHuntUpdateScanClosestTarget.cpp`|Bool, Int, UnsignedInt, Real|1|974|
|1789|`game/GameEngine/Source/Common/RTS/Team_updateState.cpp`|Bool, Int, Real, UnsignedInt|1|1293|
|1790|`game/GameEngine/Source/GameLogic/AI/AIPlayerSelectTeamToReinforce.cpp`|Bool, Int, UnsignedInt, Real|1|1243|
|1791|`game/GameEngine/Source/GameClient/DrawableUpdateDrawable.cpp`|UnsignedInt, Int, Real, Bool|1|2437|
|1792|`game/GameEngine/Source/GameLogic/AI/AIInternalMoveToState_onEnter.cpp`|Bool, UnsignedInt, Int, Real|1|1524|
|1793|`game/GameEngine/Source/GameLogic/AI/AIPlayerIsLocationSafe.cpp`|Bool, Int, UnsignedInt, Real|1|388|
|1794|`game/GameEngine/Source/GameLogic/AI/AIAttackSquadStateChooseVictim.cpp`|Int, UnsignedInt, Real, Bool|1|949|
|1795|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateAiDoCommand.cpp`|Bool, Int, UnsignedInt, Real|1|330|
|1796|`game/GameEngine/Source/Common/Rva002DB290.cpp`|Int, UnsignedInt, Bool|1|44|
|1797|`game/GameEngine/Source/GameClient/ShadowSetOpacity.cpp`|Int, UnsignedInt, Real|1|169|
|1798|`game/GameEngine/Source/GameNetwork/FirewallHelperGetNATPortAllocationSchemeThunk.cpp`|Bool, Int, UnsignedShort|1|5|
|1799|`game/GameEngine/Source/GameNetwork/NetGameCommandMsg_dtor.cpp`|Int, UnsignedInt, UnsignedShort|1|95|
|1800|`game/GameEngine/Source/Common/PackShroudPixel.cpp`|Real, Int, UnsignedByte|1|213|
|1801|`game/GameEngine/Source/Common/RTS/BFMEActionObject_testStatus.cpp`|Int, UnsignedInt, Bool|1|41|
|1802|`game/GameEngine/Source/GameLogic/Object/Object_isStealthedAndUndetected.cpp`|Bool, Int, UnsignedInt|1|50|
|1803|`game/GameEngine/Source/GameLogic/Object/WeaponEffects/Made001E5F00Constructor.cpp`|Real, Int, Bool|1|58|
|1804|`game/GameEngine/Source/Common/System/RecorderHandleCRCMessage.cpp`|UnsignedInt, Int, Bool|1|133|
|1805|`game/GameEngine/Source/Common/native_packet_crc.cpp`|Int, UnsignedInt, UnsignedByte|1|42|
|1806|`game/GameEngine/Source/GameLogic/AI/AerialPathfinder_getNoFlyZoneHeight.cpp`|Int, Real, Bool|1|152|
|1807|`game/GameEngine/Source/GameLogic/Object/Update/AttributeModifierDefinitionStore_getValue.cpp`|Bool, Int, Real|1|57|
|1808|`game/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateCtor.cpp`|UnsignedByte, UnsignedInt, Bool|1|103|
|1809|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewZoomCameraBfme.cpp`|Real, Int, Bool|1|129|
|1810|`game/GameEngine/Source/GameNetwork/NAT_generatePortNumbers.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte|1|448|
|1811|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCameraUpdateBfme.cpp`|Real, Int, Bool|1|134|
|1812|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCameraUpdateAlternateBfme.cpp`|Real, Int, Bool|1|134|
|1813|`game/GameEngine/Source/Common/System/RadarLocalPixelToRadar.cpp`|Bool, Int, Real|1|327|
|1814|`game/GameEngine/Source/GameLogic/Object/Behavior/FlightDeckBehaviorModuleDataConstructor.cpp`|Int, Real, Bool|1|50|
|1815|`game/GameEngine/Source/GameLogic/Object/WeaponTemplate_getAttackRange.cpp`|Int, Real, Bool|1|89|
|1816|`game/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap_getTerrainNameAt_Bfme.cpp`|Int, Short, Real|1|283|
|1817|`game/GameEngine/Source/GameClient/BuffNuggetFXNugget_dtor_Thunk.cpp`|Real, Bool, UnsignedInt|1|175|
|1818|`game/GameEngine/Source/GameClient/DynamicDecalFXNuggetConstructor.cpp`|Real, Bool, UnsignedInt|1|130|
|1819|`game/GameEngine/Source/GameLogic/Object/WeaponTemplate_bfmeRangeBase.cpp`|Int, Real, Bool|1|148|
|1820|`game/GameEngine/Source/GameClient/Input/Mouse_drawCursorText.cpp`|Int, UnsignedByte, UnsignedInt|1|202|
|1821|`game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva0026C320SetStatus.cpp`|Int, Bool, UnsignedInt|1|148|
|1822|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewRotateCameraBfme.cpp`|Real, Int, Bool|1|167|
|1823|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBuffer_updateTopplingTree.cpp`|Int, UnsignedInt, Real|1|193|
|1824|`game/GameEngine/Source/GameLogic/System/CaveSystem_canSwitchIndexToIndex.cpp`|Int, UnsignedInt, Bool|1|89|
|1825|`game/GameEngine/Source/GameLogic/Object/Update/Rva002871F0Update.cpp`|Bool, UnsignedInt, Int|1|128|
|1826|`game/GameEngine/Source/GameClient/MapUtil_calcCRC_Thunk.cpp`|UnsignedInt, UnsignedByte, Int|1|457|
|1827|`game/GameEngine/Source/GameClient/GameTextManager_getStringCount.cpp`|Int, Bool, Char|1|272|
|1828|`game/GameEngine/Source/GameLogic/AI/PathfinderRva003DB900.cpp`|Int, UnsignedInt, UnsignedShort|1|201|
|1829|`game/GameEngine/Source/GameClient/MapUtil_WouldMapTransferGameInfo.cpp`|Bool, Int, UnsignedShort|1|188|
|1830|`game/GameEngine/Source/GameLogic/System/BfmeCellGridRva001B1AD0.cpp`|Int, UnsignedInt, Real|1|239|
|1831|`game/GameEngine/Source/GameClient/GUI/parseFont_Thunk.cpp`|Int, Real, Bool|1|309|
|1832|`game/GameEngine/Source/GameClient/BuffNuggetFXNuggetConstructor.cpp`|Real, Bool, UnsignedInt|1|273|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
