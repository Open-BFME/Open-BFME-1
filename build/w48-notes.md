## w41-i round 1 (claude-sonnet-5-5)
3 batches x5 files served (Rva001F9C20Unknown, BezierSegment ctor dup, Rva0034FE00Assign, HordeSiegeEngineContain data ctor, CritterEmitterUpdate data ctor, DelayedLuaEventUpdate ctor, SpawnUnitBehavior data ctor, StructureCollapse data ctor, UnicodeString...). Keys were mostly opaque offset members (m_flagC4, m_f70, m_dieData0) with no header/caller evidence; all skipped. Bezier params x0..z3/cp0..cp3 are rejected as "still a placeholder" even with ZH names. Dead end: submitting ZH-identical param names.

## w41-i round 2 (claude-sonnet-5-5)
3 batches x5 served. Only submitted: S3FlagPairRefreshes classes (DefaultAlphaModule/DefaultColorModule/WindModule/DefaultUpdateModule/RenderObjectUpdateModule, from FXParticleSystem::*ModuleInfo::DoXfer callees). Everything else skipped: opaque offset members (m_210.., m_value34), address-named dump types (Rva0041F070, Rva1FC330*, BfmeThing*), param names of inline string/Lerp helpers. Dead end: ModuleData ctor members with only zero-stores and no ZH twin.
## agent h round 1 (wave 48)
- 4 batches x5 files served. Almost all keys are opaque (ctor offset fields, ICF-shared module data, Rva-typed views) with no ZH twin: skipped.
- An all-skip answer is rejected by submit ("no valid names"); nothing recorded, harmless.
- Landed: DynamicPortalBehaviour Rva001F8E20Owner::method local d -> moduleData (agreed with sol).
- Dead end: AIRootR0015C7A0 -> AI rejected (collides with `class AI;` forward decl in same TU).
- Weak/skipped: FlightDeckBehaviorModuleData +C4/C8/CC (BFME layout differs from ZH), CrossFadeImage m_image2, Rider/HordeSiege/HordeContain module data offsets.
## agent h round 2 (wave 48)
- 3 batches x5 served; all keys skipped (nothing submitted, all-skip is rejected anyway). Keys: FESL request fns Rva007FAF90.. (FourCC DISC/EPGT/RLST/RGAM/PING, no EA names), ObjectGeometry m_helper3b4/3b8, BfmeDebugDisplayVTable, Triple member copy types (Rva00138BA0*), GateOpenAndCloseBehaviorModuleData m_byte08/m_dword0C.. (no ZH twin, values 50/50 ambiguous), FXEventParser at08..at1c, drawMoveHints byte_10.
- Dead end: Rva-typed helper/copy classes and BFME-only module data ctor members.

## w41-i round 3 (claude-sonnet-5-5)
3 batches x5 served, all skipped (nothing submitted). Keys: ModuleData ctor members with only constant stores (ClearanceTestingSlowDeath, Enraged, GateOpenAndClose, HitReaction, DamageModule, Firestorm), Rva-address helper types/params, Envelope/Bfme* offset members, tree-walk Rva00477E60. No ZH twin/field-parse table evidence in the briefs. Dead end again: ctor-only ModuleData batches; prefer files whose brief cites a FieldParse table or ZH header.
## agent h round 3 (wave 48)
- 3 batches x5 served; nothing valid to submit. Keys: BezierSegment ctor params (again), CastleMember/Enraged/ShareExperience/SlaughterHorde/Garrison/W3DFloor module data ctor offsets (no ZH twin, BFME layout differs), Rva-typed dump classes, MemberTurnAndGoal offset flags.
- Dead end confirmed: Pathfinder::iterateCellsAlongLine locals xinc2/yinc2/x/y submitted as identical ZH names -> "still a placeholder" (the key is a placeholder only because of declaration-line grouping).

## w41-i round 4 (claude-sonnet-5-5)
3 batches x5 served, all skipped (nothing submitted). Keys: FESL simple requests Rva007FAF90.. (again; FourCC only, no EA names), RainOfFire/CastleMember/Spawn/Wander/Animal/BannerCarrier ModuleData ctor offset members, Open2Elem247180 stand-in, Rva005222A0 AptMessageBox members, BfmeMsgVIW/BfmeSeed, W3DLaser BfmeEnvelope (parser not shown, ZH has no Envelope), LivingWorldManager dtor Rva types + Release_Ref local n. Still no ZH twin or FieldParse evidence.
## agent h round 4 (wave 48)
- 3 batches x5 served; nothing submitted. Keys: Bezier/Devastate/FadeAndDieOrnament/W3DStreakDraw module data ctor members (no ZH twin), Rva-typed helper classes, Bfme* offset members, ScreenCrossFade postRender locals p/u/v/u1/v1 and calculateTerrainLOD freq64/startTime64/time64 (ZH-identical names are rejected as placeholders; dead end already known).

## w41-i round 5 (claude-sonnet-5-5)
3 batches x5 served, nothing landed. Keys: FESL hosted-game Rva007F61E0 Sender/Notifier, BfmeSrcGG/MaskGG, Gen003CAE40Hold, WanderAIUpdateModuleData/ReplenishUnits ctor offsets, MemberVision002434D0 atNNN fields, Shadow Rva00459960 m_value3C, SpawnUnit ctor offsets. Only one submit: DebugDisplay::setCursorPos x/y (ZH-identical) -> rejected "still a placeholder" (dead end reconfirmed).

## w41-i round 6 (claude-sonnet-5-5)
3 batches x5 served, nothing submitted. Keys: Rva0077C390 parse Model/Owner (brief leaks a BFME2 EA-name hint line; ignored for blind voting), ParseMoveCameraBlock Rva003B7650Record m_04..m_18, BfmeConv2022/1000/1778/1115 Bfme* types, Rva004155A0 notifyArrays types (Drawable.cpp, ZH-less), BFMEFactoryModuleData m_unmodelled_*, AIAttackSwoop Rva002BC870, Q3 sort median a/b/c, WaterRenderObj ctor offset members m_d0..m_400, InitializeAudioSlot offsets, calculateTerrainLOD freq64 locals (known placeholder dead end). All opaque/no ZH twin.
## agent h round 5 (wave 48)
- 3 batches x5 served. Submitted: ArchiveFileGetFileList.cpp (3 locals tempDirInfo/tempdirname/tempfilename with ZH names rejected "still a placeholder"; set/concat/compare/compareNoCase param s -> str and compare n -> minLen recorded as hashes). MapObjectFastAssignUniqueIDs AsciiString ctor param p -> s / c rejected as placeholder.
- Skipped: ToppleUpdate m_20/m_f18/m_f1c, HorseHorde/HordeSiege/FadeAndDie module data offsets, Rva-typed dump classes, LivingWorldArmyAssign m_08.., Apt bounds getter Bfme* members, Rva0010F100 call2 helper.

## w41-i round 7 (claude-sonnet-5-5)
3 batches x5 served, nothing submitted. Keys: Y2FeslDemanglerDispatch Rva00800E50Stamp/Owner m_00..m_20 (opaque), Rva8CDA60 Apt stack dispatch types, FadeAndDieOrnament/ShareExperience/Firestorm/BannerCarrier ModuleData ctor offsets, Rva003C7B60 create-render-object views (HolderView m_field08 = z height, BFME-only), BFMEFactoryModuleData m_unmodelled_*, CastleBehavior rva00371b00 (m_flagA5/m_objectIDsB8/ThingTemplate m_unmodelledD8 bit 0x200000: BFME-only, no ZH twin; Thing::getTemplate tmpl local is ZH-identical), Rva8BB1A0 bounds v00..v14, MemberTurnAndGoal offsets, BfmeConv1907/1778 Bfme* slots. Same dead ends as rounds 1-6.
## agent h round 6 (wave 48)
- 3 batches x5 served, nothing submitted. Keys: WanderAIUpdateModuleData ctor offsets (m_unknown20..m_flag54), Rva003C7B60 CreateRenderObject views, BfmeConv961/1115 Bfme* types, EnragedBehavior m_f1c/f20, DebugDisplay BfmeDebugDisplayVTable/setCursorPos x,y (known placeholder dead end), HorseHordeContain Rva002469D0 types, Rva003C1EE0 views, Rva004488B0 copy a-d, GlobalWeather m_at0C.., BannerCarrier m_field08.., Rva00889720. All opaque, no ZH twin.

## w41-i round 8 (claude-sonnet-5-5)
3 batches x5 served, nothing submitted. Keys: ClearanceTestingSlowDeath Rva001F72D0FloatPair/m_f210.., U2 Rva0083F2F0Duplicate locals p, Rva004262F0 BfmeRva004262F0Map, WeaponTemplate bfmeRangeBase, Rva005F6B60 Owner/Choice, Rva004155A0 notifyArrays (again), HordeSiegeEngine base ctor offsets, StructureCollapse m_dieData0..9 (again), Rva002D9910*, ReflectDamage m_unmodelled_*, Bezier params (again), Rva0034FE00Assign, SpawnUnit m_bfme10.. (again). Same dead ends; the queue keeps re-serving the same opaque files.
## agent h round 7 (wave 48)
- 3 batches x5 served, nothing submitted. Keys: FlightDeckBehaviorModuleData m_bfmeC4/C8/CC, EnragedBehavior m_unmodelled_18..28, Rva009A2350 Node/Link/m_08.., GloriousCharge m_field254.., Rva007F0210Set m_00.., BfmeConv1401/1901 Bfme*VKH/AU types, GettingBuilt m_f0..m_f3, CollideModule m_unknown*, AimWeapon m_08..m_14, HordeContain Rva002458B0*, Pathfinder iterateCellsAlongLine locals (known placeholder dead end), Rva00409F40Loop. All opaque, no ZH twin.

## w41-i round 9 (claude-sonnet-5-5)
3 batches x5 served, nothing submitted. Keys: Rva002BC310 height predicate (m_height44/m_heightLimit40, no ZH twin), HordeSiegeEngine ctor offsets, UpdateModule/DamageModule ctor thunks, MemberTurnAndGoal, BfmeConv961, Rva004488B0, ElementPayloadFill m_atNN, GateOpenAndClose, DeployStyleAIUpdate ctor offsets, Rva008BDD70 types, RenderObjectDrawModuleInfo copy-ctor m_nameN/m_valueNN. Same dead ends.
## agent h round 8 (wave 48)
- 3 batches x5 served, nothing submitted. Keys: BloodthirstyUpdate Gen_00287130/BfmeGuard96/BfmeFilterHolder, Lerp a/b params, CrossFadeImage m_image2, drawMoveHints byte_10/tmp, EmotionTrackerUpdateModuleData ctor offsets, BfmeConv1054 Bfme* slots, RvaTreeBounds locale comparators, Rva001F9C20 types, W3DStreak m_unmodelled_*, FindSafePath Bfme slots, S2ZeroFillCtors, Rva005F6B60, Rva0010F100, AIRootR0015C7A0. All opaque/no ZH twin: same dead ends.

## w41-i round 11 (claude-sonnet-5-5)
3 batches x5 served, nothing submitted. Keys: DamageModule/TransportAIUpdate/ReplenishUnits/ReflectDamage ModuleData ctor offsets, Gen003CAE40Hold, Rva0041F070 value2c/valuea8, Rva004488B0 copy params, BfmeConv1000/1401, BattlePlanUpdate set/clearCondition o. Same dead ends.
## agent h round 9 (wave 48)
- 3 batches x5 served, nothing submitted. Keys: BfmeConv827 BfmeMgr/Sub2B8/lookupAndSend (opaque vtable views), Rva008B7040Build m_value*, BfmeConv1226 BfmeE/P1226, MapObjectFastAssignUniqueIDs AsciiString p/s (known placeholder dead end), Rva008A4540 m_00/m_04, DebugDisplay setCursorPos x/y (known dead end), HitReaction ctor m_field*, U2 Rva0083F2F0Duplicate p, BfmeThreeHundredThirtyTwo BfmeNodeSD.., Rva005F6B60, W3DFloor m_unmodelled_*. All opaque/no ZH twin.

## w41-i round 12 (claude-sonnet-5-5)
3 batches x5 served, nothing submitted. Keys: HordeUpdateModuleData ctor thunk m_name0/m_f0..f3 (0.25/0.5/0.75/1.0, strings Gravity/DriftVelocity; actually GettingBuilt module data, opaque), ParseAudioEventBlock Rva003B7740/BfmeReleaseHolder, Rva003C7B60 views, DeployStyleAIUpdate ctor offsets, BfmeThingSF, BfmeConv1054, Rva00370730CastleMember, GloriousCharge m_field254.., Open2Elem247180, HordeSiegeEngine m_22c.., FESL Rva007F61E0. Same dead ends.
## agent h round 10 (wave 48)
- 3 batches x5 served, nothing submitted. Keys: Lerp a/b, Bfme5TinyTwentySeven Bfme* types, Rva001F9C20, U1SmallStateProbes, Rva008AE2E0 bounds, Rva005F6B60, Rva008BDD70, U2 Rva0083F2F0Duplicate p, Rva002469D0, BfmeConv2022, ClearanceTestingSlowDeath, Rva0041F070, ToppleUpdate m_20/m_f18, Rva0010F100 call2. All opaque/no ZH twin, same dead ends.

## w41-i round 13 (claude-sonnet-5-5)
3 batches x5 served, nothing submitted. Keys: EnragedBehaviorModuleData ctor m_unmodelled_18..28 (no ZH twin), BfmeConv961 Reset/Gate/Flag types, calculateTerrainLOD freq64 locals (known placeholder dead end), WanderAI/HordeWorkerAI ctor offsets, BfmeConv1054 (huge opaque), ScreenCrossFade postRender locals (dead end), Apt NativeStringSlots008B3AA0, W3DLightDrawModuleData ctor m_unmodelled_08..44, Rva007F0210Set, Rva002D9910*, BfmeConv1401, Rva00800B70FeslDtor. All opaque/no ZH twin.
## agent h round 11 (wave 48)
- 3 batches x5 served, nothing submitted. Keys: UpdateModuleModuleData ctor thunk m_unknown20.., BfmeConv1054 Bfme* (FXParticleSystem, opaque), line2_d.cpp ClipLine2D/IntersectLine2D params+locals (ZH-identical -> known placeholder dead end), GameLogicGetLoadScreen at078.. / Gen000290D2, DebugDisplay setCursorPos x/y, Rva009F4070DistanceSquared, BfmeConv1226, GarrisonContain ctor m_2F4.., Rva002CFC80TinyBodies, BfmeConv792, Rva00627AA0Obj. All opaque/no ZH twin.
