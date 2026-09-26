# BFME 1.03 INI schema

Read straight from `lotrbfme.exe`. Every
block keyword, field token and struct offset below is a byte read out of the
image, not an inference: the block registry is a linked list of static nodes
rooted at `0x0130CE50`, and each block-parse function points at a
NULL-terminated `FieldParse` array of
`{const char* token; INIFieldParseProc parse; const void* userData; Int offset;}`.

`Type` is the parse procedure the field dispatches to; where that procedure is
already recovered in `targets/game/reverse/functions.csv` it is named, otherwise its address
is given. `Offset` is the field's byte offset into the block's own struct, so
these tables double as the class layouts.

- **96** registered block keywords
- **81** with a decodable field table
- **1736** field entries

## Blocks

### `AerialPathfindNoFlyZone`

Parsed by `0x000B7E70`

_No field table: this block parses its body directly._

### `AIData`

Parsed by `0x0014E580` — `?parseAiDataDefinition@AI@@SAXPAVINI@@@Z`

Field table `0x01094B00` — 68 fields

| Field | Offset | Type |
|---|---|---|
| `StructureSeconds` | `0x004` | `Real` |
| `TeamSeconds` | `0x008` | `Real` |
| `Wealthy` | `0x00C` | `Int` |
| `Poor` | `0x010` | `Int` |
| `ForceIdleMSEC` | `0x014` | `DurationUnsignedInt` |
| `StructuresWealthyRate` | `0x018` | `Real` |
| `TeamsWealthyRate` | `0x01C` | `Real` |
| `StructuresPoorRate` | `0x020` | `Real` |
| `TeamsPoorRate` | `0x024` | `Real` |
| `TeamResourcesToStart` | `0x028` | `Real` |
| `GuardInnerModifierAI` | `0x02C` | `Real` |
| `GuardOuterModifierAI` | `0x030` | `Real` |
| `GuardInnerModifierHuman` | `0x034` | `Real` |
| `GuardOuterModifierHuman` | `0x038` | `Real` |
| `GuardChaseUnitsDuration` | `0x03C` | `DurationUnsignedInt` |
| `GuardEnemyScanRate` | `0x040` | `DurationUnsignedInt` |
| `GuardEnemyReturnScanRate` | `0x044` | `DurationUnsignedInt` |
| `SkirmishGroupFudgeDistance` | `0x058` | `Real` |
| `RepulsedDistance` | `0x060` | `Real` |
| `EnableRepulsors` | `0x064` | `Bool` |
| `AlertRangeModifier` | `0x04C` | `Real` |
| `AggressiveRangeModifier` | `0x050` | `Real` |
| `ForceSkirmishAI` | `0x065` | `Bool` |
| `RotateSkirmishBases` | `0x066` | `Bool` |
| `AttackUsesLineOfSight` | `0x067` | `Bool` |
| `AttackIgnoreInsignificantBuildings` | `0x068` | `Bool` |
| `AttackPriorityDistanceModifier` | `0x054` | `Real` |
| `MaxRecruitRadius` | `0x05C` | `Real` |
| `WallHeight` | `0x048` | `Real` |
| `SideInfo` | `0x000` | `0x0014BF10` |
| `AttackPriority` | `0x000` | `0x0014E130` |
| `SkirmishBuildList` | `0x000` | `0x0014C090` |
| `MinDistanceForGroup` | `0x06C` | `Real` |
| `FormationEnemyDistance` | `0x070` | `Real` |
| `MinClumpDensity` | `0x074` | `Real` |
| `InfantryPathfindDiameter` | `0x078` | `Int` |
| `VehiclePathfindDiameter` | `0x07C` | `Int` |
| `RebuildDelayTimeSeconds` | `0x080` | `Int` |
| `SupplyCenterSafeRadius` | `0x084` | `Real` |
| `AIDozerBoredRadiusModifier` | `0x088` | `Real` |
| `AICrushesInfantry` | `0x08C` | `Bool` |
| `MeleeApproachTolerance` | `0x090` | `Real` |
| `MeleeApproachDist` | `0x094` | `Real` |
| `MeleeAcquireLimitDist` | `0x098` | `Real` |
| `WadeWaterDepth` | `0x09C` | `Real` |
| `FormationColumnWidth` | `0x0A0` | `Real` |
| `FormationRowDepth` | `0x0A4` | `Real` |
| `FormationSquadSpacing` | `0x0A8` | `Real` |
| `FormationColumns` | `0x0B0` | `Int` |
| `NarrowPassageScale` | `0x0AC` | `Real` |
| `HordesWaitForHordes` | `0x0B5` | `Bool` |
| `AttackMoveUsesFormations` | `0x0B6` | `Bool` |
| `ForceHordesToLowLOD` | `0x0B7` | `Bool` |
| `AllowForestFires` | `0x0B8` | `Bool` |
| `UseFormations` | `0x0B9` | `Bool` |
| `WaitForOthers` | `0x0B4` | `Bool` |
| `AltCameraZoomOverride` | `0x0BC` | `Real` |
| `AltCameraPitchOverride` | `0x0C0` | `Real` |
| `MaxRetaliateDistance` | `0x0C4` | `Real` |
| `RetaliateFriendsRadius` | `0x0C8` | `Real` |
| `ChaseFromBehindLimit` | `0x0CC` | `Real` |
| `CastleSiegeStandBackDistance` | `0x0D0` | `Real` |
| `UseLowLODTrees` | `0x0D4` | `Bool` |
| `DisableTrees` | `0x0E8` | `Bool` |
| `LowLodTreeName` | `0x0D8` | `AsciiString` |
| `LowLodTreeNameNoGrab` | `0x0DC` | `AsciiString` |
| `LowLodTreeNameNoHarvest` | `0x0E0` | `AsciiString` |
| `LowLodTreeScale` | `0x0E4` | `Real` |

<details><summary><code>SideInfo</code> sub-block — 9 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `ResourceGatherersEasy` | `0x008` | `Int` |
| `ResourceGatherersNormal` | `0x00C` | `Int` |
| `ResourceGatherersHard` | `0x010` | `Int` |
| `BaseDefenseStructure1` | `0x1B8` | `AsciiString` |
| `SkillSet1` | `0x014` | `SkillSet` |
| `SkillSet2` | `0x068` | `SkillSet` |
| `SkillSet3` | `0x0BC` | `SkillSet` |
| `SkillSet4` | `0x110` | `SkillSet` |
| `SkillSet5` | `0x164` | `SkillSet` |

</details>

<details><summary><code>AttackPriority</code> sub-block — 2 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Default` | `0x008` | `Int` |
| `Target` | `0x00C` | `0x0014C8E0` |

</details>

<details><summary><code>SkirmishBuildList</code> sub-block — 1 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Structure` | `0x000` | `Structure` |

</details>

### `AmbientStream`

Parsed by `0x000B1590`

Field table `0x010813F8` — 21 fields

| Field | Offset | Type |
|---|---|---|
| `Filename` | `0x00C` | `AsciiString` |
| `Volume` | `0x010` | `PercentToReal` |
| `VolumeShift` | `0x014` | `PercentToReal` |
| `MinVolume` | `0x018` | `PercentToReal` |
| `PitchShift` | `0x000` | `0x000AFFF0` |
| `PlayPercent` | `0x024` | `PercentToReal` |
| `Delay` | `0x000` | `0x000AFF40` |
| `Limit` | `0x030` | `Int` |
| `Priority` | `0x034` | `IndexList` |
| `Type` | `0x038` | `BitString32` |
| `Control` | `0x03C` | `BitString32` |
| `Sounds` | `0x040` | `0x000B1DF0` |
| `Attack` | `0x050` | `0x000B1DF0` |
| `Decay` | `0x060` | `0x000B1DF0` |
| `MinRange` | `0x074` | `Real` |
| `MaxRange` | `0x078` | `Real` |
| `LowPassCutoff` | `0x070` | `PercentToReal` |
| `ReverbEffectLevel` | `0x07C` | `PercentToReal` |
| `DryLevel` | `0x080` | `PercentToReal` |
| `SubmixSlider` | `0x088` | `IndexList` |
| `VolumeSliderMultiplier` | `0x08C` | `0x000B0990` |

### `AnimationSoundClientBehaviorGlobalSetting`

Parsed by `0x004093C0`

Field table `0x010F03E8` — 1 fields

| Field | Offset | Type |
|---|---|---|
| `MinMicrophoneDistanceToDirty` | `0x000` | `Real` |

### `Armor`

Parsed by `0x001B09B0` — `?parseArmorDefinition@ArmorStore@@SAXPAVINI@@@Z`

Field table `0x0109C874` — 2 fields

| Field | Offset | Type |
|---|---|---|
| `DamageScalar` | `0x000` | `DamageScalar` |
| `Armor` | `0x000` | `ArmorCoefficients` |

### `AudioEvent`

Parsed by `0x000B1030`

Field table `0x010813F8` — 21 fields

| Field | Offset | Type |
|---|---|---|
| `Filename` | `0x00C` | `AsciiString` |
| `Volume` | `0x010` | `PercentToReal` |
| `VolumeShift` | `0x014` | `PercentToReal` |
| `MinVolume` | `0x018` | `PercentToReal` |
| `PitchShift` | `0x000` | `0x000AFFF0` |
| `PlayPercent` | `0x024` | `PercentToReal` |
| `Delay` | `0x000` | `0x000AFF40` |
| `Limit` | `0x030` | `Int` |
| `Priority` | `0x034` | `IndexList` |
| `Type` | `0x038` | `BitString32` |
| `Control` | `0x03C` | `BitString32` |
| `Sounds` | `0x040` | `0x000B1DF0` |
| `Attack` | `0x050` | `0x000B1DF0` |
| `Decay` | `0x060` | `0x000B1DF0` |
| `MinRange` | `0x074` | `Real` |
| `MaxRange` | `0x078` | `Real` |
| `LowPassCutoff` | `0x070` | `PercentToReal` |
| `ReverbEffectLevel` | `0x07C` | `PercentToReal` |
| `DryLevel` | `0x080` | `PercentToReal` |
| `SubmixSlider` | `0x088` | `IndexList` |
| `VolumeSliderMultiplier` | `0x08C` | `0x000B0990` |

### `AudioLOD`

Parsed by `0x0007D560` — `?parseAudioLODDefinition@INI@@SAXPAV1@@Z`

Field table `0x010768D0` — 3 fields

| Field | Offset | Type |
|---|---|---|
| `MaximumAmbientStreams` | `0x000` | `Int` |
| `AllowDolby` | `0x004` | `Bool` |
| `AllowReverb` | `0x005` | `Bool` |

### `AudioLowMHz`

Parsed by `0x0007BE70` — `?parseAudioLowMHz@@YAXPAVINI@@@Z`

_No field table: this block parses its body directly._

### `AudioSettings`

Parsed by `0x000B4B70`

Field table `0x01081D60` — 52 fields

| Field | Offset | Type |
|---|---|---|
| `AudioRoot` | `0x000` | `AsciiString` |
| `SoundsFolder` | `0x004` | `AsciiString` |
| `MusicFolder` | `0x008` | `AsciiString` |
| `StreamingFolder` | `0x00C` | `AsciiString` |
| `AmbientStreamFolder` | `0x010` | `AsciiString` |
| `SoundsExtension` | `0x014` | `AsciiString` |
| `UseDigital` | `0x018` | `Bool` |
| `UseMidi` | `0x019` | `Bool` |
| `OutputRate` | `0x01C` | `Int` |
| `OutputBits` | `0x020` | `Int` |
| `OutputChannels` | `0x024` | `Int` |
| `SampleCount2D` | `0x028` | `Int` |
| `SampleCount3D` | `0x02C` | `Int` |
| `StreamCount` | `0x030` | `Int` |
| `MixaheadLatency` | `0x048` | `UnsignedInt` |
| `MixaheadLatencyDuringMovies` | `0x04C` | `UnsignedInt` |
| `3DBufferLengthMS` | `0x050` | `UnsignedInt` |
| `3DBufferCallbackCallsPerBufferLength` | `0x054` | `UnsignedInt` |
| `AutomaticSubtitleDurationMS` | `0x058` | `Int` |
| `AutomaticSubtitleWindowWidth` | `0x05C` | `Int` |
| `AutomaticSubtitleLines` | `0x060` | `Int` |
| `AutomaticSubtitleWindowColor` | `0x064` | `ColorInt` |
| `AutomaticSubtitleTextColor` | `0x068` | `ColorInt` |
| `ForceResetTimeSeconds` | `0x06C` | `Int` |
| `EmergencyResetTimeSeconds` | `0x070` | `Int` |
| `MusicScriptLibraryName` | `0x074` | `AsciiString` |
| `MinSampleVolume` | `0x07C` | `PercentToReal` |
| `PositionDeltaForReverbRecheck` | `0x078` | `Real` |
| `GlobalMinRange` | `0x034` | `Int` |
| `GlobalMaxRange` | `0x038` | `Int` |
| `TimeToFadeAudio` | `0x03C` | `Int` |
| `AmbientStreamHysteresisVolume` | `0x040` | `Int` |
| `AudioFootprintInBytes` | `0x044` | `UnsignedInt` |
| `DefaultSoundVolume` | `0x080` | `PercentToReal` |
| `DefaultVoiceVolume` | `0x084` | `PercentToReal` |
| `DefaultMusicVolume` | `0x088` | `PercentToReal` |
| `DefaultMovieVolume` | `0x090` | `PercentToReal` |
| `DefaultAmbientVolume` | `0x08C` | `PercentToReal` |
| `MicrophonePreferredFractionCameraToGround` | `0x0A8` | `PercentToReal` |
| `MicrophonePullTowardsTerrainLookAtPointPercent` | `0x0C0` | `PercentToReal` |
| `MicrophoneMinDistanceToCamera` | `0x0B0` | `Real` |
| `MicrophoneMaxDistanceToCamera` | `0x0B8` | `Real` |
| `ZoomMinDistance` | `0x0C4` | `Real` |
| `ZoomMaxDistance` | `0x0CC` | `Real` |
| `ZoomSoundVolumePercentageAmount` | `0x0D4` | `PercentToReal` |
| `LivingWorldMicrophonePreferredFractionCameraToGround` | `0x0D8` | `PercentToReal` |
| `LivingWorldMicrophoneMinDistanceToCamera` | `0x0E0` | `Real` |
| `LivingWorldMicrophoneMaxDistanceToCamera` | `0x0E8` | `Real` |
| `LivingWorldZoomMinDistance` | `0x0F4` | `Real` |
| `LivingWorldZoomMaxDistance` | `0x0FC` | `Real` |
| `LivingWorldMicrophonePullTowardsTerrainLookAtPointPercent` | `0x0F0` | `PercentToReal` |
| `LivingWorldZoomSoundVolumePercentageAmount` | `0x104` | `PercentToReal` |

### `BannerType`

Parsed by `0x00584550`

Field table `0x0110B898` — 4 fields

| Field | Offset | Type |
|---|---|---|
| `FlagObj` | `0x000` | `AsciiString` |
| `GlowObj` | `0x004` | `AsciiString` |
| `WipeMovie` | `0x008` | `AsciiString` |
| `WipeFrame` | `0x00C` | `Int` |

### `BannerUI`

Parsed by `0x00584D20`

Field table `0x0110B984` — 2 fields

| Field | Offset | Type |
|---|---|---|
| `HeroFilter` | `0x01C` | `0x0039F470` |
| `UnitCategory` | `0x020` | `0x00584C30` |

<details><summary><code>UnitCategory</code> sub-block — 3 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Name` | `0x000` | `AsciiString` |
| `PluralName` | `0x004` | `AsciiString` |
| `Filter` | `0x008` | `0x0039F470` |

</details>

### `BenchProfile`

Parsed by `0x0007C7F0` — `?parseBenchProfile@INI@@SAXPAV1@@Z`

_No field table: this block parses its body directly._

### `Bridge`

Parsed by `0x000C2D70`

Field table `0x01114BF0` — 22 fields

| Field | Offset | Type |
|---|---|---|
| `BridgeScale` | `0x01C` | `Real` |
| `ScaffoldObjectName` | `0x020` | `AsciiString` |
| `ScaffoldSupportObjectName` | `0x024` | `AsciiString` |
| `RadarColor` | `0x028` | `RGBColor` |
| `TransitionEffectsHeight` | `0x144` | `Real` |
| `NumFXPerType` | `0x148` | `Int` |
| `BridgeModelName` | `0x034` | `AsciiString` |
| `Texture` | `0x038` | `AsciiString` |
| `BridgeModelNameDamaged` | `0x03C` | `AsciiString` |
| `TextureDamaged` | `0x040` | `AsciiString` |
| `BridgeModelNameReallyDamaged` | `0x044` | `AsciiString` |
| `TextureReallyDamaged` | `0x048` | `AsciiString` |
| `BridgeModelNameBroken` | `0x04C` | `AsciiString` |
| `TextureBroken` | `0x050` | `AsciiString` |
| `TowerObjectNameFromLeft` | `0x054` | `AsciiString` |
| `TowerObjectNameFromRight` | `0x058` | `AsciiString` |
| `TowerObjectNameToLeft` | `0x05C` | `AsciiString` |
| `TowerObjectNameToRight` | `0x060` | `AsciiString` |
| `DamagedToSound` | `0x068` | `AsciiString` |
| `RepairedToSound` | `0x0D8` | `AsciiString` |
| `TransitionToOCL` | `0x000` | `TransitionToOCL` |
| `TransitionToFX` | `0x000` | `TransitionToFX` |

### `Campaign`

Parsed by `0x005BCF20` — `?parseCampaignDefinition@INI@@SAXPAV1@@Z`

Field table `0x0110F590` — 4 fields

| Field | Offset | Type |
|---|---|---|
| `Mission` | `0x000` | `MissionPart` |
| `FirstMission` | `0x008` | `AsciiString` |
| `CampaignNameLabel` | `0x00C` | `AsciiString` |
| `FinalVictoryMovie` | `0x014` | `AsciiString` |

<details><summary><code>Mission</code> sub-block — 14 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Map` | `0x008` | `AsciiString` |
| `NextMission` | `0x00C` | `AsciiString` |
| `IntroMovie` | `0x010` | `AsciiString` |
| `ObjectiveLine0` | `0x014` | `AsciiString` |
| `ObjectiveLine1` | `0x018` | `AsciiString` |
| `ObjectiveLine2` | `0x01C` | `AsciiString` |
| `ObjectiveLine3` | `0x020` | `AsciiString` |
| `ObjectiveLine4` | `0x024` | `AsciiString` |
| `BriefingVoice` | `0x028` | `AudioEventRTS` |
| `UnitNames0` | `0x09C` | `AsciiString` |
| `UnitNames1` | `0x0A0` | `AsciiString` |
| `UnitNames2` | `0x0A4` | `AsciiString` |
| `LocationNameLabel` | `0x098` | `AsciiString` |
| `VoiceLength` | `0x0A8` | `Int` |

</details>

### `ChildObject`

Parsed by `0x000C2930`

_No field table: this block parses its body directly._

### `CloudBreakEffect`

Parsed by `0x0040B270`

Field table `0x010F0620` — 1 fields

| Field | Offset | Type |
|---|---|---|
| `SunbeamObject` | `0x000` | `AsciiString` |

### `CloudEffect`

Parsed by `0x0040BAF0`

Field table `0x010F0690` — 26 fields

| Field | Offset | Type |
|---|---|---|
| `CloudTexture` | `0x000` | `AsciiString` |
| `DarkCloudTexture` | `0x004` | `AsciiString` |
| `AlphaTexture` | `0x008` | `AsciiString` |
| `PropagateSpeed` | `0x00C` | `Real` |
| `Angle` | `0x010` | `Int` |
| `DissipateTexture` | `0x014` | `AsciiString` |
| `DissipateStartLevel` | `0x018` | `Real` |
| `DissipateSpeed` | `0x01C` | `Real` |
| `DarkeningFactor` | `0x020` | `RGBColor` |
| `DarkeningRate` | `0x02C` | `Int` |
| `LighteningRate` | `0x030` | `Int` |
| `CloudScrollSpeed` | `0x034` | `Real` |
| `DissipateRateScale` | `0x038` | `Real` |
| `LightningShadows` | `0x03C` | `Bool` |
| `JitterLightningLightPosition` | `0x03D` | `Bool` |
| `JitterLightningLightIntensity` | `0x03E` | `Bool` |
| `LightningChance` | `0x040` | `Real` |
| `LightningShadowColor` | `0x044` | `RGBColor` |
| `LightningShadowIntensity` | `0x050` | `Real` |
| `LightningDuration` | `0x054` | `GameClientRandomVariable` |
| `LightningFrequency` | `0x060` | `Real` |
| `LightningIntensity` | `0x064` | `GameClientRandomVariable` |
| `LightningLightPosition1` | `0x070` | `Coord2D` |
| `LightningLightPosition2` | `0x078` | `Coord2D` |
| `LightningLightPosition3` | `0x080` | `Coord2D` |
| `LightningFX` | `0x088` | `AsciiString` |

### `CommandButton`

Parsed by `0x000B7F80`

Field table `0x010FA3B8` — 54 fields

| Field | Offset | Type |
|---|---|---|
| `Command` | `0x010` | `Command` |
| `Options` | `0x018` | `BitString32` |
| `Object` | `0x01C` | `ThingTemplate` |
| `Upgrade` | `0x020` | `UpgradeTemplate` |
| `NeededUpgrade` | `0x024` | `UpgradeTemplate` |
| `BuildUpgrades` | `0x028` | `AsciiStringVector` |
| `WeaponSlot` | `0x06C` | `LookupList` |
| `WeaponSlotToggle1` | `0x070` | `LookupList` |
| `WeaponSlotToggle2` | `0x074` | `LookupList` |
| `WeaponSlotToggle3` | `0x078` | `LookupList` |
| `FlagsUsedForToggle` | `0x07C` | `0x001EB560` |
| `MaxShotsToFire` | `0x080` | `Int` |
| `Science` | `0x084` | `0x000BCD80` |
| `SpecialPower` | `0x034` | `SpecialPowerTemplate` |
| `TextLabel` | `0x044` | `AsciiStringVector` |
| `DescriptLabel` | `0x050` | `AsciiStringVector` |
| `PurchasedLabel` | `0x05C` | `AsciiString` |
| `ConflictingLabel` | `0x060` | `AsciiString` |
| `LacksPrerequisiteLabel` | `0x064` | `AsciiString` |
| `ButtonImage` | `0x094` | `AsciiStringVector` |
| `CursorName` | `0x03C` | `AsciiString` |
| `InvalidCursorName` | `0x040` | `AsciiString` |
| `ButtonBorderType` | `0x090` | `LookupList` |
| `RadiusCursorType` | `0x038` | `IndexList` |
| `UnitSpecificSound` | `0x0A8` | `0x000BD640` |
| `UnitSpecificSoundGroup` | `0x0B4` | `0x000BD640` |
| `UnitSpecificSound2` | `0x0C0` | `0x000BD640` |
| `UnitSpecificSoundGroup2` | `0x0CC` | `0x000BD640` |
| `SetAutoAbilityUnitSound` | `0x0D8` | `0x000BD640` |
| `SetAutoAbilityUnitSoundGroup` | `0x0E4` | `0x000BD640` |
| `SetAutoAbilityUnitSound2` | `0x0F0` | `0x000BD640` |
| `SetAutoAbilityUnitSoundGroup2` | `0x0FC` | `0x000BD640` |
| `UnsetAutoAbilityUnitSound` | `0x108` | `0x000BD640` |
| `UnsetAutoAbilityUnitSoundGroup` | `0x114` | `0x000BD640` |
| `UnsetAutoAbilityUnitSound2` | `0x120` | `0x000BD640` |
| `UnsetAutoAbilityUnitSoundGroup2` | `0x12C` | `0x000BD640` |
| `DoubleClick` | `0x14C` | `Bool` |
| `Radial` | `0x14D` | `Bool` |
| `ShowProductionCount` | `0x150` | `Bool` |
| `InPalantir` | `0x14E` | `Bool` |
| `IsClickable` | `0x151` | `Bool` |
| `ShowButton` | `0x152` | `Bool` |
| `RequireLevel` | `0x154` | `Int` |
| `RequiresValidContainer` | `0x153` | `Bool` |
| `AutoAbility` | `0x158` | `Bool` |
| `AffectsAllies` | `0x174` | `Bool` |
| `AffectsKindOf` | `0x15C` | `0x00129810` |
| `TriggerWhenReady` | `0x175` | `Bool` |
| `PresetRange` | `0x178` | `Real` |
| `AutoDelay` | `0x17C` | `Real` |
| `NeedDamagedTarget` | `0x180` | `Bool` |
| `CommandTrigger` | `0x184` | `AsciiString` |
| `EnableOnModelCondition` | `0x188` | `0x00369AD0` |
| `DisableOnModelCondition` | `0x1B0` | `0x00369AD0` |

### `CommandMap`

Parsed by `0x005B71A0` — `?parseMetaMapDefinition@INI@@SAXPAV1@@Z`

Field table `0x0110E570` — 7 fields

| Field | Offset | Type |
|---|---|---|
| `Key` | `0x008` | `LookupList` |
| `Transition` | `0x00C` | `LookupList` |
| `Modifiers` | `0x010` | `LookupList` |
| `UseableIn` | `0x014` | `BitString32` |
| `Category` | `0x018` | `LookupList` |
| `Description` | `0x01C` | `AndTranslateLabel` |
| `DisplayName` | `0x020` | `AndTranslateLabel` |

### `CommandSet`

Parsed by `0x004A2150` — `?newCommandButtonOverride@ControlBar@@IAEPAVCommandButton@@PAV2@@Z`

Field table `0x010FB5E0` — 20 fields

| Field | Offset | Type |
|---|---|---|
| `1` | `0x010` | `0x0049C7C0` |
| `2` | `0x010` | `0x0049C7C0` |
| `3` | `0x010` | `0x0049C7C0` |
| `4` | `0x010` | `0x0049C7C0` |
| `5` | `0x010` | `0x0049C7C0` |
| `6` | `0x010` | `0x0049C7C0` |
| `7` | `0x010` | `0x0049C7C0` |
| `8` | `0x010` | `0x0049C7C0` |
| `9` | `0x010` | `0x0049C7C0` |
| `10` | `0x010` | `0x0049C7C0` |
| `11` | `0x010` | `0x0049C7C0` |
| `12` | `0x010` | `0x0049C7C0` |
| `13` | `0x010` | `0x0049C7C0` |
| `14` | `0x010` | `0x0049C7C0` |
| `15` | `0x010` | `0x0049C7C0` |
| `16` | `0x010` | `0x0049C7C0` |
| `17` | `0x010` | `0x0049C7C0` |
| `18` | `0x010` | `0x0049C7C0` |
| `19` | `0x010` | `0x0049C7C0` |
| `20` | `0x010` | `0x0049C7C0` |

### `ControlBarResizer`

Parsed by `0x004AAD10` — `?parseControlBarResizerDefinition@INI@@SAXPAV1@@Z`

_No field table: this block parses its body directly._

### `ControlBarScheme`

Parsed by `0x000B8070`

Field table `0x010FC430` — 68 fields

| Field | Offset | Type |
|---|---|---|
| `ImagePart` | `0x000` | `ImagePart` |
| `AnimatingPart` | `0x000` | `AnimatingPart` |
| `ScreenCreationRes` | `0x004` | `ICoord2D` |
| `Side` | `0x00C` | `AsciiString` |
| `QueueButtonImage` | `0x010` | `MappedImage` |
| `RightHUDImage` | `0x014` | `MappedImage` |
| `BuildUpClockColor` | `0x018` | `ColorInt` |
| `ButtonBorderBuildColor` | `0x01C` | `ColorInt` |
| `CommandBarBorderColor` | `0x030` | `ColorInt` |
| `ButtonBorderActionColor` | `0x020` | `ColorInt` |
| `ButtonBorderUpgradeColor` | `0x024` | `ColorInt` |
| `ButtonBorderSystemColor` | `0x028` | `ColorInt` |
| `ButtonBorderAlteredColor` | `0x02C` | `ColorInt` |
| `OptionsButtonEnable` | `0x034` | `MappedImage` |
| `OptionsButtonHightlited` | `0x038` | `MappedImage` |
| `OptionsButtonPushed` | `0x03C` | `MappedImage` |
| `OptionsButtonDisabled` | `0x040` | `MappedImage` |
| `IdleWorkerButtonEnable` | `0x044` | `MappedImage` |
| `IdleWorkerButtonHightlited` | `0x048` | `MappedImage` |
| `IdleWorkerButtonPushed` | `0x04C` | `MappedImage` |
| `IdleWorkerButtonDisabled` | `0x050` | `MappedImage` |
| `BuddyButtonEnable` | `0x054` | `MappedImage` |
| `BuddyButtonHightlited` | `0x058` | `MappedImage` |
| `BuddyButtonPushed` | `0x05C` | `MappedImage` |
| `BuddyButtonDisabled` | `0x060` | `MappedImage` |
| `BeaconButtonEnable` | `0x064` | `MappedImage` |
| `BeaconButtonHightlited` | `0x068` | `MappedImage` |
| `BeaconButtonPushed` | `0x06C` | `MappedImage` |
| `BeaconButtonDisabled` | `0x070` | `MappedImage` |
| `GenBarButtonIn` | `0x074` | `MappedImage` |
| `GenBarButtonOn` | `0x078` | `MappedImage` |
| `ToggleButtonUpIn` | `0x07C` | `MappedImage` |
| `ToggleButtonUpOn` | `0x080` | `MappedImage` |
| `ToggleButtonUpPushed` | `0x084` | `MappedImage` |
| `ToggleButtonDownIn` | `0x088` | `MappedImage` |
| `ToggleButtonDownOn` | `0x08C` | `MappedImage` |
| `ToggleButtonDownPushed` | `0x090` | `MappedImage` |
| `GeneralButtonEnable` | `0x094` | `MappedImage` |
| `GeneralButtonHightlited` | `0x098` | `MappedImage` |
| `GeneralButtonPushed` | `0x09C` | `MappedImage` |
| `GeneralButtonDisabled` | `0x0A0` | `MappedImage` |
| `UAttackButtonEnable` | `0x0A4` | `MappedImage` |
| `UAttackButtonHightlited` | `0x0A8` | `MappedImage` |
| `UAttackButtonPushed` | `0x0AC` | `MappedImage` |
| `GenArrow` | `0x0BC` | `MappedImage` |
| `MinMaxButtonEnable` | `0x0B0` | `MappedImage` |
| `MinMaxButtonHightlited` | `0x0B4` | `MappedImage` |
| `MinMaxButtonPushed` | `0x0B8` | `MappedImage` |
| `MinMaxUL` | `0x0D0` | `ICoord2D` |
| `MinMaxLR` | `0x0D8` | `ICoord2D` |
| `GeneralUL` | `0x0E0` | `ICoord2D` |
| `GeneralLR` | `0x0E8` | `ICoord2D` |
| `UAttackUL` | `0x0F0` | `ICoord2D` |
| `UAttackLR` | `0x0F8` | `ICoord2D` |
| `OptionsUL` | `0x100` | `ICoord2D` |
| `OptionsLR` | `0x108` | `ICoord2D` |
| `WorkerUL` | `0x110` | `ICoord2D` |
| `WorkerLR` | `0x118` | `ICoord2D` |
| `ChatUL` | `0x120` | `ICoord2D` |
| `ChatLR` | `0x128` | `ICoord2D` |
| `BeaconUL` | `0x130` | `ICoord2D` |
| `BeaconLR` | `0x138` | `ICoord2D` |
| `PowerBarUL` | `0x140` | `ICoord2D` |
| `PowerBarLR` | `0x148` | `ICoord2D` |
| `MoneyUL` | `0x0C0` | `ICoord2D` |
| `MoneyLR` | `0x0C8` | `ICoord2D` |
| `CommandMarkerImage` | `0x154` | `MappedImage` |
| `ExpBarForegroundImage` | `0x150` | `MappedImage` |

<details><summary><code>ImagePart</code> sub-block — 4 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Position` | `0x004` | `ICoord2D` |
| `Size` | `0x00C` | `ICoord2D` |
| `ImageName` | `0x014` | `MappedImage` |
| `Layer` | `0x018` | `Int` |

</details>

<details><summary><code>AnimatingPart</code> sub-block — 5 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Name` | `0x000` | `AsciiString` |
| `Animation` | `0x004` | `LookupList` |
| `Duration` | `0x00C` | `DurationUnsignedInt` |
| `FinalPos` | `0x010` | `ICoord2D` |
| `ImagePart` | `0x000` | `AnimatingPartImage` |

</details>

### `CrateData`

Parsed by `0x0037A490`

Field table `0x010EA270` — 6 fields

| Field | Offset | Type |
|---|---|---|
| `CreationChance` | `0x010` | `Real` |
| `VeterancyLevel` | `0x014` | `IndexList` |
| `KilledByType` | `0x018` | `0x00129810` |
| `CrateObject` | `0x000` | `CrateCreationEntry` |
| `KillerScience` | `0x030` | `Science` |
| `OwnedByMaker` | `0x038` | `Bool` |

### `DamageFX`

Parsed by `0x00067A60` — `?parseDamageFXDefinition@DamageFXStore@@SAXPAVINI@@@Z`

Field table `0x010757C0` — 8 fields

| Field | Offset | Type |
|---|---|---|
| `AmountForMajorFX` | `0x000` | `Amount` |
| `MajorFX` | `0x000` | `MajorFXList` |
| `MinorFX` | `0x000` | `MinorFXList` |
| `ThrottleTime` | `0x000` | `Time` |
| `VeterancyAmountForMajorFX` | `0x000` | `Amount` |
| `VeterancyMajorFX` | `0x000` | `MajorFXList` |
| `VeterancyMinorFX` | `0x000` | `MinorFXList` |
| `VeterancyThrottleTime` | `0x000` | `Time` |

### `DebugCommandMap`

Parsed by `0x005B7030`

Field table `0x0110E570` — 7 fields

| Field | Offset | Type |
|---|---|---|
| `Key` | `0x008` | `LookupList` |
| `Transition` | `0x00C` | `LookupList` |
| `Modifiers` | `0x010` | `LookupList` |
| `UseableIn` | `0x014` | `BitString32` |
| `Category` | `0x018` | `LookupList` |
| `Description` | `0x01C` | `AndTranslateLabel` |
| `DisplayName` | `0x020` | `AndTranslateLabel` |

### `DialogEvent`

Parsed by `0x000B1360`

Field table `0x010813F8` — 21 fields

| Field | Offset | Type |
|---|---|---|
| `Filename` | `0x00C` | `AsciiString` |
| `Volume` | `0x010` | `PercentToReal` |
| `VolumeShift` | `0x014` | `PercentToReal` |
| `MinVolume` | `0x018` | `PercentToReal` |
| `PitchShift` | `0x000` | `0x000AFFF0` |
| `PlayPercent` | `0x024` | `PercentToReal` |
| `Delay` | `0x000` | `0x000AFF40` |
| `Limit` | `0x030` | `Int` |
| `Priority` | `0x034` | `IndexList` |
| `Type` | `0x038` | `BitString32` |
| `Control` | `0x03C` | `BitString32` |
| `Sounds` | `0x040` | `0x000B1DF0` |
| `Attack` | `0x050` | `0x000B1DF0` |
| `Decay` | `0x060` | `0x000B1DF0` |
| `MinRange` | `0x074` | `Real` |
| `MaxRange` | `0x078` | `Real` |
| `LowPassCutoff` | `0x070` | `PercentToReal` |
| `ReverbEffectLevel` | `0x07C` | `PercentToReal` |
| `DryLevel` | `0x080` | `PercentToReal` |
| `SubmixSlider` | `0x088` | `IndexList` |
| `VolumeSliderMultiplier` | `0x08C` | `0x000B0990` |

### `DrawGroupInfo`

Parsed by `0x000B8200` — `?parseDrawGroupNumberDefinition@INI@@SAXPAV1@@Z`

Field table `0x01082958` — 12 fields

| Field | Offset | Type |
|---|---|---|
| `UsePlayerColor` | `0x009` | `Bool` |
| `ColorForText` | `0x00C` | `ColorInt` |
| `ColorForTextDropShadow` | `0x010` | `ColorInt` |
| `FontName` | `0x000` | `QuotedAsciiString` |
| `FontSize` | `0x004` | `Int` |
| `FontIsBold` | `0x008` | `Bool` |
| `DropShadowOffsetX` | `0x014` | `Int` |
| `DropShadowOffsetY` | `0x018` | `Int` |
| `DrawPositionXPixel` | `0x000` | `Int` |
| `DrawPositionXPercent` | `0x000` | `PercentToReal` |
| `DrawPositionYPixel` | `0x000` | `Int` |
| `DrawPositionYPercent` | `0x000` | `PercentToReal` |

### `DynamicGameLOD`

Parsed by `0x0007D470` — `?parseDynamicGameLODDefinition@INI@@SAXPAV1@@Z`

Field table `0x01076890` — 7 fields

| Field | Offset | Type |
|---|---|---|
| `MinimumFPS` | `0x000` | `Int` |
| `ParticleSkipMask` | `0x004` | `Int` |
| `DebrisSkipMask` | `0x008` | `Int` |
| `SlowDeathScale` | `0x00C` | `Real` |
| `MaximumAmbientStreams` | `0x000` | `Int` |
| `AllowDolby` | `0x004` | `Bool` |
| `AllowReverb` | `0x005` | `Bool` |

### `EmotionNugget`

Parsed by `0x0037B8A0`

Field table `0x010EA6A8` — 28 fields

| Field | Offset | Type |
|---|---|---|
| `CopyFrom` | `0x000` | `0x0037B1B0` |
| `Type` | `0x004` | `0x0037AD00` |
| `IgnoreIfUnitIdle` | `0x008` | `Bool` |
| `IgnoreIfUnitBusy` | `0x009` | `Bool` |
| `Duration` | `0x00C` | `DurationUnsignedInt` |
| `InactiveDuration` | `0x010` | `DurationUnsignedInt` |
| `InactiveDurationSameObject` | `0x014` | `DurationUnsignedInt` |
| `InactiveDurationSameType` | `0x018` | `DurationUnsignedInt` |
| `OnlyIfEnemyThreatAbove` | `0x01C` | `0x0037A960` |
| `OnlyIfEnemyThreatBelow` | `0x01C` | `0x0037A920` |
| `OnlyIfFriendThreatAbove` | `0x024` | `0x0037A960` |
| `OnlyIfFriendThreatBelow` | `0x024` | `0x0037A920` |
| `IgnoreIfAI` | `0x02C` | `Bool` |
| `IgnoreIfHuman` | `0x02D` | `Bool` |
| `StartFXList` | `0x030` | `FXList` |
| `UpdateFXList` | `0x034` | `FXList` |
| `EndFXList` | `0x038` | `FXList` |
| `AttributeModifier` | `0x03C` | `AsciiString` |
| `AttributeStartDelay` | `0x040` | `DurationUnsignedInt` |
| `AttributeModifierWhileEmotionActive` | `0x044` | `Bool` |
| `AttributeDuration` | `0x048` | `DurationUnsignedInt` |
| `AIState` | `0x04C` | `0x0037AD60` |
| `AILockDuration` | `0x050` | `DurationUnsignedInt` |
| `ModelConditions` | `0x054` | `0x0037A9A0` |
| `ModelConditionsClear` | `0x0A4` | `0x0037A9A0` |
| `ModelConditionsSetOnExit` | `0x0CC` | `0x00369AD0` |
| `ModelConditionsClearOnExit` | `0x07C` | `0x00369AD0` |
| `LuaEvent` | `0x0F4` | `AsciiString` |

### `ExperienceLevel`

Parsed by `0x00382460`

Field table `0x010EAB48` — 22 fields

| Field | Offset | Type |
|---|---|---|
| `RequiredExperience` | `0x010` | `Int` |
| `ExperienceAward` | `0x014` | `Int` |
| `ExperienceAwardOwnGuysDie` | `0x018` | `Int` |
| `TargetNames` | `0x01C` | `AsciiStringVector` |
| `AttributeModifiers` | `0x028` | `AsciiStringVector` |
| `LevelUpFx` | `0x000` | `0x00381A00` |
| `LevelUpOCL` | `0x040` | `StringAsNameKeyType` |
| `Upgrades` | `0x000` | `0x0037FBC0` |
| `ModelConditionState` | `0x000` | `0x0037D1A0` |
| `SelectionDecal` | `0x078` | `RadiusDecalTemplate` |
| `ShowLevelUpTint` | `0x0A8` | `Bool` |
| `LevelUpTintColor` | `0x0AC` | `RGBColor` |
| `LevelUpTintPreColorTime` | `0x0B8` | `Int` |
| `LevelUpTintPostColorTime` | `0x0BC` | `Int` |
| `LevelUpTintSustainColorTime` | `0x0C0` | `Int` |
| `LevelUpTintFrequency` | `0x0C4` | `Real` |
| `LevelUpTintAmplitude` | `0x0C8` | `Real` |
| `Rank` | `0x0CC` | `Int` |
| `InformUpdateModule` | `0x0D0` | `Bool` |
| `EmotionType` | `0x0D4` | `0x0037AD00` |
| `SinglePlayerOnly` | `0x0D1` | `Bool` |
| `MultiPlayerOnly` | `0x0D2` | `Bool` |

<details><summary><code>SelectionDecal</code> sub-block — 12 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Texture` | `0x000` | `AsciiString` |
| `Texture2` | `0x004` | `AsciiString` |
| `Style` | `0x008` | `BitString32` |
| `OpacityMin` | `0x00C` | `PercentToReal` |
| `OpacityMax` | `0x010` | `PercentToReal` |
| `OpacityThrobTime` | `0x014` | `Real` |
| `RotationsPerMinute` | `0x02C` | `Real` |
| `Color` | `0x018` | `ColorInt` |
| `OnlyVisibleToOwningPlayer` | `0x01C` | `Bool` |
| `MaxRadius` | `0x024` | `Real` |
| `MinRadius` | `0x020` | `Real` |
| `MaxSelectedUnits` | `0x028` | `UnsignedInt` |

</details>

### `ExperienceScalarTable`

Parsed by `0x00380400`

Field table `0x010EA91C` — 1 fields

| Field | Offset | Type |
|---|---|---|
| `Scalars` | `0x000` | `0x00380350` |

### `FactionVictoryData`

Parsed by `0x000C31B0` — `?removeSide@SidesList@@QAEXH@Z`

Field table `0x0109FBC8` — 5 fields

| Field | Offset | Type |
|---|---|---|
| `AllyDeathScaleFactor` | `0x004` | `Real` |
| `EnemyKillScaleFactor` | `0x008` | `Real` |
| `VictoryThreshold` | `0x010` | `Real` |
| `MapToCellVictoryRatio` | `0x00C` | `Real` |
| `MajorUnitValue` | `0x014` | `Real` |

### `FireEffect`

Parsed by `0x00421FB0` — `?parseFireEffect@@YAXPAVINI@@@Z`

Field table `0x010F1808` — 9 fields

| Field | Offset | Type |
|---|---|---|
| `Scale` | `0x000` | `Real` |
| `Blend` | `0x004` | `Real` |
| `BaseSaturation` | `0x024` | `Real` |
| `EffectSaturation` | `0x020` | `Real` |
| `BaseColor` | `0x014` | `RGBColor` |
| `EffectColor` | `0x008` | `RGBColor` |
| `Velocity` | `0x04C` | `Real` |
| `TextureCross` | `0x050` | `Real` |
| `TextureRepeatCount` | `0x054` | `Real` |

### `FontDefaultSettings`

Parsed by `0x00477320`

Field table `0x010F76AC` — 1 fields

| Field | Offset | Type |
|---|---|---|
| `Antialiased` | `0x008` | `Bool` |

### `FontSubstitution`

Parsed by `0x004779C0`

_No field table: this block parses its body directly._

### `FXList`

Parsed by `0x0042E130`

Field table `0x010F2118` — 18 fields

| Field | Offset | Type |
|---|---|---|
| `Sound` | `0x000` | `parse` |
| `EvaEvent` | `0x000` | `0x0042BAA0` |
| `RayEffect` | `0x000` | `0x0042BD10` |
| `LightPulse` | `0x000` | `parse` |
| `CameraShakerVolume` | `0x000` | `0x0042C1C0` |
| `ViewShake` | `0x000` | `parse` |
| `AttachedModel` | `0x000` | `0x0042C460` |
| `TerrainScorch` | `0x000` | `parse` |
| `ParticleSystem` | `0x000` | `0x0042CB80` |
| `ParticleSysBone` | `0x000` | `0x0042C980` |
| `FXListAtBonePos` | `0x000` | `0x0042C860` |
| `CursorParticleSystem` | `0x000` | `0x0042CCA0` |
| `DynamicDecal` | `0x000` | `0x0042BF50` |
| `Laser` | `0x000` | `0x0042C090` |
| `CullingInfo` | `0x000` | `0x00427840` |
| `TintDrawable` | `0x000` | `0x0042C740` |
| `BuffNugget` | `0x000` | `0x0042D680` |
| `PlayEvenIfShrouded` | `0x010` | `Bool` |

<details><summary><code>Sound</code> sub-block — 7 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `ObjectFilter` | `0x00C` | `0x0039F470` |
| `SourceObjectFilter` | `0x008` | `0x0039F470` |
| `RequiredSecondaryModelConditions` | `0x060` | `0x00369AD0` |
| `ExcludedSecondaryModelConditions` | `0x088` | `0x00369AD0` |
| `RequiredSourceModelConditions` | `0x010` | `0x00369AD0` |
| `ExcludedSourceModelConditions` | `0x038` | `0x00369AD0` |
| `StopIfNuggetPlayed` | `0x0B0` | `Bool` |

</details>

<details><summary><code>Sound</code> sub-block — 1 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Name` | `0x0B4` | `AsciiString` |

</details>

<details><summary><code>EvaEvent</code> sub-block — 3 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `EvaEventOwner` | `0x0B4` | `0x00425B80` |
| `EvaEventAlly` | `0x0B8` | `0x00425B80` |
| `EvaEventEnemy` | `0x0BC` | `0x00425B80` |

</details>

<details><summary><code>RayEffect</code> sub-block — 3 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Name` | `0x0B4` | `AsciiString` |
| `PrimaryOffset` | `0x0B8` | `Coord3D` |
| `SecondaryOffset` | `0x0C4` | `Coord3D` |

</details>

<details><summary><code>LightPulse</code> sub-block — 5 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Color` | `0x0B4` | `RGBColor` |
| `Radius` | `0x0C0` | `Real` |
| `RadiusAsPercentOfObjectSize` | `0x0C4` | `PercentToReal` |
| `IncreaseTime` | `0x0C8` | `DurationUnsignedInt` |
| `DecreaseTime` | `0x0CC` | `DurationUnsignedInt` |

</details>

<details><summary><code>CameraShakerVolume</code> sub-block — 3 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Radius` | `0x0C0` | `Real` |
| `Duration_Seconds` | `0x0C4` | `Real` |
| `Amplitude_Degrees` | `0x0C8` | `Real` |

</details>

<details><summary><code>ViewShake</code> sub-block — 1 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Type` | `0x0B4` | `ShakeType` |

</details>

<details><summary><code>AttachedModel</code> sub-block — 3 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Modelname` | `0x0B4` | `AsciiString` |
| `RandomlyRotate` | `0x0B8` | `Bool` |
| `ExpireTimer` | `0x0BC` | `Int` |

</details>

<details><summary><code>TerrainScorch</code> sub-block — 2 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Type` | `0x0B4` | `0x00427670` |
| `Radius` | `0x0B8` | `Real` |

</details>

<details><summary><code>ParticleSystem</code> sub-block — 24 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Name` | `0x0B4` | `AsciiString` |
| `Count` | `0x0B8` | `Int` |
| `Offset` | `0x0BC` | `Coord3D` |
| `Radius` | `0x0C8` | `GameClientRandomVariable` |
| `Height` | `0x0D4` | `GameClientRandomVariable` |
| `InitialDelay` | `0x0E0` | `GameClientRandomVariable` |
| `RotateX` | `0x0EC` | `AngleReal` |
| `RotateY` | `0x0F0` | `AngleReal` |
| `RotateZ` | `0x0F4` | `AngleReal` |
| `OrientToObject` | `0x0F8` | `Bool` |
| `Ricochet` | `0x101` | `Bool` |
| `AttachToObject` | `0x0F9` | `Bool` |
| `AttachToBone` | `0x0FC` | `AsciiString` |
| `CreateAtGroundHeight` | `0x100` | `Bool` |
| `CreateBoneOverride` | `0x104` | `AsciiString` |
| `CreateBoneAtTarget` | `0x10C` | `Bool` |
| `TargetBoneOverride` | `0x108` | `AsciiString` |
| `TargetCoeff` | `0x110` | `Real` |
| `SystemLife` | `0x114` | `Int` |
| `UseTargetOffset` | `0x118` | `Bool` |
| `SetTargetMatrix` | `0x119` | `Bool` |
| `TargetOffset` | `0x11C` | `Coord3D` |
| `OnlyIfOnLand` | `0x11A` | `Bool` |
| `OnlyIfOnWater` | `0x11B` | `Bool` |

</details>

<details><summary><code>FXListAtBonePos</code> sub-block — 2 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `FX` | `0x0B4` | `FXList` |
| `BoneName` | `0x0B8` | `AsciiString` |

</details>

<details><summary><code>CursorParticleSystem</code> sub-block — 6 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Anim2DTemplateName` | `0x0B4` | `AsciiString` |
| `BurstCount` | `0x0B8` | `UnsignedInt` |
| `ParticleLife` | `0x0BC` | `GameClientRandomVariable` |
| `SystemLife` | `0x0C8` | `GameClientRandomVariable` |
| `DriftVelX` | `0x0D4` | `GameClientRandomVariable` |
| `DriftVelY` | `0x0E0` | `GameClientRandomVariable` |

</details>

<details><summary><code>DynamicDecal</code> sub-block — 14 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `DecalName` | `0x0B4` | `AsciiString` |
| `Shader` | `0x0B8` | `IndexList` |
| `Size` | `0x0BC` | `Real` |
| `Color` | `0x0C0` | `RGBColor` |
| `Offset` | `0x0CC` | `Coord2D` |
| `OrientToObject` | `0x0D4` | `Bool` |
| `OpacityStart` | `0x0D8` | `UnsignedInt` |
| `OpacityFadeTimeOne` | `0x0DC` | `Real` |
| `OpacityPeak` | `0x0E0` | `UnsignedInt` |
| `OpacityPeakTime` | `0x0E4` | `Real` |
| `OpacityFadeTimeTwo` | `0x0E8` | `Real` |
| `OpacityEnd` | `0x0EC` | `UnsignedInt` |
| `StartingDelay` | `0x0F0` | `Real` |
| `Lifetime` | `0x0F4` | `Real` |

</details>

<details><summary><code>Laser</code> sub-block — 3 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `LaserName` | `0x0B4` | `AsciiString` |
| `LaserBackwards` | `0x0B8` | `Bool` |
| `TargetPositionOffsetFallback` | `0x0BC` | `Coord3D` |

</details>

<details><summary><code>TintDrawable</code> sub-block — 6 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Color` | `0x0B4` | `0x004276A0` |
| `PreColorTime` | `0x0C0` | `UnsignedInt` |
| `PostColorTime` | `0x0C4` | `UnsignedInt` |
| `SustainedColorTime` | `0x0C8` | `UnsignedInt` |
| `Frequency` | `0x0CC` | `Real` |
| `Amplitude` | `0x0D0` | `Real` |

</details>

<details><summary><code>BuffNugget</code> sub-block — 11 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `BuffType` | `0x0B4` | `IndexList` |
| `IsComplexBuff` | `0x0B8` | `Bool` |
| `BuffThingTemplate` | `0x0C0` | `AsciiString` |
| `BuffOrcTemplate` | `0x0C4` | `AsciiString` |
| `BuffInfantryTemplate` | `0x0C8` | `AsciiString` |
| `BuffCavalryTemplate` | `0x0CC` | `AsciiString` |
| `BuffTrollTemplate` | `0x0D0` | `AsciiString` |
| `BuffMumakilTemplate` | `0x0D4` | `AsciiString` |
| `BuffLifeTime` | `0x0BC` | `DurationUnsignedInt` |
| `Extrusion` | `0x0D8` | `Real` |
| `Color` | `0x0DC` | `RGBColor` |

</details>

### `FXParticleSystem`

Parsed by `0x005D1A70`

Field table `0x0110F92C` — 1 fields

| Field | Offset | Type |
|---|---|---|
| `System` | `0x000` | `parse` |

### `GameData`

Parsed by `0x00085C20`

Field table `0x01077018` — 447 fields

| Field | Offset | Type |
|---|---|---|
| `Windowed` | `0x029` | `Bool` |
| `XResolution` | `0x02C` | `Int` |
| `YResolution` | `0x030` | `Int` |
| `MapName` | `0x008` | `AsciiString` |
| `MoveHintName` | `0x00C` | `AsciiString` |
| `GenericDamageFieldName` | `0x010` | `AsciiString` |
| `GenericDamageWarningName` | `0x014` | `AsciiString` |
| `ShowProps` | `0x018` | `Bool` |
| `UseFPSLimit` | `0x01E` | `Bool` |
| `PushAsideShrubs` | `0x019` | `Bool` |
| `UseHighQualityVideo` | `0x01F` | `Bool` |
| `DumpAssetUsage` | `0x020` | `Bool` |
| `FramesPerSecondLimit` | `0x024` | `Int` |
| `DisablePixelShader` | `0x028` | `Bool` |
| `MaxShellScreens` | `0x034` | `Int` |
| `UseCloudMap` | `0x038` | `Bool` |
| `ShowWater` | `0x039` | `Bool` |
| `ShowRoads` | `0x03A` | `Bool` |
| `ShowTrees` | `0x03B` | `Bool` |
| `UseLightMap` | `0x044` | `Bool` |
| `BilinearTerrainTex` | `0x045` | `Bool` |
| `TrilinearTerrainTex` | `0x046` | `Bool` |
| `AnisotropicTerrainTex` | `0x047` | `Bool` |
| `MultiPassTerrain` | `0x04C` | `Bool` |
| `AdjustCliffTextures` | `0x04D` | `Bool` |
| `Use3WayTerrainBlends` | `0x040` | `Int` |
| `StretchTerrain` | `0x04E` | `Bool` |
| `UseHalfHeightMap` | `0x04F` | `Bool` |
| `UserDataLeafName` | `0x1288` | `QuotedAsciiString` |
| `UseReverseMouseScroll` | `0x03C` | `Bool` |
| `LiveCampaignMode` | `0x08E` | `Bool` |
| `HideLivingWorldRegions` | `0x08F` | `Bool` |
| `LivingWorldCampaignOverrride` | `0x094` | `Bool` |
| `LivingWorldTurbo` | `0x090` | `Bool` |
| `DrawEntireTerrain` | `0x050` | `Bool` |
| `TerrainLOD` | `0x054` | `IndexList` |
| `TerrainLODTargetTimeMS` | `0x05C` | `Int` |
| `RightMouseAlwaysScrolls` | `0x061` | `Bool` |
| `UseWaterPlane` | `0x062` | `Bool` |
| `UseCloudPlane` | `0x063` | `Bool` |
| `DownwindAngle` | `0x17C` | `Real` |
| `UseShadowVolumes` | `0x064` | `Bool` |
| `UseShadowDecals` | `0x065` | `Bool` |
| `ShowSelectedUnitMarker` | `0xA75` | `Bool` |
| `UseSimpleHordeDecals` | `0xA76` | `Bool` |
| `UseSimpleMergeDecals` | `0xA77` | `Bool` |
| `OpacityOfSimpleMergeDecals` | `0xA78` | `PercentToReal` |
| `TextureReductionFactor` | `0x068` | `Int` |
| `UseBehindBuildingMarker` | `0x070` | `Bool` |
| `WaterPositionX` | `0x074` | `Real` |
| `WaterPositionY` | `0x078` | `Real` |
| `WaterPositionZ` | `0x07C` | `Real` |
| `WaterExtentX` | `0x080` | `Real` |
| `WaterExtentY` | `0x084` | `Real` |
| `WaterType` | `0x088` | `Int` |
| `FeatherWater` | `0x098` | `Int` |
| `ShowSoftWaterEdge` | `0x08C` | `Bool` |
| `VertexWaterAvailableMaps1` | `0x09C` | `AsciiString` |
| `VertexWaterHeightClampLow1` | `0x0AC` | `Real` |
| `VertexWaterHeightClampHi1` | `0x0BC` | `Real` |
| `VertexWaterAngle1` | `0x0CC` | `AngleReal` |
| `VertexWaterXPosition1` | `0x0DC` | `Real` |
| `VertexWaterYPosition1` | `0x0EC` | `Real` |
| `VertexWaterZPosition1` | `0x0FC` | `Real` |
| `VertexWaterXGridCells1` | `0x10C` | `Int` |
| `VertexWaterYGridCells1` | `0x11C` | `Int` |
| `VertexWaterGridSize1` | `0x12C` | `Real` |
| `VertexWaterAttenuationA1` | `0x13C` | `Real` |
| `VertexWaterAttenuationB1` | `0x14C` | `Real` |
| `VertexWaterAttenuationC1` | `0x15C` | `Real` |
| `VertexWaterAttenuationRange1` | `0x16C` | `Real` |
| `VertexWaterAvailableMaps2` | `0x0A0` | `AsciiString` |
| `VertexWaterHeightClampLow2` | `0x0B0` | `Real` |
| `VertexWaterHeightClampHi2` | `0x0C0` | `Real` |
| `VertexWaterAngle2` | `0x0D0` | `AngleReal` |
| `VertexWaterXPosition2` | `0x0E0` | `Real` |
| `VertexWaterYPosition2` | `0x0F0` | `Real` |
| `VertexWaterZPosition2` | `0x100` | `Real` |
| `VertexWaterXGridCells2` | `0x110` | `Int` |
| `VertexWaterYGridCells2` | `0x120` | `Int` |
| `VertexWaterGridSize2` | `0x130` | `Real` |
| `VertexWaterAttenuationA2` | `0x140` | `Real` |
| `VertexWaterAttenuationB2` | `0x150` | `Real` |
| `VertexWaterAttenuationC2` | `0x160` | `Real` |
| `VertexWaterAttenuationRange2` | `0x170` | `Real` |
| `VertexWaterAvailableMaps3` | `0x0A4` | `AsciiString` |
| `VertexWaterHeightClampLow3` | `0x0B4` | `Real` |
| `VertexWaterHeightClampHi3` | `0x0C4` | `Real` |
| `VertexWaterAngle3` | `0x0D4` | `AngleReal` |
| `VertexWaterXPosition3` | `0x0E4` | `Real` |
| `VertexWaterYPosition3` | `0x0F4` | `Real` |
| `VertexWaterZPosition3` | `0x104` | `Real` |
| `VertexWaterXGridCells3` | `0x114` | `Int` |
| `VertexWaterYGridCells3` | `0x124` | `Int` |
| `VertexWaterGridSize3` | `0x134` | `Real` |
| `VertexWaterAttenuationA3` | `0x144` | `Real` |
| `VertexWaterAttenuationB3` | `0x154` | `Real` |
| `VertexWaterAttenuationC3` | `0x164` | `Real` |
| `VertexWaterAttenuationRange3` | `0x174` | `Real` |
| `VertexWaterAvailableMaps4` | `0x0A8` | `AsciiString` |
| `VertexWaterHeightClampLow4` | `0x0B8` | `Real` |
| `VertexWaterHeightClampHi4` | `0x0C8` | `Real` |
| `VertexWaterAngle4` | `0x0D8` | `AngleReal` |
| `VertexWaterXPosition4` | `0x0E8` | `Real` |
| `VertexWaterYPosition4` | `0x0F8` | `Real` |
| `VertexWaterZPosition4` | `0x108` | `Real` |
| `VertexWaterXGridCells4` | `0x118` | `Int` |
| `VertexWaterYGridCells4` | `0x128` | `Int` |
| `VertexWaterGridSize4` | `0x138` | `Real` |
| `VertexWaterAttenuationA4` | `0x148` | `Real` |
| `VertexWaterAttenuationB4` | `0x158` | `Real` |
| `VertexWaterAttenuationC4` | `0x168` | `Real` |
| `VertexWaterAttenuationRange4` | `0x178` | `Real` |
| `DefaultUnitHealingBuffFxList` | `0xAA4` | `AsciiString` |
| `DefaultStructureRepairBuffFxList` | `0xAA8` | `AsciiString` |
| `TimeAfterDamageUntilRepairAllowed` | `0xB50` | `UnsignedInt` |
| `DrawSkyBox` | `0x180` | `Bool` |
| `DefaultCameraMinHeight` | `0x184` | `Real` |
| `DefaultCameraMaxHeight` | `0x188` | `Real` |
| `DefaultCameraPitchAngle` | `0x18C` | `Real` |
| `DefaultCameraYawAngle` | `0x190` | `Real` |
| `DefaultCameraScrollSpeedScalar` | `0x194` | `Real` |
| `CameraLockHeightDelta` | `0xE58` | `Real` |
| `CameraEaseFactor` | `0xE64` | `Real` |
| `TerrainHeightAtEdgeOfMap` | `0x198` | `Real` |
| `UnitDamagedThreshold` | `0x19C` | `Real` |
| `UnitReallyDamagedThreshold` | `0x1A0` | `Real` |
| `GroundStiffness` | `0x1A4` | `Real` |
| `StructureStiffness` | `0x1A8` | `Real` |
| `Gravity` | `0x1AC` | `AccelerationReal` |
| `StealthFriendlyOpacity` | `0x1B0` | `PercentToReal` |
| `DefaultOcclusionDelay` | `0x1B4` | `DurationUnsignedInt` |
| `PartitionCellSize` | `0x1BC` | `Real` |
| `AmmoPipScaleFactor` | `0x1E8` | `Real` |
| `ContainerPipScaleFactor` | `0x1EC` | `Real` |
| `AmmoPipWorldOffset` | `0x1C0` | `Coord3D` |
| `ContainerPipWorldOffset` | `0x1CC` | `Coord3D` |
| `AmmoPipScreenOffset` | `0x1D8` | `Coord2D` |
| `ContainerPipScreenOffset` | `0x1E0` | `Coord2D` |
| `MaxTerrainTracks` | `0x1F0` | `Int` |
| `TimeOfDay` | `0x218` | `IndexList` |
| `Weather` | `0x21C` | `IndexList` |
| `MakeTrackMarks` | `0x220` | `Bool` |
| `HideGarrisonFlags` | `0x221` | `Bool` |
| `ForceModelsToFollowTimeOfDay` | `0x222` | `Bool` |
| `ForceModelsToFollowWeather` | `0x223` | `Bool` |
| `LevelGainAnimationName` | `0x200` | `AsciiString` |
| `LevelGainAnimationTime` | `0x204` | `Real` |
| `LevelGainAnimationZRise` | `0x208` | `Real` |
| `GetHealedAnimationName` | `0x20C` | `AsciiString` |
| `GetHealedAnimationTime` | `0x210` | `Real` |
| `GetHealedAnimationZRise` | `0x214` | `Real` |
| `TerrainLightingMorningAmbient` | `0x290` | `RGBColor` |
| `TerrainLightingMorningDiffuse` | `0x29C` | `RGBColor` |
| `TerrainLightingMorningLightPos` | `0x2A8` | `Coord3D` |
| `TerrainLightingAfternoonAmbient` | `0x2FC` | `RGBColor` |
| `TerrainLightingAfternoonDiffuse` | `0x308` | `RGBColor` |
| `TerrainLightingAfternoonLightPos` | `0x314` | `Coord3D` |
| `TerrainLightingEveningAmbient` | `0x368` | `RGBColor` |
| `TerrainLightingEveningDiffuse` | `0x374` | `RGBColor` |
| `TerrainLightingEveningLightPos` | `0x380` | `Coord3D` |
| `TerrainLightingNightAmbient` | `0x3D4` | `RGBColor` |
| `TerrainLightingNightDiffuse` | `0x3E0` | `RGBColor` |
| `TerrainLightingNightLightPos` | `0x3EC` | `Coord3D` |
| `TerrainObjectsLightingMorningAmbient` | `0x518` | `RGBColor` |
| `TerrainObjectsLightingMorningDiffuse` | `0x524` | `RGBColor` |
| `TerrainObjectsLightingMorningLightPos` | `0x530` | `Coord3D` |
| `TerrainObjectsLightingAfternoonAmbient` | `0x584` | `RGBColor` |
| `TerrainObjectsLightingAfternoonDiffuse` | `0x590` | `RGBColor` |
| `TerrainObjectsLightingAfternoonLightPos` | `0x59C` | `Coord3D` |
| `TerrainObjectsLightingEveningAmbient` | `0x5F0` | `RGBColor` |
| `TerrainObjectsLightingEveningDiffuse` | `0x5FC` | `RGBColor` |
| `TerrainObjectsLightingEveningLightPos` | `0x608` | `Coord3D` |
| `TerrainObjectsLightingNightAmbient` | `0x65C` | `RGBColor` |
| `TerrainObjectsLightingNightDiffuse` | `0x668` | `RGBColor` |
| `TerrainObjectsLightingNightLightPos` | `0x674` | `Coord3D` |
| `TerrainLightingMorningAmbient2` | `0x2B4` | `RGBColor` |
| `TerrainLightingMorningDiffuse2` | `0x2C0` | `RGBColor` |
| `TerrainLightingMorningLightPos2` | `0x2CC` | `Coord3D` |
| `TerrainLightingAfternoonAmbient2` | `0x320` | `RGBColor` |
| `TerrainLightingAfternoonDiffuse2` | `0x32C` | `RGBColor` |
| `TerrainLightingAfternoonLightPos2` | `0x338` | `Coord3D` |
| `TerrainLightingEveningAmbient2` | `0x38C` | `RGBColor` |
| `TerrainLightingEveningDiffuse2` | `0x398` | `RGBColor` |
| `TerrainLightingEveningLightPos2` | `0x3A4` | `Coord3D` |
| `TerrainLightingNightAmbient2` | `0x3F8` | `RGBColor` |
| `TerrainLightingNightDiffuse2` | `0x404` | `RGBColor` |
| `TerrainLightingNightLightPos2` | `0x410` | `Coord3D` |
| `TerrainObjectsLightingMorningAmbient2` | `0x53C` | `RGBColor` |
| `TerrainObjectsLightingMorningDiffuse2` | `0x548` | `RGBColor` |
| `TerrainObjectsLightingMorningLightPos2` | `0x554` | `Coord3D` |
| `TerrainObjectsLightingAfternoonAmbient2` | `0x5A8` | `RGBColor` |
| `TerrainObjectsLightingAfternoonDiffuse2` | `0x5B4` | `RGBColor` |
| `TerrainObjectsLightingAfternoonLightPos2` | `0x5C0` | `Coord3D` |
| `TerrainObjectsLightingEveningAmbient2` | `0x614` | `RGBColor` |
| `TerrainObjectsLightingEveningDiffuse2` | `0x620` | `RGBColor` |
| `TerrainObjectsLightingEveningLightPos2` | `0x62C` | `Coord3D` |
| `TerrainObjectsLightingNightAmbient2` | `0x680` | `RGBColor` |
| `TerrainObjectsLightingNightDiffuse2` | `0x68C` | `RGBColor` |
| `TerrainObjectsLightingNightLightPos2` | `0x698` | `Coord3D` |
| `TerrainLightingMorningAmbient3` | `0x2D8` | `RGBColor` |
| `TerrainLightingMorningDiffuse3` | `0x2E4` | `RGBColor` |
| `TerrainLightingMorningLightPos3` | `0x2F0` | `Coord3D` |
| `TerrainLightingAfternoonAmbient3` | `0x344` | `RGBColor` |
| `TerrainLightingAfternoonDiffuse3` | `0x350` | `RGBColor` |
| `TerrainLightingAfternoonLightPos3` | `0x35C` | `Coord3D` |
| `TerrainLightingEveningAmbient3` | `0x3B0` | `RGBColor` |
| `TerrainLightingEveningDiffuse3` | `0x3BC` | `RGBColor` |
| `TerrainLightingEveningLightPos3` | `0x3C8` | `Coord3D` |
| `TerrainLightingNightAmbient3` | `0x41C` | `RGBColor` |
| `TerrainLightingNightDiffuse3` | `0x428` | `RGBColor` |
| `TerrainLightingNightLightPos3` | `0x434` | `Coord3D` |
| `TerrainObjectsLightingMorningAmbient3` | `0x560` | `RGBColor` |
| `TerrainObjectsLightingMorningDiffuse3` | `0x56C` | `RGBColor` |
| `TerrainObjectsLightingMorningLightPos3` | `0x578` | `Coord3D` |
| `TerrainObjectsLightingAfternoonAmbient3` | `0x5CC` | `RGBColor` |
| `TerrainObjectsLightingAfternoonDiffuse3` | `0x5D8` | `RGBColor` |
| `TerrainObjectsLightingAfternoonLightPos3` | `0x5E4` | `Coord3D` |
| `TerrainObjectsLightingEveningAmbient3` | `0x638` | `RGBColor` |
| `TerrainObjectsLightingEveningDiffuse3` | `0x644` | `RGBColor` |
| `TerrainObjectsLightingEveningLightPos3` | `0x650` | `Coord3D` |
| `TerrainObjectsLightingNightAmbient3` | `0x6A4` | `RGBColor` |
| `TerrainObjectsLightingNightDiffuse3` | `0x6B0` | `RGBColor` |
| `TerrainObjectsLightingNightLightPos3` | `0x6BC` | `Coord3D` |
| `NumberGlobalLights` | `0xA58` | `Int` |
| `MaxTranslucentObjects` | `0xA44` | `Int` |
| `OccludedColorLuminanceScale` | `0xA54` | `Real` |
| `MaxRoadSegments` | `0xA5C` | `Int` |
| `MaxRoadVertex` | `0xA60` | `Int` |
| `MaxRoadIndex` | `0xA64` | `Int` |
| `MaxRoadTypes` | `0xA68` | `Int` |
| `ValuePerSupplyBox` | `0xB24` | `Int` |
| `SupplyBoxesPerTree` | `0xB28` | `Int` |
| `AudioOn` | `0xA6C` | `Bool` |
| `MusicOn` | `0xA6D` | `Bool` |
| `AmbientStreamsOn` | `0xA71` | `Bool` |
| `SoundsOn` | `0xA6E` | `Bool` |
| `Sounds3DOn` | `0xA6F` | `Bool` |
| `SpeechOn` | `0xA70` | `Bool` |
| `VideoOn` | `0xA73` | `Bool` |
| `DisableCameraMovements` | `0xA74` | `Bool` |
| `UseCameraInReplay` | `0xC0D` | `Bool` |
| `DebugAI` | `0xA88` | `Bool` |
| `DebugAIObstacles` | `0xA8C` | `Bool` |
| `ShowClientPhysics` | `0xA80` | `Bool` |
| `ShowTerrainNormals` | `0xA81` | `Bool` |
| `ShowObjectHealth` | `0xA8D` | `Bool` |
| `ShowTooltips` | `0xA8F` | `Bool` |
| `ParticleScale` | `0xAB4` | `Real` |
| `AutoFireParticleSmallPrefix` | `0xAB8` | `AsciiString` |
| `AutoFireParticleSmallSystem` | `0xABC` | `AsciiString` |
| `AutoFireParticleSmallMax` | `0xAC0` | `Int` |
| `AutoFireParticleMediumPrefix` | `0xAC4` | `AsciiString` |
| `AutoFireParticleMediumSystem` | `0xAC8` | `AsciiString` |
| `AutoFireParticleMediumMax` | `0xACC` | `Int` |
| `AutoFireParticleLargePrefix` | `0xAD0` | `AsciiString` |
| `AutoFireParticleLargeSystem` | `0xAD4` | `AsciiString` |
| `AutoFireParticleLargeMax` | `0xAD8` | `Int` |
| `AutoSmokeParticleSmallPrefix` | `0xADC` | `AsciiString` |
| `AutoSmokeParticleSmallSystem` | `0xAE0` | `AsciiString` |
| `AutoSmokeParticleSmallMax` | `0xAE4` | `Int` |
| `AutoSmokeParticleMediumPrefix` | `0xAE8` | `AsciiString` |
| `AutoSmokeParticleMediumSystem` | `0xAEC` | `AsciiString` |
| `AutoSmokeParticleMediumMax` | `0xAF0` | `Int` |
| `AutoSmokeParticleLargePrefix` | `0xAF4` | `AsciiString` |
| `AutoSmokeParticleLargeSystem` | `0xAF8` | `AsciiString` |
| `AutoSmokeParticleLargeMax` | `0xAFC` | `Int` |
| `AutoAflameParticlePrefix` | `0xB00` | `AsciiString` |
| `AutoAflameParticleSystem` | `0xB04` | `AsciiString` |
| `AutoAflameParticleMax` | `0xB08` | `Int` |
| `BuildSpeed` | `0xB2C` | `Real` |
| `MinDistFromEdgeOfMapForBuild` | `0xB30` | `Real` |
| `SupplyBuildBorder` | `0xB34` | `Real` |
| `AllowedHeightVariationForBuilding` | `0xB38` | `Real` |
| `MinLowEnergyProductionSpeed` | `0xB3C` | `Real` |
| `MaxLowEnergyProductionSpeed` | `0xB40` | `Real` |
| `LowEnergyPenaltyModifier` | `0xB44` | `Real` |
| `MultipleFactory` | `0xB48` | `Real` |
| `RefundPercent` | `0xB4C` | `PercentToReal` |
| `CommandCenterHealRange` | `0xB54` | `Real` |
| `CommandCenterHealAmount` | `0xB58` | `Real` |
| `MaxLineBuildObjects` | `0xB5C` | `Int` |
| `MaxTunnelCapacity` | `0xB60` | `Int` |
| `MaxParticleCount` | `0xB8C` | `Int` |
| `MaxFieldParticleCount` | `0xB90` | `Int` |
| `HorizontalScrollSpeedFactor` | `0xB64` | `Real` |
| `VerticalScrollSpeedFactor` | `0xB68` | `Real` |
| `ScreenEdgeScrollSpeedFactor` | `0xB6C` | `Real` |
| `ScreenEdgeScrollRampTime` | `0xB70` | `0x00852D90` |
| `ScrollAmountCutoff` | `0xB74` | `Real` |
| `CameraAdjustSpeed` | `0xB78` | `Real` |
| `EnforceMaxCameraHeight` | `0xB7C` | `Bool` |
| `KeyboardScrollSpeedFactor` | `0xBBC` | `Real` |
| `KeyboardDefaultScrollSpeedFactor` | `0xBC0` | `Real` |
| `MovementPenaltyDamageState` | `0xBD8` | `IndexList` |
| `HealthBonus_Veteran` | `0xB9C` | `PercentToReal` |
| `HealthBonus_Elite` | `0xBA0` | `PercentToReal` |
| `HealthBonus_Heroic` | `0xBA4` | `PercentToReal` |
| `HumanSoloPlayerHealthBonus_Easy` | `0xA2C` | `PercentToReal` |
| `HumanSoloPlayerHealthBonus_Normal` | `0xA30` | `PercentToReal` |
| `HumanSoloPlayerHealthBonus_Hard` | `0xA34` | `PercentToReal` |
| `AttributeModifierArmorMaxBonus` | `0xBAC` | `PercentToReal` |
| `AISoloPlayerHealthBonus_Easy` | `0xA38` | `PercentToReal` |
| `AISoloPlayerHealthBonus_Normal` | `0xA3C` | `PercentToReal` |
| `AISoloPlayerHealthBonus_Hard` | `0xA40` | `PercentToReal` |
| `WeaponBonus` | `0xB94` | `WeaponBonusSetPtr` |
| `DefaultStructureRubbleHeight` | `0xBA8` | `Real` |
| `FixedSeed` | `0xAB0` | `Int` |
| `ShellMapName` | `0xBB0` | `AsciiString` |
| `ShellMapOn` | `0xBB4` | `Bool` |
| `ShellMapOffByCommandArgument` | `0xBB5` | `Bool` |
| `SkipMapUnroll` | `0x02A` | `Bool` |
| `PlayIntro` | `0xBB6` | `Bool` |
| `FirewallBehavior` | `0xB14` | `Int` |
| `FirewallPortOverride` | `0xB1C` | `Int` |
| `FirewallPortAllocationDelta` | `0xB20` | `Int` |
| `DamageRadiusMinimumForSplash` | `0xBDC` | `Real` |
| `GroupSelectMinSelectSize` | `0xBE0` | `Int` |
| `GroupSelectVolumeBase` | `0xBE4` | `Real` |
| `GroupSelectVolumeIncrement` | `0xBE8` | `Real` |
| `MaxUnitSelectSounds` | `0xBEC` | `Int` |
| `SelectionFlashSaturationFactor` | `0xBF0` | `Real` |
| `SelectionFlashHouseColor` | `0xBF4` | `Bool` |
| `CameraAudibleRadius` | `0xBF8` | `Real` |
| `GroupMoveClickToGatherAreaFactor` | `0xBFC` | `Real` |
| `ShakeSubtleIntensity` | `0xC10` | `Real` |
| `ShakeNormalIntensity` | `0xC14` | `Real` |
| `ShakeStrongIntensity` | `0xC18` | `Real` |
| `ShakeSevereIntensity` | `0xC1C` | `Real` |
| `ShakeCineExtremeIntensity` | `0xC20` | `Real` |
| `ShakeCineInsaneIntensity` | `0xC24` | `Real` |
| `MaxShakeIntensity` | `0xC28` | `Real` |
| `MaxShakeRange` | `0xC2C` | `Real` |
| `SellPercentage` | `0xC30` | `PercentToReal` |
| `BaseRegenHealthPercentPerSecond` | `0xC34` | `PercentToReal` |
| `BaseRegenDelay` | `0xC38` | `DurationUnsignedInt` |
| `SpecialPowerViewObject` | `0xC40` | `AsciiString` |
| `StandardPublicBone` | `0xC44` | `AsciiStringVectorAppend` |
| `ShowMetrics` | `0xC50` | `Bool` |
| `DefaultStartingCash` | `0xC54` | `UnsignedInt` |
| `ShroudColor` | `0xC78` | `RGBColor` |
| `ClearAlpha` | `0xC84` | `UnsignedByte` |
| `FogAlpha` | `0xC85` | `UnsignedByte` |
| `ShroudAlpha` | `0xC86` | `UnsignedByte` |
| `TaintOn` | `0xCF5` | `Bool` |
| `TaintColor` | `0xC88` | `RGBColor` |
| `ElvenWoodColor` | `0xC94` | `RGBColor` |
| `TaintAlpha` | `0xCA0` | `UnsignedByte` |
| `HotKeyTextColor` | `0xC3C` | `ColorInt` |
| `PowerBarBase` | `0xC5C` | `Int` |
| `PowerBarIntervals` | `0xC60` | `Real` |
| `PowerBarYellowRange` | `0xC64` | `Int` |
| `UnlookPersistDuration` | `0xC6C` | `DurationUnsignedInt` |
| `NetworkFPSHistoryLength` | `0xCA4` | `Int` |
| `NetworkLatencyHistoryLength` | `0xCA8` | `Int` |
| `NetworkRunAheadMetricsTime` | `0xCAC` | `Int` |
| `NetworkCushionHistoryLength` | `0xCB0` | `Int` |
| `NetworkRunAheadSlack` | `0xCB4` | `Int` |
| `NetworkKeepAliveDelay` | `0xCB8` | `Int` |
| `NetworkDisconnectTime` | `0xCBC` | `Int` |
| `NetworkPlayerTimeoutTime` | `0xCC0` | `Int` |
| `NetworkDisconnectScreenNotifyTime` | `0xCC4` | `Int` |
| `KeyboardCameraRotateSpeed` | `0xCC8` | `Real` |
| `PlayStats` | `0xCCC` | `Int` |
| `DefaultVoiceAttackChargeTimeout` | `0xCD0` | `DurationUnsignedInt` |
| `DefaultMaxDistanceForEngaged` | `0xCD4` | `Real` |
| `DefaultEngagedStateTimeout` | `0xCD8` | `DurationUnsignedInt` |
| `AnimationSharingCap` | `0xCDC` | `Int` |
| `AnimationSharingFrameTolerance` | `0xCE0` | `Real` |
| `AnimationSharingSpeedTolerance` | `0xCE4` | `Real` |
| `AnimationSharingWorryThreshold` | `0xCE8` | `Real` |
| `AnimationSharingDrasticThreshold` | `0xCEC` | `Real` |
| `ParticleCursorAnim2DTemplateName` | `0xDD0` | `AsciiString` |
| `ParticleCursorBurstCount` | `0xDD4` | `UnsignedInt` |
| `ParticleCursorBurstFactor` | `0xDD8` | `GameClientRandomVariable` |
| `ParticleCursorStopBurstFactor` | `0xDE4` | `Real` |
| `ParticleCursorBurstFrequency` | `0xDE8` | `UnsignedInt` |
| `ParticleCursorParticleLife` | `0xDEC` | `GameClientRandomVariable` |
| `ParticleCursorSystemLife` | `0xDF8` | `GameClientRandomVariable` |
| `ParticleCursorDriftVelX` | `0xE04` | `GameClientRandomVariable` |
| `ParticleCursorDriftVelY` | `0xE10` | `GameClientRandomVariable` |
| `ParticleCursorVelocityDrag` | `0xE1C` | `GameClientRandomVariable` |
| `ParticleCursorParticleSize` | `0xE28` | `GameClientRandomVariable` |
| `ParticleCursorPerFrameSize` | `0xE34` | `Bool` |
| `ParticleCursorAlpha` | `0xE38` | `Int` |
| `ParticleCursorOffset` | `0xE3C` | `ICoord2D` |
| `ProgressMovieOffset` | `0xE44` | `ICoord2D` |
| `ProgressMovieSize` | `0xE4C` | `ICoord2D` |
| `UseHelpTextSystem` | `0xE54` | `Bool` |
| `GuiTextureFiltering` | `0xE55` | `Bool` |
| `CameraTerrainSampleRadiusForHeight` | `0xE5C` | `Real` |
| `EnableHouseColor` | `0xE60` | `Bool` |
| `GoodCommandPoints` | `0xE70` | `Int` |
| `EvilCommandPoints` | `0xE74` | `Int` |
| `GoodCommandPointsBonus` | `0xE78` | `Int` |
| `EvilCommandPointsBonus` | `0xE7C` | `Int` |
| `GoodCommandPointsAI` | `0xE80` | `Int` |
| `EvilCommandPointsAI` | `0xE84` | `Int` |
| `GoodCommandPointsMP2` | `0xE88` | `Int` |
| `EvilCommandPointsMP2` | `0xE8C` | `Int` |
| `GoodCommandPointsMP3` | `0xE90` | `Int` |
| `EvilCommandPointsMP3` | `0xE94` | `Int` |
| `GoodCommandPointsMP4` | `0xE98` | `Int` |
| `EvilCommandPointsMP4` | `0xE9C` | `Int` |
| `GoodCommandPointsMP56` | `0xEA0` | `Int` |
| `EvilCommandPointsMP56` | `0xEA4` | `Int` |
| `GoodCommandPointsMP78` | `0xEA8` | `Int` |
| `EvilCommandPointsMP78` | `0xEAC` | `Int` |
| `InitialMaxRingLevel` | `0xEB0` | `Int` |
| `ResourceBonusMultiplier` | `0xEB4` | `Real` |
| `GoodCommandPointLimit` | `0xEB8` | `Int` |
| `EvilCommandPointLimit` | `0xEBC` | `Int` |
| `PowerLimit` | `0xEC0` | `Int` |
| `ResourceMultiplierLimit` | `0xEC4` | `Real` |
| `TreeFadeObjectFilter` | `0xEDC` | `0x0039F470` |
| `MultiPlayMoneyMult` | `0xEE0` | `0x00083510` |
| `MultiPlayUnitXPMult` | `0xEE0` | `0x00083690` |
| `MultiPlayBuildingXPMult` | `0xEE0` | `0x00083830` |
| `MultiPlayUnitSpeedMult` | `0xEE0` | `0x000839D0` |
| `MultiPlayBuildingSpeedMult` | `0xEE0` | `0x00083B70` |
| `ShrubBrightnessScale` | `0x1220` | `Real` |
| `TutorialMap` | `0x1200` | `AsciiString` |
| `TutorialLoadMovie` | `0x1204` | `AsciiString` |
| `TutorialObjective` | `0x1208` | `AsciiStringVectorAppend` |
| `BlockedByWallLeeway` | `0x11F4` | `Int` |
| `SecondsBeforeBaseCheckActive` | `0x11F8` | `Real` |
| `ObjectsThatScore` | `0x121C` | `0x0039F470` |
| `ScoreKeeper_UnitsBuiltMultiplier` | `0x1224` | `Int` |
| `ScoreKeeper_UnitsDestroyedMultiplier` | `0x1228` | `Int` |
| `ScoreKeeper_StructuresBuiltMultiplier` | `0x122C` | `Int` |
| `ScoreKeeper_StructuresDestroyedMultiplier` | `0x1230` | `Int` |
| `ScoreKeeper_HeroesVettedMultiplier` | `0x1234` | `Int` |
| `ScoreKeeper_UnitsVettedMultiplier` | `0x1238` | `Int` |
| `ScoreKeeper_ObjectivesCompletedMultiplier` | `0x123C` | `Int` |
| `ScoreKeeper_SuppliesCollectedMultiplier` | `0x1240` | `Int` |
| `ScoreKeeper_PowerPointsMultiplier` | `0x1244` | `Int` |
| `ScoreKeeper_RegionCommandPointsMultiplier` | `0x1248` | `Int` |
| `ScoreKeeper_RegionResourcesMultiplier` | `0x124C` | `Int` |
| `ScoreKeeper_RegionPowerPointsMultiplier` | `0x1250` | `Int` |
| `ScoreKeeper_TimeTakenMultiplier` | `0x1254` | `Int` |
| `ScoreKeeper_TimeTakenMaximumScore` | `0x1258` | `Int` |
| `ScoreKeeper_TimeTakenMinimumScore` | `0x125C` | `Int` |
| `ScoreKeeper_TotalVictoryRequiredScore` | `0x1260` | `Int` |
| `ScoreKeeper_NormalVictoryRequiredScore` | `0x1264` | `Int` |
| `ScoreKeeper_NormalVictoryRequiredObjectivesPercentage` | `0x1268` | `Int` |
| `TintUnitIfPathingForMoreThan` | `0x1270` | `Int` |
| `ClampedLOSHeightForCastleStructures` | `0x1274` | `Real` |

### `GlowEffect`

Parsed by `0x00421EE0` — `?parseGlowEffect@@YAXPAVINI@@@Z`

Field table `0x010F1698` — 10 fields

| Field | Offset | Type |
|---|---|---|
| `GlowEnabled` | `0x000` | `Bool` |
| `GlowDiameter` | `0x004` | `Int` |
| `GlowIntensity` | `0x008` | `Real` |
| `GlowTextureWidth` | `0x00C` | `Int` |
| `RadiusScale1` | `0x010` | `Real` |
| `RadiusScale2` | `0x018` | `Real` |
| `Amplitude1` | `0x014` | `Real` |
| `Amplitude2` | `0x01C` | `Real` |
| `TerrainGlow` | `0x020` | `Bool` |
| `MultipassGlowEnabled` | `0x021` | `Bool` |

### `HeaderTemplate`

Parsed by `0x0048CBD0` — `?parseHeaderTemplateDefinition@INI@@SAXPAV1@@Z`

Field table `0x010F9830` — 3 fields

| Field | Offset | Type |
|---|---|---|
| `Font` | `0x008` | `QuotedAsciiString` |
| `Point` | `0x00C` | `Int` |
| `Bold` | `0x010` | `Bool` |

### `HouseColor`

Parsed by `0x0039B7B0`

Field table `0x010EBD84` — 2 fields

| Field | Offset | Type |
|---|---|---|
| `BaseTexture` | `0x00C` | `AsciiString` |
| `HouseTexture` | `0x008` | `AsciiString` |

### `Language`

Parsed by `0x00438F70` — `?parseLanguageDefinition@INI@@SAXPAV1@@Z`

Field table `0x010F3AD8` — 31 fields

| Field | Offset | Type |
|---|---|---|
| `DecimalSeparator` | `0x008` | `AsciiString` |
| `ThousandSeparator` | `0x00C` | `AsciiString` |
| `TimeMinuteToSecondSeparator` | `0x010` | `AsciiString` |
| `UnicodeFontName` | `0x014` | `AsciiString` |
| `LocalFontFile` | `0x000` | `0x0043A3B0` |
| `MilitaryCaptionSpeed` | `0x024` | `Int` |
| `UseHardWordWrap` | `0x020` | `Bool` |
| `ResolutionFontAdjustment` | `0x130` | `Real` |
| `AudioLanguage` | `0x01C` | `AsciiString` |
| `CopyrightFont` | `0x028` | `0x00439150` |
| `MessageFont` | `0x034` | `0x00439150` |
| `MilitaryCaptionTitleFont` | `0x040` | `0x00439150` |
| `MilitaryCaptionFont` | `0x04C` | `0x00439150` |
| `AudioSubtitleFont` | `0x058` | `0x00439150` |
| `SuperweaponCountdownNormalFont` | `0x064` | `0x00439150` |
| `SuperweaponCountdownReadyFont` | `0x070` | `0x00439150` |
| `NamedTimerCountdownNormalFont` | `0x07C` | `0x00439150` |
| `NamedTimerCountdownReadyFont` | `0x088` | `0x00439150` |
| `DrawableCaptionFont` | `0x094` | `0x00439150` |
| `DefaultWindowFont` | `0x0A0` | `0x00439150` |
| `DefaultDisplayStringFont` | `0x0AC` | `0x00439150` |
| `TooltipFontName` | `0x0B8` | `0x00439150` |
| `NativeDebugDisplay` | `0x0C4` | `0x00439150` |
| `DrawGroupInfoFont` | `0x0D0` | `0x00439150` |
| `CreditsTitleFont` | `0x0DC` | `0x00439150` |
| `CreditsMinorTitleFont` | `0x0E8` | `0x00439150` |
| `CreditsNormalFont` | `0x0F4` | `0x00439150` |
| `HelpBoxNameFont` | `0x100` | `0x00439150` |
| `HelpBoxCostFont` | `0x10C` | `0x00439150` |
| `HelpBoxShortcutFont` | `0x118` | `0x00439150` |
| `HelpBoxDescriptionFont` | `0x124` | `0x00439150` |

### `LargeGroupAudioMap`

Parsed by `0x003D2490`

Field table `0x010EE310` — 11 fields

| Field | Offset | Type |
|---|---|---|
| `Size` | `0x00C` | `Real` |
| `Sound` | `0x018` | `0x003D0C40` |
| `StartThreshold` | `0x08C` | `Int` |
| `StopThreshold` | `0x090` | `Int` |
| `HandOffModeDuration` | `0x094` | `DurationUnsignedShort` |
| `MaximumAudioSpeed` | `0x010` | `VelocityReal` |
| `RequiredModelConditionFlags` | `0x024` | `0x00369AD0` |
| `ExcludedModelConditionFlags` | `0x04C` | `0x00369AD0` |
| `RequiredObjectStatusBits` | `0x074` | `0x00204E70` |
| `ExcludedObjectStatusBits` | `0x080` | `0x00204E70` |
| `IgnoreStealthedUnits` | `0x096` | `Bool` |

<details><summary><code>Sound</code> sub-block — 2 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Sound` | `0x00C` | `AsciiString` |
| `Key` | `0x000` | `0x003D4920` |

</details>

### `LargeGroupAudioUnusedKnownKeys`

Parsed by `0x003CF010`

Field table `0x010EE0C4` — 1 fields

| Field | Offset | Type |
|---|---|---|
| `Key` | `0x00C` | `0x003D4920` |

### `LightPointLevel`

Parsed by `0x0039CCF0`

Field table `0x010EBE44` — 2 fields

| Field | Offset | Type |
|---|---|---|
| `Name` | `0x010` | `AndTranslateLabel` |
| `SpecialAbilities` | `0x014` | `0x000BCE80` |

### `LivingWorldAnimObject`

Parsed by `0x0060A3A0`

Field table `0x01115B60` — 7 fields

| Field | Offset | Type |
|---|---|---|
| `Model` | `0x00C` | `AsciiString` |
| `Pos` | `0x01C` | `Coord3D` |
| `Frame` | `0x008` | `Real` |
| `HasAnim` | `0x010` | `Bool` |
| `Xfer` | `0x011` | `Bool` |
| `Xfer` | `0x011` | `Bool` |
| `OrientAngle` | `0x014` | `Real` |

### `LivingWorldArmyIcon`

Parsed by `0x0060B820`

Field table `0x01115DC8` — 3 fields

| Field | Offset | Type |
|---|---|---|
| `Object` | `0x000` | `0x0060B710` |
| `OnSelectedSound` | `0x004` | `0x000BABF0` |
| `OnMoveSound` | `0x008` | `0x000BABF0` |

<details><summary><code>Object</code> sub-block — 8 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Model` | `0x000` | `AsciiString` |
| `Pickbox` | `0x004` | `AsciiString` |
| `ZOffset` | `0x00C` | `Real` |
| `Scale` | `0x010` | `Real` |
| `Clickable` | `0x014` | `Bool` |
| `Hidden` | `0x015` | `Bool` |
| `CanFade` | `0x016` | `Bool` |
| `OrientAngle` | `0x018` | `Real` |

</details>

### `LivingWorldCampaign`

Parsed by `0x003AA860`

Field table `0x010EC7CC` — 2 fields

| Field | Offset | Type |
|---|---|---|
| `Act` | `0x000` | `0x003B2BB0` |
| `IsEvilCampaign` | `0x01C` | `Bool` |

<details><summary><code>Act</code> sub-block — 18 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `EnableRegion` | `0x000` | `0x003B7BA0` |
| `ForceBattle` | `0x000` | `0x003B7DC0` |
| `SpawnArmy` | `0x000` | `0x003B7F90` |
| `DespawnArmy` | `0x038` | `AsciiStringVectorAppend` |
| `CallActSubroutine` | `0x044` | `AsciiStringVectorAppend` |
| `JumpToAct` | `0x050` | `AsciiString` |
| `MoveArmy` | `0x000` | `0x003B8190` |
| `ToggleArmyControl` | `0x000` | `0x003B82D0` |
| `RegionReinforcements` | `0x000` | `0x003BABE0` |
| `MergePlayerArmy` | `0x000` | `0x003B8500` |
| `MoveCamera` | `0x000` | `0x003B7650` |
| `SplineCamera` | `0x000` | `0x003BA660` |
| `WorldText` | `0x000` | `0x003B8610` |
| `AudioEvent` | `0x000` | `0x003B7780` |
| `EndAct` | `0x0D8` | `Bool` |
| `UpdateAnimObject` | `0x000` | `0x003B8770` |
| `EyeTowerPoints` | `0x000` | `0x003BAE20` |
| `ModifyArmyEntry` | `0x000` | `0x003B88F0` |

</details>

### `LivingWorldMapInfo`

Parsed by `0x0060D6B0`

Field table `0x01116000` — 71 fields

| Field | Offset | Type |
|---|---|---|
| `MapObject` | `0x000` | `AsciiString` |
| `CloudBorderSubObject` | `0x11C` | `AsciiString` |
| `TextLayerSubObject` | `0x120` | `AsciiString` |
| `Center` | `0x004` | `Coord2D` |
| `Extent` | `0x00C` | `Coord2D` |
| `EmbersPartSys` | `0x020` | `AsciiString` |
| `CloudPos` | `0x014` | `Coord3D` |
| `Ambient` | `0x024` | `RGBColor` |
| `SunDir` | `0x030` | `Coord2D` |
| `SunRGB` | `0x038` | `RGBColor` |
| `Accent1Dir` | `0x044` | `Coord2D` |
| `Accent1RGB` | `0x04C` | `RGBColor` |
| `Accent2Dir` | `0x058` | `Coord2D` |
| `Accent2RGB` | `0x060` | `RGBColor` |
| `GondorBanner` | `0x06C` | `AsciiString` |
| `RohanBanner` | `0x070` | `AsciiString` |
| `MordorBanner` | `0x074` | `AsciiString` |
| `IsengardBanner` | `0x078` | `AsciiString` |
| `NeutralBanner` | `0x07C` | `AsciiString` |
| `GondorAnts` | `0x080` | `AsciiString` |
| `RohanAnts` | `0x084` | `AsciiString` |
| `MordorAnts` | `0x088` | `AsciiString` |
| `IsengardAnts` | `0x08C` | `AsciiString` |
| `NeutralAnts` | `0x090` | `AsciiString` |
| `BattleMarker` | `0x094` | `AsciiString` |
| `PalantirMarker` | `0x098` | `AsciiString` |
| `BattleMarkerCreatedSound` | `0x0E8` | `0x000BABF0` |
| `EnterMapSound` | `0x0EC` | `0x000BABF0` |
| `BannerScaleSpeed` | `0x09C` | `Real` |
| `BannerMaxScale` | `0x0A0` | `Real` |
| `BannerTiltAngle` | `0x0A4` | `Real` |
| `BannerHeight` | `0x0A8` | `Real` |
| `ArmyHeight` | `0x0AC` | `Real` |
| `BeaconHeight` | `0x0B0` | `Real` |
| `AnimRays` | `0x0B4` | `AsciiString` |
| `AnimRaysPartSys` | `0x0B8` | `AsciiString` |
| `AnimRaysPartSysOffset` | `0x0BC` | `Coord3D` |
| `AnimRaysColor` | `0x0C8` | `RGBColor` |
| `AnimRaysColorScale` | `0x0D4` | `Real` |
| `AnimRaysEffectShells` | `0x0D8` | `Int` |
| `AnimRaysEffectDiameter` | `0x0DC` | `Int` |
| `AnimRaysEffectLifetime` | `0x0E0` | `Int` |
| `AnimRaysCreateSound` | `0x0E4` | `0x000BABF0` |
| `AnimCloud` | `0x0F0` | `AsciiString` |
| `AnimCloudPartSys` | `0x0F4` | `AsciiString` |
| `NumAnimClouds` | `0x0F8` | `Int` |
| `AnimCloudLifetime` | `0x114` | `Int` |
| `AnimCloudRegionMin` | `0x0FC` | `Coord3D` |
| `AnimCloudRegionMax` | `0x108` | `Coord3D` |
| `MordorCloud` | `0x118` | `AsciiString` |
| `CloudGrowthPos` | `0x124` | `Coord3D` |
| `CloudGrowthRate` | `0x130` | `Int` |
| `CloudInitialSize` | `0x134` | `Real` |
| `CloudGrowthSize` | `0x13C` | `Real` |
| `CloudInitialOpacity` | `0x138` | `Real` |
| `CameraBoundX` | `0x144` | `Real` |
| `CameraBoundY` | `0x148` | `Real` |
| `ShadowColor` | `0x14C` | `RGBColor` |
| `EnableMapShadows` | `0x158` | `Bool` |
| `ArmySelectedIconObject` | `0x15C` | `AsciiString` |
| `ArmyHilightedIconObject` | `0x160` | `AsciiString` |
| `ArmySelectedFadeInStart` | `0x164` | `Int` |
| `ArmySelectedFadeInEnd` | `0x168` | `Int` |
| `ArmySelectedFadeOutStart` | `0x16C` | `Int` |
| `ArmySelectedFadeOutEnd` | `0x170` | `Int` |
| `ArmyHilightedFadeInTime` | `0x174` | `Int` |
| `ArmyHilightedFadeOutTime` | `0x178` | `Int` |
| `ArmySoldierLarge` | `0x17C` | `AsciiString` |
| `ArmySoldierMedium` | `0x180` | `AsciiString` |
| `ArmySoldierSmall` | `0x184` | `AsciiString` |
| `EyeTower` | `0x000` | `0x0060CD80` |

<details><summary><code>EyeTower</code> sub-block — 4 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `PupilAnimObject` | `0x004` | `AsciiString` |
| `PupilBeamAnimObject` | `0x008` | `AsciiString` |
| `EyeDecalAnimObject` | `0x00C` | `AsciiString` |
| `EyeDecalBeamAnimObject` | `0x010` | `AsciiString` |

</details>

### `LivingWorldObject`

Parsed by `0x00614F50`

Field table `0x01116D18`, returned by the getter at `0x006185F0`:

| Field | Offset | Parser RVA |
|---|---|---|
| `ObjectType` | `0x00C` | `0x00851050` |
| `DefaultFlashValue` | `0x010` | `0x00852B20` |
| `FlashVariation` | `0x014` | `0x00852B20` |

See [boundary and identity evidence](living_world_parser_boundary.md).

### `LivingWorldPlayerArmy`

Parsed by `0x00366410`

Field table `0x010E90A8` — 8 fields

| Field | Offset | Type |
|---|---|---|
| `Name` | `0x00C` | `AsciiString` |
| `DisplayNameTag` | `0x048` | `AsciiString` |
| `Color` | `0x018` | `RGBColor` |
| `NightColor` | `0x01C` | `RGBColor` |
| `ArmyEntry` | `0x000` | `0x00365B40` |
| `SurvivalThreshhold` | `0x044` | `Int` |
| `MinCommandPoints` | `0x050` | `Int` |
| `ReplenishArmyName` | `0x054` | `AsciiString` |

<details><summary><code>ArmyEntry</code> sub-block — 3 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `ThingTemplate` | `0x004` | `AsciiString` |
| `Quantity` | `0x034` | `Int` |
| `Default` | `0x038` | `Bool` |

</details>

### `LivingWorldRegionCampaign`

Parsed by `0x003C9B60`

Field table `0x010EDC48` — 21 fields

| Field | Offset | Type |
|---|---|---|
| `Region` | `0x000` | `0x003C9980` |
| `RegionObject` | `0x000` | `AsciiString` |
| `ZOffset` | `0x008` | `Real` |
| `RegionBonusArmy` | `0x00C` | `AsciiString` |
| `RegionBonusResource` | `0x010` | `AsciiString` |
| `RegionBonusLegendary` | `0x014` | `AsciiString` |
| `SmallArmyCommandPoints` | `0x018` | `Int` |
| `MediumArmyCommandPoints` | `0x01C` | `Int` |
| `ArmyPlacementPos` | `0x020` | `0x0061ACA0` |
| `ConqueredEffectEvenglow` | `0x000` | `0x003BB730` |
| `ConqueredEffectFlareup` | `0x000` | `0x003BB730` |
| `MouseoverEffectFlareupOwned` | `0x000` | `0x003BB730` |
| `MouseoverEffectFlareupContested` | `0x000` | `0x003BB730` |
| `MouseoutEffectFlareupOwned` | `0x000` | `0x003BB730` |
| `MouseoutEffectFlareupContested` | `0x000` | `0x003BB730` |
| `EnemyBordersEffect` | `0x000` | `0x003BB730` |
| `FriendlyBordersEffect` | `0x000` | `0x003BB730` |
| `HilightBordersEffect` | `0x000` | `0x003BB730` |
| `RegionPopupDefaultColor` | `0x04C` | `ColorInt` |
| `RegionPopupOverColor` | `0x050` | `ColorInt` |
| `RegionConqueredSound` | `0x054` | `AsciiString` |

<details><summary><code>ConqueredEffectEvenglow</code> sub-block — 3 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Opacity` | `0x024` | `Real` |
| `ControlPoint` | `0x000` | `0x00064680` |
| `Geometry` | `0x000` | `0x003BB680` |

</details>

### `LivingWorldSound`

Parsed by `0x0061C410`

Field table `0x011172B0` — 5 fields

| Field | Offset | Type |
|---|---|---|
| `Position` | `0x008` | `Coord3D` |
| `Sound` | `0x014` | `0x000BABF0` |
| `Flags` | `0x018` | `0x0061CD10` |
| `ZoomRegionLow` | `0x01C` | `Coord2D` |
| `ZoomRegionHigh` | `0x024` | `Coord2D` |

### `LoadSubsystem`

Parsed by `0x009A16A0` — `?parseSubsystemLegendDefinition@@YAXPAVINI@@@Z`

_No field table: this block parses its body directly._

### `Locomotor`

Parsed by `0x001BAEC0` — `?parseLocomotorTemplateDefinition@LocomotorStore@@SAXPAVINI@@@Z`

Field table `0x0109D860` — 82 fields

| Field | Offset | Type |
|---|---|---|
| `Surfaces` | `0x010` | `BitString32` |
| `Speed` | `0x01C` | `VelocityReal` |
| `LookAheadMult` | `0x014` | `Real` |
| `NonDirtyTransform` | `0x018` | `Bool` |
| `SpeedDamaged` | `0x020` | `PercentToReal` |
| `TurnTime` | `0x028` | `DurationUnsignedInt` |
| `TurnTimeDamaged` | `0x02C` | `DurationUnsignedInt` |
| `SlowTurnRadius` | `0x030` | `Real` |
| `FastTurnRadius` | `0x034` | `Real` |
| `TurnThreshold` | `0x038` | `AngleReal` |
| `TurnThresholdHS` | `0x03C` | `AngleReal` |
| `Acceleration` | `0x040` | `DurationUnsignedInt` |
| `Lift` | `0x044` | `PercentToReal` |
| `LiftDamaged` | `0x048` | `PercentToReal` |
| `Braking` | `0x04C` | `DurationUnsignedInt` |
| `MinSpeed` | `0x024` | `PercentToReal` |
| `MinTurnSpeed` | `0x050` | `PercentToReal` |
| `PreferredHeight` | `0x054` | `Real` |
| `PreferredHeightDamping` | `0x05C` | `Real` |
| `PreferredAttackHeight` | `0x058` | `Real` |
| `CirclingRadius` | `0x060` | `Real` |
| `SpeedLimitZ` | `0x064` | `VelocityReal` |
| `MaxThrustAngle` | `0x068` | `AngleReal` |
| `ZAxisBehavior` | `0x06C` | `IndexList` |
| `Appearance` | `0x070` | `IndexList` |
| `FormationPriority` | `0x074` | `IndexList` |
| `AccDecTrigger` | `0x078` | `Real` |
| `WalkDistance` | `0x07C` | `Real` |
| `MaxOverlappedHeight` | `0x0A0` | `Real` |
| `MaxTurnWithoutReform` | `0x080` | `AngleReal` |
| `AccelerationPitchLimit` | `0x084` | `AngleReal` |
| `BounceAmount` | `0x088` | `AngularVelocityReal` |
| `PitchStiffness` | `0x08C` | `Real` |
| `RollStiffness` | `0x090` | `Real` |
| `PitchDamping` | `0x094` | `Real` |
| `RollDamping` | `0x098` | `Real` |
| `PitchInDirectionOfZVelFactor` | `0x09C` | `Real` |
| `ForwardVelocityPitchFactor` | `0x0A4` | `Real` |
| `LateralVelocityRollFactor` | `0x0A8` | `Real` |
| `ForwardAccelerationPitchFactor` | `0x0AC` | `Real` |
| `LateralAccelerationRollFactor` | `0x0B0` | `Real` |
| `UniformAxialDamping` | `0x0B4` | `Real` |
| `TurnPivotOffset` | `0x0B8` | `Real` |
| `Apply2DFrictionWhenAirborne` | `0x0CE` | `Bool` |
| `DownhillOnly` | `0x0CF` | `Bool` |
| `AllowAirborneMotiveForce` | `0x0CD` | `Bool` |
| `LocomotorWorksWhenDead` | `0x0CC` | `Bool` |
| `AirborneTargetingHeight` | `0x0BC` | `Int` |
| `StickToGround` | `0x0D0` | `Bool` |
| `CanMoveBackwards` | `0x0D4` | `0x001B41E0` |
| `HasSuspension` | `0x0D8` | `Bool` |
| `FrontWheelTurnAngle` | `0x0E4` | `AngleReal` |
| `MaximumWheelExtension` | `0x0DC` | `Real` |
| `MaximumWheelCompression` | `0x0E0` | `Real` |
| `CloseEnoughDist` | `0x0C0` | `Real` |
| `CloseEnoughDist3D` | `0x0C4` | `Bool` |
| `SlideIntoPlaceTime` | `0x0C8` | `DurationReal` |
| `CrewPowered` | `0x0E8` | `Bool` |
| `UseTerrainSmoothing` | `0x0E9` | `Bool` |
| `WanderWidthFactor` | `0x0EC` | `Real` |
| `WanderLengthFactor` | `0x0F0` | `Real` |
| `WanderAboutPointRadius` | `0x0F4` | `Real` |
| `ChargeSpeed` | `0x0F8` | `PercentToReal` |
| `ChargeAvailable` | `0x0FC` | `Bool` |
| `EnableHighSpeedTurnModelconditions` | `0x0FD` | `Bool` |
| `WaitForFormation` | `0x0FE` | `Bool` |
| `RudderCorrectionDegree` | `0x100` | `Real` |
| `RudderCorrectionRate` | `0x104` | `Real` |
| `ElevatorCorrectionDegree` | `0x108` | `Real` |
| `ElevatorCorrectionRate` | `0x10C` | `Real` |
| `AeleronCorrectionDegree` | `0x110` | `Real` |
| `AeleronCorrectionRate` | `0x10C` | `Real` |
| `SwoopStandoffRadius` | `0x118` | `Real` |
| `SwoopStandoffHeight` | `0x11C` | `Real` |
| `SwoopTerminalVelocity` | `0x120` | `Real` |
| `SwoopAccelerationRate` | `0x124` | `Real` |
| `SwoopSpeedTuningFactor` | `0x128` | `Real` |
| `BackingUpSpeed` | `0x12C` | `PercentToReal` |
| `BackingUpStopWhenTurning` | `0x130` | `Bool` |
| `BackingUpDistanceMin` | `0x134` | `Real` |
| `BackingUpDistanceMax` | `0x138` | `Real` |
| `BackingUpAngle` | `0x13C` | `Real` |

### `LODPreset`

Parsed by `0x0007D2D0` — `?parseLODPreset@INI@@SAXPAV1@@Z`

_No field table: this block parses its body directly._

### `MappedImage`

Parsed by `0x000C2480`

Field table `0x0110FF08` — 5 fields

| Field | Offset | Type |
|---|---|---|
| `Texture` | `0x008` | `AsciiString` |
| `TextureWidth` | `0x00C` | `Int` |
| `TextureHeight` | `0x010` | `Int` |
| `Coords` | `0x014` | `ImageCoords` |
| `Status` | `0x030` | `ImageStatus` |

### `MiscAudio`

Parsed by `0x000C25B0` — `?parseMiscAudio@INI@@SAXPAV1@@Z`

Field table `0x01083310` — 32 fields

| Field | Offset | Type |
|---|---|---|
| `RadarNotifyHarvesterUnderAttackSound` | `0x000` | `AudioEventRTS` |
| `RadarNotifyStructureUnderAttackSound` | `0x070` | `AudioEventRTS` |
| `RadarNotifyInfiltrationSound` | `0x0E0` | `AudioEventRTS` |
| `RadarNotifyOnlineSound` | `0x150` | `AudioEventRTS` |
| `RadarNotifyOfflineSound` | `0x1C0` | `AudioEventRTS` |
| `DefectorTimerTickSound` | `0x230` | `AudioEventRTS` |
| `DefectorTimerDingSound` | `0x2A0` | `AudioEventRTS` |
| `AllCheerSound` | `0x310` | `AudioEventRTS` |
| `BattleCrySound` | `0x380` | `AudioEventRTS` |
| `NoCanDoSound` | `0x3F0` | `AudioEventRTS` |
| `StealthDiscoveredSound` | `0x460` | `AudioEventRTS` |
| `StealthNeutralizedSound` | `0x4D0` | `AudioEventRTS` |
| `MoneyDepositSound` | `0x540` | `AudioEventRTS` |
| `MoneyWithdrawSound` | `0x5B0` | `AudioEventRTS` |
| `BuildingDisabled` | `0x620` | `AudioEventRTS` |
| `BuildingReenabled` | `0x690` | `AudioEventRTS` |
| `VehicleDisabled` | `0x700` | `AudioEventRTS` |
| `VehicleReenabled` | `0x770` | `AudioEventRTS` |
| `SplatterVehiclePilotsBrain` | `0x7E0` | `AudioEventRTS` |
| `CrateHeal` | `0x850` | `AudioEventRTS` |
| `CrateShroud` | `0x8C0` | `AudioEventRTS` |
| `CrateSalvage` | `0x930` | `AudioEventRTS` |
| `CrateFreeUnit` | `0x9A0` | `AudioEventRTS` |
| `CrateMoney` | `0xA10` | `AudioEventRTS` |
| `UnitPromoted` | `0xA80` | `AudioEventRTS` |
| `RepairSparks` | `0xAF0` | `AudioEventRTS` |
| `EnterCloseCombat` | `0xB60` | `AudioEventRTS` |
| `ExitCloseCombat` | `0xBD0` | `AudioEventRTS` |
| `IncomingChatNotification` | `0xC40` | `AudioEventRTS` |
| `EnabledHotKeyPressed` | `0xCB0` | `AudioEventRTS` |
| `DisabledHotKeyPressed` | `0xD20` | `AudioEventRTS` |
| `LowLODShellMusic` | `0xD90` | `AudioEventRTS` |

### `MiscEvaData`

Parsed by `0x00422BD0` — `?parseMiscEvaData@INI@@SAXPAV1@@Z`

Field table `0x010F1E48` — 3 fields

| Field | Offset | Type |
|---|---|---|
| `EnemySightedMaxVoicePositionScanRange` | `0x000` | `Real` |
| `EnemyCampDestroyedDamageTimeoutMS` | `0x004` | `DurationUnsignedInt` |
| `FriendlyCampDestroyedDamageTimeoutMS` | `0x008` | `DurationUnsignedInt` |

### `ModifierList`

Parsed by `0x0036B7C0`

_No field table: this block parses its body directly._

### `Mouse`

Parsed by `0x005A4690` — `?parseMouseDefinition@INI@@SAXPAV1@@Z`

Field table `0x0110D140` — 21 fields

| Field | Offset | Type |
|---|---|---|
| `TooltipFontName` | `0x1070` | `AsciiString` |
| `TooltipFontSize` | `0x1074` | `Int` |
| `TooltipFontIsBold` | `0x1078` | `Bool` |
| `TooltipAnimateBackground` | `0x1079` | `Bool` |
| `TooltipFillTime` | `0x107C` | `Int` |
| `TooltipDelayTime` | `0x1080` | `Int` |
| `TooltipTextColor` | `0x1090` | `RGBAColorInt` |
| `TooltipHighlightColor` | `0x10A0` | `RGBAColorInt` |
| `TooltipShadowColor` | `0x10B0` | `RGBAColorInt` |
| `TooltipBackgroundColor` | `0x10C0` | `RGBAColorInt` |
| `TooltipBorderColor` | `0x10D0` | `RGBAColorInt` |
| `TooltipWidth` | `0x1084` | `PercentToReal` |
| `CursorMode` | `0x10E0` | `Int` |
| `UseTooltipAltTextColor` | `0x10E4` | `Bool` |
| `UseTooltipAltBackColor` | `0x10E5` | `Bool` |
| `AdjustTooltipAltColor` | `0x10E6` | `Bool` |
| `OrthoCamera` | `0x10E7` | `Bool` |
| `OrthoZoom` | `0x10E8` | `Real` |
| `DragTolerance` | `0x10EC` | `UnsignedInt` |
| `DragTolerance3D` | `0x10F0` | `UnsignedInt` |
| `DragToleranceMS` | `0x10F4` | `UnsignedInt` |

### `MouseCursor`

Parsed by `0x005A5FA0` — `?parseMouseCursorDefinition@INI@@SAXPAV1@@Z`

Field table `0x0110D070` — 34 fields

| Field | Offset | Type |
|---|---|---|
| `CursorText` | `0x004` | `AsciiString` |
| `CursorTextColor` | `0x008` | `RGBAColorInt` |
| `CursorTextDropColor` | `0x018` | `RGBAColorInt` |
| `W3DModel` | `0x030` | `AsciiString` |
| `W3DAnim` | `0x034` | `AsciiString` |
| `W3DScale` | `0x038` | `Real` |
| `Loop` | `0x03C` | `Bool` |
| `Image` | `0x02C` | `AsciiString` |
| `Texture` | `0x028` | `AsciiString` |
| `HotSpot` | `0x040` | `ICoord2D` |
| `Frames` | `0x048` | `Int` |
| `FPS` | `0x04C` | `Real` |
| `Directions` | `0x050` | `Int` |
| `TooltipFontName` | `0x1070` | `AsciiString` |
| `TooltipFontSize` | `0x1074` | `Int` |
| `TooltipFontIsBold` | `0x1078` | `Bool` |
| `TooltipAnimateBackground` | `0x1079` | `Bool` |
| `TooltipFillTime` | `0x107C` | `Int` |
| `TooltipDelayTime` | `0x1080` | `Int` |
| `TooltipTextColor` | `0x1090` | `RGBAColorInt` |
| `TooltipHighlightColor` | `0x10A0` | `RGBAColorInt` |
| `TooltipShadowColor` | `0x10B0` | `RGBAColorInt` |
| `TooltipBackgroundColor` | `0x10C0` | `RGBAColorInt` |
| `TooltipBorderColor` | `0x10D0` | `RGBAColorInt` |
| `TooltipWidth` | `0x1084` | `PercentToReal` |
| `CursorMode` | `0x10E0` | `Int` |
| `UseTooltipAltTextColor` | `0x10E4` | `Bool` |
| `UseTooltipAltBackColor` | `0x10E5` | `Bool` |
| `AdjustTooltipAltColor` | `0x10E6` | `Bool` |
| `OrthoCamera` | `0x10E7` | `Bool` |
| `OrthoZoom` | `0x10E8` | `Real` |
| `DragTolerance` | `0x10EC` | `UnsignedInt` |
| `DragTolerance3D` | `0x10F0` | `UnsignedInt` |
| `DragToleranceMS` | `0x10F4` | `UnsignedInt` |

### `MultiplayerColor`

Parsed by `0x000C2690` — `?parseMultiplayerColorDefinition@INI@@SAXPAV1@@Z`

Field table `0x0107F6D8` — 3 fields

| Field | Offset | Type |
|---|---|---|
| `TooltipName` | `0x000` | `AsciiString` |
| `RGBColor` | `0x004` | `RGBColor` |
| `RGBNightColor` | `0x014` | `RGBColor` |

### `MultiplayerSettings`

Parsed by `0x000C2600` — `?parseMultiplayerSettingsDefinition@INI@@SAXPAV1@@Z`

Field table `0x0107F718` — 11 fields

| Field | Offset | Type |
|---|---|---|
| `InitialCreditsVeryLow` | `0x01C` | `Int` |
| `InitialCreditsLow` | `0x020` | `Int` |
| `InitialCreditsMedium` | `0x024` | `Int` |
| `InitialCreditsHigh` | `0x028` | `Int` |
| `InitialCreditsVeryHigh` | `0x02C` | `Int` |
| `StartCountdownTimer` | `0x010` | `Int` |
| `MaxBeaconsPerPlayer` | `0x014` | `Int` |
| `UseShroud` | `0x018` | `Bool` |
| `ShowRandomPlayerTemplate` | `0x019` | `Bool` |
| `ShowRandomStartPos` | `0x01A` | `Bool` |
| `ShowRandomColor` | `0x01B` | `Bool` |

### `MusicTrack`

Parsed by `0x000B1B70`

Field table `0x010813F8` — 21 fields

| Field | Offset | Type |
|---|---|---|
| `Filename` | `0x00C` | `AsciiString` |
| `Volume` | `0x010` | `PercentToReal` |
| `VolumeShift` | `0x014` | `PercentToReal` |
| `MinVolume` | `0x018` | `PercentToReal` |
| `PitchShift` | `0x000` | `0x000AFFF0` |
| `PlayPercent` | `0x024` | `PercentToReal` |
| `Delay` | `0x000` | `0x000AFF40` |
| `Limit` | `0x030` | `Int` |
| `Priority` | `0x034` | `IndexList` |
| `Type` | `0x038` | `BitString32` |
| `Control` | `0x03C` | `BitString32` |
| `Sounds` | `0x040` | `0x000B1DF0` |
| `Attack` | `0x050` | `0x000B1DF0` |
| `Decay` | `0x060` | `0x000B1DF0` |
| `MinRange` | `0x074` | `Real` |
| `MaxRange` | `0x078` | `Real` |
| `LowPassCutoff` | `0x070` | `PercentToReal` |
| `ReverbEffectLevel` | `0x07C` | `PercentToReal` |
| `DryLevel` | `0x080` | `PercentToReal` |
| `SubmixSlider` | `0x088` | `IndexList` |
| `VolumeSliderMultiplier` | `0x08C` | `0x000B0990` |

### `NewEvaEvent`

Parsed by `0x00426C60`

Field table `0x010F1B68` — 5 fields

| Field | Offset | Type |
|---|---|---|
| `Priority` | `0x00C` | `UnsignedInt` |
| `TimeBetweenEventsMS` | `0x000` | `UnsignedInt` |
| `ExpirationTimeMS` | `0x004` | `UnsignedInt` |
| `QuietTimeMS` | `0x008` | `UnsignedInt` |
| `SideSound` | `0x010` | `0x004255F0` |

<details><summary><code>SideSound</code> sub-block — 2 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Side` | `0x000` | `AsciiString` |
| `Sound` | `0x004` | `0x000BABF0` |

</details>

### `Object`

Parsed by `0x000C27E0`

_No field table: this block parses its body directly._

### `ObjectCreationList`

Parsed by `0x001DB050` — `?parseObjectCreationListDefinition@ObjectCreationListStore@@SAXPAVINI@@@Z`

Field table `0x0109EEF8` — 5 fields

| Field | Offset | Type |
|---|---|---|
| `CreateObject` | `0x000` | `0x001DA620` |
| `CreateDebris` | `0x000` | `Debris` |
| `ApplyRandomForce` | `0x000` | `parse` |
| `FireWeapon` | `0x000` | `parse` |
| `Attack` | `0x000` | `parse` |

<details><summary><code>CreateObject</code> sub-block — 30 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `PutInContainer` | `0x010` | `AsciiString` |
| `ParticleSystem` | `0x024` | `AsciiString` |
| `Count` | `0x028` | `Int` |
| `OrientInForceDirection` | `0x116` | `Bool` |
| `ExtraBounciness` | `0x02C` | `Real` |
| `ExtraFriction` | `0x030` | `0x001D5F40` |
| `Offset` | `0x034` | `Coord3D` |
| `Disposition` | `0x040` | `BitString32` |
| `DispositionIntensity` | `0x044` | `VelocityReal` |
| `DispositionAngle` | `0x048` | `AngleReal` |
| `VelocityScale` | `0x04C` | `Real` |
| `MinForceMagnitude` | `0x050` | `Real` |
| `MaxForceMagnitude` | `0x054` | `Real` |
| `MinForcePitch` | `0x058` | `AngleReal` |
| `MaxForcePitch` | `0x05C` | `AngleReal` |
| `MinLifetime` | `0x060` | `DurationUnsignedInt` |
| `MaxLifetime` | `0x064` | `DurationUnsignedInt` |
| `SpreadFormation` | `0x117` | `Bool` |
| `MinDistanceAFormation` | `0x084` | `Real` |
| `MinDistanceBFormation` | `0x088` | `Real` |
| `MaxDistanceFormation` | `0x08C` | `Real` |
| `FadeIn` | `0x118` | `Bool` |
| `FadeOut` | `0x119` | `Bool` |
| `FadeTime` | `0x07C` | `DurationUnsignedInt` |
| `FadeSound` | `0x080` | `AsciiString` |
| `PreserveLayer` | `0x10A` | `Bool` |
| `IgnoreAllObjects` | `0x10B` | `Bool` |
| `IgnoreEnemyUnits` | `0x10D` | `Bool` |
| `IgnoreAllyUnits` | `0x10C` | `Bool` |
| `StartingConditions` | `0x120` | `0x00369AD0` |

</details>

<details><summary><code>CreateObject</code> sub-block — 15 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `ContainInsideSourceObject` | `0x109` | `Bool` |
| `ObjectNames` | `0x004` | `AsciiStringVector` |
| `ObjectCount` | `0x090` | `Int` |
| `InheritsVeterancy` | `0x11A` | `Bool` |
| `VeterancyLevel` | `0x11C` | `Int` |
| `SkipIfSignificantlyAirborne` | `0x11B` | `Bool` |
| `InvulnerableTime` | `0x070` | `DurationUnsignedInt` |
| `StartingBusyTime` | `0x110` | `DurationUnsignedInt` |
| `MinHealth` | `0x074` | `PercentToReal` |
| `MaxHealth` | `0x078` | `PercentToReal` |
| `RequiresLivePlayer` | `0x104` | `Bool` |
| `IgnoreCommandPointLimit` | `0x105` | `Bool` |
| `InheritAttributesFromSource` | `0x106` | `Bool` |
| `UseJustBuiltFlag` | `0x108` | `Bool` |
| `InheritScriptingName` | `0x107` | `Bool` |

</details>

<details><summary><code>CreateDebris</code> sub-block — 7 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `ModelNames` | `0x004` | `AsciiStringVector` |
| `AnimationSet` | `0x014` | `0x001DABF0` |
| `FXFinal` | `0x020` | `FXList` |
| `OkToChangeModelColor` | `0x115` | `Bool` |
| `MinLODRequired` | `0x06C` | `0x0007BCF0` |
| `Shadow` | `0x068` | `BitString32` |
| `BounceSound` | `0x094` | `AudioEventRTS` |

</details>

<details><summary><code>ApplyRandomForce</code> sub-block — 4 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `MinForceMagnitude` | `0x004` | `Real` |
| `MaxForceMagnitude` | `0x008` | `Real` |
| `MinForcePitch` | `0x00C` | `AngleReal` |
| `MaxForcePitch` | `0x010` | `AngleReal` |

</details>

<details><summary><code>FireWeapon</code> sub-block — 1 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Weapon` | `0x004` | `WeaponTemplate` |

</details>

<details><summary><code>Attack</code> sub-block — 4 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `NumberOfShots` | `0x038` | `Int` |
| `WeaponSlot` | `0x03C` | `LookupList` |
| `DeliveryDecal` | `0x004` | `RadiusDecalTemplate` |
| `DeliveryDecalRadius` | `0x034` | `Real` |

</details>

### `ObjectReskin`

Parsed by `0x000C2870`

_No field table: this block parses its body directly._

### `OnlineChatColors`

Parsed by `0x006250A0` — `?parseOnlineChatColorDefinition@INI@@SAXPAV1@@Z`

Field table `0x01117700` — 29 fields

| Field | Offset | Type |
|---|---|---|
| `Default` | `0x000` | `ColorInt` |
| `CurrentRoom` | `0x004` | `ColorInt` |
| `ChatRoom` | `0x008` | `ColorInt` |
| `Game` | `0x00C` | `ColorInt` |
| `GameFull` | `0x010` | `ColorInt` |
| `GameCRCMismatch` | `0x014` | `ColorInt` |
| `PlayerNormal` | `0x018` | `ColorInt` |
| `PlayerOwner` | `0x01C` | `ColorInt` |
| `PlayerBuddy` | `0x020` | `ColorInt` |
| `OfflinePlayerBuddy` | `0x024` | `ColorInt` |
| `PlayerSelf` | `0x028` | `ColorInt` |
| `PlayerIgnored` | `0x02C` | `ColorInt` |
| `OfflinePlayerIgnored` | `0x030` | `ColorInt` |
| `ChatNormal` | `0x034` | `ColorInt` |
| `ChatEmote` | `0x038` | `ColorInt` |
| `ChatOwner` | `0x03C` | `ColorInt` |
| `ChatOwnerEmote` | `0x040` | `ColorInt` |
| `ChatPriv` | `0x044` | `ColorInt` |
| `ChatPrivEmote` | `0x048` | `ColorInt` |
| `ChatPrivOwner` | `0x04C` | `ColorInt` |
| `ChatPrivOwnerEmote` | `0x050` | `ColorInt` |
| `ChatBuddy` | `0x054` | `ColorInt` |
| `ChatSelf` | `0x058` | `ColorInt` |
| `AcceptTrue` | `0x05C` | `ColorInt` |
| `AcceptFalse` | `0x060` | `ColorInt` |
| `MapSelected` | `0x064` | `ColorInt` |
| `MapUnselected` | `0x068` | `ColorInt` |
| `MOTD` | `0x06C` | `ColorInt` |
| `MOTDHeading` | `0x070` | `ColorInt` |

### `OptionGroup`

Parsed by `0x000945A0`

_No field table: this block parses its body directly._

### `PlayerAIType`

Parsed by `0x000DF1A0`

_No field table: this block parses its body directly._

### `PlayerTemplate`

Parsed by `0x000E4210` — `?parsePlayerTemplateDefinition@PlayerTemplateStore@@SAXPAVINI@@@Z`

Field table `0x010847E0` — 49 fields

| Field | Offset | Type |
|---|---|---|
| `Side` | `0x008` | `AsciiString` |
| `PlayableSide` | `0x0BD` | `Bool` |
| `DisplayName` | `0x004` | `AndTranslateLabel` |
| `StartMoney` | `0x01C` | `StartMoney` |
| `PreferredColor` | `0x028` | `RGBColor` |
| `StartingBuilding` | `0x034` | `AsciiString` |
| `StartingUnit0` | `0x038` | `AsciiString` |
| `StartingUnit1` | `0x03C` | `AsciiString` |
| `StartingUnit2` | `0x040` | `AsciiString` |
| `StartingUnit3` | `0x044` | `AsciiString` |
| `StartingUnit4` | `0x048` | `AsciiString` |
| `StartingUnit5` | `0x04C` | `AsciiString` |
| `StartingUnit6` | `0x050` | `AsciiString` |
| `StartingUnit7` | `0x054` | `AsciiString` |
| `StartingUnit8` | `0x058` | `AsciiString` |
| `StartingUnit9` | `0x05C` | `AsciiString` |
| `ProductionCostChange` | `0x000` | `ProductionCostChange` |
| `ProductionTimeChange` | `0x000` | `ProductionTimeChange` |
| `ProductionVeterancyLevel` | `0x000` | `ProductionVeterancyLevel` |
| `IntrinsicSciences` | `0x08C` | `0x000BCD80` |
| `IntrinsicSciencesMP` | `0x098` | `0x000BCD80` |
| `PurchaseScienceCommandSet` | `0x0A4` | `AsciiString` |
| `PurchaseScienceCommandSetMP` | `0x0A8` | `AsciiString` |
| `SpecialPowerShortcutCommandSet` | `0x0AC` | `AsciiString` |
| `SpecialPowerShortcutWinName` | `0x0B0` | `AsciiString` |
| `SpecialPowerShortcutButtonCount` | `0x0B4` | `Int` |
| `IsObserver` | `0x0BC` | `Bool` |
| `IntrinsicSciencePurchasePoints` | `0x0C0` | `Int` |
| `ScoreScreenImage` | `0x0CC` | `AsciiString` |
| `LoadScreenImage` | `0x0D0` | `AsciiString` |
| `LoadScreenMusic` | `0x0B8` | `AsciiString` |
| `HeadWaterMark` | `0x0D4` | `AsciiString` |
| `FlagWaterMark` | `0x0D8` | `AsciiString` |
| `EnabledImage` | `0x0DC` | `AsciiString` |
| `SideIconImage` | `0x0E0` | `AsciiString` |
| `BeaconName` | `0x0E4` | `AsciiString` |
| `LightPointsUpSound` | `0x100` | `0x000BABF0` |
| `ObjectiveAddedSound` | `0x104` | `0x000BABF0` |
| `ObjectiveCompletedSound` | `0x108` | `0x000BABF0` |
| `InitialUpgrades` | `0x0E8` | `AsciiStringVector` |
| `DefaultPlayerAIType` | `0x10C` | `AsciiString` |
| `SpellBook` | `0x110` | `AsciiString` |
| `SpellBookMp` | `0x114` | `AsciiString` |
| `MaxLevelMP` | `0x0C4` | `Int` |
| `MaxLevelSP` | `0x0C8` | `Int` |
| `Evil` | `0x118` | `Bool` |
| `BuildableHeroesMP` | `0x0F4` | `AsciiStringVector` |
| `SpellStoreCurrentPowerLabel` | `0x11C` | `AsciiString` |
| `SpellStoreMaximumPowerLabel` | `0x120` | `AsciiString` |

### `PredefinedEvaEvent`

Parsed by `0x00425C90`

Field table `0x010F1B68` — 5 fields

| Field | Offset | Type |
|---|---|---|
| `Priority` | `0x00C` | `UnsignedInt` |
| `TimeBetweenEventsMS` | `0x000` | `UnsignedInt` |
| `ExpirationTimeMS` | `0x004` | `UnsignedInt` |
| `QuietTimeMS` | `0x008` | `UnsignedInt` |
| `SideSound` | `0x010` | `0x004255F0` |

<details><summary><code>SideSound</code> sub-block — 2 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Side` | `0x000` | `AsciiString` |
| `Sound` | `0x004` | `0x000BABF0` |

</details>

### `Rank`

Parsed by `0x003A0DA0`

Field table `0x010EC620` — 9 fields

| Field | Offset | Type |
|---|---|---|
| `RankName` | `0x00C` | `AndTranslateLabel` |
| `SkillPointsNeededDefault` | `0x010` | `Int` |
| `SkillPointsNeededCampaign` | `0x014` | `Int` |
| `SkillPointsNeededGondor` | `0x018` | `Int` |
| `SkillPointsNeededRohan` | `0x01C` | `Int` |
| `SkillPointsNeededMordor` | `0x020` | `Int` |
| `SkillPointsNeededIsengard` | `0x024` | `Int` |
| `SciencesGranted` | `0x02C` | `0x000BCD80` |
| `SciencePurchasePointsGranted` | `0x028` | `UnsignedInt` |

### `ReallyLowMHz`

Parsed by `0x0007BE30` — `?parseReallyLowMHz@@YAXPAVINI@@@Z`

_No field table: this block parses its body directly._

### `RingEffect`

Parsed by `0x00421F50` — `?parseRingEffect@@YAXPAVINI@@@Z`

Field table `0x010F1748` — 11 fields

| Field | Offset | Type |
|---|---|---|
| `Scale` | `0x000` | `Real` |
| `Blend` | `0x004` | `Real` |
| `BaseSaturation` | `0x024` | `Real` |
| `EffectSaturation` | `0x020` | `Real` |
| `BaseColor` | `0x014` | `RGBColor` |
| `EffectColor` | `0x008` | `RGBColor` |
| `Velocity` | `0x04C` | `Real` |
| `TextureCross` | `0x050` | `Real` |
| `TextureRepeatCount` | `0x054` | `Real` |
| `EffectBlurDiameter` | `0x058` | `Int` |
| `BaseBlurDiameter` | `0x05C` | `Real` |

### `Road`

Parsed by `0x000C2EE0`

Field table `0x01114BB0` — 3 fields

| Field | Offset | Type |
|---|---|---|
| `Texture` | `0x038` | `AsciiString` |
| `RoadWidth` | `0x014` | `Real` |
| `RoadWidthInTexture` | `0x018` | `Real` |

### `Science`

Parsed by `0x000E8630` — `?friend_parseScienceDefinition@ScienceStore@@SAXPAVINI@@@Z`

Field table `0x01084D40` — 6 fields

| Field | Offset | Type |
|---|---|---|
| `PrerequisiteSciences` | `0x018` | `0x000BE440` |
| `SciencePurchasePointCost` | `0x024` | `Int` |
| `SciencePurchasePointCostMP` | `0x028` | `Int` |
| `IsGrantable` | `0x02C` | `Bool` |
| `DisplayName` | `0x010` | `AndTranslateLabel` |
| `Description` | `0x014` | `AndTranslateLabel` |

### `ScriptAction`

Parsed by `0x00340A40`

Field table `0x010E7470` — 4 fields

| Field | Offset | Type |
|---|---|---|
| `InternalName` | `0x008` | `AsciiString` |
| `UIName` | `0x000` | `AsciiString` |
| `UIName2` | `0x004` | `AsciiString` |
| `HelpText` | `0x078` | `AsciiString` |

### `ScriptCondition`

Parsed by `0x00340AE0`

Field table `0x010E7470` — 4 fields

| Field | Offset | Type |
|---|---|---|
| `InternalName` | `0x008` | `AsciiString` |
| `UIName` | `0x000` | `AsciiString` |
| `UIName2` | `0x004` | `AsciiString` |
| `HelpText` | `0x078` | `AsciiString` |

### `ShellMenuScheme`

Parsed by `0x00581790` — `?parseShellMenuSchemeDefinition@INI@@SAXPAV1@@Z`

Field table `0x0110B5F0` — 2 fields

| Field | Offset | Type |
|---|---|---|
| `ImagePart` | `0x000` | `ImagePart` |
| `LinePart` | `0x000` | `LinePart` |

<details><summary><code>ImagePart</code> sub-block — 3 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `Position` | `0x004` | `ICoord2D` |
| `Size` | `0x00C` | `ICoord2D` |
| `ImageName` | `0x014` | `MappedImage` |

</details>

<details><summary><code>LinePart</code> sub-block — 4 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `StartPosition` | `0x000` | `ICoord2D` |
| `EndPosition` | `0x008` | `ICoord2D` |
| `Color` | `0x014` | `ColorInt` |
| `Width` | `0x010` | `Int` |

</details>

### `SkyboxTextureSet`

Parsed by `0x000B8C90`

Field table `0x010F1638` — 5 fields

| Field | Offset | Type |
|---|---|---|
| `SkyboxTextureN` | `0x004` | `AsciiString` |
| `SkyboxTextureE` | `0x008` | `AsciiString` |
| `SkyboxTextureS` | `0x00C` | `AsciiString` |
| `SkyboxTextureW` | `0x010` | `AsciiString` |
| `SkyboxTextureT` | `0x014` | `AsciiString` |

### `SpecialPower`

Parsed by `0x000EBE90` — `?parseSpecialPowerDefinition@SpecialPowerStore@@`

Field table `0x012A8FA0` — 13 fields

| Field | Offset | Type |
|---|---|---|
| `ReloadTime` | `0x018` | `DurationUnsignedInt` |
| `RequiredScience` | `0x01C` | `Science` |
| `LightPointCost` | `0x020` | `Int` |
| `InitiateSound` | `0x024` | `AudioEventRTS` |
| `InitiateAtLocationSound` | `0x094` | `AudioEventRTS` |
| `PublicTimer` | `0x114` | `Bool` |
| `Enum` | `0x014` | `IndexList` |
| `DetectionTime` | `0x104` | `DurationUnsignedInt` |
| `SharedSyncedTimer` | `0x115` | `Bool` |
| `ViewObjectDuration` | `0x108` | `DurationUnsignedInt` |
| `ViewObjectRange` | `0x10C` | `Real` |
| `RadiusCursorRadius` | `0x110` | `Real` |
| `PalantirMovie` | `0x118` | `AsciiString` |

### `StaticGameLOD`

Parsed by `0x0007CEC0` — `?parseStaticGameLODDefinition@INI@@SAXPAV1@@Z`

Field table `0x01076760` — 26 fields

| Field | Offset | Type |
|---|---|---|
| `MaxParticleCount` | `0x000` | `Int` |
| `UseShadowVolumes` | `0x004` | `Bool` |
| `UseShadowDecals` | `0x005` | `Bool` |
| `UseAnisotropic` | `0x006` | `Bool` |
| `UsePixelShaders` | `0x007` | `Bool` |
| `UseLightMap` | `0x008` | `Bool` |
| `ShowSoftWaterEdge` | `0x009` | `Bool` |
| `MaxTankTrackEdges` | `0x00C` | `Int` |
| `MaxTankTrackOpaqueEdges` | `0x010` | `Int` |
| `MaxTankTrackFadeDelay` | `0x014` | `Int` |
| `UseBuildupScaffolds` | `0x018` | `Bool` |
| `UseTreeSway` | `0x019` | `Bool` |
| `GrassDrawSkip` | `0x01A` | `Int` |
| `ShowProps` | `0x022` | `Bool` |
| `TextureReductionFactor` | `0x01C` | `Int` |
| `UseHighQualityVideo` | `0x023` | `Bool` |
| `AnimationDetail` | `0x024` | `0x0007BCF0` |
| `MinParticlePriority` | `0x028` | `IndexList` |
| `MinParticleSkipPriority` | `0x02C` | `IndexList` |
| `MinimumFPS` | `0x000` | `Int` |
| `ParticleSkipMask` | `0x004` | `Int` |
| `DebrisSkipMask` | `0x008` | `Int` |
| `SlowDeathScale` | `0x00C` | `Real` |
| `MaximumAmbientStreams` | `0x000` | `Int` |
| `AllowDolby` | `0x004` | `Bool` |
| `AllowReverb` | `0x005` | `Bool` |

### `StreamedSound`

Parsed by `0x000B17C0`

Field table `0x010813F8` — 21 fields

| Field | Offset | Type |
|---|---|---|
| `Filename` | `0x00C` | `AsciiString` |
| `Volume` | `0x010` | `PercentToReal` |
| `VolumeShift` | `0x014` | `PercentToReal` |
| `MinVolume` | `0x018` | `PercentToReal` |
| `PitchShift` | `0x000` | `0x000AFFF0` |
| `PlayPercent` | `0x024` | `PercentToReal` |
| `Delay` | `0x000` | `0x000AFF40` |
| `Limit` | `0x030` | `Int` |
| `Priority` | `0x034` | `IndexList` |
| `Type` | `0x038` | `BitString32` |
| `Control` | `0x03C` | `BitString32` |
| `Sounds` | `0x040` | `0x000B1DF0` |
| `Attack` | `0x050` | `0x000B1DF0` |
| `Decay` | `0x060` | `0x000B1DF0` |
| `MinRange` | `0x074` | `Real` |
| `MaxRange` | `0x078` | `Real` |
| `LowPassCutoff` | `0x070` | `PercentToReal` |
| `ReverbEffectLevel` | `0x07C` | `PercentToReal` |
| `DryLevel` | `0x080` | `PercentToReal` |
| `SubmixSlider` | `0x088` | `IndexList` |
| `VolumeSliderMultiplier` | `0x08C` | `0x000B0990` |

### `Terrain`

Parsed by `0x000C2AC0`

Field table `0x01080BF8` — 5 fields

| Field | Offset | Type |
|---|---|---|
| `Texture` | `0x008` | `AsciiString` |
| `BlendEdges` | `0x00C` | `Bool` |
| `Class` | `0x010` | `0x000BD9F0` |
| `RestrictConstruction` | `0x01C` | `Bool` |
| `TerrainObject` | `0x000` | `0x000A8820` |

### `Upgrade`

Parsed by `0x0010B280` — `?parseUpgradeDefinition@UpgradeCenter@@SAXPAVINI@@@Z`

Field table `0x01088B60` — 12 fields

| Field | Offset | Type |
|---|---|---|
| `DisplayName` | `0x010` | `AsciiString` |
| `Tooltip` | `0x014` | `AsciiString` |
| `Type` | `0x004` | `IndexList` |
| `BuildTime` | `0x018` | `Real` |
| `BuildCost` | `0x01C` | `Int` |
| `ButtonImage` | `0x110` | `AsciiString` |
| `ResearchSound` | `0x028` | `AudioEventRTS` |
| `UnitSpecificSound` | `0x098` | `AudioEventRTS` |
| `UpgradeFX` | `0x024` | `AsciiString` |
| `Cursor` | `0x118` | `AsciiString` |
| `PersistsInCampaign` | `0x11C` | `Bool` |
| `NoUpgradeDiscount` | `0x11D` | `Bool` |

### `VictorySystemData`

Parsed by `0x000C3060`

Field table `0x0109FC28` — 4 fields

| Field | Offset | Type |
|---|---|---|
| `CellSize` | `0x00C` | `Real` |
| `ScalePerLogicFrame` | `0x014` | `Real` |
| `SubtractPerLogicFrame` | `0x018` | `Real` |
| `CellBonusRadius` | `0x020` | `Real` |

### `WaterSet`

Parsed by `0x000C37E0` — `?parseWaterSettingDefinition@INI@@SAXPAV1@@Z`

Field table `0x010F6C00` — 12 fields

| Field | Offset | Type |
|---|---|---|
| `SkyTexture` | `0x004` | `AsciiString` |
| `WaterTexture` | `0x008` | `AsciiString` |
| `Vertex00Color` | `0x014` | `RGBAColorInt` |
| `Vertex10Color` | `0x024` | `RGBAColorInt` |
| `Vertex01Color` | `0x044` | `RGBAColorInt` |
| `Vertex11Color` | `0x034` | `RGBAColorInt` |
| `DiffuseColor` | `0x054` | `RGBAColorInt` |
| `TransparentDiffuseColor` | `0x064` | `RGBAColorInt` |
| `UScrollPerMS` | `0x074` | `Real` |
| `VScrollPerMS` | `0x078` | `Real` |
| `SkyTexelsPerUnit` | `0x010` | `Real` |
| `WaterRepeatCount` | `0x00C` | `Int` |

### `WaterTextureList`

Parsed by `0x000C2BC0`

Field table `0x0108132C` — 1 fields

| Field | Offset | Type |
|---|---|---|
| `Texture` | `0x008` | `AsciiStringVectorAppend` |

### `WaterTransparency`

Parsed by `0x000C3A00` — `?parseWaterTransparencyDefinition@INI@@SAXPAV1@@Z`

Field table `0x010F6CD0` — 7 fields

| Field | Offset | Type |
|---|---|---|
| `TransparentWaterDepth` | `0x00C` | `Real` |
| `TransparentWaterMinOpacity` | `0x010` | `Real` |
| `StandingWaterColor` | `0x014` | `RGBColor` |
| `StandingWaterTexture` | `0x030` | `AsciiString` |
| `AdditiveBlending` | `0x02C` | `Bool` |
| `RadarWaterColor` | `0x020` | `RGBColor` |
| `RiverTransparencyMultiplier` | `0x034` | `Real` |

### `Weapon`

Parsed by `0x001E9C40` — `?parseWeaponTemplateDefinition@WeaponStore@@SAXPAVINI@@@Z`

Field table `0x0109FE18` — 112 fields

| Field | Offset | Type |
|---|---|---|
| `AttackRange` | `0x014` | `Real` |
| `MinimumAttackRange` | `0x018` | `Real` |
| `RequestAssistRange` | `0x01C` | `Real` |
| `AcceptableAimDelta` | `0x020` | `AngleReal` |
| `AimDirection` | `0x024` | `AngleReal` |
| `ScatterRadius` | `0x028` | `Real` |
| `ScatterTargetScalar` | `0x02C` | `Real` |
| `ScatterRadiusVsInfantry` | `0x514` | `Real` |
| `ScatterIndependently` | `0x030` | `Bool` |
| `DisableScatterForTargetsOnWall` | `0x031` | `Bool` |
| `WeaponSpeed` | `0x058` | `VelocityReal` |
| `MinWeaponSpeed` | `0x05C` | `VelocityReal` |
| `MaxWeaponSpeed` | `0x060` | `VelocityReal` |
| `ScaleWeaponSpeed` | `0x064` | `Bool` |
| `CanBeDodged` | `0x065` | `Bool` |
| `IdleAfterFiringDelay` | `0x068` | `DurationUnsignedInt` |
| `HoldAfterFiringDelay` | `0x06C` | `DurationUnsignedInt` |
| `CanFireWhileMoving` | `0x070` | `Bool` |
| `CanFireWhileCharging` | `0x071` | `Bool` |
| `CanSwoop` | `0x072` | `Bool` |
| `WeaponRecoil` | `0x074` | `AngleReal` |
| `MinTargetPitch` | `0x078` | `AngleReal` |
| `MaxTargetPitch` | `0x07C` | `AngleReal` |
| `PreferredTargetBone` | `0x080` | `AsciiString` |
| `FireSound` | `0x0B4` | `AudioEventRTS` |
| `FireSoundLoopTime` | `0x124` | `DurationUnsignedInt` |
| `FireFX` | `0x094` | `AllVetLevelsFXList` |
| `PreAttackFX` | `0x0A4` | `AllVetLevelsFXList` |
| `ProjectileExhaust` | `0x084` | `AllVetLevelsPSys` |
| `VeterancyFireFX` | `0x094` | `PerVetLevelFXList` |
| `VeterancyProjectileExhaust` | `0x084` | `PerVetLevelPSys` |
| `ClipSize` | `0x4AC` | `Int` |
| `ContinuousFireOne` | `0x4C0` | `Int` |
| `ContinuousFireTwo` | `0x4C4` | `Int` |
| `ContinuousFireCoast` | `0x4C8` | `DurationUnsignedInt` |
| `AutoReloadWhenIdle` | `0x4CC` | `DurationUnsignedInt` |
| `ShotsPerBarrel` | `0x4D0` | `Int` |
| `DamageDealtAtSelfPosition` | `0x4E4` | `Bool` |
| `ProjectileFilterInContainer` | `0x4E8` | `0x0039F470` |
| `ProjectileSelf` | `0x4EC` | `Bool` |
| `MeleeWeapon` | `0x4ED` | `Bool` |
| `ChaseWeapon` | `0x4EE` | `Bool` |
| `LeechRangeWeapon` | `0x4F8` | `Bool` |
| `HitStoredTarget` | `0x4F9` | `Bool` |
| `CapableOfFollowingWaypoints` | `0x4FA` | `Bool` |
| `ShowsAmmoPips` | `0x4FB` | `Bool` |
| `AllowAttackGarrisonedBldgs` | `0x4FC` | `Bool` |
| `PlayFXWhenStealthed` | `0x4FD` | `Bool` |
| `FiringDuration` | `0x50C` | `DurationUnsignedInt` |
| `ContinueAttackRange` | `0x510` | `Real` |
| `SuspendFXDelay` | `0x518` | `DurationUnsignedInt` |
| `IgnoreLinearFirstTarget` | `0x51C` | `Bool` |
| `ForceDisplayPercentReady` | `0x51D` | `Bool` |
| `IsAimingWeapon` | `0x51E` | `Bool` |
| `NoVictimNeeded` | `0x533` | `Bool` |
| `RotatingTurret` | `0x534` | `Bool` |
| `HitPercentage` | `0x520` | `PercentToReal` |
| `HitPassengerPercentage` | `0x524` | `PercentToReal` |
| `PreAttackDelay` | `0x500` | `DurationUnsignedInt` |
| `PreAttackRandomAmount` | `0x504` | `DurationUnsignedInt` |
| `PassengerProportionalAttack` | `0x508` | `Bool` |
| `MaxAttackPassengers` | `0x509` | `Int` |
| `FinishAttackOnceStarted` | `0x529` | `Bool` |
| `OverrideVoiceAttackSound` | `0x128` | `AudioEventRTS` |
| `OverrideVoiceAttackGroupSound` | `0x198` | `AudioEventRTS` |
| `OverrideVoiceAttack2Sound` | `0x208` | `AudioEventRTS` |
| `OverrideVoiceAttackGroup2Sound` | `0x278` | `AudioEventRTS` |
| `OverrideVoiceEnterStateAttackSound` | `0x2E8` | `AudioEventRTS` |
| `OverrideVoiceEnterStateAttackGroupSound` | `0x358` | `AudioEventRTS` |
| `OverrideVoiceEnterStateAttack2Sound` | `0x3C8` | `AudioEventRTS` |
| `OverrideVoiceEnterStateAttackGroup2Sound` | `0x438` | `AudioEventRTS` |
| `RestrictedHeightRange` | `0x52C` | `Real` |
| `CannotTargetCastleVictims` | `0x530` | `Bool` |
| `RequireFollowThru` | `0x531` | `Bool` |
| `ShareTimers` | `0x532` | `Bool` |
| `ShouldPlayUnderAttackEvaEvent` | `0x535` | `Bool` |
| `PreAttackType` | `0x4F4` | `IndexList` |
| `AutoReloadsClip` | `0x4F0` | `IndexList` |
| `RadiusDamageAffects` | `0x4D8` | `BitString32` |
| `ProjectileCollidesWith` | `0x4E0` | `BitString32` |
| `FXTrigger` | `0x010` | `IndexList` |
| `DamageType` | `0x04C` | `IndexList` |
| `DeathType` | `0x050` | `IndexList` |
| `DamageFXType` | `0x054` | `IndexList` |
| `AntiAirborneVehicle` | `0x4D4` | `BitInInt32` |
| `AntiGround` | `0x4D4` | `BitInInt32` |
| `AntiProjectile` | `0x4D4` | `BitInInt32` |
| `AntiSmallMissile` | `0x4D4` | `BitInInt32` |
| `AntiMine` | `0x4D4` | `BitInInt32` |
| `AntiParachute` | `0x4D4` | `BitInInt32` |
| `AntiAirborneInfantry` | `0x4D4` | `BitInInt32` |
| `AntiAirborneMonster` | `0x4D4` | `BitInInt32` |
| `AntiBallisticMissile` | `0x4D4` | `BitInInt32` |
| `AntiStructure` | `0x4D4` | `BitInInt32` |
| `DelayBetweenShots` | `0x000` | `0x001E1220` |
| `ClipReloadTime` | `0x000` | `0x001E1350` |
| `ScatterTarget` | `0x000` | `0x001EA7F0` |
| `LinearTarget` | `0x000` | `0x001EA880` |
| `WeaponBonus` | `0x000` | `0x001E3F20` |
| `DamageNugget` | `0x000` | `0x001E5940` |
| `ClearNuggets` | `0x000` | `0x001E3F90` |
| `DamageFieldNugget` | `0x000` | `0x001E5C90` |
| `WeaponOCLNugget` | `0x000` | `0x001E5D60` |
| `ProjectileNugget` | `0x000` | `0x001E5E30` |
| `MetaImpactNugget` | `0x000` | `0x001E5F00` |
| `HordeAttackNugget` | `0x000` | `0x001E60A0` |
| `SpawnAndFadeNugget` | `0x000` | `0x001E6170` |
| `GrabNugget` | `0x000` | `0x001E5FD0` |
| `AttributeModifierNugget` | `0x000` | `0x001E5A20` |
| `SpecialModelConditionNugget` | `0x000` | `0x001E5AF0` |
| `ParalyzeNugget` | `0x000` | `0x001E5BC0` |
| `LuaEventNugget` | `0x000` | `0x001E6240` |

### `Weather`

Parsed by `0x0045B130` — `?parseWeatherDefinition@INI@@SAXPAV1@@Z`

Field table `0x010F6540` — 24 fields

| Field | Offset | Type |
|---|---|---|
| `SnowTexture` | `0x00C` | `AsciiString` |
| `SnowFrequencyScaleX` | `0x010` | `Real` |
| `SnowFrequencyScaleY` | `0x014` | `Real` |
| `SnowAmplitude` | `0x018` | `Real` |
| `SnowPointSize` | `0x01C` | `Real` |
| `SnowMaxPointSize` | `0x020` | `Real` |
| `SnowMinPointSize` | `0x024` | `Real` |
| `SnowQuadSize` | `0x028` | `Real` |
| `SnowBoxHeight` | `0x02C` | `Real` |
| `SnowSpacing` | `0x030` | `Real` |
| `SnowSpeed` | `0x034` | `Real` |
| `SnowPointSprites` | `0x038` | `Bool` |
| `SnowEnabled` | `0x039` | `Bool` |
| `IsSnowing` | `0x03A` | `Bool` |
| `NumberTiles` | `0x03C` | `Int` |
| `LightningEnabled` | `0x040` | `Bool` |
| `LightningFactor` | `0x044` | `GameClientRandomVariable` |
| `LightningDuration` | `0x050` | `Int` |
| `LightningChance` | `0x054` | `Real` |
| `SpellEnabled` | `0x058` | `Bool` |
| `SpellDuration` | `0x05C` | `Int` |
| `RampControl` | `0x060` | `Coord2D` |
| `RampSpacing` | `0x070` | `Coord2D` |
| `RampSpeed` | `0x068` | `Coord2D` |

### `WeatherData`

Parsed by `0x0039B380`

Field table `0x010EBC2C` — 2 fields

| Field | Offset | Type |
|---|---|---|
| `WeatherSound` | `0x000` | `0x000BABF0` |
| `HasLightning` | `0x004` | `Bool` |

### `WindowTransition`

Parsed by `0x0048B7C0`

Field table `0x010F95A4` — 2 fields

| Field | Offset | Type |
|---|---|---|
| `Window` | `0x000` | `0x0048BD60` |
| `FireOnce` | `0x000` | `Bool` |

<details><summary><code>Window</code> sub-block — 3 fields</summary>

| Field | Offset | Type |
|---|---|---|
| `WinName` | `0x000` | `AsciiString` |
| `Transition` | `0x000` | `0x0048BD00` |
| `FrameDelay` | `0x004` | `Int` |

</details>

