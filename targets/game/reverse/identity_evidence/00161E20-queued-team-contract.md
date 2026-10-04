# AIPlayer::checkQueuedTeams: banked callable and nested-layout evidence

2026-10-04; RVA `0x00161E20`, 697 bytes. **Partial evidence only.** This
change adds no production body, pin, header, matched row or LINKED gain.
The current-input MSVC 7.1 replay still differs at exactly byte `+0x239`.

## Retained source and reproducible result

- Preferred bank remains `../attempts/0x00161e20.cpp`, score **0.9986**, SHA256
  `9034003c1418f2e4f21a7cf5e942ac6c9f5e9e78d0358e46f1f48d830c5e0d50`.
- The structurally corrected alternative is
  [attempt history](../attempt_history/0x00161e20/b48dbfdd19e58fb31ddce8208546a682e25b441b5ff1bd5d2cbd8d8ceeaaeb72.json).
  `re_log.py record ... partial --stash ... --score 0.9986` measured both
  candidates at 0.9986, archived the alternative and preserved the preferred
  bytes/date. The archive's `source` contains the complete candidate, with
  only bank metadata refreshed from the previously reviewed source.
- [Replay evidence](00161E20-queued-team-contract.json) records the baseline,
  compiler inputs, native witnesses, call endpoints and historical MCP reads.
  The replay used unchanged source SHA256
  `683059ad09170533fadfe9571931640b5a11a87000509fa229ac818cecfc081e`.
  Its complete 697-byte COFF body and all 16 relocation records equal the
  reviewed nested-template object; all 33 named code/data/EH symbol records
  reproduce that object. No additional source-shape variant was tried.

To replay, extract the archive's `source` into a file under untracked `build/`
and run `python3 tools/probe.py <file> '?checkQueuedTeams@AIPlayer@@MAEXXZ'
0x00161E20 --size 697` with the repository MSVC 7.1 environment. Expected:
697/697 bytes, 16 relocations, one differing non-relocation byte at +569.
A probe exit of zero is diagnostic success, **not** byte-match acceptance.

Identity is independently anchored by AIPlayer vtable VA`010968B0` slot 17:
its entry at VA`010968F4` points to ILT VA`0041E27C`, whose `E9 9F 3B 14 00`
routes to this body. Further corroboration comes from the Zero Hour
`GeneralsMD/.../GameLogic/AI/AIPlayer.cpp` twin and the three distinct inlined
queue predicates documented in
[the predicate evidence](0x00160f80-team-in-queue-build-predicates.md).
The native `ret` at +0x2B8 proves the retained extent.

## Narrow string and actual output class

Addresses here are RVAs unless prefixed VA. Pinned PE SHA256:
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`,
image base `0x00400000`.

- ScriptEngine constructor `00347E90` installs primary vptr VA`010E7A30`.
  Slot 25 (+0x64) routes ILT `000086E8` to `003490C0` (ret 12); slot 53
  (+0xD4) routes `00039347` to `0034C7A0` (ret 12); slot 52 (+0xD0)
  routes `00045728` to `0034C710` (ret 8).
- Slots 25/53 latch their first input through `00339DA0`; its saved/current
  values use exported `StringBase<char>::set` at `00887C90`. Latch cleanup
  `00339E20` restores with the same set and releases via `00887940`.
- Slot 53 forwards its second/third inputs through slot 52. The latter copies
  a narrow string via `00887B60` and calls lookup `0033C450`. That lookup
  writes its successful output through narrow set `00887C90` at +0x66 and
  cleans narrow locals via `00887940`. Output is independently narrow.
- Native caller EH handler VA`01005438` references FuncInfo VA`011F3970`,
  maxState 1, unwind map VA`011F3968`. Its cleanup VA`01005430` is
  `lea ecx,[ebp-0x34]; jmp VA0040D828`. The PE exports that ILT as
  `??1AsciiString@@QAE@XZ`, routing to `0005EE90`, then narrow release.
  This proves the local is **AsciiString**, not merely an unknown narrow
  wrapper. The canonical `ascii_string.h` reproduces the same cleanup graph.

Thus the old bank's UnicodeString labels are unsupported. Existing pointer
argument forms are retained: native address ABI alone does not establish
pointer-versus-reference source syntax or the original virtual method names.
The production ScriptEngine header reconciliation is still future work.

## Actual embedded TeamTemplateInfo

`TeamPrototype` constructor `000F3E40` saves the original receiver in ESI at
`000F3E58`, then passes `ESI+0x12C` at `000F3ED9` through ILT `000498FF` to
`TeamTemplateInfo` constructor `000EFEB0`. No intervening instruction changes
ESI. The latter installs a vptr at member +0, and witnesses:

| Relative field | Native instruction | Complete-object offset |
| --- | --- | --- |
| initialIdleFrames +0x78 | `000F06C1: mov [ebp+78],edx` | 0x1A4 |
| productionCondition +0xBC | `000EFF23`, `000F0834` | 0x1E8 |
| executeActions +0xC0 | `000F0869: mov [ebp+C0],al` | 0x1EC |

The banked alternative uses the constructor's witnessed polymorphic base,
member extent 0x144, member start 0x12C, and compile-time offset assertions.
The name stays at prototype +0x10. Sources corroborating this layout are
`game/GameEngine/Source/Common/RTS/TeamPrototypeConstructor.cpp`,
`TeamPrototypeDestructor.cpp`, `TeamTemplateInfoConstructor.cpp`, and
[constructor evidence](000EFEB0-team-template-constructor.md).
The sibling build-specific-team view at +0x130 is the real member's **data
start after its four-byte vptr**; its compensated offsets do not disprove +0x12C.

The emitted non-const inline getter returns `this+0x12C`. This does not rename
opaque native accessor `000EC420`, nor validate the distinct older const
`getTemplateInfo` row at `003BCD70`, whose bytes return `this+0x68`.

## Exact remaining limit

Current `callees.py 0x00161E20 697` reports five distinct named endpoints.
`build.compile_function` resolves all seven REL32 sites to their actual
native targets with no unresolved names. The JSON separately records all
nine native DIR32 operands; merely masking those slots would not prove them.

At +0x238 native encodes `8B D1` (mov edx,ecx), candidate `8B D0`
(mov edx,eax). In both bodies, `mov eax,ecx` at +0x230 dominates that copy;
only a comparison and a store of ESI intervene. EAX therefore equals ECX
there. This proves local register-state equivalence, not exact bytes and not
a reason to weaken the gate. Every branch displacement and relocation site
is unchanged.

The fallback still emits `B8 50 6E 33 01` at +0x23C, with no symbolic COFF
relocation for VA`01336E50`. This is unresolved integration debt even after a
future ModRM fix. The PE export directory itself names RVA`00F36E50`
`?TheEmptyString@AsciiString@@2V1@B`; this is an AsciiString empty object,
not a real TeamPrototype. The existing nullable name accessors in
`game/GameEngine/Source/GameLogic/Object/ObjectSetTeam.cpp` and
`game/GameEngine/Source/GameLogic/AI/AIPlayerCheckReadyTeams.cpp` use the
address-derived one-word narrow-string symbol `Rva01336E50EmptyString`.
The retained candidate's numeric TeamPrototype-pointer view must not ship
unchanged. No fallback rewrite was mixed into this controlled replay.
The unpacked PE has an empty base-relocation directory;
that absence cannot establish the original linked executable's relocation
metadata. No named-data rewrite or whole-image link acceptance was attempted.

## Ghidra/MCP provenance and limits

The 2026-10-04 direct-only stdio MCP sessions at 13:40:04 and 13:40:49 UTC
successfully read ten byte blocks covering the vtable, thunks, caller slice,
virtual callees, narrow release and latch bodies. Every recorded block was
rechecked byte-for-byte against this worktree's pinned PE. Their addresses,
sizes and SHA256 values are retained in the replay JSON. Decompiles succeeded
for the caller, slots 25/53, narrow release and latch constructor/destructor.
Decompile at VA`0074C710` reported no defined function; its raw-byte read and
complete native decoding succeeded. Both sessions closed without saving.

This evidence preservation replays the reviewed source and rechecks those
recorded MCP results; it does not claim a new Ghidra session. Decompiled C
is supporting context, never byte-match or original-signature proof.
