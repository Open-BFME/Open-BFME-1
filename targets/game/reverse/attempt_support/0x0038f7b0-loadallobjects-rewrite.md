# 0x0038F7B0 GameLogic::loadAllObjects: full rewrite handoff (2026-11-04)

Bank: `targets/game/reverse/attempts/0x0038f7b0.cpp` (replaces the 493-byte placeholder bank).
Probe: 2320/2335 bytes, shape 0.941, 31 structural differences, 1795 non-relocation
byte differences (frame `sub esp,0xF8` now matches). Built as a scratch TU with local
declarations; callee names are NOT yet ledger-reconciled (probe masks relocations).
VC7.1 `/DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB`, STLport.

## Identity and ABI (BFME 1 evidence)

- `targets/game/reverse/ea_evidence.csv`: 0x0038F7B0 name `GameLogic::loadAllObjects`
  (chain+direct, strong), file GameLogic.cpp (wb1).
- `ret 0x10`, incoming ECX ignored; args: vector of (Object*, MapObject*) pairs
  (push_back ILT 0x0003A855 -> 0x0038EB40), `const KindOfType *exclude`,
  `const KindOfType *require`, `Bool dontCreate` (byte). Matches
  `identity_evidence/003916f0-kind-filter-abi.md`.

## Donor (structure only, not BFME 1 proof)

BFME 2 `Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp`
`GameLogic::loadAllObjects` at open-bfme-2 8b2b7696 has the same skeleton: three AI
tree templates (second/third null clears the first), multiplayer gate,
`isProp = kind bit; if (kind && fenceWidth == 0) isProp = TRUE`, prop/tree path with
`Matrix3D mtx(true)` + alignToTerrain/Rotate_Z, AssetList submit+clear every 20,
neutral-team `strncmp("Player_", ..., 7)` skip, newObject path with alignToTerrain.

## Body facts recovered from retail (all in the bank)

- `useTrees` starts TRUE and is reassigned (`!aiData+0xE8`) only inside the
  non-multiplayer block (multiplayer path jumps past the `sete`).
- Game mode 6 and mode 2 clear the multiplayer flag; then `aiData+0xD4 &&
  TheGameLODManager+0x16C4 <= 1 && treeA` resolves the three final overrides.
- Each map object: FirstUpdateSubsystem(0x0134FAA0)->slot5, Rva0090F050, Sleep(0)
  + TheGameEngine slot16 (+0x40); flags & 0x36 skip; second Sleep/service;
  handleNameChange; getThingTemplate (0x00087E80); template+0x485 skip; inline kind
  filters on template+0xC8; kind 6 (`byte +0xC8 & 0x40`) && !useTrees skip.
- AssetList local at frame 0x38 (set header/count/compare, pad 0, changed=TRUE);
  ThingTemplate::rva00144DC0(assets, &AssetLoadMode{0}); ++count == 20 ->
  Rva009EBAC0(&assets), bfmeGoAUC (AssetList clear); final Rva009EBAC0 then
  `_Rb_tree<Gen_t_00140950_k4>` dtor via ILT 0x00015D7A.
- Tree path: AI tree selection `b48b&&b48c ? A : !b48b&&b48c ? B : C`, scale
  from aiData+0xE4; placement via ILTs 0x000364AD (tree, gated by useTrees),
  0x000050C9 (kind 0x5E), 0x00037F83 (other). All three are called with
  ECX=TheTerrainLogic and four args (template, &pos, &mtx, scale), but the ledger
  names 0x001A7A90 and 0x001A34C0 as free `__stdcall` functions with other
  parameter types: their ABI/names need independent proof and pins before landing.
- Object path: team = ThePlayers(0x012ED748) ILT 0x0001BE82 (AsciiString by value,
  MapObject*); newObject(template, team, BitFlags<86>{0}, 0); mirror flag via
  getDrawable (slot +0x28) status |= 1; behaviour-module loop calling getCreate
  (+0xC interface slot 3) -> onBuildComplete (slot 1) with Sleep/service per
  module; Team setActive inline (+0x31/+0x32); pathfinder add; push_back.

## Measured levers

- STLport-style `(getWord(k) & maskBit(k)) != 0` for the kind filters: shape
  0.932 -> 0.938. Element-wise position copy (donor form) is worse (0.850).
- `Vector4 Row[3]` with `operator[]` returning `(&X)[i]` (WWMath layout) instead of
  `float Row[3][4]`: 0.938 -> 0.941, row 0 of the inlined Rotate_Z now matches.
- Inert: Rotate_Z operand orders (MSVC canonicalises), `volatile` global pointers,
  loop counter/iterator spellings for both loops.

## Remaining residue (next steps)

1. Global `this` loads (TheThingFactory/TheTerrainLogic) sit right before the call in
   retail (+0x23, +0x4A, +0x413, +0x89B, +0x8C3) but are hoisted in ours (scheduling).
2. Outer loop top is aligned in ours (`jmp; lea esp,[esp]`), the behaviour-module
   loop is aligned in retail (`lea ebx,[ebx]` at +0x55A): opposite loop chosen.
3. Rotate_Z rows 1-2 x87 shape; dead store of the raw angle to frame 0x88 at +0x289.
4. Port into game/GameEngine/Source/GameLogic/System/GameLogic.cpp (ZH-header TU);
   0x003916F0 needs this body visible in the same TU to go exact.
