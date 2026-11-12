# 0x0049FC90 ControlBar::setControlBarSchemeByPlayerTemplate (818 B) - 6-byte scratch residue

2026-11-12, model=claude-opus-5-5, t=75min. Bank: `targets/game/reverse/attempts/0x0049fc90.cpp`.

## Identity and boundary (BFME 1 evidence)

- `?setControlBarSchemeByPlayerTemplate@ControlBar@@QAEXPBVPlayerTemplate@@@Z` is
  **CONFIRMED** by `ilt_oracle` at ILT slot 21433 (thunk 0x0001B2A2 -> 0x0049FC90, an
  anchor slot). The earlier CONTRADICTED reading came from a bug in the `ilt_oracle.py
  check` CLI, not from the window file: `main()` subtracts the image base from any
  RVA >= 0x401000 whose `rva - 0x400000` is also a thunk target, so the CLI tested
  0x0009FC90 (slot 35791) instead. `Oracle.check()` called directly, `audit` and the
  landing guards are not affected. Other CLI checks this bug falsified in the lift
  list: 0x004AEE00 and 0x00666300 (both still CONTRADICTED under the API).
- Nothing calls it (no E8/E9 to either ILT thunk, no DIR32 to the body or thunks):
  linked but unreferenced, like Zero Hour where only the Player overload is used.
- Extent 818 B: `ret 4` at +0x32F, int3 after. Zero Hour twin in
  `GeneralsMD/.../ControlBar.cpp`; BFME 2 `Code/.../ControlBar.cpp` (76f0baefa6) has the
  same donor body at its own 0x0031C5C8 without the BFME 1 additions below.
- The `refuted` row at this RVA retired an `?update@ControlBar@@` alias, not this name;
  it is why `lift_lane.py` lists the lift as retired.

## The near miss

Edit the present-unmatched Zero Hour copy that already sits in
`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp` (the bank holds the
exact function). Three BFME adaptations, all read off retail:
`m_isObserverCommandBar` at this+0x270 (ControlBar_reset.cpp's view; the ZH header has
+0x2CC), game mode from the BFME GameLogic view (+0x10C) and `isMultiPlayer` as the
GameInfo virtual at +0x2C, and the trailing `::hidePurchaseScience()` free function
(ILT 0x0003576F, called this-less as in ControlBarPurchaseScience.cpp), plus
`(ControlBarContext)9` for the observer context and the manager call's `FALSE`.
The compiler inlines `switchToContext(9, NULL)` from the TU's own matched definition,
exactly as retail expands it (including showRallyPoint's null path).

Result: 818/818, shape 1.000, 6 non-reloc bytes at +0x179..+0x18F. Retail:
`mov ecx,[esi+0x5c]` (oldSelected) / `mov eax,[chat]` / `test eax` / `mov [cache],ecx`;
ours swaps EAX/ECX. This is the same CAA-vs-ACA scratch phase residue the 0x0049F8B0
(setControlBarSchemeByPlayer) bank closed after ~150 variants. Unlike 0x0049F8B0, the
callee-saved choice (pt=EBP, buttonPlaceBeacon=EBX) is already exact here, and
switchToContext's matched out-of-line body gets CAA only thanks to its
`BfmeContextSwitchSelectionState {chat; oldSelected}` struct (plain locals: 6 diffs there
too, measured).

## Ruled out (all 818 B / 6 diffs unless noted)

- `rotation_sweep.py` on the auto-inline form (19 toggles) and on a hand-expanded
  observer arm (19 toggles): no change.
- Hand expansion of switchToContext(9, NULL) instead of inlining: identical 6 bytes.
  On it: the selection-state struct in both member orders, a 3-field struct, a
  `void *[2]` array, a union, plain locals, typed chat pointer, chat via inline
  predicate, inverted if/else, goto join, `NULL` vs 0 store; receiver locals for the
  overlay sink, InGameUI and transition.
- Store hoisted before the chat test (817 B / 286), chat local first (13), cache stored
  straight from the member (12, old lands in ECX but the store is scheduled early).
- Upstream receiver/argument copies: TheWindowManager (each of the three calls), the
  observer key, the found template, the scheme manager, TheNameKeyGenerator: 6;
  ThePlayerTemplateStore local: 802 B.
- switchToContext-level respellings (keep 0x0049E780 exact): typed chat member,
  `draw` vs `incomingDraw`, `Drawable *const`: 6. Swapping the struct's assignment
  order breaks both bodies (13 / 9).

- `__fastcall` dummy-EDX adapter (the 0x0020DF90 phase lever) on the overlay
  `slot04` call: 820 B / 305; on the transition call: 822 B / 340 (EDX setup bytes).
- The bank is a standalone private view (from the 0x0049F8B0 bank's declarations,
  compiled `/DNDEBUG /MD /EHsc`); it gives the identical 6 bytes, so it is a fast
  test bed. The in-TU form is the one to land.

## In-TU recipe (the landing form)

Replace the present-unmatched body in ControlBar.cpp with the Zero Hour text plus:
`m_controlBarSchemeManager->setControlBarSchemeByPlayerTemplate(pt, FALSE)`;
`BfmeSchemeObserverView { char pad[0x270]; Bool isObserverCommandBar; }` for the flag;
`switchToContext((ControlBarContext)9, NULL)` in the observer arm (no DEBUG_LOG);
`BFME_CONTEXT_GAME_LOGIC->mode` for both game-mode reads;
`((BfmeSchemeGameInfoView *)TheGameInfo)->isMultiPlayer()` with eleven pure-virtual
slots before it; keep `switchControlBarStage(CONTROL_BAR_STAGE_DEFAULT)` (inlines to
retail's recorder test plus setDefaultControlBarConfig); end with
`::hidePurchaseScience()` after a file-scope `void hidePurchaseScience( void );`.

## Next

Not a spelling problem inside this function. Untested: a lever that changes
switchToContext's IR without changing its out-of-line bytes. If one fixes this body,
try it on 0x0049F8B0 too (same residue).
