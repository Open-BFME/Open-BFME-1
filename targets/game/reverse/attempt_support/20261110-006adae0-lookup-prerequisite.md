# 0x006ADAE0 `?helper@Rva006AE610@@AAEXHPAX@Z` (458 B): EXACT in a TU that also holds the visible callee bodies

> `build/wf/006adae0/` paths below are untracked scratch and are not kept. The banked source is `targets/game/reverse/attempts/0x006adae0.cpp`.

Best candidate: `build/wf/006adae0/best.cpp`
(`// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB`, `// stlport`, the bank's flags unchanged).
`probe.py best.cpp '?helper@Rva006AE610@@AAEXHPAX@Z' 0x006ADAE0 --size 458` prints `result EXACT (modulo relocation slots)`.

## Root cause of the old 7-byte residue (+0x17A)

Retail loads the by-value erase iterator (`mov ecx,[esp+0x2c]`) **before** the x87
`fstp [edi+0x28]` (`ref.ptr->value28 = (float)clock->value3c`), and passes the
iterator's own slot as erase's sret temp. Ours loaded it after the fstp.

* Diagnostic e3: when the float goes to a global rather than through `ref.ptr`,
  the bank emits retail's exact order. So the problem is aliasing. In the bank,
  `it` is treated as escaped, so the indirect store pins the load of `it` after it.
* Retail's `it` therefore does not escape, even though it is the sret slot of
  the 0x0069D620 lookup and of erase. VC7.1 /O2 does this only when it sees
  every body that receives `&it` in the TU, and it measurably needs both bodies:
  * a visible lookup body plus native `streams.erase(it)` (visible STLport COMDAT): EXACT (k1, k5, k6, m1, best).
  * a visible lookup plus the erase through the opaque ILT union with `&it` as output: 7 diffs (n1, n2).
  * a visible lookup plus the opaque union erase returning by value: 9 diffs (n3).
  * a declared-only lookup plus native erase: 7 diffs, with sret in the `extra` slot (b1, v6, d*, f*).
  * Defining the lookup after the helper also works (k5), so definition order does not matter.
  * The lookup body's own codegen does not matter (ga..gg, r1..r3 all keep the
    helper EXACT) unless it is small enough to be inlined (k4: 439 B).
* The same mechanism appears in MilesAudioManagerStopChain.cpp's header note
  ("VC7.1 only does that when every body that receives the address is visible here").

## Ruled out this session (each probed)
- Lookup through a member-pointer union that returns by value (v1-v3, a1-a6, c3, i1-i3): 464 B / 205 diffs. The result is read through EAX and copied to a new slot.
- `it = streams.erase(it)` in any form (v5, v7, b2, k2): 464 B / 55 diffs, or 9 diffs.
- `erase(it++)` (c1, c2): adds an EH state, 476 B.
- An unused `next = erase(it)` (d1-d3), and a `victim` copy at three points (h1-h3): 7 / 22 / 35 diffs, or 478 B.
- A forceinline wrapper that takes the iterator by value (g1, g2): VC7.1 does not inline it because it holds a ThingRef EH local.
- Flags: `/Oa` gives 471 B; `/Ow` leaves the same 7 diffs. No sibling uses them, so they are not justified anyway.

## Landing notes (read-only checks; nothing landed)
a. `ilt_oracle check '?helper@Rva006AE610@@AAEXHPAX@Z' 0x006ADAE0` reports CONTRADICTED.
   * The name is a placeholder (`Rva006AE610`), so `ilt_guard` exempts it.
   * It is already pinned at ILT 0x00021C1F in symbols.csv, and the matched
     setIfGreater calls it through `j_00021c1f`. Keep this name.
   * `?bfmeSetPG@BfmeThingPG@@QAEXHPAX@Z` is pinned at the same ILT and is also contradicted.
b. COMDAT and helper copies the TU emits:
   * `deque<ThingRef>::_M_push_back_aux_v` against 0x006A7DF0: EXACT, and its
     name equals the ledger row (ThingRefDequePushBackAux.cpp). It is a
     retail-identical copy.
   * `?erase@?$list@VThingRef@@V?$allocator@VThingRef@@@_STL@@@_STL@@QAE?AU?$_List_iterator@VThingRef@@U?$_Nonconst_traits@VThingRef@@@_STL@@@2@U32@@Z`
     against 0x0069DBE0 (73 B): EXACT. The ledger row there is the stand-in
     `?erase_Open269DBE0@@YG?AVListIterator@@PAVListNode@@@Z`.
     * Re-home that row to the native STLport name
       (`add_match --replace-rva 0x0069DBE0`, home TU Rva0069DBE0ListErase.cpp or this TU).
     * Otherwise the helper's call names a symbol the ledger lacks.
   * The lookup `?getSlot@Rva006AE610@@QAE?AU?$_List_iterator@...@_STL@@HH@Z`
     against 0x0069D620 (285 B) is still 13 diffs.
     * The residue is unchanged from the banked `getSlot@Rva0069F740Owner`
       attempt: swapped scratch registers in the two release tails, so the
       skip-path cross-jump lands in the no-match tail at +0x5C.
     * Today the ledger holds 0x0069D620 only as gen-dump `?d_0069d620@@YAXXZ`.
   * **Landing is blocked on 0x0069D620.** The helper needs that body defined in
     its TU. With a `present-unmatched` copy, the link would contain a non-retail
     lookup body, and the helper's call would bind to it.
     * Next step: finish the 13 diffs of 0x0069D620 inside this TU context, or
       land it first, then add the helper beside it.
     * Callers elsewhere (Rva0069F740Check.cpp, MilesAudioManagerGetMusicTrackName.cpp,
       IndexedAudioEvent006B0210.cpp, BfmeConv2100.cpp) keep using ILT pin
       `j_0001815b`. The pin must route to whatever name lands at 0x0069D620.
c. Globals: the body references none by address.
   * Its only references are the IAT imports InterlockedIncrement,
     InterlockedDecrement and AIL_pause_stream, and the TU-local EH handler
     (retail eh_00c48628).
   * Run `eh_state_pins.py` for the `$L` labels at landing.
d. Home TU: put it beside the 0x0069D620 lookup. Both are MilesAudioManager
   bodies; retail's MilesAudioManager.cpp is one TU.
   * Suggested: a game/GameEngineDevice/Source/MilesAudioDevice/ unit that
     holds getSlot plus helper, using the `ThingRef`/`RefCountedThing` class
     names. These make the push_back_aux COMDAT name equal its ledger row.
   * Do not put it in MilesAudioManagerStopChain.cpp: its `PlayingAudioRef`
     model would rename the deque/list COMDATs.

Trial sources: build/wf/006adae0/{v*,a*,b*,c*,d*,e*,f*,g*,h*,i*,j*,k*,m1,n*,r*,t*}.cpp
(generators gen.py, genget.py, genget2.py).
