# 0x00693B90 audio cache lookup (525 B): EXACT

Session wf 2026-11-06, model claude-opus-5-5. MSVC 7.1 (cl 13.10). The cl line is unchanged
from the bank and the host TU:
`/O2 /Ob2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB` plus STLport include paths.
The host TU is `game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioCacheReadAudioFile00694230.cpp`.

Best candidate: the landed TU `game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioCacheReadAudioFile00694230.cpp`. Probe reports
`result EXACT (modulo relocation slots)` at 525/525 B for
`?rva00693B90@Rva00694710AudioWorker@@QAE?AVRva006910F0Handle@@ABVAsciiString@@H@Z`.
The same TU is also EXACT for 0x00694230 (654 B), 0x006925F0 (45 B) and 0x006915E0 (25 B).

## Starting point

- The bank (`targets/game/reverse/attempts/0x00693b90.cpp`) still reproduces as logged:
  9 non-relocation bytes. The `file` and `handle` slots are swapped, and the epilogue order is wrong.
- A same-day scratch candidate (`best_clean.cpp`) had already fixed the slot swap with natural
  code. It uses a single `file` local, and `push_back` has a visible `__declspec(noinline)`
  body, so the compiler can prove the call leaves `file` unchanged. Its mutex flag is not
  volatile; the destructor clears it instead. Only the epilogue remained, 4 bytes:
  retail `pop ebp; mov fs:[0],ecx; pop ebx`, ours `pop ebp; pop ebx; mov fs:[0],ecx`.

## Fix for the epilogue (new)

The fix uses a list view (`Rva00693B90List`) shaped like STLport's list:
- an `iterator` with a user-declared copy constructor, as STLport's `_List_iterator` has;
- `end()`, plus `insert(iterator, const T&)` and `erase(iterator)`, which take the iterator by
  value. These three are `__forceinline` because at this function's size VC7.1 refuses to
  auto-inline them (`itc_ins`: 554 B);
- `push_back(v) { insert(end(), v); }` marked `__declspec(noinline)`. Its emitted COMDAT matches
  retail 0x006925F0 byte for byte.

The hit path does `m_lists[old].erase(iterator(n)); m_lists[level].insert(m_lists[level].end(), file);`.
The new-record path calls `push_back(file)`, which retail calls out of line through ILT 0x0001F3A2.

**Measured.** Passing a by-value class object with a user-declared copy constructor into an
inlined function flips the epilogue tie-break to retail's order. The instruction stream is
otherwise identical. Isolated in the FxClone0042CDF0 testbed (scratch harness, not kept):

| Iterator passed by value | Epilogue order |
|---|---|
| plain struct | B (ours) |
| struct with a base class | B (ours) |
| aggregate | B (ours) |
| plain struct with a copy constructor | A (retail) |
| based struct with a copy constructor | A (retail) |

The real STLport `push_back` gives A. A hand-inlined relink gives B with identical code
bytes (scratch disassemblies, not kept).

**Hypothesis.** The unscheduled epilogue is `mov ecx; mov fs; pop×4`. The scheduler sinks the
`fs` store, and two orders look equally good to it. The copy-constructed temporary changes the
hidden IR ordering that breaks that tie. This cause is not proven.

## Ruled out this session (all keep the epilogue as B)

- Ablating each part of the body: the loop, the empty-name return, the failed-set test, the hit
  path, update, push_back, the map store.
- Minimal skeletons with or without the mutex.
- Extra frame locals of 1 to 16 dwords.
- `std::list` push_back cast in the hit path: not inlined, 536 B.
- By-value iterator without a copy constructor: forced inline (`itf_*`) or not (`it_*`).

Natural loop forms with the new iterator type all rotate the scan loop (529-568 B): a `findIt`
template, `for` over iterators, `while` with `!=`, and a raw-node `for`. The documented
foldable-first-term lever (`bool searching = true; while (searching && n != head)`) stays.
Retail statistics: the two epilogue orders are about 50/50 across retail (A 87, B 109 with the
same register set), and they do not correlate with:
- frame size;
- the epilogue address modulo 16;
- prologue contiguity.

The prior handoff `targets/game/reverse/attempt_support/0x00693b90-cache-lookup.md` lists
earlier ruled-out families. The same-day `trials.log` adds about 150 more.

## Landing notes (read-only checks)

**(a) ILT oracle.**
- `ilt_oracle.py check` on the target name prints CONTRADICTED (p_false 1.1e-3). This is
  expected, because the pinned name is the address-derived placeholder, not EA's.
- `symbols.csv` already pins
  `?rva00693B90@Rva00694710AudioWorker@@QAE?AVRva006910F0Handle@@ABVAsciiString@@H@Z` at
  0x00693B90, and ILT 0x0003214B routes to it. Keep that name: the caller
  `Rva00694130AudioWorker.cpp` uses it.
- The other names at this address are `?b_00693b90@@YAXXZ` (a gen-thunk) and
  `?d_00693b90` (the gen_asm row to replace with `--replace-rva`).

**(b) Helpers the TU emits.**
- `?push_back@Rva00693B90List@@QAEXABQAVGen0002857E@@@Z` matches retail 0x006925F0 (45 B), so it
  is retail-identical. That address's row is `?dup_006925f0@@YAXXZ`, a gen-alias with object
  symbol ShellMenuScheme `list::push_back`. Either re-home that row to this symbol after
  checking identity, or rename the helper to the pinned symbol. Otherwise the staged-source
  check refuses an unledgered definition. Note that ILT oracle also says CONTRADICTED for the
  view-class name.
- `??1ScopedMutex@@QAE@XZ` matches retail 0x006915E0 (25 B), so it is retail-identical. The
  body now uses the TU's existing `ScopedMutex` (`typedef Rva006915E0`) with a new inline
  `ScopedMutex(void *)` constructor, so no second mutex type is added. 0x006915E0 is ledgered
  as `?release@Rva006915E0@@QAEXXZ` in `MilesAudioManagerConstructor.cpp`. Here it is the
  unwind destructor, so its identity or name may need a check: link-only, bytes are fine.
- `Rva00694230` in the same TU is still EXACT.

**(c) Globals.** The body references no data globals. It uses only the
WaitForSingleObject/ReleaseMutex IAT slots (0x01358F64, 0x01358ECC) and its own EH FuncInfo.
Every callee is ledgered:
- 0x006BA2D0, 0x006BA130, 0x0038C0E0, 0x00693880, 0x006931A0, 0x00693B00;
- the handle functions at 0x006910E0, 0x006910F0, 0x00691110 and 0x00691130;
- `_M_allocate`, `_M_deallocate` and `operator new`.

**(d) Target TU.** Use `MilesAudioCacheReadAudioFile00694230.cpp`, the TU the bank extends.
The final.cpp prefix equals that TU apart from the include path spelling
(`../../../Libraries/...`) and the added constructor. Then make the forwarder in
`Rva00694130AudioWorker.cpp` declaration-only, as the earlier handoff says. Run a full-TU
build to confirm 0x00694230 and the other rows are unchanged.

## Landed (2026-11-07)

- `?rva00693B90@...` was landed in the host TU with `--replace-rva` over the gen dump.
- The helper's 0x006925F0 row was re-homed from a ShellMenuScheme gen-alias to
  `?push_back@Rva006925F0List@@...`, the view class renamed after its own address. Evidence:
  `identity_evidence/0x006925f0-audio-cache-list-push-back.md`.
- The forwarder in `Rva00694130AudioWorker.cpp` is now declaration-only, and its two unwind
  funclet `$L` pins were repointed with `eh_state_pins.py --fix`.
