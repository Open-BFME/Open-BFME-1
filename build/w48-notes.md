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
