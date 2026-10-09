# AISideInfo identity: verified repair blocked by DIR32 record guard

Worker C1, 2026-10-09. This is the owner-assigned AISideInfo lane; the lane
explicitly authorizes this shared-shim edit and any snapshot-specific name
corrections required for this rename. No other reference file is changed.

## Independent identity witnesses

The matched AI::newOverride caller in
`game/GameEngine/Source/GameLogic/AI/AINewOverride.cpp` allocates AISideInfo
and invokes its constructor and assignment operator. Existing symbols.csv
pins, independently checked with tools/pin_consistency.py, resolve as follows:

- `??0AISideInfo@@QAE@XZ`: ILT 0x00045165 -> body 0x0014B6B0,
  existing matched extent 140 bytes, formerly `??0Gen_0014B790@@QAE@XZ`.
- `??4AISideInfo@@QAEAAV0@ABV0@@Z`: ILT 0x00019FB0 -> body
  0x0014A470, existing matched extent 162 bytes, formerly
  `??4Rva0014A470@@QAEAAV0@ABV0@@Z`.

`tools/ilt_oracle.py check` independently CONFIRMS the exact decorated names:

- ctor at 0x0014B6B0: p_false=2.61e-4;
- virtual complete dtor `??1AISideInfo@@UAE@XZ` at 0x0014B790:
  p_false=3.91e-4, existing matched extent 86 bytes;
- assignment at 0x0014A470: p_false=5.22e-4.

The constructor installs vftable VA 0x010957C4. Its first slot points to
ILT 0x000319C6 -> deleting destructor 0x0014B760 -> complete destructor
0x0014B790. Constructor and destructor both operate on the string members
at +0x04 and +0x1B8. The assignment skips the vptr, copies the same strings,
three gatherer counts, five 21-dword skill records, and next pointer +0x1BC.
These witnesses identify one class across all three bodies; byte matching
alone is not the identity evidence.

The independent Zero Hour AI::parseSideInfo allocation also uses AISideInfo.
BFME's matched parseSideInfo at 0x0014BF10 (299 bytes) allocates the same
0x1C0-byte object and calls body 0x0014B6B0. Its typedef forwarder is
replaced by the real class declaration, without a macro or typedef alias.

## Provider collision

FX recorded the previous verified rename attempt in the host evidence file
`build/linkfleet/fx/forwarder-pass-2026-10-09.md`. The constructor and dtor
byte-verified under the recovered identities, but ai.cpp emitted a competing
inline Zero Hour AISideInfo constructor from the aicommandoutofline shim.
The competing constructor won selection and BfmeConv1651.cpp LINKED fell
140 -> 0. The shim must declare the constructor out of line so it calls
retail's existing provider. Its inline empty complete destructor likewise
must not compete with retail's verified destructor. The pool macro already
declares the virtual destructor; remove its EMPTY_DTOR definition.

No extent is enlarged, new pin introduced, generated body edited, baseline
expanded, or escape hatch added. The vftable address record is respelled to
the proven class while preserving its existing retail address.

## Compiler dependency receipt correction

The initial C1 link check still saw both inline copies after the shim edit.
The actual ai.cpp dependency receipt selected the upstream GeneralsMD
GameLogic/AI.h, not aicommandoutofline. Its cl include path therefore must
select the existing aicommandoutofline shim before upstream headers. This
change removes the competing emitters rather than editing upstream code.

## Existing unwind row follows its independently proven parent

After selecting the shim, ai.cpp no longer emits AISideInfo's constructor,
so its existing row uw_00c044eb (RVA 0x00C044EB, extent 14 bytes) must follow
the real constructor provider. `tools/eh_info.py 0x0014B6B0` independently
reads retail handler 0x00C044F9 and FuncInfo 0x00DF2974: state 0 unwinds
+0x04 via cleanup 0x00C044E0, state 1 unwinds +0x1B8 via 0x00C044EB.
The latter is exactly the existing row, not an adjacency-derived parent.
The initially compiled BfmeConv1651.cpp has one matching parent-group cleanup,
$L891; $L890 does not match. After adopting the witnessed member names and
explicit 21-word records, that same cleanup renumbers to $L886. Repointing the same row preserves its extent,
parent, and existing object-symbol hatch; it creates no new escape hatch.
The unrelated AI::crc cleanup at 0x00C04530 renumbers from $L81110 to
$L80656 in ai.cpp; the byte gate identifies that same parent-group body.

The attempted constructor member names were supplied by name_oracle's FieldParse
witnesses. Its five skill records retain their existing 0x54-byte layout,
represented as 21 four-byte words with the count at index zero, matching
the shipped skill parser and upstream TSkillSet definition.

## C1 outcome: blocked and reverted, no source or ledger landing

All three identity corrections byte-verified with add_match --correct-identity.
Selecting aicommandoutofline in ai.cpp and moving the independently proven
constructor cleanup also verified: BfmeConv1651 2/2, destructor TU 2/2,
assignment TU 1/1, parser 1/1, AINewOverride 1/1, ai.cpp 16/16.
The six-file current preview preserved LINKED 471 -> 471 bytes; wrong ctor
and assignment selections disappeared, while unrelated AI/string blockers
remained. The ctor/dtor/assignment providers individually kept 140/169/162
LINKED bytes. No name correction JSON entry was required. All staged naming,
ILT, pin-consistency, header-adoption and ledger checks passed. Hatch counts
compared directly against HEAD did not grow; five shadow register warnings
were already present in functions.csv outside this lane.

`python3 tools/dir32_record_guard.py --staged HEAD` refused the vftable
record rename with this diagnostic:

    ??_7AISideInfo@@6B@,0x010957C4 added: retail 0x010957C4 is already
    recorded as ??_7BfmeOwnVUP@@6B@ (+1 more); reference that name,
    not a new one

The compiler emits the recovered class's own vftable name; the independently
proved identity cannot spell either obsolete placeholder. The record guard
compares additions against the base record, so the coordinated proven rename
is rejected even though its retail address is unchanged. This is recorded as
a false reject, without aliases, forwarders, new pins, checker changes or
baseline expansion. Operator review is required before retrying this lane.

The required full gate had started and was waiting for the host build lock;
it was cancelled after this blocking check, before byte comparison. The
113-TU dependency run was stopped to correct ai.cpp's include routing; the
final state never received a completed full/dependency gate. All code,
shim and ledger changes were reverted. Only this evidence and the re_log
false-reject outcomes are published. The complete attempted patch and tool
transcripts remain in this worktree's build/c1_* files, with a durable host
copy under build/linkfleet/codex/C1-aisideinfo-blocked/.
