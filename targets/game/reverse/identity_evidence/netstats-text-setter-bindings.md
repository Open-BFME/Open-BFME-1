# Network auth readers: three bounded native text-setter bindings

## Scope and identity

Only `game/GameEngine/Source/GameNetwork/NetPacket_readRequestGameSpyStatsAuthKey.cpp`
changes. Existing reader identities, signatures, message types/storage, parsing,
allocation, `AsciiString(textBuffer)` expressions and lifetimes remain unchanged:

| Existing reader | RVA | Complete extent |
| --- | --- | --- |
| `NetPacket::readRequestGameSpyStatsAuthKeyMessage` | `0067EB80` | 187 B |
| `NetPacket::readGameSpyStatsAuthKeyMessage` | `0067EC70` | 251 B |

These are existing matched rows, not new recoveries. The census counts 435
non-padding bytes across their 438 B extents; neither count is new progress.
The change substitutes three obsolete undefined member names for three existing
implementations in `game/GameEngine/Source/GameNetwork/NetCommandMsg_text.cpp`:

| Caller's old formal argument | Existing provider | Original ILT | Body/extent | Receiver field |
| --- | --- | --- | --- | --- |
| request `setText1C(AsciiString)` | request `setText1C(StringBase<char>)` | `0000AA65` | `00675A20`, 75 B | `+1C` |
| reply `setText1C(AsciiString)` | reply `setText1C(StringBase<char>)` | `0002F423` | `00675C50`, 75 B | `+1C` |
| reply `setText20(AsciiString)` | reply `setText20(StringBase<char>)` | `0001711B` | `00675CE0`, 75 B | `+20` |

Names are existing ledger/provider identities, not new original-EA naming or
access-level claims. In particular the two distinct `+1C` bodies are NOT folded
or assigned a shared identity merely because their instructions are similar.
Both message constructors are independently verified, complete 45/48 B bodies
at `006759B0`/`00675BE0`, selected by their original reader routes
`00028F6A`/`00042799`; message allocations remain `20`/`24` hex bytes.

## Why a strictly bounded ABI view

`inputs/reference/shims/stringinline/StringInline.h` intentionally uses private
base construction and inline forwarding to preserve the argument-slot EH/ESP
schedule. Its `StringBase` constructors/destructor and `AsciiString` inheritance
are private. Directly changing the formal parameter to the private base would
not be a legal call from this reader and would abandon that proven shape.

The supervisor authorized ONE isolated experiment at exactly these three sites,
then required independent review before publication. The source retains the
existing `AsciiString` construction and nominal call argument type, using exact
external native COFF references through fully initialized local single-word
member-pointer unions. Negative-array checks require four-byte code pointers,
both existing string representations, each member pointer and each union.
These assertions are necessary admission checks, NOT lifetime proof.
No header/provider change, friend/access expansion, new helper/function/class,
inheritance change, macro, alias/pin or verifier exemption is introduced. This
is not authorization or evidence for a generalized private-access bridge.

## Positive ABI and lifetime evidence

The strict full-reader comparison is unmasked with no unresolved references.
All three calls retain their original E8 ILTs above. Immediately before each:

1. `push ecx` reserves the one-word argument object; the parser's offset update
   and null termination are unchanged.
2. `lea edx,[esp+14h]` selects the existing text buffer.
3. `mov [esp+10h],esp` occurs BEFORE `mov ecx,esp`, preserving the intentional
   forwarding-constructor schedule. The buffer pointer is pushed and the
   actual 72 B char constructor `00888BC0` constructs directly at that ESP.
   Its two complete normal exits are RET4. No copy-constructor call is added.
4. `mov ecx,ebp` restores the original message receiver; then the native setter
   consumes that same constructed one-word argument.

All three full 75 B setters have the same owned-parameter protocol:

- After the three-word EH record, `lea eax,[esp+10h]` addresses entryESP+4,
  the argument OBJECT, not an extra pointer/copy. Receiver adjustment is `+1C`
  or `+20`, then `StringBase<char>::set` at `00887C90` receives its address.
- On normal completion `lea ecx,[esp+10h]` addresses the SAME argument object;
  state becomes -1 before `00887940` releases its buffer, then RET4 consumes
  the argument word. The caller performs no additional argument destruction.
- Native FuncInfo has one state, `0 -> -1`, no catch map. Its complete 8 B
  exceptional action is `lea ecx,[ebp+4]; jmp 0000D828`. The physical chain is
  `0000D828 -> 0005EE90 -> 00887940`: one-word argument cleanup on exception.

The actual full 134 B release body reads the pointer at receiver+0, decrements
that buffer's DWORD reference count, frees it at zero and clears receiver+0;
its complete exit is RET0. The actual full 135 B set body, 72 B from-char
constructor and 121 B copy constructor are independently strict/unmasked, not
assumed from mangling or equal sizes. The latter is NOT newly called here.
`operator new`/`delete` at `00881F30`/`00881EB0` are also complete 17/21 B
verified providers.

**Nominal destructor distinction is preserved.** The existing provider's COFF
unwind action references its inline private `StringBase<char>` destructor
COMDAT, a bare jump to `00887940`; the separate base-destructor retail body at
`0005E490` is also a bare jump there. Native exceptional cleanup instead takes
the physical `D828 -> 5EE90` chain above. These are NOT claimed to be the same
identity, same route, an ICF fold or proof that the original EA types were
aliases. Their complete one-word release protocols establish the bounded
parameter-ownership equivalence; no destructor/provider/pin is rewritten.

## Caller EH metadata, not just main bodies

Both readers' native FuncInfo maps have exactly one `0 -> -1` state and no
catches. The complete 14 B action loads the allocation from `[ebp-110h]`,
pushes it, calls actual `operator delete` at `00881EB0`, pops its argument and
returns. It guards failed MESSAGE construction only; there is no caller
string-argument cleanup. The emitted COFF maps/actions independently decode to
this same state/action contract, not an inferred temporary ownership rule.

| Reader | Native action | Native handler | Native FuncInfo |
| --- | --- | --- | --- |
| request | `00C45D70` | `00C45D7E` | `00E357E0` |
| reply | `00C45D90` | `00C45D9E` | `00E35808` |

Before/after comparison covers **ALL eleven non-debug consumer COFF sections**,
not only row bytes: directives, three existing inline bodies, both reader
bodies, both `.text$x` sections (14 B action + 10 B handler each), both 36 B
`.xdata$x` unwind/FuncInfo records and `.sxdata` SafeSEH identities. Runtime
bytes and every relocation are identical after only the three intended
external setter-name substitutions. Defined static labels are compared by
section/offset rather than compiler-generated label spelling; SafeSEH symbol
indices are resolved to the same defined identities. Debug records are excluded,
not runtime EH records. Normalized runtime SHA256:
`d3bcbc2e963e90c1e555aa4060a5c02cca968afab21a153a6cbdd22e19f43138`.
No added body/data/helper/cleanup, changed exception home, hidden copy or new
ownership state exists. All five external definitions are unchanged; exactly
three undefined references change and no others.

## Reference-source pass

Read-only BFME 2 revision `76f0baefa6f285d54bc1ca922397674312a5913f` reviewed:

- `Code/GameEngine/Source/GameNetwork/native_connection_timing_ConnectionManager_getPlayerName.cpp`
- `Code/GameEngine/Source/GameNetwork/BFMEConnectionManager_sendGameSpyStatsAuthKey.cpp`
- `Code/GameEngine/Source/GameNetwork/ConnectionManager_processGameSpyStatsAuthKey_Rva004CFE24.cpp`
- `docs/recipes.md`, stack-slot packing section, including argument-slot class
  construction and negative flag/lifetime experiments.

Donor observations support only a lead for the two narrow message fields.
Its folded request/reply setter at `004D65F9`, unrelated `CDDrive`/field-view
casts and layouts are NOT transferred: BFME 1 has distinct native identities
and no ICF. No corresponding donor reader implementation was found in the
narrow reviewed network paths. The shallow donor history exposes the snapshot
commit only for these paths, so older source-specific history is unavailable,
not silently claimed reviewed. No donor source/build input/gitlink is changed.
This repair uses BFME 1's existing providers and independent native evidence,
not a donor implementation/name/layout import.

## Validation and current limits

All actual builds use MSVC 7.1 with the existing root `/DNDEBUG /MD /EHsc`
context and approved private WoW64 Wine prefix, `WINEARCH=win64`, `BUILD_POOL=2`,
`WINEDEBUG=-all`, empty DISPLAY/WAYLAND_DISPLAY. No compiler variant is added.

Normal before/after unified verification over the reader, setter, StringBase,
AsciiString destructor, physical destructor thunk and memory-operator TUs:
**218/218 functions, 361 DIR32 references, 6 literals + 26 empty-string refs**;
zero skipped/unverified refs and zero baselined body findings.
`find_declared_unmatched.py` reports all defined functions already matched.

Before scoped preview: **0/6 clean**, 237.2 s, 2 UNKNOWN / 4 independent-debt
verdicts. After: **0/6 clean**, 230.7 s, 3 UNKNOWN / 3 independent-debt verdicts.
All six selection sets have stale census evidence; 22,758 cold/changed ledger
objects cannot be read here. Historical LINKED **989 -> 989** is unchanged and
NOT current confirmed coverage. Exactly three old unresolved diagnostics are
removed; every selected duplicate/COMDAT/other diagnostic remains and none is
added. No confirmed linked-byte gain or closure is claimed. Other network,
string ownership/COMDAT and global allocator debt remains outside this repair.

Private evidence under `build/sol12h-bindings/`:
`netstats-{before-full-build,after-build,link-before,link-after}.log`,
`netstats-{routes,runtime-coff,object-facts,link-delta,native-eh,native-decode}.txt`
(or `.log` for routes/runtime-coff), `netstats-runtime-coff.json`,
`check_netstats_routes.py`, `check_netstats_runtime_coff.py`,
`netstats-before.{cpp,obj}`, `netstats-sources.txt`, claim log and donor search.
An initial private preview-count assertion counted both UNKNOWN headlines and
selection-detail lines; corrected to count the latter separately, with its
failure preserved in `netstats-initial-preview-count-failure.txt`. It was not a
source/build/ABI failure or verifier relaxation.
