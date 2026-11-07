# 0x0079DEE0 AptPalantir::renderRadarViewBox (423 B) — EXACT

Best candidate: `build/wf/0079dee0/best.cpp` (defines `?renderRadarViewBox@AptPalantir@@UAEXXZ`).
`python3 tools/probe.py build/wf/0079dee0/best.cpp '?renderRadarViewBox@AptPalantir@@UAEXXZ' 0x0079DEE0 --size 423`
-> `result EXACT (modulo relocation slots)`, 423/423, 11 relocs.
Compiler: `// cl: /DNDEBUG /MD /EHsc` (bank flags, unchanged). It is also EXACT with the AptPalantir sibling
flags `/DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc` (AptPalantirConstructor.cpp), see `v/C.cpp`.

## Baseline
Bank `targets/game/reverse/attempts/0x0079dee0.cpp` reproduced as logged: 423 B, 58 non-reloc diffs,
shape 0.978. The first difference is at +0x87, where the flag temporary is edx in retail and eax in the bank. The second is at
+0x126, where the UV temporary stores are scheduled differently. The rest of the loop has the ecx/edx roles swapped, and the final guard restore
uses ecx in retail and eax in the bank.

## Fix (callee visibility / types family)
The renderer is BFME's Render2DClass. The matched constructor places the Shader state at +0, the Texture
at +0x4C, CurrentBatch at +0x50 and IsDirty at +0x54. The bank open-coded the texture swap on raw pointers.
The fix models the texture as a handle with an inline guarded `operator=`, which does Add_Ref of the source, then
Release_Ref of the destination, then the store. It also adds an inline member

    void Set_Texture(const TexRef &t){ if(t.m_texture==m_texture4c.m_texture)return;
      m_texture4c=t; m_flags50=m_texture4c.m_texture?-1:0; }

The method then calls `renderer->Set_Texture(m_texture520)`, where `m_texture520` is a `TexRef`.
This change alone takes the bank from 58 diffs to EXACT. The register-allocation residue throughout the function was caused by the
temporaries of the open-coded swap. This is the shape of the BFME 2 donor
`Code/Libraries/Source/WWVegas/WW3D2/Render2DSentenceBuildTexturesBFME2.cpp` (45afcff3), which
BFME 1 already uses in `game/Libraries/Source/WWVegas/WW3D2/Render2DSentenceClass_Build_TexturesMethodThunk.cpp`.
The guard was also replaced by its real shape: `{int *m_ptr; int m_saved;}`, constructed as `(&renderer->m_state00, 1)`. With it the body stays EXACT. The
emitted guard COMDATs are retail-identical to their rows: `??0StateGuard0079DEE0@@QAE@PAHH@Z` matches 0x0079D070
(22 B) and `??1StateGuard0079DEE0@@QAE@XZ` matches 0x0079D090 (8 B). Both probes are EXACT. This confirms that the
uncalled 0x0079D070 and the funclet target 0x0079D090 are this guard's out-of-line copies.

## Trials
| family | change | result |
|---|---|---|
| (d) visibility/types | handle TexRef with inline operator= + inline Set_Texture (early return), flag from stored handle (`v/A.cpp`) | EXACT |
| (c) | same, but flag derived from argument `t.m_texture` (`v/A2.cpp`) | 84 diffs |
| (a) control flow | Set_Texture with `if(!=){...}` instead of early return (`v/A3.cpp`) | EXACT |
| (c) | real `{int*,int}` guard ctor `(int*,int)` (`v/B.cpp`, best) | EXACT |
| (e) | sibling flags /DWIN32 /D_WINDOWS (`v/C.cpp`) | EXACT |

Earlier disproven work, all from re_attempts.log: EH search; register rotation sweeps; typed region, copy, ctor and order
forms; signed or negated-bool flag; split flag declaration; reversed or direct field stores; Coord2D typing;
native Vector2; a raw-pointer texture setter taking const-ref; out-of-class guard; texture operator= on
raw fields (164-299 diffs). The earlier operator= trials failed because they lacked the inline Set_Texture member
with the flag read back from the stored handle.

## Landing notes (read-only checks; nothing landed)
a. `tools/ilt_oracle.py check '?renderRadarViewBox@AptPalantir@@UAEXXZ' 0x0079DEE0` gives CONTRADICTED
   (slots 46019:27490-27500). Every other spelling tested is also CONTRADICTED: `Render…`, `QAE`, `MAE`, `EAE`, `?rva0079dee0@AptPalantir`
   and `?d_0079dee0`. The landed sibling `?rva0079d3a0@AptPalantir@@UAEXXZ` is CONTRADICTED too. The ILT at
   0x000392D4 holds only `?j_000392d4@@YAXXZ` (a gen-thunk row in functions.csv). symbols.csv has only
   `?b_0079dee0@@YAXXZ` (a gen-thunk body pin) and no address-derived method pin. Either land the identity-proven
   `?renderRadarViewBox@AptPalantir@@UAEXXZ`, accepting that the ILT name is unproven, or use the sibling
   convention `?rva0079dee0@AptPalantir@@UAEXXZ` if the ILT guard refuses the first. Do not invent a pin.
b. Helper COMDATs the TU emits:
   - The guard ctor and dtor are retail-identical to 0x0079D070 and 0x0079D090. Those rows are currently
     `?apply@Rva0079D070Apply@@QAEPAV1@PAHH@Z` (Rva0079D070Apply.cpp) and `?run@Rva0079D090@@QAEXXZ`
     (R2SmallMemberOps.cpp). The copies have different symbols, so there is no link conflict. Re-homing those rows to this TU's
     guard is optional follow-up work.
   - The TU also emits inline COMDATs for `Set_Texture`, `TexRef::operator=`, `Add_Ref` and the `BfmeV1207` ctor.
     None of them has a ledger row. Retail has no Set_Texture copy near 0x0079D0xx.
   - `bfmeGo1207` (0x0079D470) and `Rva0079D180::compare` (0x0079D180) are external declarations whose names match ledger rows.
   - The callees `QuadrilateralInset0079D530::update` (0x0079D530) and `RenderBuffer0079DEE0::render`
     (0x00934940) have no symbol pin; both are still `?d_` gen-dump rows. They need independent identity/ABI
     proof and a pin (callees.py infers `__thiscall`, 0 stack args, void).
   - `Release_Ref` resolves to 0x009EB7A0. callees.py reports two ledger names there (TextureBaseClass and TextureClass).
c. Globals: `?TheDisplay@@3PAVDisplay@@A` at 0x012F1270 is recorded in data_rows.csv (row 498, Display.cpp).
   The other relocations are the EH handler and FuncInfo plus the call targets.
d. TU: put it in a new AptPalantir method TU under `game/GameEngine/Source/GameClient/GUI/`, following the per-method sibling
   files `AptPalantirRva0079D3A0.cpp` and `AptPalantirRva0079DC00.cpp`, for example `AptPalantirRenderRadarViewBoxMethod.cpp`.
   `AptPalantirRenderRadarViewBox.cpp` already holds the 0x00563C40 callback with a minimal class view. No visible
   helper from another TU is required.
