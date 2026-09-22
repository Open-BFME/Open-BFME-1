# Where names come from

A byte-matching row says nothing about what anything is CALLED, and that is the one
defect class with no gate behind it. `m_pitchShift` compiles to the same bytes as
`m_priority`. The five identity detectors (`multi_name`, `ctor_vtable`, `null_reloc`,
`size_outlier`, `find_emitter`) are all keyed on an ADDRESS; a member name has none,
so not one of them can see a wrong one.

This document is what a naming spike on 12 Sep 2026 measured, and the rule it settled.

## The rule

An `Rva0026C320Owner` is not laziness and it is not the problem. It is
**self-labelling**: it announces its own ignorance, it greps out in a second, and no
reader is misled by it. A plausible wrong name does none of those things. So the
property to defend is the self-labelling, not the machine-generatedness.

| The name claims | What checks it | What to write |
|---|---|---|
| nothing (`Rva0026C320Owner`) | — | fine as a floor, never as an answer |
| a SHAPE (`FiveDwordElem`, `PooledNodeHeader`) | the body itself | when identity is unproven — **keep the address token** |
| an IDENTITY (`Player`, `AudioEventRTS`) | caller, vtable, string literal, ZH twin | only with evidence, and cite it |

**The address disappears as a reward for evidence, not as a style preference.** An
unproven name that drops its address has converted a visible unknown into an invisible
one, which is strictly worse than where it started. ICF makes this concrete. `vector<AsciiString>::_M_insert_overflow` exists twice:
`0x00063700` has 38 retail call sites across 29 claimed sources and `0x00757C70`
has 2. They are the same 268-byte template body and differ only in three rel32
slots. A type named after an address exists so the mangled callee resolves at the
copy you want — `Open2Elem063700` reaches `0x00063700`, not `0x00757C70`:

    class Open2Elem063700 : public AsciiString      // shim AsciiString: derive
    { public: Open2Elem063700( const Open2Elem063700 &o ) : AsciiString( o ) {} };

Deriving keeps the layout and both string callees, so only the mangled callee
changes. **The address must stay UNIQUE; it never has to be the whole name.**
`AsciiStringElemNoRefcountBump` disambiguates exactly as well and says what the
distinction IS, which is the whole difference between a disambiguator and a
riddle. Count the call sites before deciding which ICF copy owns a name.

## Do not guess — ask

The repository already holds the real name for a large share of the member surface.
Nothing was putting it in front of the agent at the moment of choosing, so it was
re-derived by hand or skipped. `tools/name_oracle.py` is that lookup:

    python3 tools/name_oracle.py --class AudioEventRTS
    python3 tools/name_oracle.py --class AudioEventRTS --offset 0x20
    python3 tools/name_oracle.py --todo          # placeholders the evidence can already name
    python3 tools/name_oracle.py --check         # sources that CONFLICT with the witness

An agent guesses because guessing is cheaper than finding out. One command is cheaper
than guessing.

## The supply, measured

| Source | Real names | Notes |
|---|---|---|
| `reverse/zh_offsets.json` | **9,539** `(class, member)` at ZH offsets, 1,488 classes | parsed from ZH headers |
| `reverse/name_tables.tsv` | **4,814** enumerator names, 229 confident tables | SAGE puts every shipped enum's full name list in the image, in declaration order |
| `reverse/field_names.csv` | **2,063** members (1,984 with ≥2 votes) | binary `FieldParse` tables × upstream `offsetof` |
| `reverse/exports.csv` | **1,820** real mangled symbols at RVAs | authoritative |
| `reverse/bfme_layouts.json` | **2,780** members, 430 classes | the harvested slice, at *BFME* offsets |
| `lotrbfme.exe` string data | **118** `\bfme\Code\...` source paths | EA's own build tree; anchors nearby vftables |

Against ~15,620 remaining `char pad[N]` members, the 9,539 ZH pairs are roughly **61%
potential coverage**. The split by surface matters:

* **Members** — high coverage, largely unharvested. Worth automating.
* **Enums / BitFlags** — effectively complete for shipped enums. `ModelCondition` = 304
  names, `KindOf` = 181.
* **Function identity** — thin. 1,820 exports plus the ~142 reloc-named candidates
  `next_work.py` serves, against 22,233 nameable placeholder rows. This stays
  evidence-capped: more agents does not raise it.

## The pipeline, and why it is stuck at 430 classes

    ZH header          class X { m_foo @ +0x04 }          zh_offsets.json, 9,539 pairs
         |
    layout_witness     align ZH body <-> retail body, instruction for instruction
         |             (displacements normalised away; <70% alignment dropped)
         v
    bfme_layouts.json  X::m_foo is at BFME +0x08          430 of 1,488 classes

The gap is NOT "nobody ran the pass". Running `layout_witness.py --compile` fresh in a
clean tree makes coverage **worse** — 2,780 named members fall to 1,726, and 430 classes
to 324 — because the tool consumes `build/layout/ref/*.obj` **plus**
`build/match/reference_*.obj`, and a fresh compile succeeded on only 415 of 704
reference TUs. The committed artifact was produced from a larger successful set.

**So the lever on witness coverage is making more reference TUs compile, not re-running
the aggregation.** `compile_reference()` swallows every exception
(`except BaseException: return False`), so the failures are currently unattributed —
that is the first thing to fix for anyone who wants this number to move.

Until then: `reverse/bfme_layouts.json` is a committed artifact that a naive re-run
silently degrades. Do not regenerate it without comparing the before/after counts.

## The offset model, and why it refuses so much

Only 11.1% of member declarations state their offset in a comment, so requiring one
confined the checker to ~1% of the member surface. It computes the offset instead —
declaration order, natural alignment capped at 8 (`/Zp8`), a 4-byte vptr at +0 for any
polymorphic class. That reaches 43,332 members, of which **3,277 land on a
`(class, offset)` the witness knows**: agreements went 548 → 2,311 and the nameable
placeholder queue 10 → 288.

Note what that ratio means. Once offsets are computed, only 7.6% of them find a
witness — **the bottleneck moves from the source side to the evidence side**, and the
next lever becomes `layout_witness`'s 289 failing reference compiles rather than
anything about parsing.

The model is validated against evidence the tree already contains: **5,285 members
state their own offset, and it reproduces 5,260 of them — 99.5%.** That is
`--selfcheck`, it needs no new data, it runs in seconds, and `--max-mismatch` turns it
into a regression test so a change to the size table is answerable as better-or-worse.
Both corrections that got it there came from reading failures rather than guessing:
the off-by-four cluster was the unmodelled vptr (90.5% → 99.5%), and
`GlobalData::m_bfmeOn` stating `+0x1278` as its FIRST member revealed declarations that
window into the middle of a larger class.

Everything the model cannot account for is refused, and the refusals are counted
because they are the safety property: 5,150 structs with a base class of unknown size,
4,867 with an unsizeable type, 1,367 with an unparsed member, 23 windowing into a
larger class. A struct whose own annotation contradicts the computed layout is
disqualified outright — the file wins over the model, which is what stops the 25 known
packed-struct residuals from becoming 25 false findings on somebody's commit.

## It shipped in shadow, and was promoted on a backtest

`--check --staged` now FAILS a commit. Waiting for 300 exposed commits to arrive would
have taken 42 hours (master runs 41 commits/h and 17.8% of them add a member in a file
naming a witnessed class, so 7.2 exposed/h). Replaying the 3,000 that already arrived
is the same evidence and took 2m36s:

    replayed 3000 commits
       1139  commits touching Code/
         70  commits introducing ANY finding   (all already in the baseline)
          1  *** WOULD HAVE BEEN BLOCKED ***

Zero false positives over 1,139 exposed commits bounds the rate under 0.26%, and the
single block is a true catch: `cbedb732c` put `m_status` at `WinInstanceData+0xC`,
where the witness has `m_style`, with a `getStatus()` reading it — byte-green, and
corrected by hand three commits later in `bd878b1eb1`. The gate would have caught it
at commit time.

`tools/backtest.py`-style replay is the right validation for any future widening: it
answers in minutes what a shadow period answers in days.

## An incident worth not repeating

The first `--todo --apply` pass renamed 116 members and five of them were regressions,
landed on master and reverted afterwards:

    m_isScoringEnabled     -> m_nextObjID     leaving  isScoringEnabled() { return m_nextObjID != 0; }
    m_ambientSoundEnabled  -> m_secondMaterialPassOpacity   beside m_ambientSoundEnabledFromScript
    m_kindOf0 / m_kindOf1  -> m_kindof / m_shadowOffsetY    splitting one 64-bit KindOf mask

The cause was a single `re.I` on the placeholder pattern: with it,
`[0-9A-Fa-f]{2,}$` matched ordinary letters, so `m_shouldFade` parsed as
`shouldFa` + `de` and read as address-derived. A rule meant to identify names that
admit ignorance was quietly classifying real names, and `--apply` then overwrote them
from the witness.

Two lessons, both now enforced by `tools/tests/test_name_oracle.py`. **The placeholder
test is load-bearing** — it decides what gets rewritten automatically, so it needs
fixtures asserting both what it matches and what it must not. And **a name that is not
a placeholder is a question, never an automatic rewrite**, however confident the
witness: `m_forced -> m_radarForceOn` was kept because it reads coherently in a Radar
body, and that judgement is not one a script gets to make.

## Reading a `--check` finding

    name_oracle: 494 agree, 16 resolve inside an embedded struct, 7 spelling variants,
                 65 nameable placeholders (--todo), 94 conflicts, 0 not in the baseline

A conflict is **a question, not a verdict**. The witness is itself inferred, and BFME
forked the ZH layout — a field BFME added can land on an offset ZH used for something
else. `ScoreKeeper+0x124` reads `m_powerPoints` in source and `m_totalUnitsBuilt` in the
witness, and BFME really does have power points. Two independent claims conflicting is
something a human settles, which is why `reverse/name_oracle_baseline.csv` is a
shrink-only debt register in the same shape as `pin_consistency_baseline.csv`.
**Never add a line to go green.**

Conflicts propagate by copy-paste: `NetCommandRef+0x10 m_timeLastSent` vs `m_relay`
appears in eleven files. 94 findings are far fewer than 94 decisions.

## Traps this cost a day to find

* **A nested struct's offsets are relative to the NESTED type.** Folding them into the
  outer class's offset space invents contradictions that are not there. The first
  version of this scan scored `GeometryInfo`'s inner `BfmeShape::m_height` against
  `GeometryInfo+0x04` and reported a correct file as a defect, at a 22% false rate.
  `outer_members()` tracks brace depth for exactly this reason.
* **A type can be pinned without its bare name appearing in the ledger.** Searching
  `functions.csv` for `Sub005C6A40` finds nothing; the token only exists inside the
  decoration `??1Sub005C6A40@@QAE@XZ`. Two agents lost a build to this. Check decorated
  forms before calling a type free to rename.
* **Commits per hour rewards the wrong work.** A member-naming lane landed sixteen
  commits that pasted the same twelve `TAiData` fields into sixteen different TU-local
  shims — each honestly gated, together sixteen copies of one fact, and a net loss on
  SSoT. Score identifiers removed and duplicate definitions eliminated instead.
* **Renaming without identity produces longer opaque names.** `Q2Vt0110F978` became
  `PolymorphicVptrBase0110F978`: byte-clean, honest, and still unreadable, because
  `0110F978` is a vftable address and the reader still cannot tell what the class is.
  Require the ADDRESS to disappear, not merely the name to get longer.

## The inflow

Over 14 days to 12 Sep 2026 master took roughly 12,000 commits. `Body` rose 63 → 75
while `Iface` fell 59 → 47, `Local` 34 → 26 and `SrcIdent` 65 → 58; the composite `BRI`
read 48 then 47. In the last seven days 3,942 real `.cpp` were added under `Code/` and
840 removed, and **1,615 of the additions — 41% — shipped with a fresh address-derived
identifier**, every one from a conversion commit.

That is ~231 newly illegible files a day. A six-seat naming fleet clears roughly ten
files per seat-hour, so a cleanup lane cannot outrun the conversion lane. The naming
convention has to be right where the file is BORN; everything in this document is
cheaper applied at conversion time than retrofitted.

## A lane with evidence already in the ledger: aliased base classes

Some invented class names are already PROVED to be a real class, by a pin somebody
landed: `reverse/symbols.csv` pins the invented class's destructor onto the real
class's destructor body. That pin is the evidence the naming rule asks for -- the
address disappears as a reward for evidence, and here the evidence exists.

Measured by matching `??1<Class>@@[UQ]AE@XZ` pins against the matched row that owns
the target address (non-template, non-nested destructors only -- the class token
cannot be read off a template mangling with a regex, and trying produced
"VAsciiString" and "ABV0" as class names):

| | count |
|---|---|
| invented classes pinned onto a real class's destructor | 139 |
| ...of which GENERATOR-minted (`Gen_t_*`, `Gen_uw*`, `Mem<n>`) | 117 |
| **hand-written, genuinely misnamed** | **22** across 20 real classes |

The 117 are not misnamed and must not be touched: gen_uw's own header says its
payloads "reproduce a frame slot and a call, never a class identity". Anonymous by
design is not the same as badly named.

Of the 22, several alias a target that is itself invented (`BfmeHostZB`,
`BfmeOwnVVE`), so the clean set is about a dozen:

    SubsystemInterface  <- BfmeBase1134, BfmeDtorBase_00077560, Rva004948B0Base
    RenderObjClass      <- Rva0091FC10MultiBase
    ModelConditionInfo  <- Gen0013C3F0
    AIInternalMoveToState <- Gen00172430
    LZHLCompressor      <- Gen00825550
    LZHLDecompressor    <- Gen008267E0
    HLodDefClass        <- Gen0097D800
    Video               <- Gen000C3410 (recovered; earlier DamageInfo alias was wrong)
    ServiceHubImpl      <- Gen007EB140

**Why this has not been done.** Renaming a class changes the mangled name of every
one of its members, so each rename is a large `reverse/functions.csv` edit, not a
source edit. That is the shape that hides defects when it goes wrong, so it wants a
green full gate, a byte-verify per touched row, and one class per commit -- not a
batch. The evidence is banked here so the next attempt starts from the list rather
than from a survey.

### Guard-machine layout witness conflict

`AIGuardInnerState::onEnter` at `0x0015C570` is identified by dedicated
vtable `0x01096160`, slot 4 via ILT `0x0003D6FE`. Its machine view uses
`+0x4C` as the polygon receiver for `0x0018F880` and `0x0018F790`,
`+0x50` as a three-component position, and `+0x6C` as an ID passed to
`GameLogic::findObjectByID`. The independently matched guard scan-position
body `0x0015C330` agrees on polygon/position offsets.

The current inferred `AIGuardMachine` witness instead assigns nemesis ID
to `+0x4C` and guard mode to `+0x50`, based on tiny setter identities at
`0x0016A390` and `0x0016AEB0`. Those identities need a separate caller
audit before changing the shared witness. The new state routine therefore
uses `Rva0015C570GuardMachine` as its partial layout view; its proven method
identity remains intact. No baseline was increased and no shared witness
was silently rewritten to accept the new source.


### Video and the unrelated 12-byte template family

The earlier `Gen000C3410 -> DamageInfo` entry was false. Retail
`INI::parseVideoDefinition` (`0x000C3480`) constructs a 28-byte local, requests
`DefaultVideoData`, passes it to `VideoPlayer::addVideo`, and destroys it through
ILT `0x000167CF` to `0x000C3410`. That 89-byte destructor releases three strings at
`+8`, `+4`, and `+0`; the real DamageInfo constructor instead places its output
subobject at `+0x4C`. The canonical recovered layout is
`Code/GameEngine/Include/GameClient/Video.h`, and its parser/destructor owner is
`Code/GameEngine/Source/Common/INI/INIVideo.cpp`.

Retail field table RVA`0x00D2CBD8` names Filename (+0), Comment (+8),
HasSubtitles (+0xC), Volume (+0x10; percent-to-real parser), and IsDefault (+0x14).
The three string names agree with the upstream Video declaration. The old
`m_isLooping` name conflicted with the table. VideoPlayer::init calls the
100-byte SubtitleManager constructor at `0x0081DA30` and stores its result at
record +0x18 (`0x0081CC94`, `0x0081CCAC`). The getter at `0x0081CA10` reads that
field; its exact diagnostic at VA`0x0112CD30` names
`VideoPlayer::getSubTitleMgrForVideo`. `parseSubtitle` calls its virtual slot +0x58.
The two query bodies read the same 28-byte table at VA`0x0130B19C`/`0x0130B1A0`.

Six unrelated 12-byte template bodies, 553 bytes total, now use the address-derived
emission surrogate `Rva00755100Element` in the STLport directory. Its string
member reproduces the observed assignment shape; it does **not** identify the
original semantic element. The former Video aliases at `0x000FB9C0`,
`0x0010BDB0`, and `0x007544F0` are retired while their existing owners retain the
ranges. The first two have exported Coord3D and GameClientRandomVariable
identities. The retained vector<ICoord2D> owner has upstream nesting and byte
proof; this audit did not discover a uniquely named direct retail caller.

Video's no-EH vector destructor at `0x0081D0F0` retains an address-qualified
variant claim, distinct from the existing EH body at `0x0081D040`. The three
range helpers keep their addresses and call the actual destructor explicitly;
there is no recovered `Video::handle` method.

## Preserve names when landing or moving a body

`tools/name_regression.py OLD NEW` (`NEW` may be `:` for the staged index)
compares descriptive names with address/offset placeholders. Both commit and
push hooks run it. It links files by path, Git rename, and the function RVA in
changed ledger rows or address-bearing filenames, including an existing bank
under `reverse/attempts/`. Renaming the owning class cannot hide a regression
behind an unknown `(class, offset)` witness key. Comments retaining the old
name do not count as preserving its declaration.

This is a historical regression check, not proof that an inherited name is right.
It checks aligned identifier substitutions and unambiguous layouts that
`name_oracle` can compute; it is not a complete C++ semantic rename detector.
A semantic rename supported by better evidence remains permitted. Do not replace
an established name with an opaque name merely to land a matching body.

An intentional descriptive-to-opaque identity correction requires an entry in
`reverse/name_corrections.json` (a JSON list). Each entry contains `old_path`,
`new_path`, `old_name`, `new_name`, `before_sha256`, `after_sha256`, `evidence`,
and `reason`. Hashes are SHA-256 of the exact UTF-8 source snapshots, including
line endings. `evidence` names a nonempty tracked file under `docs/` or `reverse/`
that independently refutes the old identity; `reason` explains that evidence.
The record applies only to those exact snapshots and that name pair. It is not
a reusable exemption or a growable count baseline. Review the evidence with the
correction: the check can enforce its presence, not prove the identity for you.

The hooks also require the checker and its layout walker to match the staged
index (commit) or outgoing commit (push), so an unstaged tool experiment cannot
silently change the verdict on the reviewed source.
