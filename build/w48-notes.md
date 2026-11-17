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
# w48 lane c (stlport) notes
- Rank 6/1 (deque Gen_t_00593270 reallocate_map), 11/12 list insert, 131 vector<void*>::erase: frozen gen_small holders, out of scope.
- Landed: list<Object*> ctor 0xCFFB0 (rank 14): TransportContainOnRemoving.cpp defined it with _STLP_USE_NEWALLOC -> operator new reloc; removing the define fixed it.
  Technique: comdat_families.py ranked --index ... --limit 20000 > json gives wrong_emitters/proven_copies per name; lc._comdat_sections(obj) shows relocs of an emitted copy.
- Rank 24 vector<bool>::reserve (RvaVectorBoolAssignment.cpp): link_check UNKNOWN, not analysed. Rank 13 find<void*> Rb_tree: wrong emitters are 3 GameNetwork Rva00654130/65B350 TUs sharing digest dc1e3f8bd848, owner-held, not analysed.
- Worktree: submodule pointer drift (master records aa505f34, checkout at 0630f0ef) blocks pre-push; used git update-index --assume-unchanged inputs/reference/open-bfme-2.
- link_check on a provider with many changed names takes ~3 min on a loaded host.

## w41-i round 14 (claude-sonnet-5-5)
3 batches x5 served, nothing submitted. Keys: BfmeConv1778 BfmeValDB/m_bfmeHeadDB (idle worker list node), W3DLaserDraw BfmeEnvelope m_bfme00..24 (again), BattlePlanUpdateSetStatus, V4GuardedTailCalls, BfmeConv1907 Bfme*BA slots, GettingBuilt/Enraged/TransportAI ctor thunks, BfmeConv808 EFC..EFH types/functions, WeaponTemplate bfmeRangeBase, LivingWorldArmyAssign. Same dead ends.
## agent h round 12 (wave 48)
- 3 batches x5 served, nothing submitted. Keys: CritterEmitterUpdate ModuleData ctor offsets, drawMoveHints byte_10/tmp, SlaughterHorde/SiegeDeploy ctor offsets, Rva009F4070DistanceSquared a/b, S5Parse005A0720, Bezier params, BloodthirstyUpdate Bfme*, Rva00889720, Rva00903470 slot77, GettingBuilt m_name0/f0.., Rva005F6B60. All opaque/no ZH twin, same dead ends.

## w41-i round 15 (claude-sonnet-5-5)
3 batches x5 served, nothing submitted. Keys: DeployStyleAIUpdateModuleData ctor thunk (stand-in actually Wander-like layout, ZH DeployStyle fields don't match), Glo012F1028Sub bfmeFinish members, Rva008BDD70 types, Rva001515C0Xfer, PathfinderFindSafePathBfme slots, BfmeOneHundredThirty m_bfmeNN, Small03eListNode, EnragedBehavior m_f1c/f20, Rva002CFC80TinyBodies, BfmeConv2022. Same dead ends.
## agent h round 13 (wave 48)
- 3 batches x5 served, nothing submitted. Keys: UnicodeString set/concat s, nextToken tmp (ZH-identical, known placeholder dead end), BfmeConv1309 TDA/TDB, Rva005222A0NoteCalls m_34..m_40, AIRootR0015C7A0, W3DLightDraw m_unmodelled_*, Rva001A51F0GridVisit flag2c/2d, RadarConstructor m_bfme000c/d/1454.. (no ZH twin), Rva002CFC80TinyBodies, BfmeConv808, CivilianSpawn ctor thunk, Rva00943DB0Node, BFMEFactory m_unmodelled_*, Rva0041F070. All opaque/no ZH twin.

## w41-i round 16 (claude-sonnet-5-5)
3 batches served, nothing submitted. Keys: HordeContainConstructor Rva0023EAF0TenWords/m_1e4..m_221 (opaque), RadiusDecalTemplate m_unmodelled_20..2C (BFME extras beyond ZH fields, no evidence), EnragedBehavior/ReflectDamage ctor offsets, Rva003C7B60, Rva007F0210Set, AIUpdateComputeQuickPath, BfmeConv1000/322, Rva0077C390Parse. Same dead ends.
## agent h round 14 (wave 48)
- 3 batches x5 served, nothing submitted. Keys: Y2FeslDemanglerDispatch Rva00800E50Stamp/Owner m_00.. t04/t18.., Rva004155A0 notifyArrays (Primary/Secondary callback arrays, EA Drawable.cpp, no evidence), GlobalWeather Rva0039B450Element m_at0C.., ObjectCreationUpgradeModuleData m_9c (custom DeathAnim third field, opaque), RubbleRise m_dwordB4/C4, StructureCollapse m_dieData0..9, HordeSiegeEngine ctor, BfmeConv1901, BfmeSeed37A750, W3DTerrainBackgroundReset m_78.., SiegeDeploy/DeployStyle/RainOfFire ctor offsets, Rva008A4540, InitializeAudioSlot006ACB90. All opaque/no ZH twin.

## w41-i round 17 (claude-sonnet-5-5)
3 batches served, nothing submitted. Keys: Rva0041F070 value2c/valuea8, BezierProjectile ctor m_value34/m_value84/m_flag88, RiderChangeContain ctor m_word/m_byte, BfmeConv1115, Rva008B7040Build, Gen001FE050 m_bfmeItem*, Create_Render_Obj field1..5, Rva0029C380, BfmeScriptCondAreaGate a0..a2 (arg semantics unknown), BfmeThreeHundredThirtyFour, S5Parse005A0720, Rva00800B70FeslDtor. Same dead ends.

## w41-i round 18 (claude-sonnet-5-5)
3 batches served, nothing submitted. Keys: SiegeDeploySpecialPowerModuleData ctor m_1d0..m_1e0 (500/200 floats, no ZH twin), BfmeConv1115, HordeContain ctor Rva0023EAF0TenWords/m_1e4.., WanderAIUpdate/CollideModule ctor thunk m_unknown*, Pathfinder iterateCellsAlongLine Bresenham locals (ZH-identical, known placeholder dead end). Same dead ends.
# w48 lane e (non-family LOSERS) notes
- link_check on one file takes ~4 min (run in background, poll). Index loader snippet: pickle build/link_census/link_index.pkl -> ix['comdat'][name] lists (obj, digest, 'retail'|'wrong'|'unknown').
- LANDED: SparseMatchFinderFindBestInfoSlowThunk.cpp: inline member BitFlags<17>::countInverseIntersection was emitted as COMDAT even though inlined (cl emits inlined inline-members). Declaring it extern-only breaks bytes (retail inlines). Recipe that works: replace member by a `static __forceinline` free helper (no COMDAT, same bytes).
- Dead ends: setAnimationLoopDuration@Drawable (Drawable.cpp present-unmatched body; retail body 0x413490 is ledgered as BfmeOwner1158::bfmeSubDAll1158 in BfmeConv1158.cpp, ILT 0x478CA; needs a name_lane rename ripple across 5+ callers; not done).
- RefHandle008958D0 dtor (row 32): Apt TUs 0x893030/895A00/895D30 need the dtor inlined in the body but funclet references the symbol; forceinline copy still emitted; documented in identity_evidence/00784a70-*. Needs a trick to keep funclet call external while body inlines; untried.
- MapMetaData::operator= (row 104, rva 0xC1050): INIMapCache/MapUtil use ZH MapUtil.h with implicit operator=; implicit copy COMDAT emitted. Fix needs explicit declaration in a shim header (full gate) -- not done.
- countInverseIntersection<17> also still emitted by ThingTemplate.obj (real header inline); needs shared header change.
- Push contention is heavy; loop pull --rebase + push; submodule pointer may need `git submodule update inputs/reference/open-bfme-2` (slow, ~3 min) before pre-push accepts.

## w41-i round 19 (claude-sonnet-5-5)
3 batches served, nothing submitted. Keys: AutoPickUpUpdateModuleData ctor m_flag3C/3D/m_value40/m_flag44, DelayedLuaEventUpdate ctor m_f20/f70.., T3SmallLeafBodies Rva*Key/Less, TaintSpecialPower m_unmodelled_214.., BfmeScriptCondAreaGate, CritterEmitter ctor, EnragedBehavior m_f1c/f20, DevastateSpecialPower m_210.., U1SmallStateProbes, Rva00889720, Rva008A4540. Same dead ends.
## agent h round 15 (wave 48)
- 3 batches x5 served, nothing submitted. Keys: BFMEFactoryModuleData LaserUpdate ctor m_unmodelled/flagPair, Rva0034FE00Assign (Scripts.cpp, opaque), calculateTerrainLOD freq64/startTime64/time64 (dead end), FreeLifeBody ctor m_unmodelled_*, drawMoveHints byte_10/tmp, HordeContain ctor m_1e4.., MpGameSetupSetMap m_flag10..15, ToggleMountedSpecialAbility ctor m_field254.., S2ZeroFillCtors, BfmeConv1279/970, BannerCarrier dtors m_fieldNN. Same dead ends.

## w41-i round 20 (claude-sonnet-5-5)
2 batches served (late-session, same pool), nothing submitted. Keys: DelayedLuaEventUpdate ctor m_f20/f70/f74/f75, Rva008BDD70 types, Rva00063F90Blend, Rva004155A0 Primary/Secondary/Owner, Rva005222A0NoteCalls m_34.., Rva0041F070, Rva008A4540. Same dead ends.

## w48 DXTRACE lane (wt/w41-a) round 1 (claude-opus-5-5, 2026-11-17)
- DXTraceA 0x00AFD388 banked partial (commit "Bank DXTraceA: MSVC 13.10 never biases its EBP frame"); handoff attempt_support/dxerr9-summer2003/tracea-bias-heuristic-20261117.md. Body = retail minus the 0x64 EBP bias (probe --shape: 3 structural diffs). Measured stash score 0.246 only because every displacement shifts.
- Dead ends (do not repeat): every flag family (/O1 /O2 /Ox /Os /Ot /Og /Od, /Oy-, /Ob0-2, /Oi-, /G5-7 /GB, /Gz /Gr, /ML /MD, /Zi /Z7, /Gs0 /Gs8192, /GF- /Gy-, /GA /Ge /J /Zp1 /Gm /Gi /GX /GR /QIfist), all 120 buffer declaration orders, inline StringCchCopyA + nResult, unused locals, scoped/packed strBuffer copies: all 369 B unbiased. /GZ and /RTCs are refused with /O1.
- Why: 13.10.3077 biases only when >=~3 refs to locals based BELOW -0x80 come into disp8; a local based at exactly -0x80 counts as near (repro attempt_support/dxerr9-summer2003/tracea-bias-micro.cpp.txt: b_128 unbiased, b_129/b_132 biased). DXTraceA's strBufferLine is at exactly -0x80, so zero gain. dxerr9.obj is 13.00.9178 (@comp.id 0x1d23da). Only routes left: a MASM body (policy call for the retirement lane) or none.
- DXTraceW 0x00AFD20F: same-structure candidate probes EXACT 377/377 (tracew-candidate.cpp.txt). Claimed by the sibling w48 retirement lane (Lomchat/59bfb59e); not landed here. If that claim is gone next round and W is still archive-owned, land it via add_match --replace-existing into game/Libraries/Source/DirectX/dxtracew.cpp.
- Gotcha: build/w48-notes.md is TRACKED and shared with the naming lanes; an untracked copy is clobbered by git pull. Append, then commit it.
- Gotcha: a /Zi probe writes vc70.pdb into the worktree root; delete it.
## w41-i round 21 (claude-sonnet-5-5)
3 batches served (1 file each seen), nothing submitted. Keys: HorseHordeContainModuleData dtor Rva002469D0* entries/m_00..m_2bc (opaque), Rva003B9AD0 pair copy ctor, Rva009F4070DistanceSquared a/b. Same dead ends.
## agent h round 16 (wave 48)
- 3 batches x5 served, nothing submitted. Keys: BfmeConv792 DWH/DWJ/DWL (tiny, no semantics), AIUpdateComputeQuickPath m_unmodelled_08/00 + ZH-identical params, Rva003B9AD0PairCopyCtor m_at04, INIMapCache locals (ZH-identical), Rva00409F40Loop, BfmeConv2137, InitializeAudioSlot006ACB90 floats, BfmeConv1226, Q3SortElem16Median a/b/c, ObjectCreationUpgrade m_9c, BfmeConv1778/1838, ParseMoveCameraBlock Rva003B7650Record. Same dead ends.

## w41-i round 22 (claude-sonnet-5-5)
3 batches served, nothing submitted. Keys: LivingWorldManagerDestructor Rva0060EBB0/Rva00614820 types, MemberTurnAndGoal0024E310, GettingBuilt/drawMoveHints, CrossFadeImage m_image2, BfmeScriptCondAreaGate, W3DLightDraw m_unmodelled_*, RiderChangeContain ctor, BfmeConv664/962, FlightDeck m_bfmeC4.. All opaque/no ZH twin.
## agent h round 17 (wave 48, claude-sonnet-5-5)
3 batches x5 served, nothing submitted (all skips). Keys: Rva00063F90Blend, EnragedBehavior m_f1c/m_f20 (ZH UpdateModule has only 2 fields), HordeUpdateModuleData m_f0..f3/m_name0/1 (no ZH twin), LivingWorldArmyAssign m_08.., BfmeConv1901, ParseFXEvent BfmeAnimationStateFXE, W3DStreakDrawModuleData m_unmodelled_*, bfmeMax/Min a,b, Rva0049A100Set, Rva00477E60Walk m_1F8/200/204 (tree links, weak), Rva8CDA60, V4GuardedTailCalls. Same dead ends.

## w41-i round 23 (claude-sonnet-5-5)
3 batches served, nothing landed. Keys: Create_Render_Obj field1..5, BloodthirstyUpdate BfmeGuard96/Gen_00287130, InGamePopupMessage mData1/2 + tempString and Bezier x0..z3 and line2_d p1/c1/a/b (all ZH-identical already; submitting the same name is rejected "still a placeholder"), BfmeConv1226/1279/2137/1838/334, Rva008B7040Build, CritterEmitter ctor, RbTree insert x/y/v/w. Same dead ends.
## agent h round 18 (wave 48, claude-sonnet-5-5)
- 3 batches x5 served, nothing submitted. Keys: CollideModule/Enraged/Firestorm/BezierProjectile ModuleData ctor offsets, HorseHordeContain dtor Rva002469D0*, P6MemberVectorCopyConstructor m_at00.., BfmeConv1054/2022 (again), Rva0020DEE0 VirtualMode m_08..m_18, Rva008A4540, Rva003B9AD0PairCopyCtor. All opaque/no ZH twin, same dead ends.

## agent h round 19 (wave 48, claude-sonnet-5-5)
- 1 batch x5 viewed, nothing submitted. Keys: BfmeConv961 Reset/Gate/Flag types (tiny, no ZH twin), Rva0041F070 value2c/valuea8/value11c, StructureCollapse/FadeAndDieOrnament ModuleData ctor m_dieData*/m_one*, LivingWorldArmyAssign m_08.., RbTree insert x/y/v/w. Same dead ends; stopped early.

## w41-i round 24 (claude-sonnet-5-5)
3 batches served, all skipped (nothing justifiable). Keys: Rva009A2350Node/Link (collision manager link), Rva8CDA60 stack dispatch, Rva0010F100Receiver, S2ZeroFillCtors, Rva0049A100, RubbleRise dword B4/C4, Lerp a/b, Bfme5TinyTwentySeven, Rva00063F90Blend, WanderAI ctor, Rva002CFC80TinyBodies, ToggleMounted, Rva0029C380, EnragedBehavior, BfmeConv2022. Same dead ends.
## agent h round 20 (wave 48, claude-sonnet-5-5)
- 3 batches served (1 file each), nothing submitted. Keys: BfmeConv808 (BfmeAEFC/BEFC/NodeEFE/GoEFx, tiny, no ZH twin), Rva008B7040Build m_value20..60 (Apt stack builder, opaque), FlightDeckBehaviorModuleData ctor m_bfmeC4/C8/CC (again, no ZH twin). Same dead ends.

## w41-i round 25 (claude-sonnet-5-5)
3 batches served, all skipped. Keys: Rva005222A0NoteCalls m_34/38/3C/40, Rva0020DEE0VirtualMode, Bfme5ThirtyThree, Rva0018F660 transformPoints A/R0/tmp/v (ZH Matrix3D-identical), GloriousCharge/SiegeDeploy ctor m_NNN, Rva001515C0Xfer, WeaponTemplate bfmeRangeBase, Rva00477E60Walk, Rva002BC870, HordeContainConstructor m_1e4.., BfmeConv1279, BfmeOptionsDispatchYV. Same dead ends.
# w48 lane d (duplicates/wrong_selected) notes
- r1: startMoveSound@AIInternalMoveToState (0x16E6C0): AIStates.cpp held ZH present-unmatched copy; removed body -> landed 907c71686. Pattern: ZH-ported TUs (AIStates.cpp etc.) keep 'present-unmatched' strong copies of matched symbols; delete body, leave comment.
- Push contention: pre-push takes ~1-2 min, loses race to others; loop `git push || git pull --rebase` many times (took ~50 min).
- Submodule inputs/reference/open-bfme-2 pointer moved upstream (aa505f3, object absent locally): worktree shows ' M'; used `git update-index --assume-unchanged inputs/reference/open-bfme-2` to let verification-cache pass.
- link_check on AIStates.cpp lists many other duplicates (AIAttack*State::update, xfer@Squad etc.) = more present-unmatched copies in same file.
- r1: AIStates.cpp ZH copies (59 duplicates incl. ctor/onEnter/update of AI*State): dead end, re_attempts shows dropping fails rows (AIStateMachine ctor 36/106 rows; reconstitute etc.). Don't retry.
- r1: PopulateReplayFileListbox (ReplayMenu.cpp:114 ZH copy): only blocker is uw_00c3318d/uw_00c3f63e funclet rows (parent= unproven; not in retail unwind map of Populate). Re-identify their real parent first. Same shape as AI::crc false-reject.
- r1: AI::crc (ai.cpp) recorded false-reject uw_00c04530; BridgeBehavior update is partial (not dup in same file) - skip.

## w41-i round 26 (claude-sonnet-5-5)
3 batches served, nothing landed. Keys: BattlePlanUpdateSetStatus clearCondition/setCondition param o ("obj" rejected as too generic), Small03hRefCopy Rva0094C* Box/Head/Tail (opaque), P6MemberVectorCopyConstructor m_at00.. (again), Small03hWordSwap Rva009CC2C0Box/v/a. Same dead ends.
## agent h round 21 (wave 48, claude-sonnet-5-5)
- 6 batches served (late session), submitted skips for 3, one name proposal rejected ("byteSwap32" for Rva009CC290Swap: address-derived names stay placeholders). Keys: RvaTreeBoundsAsciiStringLocale value/keyofvalue types (pair of AsciiString+2 pad ints, no real class), Rva003C7B60 Create_Render_Obj views, Small03hWordSwap (full 32-bit byte swap, rejected as placeholder), AIGroup m_unmodelled00, UpdateModuleModuleData_ctor_Thunk m_unknown20.., ParseAudioEventBlock Rva003B7740, U4Blend00609600 blend3, FreeLifeBody ctor m_unmodelled_*. Same dead ends. Note: worktree started mid-rebase on build/w48-notes.md; resolved by keeping both sections.

## w41-i round 27 (claude-sonnet-5-5)
3 batches served, all skipped. Keys: Recorder.cpp (GameLogic m_unreconstructed_00 stand-in, getReplayDir tmp / writeArgument arg ZH-identical), ShadowRva00459960 m_value3C, ElementPayloadFill003ACD30 m_at00/04/08/0C (opaque). Same dead ends.
## agent h round 22 (wave 48, claude-sonnet-5-5)
- 3 batches served, nothing landed. Keys: Rva008B7040Build (Apt stack builder), DamageModuleModuleDataCtorThunk m_unknown*, MemberVision002434D0 at### members, ShadowRva00459960 m_value3C, W3DLightDrawModuleData m_unmodelled_*, PathfinderFindSafePathBfme, Glo012F1028Sub bfmeFinish, MemberTurnAndGoal0024E310, BfmeConv2137/1916, calculateTerrainLOD freq64/time64/startTime64 and line2_d.cpp (verbatim ZH Line2D copy): ZH-identical names are rejected as "still a placeholder" (re-verified), so those can never land.

## w41-i round 28 (claude-sonnet-5-5)
3 batches served, all skipped. Keys: ScreenCrossFadeFilter::postRender vertex p/u/v/u1/v1 (ZH-identical already), Gen_0037A750 seed (opaque), EnragedBehaviorModuleData ctor thunk m_unmodelled_18/1C, RenderObjectDrawModuleInfo copy ctor m_name0..2/m_valueNN (opaque). Same dead ends.
## agent h round 23 (wave 48, claude-sonnet-5-5)
- 3 batches served, nothing submitted. Keys: Rva004155A0 NotifyArrays Primary/Secondary/Owner (Drawable.cpp listener arrays, no solid name), BfmeSeed37A750, BfmeConv1279, BannerCarrier/CivilianSpawn/BezierProjectile ModuleData ctor fields, PathfinderFindSafePathBfme, BfmeConv902, Q3IntrosortLoop, ScreenCrossFadeFilter postRender p/u/v. Same dead ends.
