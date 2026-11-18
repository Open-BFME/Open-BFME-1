# Scalar alias contracts: cohort 131

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
|2216|`game/GameEngine/Source/GameLogic/AI/AIQuarrelState_update.cpp`|Bool, UnsignedInt|1|36|
|2217|`game/GameEngine/Source/GameLogic/Object/Weapon_getAttackRangeHeightAdjusted.cpp`|UnsignedInt, Real|1|99|
|2218|`game/GameEngine/Source/GameClient/TintDrawableFXNugget_parseColor.cpp`|Real, Int|1|169|
|2219|`game/GameEngine/Source/GameLogic/Object/BitFlags192Xfer.cpp`|Int, UnsignedByte|1|342|
|2220|`game/GameEngine/Source/Common/BitFlags86Xfer.cpp`|Int, UnsignedByte|1|151|
|2221|`game/GameEngine/Source/Common/BitFlags116Xfer.cpp`|Int, UnsignedByte|1|248|
|2222|`game/GameEngine/Source/Common/QuickMatchPreferences_isMapSelected.cpp`|Int, Bool|1|106|
|2223|`game/GameEngine/Source/Common/RTS/ClosestKindOfDataConstructor.cpp`|UnsignedInt, Real|1|107|
|2224|`game/GameEngine/Source/Common/Thing/ThingTemplateShadowSelector_usePluralShadowName.cpp`|Int, Bool|1|47|
|2225|`game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogicMaximumPathfindExtent.cpp`|Real, Int|1|127|
|2226|`game/GameEngine/Source/GameLogic/Object/Update/Gen002569F0SetStatus.cpp`|Int, Bool|1|79|
|2227|`game/GameEngine/Source/GameLogic/Object/Update/BfmeAttrERTCopyConstructor.cpp`|Int, Bool|1|511|
|2228|`game/GameEngine/Source/GameLogic/AI/PathfindCellFlagsCompatible00402390.cpp`|Bool, UnsignedInt|1|90|
|2229|`game/GameEngine/Source/GameClient/EvaCheck_trigger.cpp`|Bool, Real|1|121|
|2230|`game/GameEngine/Source/Common/BitFlags304Xfer.cpp`|Int, UnsignedByte|1|271|
|2231|`game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain_calcBestGarrisonPosition.cpp`|Int, Bool|1|114|
|2232|`game/GameEngineDevice/Source/W3DDevice/GameClient/Rva0078AC80ClipToRenderTarget.cpp`|Bool, Real|1|207|
|2233|`game/GameEngine/Source/Common/BitFlags304BuildDescription.cpp`|Int, Bool|1|168|
|2234|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroud_fillShroudData.cpp`|UnsignedByte, UnsignedShort|1|142|
|2235|`game/GameEngine/Source/GameNetwork/ConnectionManager_areAllQueuesEmptyTwin.cpp`|Bool, Int|1|41|
|2236|`game/GameEngine/Source/Common/Rva003A2270Find.cpp`|Real, Bool|1|185|
|2237|`game/Libraries/Source/WWVegas/WWLib/RvaDequeInitializeMap00644D70.cpp`|Int, Bool, UnsignedInt, UnsignedShort|1|189|
|2238|`game/GameEngine/Source/GameLogic/Object/Damage/EvacuateDamageModuleDataConstructor.cpp`|Int, Real|1|101|
|2239|`game/GameEngine/Source/GameNetwork/Network_AllCommandsReady.cpp`|UnsignedInt, Bool|1|41|
|2240|`game/GameEngine/Source/GameLogic/Object/Rva001CDBE0Ready.cpp`|Bool, UnsignedInt|1|56|
|2241|`game/GameEngine/Source/Common/Gen_003BEBA0Find.cpp`|Int, UnsignedShort|1|218|
|2242|`game/GameEngine/Source/Common/Rva003EEB50_checkForTargetFwd.cpp`|Int, Bool|1|50|
|2243|`game/GameEngine/Source/Common/INI/Rva000697B0ScanTangentAngle.cpp`|Int, Real|1|136|
|2244|`game/GameEngine/Source/GameLogic/Object/WeaponEffects/Made001E5BC0Constructor.cpp`|Int, Real|1|36|
|2245|`game/GameEngine/Source/Common/Rva0087F9C0Flag.cpp`|Int, UnsignedShort|1|143|
|2246|`game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadarFormatCaps_supportTextureFormat.cpp`|Bool, Int|1|110|
|2247|`game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogicGetExtent.cpp`|Real, Int|1|171|
|2248|`game/GameEngine/Source/Common/BitFlags86BuildDescription.cpp`|Int, Bool|1|165|
|2249|`game/GameEngine/Source/Common/BitFlags181Xfer.cpp`|Int, UnsignedByte|1|111|
|2250|`game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006DFDB0Ray.cpp`|Real, Int|1|316|
|2251|`game/GameEngine/Source/Common/System/GeometryParseMinorRadius.cpp`|Bool, Real|1|68|
|2252|`game/GameEngine/Source/GameNetwork/FrameData_ackCommandCount.cpp`|UnsignedInt, Int|1|47|
|2253|`game/GameEngine/Source/GameLogic/Object/PartitionFilterRelationshipCtor.cpp`|Bool, Int|1|39|
|2254|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroud_fillBorderShroudData.cpp`|UnsignedByte, UnsignedShort|1|118|
|2255|`game/GameEngine/Source/GameLogic/Object/PartitionFilterRejectBehind_allow.cpp`|Bool, Real|1|198|
|2256|`game/GameEngine/Source/Common/RTS/Handicap_readFromDict_Thunk.cpp`|Real, Bool|1|368|
|2257|`game/GameEngine/Source/GameClient/GUI/Rva0052DB10ListboxColumnText.cpp`|Int, Bool|1|136|
|2258|`game/GameEngine/Source/Common/Audio/Rva006A5570HandleSweep.cpp`|Int, Bool|1|109|
|2259|`game/GameEngine/Source/Common/DamageFX_doDamageFX.cpp`|Real, Bool|1|95|
|2260|`game/GameEngine/Source/GameLogic/Object/WeaponEffects/Made001E5940Constructor.cpp`|Int, Real|1|131|
|2261|`game/GameEngine/Source/Common/RTS/PlayerFindClosestByObject.cpp`|Real, Int|1|185|
|2262|`game/GameEngine/Source/GameClient/DrawableBFMERecordTransform.cpp`|UnsignedInt, Bool|1|217|
|2263|`game/GameEngine/Source/Common/Rva0060B900.cpp`|UnsignedByte, UnsignedInt|1|147|
|2264|`game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva0026CBE0SetStatus.cpp`|Int, Bool|1|80|
|2265|`game/GameEngine/Source/Common/Bfme5LinearFind133.cpp`|Int, UnsignedShort, Bool|1|133|
|2266|`game/GameEngine/Source/GameNetwork/DisconnectManagerIsPlayerVotedOutThunk.cpp`|Bool, Int|1|5|
|2267|`game/GameEngine/Source/Common/Q2FlagOwner_query.cpp`|Int, Bool|1|19|
|2268|`game/GameEngine/Source/GameLogic/System/VictorySystemApplyCells.cpp`|Int, UnsignedInt|1|199|
|2269|`game/GameEngine/Source/GameClient/DrawableBFMEBuffEffect.cpp`|UnsignedInt, Int, Real|1|144|
|2270|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderGetLayer.cpp`|Int, Bool|1|105|
|2271|`game/Libraries/Source/geometry/Rva0087FA50UpdateFlags.cpp`|Int, UnsignedShort|1|311|
|2272|`game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva0026C940SetStatus.cpp`|Int, Bool|1|117|
|2273|`game/GameEngine/Source/Common/Rva0029BF50CountThingTemplates.cpp`|Int, Bool|1|68|
|2274|`game/GameEngine/Source/GameClient/GUI/parseDrawCallback_Thunk.cpp`|Int, Bool|1|130|
|2275|`game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapXfer.cpp`|UnsignedByte, Bool|1|141|
|2276|`game/GameEngine/Source/GameClient/GUI/PositionStartSpotsGameInfo.cpp`|Int, Bool|1|167|
|2277|`game/GameEngine/Source/GameLogic/AI/Rva0017C8A0ChooseWeapon.cpp`|Bool, UnsignedInt|1|80|
|2278|`game/GameEngine/Source/GameLogic/System/BfmeCellDecay.cpp`|UnsignedInt, Real|1|369|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
