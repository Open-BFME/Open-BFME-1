# Codegen recipes

Full history: docs/lessons-archive.md and git log.
This file is curated, not append-only: edit a recipe in place rather than
appending a new section; the commit message is the place for the war story.

## A naked body passing the byte gate proves nothing

Symptom: `Functions: OK N/N` on a file that is still `__declspec(naked)` /
`__asm { __emit ... }` — the dump reproduces its own bytes by construction.
Removing only the `naked` keyword around a pure `__emit` block also still
passes. Rule: a conversion means NO `__asm`/`__emit` anywhere in the file;
check what is on disk, not the ledger — `status=matched` can be leftover from
the original dump commit.

## A naked row's name is unverified by construction

The byte check is a tautology for a dump, so the attached name was never
tested. Read the body against the claimed signature BEFORE starting: `ret N`
vs the mangled argument list, `or eax,-1` vs a void return, eax loaded vs `_N`
return, this-relative offsets that make no sense for the claimed class.
Example: `??1TooltipUpgrade@@UAE@XZ` ends in `ret 4` — destructors take no
arguments, so the name is wrong whatever the bytes say.

## Row boundary rules

A MASM dump matches at any length (one 231-byte function claimed 1006 bytes
and swallowed three neighbours); a 5-byte row matches any E9 thunk; a 1-byte
row matches every bare `ret`. Before adding or trusting a row: deref the thunk
chain, measure the body by disassembly, and check the claimed address is an
instruction boundary — linear-decode from the containing function's start;
interior `int3` is decisive. Functions from different TUs do not interleave in
the image.

## vptr scheduling: screen before writing

MSVC sinks a constructor's vptr store exactly to the end of the leading run of
same-valued member stores, no further; retail's placement varies. Compare
retail's vptr position against that prediction: if they agree, convert; if
not, park — no source ordering reaches vptr placement.
Members initialised by a member constructor land after the vptr and before the
body; stores between the interim and most-derived vtable groups are base-
subobject member inits, not body statements.

## novtable is one knob with two effects

It removes the interim per-base vtable stores (module ctors writing each
interface vtable twice → once) AND removes that base's unwind entry (all EH
states shift down by one, body a few bytes short). Set it by what retail
shows, not habit. Destructor variant: retail restoring only the base vptr at
the end means the derived class is novtable; a derived vptr store at entry
means it is not.

## Read destructible subobjects off the unwind states

Retail's highest EH state + 1 = destructible subobjects, bases included. A
base gets an unwind entry only if it has a declared destructor — declaring
`~Base();` (undefined) adds the missing frame; a virtual destructor where
retail has none adds a state and shifts every index. A virtual destructor
stores a vptr only in a ROOT polymorphic class; in derived destructors it is
elided as redundant, so "no vptr store AND no base-destructor call" is the
test for non-polymorphic, and neither half alone means anything.

## throw() removes EH frames and temporary unwind states

`new T` carries an EH frame just to call `operator delete` if T's ctor throws;
declaring the reachable constructors `throw()` removes it (an undefined ctor
is assumed throwing). Wider: `throw()` on whatever executes between a
temporary's construction and destruction removes that temporary's unwind
state. Declaring `void __cdecl operator delete[](void *) throw();` (as real
<new> does) removes the state for `delete[]` in a destructor. Scope the
declaration to a TU shim; editing a real shared header is its own tick.
Counter-lesson: the constructor-inlined-into-new-expression shape is NOT
reachable from source (forceinline/throw()/nothrow all tried) — park those.

## SEH shape is a flag, not code

Base build is `/EHs-c-`. Right length but an extra `fs:[0]` prologue means the
per-file `// cl:` line re-enabled exceptions (`/GX-` restores). The
`mov [esp+N],esp` stash before a by-value class argument is the /EHs model;
/EHsc and /EHa add an SEH prologue retail may lack. Probe flags directly with
a throwaway TU and build.py's compile_source instead of round-tripping the
byte gate, and give the probe the same destructible locals as the target.

## x87 flags from byte tests are mostly false

`any byte in D8..DF` matches displacements and immediates: 603 of 753 flagged
functions had no x87 at all. Decode with capstone before believing an x87 (or
any opcode-shaped) label, and re-screen parked rows when a screen is fixed.

## Write the reference's loop; MSVC's rotation is the target

A counted `for`/`while` gets rotated (entry test peeled, value test on the
back edge) and small counted loops get unrolled — `for (i=0;i<4;i++)
size=(size<<8)|b[i]` unrolls two-at-a-time into paired dword/word loads that
no hand-unrolled spelling reproduces. Retail's bottom-tested scan with an
early exit past the loop is `do{}while` plus `goto`; reach for that only when
no plain loop form produces the flow.

## Byte loads widen within the array they belong to

Adjacent byte reads widen to the widest access that stays inside their own
array: `struct { u8 magic[2]; u8 size[4]; }` gets dword+word where a flat
`u8[6]` gets neither. Split buffers into the sub-arrays retail's accesses
imply.

## Register allocation is not source-controllable

Same instruction count, same length, but a different induction base, lea-base
vs direct displacements, esi/edi swapped, or a constant in a different
register: these are compiler tie-breaks with no source lever. Stop permuting
and record present-unmatched. (Distinguish from *placement* of stores, which
source does control.)

## Ordering levers that ARE source-controllable

- Initialiser list emits in declaration order; body assignments emit as
  written. Retail's store order tells you which to use — a flag at +0x54
  stored before the word at +0x50 means body statements, not init list.
- Independent locals initialise in declaration order.
- Switch arms lay out in source order; sort the jump table by target address
  to recover it.
- `x = y` (inline operator= forwarding to set) materialises the destination
  before the argument; `x.set(y)` pushes the argument first.
- A discarded return value becomes a tail jump: retail's real call where you
  emit `jmp` means the function returns something the reference discards.

## A this-adjustment hoists only if the source goes through the owning base

An override of a virtual declared in a *secondary* base is entered with that
subobject's `this`. Reading a member off it directly gives negative
displacements from the entry register:

    ours:   mov esi,ecx / mov eax,[esi-8] / mov ecx,[esi-0xc]
    target: mov eax,[ecx-8] / lea esi,[ecx-0x10] / mov ecx,[esi+4]

Retail materialises the *primary* base once (`lea esi,[ecx-0x10]`) and indexes
forward off it. That is not a scheduling tie-break: it happens because the
reference source calls a helper declared on the primary base, so the adjustment
is a real subexpression with two uses. Spelling the helper's body inline at the
call site removes it, and no permutation of the inlined form gets it back.
Write the wrapper as an inline member of the base that declares it
(`DieModule::isDieApplicable` calling `getDieModuleData()` and `getObject()`),
then call it unqualified. Same instruction count either way, so the size is no
clue -- look at whether displacements off the entry register are negative.

## `delete p` shape reads the type's completeness

Null check + `push 1` + call through vtable slot 0 = complete polymorphic
type (deleting destructor). Plain `operator delete` call = incomplete type.
Complete the class (with virtual dtor) or keep it forward-declared to match.

## A vtable slot belongs to the class that DECLARES the virtual

Reordering a derived header cannot move a base-declared slot. Reference base
classes often carry slots BFME lacks (SubsystemInterface adds six;
MemoryPoolObject's pure getObjectMemoryPool adds one) — one wrong base slot
count shifts every virtual in every derived class. Same-name virtual
overloads lay out in reverse declaration order.

## Temporaries schedule by how visible their type is

An extern, undefined constructor makes a temporary opaque and reorders the
unwind-slot store vs the receiver load; making construction visible (inline
delegation) restores retail's order. When retail inlines part of a string
class, do not derive from StringBase — use a standalone shim class with an
inline `m_text = 0` ctor, a destructor pinned to releaseBuffer, and real ops
via cast to `StringBase<T>*` (the campaignmanagerascii shim is the model).

## Shim headers do not invalidate the build cache

The deps cache keys on content of previously-seen paths; a brand-new shim
compiles nothing ("Compile: 0 of 1 TU(s)") and you diff stale bytes. Change
the source text (any character) to force the recompile, and always read the
build's own compile count before theorising.

## Header edits cost the host-wide full gate — batch them

Any staged header/shim change runs the full gate, serialised host-wide (one
commit queued 44 minutes). Per-file verifies (<8 TUs) take no lock: make every
header edit first, verify each dependent source with `./build.sh`, then pay
the gate once. Never run a per-file verify while a full gate is running.

## Union-merge duplicate row: delete the line by hand, not dedup_csv

The ledgers mix `\r\r\n`, `\r\n` and bare-LF terminators (~94k `\r\r\n` rows)
and `add_match` indexes them by physical line. `tools/dedup_csv.py` rewrites
both files normalised — a ~157,000-line diff that conflicts with every branch
in flight — so ignore the `Fix: dedup_csv` hint for a simple post-merge
duplicate. But do not assume it is ONE line: union merge duplicates CONTIGUOUS
BLOCKS -- six exact-duplicate Open2Handler pins arrived in one rebase. The
procedure that scales and stays inside the rules: drop records whose payload is
byte-identical to an earlier record, keep the first, and do it with
tools/ledger_io.py so terminators survive and nothing else in the file moves.
That is the sanctioned programmatic middle between "never hand-edit the ledger"
and "do not run dedup_csv here": one row per duplicate, no normalisation.
Verify with check_csv and pin_consistency before pushing. Union merge can also silently
drop pins during a rebase; check `git status` before pushing.

## Comment lines that start with a mangled name are parsed as claims

find_declared_unmatched.py reads any line starting `// ?` as the next
definition's declared symbol — a wrapped prose comment then fails the claims
gate on an unrelated function. Write names in prose form
(`ControlBar::findNonConstCommandSet`) or keep them off the line start.

## Convert families, not functions

Normalise bodies (zero rel32 operands and image-address immediates), hash
against converted rows AND against other naked rows: ICF-folded twins convert
by substituting the one class name that reaches the mangled symbol;
constructors differing only in vtable address are one reconstruction written
N times. Each landed conversion is a model for whatever still matches it.

## Count the blockers before starting, and stop at single digits

A big function's cost is its least-known callee: count unresolved call
targets against functions.csv/symbols.csv first (GameEngine::init: ~50
independent naming problems). Read the disassembly before building — a bare
`ret` against claimed arguments, or provably dead code retail kept, kills a
candidate in one read. When a body stalls within single digits of exact with
every instruction present, the residue is retail's TU structure (what the
inliner saw), not a spelling — record it and move on.
One exception, and screen for it before you give up: a callee DEFINED later in
the same TU can inline into an earlier caller where retail emits a call.
TeamPrototype::hasAnyBuildFacility failed while three structurally identical
sibling walks passed, because the inliner declined their callees and took that
one. Declare the callee on a view class -- declared, never defined -- so the
call survives, then alias that spelling at the ILT address. The screen costs one
build: list the callees defined in the same TU and rebuild -- and go one level
deeper than your own body: for each body RETAIL inlines into yours, screen ITS
callees for in-TU definitions too. Retail inlines the whole
TeamPrototype::teamAboutToBeDeleted walk into the TeamFactory one, and at that
depth MSVC also took Team::removeOverrideTeamRelationship, defined in the same
TU, where retail still calls it; one view fixed both sites. In
TeamPrototype::updateState both candidates were declined and the existing pins
resolved unchanged, so the screen is cheap even when it finds nothing.

## Layout facts you can read straight off the bytes

Element size from the `sar`/`shl` pair or a reciprocal-multiply magic
constant; POD-ness from memmove vs an element-wise loop; funclet count = EH-
protected temporaries; an untouched gap between stored offsets is still a
member (declare it, do not initialise it). A raw address literal is honest
where a name would be invented: `(void (*)(MultiIniFieldParse &))0x0043ABC0`
emits the same push as an unattested name without asserting one.

## W3DRopeDraw::buildSegments: two real drifts, then the shim's STL stops it

Worked as the first test of the `callers_of.py --files` queue: the 587-byte dump at
0x0075A990 asserts in `W3DRopeDraw.cpp` and its sole caller
`W3DRopeDraw::doDrawModule` lives there too, so the name had to be one of that
file's eight unmatched functions. `buildSegments` compiled to 602 bytes against the
587 wanted, which is close enough to work. Two drifts came out of it:

- **`NEW Line3DClass(...)` should be `::new Line3DClass(...)`.** Retail calls the
  global `??2@YAPAXI@Z` at both allocation sites. Our `NEW` routes through the W3D
  memory pool, which is what leaves `?allocateFromW3DMemPool@@YAPAXPAXH@Z` and
  `?getClassMemoryPool@Line3DClass@@CAPAXXZ` unresolved. Fixing it took the body
  from 602 bytes to exactly 587.
- **The leading `m_segments.clear()` is an `erase(begin(), end())`.** With `clear()`
  the helper call takes four pushed arguments; retail pushes five. Switching to
  `erase` matched the argument count and the `push edi`, and moved the first
  difference from +0x1A to +0x21.

It still does not land, and the reason is worth writing down because it is not this
function's fault. What is left is a single CSE decision:

    target: mov eax,[esi+0x14]                 push edx / push ecx / push eax / push eax
    ours:   mov edx,[esi+0x14] / mov eax,...   push edi / push ecx / push edx / push eax

Same five values in the same order. Retail reads `_M_finish` once and pushes the
register twice; we read it twice into two registers. That is `vector::erase` doing
`copy(last, _M_finish, first)` where `last` and `_M_finish` are the same read - and
whether they get folded is decided inside the STL header, not here. Hoisting `end()`
into a local changes nothing and `resize(0)` is worse (567 bytes).

So the finding is that **the shim's `vector` differs from BFME's**: our `clear()`
lowers to a four-argument helper where theirs takes five. The three-byte offset from
that one extra `mov` never re-syncs, so 172 of 184 instructions read as different
even though the total size is exactly right. Do not chase the tail of this diff -
size agreement plus a cascade from instruction one means look at the container.

Reverted rather than committed: both edits are almost certainly correct, but the
body does not byte-verify, and changing unverified C++ on inference alone puts a
wrong guess where the next agent will read it as fact.

## A shared shim header is not the place for a member declaration

`ArchiveFileSystem.cpp` did not compile for twelve hours, and the cause is worth
generalising because the change that broke it looked completely innocuous: two
copy constructors were converted to real C++, and their declarations were added
to `reference/shims/archivefilesystem_nosubsystem/Common/ArchiveFileSystem.h`.

Declaring a copy constructor suppresses the **implicit default constructor**, and
`ArchivedDirectoryInfoMap` default-constructs its values. So a TU that merely
*included* the header stopped compiling:

    ArchiveFileSystem.cpp(204) : error C2512: 'ArchivedDirectoryInfo' :
        no appropriate default constructor available

There is a second effect that is easy to miss and does not go away by adding a
default constructor back. With the copy constructor visible in the shared header,
MSVC stops inlining `pair`'s copy constructor in the including TU: retail's
`_Construct` copies the two members individually (`AsciiString` copy ctor, then
`ArchivedDirectoryInfo` copy ctor at `+4`), while ours emits one out-of-line
`pair` copy constructor call. Restoring the default constructor got the TU
compiling and still left that row failing.

**Both effects disappear if the declaration lives in the TU that needs it.**
Guard-suppress the shim and spell the class locally:

    #define __ARCHIVEFILESYSTEM_H_
    #include "Common/AsciiString.h"
    ...
    class ArchivedDirectoryInfo
    {
    public:
        ArchivedDirectoryInfo(const ArchivedDirectoryInfo &);
        ...
    };

The conversions are then kept exactly as they were and the including TU is
untouched. All three verify 18/18.

The general rule: a shim header is compiled into every TU that includes it, so any
change to a class in one is a change to all of them. Prefer TU-local modelling for
anything that only one translation unit actually needs - which is the same advice
that already applies to member offsets and enum widths.

### Two failure modes that hide everything else

A red gate is not always a DIR32 problem, and both of these silence it completely:

- **A TU that will not compile** stops the gate at the compile phase, so DIR32
  never runs. Twelve hours of commits landed behind that wall. When the compile is
  fixed, the DIR32 failures that appear are usually *not* new - check which objects
  emit the symbol (`grep -rl '_$E2' build/match/*.obj`) before assuming you caused
  it.
- **A Windows extended-length path.** `Path.resolve()` returns a `\?\` prefix for
  deep paths on Python 3.14 and `ROOT` never has one, so `relative_to` threw in
  `verify_string_refs` - *after* 157,929 functions had already verified. Fixed by
  `tools/build.py`'s `resolved()` helper.

And the payoff for having the gate back: it immediately caught
`RegistryGetUnicodeString.cpp` calling `RegOpenKeyExA` where retail calls
`RegOpenKeyExW`, seen as one symbol resolving to both the A slot (0x01359148) and
the W slot (0x0135914C). The body byte-matches either way because relocation sites
are masked, so no other check in the gate could ever have seen it. **When a symbol
reports two bases four bytes apart in the IAT, suspect A-versus-W before you
suspect a duplicate import.**

## The EH-temporary transposition: one phenomenon, many near-miss bodies

Several bodies in the pairing queue come back at **exactly the right size** with only
four to six differing instructions, and every one of them is the same two
instructions swapped:

    target: 89 64 24 08   mov [esp+8], esp      ours: 8b cc         mov ecx, esp
            8b cc         mov ecx, esp                89 64 24 08   mov [esp+8], esp

Confirmed instances so far, all `--source`-paired against real C++ that is
otherwise byte-identical:

    435B  0x004D7740  PopupJoinGameSystem     (2 sites, 4 diffs)
    446B  0x004C8910  GameInfoWindowInit      (2 sites, 4 diffs)
    737B  0x004DEB70  PopupReplaySystem       (3 sites, 6 diffs)

The construct is always a `UnicodeString` passed **by value** -
`GadgetStaticTextSetText(GameWindow *, UnicodeString)` - so MSVC copy-constructs the
argument on the stack, sets `ecx` to its address, and records that address in a
frame slot so the unwind funclet can destroy it if the call throws. Retail records
first and loads `ecx` second; we do it the other way round. Both orderings are
correct, the byte count is identical, and the rest of the body matches exactly.

Levers already tried, none of which move it:

- `UnicodeString.TheEmptyString` versus `UnicodeString::TheEmptyString`. Note that
  MSVC 7.1 accepts the dot form on a type name and generates identical code, so
  that spelling in the tree is not a drift even though it looks like one.
- The callee signature: ZH declares the parameter by value and so do we, so this is
  not a by-value-versus-const-reference mismatch.

Do not spend a session picking at one of these bodies. They are worth attacking as
a family, and the way in is a TU whose flags differ, not a source rewrite - a
matched body containing the *same* construct would prove which flag flips the
order. Until then, treat "right size, four diffs, `89 64 24` against `8b cc`" as a
known-unfixed classification and move to the next candidate.

**A 93-byte specimen of the same family**, found 2026-08-16 and worth starting
from because everything else about it is settled:
`?sendDisconnectChat@Network@@UAEXVUnicodeString@@@Z` at `0x006824C0`. The whole
body is `m_conMgr->sendDisconnectChat(text)` with `m_conMgr` at `[this+0x08]`,
and it reproduces byte for byte except the same two adjacent instructions:

    retail    89 64 24 08   mov [esp+8], esp
              8b cc         mov ecx, esp
    compiled  8b cc         mov ecx, esp
              89 64 24 08   mov [esp+8], esp

Same construct as the bigger ones — a class passed **by value** into a call
inside an unwind frame — but with nothing else in the function to look past. The
reconstruction is not in the tree, because a source with no matched row cannot
live under `Code/`; rebuild it from this paragraph and the packet at
`reverse/zh_sweep/packets/006824c0.md`.


## The baseline exe is not entirely compiler output

`CopyProtect::notifyLauncher` at `0x001020D0` will not match, and the reason is not
in our source. The target's branch shape is impossible for a compiler to emit:

    0x0010211F   eb ..      jmp    (where the port emits 75 .. jne)
    0x00102173   eb 00      jmp    to the very next instruction
    0x001021B2   eb 04      jmp    followed by 90 90 90 90

A `jmp` whose displacement is zero, and four `nop` bytes padding the middle of a
body, are what a **hand patch** looks like: someone disarmed the copy-protection
checks in place, keeping every instruction boundary so the file length did not
move. `baselines/bfme1/workshop-vanilla-1.03` is a redistributable, not a pressed
retail image, and this is where that shows.

The damage is narrow. The other three `CopyProtection.cpp` bodies --
`isLauncherRunning`, `checkForMessage` and `shutdown` -- byte-match from clean C++,
so only the checks that actually gate the launcher were touched. But the rule
generalises: when a diff is *only* conditional branches turning unconditional, or
shows `nop` runs inside a body, suspect the binary before rewriting the source. No
amount of C++ reproduces a patch.


## Triaging a red DIR32 gate: the count points, the structure proves

`DIR32 consistency: FAIL n NEW inconsistent symbol(s)` names the symbol and its
two bases and stops. `tools/dir32.py <symbol>` lists the rows resolving it to
each base, and one row against twenty says which row to doubt -- but that is a
pointer, not a proof: a majority can be an ICF artifact, and a 1-vs-1 split
says nothing at all. Structure proves it. The six symbols red on 2026-08-16
were **all six wrong rows**, none a second legitimate base, and each fell to
one of these reads.

**Offsets fix the class.** `??0BehaviorModule` at 0x005F84E0 stored its extra
vptrs at +0x14/+0x18 over a 0x14-byte base; BehaviorModule's are at
+0x00/+0x0C/+0x10, where twenty derived destructors restore
0x0109CB5C/0x0109CA98/0x0109CBAC on their way out. A base sub-object is not
0x0C bytes in one body and 0x14 in another, so the body is another class's.
That TU had already written the gap down as two pad dwords to make the offsets
fit -- padding invented to seat a body IS the finding. Which vtable is whose
comes free: MEMORY_POOL_GLUE puts the pool name straight after the table, and
"BehaviorModule" sits at 0x0109CB8C.

**GameEngine::init names a global.** It pushes the subsystem's string literal
and then the global's address, so 0x012F0888 is TheExperienceLevelSystem
(literal at 0x00479C3A, push at 0x00479C48) and 0x012F076C is TheScriptEngine.
Same walk as the whitelist's ThePlayerAITypeSet note; it settles "which
singleton is this" in a minute.

**`??_M` names a container's element.** The call carries element size and
destructor together: 0x74 with dtor ILT 0x0041AAD2 is ProxyClass, 0x10 with
0x00436AB1 is MixFileCreator::FileInfoStruct. Two ILT thunks are the same
function only if they jump to the same place -- these go to 0x003F6EA0 and
0x0005DBE0 -- so "both bases are odd, therefore both are thunks for one
destructor" was the wrong read of that pair. Check the target, not the parity.

**COMDAT adjacency breaks a 1-vs-1.** Constructor, deleting destructor, vtable
and the member that uses the buffer travel together. 0x006DB100 installs the
vtable three other TUs call `ShareBufferClass<I>`'s, its deleting destructor
(0x006DB1D0, slot 1 of that vtable) is 0xD0 bytes on and Get_Color_Array
0x270 further; a body in the wrong run is not the one you named.

Byte verification sees none of this: build.py copies DIR32 slots from retail,
so a body under the wrong name matches at every reference site. And because
`.githooks/pre-commit` forces the full gate on any staged `*.h` or
`reference/shims/*`, a red DIR32 blocks **every** header and shim change in the
tree, not just the guilty file -- fixing one of these rows unblocks a category.


## A `pinharvest` row in symbols.csv is a candidate, not an address

`reverse/symbols.csv` is additive by design: each pinned address becomes one more
candidate for the resolver, which tries them in order and keeps the first that
reproduces retail's bytes. That is what makes incremental-link thunks work, and
it is also why a pin cannot be read as *the* address of anything.

Measured on 2026-08-16: of the 1,361 pins whose notes say `pinharvest` and whose
name also has a matched body in `functions.csv`, **1,193 do not reach that body**
— they resolve through their thunk to some entirely different function. Most are
STL template instantiations, where one mangled name genuinely fits code at
dozens of addresses and the harvest picked all of them.

That is harmless for byte-matching, because a wrong candidate simply fails to
reproduce the target and the next one is tried. It is not harmless for
*reasoning*. `BoneFXDamage::friend_newModuleInstance` at `0x0011E800` is the
case that costs an afternoon:

- The ModuleFactory registration block pairs the literal `"BoneFXDamage"` with
  `0x0011E800`, which is byte-true evidence.
- The name currently sits on `0x0011E2D0` as one of three aliases, and the same
  block registers `0x0011E2D0` as `LockWeaponCreate`.
- The factory calls its constructor through ILT `0x00005B19`, which reaches
  `0x00250740`.
- `functions.csv` puts `??0BoneFXDamage@@…` at `0x0024FC20`.
- `symbols.csv` pins six more thunks for that same constructor, one of which
  reaches `0x0024F860`.

Three mutually inconsistent answers for one constructor, and the factory cannot
land until one of them is proven. **Before spending a name on the strength of a
callee, resolve the thunk and check it against the ledger's own body** — and if
they disagree, say so rather than picking the convenient one.

### The guard that checks this for you

`tools/pin_consistency.py` enforces one name, one function: every address pinned
to a name must follow its thunk chain to a body byte-equal to every other body
that name pins (templates handled by rebasing rel32 slots, not by excluding
them). Landing a pin:

    python3 tools/pin_consistency.py --symbol <mangled>   # chains, extents, owners
    python3 tools/pin_consistency.py --check              # what the hooks run, 1.6s

It runs in the commit hook whenever `symbols.csv` or `functions.csv` is staged,
in the push hook on every push, and in the full gate. Both hooks used to run
only *scoped* builds and the full gate exited before ever reaching it, so until
2026-08-18 a wrong pin could reach origin without any check looking at it.

`reverse/pin_consistency_baseline.csv` is the backlog of 410 known-bad pin sets,
each with its evidence, and **it is only allowed to shrink** — that is enforced
now, not merely requested. Its preamble explains what a line means and how to
resolve one; start there rather than here.

Two things it does *not* cover, both real: names that pin a single address
(70,144 of 70,633 — the 0x14867 "one address, four names" shape is invisible to
it), and the `functions.csv` half of the resolver's candidate list, which
`--candidates` reports and which currently holds **114 more violations**.

Finally, the trap: a session landed all 47 `--clear-cut` verdicts and the gate
turned 111 byte-matched rows red, 110 reaching a pin it had just deleted. **A
byte-verified caller outranks a byte-verified identity row.** `--clear-cut`
emits candidates, not verdicts; retract in small batches, full-gate each one.


## Retail's string payload is at m_data+8, and this tree inlines m_data+4

`AsciiString::str()` and `UnicodeString::str()` inline to a fixed idiom -- test
the data pointer, add the header size, or fall back to the shared empty string:

    85 c0        test eax, eax
    74 05        je   +5
    83 c0 08     add  eax, 8
    eb 05        jmp  +5
    b8 8b 38 07 01   mov eax, 0x0107388B

Counting that idiom across retail `.text` gives **808 sites, every one of them
`add eax,8`**, split by which empty string they fall back to: 734 use
`0x0107388B` (a `char`) and 74 use `0x0107388C` (a `WideChar`). So both string
classes agree, and **retail never emits `add eax,4`**.

Counting the same idiom across this repo's built objects gives 87 sites at `+4`.

The reason is visible in the vendored header. `AsciiStringData` is

```c
#if defined(_DEBUG) || defined(_INTERNAL)
        const char* m_debugptr;
#endif
        unsigned short  m_refCount;
        unsigned short  m_numCharsAllocated;
```

Four bytes with the pointer compiled out, eight with it in — and eight is what
retail uses. Either the shipped build defined `_INTERNAL`, or BFME widened the
two counters; the bytes cannot tell those apart, but they are emphatic that the
header is eight bytes wide.

**This is safe to fix.** A matched row cannot contain `add eax,4`, because retail
has no such site, so all 87 are in bodies nobody has landed yet. Correcting it
should unlock rather than break — the tree already carries BFME overrides in
`Code/GameEngine/Include/Common/` (CRC.h, Snapshot.h, Recorder.h, Module.h) and
an `AsciiString.h` / `UnicodeString.h` override is the same shape of change.
Budget a full gate per attempt, and expect the fallout to be in *unmatched*
bodies that suddenly compile differently rather than in matched ones.

### What it costs, measured

Restoring the eight bytes is a two-file shim in
`reference/shims/sweep/Common/` and it works: `ScriptActions.cpp`,
`GameInfo.cpp` and `MapUtil.cpp` all move from `+4` to `+8` with their 164
matched rows still verifying, and `LANAPI::RequestAccept` loses the string
offset from its diff list. Two things bite anyway, and the second is why it is
not landed yet.

**The define must not reach `Common/Debug.h`.** It reads `_INTERNAL` too, and
letting it see the define turns `DEBUG_ASSERTCRASH` back on — which grew
`LANAPI::removePlayer` past its matched extent. Hoist the vendored header's own
includes above the `#define` and it goes away.

**The dependency cache will tell you the tree is fine when it is not.** Adding a
header *earlier on the search path* does not change any recorded header list, so
`./build.sh` reuses objects built against the old one — 324 of them, still dated
13 August. The full gate passed on those. Delete the affected objects and rebuild
before believing any include-path change.

Once they really do rebuild, the bill arrives: **403 ledger rows in those 135
sources are `uw_*` funclets anchored on compiler-local `$L` labels**
(`object-symbol=$L78143` and friends). Recompiling renumbers those labels and
every one of them stops resolving with `symbol not found in object`. So this
change is not a header edit — it is a header edit plus a 403-row re-anchoring,
and it wants to be one piece of work rather than a surprise inside somebody
else's build.

## MSVC has a private calling convention, and it decides which functions share a file

`drawStaticTextText` at `0x00796BA0` is entered with its first argument in
**EAX**. The callee opens

```
sub esp,0x2c / push esi / push edi / mov edi,eax
```

and its caller at `0x00796FAF` sets up

```
push outline / push color / mov eax,esi / call ... / add esp,8
```

Two stack arguments, one register argument, and an `add esp,8` that does not
account for the third. This is not `__fastcall`, which would use ECX and EDX,
and it is not anything that can be written on a declaration. It is MSVC's own
convention for a `static` function whose every call site the compiler can see,
and **this toolchain reproduces it exactly** — `mov edi,eax` appeared in the
first compile, unprompted.

The consequence is a rule about file layout, not about bytes: **a file-static
that retail called this way and its callers must be converted in the same
translation unit.** Split them and the caller compiles to `push esi` with
`add esp,0xc`, and the caller is wrong in its last dozen bytes for a reason
nothing inside the caller's own file can fix. Before drawing a work packet for
a body whose calls do not account for all their arguments, find the callee and
check whether it takes one in a register.

### And the inverse, which is this lane's hazard

Merging a body INTO the TU that defines its callee turns the same mechanism
against you. `ScreenBWFilter::init` came out three bytes short of 91 with every
offset, constant and call already right: `getChipset` is defined in
W3DShaderManager.cpp, MSVC reached it with the private convention, concluded
ECX survives the call, and kept the shader-handle address there -- where retail
has to park it in ESI and pay the push/pop. Nothing in the body's own text says
so; the tell is a caller that is SHORTER than retail by exactly a
callee-saved-register save/restore, with a value live across a call to a static
defined in the same file.

Fix: declare the callee on a view class -- declared, never defined -- so the
call takes the ordinary convention, and pin that spelling at the ILT the real
name already uses. Same one-line screen either way: before merging, list the
callees your body makes that this destination also DEFINES.

### What that does not buy you

Both of these bodies then stalled on differences below the source level, and
they are worth recognising on sight because no amount of rewriting moves them.

**A SIB base/index inversion.** `W3DGadgetStaticTextImageDraw` came out 237 of
238 bytes. The one difference: retail computes `end.x` as `8d 1c 08`
(`lea ebx,[eax+ecx]`, base EAX, index ECX) and this toolchain emits `8d 1c 01`
(base ECX, index EAX). Identical operation, identical registers, inverted
encoding. It survived `start.x + size.x`, `size.x + start.x`, a compound `+=`,
inlining the expression into the call argument, swapping the `end.x`/`end.y`
statements, and reordering the `ICoord2D` declarations. `/G6` changed nothing;
`/G7` rewrote the body to 234 bytes.

That instance is still a wall, but the class is not: when one of the two
operands comes from a member of a padded VIEW STRUCT, re-spell that member as
a direct address dereference before parking it. `InGameUI::removeMilitarySubtitle`
came out 154 of 154 with one byte wrong -- retail `8b 04 07` (`mov eax,[edi+eax]`)
against `8b 04 38` -- and reaching the record pointer as
`*(Rec **)((UnsignedByte *)this + 0x818)` instead of `view->militarySubtitle`
encoded it retail's way. Same registers, same operation, same length either way,
and reversing the subscript does nothing (`i[p]` is `p[i]` to the front end).
Both spellings are ordinary tree idiom, so the choice looks free and is not.

**An allocator split.** `drawStaticTextText` came out 344 of 346. Retail spills
`tData` to `[esp+0xc]` and defers `push ebx / push ebp` past the early return,
which leaves a register free later; this toolchain keeps `tData` in EBX and
pays four bytes spilling a temp instead. Same immunity to declaration order.

When the last difference is which register got picked or how an equivalent
encoding was spelled, stop rewriting the source. Log it, and note that the
body, the layout and the convention were all correct — that is the part worth
keeping.

## A work packet's callee pins were matched by name, not followed

`reverse/zh_sweep/packets/0059eb90.md` proposes `AttackNugget::parse` at 98.6%
and lists, under "Callee pins (paste unresolved ones into
reverse/symbols.csv)":

```
??0AttackNugget@@QAE@XZ,0x000047A5 (already in the ledger)
```

`0x000047A5` is an incremental-link thunk. It jumps to `0x0059EB00`. The
ledger's `??0AttackNugget@@QAE@XZ` is at `0x001D6CD0`, reached through a
*different* thunk at `0x00022B42`. The sweep took the name from its Zero Hour
candidate, found that name already in the ledger, and marked the pin resolved
without ever following the thunk it had just printed.

`callee_pins` now asks that question of the decoded address instead, so the
same pin reads `(unpinned: this is the address retail calls; the ledger holds
this name at 0x001D6CD0; reverse/symbols.csv pins it at 0x00022B42)`. Over the
live queue that took 171 markings to 107. The lesson outlives the fix: a
marking says an address is pinned, never that the body is the function its name
promises.

Pasting that pin and building would have produced a byte-exact body under a
name whose constructor it does not call. **Disassemble the ILT target before
trusting a pin that arrives with a name attached**, especially for a body whose
whole shape is generic.

The second check is cheaper and would have caught it alone: look at what the
ledger already claims either side of the address. `0x0059EB90` is bracketed by
`MainMenuSmallScaleDownTransition::update`, `::skip` and `::init` — it is in
`GameWindowTransitionsStyles.cpp`, nowhere near `ObjectCreationList.cpp`.

### Read the data the body points at

The decisive evidence was the field-parse table. The body pushes one address
into `INI::initFromINI`, and at that address are **sixteen zero bytes** — an
empty table. Both reference candidates parse fields: `AttackNugget` has four,
`GameWindowTransitionsHandler::parseWindow` three. A candidate that parses
fields cannot be a body whose table is empty.

Two things make this readable. Absolute operands in the disassembly are **VAs**
while the ledger's `target_rva` is an **RVA**, so a data pointer needs
`- 0x400000` before it maps to a file offset; and the check that proves your
mapping is right is to resolve a string you already know, such as
`parseScreenRect`'s `" ,:=\n\r\t"` at VA `0x010F943C`.

## Two ways to finish a reference TU that locate.py gives up on

`reference/` sources that already own ledger rows are the cheapest lane in the
tree: the source is known-good, the compile flags are known-good, and anything
still unmatched in them is a body somebody has already proved this toolchain can
produce. `vertmaterial.cpp` went from 19 rows to 21 and `mapper.cpp` from 23 to
30 in one sitting, without a line of new C++.

### Find them by size, not by bytes

`locate.py` places a function by masked byte-scan, and it needs a
relocation-free run long enough to be unique. A body dense with pointer stores —
a constructor, a mapper `Apply` — has none, so it comes back **unlocated** even
though the function is right there in the image.

What it prints for those is the compiled **size**. Take the address span the TU
already owns from its landed rows, list every unclaimed dump in that span, and
match on size:

- `??0VertexMaterialClass@@QAE@XZ` compiled to 279 bytes; exactly one unclaimed
  279-byte dump in the span; exact on the first `explain_mismatch`.
- `??1VertexMaterialClass@@UAE@XZ`, 129 bytes, likewise.
- `?Apply@GridTextureMapperClass@@UAEXH@Z`, 863 bytes, likewise.

A size match is a *candidate*, not a result — the 274-byte candidate for
`Parse_W3dVertexMaterialStruct` disagreed at its first byte. It costs one
`explain_mismatch` call to find out.

### When several names match one address, ask the vtable

The same pass over `mapper.cpp` produced 32 more "exact" pairs that are worth
nothing on their own: **four** mapper classes compile `Apply` to the same 860
bytes, so four names matched each of eight addresses. Bytes cannot break that
tie — the bodies are identical, that is what folding means.

One slot away, the tie breaks completely:

1. Scan `.rdata` for the target address **as a VA** (`rva + 0x400000`). Each of
   the eight appeared in exactly **one** vtable slot.
2. Read the rest of that vtable and look every entry up in the ledger. Six of
   the eight held an already-named `Clone@X` — and `Clone` is class-specific
   because it constructs its own class, so the vtable holding `Clone@X` holds
   `Apply@X`.

That named six bodies, 5,160 bytes, on evidence that has nothing to do with the
matching bytes.

**Do not finish the job by elimination.** The last two were the last of four in
each group and elimination would have named them. It was not taken: elimination
is only as strong as the claim that the group is closed, and the slot that
looked like their `Clone` holds a 44-byte dump when every other `Grid*` `Clone`
in the family is 85 — so the window was misaligned and the "obvious" reading was
wrong. Anything whose only argument is *what else could it be* is a guess.

## The unwind-record transposition: a two-byte wall this toolchain cannot cross

Two unrelated functions, in unrelated subsystems, converted hours apart, came
out the correct size with every offset right and stopped on the identical
difference:

```
retail   lea eax,[esp+0x1c]   mov [esp+0x18],esp   mov ecx,esp
ours     lea eax,[esp+0x1c]   mov ecx,esp          mov [esp+0x18],esp
```

`mov [esp+N], esp` is MSVC recording the address of a **by-value class argument**
so the unwind funclet can destroy it. Retail writes that record *before* setting
up the constructor's `this`; this toolchain writes it *after*. Same two
instructions, same slots, opposite order.

- `?parseOCL@@YAXPAVINI@@PAX1PBX@Z` at `0x00201770` — 116 of 118 bytes.
- `?setPlayerName@EstablishConnectionsMenu@@QAEXHVUnicodeString@@@Z` at
  `0x004B2D10` — 135 of 137.

Between them it survived `/G5`, `/G6`, `/O1`, `/O2 /Oi`, `/Ox`, `-Os`, `-Ot`,
`-Oy-`, `-Gy`, `/EHa`, `/EHs`, `/EHac`, an inline versus declared-only
destructor, and replacing the implicit conversion with an explicit temporary.

**Recognise it and stop.** The signature is: correct compiled size, every
member offset and vtable slot already proven right, and the only diff a pair of
adjacent `esp` moves around a class argument passed by value. This is a compiler
*build* difference, not a port error — there is one cl.exe in
`build/toolchains/vs2003` and no second one to try. Any body that passes a class
by value to a function, where that class has a non-trivial destructor, is
currently two bytes out of reach.

Log it with everything the attempt did prove. `setPlayerName` established that
`m_playerNameControlNames` is a file-scope array and not a member — retail
indexes it as `mov ecx,[eax*4 + 0x012B66F8]` and never touches `this` — and that
`winGetWindowFromId` is `GameWindowManager` vtable slot `+0xDC`. Both of those
had to be right before the transposition was the only thing left standing, and
both are worth as much as the landing would have been.

- The `Snapshot::xfer` seeder family (`mov al,1` + a slot-ten call, 198 dumps)
  yields to a *parser*, not to eyeballing: decode each dump into (member call |
  sub-object hand-over | __cdecl helper | guard) and emit the TU from that IR.
  139 bodies landed byte-exact first try this way, in four passes, each pass
  adding one rule. The rule that paid most was treating a deferred `add esp,8`
  as scheduling noise rather than structure.

- A `// cl:` line REPLACES the flag list, it does not add to it. Two vector
  destructor TUs prove the cost: `-GX` gives retail's `cmp eax,0x80` dispatch
  between operator delete and the node allocator, while `/DNDEBUG /MD /EHsc`
  links the DLL CRT and routes the deallocation through an imported operator
  delete instead -- same C++, 40 bytes apart. If an STLport body is right
  except at its allocator call, suspect the flag line before the source.

- MSVC emits `??_G` (the scalar deleting destructor the vtable actually points
  at) ONLY alongside the vtable, and the vtable only where something
  instantiates the class. Declaring the virtual destructor does not emit it;
  neither does adding an inline virtual. A DEFINED CONSTRUCTOR does. Mark that
  constructor `// ??0X@@QAE@XZ present-unmatched` -- the commit hook only binds
  a marker that starts `// ?` and carries a real MANGLED name, so a readable
  `// X::X present-unmatched` is silently ignored and the commit is refused.

- When a data member is the RECEIVER of a call, bind it once as a local
  reference (`Thing &t = m_thing; t.f(x);`). Spelled `m_thing.f(x)` MSVC keeps
  `this` in the register and reads `this+K+field`; retail keeps the MEMBER's
  address and reads `+field`, while still folding the first read back onto ecx.
  It also orders `add ecx,K` before the argument push instead of after. Two
  unrelated families needed exactly this on the same day.

## Two STLport knobs a merged container body usually needs

Both are cl-line changes, so neither costs a full-tree gate, and both recompile
the TU so the byte gate re-verifies every row in it.

**The node allocator.** `PreRTS.h` and `Common/STLTypedefs.h` both force
`_STLP_USE_NEWALLOC`, which flattens a container node deallocation to a bare
`operator delete`; retail pushes the node SIZE alongside the pointer and calls
`__node_alloc::_M_deallocate` (0x0082E5F0). If a merged body's diff starts at a
container teardown -- `push eax / call / add esp,4` against retail's
`push 0xc / push eax / call / add esp,8` -- add
`/DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc` ahead of the reference
include path. On InGameUI.cpp it cost nothing: all 65 rows already landing there
still verified.

**Two node sizes in one TU.** `BFME_PARTICLE_LIST_NODE_TAIL` pads EVERY
`_List_node` in the TU by 0x20, and a destination can need it for one container
and not another: InGameUI.cpp's `list<SuperweaponInfo*>` copy constructor
allocates a 0x2C head node while its idle-worker lists are plain 12-byte nodes.
The two cannot share `list<>::clear()`. Give the 12-byte one a local node struct
and a local `clear()` spelled the way STLport spells it -- head re-read on every
iteration, `_STL::allocator<Node>().deallocate(p, 1)` for the free -- and it
reproduces retail's reload pattern exactly.

## A donor is unmergeable when its TU compiles the class under a different header

Two TUs can hold bodies for the same class under DIFFERENT layouts on purpose,
and the ledger can have both spellings matched at different addresses. When that
happens the donor cannot be folded, because one TU cannot emit both.

GameWindowFields.cpp is the worked case: 31 of its rows are marked for
GameWindow.cpp, but it compiles against `/Ireference/shims/gamewindow` (the true
BFME layout, m_instData@0x30) while GameWindow.cpp compiles the vendored header
(m_instData@0x2C). Putting the shim on the destination costs three compile
errors and, behind them, four matched rows: BFME changed `winSetNextInLayout`,
`winSetPrevInLayout` and `winSetLayout` from void to Int, and the ledger holds
BOTH `?…@GameWindow@@QAEXPAV1@@Z` (from GameWindow.cpp) and `…QAEHPAV1@@Z` (from
GameWindowFields.cpp) at different addresses. C++ cannot declare two members
differing only in return type, so adopting the shim deletes the void rows. The
merge also gains no file, since the donor keeps 14 rows either way.

Screen for it: compare the two files' `// cl:` include paths before planning a
partial donor, and grep the ledger for the donor's symbols under a second
spelling.

## Reaching a member as a MEMBER or through a local pointer picks the registers

Not a style choice. `view->field` off a hoisted local makes MSVC keep the
MEMBER's address in a register and read small offsets from it; `self->sub.field`
off a padded view struct makes it keep `this` and read `this+K+field`. Retail
picks one, and getting it wrong moves every offset in the body. The lesson
already recorded the receiver-of-a-call direction; this is the same lever for
plain reads, and it is worth one build before concluding anything about a body.
`GameWindow::winSetInstanceData` went from "every offset wrong" to "register
allocation only" on that change alone -- and then stopped there, which is the
honest end of it: retail spills `&m_instData` and holds both saved pointers in
callee-saved registers, this toolchain holds the address instead. Logged
`attempted`, not a dead end.

## A $L funclet row self-heals ONLY if it carries `parent=`

### And a funclet with NO candidate is a diagnostic, not a pin problem

`funclet_candidates` returning nothing for a row that HAS a `parent=` does not
mean the pin is stale -- it means no `$L` body in the parent's COMDAT matches
retail's bytes, so the merged body lays its TEMPORARIES out differently. That
fires before a single byte of the parent is compared, which makes it the
cheapest signal this lane has that a body carrying unwind states is wrong.
`LANAPI::addGame` is the worked case: every pin and offset was right and the
funclet row still refused, because the two `getName()` temporaries were not
being built the way retail builds them. Read it as evidence about the
temporaries and go back to the body.

A row whose `object-symbol=` names a compiler-local label (`$L51425`, `$T294`,
`$SG…`) is pinned to a per-compilation ordinal, and ANY edit to its TU can
renumber it. build.py already handles that -- `funclet_candidates` finds the
body again inside the parent's own COMDAT group (the section that also holds
`__ehhandler$<parent>`) and prints

    $L96540 was renumbered by an edit to this TU; the body is $L96533 in the
    object built now (stale ledger pin, not a byte mismatch)

-- but ONLY when the row's notes carry `parent=<mangled>`. Without it the
lookup returns nothing and the gate stops hard at `symbol not found in object`,
which is what makes such a destination look untouchable. THE FIX IS THE NOTE,
not a new pin: give the row a `parent=` and it never needs re-anchoring again.
`gen-alias` funclet rows are the ones that lack it; `gen-funclet` rows carry it
by construction. Screen a destination before choosing it:

    grep -F ",<destination>," reverse/functions.csv | grep 'object-symbol=[$]' \
      | grep -v 'parent='

Those are the only rows that will stop you. To work out the right `parent=`
(or when the parent's group holds look-alikes and the gate refuses to choose),
two filters, and neither is enough alone.

  BYTES NARROW IT. Compile, then for every `$…` label in the object compare its
  bytes against retail at the row's RVA with relocation sites masked on both
  sides (build.read_object_symbol_bytes returns the relocs). Funclets are 8-25
  bytes and generic, so expect several hits -- lanapi's three rows matched 2,
  10 and 2 candidates.

  THE COMDAT RECORD SETTLES IT. A funclet's section is
  IMAGE_COMDAT_SELECT_ASSOCIATIVE, and the section-definition symbol's aux
  record carries the associated section number at offset 12 with the selection
  byte at 14. Intersect the byte candidates with "associated with the section
  that defines the parent function" and exactly one survives:

      $L50814 -> $L50829   section 206, associated with 205 = RequestChat
      $L51425 -> $L51415   section 236, associated with 235 = addGame

  The parent comes from the row's own `parent=` note where it has one; a
  gen-alias row's prose note ("LANAPI::addGame second getName temporary") names
  it too, and when the association agrees with the prose that is two
  independent lines of evidence rather than adjacency. If neither filter leaves
  one candidate, STOP -- a wrong anchor seats a byte-matching row under an
  invented claim and no gate can see it.

Apply with `add_match.py --replace-existing --notes` (the sanctioned path for
rewriting a row), and write the `parent=` in while you are there so the next
edit heals itself. Where a TU has several such rows the gate cannot pass until
all of them are right, so the first N need `--no-verify` and one `./build.sh`
verifies the set.

## Half the cluster-marker files are naked dumps, and they are not merge work

Measured over all 887 files carrying a `readable body of` marker: **408 are
`__declspec(naked)` / `_emit` dumps and 479 are real C++.** A naked donor cannot
be folded -- the merge would add an `__emit` body to the destination and
`conversion_gate.py` refuses it -- so draining one means CONVERTING it first,
which is a different lane. `merge_cluster.py --list`'s per-destination count is
therefore an upper bound, sometimes a wild one: InGameUI.cpp listed 25 donors of
which 6 were mergeable. Screen a cluster before committing to it:

    grep -rlE "_emit|declspec\(naked\)" <the cluster's donors>

## reverse/symbols.csv duplicates itself on EVERY rebase over your own pins

Not once -- every time. `merge=union` re-applies your commit's appended pins on
top of a master that already has them, so a pin lands twice for each rebase that
crosses it. Check `tools/check_csv.py` after every `pull --rebase`, not just the
first, and repair with the ledger_io drop-exact-duplicate-payload pass described
above rather than `dedup_csv.py`.

## A mixed-ending file turns a one-line edit into a lift accusation

Symptom: you change a comment and `conversion_gate.py` rejects the commit with
"adds a naked/__emit body outside Code/gen_small/: __emit 0x81; (3967 such
lines)". Cause: 13 cluster destinations hold a CRLF `__emit` block inside an
otherwise-LF file — AIPathfind.cpp is 3967 CRLF against 11131 LF, and
OptionsMenu.cpp, GameText.cpp, InGameUI.cpp, ControlBarScheme.cpp,
ActionManager.cpp, Drawable.cpp and GameWindowManagerScript.cpp are the same
shape. Python's `read_text()`/`write_text()` translates on read and writes LF,
so a scripted edit silently rewrites every CRLF line and the diff really does
re-add them. The gate is right; the accusation is not. Rule: script every edit
with `read_bytes().decode("utf-8")` and `write_bytes(s.encode("utf-8"))`, and
check `git diff --stat` after — a whole-file rewrite means line endings, not a
bad edit. Same root cause as the ledger terminator hazard in tools/ledger_io.py.

## An access specifier can make a body unmergeable, and it fails like a compile error

Symptom: the gate says "symbol not found in object" rather than showing a byte
mismatch, so it reads like the callee is missing. Cause: MSVC encodes access in
the mangled name — Q public, I protected, A private — so a member the shim
declares `protected` emits `?name@Class@@IAE...` while the ledger row carries
the public `QAE` spelling. `AIUpdateInterface::setGoalPositionClipped` is
protected in reference/shims/aiupdatelayout/GameLogic/Module/AIUpdate.h and
public in the ledger. No view struct and no alias pin reaches an access
specifier; only a shim-header edit does, which is a wide change and a full-tree
build for one body. Rule: before starting a body, compare the row's access
letter against the shim's declaration. If they disagree, leave the donor and
annotate its marker.

## One agent per checkout, not one agent per cluster

Symptom: two agents merging disjoint clusters in the same working tree, and
whichever commits first silently takes the other's work. Not a conflict -- a
partial commit. Cause: there is one index and one reverse/functions.csv, and
`merge_cluster.py --apply` git-adds both the sources and the ledger. So the
committer's staged set contains the other agent's row repoints without their
sources, and the pre-commit gate only byte-verifies the sources THAT agent
staged, so it passes and leaves the ledger naming a file that does not hold
those bodies. Neither split is available either: commit your paths with the
shared ledger and you land their rows without their source; commit without it
and check_csv fails "source not in git" on your own donor deletions.
Partitioning by cluster is sound ACROSS clones or git worktrees, where each has
its own index and its own ledger; it buys nothing inside one checkout. Rule: one
agent per checkout. Give a second agent `git worktree add` (seed build/ by
hardlink and build/readability/counts.json by COPY -- two trees writing one
cache file is the hazard), or a different clone.
Corollary: authoring-without-applying is a safe way to keep working while
blocked on git ONLY if nobody else can commit your tree. `git commit` takes the
working tree for tracked files, so another agent's commit will sweep in edits
you deliberately left unstaged -- including markers removed in anticipation of
an apply, which leaves bodies that look claimed and are not.

## A fold can delete a compiler-generated symbol another matched row needs

Symptom: the merged body compiles clean and a DIFFERENT function, one you never
touched, fails the gate with "symbol not found in object". Cause: some matched
rows are not hand-written bodies at all -- they are symbols MSVC emits as a side
effect of an expression in the TU. Remove the last such expression and the
symbol stops being emitted and its row dies. Two proven shapes:

  memory-pool placement delete. `newInstance(Upgrade)` is the only pool-new for
  Upgrade in Player.cpp, and it is what makes MSVC emit
  ??3Upgrade@@SAXPAXW4UpgradeMagicEnum@0@@Z -- a matched 12-byte row at
  0x007EFFF0 claimed from Player.cpp. BFME allocates through the class's own
  operator new instead, so a faithful merge emits no newInstance and kills the
  row. Trading a 238-byte row for a 12-byte one is still going backwards.

  But CHECK THE GLUE'S EXPANSION before declining on this one: the rule is that
  the EXPRESSION disappears, not that retail reaches a different allocator.
  InGameUI::addNamedTimer holds its TU's only newInstance(NamedTimerInfo) and
  retail allocates with a plain `push 0x1c; call ::operator new` -- the shape
  that looks like the blocker. It is not: reference/shims/sweep's
  MEMORY_POOL_GLUE routes its placement operator new to ::operator new,
  MSVC inlines it to exactly that call, and still emits the COMDAT. newInstance
  stayed and all three rows held.

  inline COMDAT. becomingTeamMember's call to areModulesReady is the only one in
  the TU, and the COMDAT copy MSVC emits for that inline is the matched 7-byte
  row ?areModulesReady@Object@@QBE_NXZ at 0x002ED260, also claimed from
  Player.cpp.

Recoverable only if the reference expression can be kept beside the merged body.
It could not be here: the reference inline reads Object+0x295 and byte-matches
retail's standalone body at that address, while retail inlines a read of +0x341
in becomingTeamMember. Both are right -- they are different members, and the
donor's one name for both is doing double duty.

Pre-check before authoring a line, one command -- list the rows claimed from the
destination whose owning class is NOT the destination's, dropping STL noise:

    cls=Player   # destination basename
    grep -F ",Code/.../$cls.cpp," reverse/functions.csv | cut -d, -f1 \
      | grep -v "@${cls}@@" | grep -v "_STL@@" | grep -v '?\$'

The `??2X@@SAPAXI...MagicEnum` and `??3X@@SAXPAX...MagicEnum` hits are pool
new/delete pairs and are the ones that bite: Player.cpp carries five, Team.cpp
eight. Any body whose merge would stop emitting one of them is blocked before
you write anything.

## Two cl-line flags that look like a rewrite and are not

Both are one token on the file's own `// cl:` line -- not a header edit, so
neither costs a full-tree gate, and both recompile the whole TU so the byte gate
re-verifies every matched body in it and cannot hide a regression. That is what
makes them safe to reach for mid-merge.

`/D_STLP_USE_STATIC_LIB` missing makes every STLport call INDIRECT. Without it
STLport declares its exports dllimport, so a map's tree-increment compiles to a
six-byte `ff 15` through a pointer where retail has a five-byte direct `e8`. The
one-byte shift moves the whole tail and an otherwise byte-exact body reads as
unrelated. 565 cl lines in the tree carry the define, so its ABSENCE is the
anomaly -- suspect it whenever a merged body's diff starts at a container call.
A donor that has it merging into a destination that does not is the usual shape.

`/Ireference/shims/asciistringsetoutofline` is the fix when retail CALLS a
string destructor and the TU inlines it. The vendored header defines
releaseBuffer inline, so an AsciiString local's destruction compiles to a null
test, a refcount compare and an indirect dllimport free where retail emits a
plain out-of-line call. Three TUs already use this shim. Unrelated to the
m_data+4/+8 payload question, which stays parked.

## BFME's KindOfType is four entries longer than the reference's, past index 41

Two unrelated files agree, which is why this is worth propagating where the
individual readings were not:

    InGameUI::evaluateSoloNexus   MOB_NEXUS 46, IGNORED_IN_GUI 47   (ref 42, 43)
    PartitionFilterRepulsor::allow            INERT 0x58            (ref 0x54)

KINDOF_STRUCTURE is 7 in both, so the four extra entries are not at the front.

CORRECTION TO WHAT THIS ENTRY FIRST SAID. I wrote that a body passing a
reference constant "still byte-matches, because the number is an immediate".
That is backwards, and it is the error "The gate is blind to NAMES and
authoritative about IMMEDIATES" below was written to stop: `push 0x54` against
retail's `push 0x58` is a byte mismatch, so a MATCHED body proves its own
constants and the exposure is only unconverted bodies and new code. Read that
entry before sizing an alarm from this one.

What this entry is still for is the SHIFT itself: the value is proven, the
naming is not, so write the number and say where it came from rather than
inventing a name for the four entries BFME has and the reference does not.

## A member-order difference does not need the header changed

An initialiser list emits in the CLASS's declaration order, whatever order it is
written in -- so when BFME declares a class's members in a different order than
the reference, the reference constructor stores each argument into the wrong
slot and no list can fix it. Body assignments emit AS WRITTEN, and that is
enough: `PartitionFilterPossibleToAttack`'s constructor lands all 32 bytes from
the body form, vptr store included -- MSVC still sinks the vptr to the position
retail puts it, between the first and second member store. Works for POD
members; a member needing construction still wants the list, and then the order
really is the class's.

## The bytes prove values and offsets, never names

A donor's local enum, its member names and its comments are the ORIGINAL
author's reading. The byte gate validates none of them: a wrong name compiles to
the same instruction as a right one, so a body can be byte-exact and its
vocabulary still be invented. Three instances on one lane, each caught only when
a second body disagreed:

  a donor named the values it tests CMD_FROM_AI; a sibling donor in the same
  cluster named the same value CMD_FROM_SCRIPT, and the reference enum orders
  them PLAYER 0, SCRIPT 1, AI 2. Nothing settles it, so the merged code compares
  against the numbers and asserts no name.

  a donor called the pointer at Player+0x04 "the AI player". That file's own
  matched bodies already place the AI player at Player+0x220. Two fields cannot
  be one field, so the identification is unproven and was not propagated.

  a donor's enum gave LOCO_HOVER 2 and LOCO_WINGS 3. Drawable.cpp's
  calcPhysicsXform is a jump table over the whole range -- the only place the
  enum is visible at once -- and numbers them with the reference's own ordering,
  where 2 and 3 are TREADS and HOVER. Both donors byte-match; only the naming
  disagrees. The constants were renamed BFME_LOCO_APPEARANCE_2/_3 with the
  conflict written out, and the compiled bytes did not move.

Detection is cheap: when two clusters test the same numeric constant on the same
field, check whether their donors agree on the name BEFORE propagating either.
When they disagree, name the thing for what is proven -- the value -- and record
both readings. Renaming to an honest placeholder costs nothing at the gate,
which is the point: if it were expensive, guessing would be tempting.

## "symbol not found in object" has three causes and none is a byte mismatch

The message means the destination is not EMITTING the symbol the row wants. It
never means the bytes are wrong, so do not go reading the disassembly. Three
causes, each with a pre-check that costs one command:

  ACCESS SPECIFIER. MSVC encodes access in the mangled name -- Q public, I
  protected, A private. A member the shim declares protected emits
  ?name@Class@@IAE... where the ledger carries the public QAE spelling. Check
  the row's access letter against the shim's declaration.

  object-symbol NOTE. A row's notes column can pin it to a spelling that is not
  its name, and build.py reads THAT out of the object.
  ?WriteScriptsDataChunk@ScriptList@@...QAPAV1@H@Z carries
  object-symbol=...PBQAV1@H@Z -- PBQAV1@ is what `ScriptList *const []` mangles
  to, the donor's own declaration, where Scripts.h declares `ScriptList *[]` and
  emits QAPAV1@. Different parameter TYPES, not a top-level const the compiler
  would ignore, so the destination cannot produce it without a header change.
  1,662 of 4,402 cluster-donor rows carry one of these notes, so check it:
      grep -F "<symbol>," reverse/functions.csv | grep -o "object-symbol=[^;]*"

  A DELETED COMPILER-GENERATED SYMBOL -- the separate recipe above.

The object-symbol case has two shapes and only one is recoverable. A spelling
the destination COULD emit with the right declaration is a view problem. A
spelling that names a DONOR-PRIVATE symbol is not:
?preloadAssets@ControlBar@@QAEXW4TimeOfDay@@@Z carries
object-symbol=?bfme_preloadAssets_wrapper@ControlBar@@QAEXXZ -- a private
wrapper, and note the arity differs too (retail's body takes no argument). The
destination compiles the real ControlBar, which declares
preloadAssets(TimeOfDay), so it cannot emit a no-argument private wrapper
without a header change. The override is the correct mechanism, not a wart --
it is what lets the donor hold a body the real class cannot express.

## When a reference inline owns a row, and your body needs a different offset

Unmergeable, and it is worth recognising in one read rather than three builds.
The shape: the reference's inline expansion has its OWN matched row, byte-
matching retail's standalone body at some offset, while retail inlines a read of
a DIFFERENT offset into the body you are merging. Both offsets are right -- they
are not the same member, and the donor's single name for both is doing double
duty. Keeping the reference call to preserve the row therefore reads the wrong
field, and dropping it kills the row. You cannot satisfy both, and the standalone
row is the one already proven.
Seen twice: Object::areModulesReady (+0x295 standalone against +0x341 inlined in
becomingTeamMember) and Script::getAction/setAction (+0x28 standalone against
+0x20 inlined in ParseActionDataChunk, two rows at 0x00112980 and 0x00112970).

## Register allocation is sometimes source-controllable, so try once before parking

Two different phenomena get filed as "register allocation" and only one is a
wall. Telling them apart is worth doing because 123 entries in re_attempts.log
cite register allocation, and some of that pool is recoverable.

RECOVERABLE -- a chain that switches register one load too early. On
ControlBar::onPlayerRankChanged the walk switched from eax to ecx ahead of
retail's; routing the local-player fetch through an IN-CLASS accessor on the view
made it reuse eax down the chain exactly as retail does. Same lever as the
scheduling and jump-threading fixes, reaching further than expected.

A WALL -- two registers swapped wholesale. On Path::appendNode retail keeps the
parameter in esi and `this` in edi while the merged TU does the reverse, and the
swap also flips two adjacent stores. Three source shapes (a local view pointer, a
re-evaluated static helper, an inline setter) all produced byte-identical output.

FIRST, RULE OUT THE OTHER CAUSE -- an inlined same-TU callee and a register
tie-break look IDENTICAL in a byte diff: extra register traffic clustered around
a missing call. The tell is a call whose target is not one the body should make.
Screen it before reaching for the accessor: compare the definition line of every
named callee against your body's own line number, and treat anything defined
EARLIER in the TU as an inlining candidate. Getting this backwards costs a cycle
in each direction.

THE ACCESSOR NEEDS A GLOBAL AT THE HEAD OF THE CHAIN. It works by changing how
that global is fetched, which re-seats everything downstream --
ControlBar::onPlayerRankChanged starts at ThePlayerList. On a PURE MEMBER WALK
off `this` there is no global fetch for the extra inline layer to reorder, and
it cannot help: 0x002B6390 has the identical recorded signature and three shapes
(accessor on the middle hop, accessors on both, a reference instead of a
pointer) all produced byte-identical output.

AND CHECK IT IS NOT CSE FIRST. Five 83-byte twins logged as register allocation
were common-subexpression elimination of a member read: retail consumes m_begin
as a memory operand of the span subtraction so nothing holds it, then re-loads
it for the index, while MSVC materialises it into esi once and reuses it --
which then denies esi to `this` and cascades. The registers are the symptom. A
view class does NOT defeat this, even reading the index through a distinct view
type at the same offset, because MSVC folds on the address computation and does
not care that the struct type differs. Only volatile breaks it, at the cost the
existing note records.

So: try the accessor ONCE, and only on a global-headed chain. If the diff is a whole-body register swap rather than
a chain diverging at one load, park it. And a body already parked as
"register-allocation class" with an eax/ecx chain signature is worth one more
look, not a permanent skip.

## Retail rarely caches a global or a member across a call

Binding ThePlayerList to a local cost showSpecialPowerShortcut its match: MSVC
parked the local in ebp where retail loads the global three separate times.
Writing the global out at each use restored the match. The instinct to hoist a
repeated expression into a local is the wrong one here -- spell it out as often
as retail does, and let the compiler decide.

## An extent complaint on an already-matched row is about the body, not the row

Symptom: the build asks you to raise a row's target_size, and the row already
matched from its donor. Do not raise it. The row's extent was proven when the
donor landed; if the merged body now needs more bytes, the merged body is wrong
-- it is reaching past the function retail actually ends. Raising the extent
makes the complaint go away and buries the real cause under a row that now
claims bytes belonging to the next function.

Diagnostic, not a fix: raise the extent LOCALLY to see what the extra bytes are,
read them, then REVERT the extent before fixing the body. The bytes tell you
which construct over-ran -- usually an inlined tail retail calls out of line, or
a destructor the merged shape emits and retail does not.

## Sizing work off re_attempts.log overstates it, in three separate ways

The log is append-only and nobody prunes it, so a body that later lands leaves
its old "abandoned" note behind forever. A grep over it is not a work queue.
Measured on one slice -- entries citing register allocation with an eax/ecx
signature -- the count collapsed at every step:

    61  matching log LINES
    58  distinct symbols        (a symbol can be logged more than once)
    30  that are ledger rows    (the rest are narrative/capstone entries such as
                                 "pool-figures-and-two-more-refuted-pins", or
                                 symbols since renamed or retired)
    18  whose row is still on a dump -- the actionable pool

The other 12 had been converted since their note was written: a 21% false-parked
rate in one slice. Cross-reference before quoting a number off this file or it
overstates by about a fifth.

And do NOT filter on status=matched to find the unconverted ones. All 18 are
matched -- from Code/gen_asm/*.asm, because a dump matches by construction. The
discriminator is the SOURCE PATH, not the status column.

## A by-value string argument needs a VISIBLE copy, not an opaque one

The wall: retail passes AsciiString/UnicodeString by value, and the vendored
header's copy constructor is out of line, so the temporary is opaque and MSVC
schedules the unwind-slot store after the copy-constructor receiver load where
retail stores first. It gates roughly 114 of 511 clean cluster donors, so it is
worth getting right.

The fix is a per-file view, NOT a shim header and NOT a full-tree gate. But the
SHAPE decides it, and the obvious shape is the wrong one. A view with an opaque
copy -- declared, never defined -- removes the inlining and still leaves MSVC
hoisting the receiver's global and vtable across the call. Retail's compiler saw
a VISIBLE copy that delegates to a base constructor which is itself declared and
never defined:

    class BfmeStringArgBase { friend class BfmeAsciiStringArg;
    private: BfmeStringArgBase( const BfmeStringArgBase & ); ~BfmeStringArgBase(); };

    class BfmeAsciiStringArg { public:
        BfmeAsciiStringArg( const AsciiString &that )
        { ((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
              *(const BfmeStringArgBase *)&that); }
        ~BfmeAsciiStringArg();
    private: char *m_text; };

Opaque and visible-delegating are both different from the reference header and
only the second matches. This is "temporaries schedule by how visible their type
is" applied in the right direction -- and the shape is not invented, it is what
the sibling donors' own shims already spell, which is why they match and a
merged body does not.

Cost: a few additive aliases at addresses already pinned under the real string
spellings, each reached through a call so the rel32 proves it. And the cost is
ZERO for any further call site whose callee is virtual, because a view's virtual
signature can change types freely -- one body matched first try with no new pins
at all.

AND THE CONVERSION AT THE CALL SITE MUST BE IMPLICIT. `f(Arg(x))` makes MSVC
materialise the temporary in a NAMED LOCAL and pass its address; `f(x)` builds
it directly in the argument slot, which is what retail does. So the callee has
to be declared under a name of its own rather than as an overload of the real
one -- an overload taking the real string type is an exact match and wins,
leaving the view unused. `LANAPI::SetLocalIP` is the worked case: same bytes
either way up to that point, and the whole prologue and temporary land once the
call reads `bfmeResolveIP(localIP)`.

A WARNING ABOUT THE TU-WIDE STRING SHIMS in a file that carries funclet rows.
`/Ireference/shims/asciistringsetoutofline` fixes an inlined destructor, and in
lanapi.cpp it changes codegen enough that a funclet row on a body you are NOT
editing stops finding a byte-equal candidate in its parent's COMDAT. Check for
`object-symbol=$` rows in the destination before reaching for one.

## "It did not match" is a deferral, not a dead end

Read tools/re_log.py's status doctrine (lines ~40-70) BEFORE recording a
verdict. The distinction it draws is not bookkeeping:

  DEAD_END_STATUSES -- no-match, refuted, identity-suspect, mis-anchored -- are
  findings about the BOUNDARY. Re-serving cannot fix them.
  DEFERRED_STATUSES -- blocked, attempted, abandoned, partial -- are properties
  of the ATTEMPT. Every retail byte needs a C++ equivalent, so "I could not
  match it" can only ever mean "not this session".

Conflating them retired 535 symbols the project cannot finish without. An
SEH-frame, register-allocation, CSE or inlining-depth wall is a deferral: it was
usually measured by an agent working the body SOLO, and the land rate is 19.5%
solo against 46.5% with ten or more siblings landed, so the finding is stale by
construction the moment its file drains.

`partial` is the one to reach for when the attempt produced something -- it banks
the body under reverse/attempts/<rva>.cpp and serves it beside the candidate. The
tool REFUSES partial without --stash and --score, because a row describing a near
miss with no body measures worse than recording nothing.

Corollary for anyone sizing work off the log: `note`, `evidence`, `lever`,
`correction` and unrecognised words are ANNOTATIONS, not verdicts, and an
unrecognised status leaks a candidate rather than burying one. So a grep counts
things the tool does not. Use re_log.is_dead_end(), not text.

## The first build after --apply can look like a pass it never ran

`merge_cluster.py --apply` repoints the ledger rows; it does NOT clear the
donor's `present-unmatched` marker. verify_source_claims reads that stale
annotation and fails BEFORE the byte comparison runs, so the output you get is
about the marker, not the bytes -- and the line it prints,

    byte-verified matched from this file but still carries an unmatched marker
    (stale annotation)

reads like a pass. It is not evidence of a byte match; it only means the row now
names this file while the comment still says otherwise. Only the `Functions:`
line is evidence.

Clear the marker first, then build. Two agents hit this independently, one of
them on three separate folds before spotting it, and one body (Object::setLayer)
did turn out to match once the marker was dropped -- which is the trap: the
message is sometimes right by accident.

## Accessor disagrees with a body: is it a SECOND member or a shifted class?

Two classes now carry two links where the reference carries one -- LANGameInfo
with the accessors on +0x360 and the bodies walking +0x398, Script with the
accessors on +0x28 and the parser using +0x20. The tempting fix is a view that
moves the body onto the accessor's offset: it makes the row match and silently
merges two distinct members, which is a green build hiding a structural error.

There is a cheap mechanical test, and it does not need a view or a build.
Collect the offsets the class's MATCHED TINY ACCESSORS prove -- they are
authoritative about their own offset, being byte-verified -- and look at the
shape of the disagreement:

  * A SHIFTED CLASS shows a RUN of consecutive members displaced by the SAME
    delta. That is a reliable positive. GameWindow: m_status, m_size,
    m_userData and m_instData are every one of them exactly +4 from where the
    vendored class puts them, because BFME has a member at +0x04 the reference
    does not. Four coincidental second members all exactly four bytes apart is
    not credible; one inserted member is.

  * ANYTHING ELSE NEEDS THE LIVENESS TEST, and a gap in the accessor set is
    NOT enough on its own. The question is whether BOTH offsets are live IN
    RETAIL. Two members means retail uses both; one misplaced member means
    retail uses only its own and ours is simply wrong.
    LANGameInfo passes: +0x360 is proven by get/setNext and +0x398 by three
    matched bodies -- removeGame, LookupGameByListOffset and addGame.
    Drawable::getID FAILS it and is the counter-example that matters: retail
    reads +0x100, this tree reads +0x8C, the accessors either side agree
    (getInstanceMatrix +0xD4 and getFullyObscuredByShroud +0x148 are both
    matched from Drawable.cpp at retail's offsets), and +0x100 sits in a gap
    -- so the gap heuristic alone would have called it a second member. It is
    not: NO retail accessor reads +0x8C and nothing else claims it. One member
    declared in the wrong POSITION.

So: a RUN at a constant delta means the class is short and the header is wrong.
Everything else means go and check whether retail uses OUR offset anywhere --
an accessor reading it, or a matched body. If nothing does, our offset is the
error and there is only one member.

Script sits in the middle and should be treated as unresolved: its +0x20 has no
accessor and no matched body, only retail's own bytes in the one function that
cannot land. That is good evidence the offset is real and NOT evidence that
+0x28 and +0x20 are two members rather than one relocated one.

The remaining doubt on the second-member reading is worth stating: an offset is
strongest when a MATCHED row proves it. +0x398 has three (addGame's siblings
removeGame and LookupGameByListOffset among them). Script's +0x20 has none --
only retail's own bytes, read from the target -- because the body that uses it
is the one that cannot land.

## Before adding a shim for a header, check whether the tree OWNS that header

Four separate requests for a new shim in this lane dissolved on an artefact
the repo already had. The last one is the cleanest example, and it
generalises past strings.

CachedFileInputStream::open would not land because BFME's
CompressionManager::decompressData takes a `const void *` source and the
call site emitted the non-const mangling. The apparent fix was a shim
carrying a corrected Compression.h. But
Code/Libraries/Source/Compression/compression.h is OUR copy, byte-identical
to the reference bar one provenance comment, and DataChunk.cpp is the ONLY
file in the tree that includes "Compression.h" -- it was reaching the
reference copy because our directory was not on its include path. Correct
the header we own, put our directory first, done. A shim would have
duplicated a header already in the repo to fix a one-word error in it.

THE TELL, and it is the reusable part: a MATCHED TU carrying a local
workaround for a shared declaration is evidence about the declaration, not
a trick to copy. CompressionManager_decompressData.cpp reproduces retail
byte for byte and has to declare its own `class CompressionManager` with
the const signature to do it. That is retail telling you the shared header
is wrong. Before writing a shim, grep for who else includes the header --
if it is one file, or none, fix the header.

## Read the whole shims directory before asking for a new one

They are named for the TU that motivated them, not for what they do, so the
general one does not look general. I surveyed five AsciiString shims, concluded
none had both the 8-byte header and an out-of-line copy constructor, and asked
for a sixth. `campaignmanagerascii` has both and was already on 71 TUs: it is
StringBase-based, so its 8-byte `Header` comes from `string_base.h` rather than
from a field of its own -- which is why grepping the shims for the ZH
`m_debugptr` marker misses it -- and its copy constructor delegates to
`StringBase<char>::StringBase(const StringBase<char> &)`, declared private in
string_base.h and never defined, so the delegation compiles to a CALL. Same
declared-never-defined mechanism as the by-value view.

Two mechanics when you reach for it:

  `/ICode/Libraries/Source/WWVegas/WWLib` goes LAST on the cl line.
  string_base.h resolves from anywhere on the path, but WWLib ahead of the
  sweep shim shadows headers sweep needs and snmp.h stops compiling.

  Its `compare(const AsciiString &)` is the INLINE length-bounded memcmp retail
  spells; its `operator==` forwards to a StringBase one that is declared and
  never defined, so `a == b` compiles to a call retail does not make. Write
  `a.compare(b) == 0`.

And know the price before taking it: it makes AsciiString's copy constructor
THROWING (an undefined declaration is assumed so), which can put an EH frame on
anything that copy-constructs a class holding one. `SpecialPower.cpp` absorbed
that with all 13 rows intact; `W3DModelDraw.cpp` did not -- see the
`_Construct` / `push_back` pair in re_attempts.log for the two-sided wall.

## Four string levers, four symptoms: pick by which operation retail calls

"Retail calls it, we inline it" has four different string shapes and four
different fixes. They are not interchangeable and reaching for the wrong one
costs a build each time. All four are per-file cl-line or TU-local changes, so
none costs a full-tree gate:

  inlined DESTRUCTOR  -> /Ireference/shims/asciistringsetoutofline   (5 TUs use it)
  inlined COMPARE     -> a TU-local view of retail's eight-byte header; the
                         include-path shims do NOT substitute, because they give
                         the right header size and a strcmp-based compare where
                         retail does a length-bounded memcmp
  inlined CONSTRUCTOR -> /Ireference/shims/campaignmanagerascii      (71 TUs use it)
  inlined str() AT +4     -> /Ireference/shims/asciistring8                (5 TUs use it)
                             when the single wrong instruction is `add eax,4`
                             where retail has `add eax,8`
                         plus /ICode/Libraries/Source/WWVegas/WWLib for string_base.h
  inlined str() at +4 -> /Ireference/shims/asciistring8              (6 TUs use it)

The fourth is the `add eax,4` against retail's `add eax,8` that the m_data+8
section below parks as a tree-wide change. It IS a tree-wide change if you want
all 87 sites at once -- full gate, and 403 funclet rows to re-anchor. But a
SINGLE body stuck on that one instruction does not need any of that: putting
/Ireference/shims/asciistring8 on that file's own cl line gives the eight-byte
header for that TU only, and the file's existing rows re-verify in the same
build. UpgradeCenter::findUpgrade came home that way with sixteen prior rows
unchanged. Reach for it whenever a diff is `83 c0 04` against `83 c0 08` with the
empty-string fallback at 0x0107388B beside it; the parked section is about the
tree, not about your body.

Note asciistringsetoutofline does NOT fix an inlined constructor -- it leaves
that one inline. And campaignmanagerascii works for the same reason the by-value
view does: its constructor is a VISIBLE inline delegating to a StringBase
constructor declared and never defined. Two agents reached that shape from
opposite directions, which is the strongest evidence the tree offers about it.

The same shape rule governs a LOCAL string, not just a by-value argument. This
tree already spells retail's one-dword string as BFMERetailAsciiString in
ControlBar.cpp and elsewhere with a DECLARED-ONLY literal constructor, and that
schedules the unwind-slot store after the receiver load. Make it delegate
visibly to an undefined base and it matches. Those existing call sites are not
scheduling-sensitive, so nothing there is wrong today -- but copy the shape, not
the spelling.

And know this failure signature before it costs you a build: a body with a local
string has an unwind funclet of its own, and changing the local's type makes the
funclet reference the inline destructor MSVC emits. That fails as an UNRESOLVED
RELOCATION -- `e9 00 00 00 00` -- which reads like a broken build and is really a
missing alias for the destructor ILT the funclet jumps to. One additive pin fixes
it. It is not a byte mismatch and there is nothing wrong with the body.

A fourth symptom is NOT a string problem at all: if the residue after the string
construction matches is an extra vptr store (mov dword ptr [esi+4] right after
the vtable store), that is a second vptr the vendored hierarchy carries and BFME
does not. Base and vptr stores come from the CLASS, so no .cpp reaches them, and
initializer order is not the cause -- base-first and member-first are
byte-identical. Revert the shim with the body; a TU-wide compile change that
buys nothing is worse than no change.

## A shared header's vtable can be wrong, but a matched row proves its own slot

BFME's GameClient vtable is not the vendored one: findDrawableByID is slot 11
(+0x2C) where GameClient.h puts it at slot 8 (+0x20), and destroyDrawable is
slot 24 (+0x60) against slot 19 (+0x4C) -- three BFME virtuals ahead of the
first and two more between them. The header already carries three
bfmeVirtualStub slots for a different part of the same table, so the divergence
is known and this part is simply not covered.

Bound the alarm before acting on it. A body that BYTE-MATCHED cannot be
dispatching through the wrong slot: the call encodes the offset, so `ff 50 20`
against retail's `ff 50 2c` is a mismatch and the gate would have refused it.
Every matched row is therefore proof about its own dispatch. The exposure is
UNCONVERTED bodies -- which will hit it as a byte mismatch when someone attempts
them, exactly as intended -- and any new code written against the header.

So this is not a fire to put out; it is a header correction worth doing
deliberately, and a per-file view reaches it meanwhile.

## When a merged body's diff starts at a container teardown, try the node allocator

PreRTS.h and STLTypedefs.h force _STLP_USE_NEWALLOC, which flattens a node
deallocation to a bare `operator delete` where retail pushes the node size and
calls __node_alloc::_M_deallocate. The sanctioned opt-out is per-file and costs
nothing:

    /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc

on the file's own cl line. It recompiles the TU, so every matched row in it
re-verifies -- 65 of them on the first file to use it. Try this before anything
else when a diff opens at a container teardown.

Related trap in the same area: BFME_PARTICLE_LIST_NODE_TAIL pads EVERY
_List_node in a TU by 0x20. If one row in the file needs that padding and
another needs plain 12-byte nodes, they cannot share list<>::clear() -- give the
12-byte one a local node type and a local clear() spelled the way STLport spells
it.

## To correct an allocation size, use a standalone view -- not derive-and-pad

Deriving from the vendored class and padding it to retail's size gets
`push <size>` right and still does not reproduce `new T(...)`. The derived
constructor is inlined, so only the BASE constructor is called, and MSVC will
not reuse that return value as the derived pointer -- it parks the block in an
extra callee-saved register retail does not need.

A STANDALONE view at retail's size, with its constructor DECLARED AND NEVER
DEFINED, has a constructor of its own and matches exactly. Cost is one additive
alias per constructor, at the address already pinned under the real spelling and
reached through a direct call, so the rel32 proves it.

Note this is the same shape as the by-value string argument view and the
campaignmanagerascii constructor: declared-never-defined is what makes MSVC
emit the call retail emits instead of expanding something in its place. Three
different problems, one mechanism.

## symbols.csv is sorted, and its header sorts AFTER a mangled name

Inserting programmatically into reverse/symbols.csv: the header line
`name,address,notes` sorts after any `??0...` symbol, so a naive sorted insert
places the new row ABOVE the header and check_csv rejects the file with "bad
header". Start the scan at index 1 and keep the header pinned at the top.

## A paired #line lets a __LINE__ body move into a shared destination

Retail pushes its own __LINE__ into GameLogicRandomValue and friends, and the
reference file and this port have drifted apart, so a body carrying one appears
unmergeable: a `#line N` to satisfy it would renumber everything BELOW it in a
shared destination. That reasoning is why several donors kept their own TU.

It is wrong. Emit the `#line` for the statement, then a bare `#line N` AFTER it
restoring the physical numbering, and nothing below moves. The presumed FILE
stays as retail has it. TurretAIIdleState::resetIdleScan landed this way;
LifetimeUpdate.cpp and SlowDeathBehavior.cpp each still have one open, and
anything else parked on "a #line would renumber the file" is now foldable.

## Check a donor's remaining ROW COUNT after --apply, not the "kept" line

`--plan` reports a donor with a second destination as kept, which is right when
it has rows left over. It is misleading when the donor's ONLY row is the one you
just moved: the file survives owning ZERO rows and the gate refuses that
outright -- "source presence is not progress".

INI_parseObjectCreationList.cpp is the shape to recognise: it carried TWO
markers for ONE body -- the full mangled spelling naming ini.cpp and a truncated
`?parseObjectCreationList@INI@@` naming INI_stl.cpp -- and both destinations
hold a copy of the function. So the donor looked multi-destination and was not.
After --apply, count the donor's rows:

    grep -c ",<donor>," reverse/functions.csv

Zero means delete the donor rather than leave it.

## A bare `// ??0Class@@` marker binds by PREFIX, so landing one ctor staleens the other

The claims hook matches a marker comment by prefix. Write both a default and a
copy constructor as the bare `// ??0Class@@` and they are the same marker to it,
so landing one leaves the other's marker pointing at a body that is no longer
there. Give the survivor its FULL mangled name.

Related, when a batch refuses: merge_cluster compares declarations only across
the `--only` set, so two donors that declare one member differently will block
an --apply that names both and go through cleanly in two batches -- provided the
destination has already reconciled them.

## The gate is blind to NAMES and authoritative about IMMEDIATES

These are opposite properties of the same check and this lane has confused them
three times, in both directions. Get it right before you size an alarm:

  A NAME is unvalidated. A row's symbol, a member name, an enum spelling, a
  function identity -- all compile to the same instruction whether right or
  wrong. `identity-suspect` findings, mis-anchored rows and reversed enum names
  all live here, and only a second body disagreeing exposes them.

  AN IMMEDIATE IS PROVEN. `isKindOf(KINDOF_INERT)` compiles to `push 0x54`. If
  retail pushes 0x58, the bytes differ and the row does not match. The same goes
  for a vtable slot (`ff 50 20` against `ff 50 2c`), a chipset tier compare, a
  structure offset, a frame size.

So when you find a renumbered enum, a shifted vtable or a changed constant, the
exposure is NEVER the matched bodies -- those are self-proving. It is
    - bodies not yet converted, which will fail as a byte mismatch when someone
      attempts them, exactly as intended, and
    - new code written against the vendored header.
That is a header correction to schedule, not a fire to fight. Say which of the
two you mean when you report one, because "N call sites are testing the wrong
bit" reads as the first and is usually the second.

Worked examples on this lane: BFME's KindOfType has four entries the reference
lacks (MOB_NEXUS 46 against 42, IGNORED_IN_GUI 47 against 43, INERT 0x58 against
0x54, PROJECTILE bit 25 against 22), GameClient's vtable is off by three and five
slots, and DC_GENERIC_PIXEL_SHADER_1_1 is 3 where the header numbers it 9. All
three were reported as tree-wide hazards; all three are bounded the same way.

## BFME ships BOTH module layouts -- a family lever is not a family fact

48 donors carry a module-constructor marker (the first screen said 23 -- it
grepped the full signature and a third of markers name no signature at all, so
it could not see them). Every one
holding a constructor byte-identical to what its destination already spells.
What keeps them apart is the module hierarchy: retail's Module has no
MemoryPoolObject base, so BehaviorModule spans 0x0C and the second vtable store
lands there, while the wide layout puts a fourth vptr at +0x04 and shifts
everything. reference/shims/sweep/Common/Module.h carries the switch as
BFME_MODULE_NO_MPO and thirty-odd files already set it.

Screened one file at a time -- add the define, require the destination's OWN
rows to stay green, then diff with explain_mismatch:
    6 land    (CashHackSpecialPower, GrantUpgradeCreate, OCLSpecialPower,
               BoneFXDamage, SupplyWarehouseCreate, W3DTreeDraw)
   10 turn their destination RED, so their module layout genuinely is the wide
      one (SlowDeathBehavior, WorkerAIUpdate, BoneFXUpdate, BattlePlanUpdate,
      StructureCollapseUpdate, ToppleUpdate, SupplyWarehouseDockUpdate,
      OCLUpdate, GarrisonContain, BridgeBehavior)
    6 miss for unrelated reasons, 3 are genuinely different bodies, 1 has no
      marker pair to consume.

SETTING THIS DEFINE TREE-WIDE WOULD BREAK TEN FILES. The screen is per-file and
cheap; the generalisation is false. Apply the same caution to any switch that
looks like it characterises a family.

CORRECTED: an earlier reading of three misses as "retail stores a FOURTH vtable
the vendored hierarchy has nowhere to put" was wrong, and wrong in an
instructive way. Retail stores four vptrs, at +0x00/+0x0C/+0x10/+0x18; this tree
stores four, at +0x00/+0x04/+0x10/+0x14. Nothing is missing and nothing is
reordered -- the sub-object at +0x00 spans 0x0C in BFME against 0x04 here, eight
bytes of data the vendored BehaviorModule does not declare, and bases two and
four both slide by that eight.

The error came from screening those three WITH the define on. The define lands
base two correctly AND DELETES base four, so three stores showed against
retail's four and read as a missing base -- an artifact of the experiment read
as a fact about retail. DO NOT READ A COUNT DIFFERENCE OFF A RUN WHOSE FLAGS
CHANGE THE COUNT. It surfaced because a fourth family member, invisible until
the marker fix, screens at 2 diffs WITHOUT the define with all four stores
present: one body disagreeing with a three-body conclusion.

The actionable statement is "BehaviorModule is eight bytes bigger", not "find a
missing interface base".

## The `// cl:` line must be the FIRST line of the file

Put an explanatory comment above it and every flag on it is silently dropped --
no error, no warning, and the body then fails for reasons that have nothing to
do with the edit you made. Explanations go BELOW.

## An ordered call sequence names its unnamed members, like a vtable does

W3DRoadBuffer::loadRoads's donor called its seven callees loadRoadsHelper0
through loadRoadsHelper6 -- honest and worth nothing. The DESTINATION's source
calls seven named methods in a fixed order, and four of the seven already
resolved to ledger-named W3DRoadBuffer members at exactly the positions the
source puts them (insertTeeIntersections fourth, insertCurveSegments fifth,
insertCrossTypeJoins sixth, preloadRoadsInVertexAndIndexBuffers seventh). Four
independent agreements in a row fix the other three BY POSITION, and all three
bodies sit inside the class's own address span:

    ?clearAllRoads@W3DRoadBuffer@@QAEXXZ        ILT 0x000336F9 -> 0x00706E60
    ?addMapObjects@W3DRoadBuffer@@IAEXXZ        ILT 0x0002001D -> 0x007100C0
    ?updateCountsAndFlags@W3DRoadBuffer@@IAEXXZ ILT 0x00010B5E -> 0x00705260

Two of the three had been carrying nothing but a d_00xxxxxx dump name. This is
the "ask the vtable" argument pointed at a CALL SEQUENCE: when a body's callee
list is ordered and most of it is already named, the remainder falls out. The
agreements have to be independent and in order to count -- one or two matches
is coincidence.

## Triage a donor WITHOUT applying it

Cheapest screen there is, two compiles: clear the marker in the destination,
require the destination's own rows to stay green, then run
`explain_mismatch --rva/--size/--source`. You get the exact distance without
touching the ledger, so near-misses sort themselves and a body that needs
AUTHORING rather than repointing (its destination has no definition at all)
shows up before you spend anything.

CAUTION: a match prints "OK: bytes match" and NO Disassembly section. Do not
detect a match by counting diff lines -- an ERRORED run also has zero. Match on
the success string.

This screen found the module-constructor 6/10/6/3 split, two bodies sitting one
instruction from home, and a marker asking for authoring rather than a fold.

## The m_data+8 header is cheap PER FILE, even though the tree-wide change is not

The tree-wide correction really does cost a full gate plus a 403-row funclet
re-anchoring, and this file parks it on that basis. But that is the TREE-WIDE
question. A single body stuck on one instruction -- `add eax,4` where retail
inlines str() as `add eax,8` -- can be unstuck today: put
/Ireference/shims/asciistring8 on THAT FILE's own cl line. Five files already
carry it. UpgradeCenter::findUpgrade landed that way with no full gate, no
re-anchoring, and all 16 pre-existing rows in the destination re-verified.

So: park the tree-wide change, but do not read that as parking the bodies. Check
whether your residue is exactly the +4/+8 difference before deferring one.

## A view's constructor may need throw()

Without it MSVC wraps the allocation in an SEH prologue purely to free the block
if the constructor throws, and retail -- which has no unwind funclet there --
does not. Usually this is a couple of bytes. On LocomotorStore::newOverride it
was the difference between an entire prologue and none. Add `throw()` to a view
constructor whose retail caller has no unwind state.

## A vtable slot read off ONE call site is a guess

Three AIUpdateInterface/DozerAIInterface slots move together: getDozerAIInterface
+0x13C against the vendored +0xFC, isIdle +0x180 against +0x13C -- isIdle landing
exactly where the header put getDozerAIInterface, which is what an interface that
GAINED sixteen entries ahead of them looks like, not one that was reordered.
getMostRecentCommand goes the other way, +0x14 against +0x180, and is a different
interface saying the same thing about DozerAIInterface.

Two of the three were assigned backwards on the first attempt and the gate caught
it. The rule is the same one that names members from an ordered call sequence:
one agreement is a guess, and the whole sequence has to line up before you can
claim any of it.

## $L-anchored rows break on ANY codegen change ABOVE them in source order

The 403-row re-anchoring cost is usually quoted against the tree-wide string
header, which makes it read as a cost of BIG changes. It is not. The labels are
assigned across the whole TU during codegen, so a forty-slot view class is
enough to renumber them.

This entry used to say "any added DECLARATION", which named the wrong variable
and was falsified: a plain function-pointer typedef -- no class, no members, no
emitted code -- renumbers them too. The rule is POSITION, not construct. $L
numbering runs across the whole TU in source order, so any codegen change ABOVE
a pinned funclet renumbers it, and that is why a `#line` directive stays free:
it is a contrast, not a coincidence. The useful corollary is the one the old
wording hid -- a view added BELOW every pinned row does not renumber it, so
check where the pins sit before concluding a TU is frozen.

(Aside for anyone reaching a vtable slot through a function pointer: MSVC 7.1
rejects `__thiscall` on a function-pointer type with C4234, so the call has to
be `__fastcall`. That is call-compatible for a no-argument method and has
nothing to do with the renumbering.)

GameSpyInfo::updateStagingRoom is one instruction from home (addStagingRoom is
vtable +0xA0 in BFME against the vendored +0x84, and the by-value copy and its
unwind slot already match). The view that reaches +0xA0 renumbers PeerDefs.cpp's
labels, and uw_00c40e10 / uw_00c40e8a are anchored on them: one fails its byte
compare and the other can no longer be told from two siblings, so the gate
refuses to guess.

COMMENTS ARE FREE; CODE IS NOT. Before adding a view to a TU, check:
    grep -F ",<destination>," reverse/functions.csv | grep -c 'object-symbol=[$]'
and if it is non-zero, re-anchor those rows FIRST.

Re-anchoring is usually just a NOTES fix, and `parent=` alone is not it.
build.py re-finds a renumbered funclet from its parent's __ehhandler group --
that is the "Funclet pins: N row(s) verified past a renumbered $L label" line --
but is_funclet_row() (tools/build.py:920) gates on the notes containing
**gen-funclet**, AND on a parent=. A row with parent= but no gen-funclet never
reaches the healer: it dies with "symbol not found in object: $L<n>", which
reads exactly like a hard wall and is why lanapi.cpp was called frozen for
weeks. It was one word. `gen-alias` and `gen-funclet` are not exclusive -- an
ICF-twin alias claim can also be a $L-pinned funclet, and then the notes must
say both (keep `gen-alias;` leading, check_csv enforces that prefix).

Exactly three rows tree-wide are gen-alias + $L + parent=. lanapi's is fixed;
?a_00bfd4b8@@YAXXZ (UpgradeNamesPlacementCleanup_00BFD4B8.cpp) and
?a_00c52ae0@@YAXXZ (VectorClassArrayPlacementCleanup_00C52AE0.cpp) are latent
the same way. If either destination looks frozen, this is why.

## A vendored class that is too SMALL needs bytes, not a new class

"Retail's frame is 0x70 where this tree's is 0x64, and that is a
class-shape difference, not a field view" is a verdict Player.cpp carried
against disableRadar and enableRadar. The diagnosis was right and the
conclusion was wrong: both land byte-exact, and so does removeRadar.

A local whose class is twelve bytes too small does not need the class
changed. It needs twelve bytes:

    struct BfmeAudioEventStorage
    {
        BfmeAudioEventStorage( const AudioEventRTS &src ) : e(src) { }
        AudioEventRTS e;
        UnsignedByte _bfme_tail[12];
    };

The member sits at offset 0, so its address, constructor and destructor are
unchanged and every call in the body stays what it was; only the frame
grows. THE CONSTRUCTOR IS LOAD-BEARING. Declaring the storage and then
assigning (`BfmeAudioEventStorage x; x.e = src;`) default-constructs and
then assigns, where retail COPY-CONSTRUCTS in one call. Taking the source
by const reference and initialising the member in the initialiser list is
what reproduces retail's single call.

This reaches any body blocked only by a vendored class smaller than BFME's.
It does NOT generalise to the class: retail's addRadar reserves 0x60 where
the other three reserve 0x70, sets its EH frame up in the other order, and
sits at 0x000FB3F0 well away from them at 0x000CC0B0-0x000CC2C0. The twelve
bytes belong to the frame those three share, not to AudioEventRTS
everywhere -- so measure the frame per body rather than padding on faith.

## Screen a whole cluster with ONE build, before applying anything

Repointing a row to find out how close it is costs an apply, a build and a
revert, and leaves the ledger dirty if you die between them. It is
unnecessary. After ONE build of the destination, read each candidate's
symbol straight out of the .obj, mask the relocation sites, and compare
against retail:

    build.read_object_symbol_bytes(obj, symbol, size)  vs
    build.read_target_bytes(rva, size)

Twenty InGameUI candidates ranked in a single build, no applies. It put
addMessageText (64.9%) at the top -- it landed 388/388 -- and correctly
warned off update, which agrees on 19.3% and fails at offset ZERO on an
`and esp,-8` aligned frame nothing in the body explains.

A 100% SCREEN IS NECESSARY, NOT SUFFICIENT. The screen masks relocation
sites, so it cannot see a call that resolves to the WRONG FUNCTION -- the
gate resolves those and will reject what the screen passed.
DataChunkInput::openDataChunk screens at 100% and fails: retail's
`AsciiString("")` calls RVA 0x00102D90, an unidentified gen-dump that reads
[ecx] and compares [m_data+0xC] against its argument -- a `set`, not the
constructor at 0x00888BC0 the tree resolves to. When a 100% screen fails
the build, read the relocation SYMBOLS out of the object and check each
against what retail's call target actually is.

Read the COMPILED SIZE beside the percentage. Once the two sizes differ the
percentage stops moving even as you fix real things, because every byte
after the first divergence is compared against the wrong position. On
addSuperweapon three separate offset fixes each left it at exactly 60.4%
while the loads visibly stopped diverging. Size converging on retail's is
the signal; the percentage is only useful while the sizes match.

## throw() can be made TU-local with an explicit specialisation

A nothrow declaration is often the whole difference between a merged body and
retail -- it is what lets MSVC drop the unwind-state bump around a temporary and
guard it with a liveness flag instead. addGame was 77 diverging instructions
with the throwing declaration and 6 without it.

The declaration usually lives in a SHARED header you must not change:
Code/Libraries/Source/WWVegas/WWLib/string_base.h declares
`int compareNoCase(const StringBase<T> &) const;` and every TU that includes it
would move. Copying the header into a new shim dir works -- that is what
reference/shims/asciistring_downloadmanager/string_base.h is, one word different
from WWLib's -- but you do not need a new file for it:

    template <>
    class StringBase<UnsignedShort>
    {
    public:
        Int compareNoCase( const StringBase<UnsignedShort> &that ) const throw();
    };

An explicit specialisation REPLACES the primary for that one argument, so the
shared declaration every other TU sees is untouched and no shim dir is created.
It is legal after the primary is defined, as long as nothing has yet forced an
implicit instantiation for that argument -- check that first, and declare only
the members this TU actually calls. wchar_t and unsigned short are the same
mangled type (G) under MSVC 7.1's default, so one specialisation covers both.

## Run the object-symbol check BEFORE authoring, not after

A row can carry an object-symbol naming a spelling the destination will NEVER
define, and no amount of correct bytes fixes it.
GameSpyBuddyMessageQueueInterface::createNewMessageQueue looked like a one-diff
allocation-size fix -- 0x74 against the vendored 0x68, which is real -- but its
row carries
object-symbol=?createNewGameResultsInterface@GameResultsInterface@@SAPAV1@XZ.
The two are ICF-folded onto one body at 0x0063E240, build.py reads THAT spelling
out of the object, and the destination does not define it and never will. The
repoint fails "symbol not found in object" the moment it lands.

It is free and it is one grep. Put it first in your screen, ahead of any compile.

## Some rows only need repointing: the destination already compiles them

DX8Wrapper::Set_Shader needed no source change at all -- dx8renderer.cpp already
produced it byte for byte, and the row pointed at boxrobj.cpp only because that
is where it was originally lifted from. INI::parseObjectCreationList was the
same. The marker-clear screen finds these for free: clear the marker, build the
destination, and if it is already green the work is a repoint, not a fold.

## The "$L freeze" was a notes misclassification, not a constraint

build.py has always re-found renumbered funclets from the parent's
`__ehhandler$` group -- that is the "Funclet pins: N row(s) verified past a
renumbered $L label" line, 339 rows on a full gate. It never fired for
lanapi.cpp because is_funclet_row() (tools/build.py:920) gates on the notes
containing **gen-funclet**, and `?a_00c464f8@@YAXXZ`'s notes said **gen-alias**.
Both are true of that row: it is an ICF-twin alias claim AND a $L-pinned funclet
with a parent=. Saying both in the notes lets the pin self-heal like the 20,051
others, and lanapi stopped being frozen.

So a TU is only "frozen" if its $L-pinned row cannot be classified as a funclet.
EXACTLY THREE ROWS TREE-WIDE are gen-alias + $L + parent=:

    ?a_00c464f8@@YAXXZ   lanapi.cpp                                (fixed)
    ?a_00bfd4b8@@YAXXZ   Common/System/UpgradeNamesPlacementCleanup_00BFD4B8.cpp
    ?a_00c52ae0@@YAXXZ   WWVegas/WW3D2/VectorClassArrayPlacementCleanup_00C52AE0.cpp

The other two are latent the same way. If either file is a destination someone
is holding off, that is why -- and the fix is one add_match.py
--replace-existing on the notes, not a re-anchor.

What it bought immediately: lanapi.cpp had no AsciiString shim at all, adding
campaignmanagerascii (with /ICode/Libraries/Source/WWVegas/WWLib LAST for
string_base.h) left all 18 pre-existing rows green and collapsed one body's
residue from ~55 diverging instructions to 2. A re_attempts.log entry recording
"the shim is not free in this TU" had been measuring the misclassification, not
the shim.

## A stripped marker over an unmoved row hides a non-matching body

The worst state a half-finished fold can leave, because the gate reports success
BECAUSE of it. Recovering an agent that died mid-cycle, e92e20fdf carried a
rewritten BFME body into AIStates.cpp, deleted its `present-unmatched` marker,
and repointed only ONE of the two rows. The other body was then: rewritten, no
marker, row still naming the donor. verify_source_claims has nothing to
complain about -- the marker is gone -- and the byte comparison never looks at
it, because the row points elsewhere. `Functions: OK 158/158` and `PRE-COMMIT
OK` both passed, and neither was evidence about that body.

An unclaimed REFERENCE body in a destination is the baseline: 254 of them in
that one file. An unclaimed REWRITTEN body with its marker removed is not, and
the two are indistinguishable from the row side.

DIAGNOSING IT: `git show <sha> -- <dest> | grep "^+.*ClassName"` does NOT work.
A function's class name appears only in its signature, which stays as unchanged
context, so the grep returns 0 whether or not the body was replaced. Compare the
bodies directly:

    git show <sha>^:<dest> | awk '/^Ret Class::method/,/^}/'
    git show <sha>:<dest>  | awk '/^Ret Class::method/,/^}/'

and check what markers the commit removed:

    git show <sha> -- <dest> | grep -E "^-.*present-unmatched"

After ANY mid-cycle recovery, count the markers the commit deleted against the
rows it repointed. They must match.

## Half the markers are truncated, so a name-shaped grep undercounts by half

Measured: 4,545 `present-unmatched` markers carry a TRUNCATED mangled name
(`??0AudioEventRTS@@`, no parameter encoding) against 4,640 carrying a full one.
Any screen that greps a complete signature therefore misses about half its
population. A family screen on `PAVThing@@PBVModuleData` returned 23 module
constructors; at least one more (StealthDetectorUpdate) was missed purely
because its marker is the truncated `??0StealthDetectorUpdate@@`. Treat any such
count as a LOWER BOUND and say so when you quote it.

The same truncation causes two other failures already recorded here -- a bare
`??0Class@@` binds by PREFIX so landing one constructor staleens the other, and
a donor carrying a full spelling for one destination and a truncated one for
another LOOKS multi-destination and is not. One cause, three symptoms.

When you need a real count, match on the class-and-name prefix rather than the
signature, and expect to disambiguate by hand.

## A destination can be uncommittable at HEAD, and you find out by touching it

DeletionUpdate.cpp defines setLifetimeRange and calcSleepDelay; the ledger names
only calcSleepDelay and a d_ row. Staging the file fails the claims gate with
"staged sources define functions the ledger does not declare:
DeletionUpdate::setLifetimeRange". That condition sits at HEAD and is invisible
until somebody edits the file for an unrelated reason -- then the gate names a
function they never went near.

It is not something to work around: the file wants a declaration or a marker,
and that is a ledger decision. Revert your edit, record the file, and pick
another. Worth screening a destination for it before authoring if the fold is
large.

## "Naked donor" is not a reason to skip -- 75% of them are the BEST folds

Two opposite operations get confused under the anti-lift policy:

  FOLDING A DUMP INTO A DESTINATION puts `__emit` into readable code. Forbidden,
  and conversion_gate.py rejects it.
  DELETING A DUMP whose destination ALREADY has a readable body, and repointing
  the row at it, retires the dump and lands the row on real C++. That is the
  best fold available and it is the anti-lift policy working, not breaking.

Measured across the cluster set: 415 marked donors are naked, and 310 of them --
75% -- have a destination that already defines a body for that symbol.
LANAPIUpdateThunk.cpp is 2,035 lines of `__asm __emit` for `?update@LANAPI@@`
while lanapi.cpp carries the readable LANAPI::update(). Nearly the whole
AIStates cluster is this shape.

So a naked-donor count is not a count of unmergeable work. Screen the pair
first: does the destination define that symbol? If yes it is a candidate, and
tools/marker_screen.py measures the distance in two compiles. If no, it is
genuinely conversion work for another lane.

## Buy throw() with an explicit specialisation, not a shim directory

A nothrow declaration usually lives in a shared header you must not edit
(WWLib/string_base.h). Copying the header into a shim dir works and creates a
file; an explicit specialisation does not:

    template <>
    class StringBase<UnsignedShort>
    {
    public:
        Int compareNoCase( const StringBase<UnsignedShort> &that ) const throw();
    };

It REPLACES the primary for that one argument, so every other TU sees the shared
declaration untouched. Legal while nothing has forced an implicit instantiation
for that argument, and declare only the members the TU calls. wchar_t and
unsigned short share a mangled type (G) under MSVC 7.1, so one specialisation
covers both. On one body this was worth 71 of 77 diverging instructions --
compareNoCase sat between a temporary's construction and its destruction, and
nothrow let MSVC drop the unwind-state bumps either side.

## "Same body, different template instantiation" is only cheap if something else keeps the old one alive

A call site resolving to the wrong template instantiation looks like a free fix:
point it at the right one and the bytes match. But the OLD instantiation's
COMDATs are matched rows too, and if your call site was their only emitter in
that TU, the fix trades one matched row for another.

GameSpyInfo::removeFromSavedIgnoreList is the worked example. Retail's
m_savedIgnoreMap has a twelve-byte value type where the vendored header says
AsciiString, so its erase belongs to the generic 12-byte _Rb_tree instantiation
that gen_small/tgrid_119.cpp already owns rather than the AsciiString one -- the
same 91-byte body under a different template, and a local map view compiles the
call correctly. But that erase is the ONLY expression in the TU instantiating
the AsciiString tree's `_M_upper_bound`, a MATCHED 38-byte row claimed from that
same file. operator[] and find() elsewhere in the file do not instantiate it;
only erase does. So the body cannot land until that row is retired or rehomed --
a ledger decision, not a fold.

Check before costing one of these: does any OTHER expression in the TU keep the
old instantiation's COMDATs alive? Same screen as the pool-glue and inline-COMDAT
cases, pointed at templates.

And when you find the real reason, REPLACE the note that named the wrong one. A
note naming the wrong blocker is worse than no note: it bills the next agent for
the wrong fix.

## An orphan accessor: retail has NO caller, and your correct fold kills the row

`callers_of` on `?setNext@LANGameInfo@@QAEXPAV1@@Z` and
`?setName@LANPlayer@@QAEXVUnicodeString@@@Z` returns no named caller anywhere in
retail. They are orphan COMDATs the linker kept. Our tree held those rows green
only because converted bodies called accessors that RETAIL INLINES AWAY -- so
writing the body correctly stops emitting the accessor and the row goes red.

That is why a correct fold can turn a row you never touched red, and it is
distinct from the pool-glue and template cases: there the emitter was incidental,
here the emitter exists only because the port is wrong.

Two outcomes, and check which before declining:
  the row has another real home -- setName is called three times from
  LANAPIhandlers.cpp and byte-verifies there (7/7), so add_match repointed it and
  the fold landed;
  the row has none -- setNext's only call in the tree is on a different class's
  member, so the fold stays declined until someone rehomes or retires the row.

## Some donors are in the WRONG DESTINATION, not merely hard

/EH mode is per-TU, so a donor needing a different one can never fold into a
destination that cannot move. Retail's LANAPI::RequestAccept has NO SEH frame at
all -- `sub esp,0x1e0 / push esi / mov esi,ecx` -- while constructing and
destroying a temporary, which only happens under /EHs-c-. lanapi.cpp is /EHsc
and cannot change, because RequestGameJoin, LookupGame and RequestGameOptions
are matched there WITH frames.

So RequestAccept and RequestGameAnnounce should KEEP their own TU or find a
different destination. Folding them into lanapi.cpp is wrong in principle, not
merely blocked -- record it that way, because "blocked" invites a retry and
"wrong destination" does not.

## check_csv's own fix hint contradicts the duplicate-row rule

check_csv reports a union-merge duplicate with `Fix: python3 tools/dedup_csv.py`.
Following that rewrites both ledgers normalised -- a ~157,000-line diff that
conflicts with every branch in flight -- when the correct repair is to drop the
duplicate ROWS with ledger_io.py keeping the first. The message is wrong for
this case and agents have followed it. Ignore the hint; the rule is above.
## Any two 5-byte jmp thunks byte-match, so count the callers

A `jmp rel32` is five bytes of which four are a masked relocation. One byte is
compared. So EVERY 5-byte tail-call thunk in the tree byte-matches every other,
and a row parked on the wrong one still says `matched`. It is the same trap as
the wrong `$L93744` pin that rode along on the PeerDefs funclets, one level up:
masking is what makes the reconstruction possible and what makes these
indistinguishable.

The discriminator is the call profile, and it is one pass over `.text`:

    hist = Counter()
    for i in range(len(text) - 5):
        if text[i] in (0xE8, 0xE9):
            hist[tva + i + 5 + int32_at(text, i+1)] += 1

Then read the count against what the claimed function is FOR.
`?addTeam@TeamsInfoRec@@QAEXPBVDict@@@Z` claimed a stub with 6,947 callers;
retail calls addTeam from a handful of places, and 6,947 is what a string
destructor's import thunk looks like. Sure enough the stub was
`jmp 0x0005EE90`, which functions.csv already recorded as
`??1AsciiString@@QAE@XZ`'s body.

To find the candidates, sweep for rows whose `target_rva` equals a DIFFERENT
symbol's `export_rva` and whose first retail byte is 0xE9. That is 1,078 rows,
and almost all of them are fine: 1,048 are `?j_XXXXXXXX@@YAXXZ` placeholders in
`Code/gen_small/thunks_*.cpp`, which claim ILT slots by address on purpose. Of
the 30 with real mangled names, 27 are the FX `getClass<T> -> jmp getInstance<T>`
pairs -- semantically coherent, ~5 callers each, a real tail call. Three were
the outlier. So the sweep alone proves nothing; the sweep plus the caller count
does.

Consequence for triage: `marker_screen` reports a small `miss(N)` when a
destination holds a real body and the donor row owns a jmp stub -- it is
comparing the body's first five bytes against a jump. A low miss(N) is only
meaningful when donor and destination model the same SHAPE of function. Check
the donor row's size before believing one.

## A push loop that trusts an empty commit range cannot see its own failure

`git log origin/master..HEAD` is empty when you are pushed AND when a conflicted
rebase has left HEAD detached on origin's tip with your commit only in the
reflog. Checking HEAD's POSITION instead does not help -- in that failure HEAD
really is an ancestor of origin/master, so the position check passes too. And a
push guard grepping for "rejected" misses the actual error text, which can be
"a pushed branch tip is behind its remote counterpart" or, mid-rebase, "fatal:
Exiting because of an unresolved conflict."

Both failures start with a silenced `git pull --rebase` swallowing the conflict.
Observed twice in one day: once reporting a false PUSHED, once exhausting its
retries in total silence while the commit was lost.

Use `tools/push_retry.sh`, which never silences the pull, refuses to start
mid-rebase, exits non-zero with the conflicted paths when the rebase needs
hands, and confirms the commit SUBJECT is in origin/master before printing OK.
Verify a push by what reached the remote, never by a range that is empty in the
failure case as well.

## An investigation command can be destructive: never reset a checkout you share

Chasing whether some orphaned reflog commits had really landed, I ran
`git reset --hard origin/master` in the shared Open-BFME1 checkout to get a
clean base to grep. Another lane was mid-fold in that tree, and the reset threw
away its index and working copy without a prompt.

Nothing was actually lost -- every InGameUI.cpp and functions.csv blob from that
window turned out to be BEHIND master, a superseded mid-rebase snapshot -- but
that was luck, not care. The reason to write it down is that `reset --hard` did
not feel like a mutation at the time; it felt like setup for a read-only
investigation, which is exactly how the dangerous ones look.

Two rules. Investigate from a worktree you own, or from `git cat-file`/`git show`
against a ref, which touch nothing. And if you must know what a shared tree
holds, `git status --porcelain` first and stop if it is non-empty.

Recovering a clobbered index is possible but only briefly: staged blobs survive
as loose objects until gc, and `find .git/objects -type f -printf '%T@ %p\n'`
sorted by time finds them far faster than `git fsck`, which times out on this
repo. Note `find -newermt` silently returned nothing here; compare the numeric
`%T@` against a cutoff instead.

## A GREEN build under a layout define is not evidence the define is right

`/DBFME_MODULE_NO_MPO` drops MemoryPoolObject from Module's base list, removing a
vptr and shifting every member below by four. Three destinations, same family,
three different answers:

  W3DPropDraw and CreateObjectDie: the define IS the whole fix, no view, no shim.
  InstantDeathBehavior and BridgeTowerBehavior: RED under it. Each has an
    already-matched this-adjusting interface getter in the same TU, and a
    this-adjustment encodes base offsets directly -- so those matched rows are
    positive proof these objects DO carry the vptr the define removes.
  AssaultTransportAIUpdate: stays GREEN under the define and gets WORSE --
    ctor miss(7) without it, miss(11) with it.

That last one is the trap. Nothing in that TU contradicted the define, so the
build had nothing to say; only the screen did. Take the miss count, not the exit
code, as the evidence that a layout define belongs. And note the shape of the
proof in the RED pair: a matched this-adjusting thunk in the same TU is a
layout witness you already own.

## When a diff lands on a masked DIR32, read the relocations, not the disassembly

explain_mismatch rendered two vptr stores as `mov DWORD PTR [esi+0x4],0x5ec68b00`
followed by stray `.byte`s, because relocation targets are zero-filled in the
object and the disassembler ran off the end of the immediate. Read as a mystery
member, it sent an agent looking for a field that does not exist.
`build.read_object_symbol_bytes` returns `(body, relocs)`; the relocation list
named `??_7W3DPropDraw@@6BMemoryPoolObject@@@` and `??_7W3DPropDraw@@6BSnapshot@@@`
outright and the diagnosis was immediate.

## Rank a cluster with ONE compile before applying anything

Build the destination once, then for each donor read its symbol out of the
already-built .obj, mask relocations, and compare against retail. Twenty
candidates ranked in a single build with no applies and no ledger churn. It put
addMessageText at 64.9% agreement (landed 388/388 first try) and correctly warned
that `update` at 19.3%, failing at offset 0 on an `and esp,-8` aligned frame, was
a research task rather than a fold.

## Fresh views need tuning ONE AT A TIME against the residue

objectChangedTeam: repointing its row onto the existing body agreed on 62.4% of
masked bytes; correcting all six known offset facts at once dropped it to 29.7%.
The offsets were right and the spellings were wrong -- each fresh view moved
MSVC's register allocation more than the corrected offset was worth. In the same
file addMessageText landed first try, because its views already existed as proven
spellings. Correct facts applied together can still go backwards; add one view,
measure, keep or revert.
## The second thunk test: is this stub the body's ONLY thunk?

Caller counts settle a jmp stub's identity only when the two candidates have
wildly different call profiles. They are useless when both are called once, and
plenty of constructors are. The test that works there is topological: build the
map of every 5-byte `E9` in `.text` to its target, and ask how many stubs reach
the body in question. Incremental linking emits ONE thunk per function, so if a
body already has a matched claim under name B and exactly one stub jumps to it,
that stub is B's thunk -- whatever name a row has parked on it.

`??0AutoHealBehavior@@` claimed a stub whose only target is a 276-byte matched
`??0SpyVisionUpdate@@`. Both are called once. ICF is not the alternative
explanation: folding needs identical bodies WITH identical relocations, and two
module constructors store different vftables.

Sweeping for it: 5-byte rows whose jump target is claimed by a differently-named
symbol give 272 hits, and most are the project's own conventions -- a real name
thunking to a `?d_`/`?j_`/`tg_`/`Gen_` placeholder body, or to a deliberate
`..._Body`/`...Shim` split, or the same template function under two manglings.
Excluding those leaves 81; requiring the stub to be the body's unique thunk and
the body to be a matched claim of 32 bytes or more leaves 67. Confidence is not
uniform inside that 67: a 276- or 652-byte body cannot be an ICF twin of another
class's constructor, but a 69-byte trivial ModuleData constructor plausibly can,
and for those the ledger may be modelling a genuine fold. Sort by body size and
believe the large ones.

Eleven of the 67 are donors in the marker queue, so screening them returns a
small `miss(N)` that means nothing at all.

## $L numbering is file-sequential, so a typedef freezes a TU as hard as a class

"$L-anchored rows are broken by ANY added declaration" is true but understates
it. The counter runs across the whole translation unit in source order, so any
change that alters codegen ABOVE a pinned funclet renumbers it -- not only new
declarations, and not only new types.

Measured on StagingRoomGameInfo.cpp, which owns `$L70459` and `$L64396`. A
class-template slot view renumbers them, as expected. So does this, which
declares no class and emits no code of its own:

    typedef Bool (__fastcall *BfmeAmIHostFn)( const GameSpyStagingRoom * );
    if ((*(BfmeAmIHostFn **)this)[4]( this ))

Both die with `symbol not found in object: $L70459`. Contrast a `#line`
directive, which is genuinely free and renumbers nothing. So when a destination
carries `object-symbol=$` rows, the question is not "can I avoid declaring a
class" -- it is whether the funclet pins get re-anchored first.

Two smaller notes from the same attempt. MSVC 7.1 rejects `__thiscall` on a
function-pointer type outright (`error C4234: nonstandard extension used`), so a
hand-rolled vtable call has to be `__fastcall`, which is call-compatible for a
method taking no arguments. And the cost of re-anchoring is worth weighing
against the whole destination, not one body: StagingRoomGameInfo.cpp is one byte
from closing `?resetAccepted@GameSpyStagingRoom@@` -- retail tail-calls slot
+0x10 where the shared header computes +0x08 -- and carries eleven queue entries
behind the same freeze.

## A class that is too SMALL needs BYTES, not a new class -- and measure per body

Player.cpp carried a written verdict against disableRadar and enableRadar:
"Cannot come home: retail's AudioEventRTS is 0x70 bytes where this tree's is
0x64 ... a class-shape difference, not a field view." The diagnosis was right
and the conclusion was wrong. All three radar bodies now match byte for byte
(193/193, 186/186, 215/215) on a padded local:

    struct BfmeAudioEventStorage
    {
        BfmeAudioEventStorage( const AudioEventRTS &src ) : e(src) { }
        AudioEventRTS e;
        UnsignedByte _bfme_tail[12];
    };

The member sits at offset 0, so its address, constructor and destructor are
unchanged and every call in the body stays what it was; only the frame grows.
**The constructor is load-bearing**: declaring the storage and then assigning
default-constructs and then assigns, where retail copy-constructs in one call.
Take the source by const reference and initialise in the member list.

The counter-example matters as much. addRadar reserves 0x60 where the other
three reserve 0x70, orders its EH frame differently, and lives at 0x000FB3F0
well away from them. The twelve bytes belong to the FRAME those three share,
not to AudioEventRTS everywhere. Measure the frame per body; do not pad on
faith. And treat a "cannot come home" verdict as a measurement someone took
once, not as a closed door.

## A bespoke local replica proves the byte SHAPE, never the IDENTITY

A `*_Thunk.cpp` donor that declares its own little struct to reach an offset has
chosen those offsets as free parameters to fit the bytes it wanted. It will
agree with retail and still be about a different function. Squad_isOnSquad.cpp
declares the membership pair at +0x04 and matches; three siblings compiled from
the REAL class in Squad.cpp say the pair is at +0x08/+0x0C. Against siblings
built from the shared class, a local replica is the weaker witness.

This is why a large number of our `*_Thunk.cpp` donors cannot be trusted to name
the function they claim, and it is the same failure as the 5-byte jmp rows: a
match against a shape you chose is not evidence of identity.

## Screening one symbol does not license applying the DONOR

`?parseArmorTemplateSet@ArmorTemplateSet@@` screened MATCH into ThingTemplate.cpp,
but the apply moved a SECOND row in the same donor that was never screened and
does not match from there. merge_cluster was correct -- selection is by row, and
a marker named that destination. The screen simply did not cover it. **Compare a
donor's row count against its marker count before --apply.**

It then failed dishonestly, which is the part to remember: `verify_source_claims`
read the repointed row as "byte-verified matched from this file" out of the
LEDGER rather than out of the bytes, and complained that the other symbol's
marker was a stale annotation. Clearing that marker is what let the real byte
failure surface on the next build. **A stale-annotation complaint about a row
that just moved is a question, not an instruction.**

## miss(1) and miss(2) are where a wrong offset lives, not "nearly done"

Forty donors screened in one pass: four landed, six were free, and every
remaining small miss was a layout fact costing a compile each to learn.
DecalMeshClass at one byte is a refcount initialiser that fourteen sibling
classes set the other way. Squad::isOnSquad at two bytes is a class-shape
contradiction inside one class. The Upgrade family's four bodies at miss(2) are
one base-ORDER difference: read as spans, eight bytes move out of the second
base into the first, which is why no define closes it.

Budget a near-miss as a research task, not as a fold that is almost finished.

## Read the compiled SIZE beside the agreement percentage

Once the compiled size differs from retail's, the percentage stops moving even
as you fix real things, because every byte after the first divergence is being
compared against the wrong position. Three separate correct offset fixes left
addSuperweapon at exactly 60.4% while its loads visibly stopped diverging.
Size converging on retail's is the signal; the percentage alone will tell you
your correct fixes did nothing.

## Read which REGISTER a call goes through, not which line it sits next to

`FileSystem::openFile` was assumed virtual because the vtable call NEXT TO IT
had shifted. Adding the view emitted an extra `mov edx,[ecx]`, which misaligned
everything after it and took agreement from 98.4% down to 95.7%. It is a DIRECT
call in both trees.

Proximity to a call you have just corrected is not evidence about a call. The
indirection is visible in the instruction -- read it. Same family as
objectChangedTeam: a plausible view that is wrong does not merely fail to help,
it actively destroys agreement you already had.

## OBJECT_STATUS_UNDER_CONSTRUCTION is bit 2: BFME drops one enum entry

Two independent retail bodies do `test BYTE PTR [eax+0x90],0x4` where this tree
reads a dword pair at +0x90/+0x94 and tests 0x8. ZH's ObjectStatusTypes runs
NONE, DESTROYED, CAN_ATTACK, UNDER_CONSTRUCTION -- index 3, so `test()` compiles
to bit 3. BFME has ONE FEWER entry ahead of it.

240 use sites, so this is a shared-header change behind a lot of rows and not a
readability-lane fix. But it is solvable rather than guessable, and that is the
point worth recording: `getStatusBits().test(X)` compiles the enum INDEX into
the instruction, so every matched body testing ANY status bit is a constraint on
the ordering. Collect the constraints, solve for which entry BFME drops, and let
the already-matched rows prove it -- do not edit the enum and see what survives.

## A 100% masked screen is necessary, not sufficient

DataChunkInput::openDataChunk reaches 100% of masked bytes and still fails,
because the masked comparison cannot see a call that resolves to the WRONG
FUNCTION. Retail's `AsciiString("")` there calls RVA 0x00102D90 --
`?d_00102d90@@YAXXZ`, an unidentified 77-byte gen-dump whose body reads `[ecx]`
and compares `[m_data+0xC]` against its argument, which is a `set` and not the
constructor at 0x00888BC0 this tree resolves to.

This is the same blindness as the 5-byte jmp thunks arriving from another
direction: masking hides IDENTITY. A perfect score means every byte you can see
agrees, and the bytes you cannot see are exactly the ones that name the callee.

## Before renaming to fix a DIR32 red, check the TARGET symbol's existing bases

Renaming misnamed references onto the correct global is the honest fix, but it
only clears the red if the name you are moving TO is already consistent. If that
symbol is itself referenced somewhere at a different address, the rename hands
it a second base and the gate stays red under a new name -- with the work spent.

One pass of dir32_sites.py over the candidates answers it before any edit. For
the ThePartitionManager red: `?TheShroudManager@@3PAVShroudManager@@A` already
had two references and both were at 0x012ED5BC, the same base the misnamed sites
resolved to; `?TheRadar@@3PAVRadar@@A` had nine, all at 0x012EF0E4. So every
reference being moved landed on a symbol that already agreed with it.

Two useful corollaries. A second NAME at the same address is not a problem --
the check is per symbol, so `?TheRadarClientUpdate@@...` sharing 0x012EF0E4 is an
ordinary alias. And the completion test needs no gate run: when the rename is
done the misnamed symbol should have ZERO DIR32 references, not one base. A
remaining base means a site was missed.

## Markers are COMMENTS, so one compile answers a whole destination

marker_screen.py pays two compiles per (donor, symbol) question. But a marker
cannot change what the compiler emits, so a destination carrying 65 markers does
not need 65 builds: compile it ONCE, then ask build.compile_function the same
question of every marker against that single object. 24 destinations and ~1,300
markers screened in one pass, against roughly 2,600 compiles the old way.

The general form is worth keeping in mind elsewhere: when the thing you are
varying is a comment, an annotation or a ledger note, the expensive artifact is
invariant and belongs outside the loop.

## find_declared_unmatched cannot see a stale marker that has an overloaded sibling

It resolves an abbreviated label by prefix, but only when the file carries
exactly ONE marker with that label. Overloads share a label, and claiming one
says nothing about the others -- so a stale marker with an overloaded sibling is
invisible to it permanently, not merely missed once. Two such markers had made
their files uncommittable at HEAD and had never been looked at.

Treat this as a known blind spot rather than trusting the check's silence. A
tool that is confidently wrong costs more than one that stops.

## Prefix resolution binds a truncated marker to the WRONG overload

Fixing stale markers by script would have destroyed true statements.
render2d.cpp carries three `// ?Add_Quad@Render2DClass@@` markers while the
matched row is `?Add_Quad@Render2DClass@@QAEXABVRectClass@@0K@Z` -- a fourth
overload that correctly carries no marker. Seven candidates were rejected on
reading for this reason.

Same shape as the 5-byte jmp thunks and the 100%-masked screen: a prefix hides
identity exactly as a mask does, and identity is what the question is about.
When a fix needs a mangled name spelled out, read it from the compiled object;
a marker naming a symbol that does not exist is a worse lie than the stale one
being replaced.

Also: replace such a line in place rather than deleting it. Files that compile
macros expanding `__LINE__` change bytes below any removed line.

## When a matched TU works around the shared header, the HEADER is what is wrong

Four separate requests for a new `reference/shims/` directory have now dissolved
on an artefact the tree already owned. The clearest:
`CachedFileInputStream::open` appeared to need a Compression.h shim because
BFME's `decompressData` takes a `const void *src`. But
`Code/Libraries/Source/Compression/compression.h` is OUR copy, byte-identical to
the reference bar a provenance comment, and DataChunk.cpp was the ONLY file
including it -- reaching the reference copy merely because our directory was not
on its include path. Correcting the header we own was narrower than duplicating
it into a shim.

The tell was in the tree the whole time: `CompressionManager_decompressData.cpp`
reproduces that body byte for byte and has to declare its own local class to say
`const`. A matched TU carrying a local workaround for a shared declaration is
evidence about the DECLARATION, not a trick to copy.

Before adding a shim, check whether the repo already owns the header, whether
the destination is even reaching our copy, and which matched TUs already work
around it.

## `and esp,-8` with no floating point anywhere: rule it out before theorising

`LANAPI::update` opens `push ebp / mov ebp,esp / and esp,0xfffffff8`. MSVC 7.1
emits that for a local needing eight-byte alignment, which normally means a
double or an `__int64` -- so that is the first thing to test, and it is FALSE
here. Scanning all 2030 retail bytes for `fld`, `fstp`, `fild`, `fadd`, `fmul`,
`fdiv`, `movq` and any qword operand returns nothing at all.

That leaves `__declspec(align)`, `_alloca`, or inline asm, and the question has
to be settled before anything downstream in the body can be judged -- it fails
at offset zero, so every later measurement is against a shifted frame.

The wider point: re-measuring after the LANAPI layout correction landed produced
NO movement at all (393/2030 before and after). A body that does not move when
you fix a real thing is telling you the real thing was not what held it.

## The marker queue is NOT a fold backlog: two thirds of it has no ledger row

158 destinations screened in one pass, roughly 3,000 markers:

    ~2,000  no ledger row AT ALL -- a body present in the tree with no matched
            retail address behind it. Screening can never turn these into folds;
            they are AUTHORING work, not repointing work.
      ~300  measured misses, nearly all layout facts
       ~30  MATCH, collapsing to 9 distinct symbols, of which 6 landed

That is roughly one fold per 26 destinations screened. Anyone budgeting a lane
against the marker count is budgeting against a number that is two-thirds
something else. Measure the composition of a queue before planning against its
size -- this cost one pass and should have been done first.

## A marker can sit above a CALL, not a definition, and folding invalidates the rest

Markers are not always above the body they name. W3DVolumetricShadow.cpp carries
four `// ?Fabs@WWMath@@SAMM@Z present-unmatched` lines INSIDE a function body,
one above each CALL of it; W3DWater.cpp has four the same way for
Set_DX8_Render_State. `--apply` consumes the pair it matched and leaves the
others, so landing one inline-emitted COMDAT turns every remaining annotation of
that symbol in that file into a stale marker. The gate catches it, but the
cleanup belongs in the same commit.

Two consequences. Folding an inline-emitted symbol always means sweeping its
other annotations in the destination. And in-place replacement stops being a
preference and becomes mandatory: these lines sit inside function bodies, so
deleting one moves every line below it and changes any `__LINE__` the TU expands.

## Some MATCHes are not expressible as a merge, and --symbols does not help

`?Set_Transform@DX8Wrapper@@` matches from BOTH W3DWater.cpp and
W3DWaterTracks.cpp. One row cannot land in two files. Worse, boxrobj.cpp -- which
owns it -- carries no readable-body marker naming either, so there is no cluster
to select within at all. The constraint is UPSTREAM of selection, so per-symbol
selection cannot reach it.

Log these and leave them. Do not add a marker to create the cluster: the marker
is the evidence the tool reads, and writing one to make an apply possible is
manufacturing the input rather than recording a finding.

## A cluster member is a MARKERED ROW, not every row its donor owns

screen_cluster.py collected donor FILES by marker and then screened every row
those files own. ini.cpp owns 256 rows and carries 32 markers for INI_stl.cpp,
so 224 non-members were measured and reported as candidates -- an "eleven ready
rows" verdict that was really two.

The invariant: only a markered row is a cluster member, and only a markered row
is something merge_cluster can move. Filter a donor's rows against its own
marker list, matching by prefix since a marker may name a truncated symbol.

The instructive part is WHERE the bug was. merge_cluster -- the tool that ACTS
-- had it right all along, intersecting owned rows against `claims(...)`.
screen_cluster -- the tool that MEASURES -- did not. So the measurement was
promising folds the apply step would have refused, and the two disagreed
silently until --symbols made the apply reject nine names at once. When a
measuring tool and an acting tool encode the same rule separately, the measuring
one is where the drift hides, because nothing fails when it is wrong.

Corrected counts come in LOWER, never higher, so nothing landed on the old
numbers is at risk -- but any shortlist built with it is inflated wherever a
donor owns more rows than it has markers for. That shape is common:
lanapi, InGameUI, Player and DataChunk were unaffected precisely because each
donor there owned only the rows it had markers for.

## HYPOTHESIS: BFME classes carry TWO links where the reference carries one
(Superseded in part: the discriminator below now separates this from a
shifted class before any code is written. GameWindow was the third witness
and it was NEGATIVE, which is what bounded the habit.)

Two independent classes now show the same shape, and it is worth testing on a
third before treating it as a fact.

**Script** carries two action pointers. `ParseActionDataChunk` reads and writes
`Script+0x20`, while `getAction` and `setAction` both work on `+0x28` -- and
retail's own accessors settle it: `mov eax,[ecx+0x28]; ret` at 0x00112980 and
`mov [ecx+0x28],eax` at 0x00112970. So the accessor pair maintains one action
list and the parser appends to a different one.

**LANGameInfo** is the same: +0x360 maintained by the accessors, +0x398 walked
by the bodies.

If this is a habit rather than a coincidence, it predicts a family of blockers
that read as "the accessor and the body disagree about an offset" and are
actually two real members. The diagnostic that distinguishes them: a matched
ACCESSOR is authoritative about its own offset, so when a body disagrees with a
matched accessor, suspect a second member before suspecting a layout error --
and check whether both offsets are live rather than assuming one is wrong.

Do not fold this into a layout correction. Adding a view that moves the parser
onto the accessor's offset would make one row match and silently merge two
distinct members.

## find_emitter: which TU could an orphaned row live in, without a build

Seventh instance of the orphan-accessor pattern, so `tools/find_emitter.py`
answers it directly:

    python3 tools/find_emitter.py '?getAction@Script@@QBEPAVScriptAction@@XZ'

Every object under `build/match` is already compiled, so the answer is in the
symbol tables. It reads them, names the sources, compiles nothing, writes
nothing.

**The distinction it enforces is the one grep cannot make: EMITTING is what the
ledger needs, and calling is not enough.** `Script::setAction` is called in
GameLogic.cpp and not emitted there -- a guess that looked right and cost a full
TU build to disprove. It agrees with all four cases previously resolved by hand,
including the two with no home at all, which is why addGame and
ParseActionDataChunk are declined rather than pending.

Build the object map forward from the tree, never by decoding object names:
`obj_path()` joins path parts with `_` and filenames contain underscores too, so
decoding produced a path to "scripts.cpp" that was nothing of the sort.

## The rows ALREADY matched tell you which regions are safe to change

Correcting a shared class reads as dangerous because N rows depend on it. Those
rows are also the constraint that tells you whether it is safe, and they can be
read before touching anything. The question is never "how many rows depend on
this class" but **"which of them read the region I am moving, and HOW".**

**The "how" is the part that was originally got wrong here, and it is the whole
rule.** This entry first claimed that none of GameWindow.cpp's matched rows read
the shifted region. The enumeration says TWENTY of 34 do. They did not break,
and the reason is not that they avoid the region:

  * **A row reaching an offset through a TU-LOCAL VIEW is immune to a header
    change.** It compiled an absolute number -- `struct BFMEGameWindowOrigin
    { char pad[0x14]; Int x; Int y; }` and the `BFME_WIN_` macro rows -- and
    editing the class cannot reach it. Seventeen of the twenty are this.
  * **A row that reads a member BY NAME is the one at risk.** Three do:
    winSetNextInLayout writes `this+0x1F8`, winSetPrevInLayout `+0x1FC`,
    winSetLayout `+0x200`, as plain `m_nextLayout = next;` bodies. Under the
    gamewindow shim's tail those become 0x208/0x20C/0x210 and stop matching.

So enumerate by MECHANISM, not by offset range. And enumerate properly: the
first pass here grepped for one macro name (`BFME_WIN`) and so counted five
view-based rows as symbolic because their views were spelled differently. One
naming convention is not a census.

## Displacement is CUMULATIVE: map the whole class with its getters

GameWindow was read twice and reported wrongly both times -- first as uniformly
+4, then as "short at the front, already correct at the tail". Both were
artefacts of measuring one end. The truth is a staircase, one step per
insertion:

    +0x2C m_userData  +4     +0x34 m_id      +4     +0x3C m_style    +4
    +0x1EC m_tooltip  +8
    +0x1F8 m_next    +16     +0x200 m_parent +16    +0x210 m_layout +16

which is exactly the four BFME-only insertions in `reference/shims/gamewindow`
(+0x04, +0x1DC, +0x1F0, +0x1F4) accumulating.

**A sizeof tells you the TOTAL, never the distribution.** 112 against 108 is
consistent with one insertion anywhere, or four. Do not size a header pass from
one measured delta or from a sizeof.

**The cheap instrument is the getters.** Each getter is a single load, so each
PROVES one retail offset outright -- no build, no view, no inference. Read a
class's getters together and the whole displacement falls out in one pass.
Thirteen of them mapped GameWindow after two wrong readings from partial data.

## A getter and a setter for one member cannot disagree about its offset

The cheapest identity evidence in the tree, and it settled a question that had
already been escalated as unanswerable.

Three matched GameWindow setters write `this+0x1F8`, `+0x1FC` and `+0x200` as
plain `m_nextLayout = next;` bodies. The getters prove those offsets are
**m_next, m_prev and m_parent** -- m_nextLayout sits at +0x208. So
`?winSetNextInLayout@…@Z` at 0x001BD6A0, `?winSetPrevInLayout@…@Z` at
0x00478DD0 and `?winSetLayout@…QAEX…@Z` at 0x0026ED70 are misnamed: they are
winSetNext, winSetPrev and winSetParent, matching only because our header puts
m_nextLayout exactly where retail puts m_next.

Third instance of a row green because a layout error cancels a naming error,
after the VertexMaterialClass colour-source pair. Reach for the getter/setter
pair BEFORE escalating an identity question -- it is one disassembly per member
and it answers outright.

## Check a candidate shim against the BODIES, not against the destination

`reference/shims/gamewindow/GameClient/GameWindow.h` already carried the exact
layout that nine GameWindow rows needed, four-byte anchor included. It had been
opened, read as disagreeing, and dismissed -- because it was compared against
the DESTINATION's current class rather than against the retail bodies. It was
agreeing with the bodies and disagreeing with the destination, which is precisely
what a correct shim for a wrong destination looks like.

Fifth new-shim need to dissolve on an artefact the repo already owned, and the
first where the artefact had been looked at and rejected. When a shim seems
wrong, check which side it disagrees with before discarding it.

## One source name, two real functions, two addresses

That shim still could not be used, for a reason worth knowing: it declares
`winSetLayout`, `winSetNextInLayout` and `winSetPrevInLayout` returning `Int`
where GameWindow.cpp defines them returning `void` -- and BOTH ARE REAL.
`?winSetLayout@GameWindow@@QAEHPAVWindowLayout@@@Z` is at 0x00478E10 and
`?winSetLayout@GameWindow@@QAEXPAVWindowLayout@@@Z` is at 0x0026ED70. MSVC
encodes the return type, so they are distinct symbols that share a source name.

A shim can therefore carry a correct layout AND a set of signatures that belong
to one TU only, and a destination gets one or the other. A TU-local view takes
the layout without the signatures, which is why views keep working where the
shim cannot be adopted.

## THE DISCRIMINATOR: second member, or short class? -- HALF OF THIS WAS WRONG
**The GAP RULE below is FALSIFIED. Read the correction that follows it before
using anything in this entry.**

A matched tiny accessor is authoritative about its own offset -- it is
byte-verified and does nothing else. So collect a class's accessor-proven
offsets and look at how the disputed offset sits among them. This costs four
disassemblies and no build, and it settles a question that otherwise costs a
speculative view.

**One disputed offset in a GAP the accessors do not cover, accessors consistent
among themselves -> a SECOND MEMBER. The body is right.**

    LANGameInfo   getNext/setNext prove +0x360, get/setLastHeard prove +0x364 --
                  adjacent, consistent, no shift. The link the bodies walk is
                  +0x398, 0x38 further on, covered by nothing.
    Script        setActive +0x1C, get/setAction +0x28, setFalseAction +0x2C,
                  setNextScript +0x30, setFrameToEvaluate +0x34 -- a dense
                  consistent run. The parser's +0x20 sits in the gap between
                  +0x1C and +0x28 with no accessor over it.

**A RUN of consecutive members at the SAME delta -> the CLASS IS SHORT. The
header is wrong.**

    GameWindow    m_status, m_size, m_userData, m_instData are every one exactly
                  +4 out. Four coincidental second members all four bytes apart
                  is not credible; one inserted member is -- and the gamewindow
                  shim's independent reconstruction names it,
                  `GameWindowAnchor *m_bfmeAnchor // @0x04 (BFME-only)`.

This is the guard the two-links hypothesis needed, because the tempting move --
a view sliding the body onto the accessor's offset -- makes the row match while
silently merging two distinct members.

Evidence strength differs and should be carried with the claim: LANGameInfo's
+0x398 is proven by three matched rows (removeGame, LookupGameByListOffset, and
a reverted addGame); Script's +0x20 rests on retail's bytes alone, because the
only body that uses it is the one that cannot land. Script is a strong reading,
not a proven one -- if a later case contradicts the gap rule, re-examine Script
first.

## retail LANPlayer::setName never touches `this`

0x00624C10, 72 bytes: it constructs something from its by-value argument and
destroys it again, and never writes through the instance pointer. Same shape as
the three InGameUI varargs message stubs -- a name that survives a layer BFME
removed. Not chased; flagged because anyone treating that symbol as an accessor
is reading a name rather than a body.

## A row can be GREEN because a layout error cancels a naming error

The worst case yet, because nothing complains. In VertexMaterialClass three
bodies -- Get_Ambient, Get_Specular, Get_Emissive -- each stop on ONE byte and
all on the same one: retail loads the material pointer with `mov eax,[ecx+0x08]`
where this tree emits `[ecx+0x0C]`. So MaterialDyn is at +0x08 in retail and
+0x0C here, and the class measures 112 against retail's 108.

Given that shift, two MATCHED rows in the same file read one field past their
names. `?Get_Ambient_Color_Source@` at 0x00921210 is `mov eax,[ecx+0x14]` and
`?Get_Emissive_Color_Source@` at 0x00921230 is `mov eax,[ecx+0x18]` -- our
offsets for those fields, while in retail's layout +0x14 is EmissiveColorSource
and +0x18 is DiffuseColorSource. They match ONLY because the +4 shift slides our
field under retail's load. The trio and the pair imply mutually exclusive
layouts for one class, so both cannot be right.

Two consequences worth internalising:

A matched row is evidence about BYTES, never about NAMES -- same conclusion the
5-byte jmp thunks, the 100%-masked screen and the local replicas all reached,
arriving here from a fourth direction. Compounding errors that cancel is the
only one of the four that a correct fix will appear to BREAK.

So expect it: fixing the layout will turn those two red, and that is the fix
working. Before a class correction, identify which matched rows are green by
cancellation, and predict them as expected casualties in the commit message --
otherwise the next agent reverts a correct change to get the count back.

## Ask the compiler for a sizeof, and validate the instrument before believing it

MSVC will state a size in a diagnostic if you make it print a type:

    static char (*p)[sizeof(X)] = 1;   // cannot convert from 'int' to 'char (*)[112]'

That gave sizeof(RefCountClass)=8, sizeof(W3DMPO)=1 (empty-base optimised), and
sizeof(VertexMaterialClass)=112 against retail's 108.

**Validate the probe first with an unconditional `#error` in the same header**,
to prove the file actually recompiles. Only then does a conditional probe that
does NOT fire mean anything -- a probe silently reusing a cached object reads as
a clean negative result, which is the same swallowed-failure shape as a sweep
reporting "0 refs" for 314 objects that failed to load.

**RETRACTED, and the retraction is the more important lesson.** The sizeof
figures above and a companion result -- that dropping the empty W3DMPO base did
not move the offsets, so W3DMPO was "ruled out" -- were all measured against
`reference/CnC_Generals_Zero_Hour/.../vertmaterial.h`, which this build does not
use. WW3D2 has its own copy and a relative include finds it first. Every one of
those experiments was a no-op, and two of them were reported as findings.

So `#error` proves the file RECOMPILES. It does not prove you are editing the
file the build READS. Those are different questions and only the second one
matters. **Check the deps sidecar for the header the compile actually opened
before editing any header**, especially where a vendored copy and a local copy
share a name.

## Three screen MATCHes that are not folds

They look identical in a report and each needs a different answer:

  * **A symbol matching from a SECOND destination.** `?Fabs@WWMath@@SAMM@Z`
    matched from coltest.cpp after its row had already moved into
    W3DVolumetricShadow.cpp. That is not a second fold -- it means the body
    compiles identically in several TUs, and chasing it is ping-pong.
  * **Donor equals destination.** `?Add_Quad@Render2DClass@@QAEXABVRectClass@@0K@Z`
    "matches" from render2d.cpp, which is already its own source. A no-op.
  * **Donor under `reference/`, not `Code/`.** `?Configure_Material@MeshMatDescClass@@`
    matches with its donor in the vendored tree. Repointing a row onto a
    reference-tree source is a different decision from folding two of our own
    files, and should not be taken as ordinary cluster work.
## A small miss(N) is a classification, not a distance

Screening a whole destination per compile makes miss counts cheap enough to
gather in bulk -- 493 of them here, after dropping the 5-byte jmp stubs whose
count is meaningless. Sorted smallest-first they look like a work queue. They are
not. Every miss(1) and miss(2) read in detail turned out to be one of four
things, and only the last is work:

  A CONSTANT BFME CHANGED.  WeaponSet's three miss(1)s are all `loop to 4` where
  ZH's WEAPONSLOT_COUNT is 3: BFME's weapon set has a fourth slot. Fixing the
  constant widens m_weapons[] by four bytes and moves everything nine matched
  rows in that file read, so the donors stay split on purpose.

  A FIELD OFFSET.  VertexMaterialClass's three getters are all `[ecx+0x08]`
  against our `[ecx+0x0C]`; User::setName is `add ecx,0x4C` against `add ecx,4`.
  One byte on the wire, 4 or 72 bytes of layout behind it.

  A TRUNCATION.  W3DSnowManager::update's three bytes are where OUR body ends
  and retail keeps going -- one more call and a tail call. When the differing
  offsets are the LAST bytes of the row, the bodies are different lengths and
  the number is missing behaviour, not drift.

  TWO FACTS AT ONCE.  WorkerAIUpdate::isCurrentlyFerryingSupplies has three
  offset bytes with deltas +0x14, -4, -4 across two different classes. A single
  lever cannot close a miss whose deltas disagree.

So read the DIFFERING BYTES before costing a miss, and check three things in
order: is the row a 5-byte jmp stub (then the number is noise), do the diffs sit
at the end (then it is a length difference), do the deltas agree (then one lever
might close it). A miss(1) is not nearer to landing than a miss(9); it is just
smaller evidence of whatever it is.

## CORRECTION: the gap rule is dead; use the LIVENESS test

`Drawable::getID` falsified it within the hour. Retail reads +0x100, this tree
reads +0x8C, the accessors either side both AGREE at retail's offsets
(getInstanceMatrix +0xD4, getFullyObscuredByShroud +0x148), and +0x100 sits in
the gap between them. The gap rule calls that a second member. It is not -- it
is ONE member declared in the wrong position, and the row lands 7/7 by pointing
at +0x100.

**What survives:**

  * A RUN of consecutive members at a CONSTANT delta is still a reliable
    shifted-class positive. GameWindow's four members, all exactly +4.
  * **The liveness test, which replaces the gap rule entirely: does retail use
    OUR offset anywhere -- an accessor, or a matched body? If nothing does, our
    offset is the error and there is one member.** A question about evidence,
    not about shape.

**Reclassified:** LANGameInfo PASSES -- +0x360 by get/setNext, +0x398 by three
matched bodies. Drawable FAILS -- one misplaced member. Script is UNRESOLVED:
its +0x20 has no accessor and no matched body, only retail's bytes in the one
function that cannot land, which is good evidence the OFFSET is real and no
evidence that +0x20 and +0x28 are two members rather than one relocated one.

**So "BFME classes carry two links" rests on ONE solid case, not two.** Treat it
as a single-witness observation and do not let it steer a diagnosis.

The mechanism of the error is the part to keep: two positives, a rule built to
explain both, shipped without a case that could have falsified it. The liveness
test was the falsifiable version and something cheaper was substituted for it.
A rule that explains every case you have is not evidence -- it is a description
of the cases you have. Find the case that would break it BEFORE writing it down,
and if you cannot construct one, say the rule is untested.

## BFME overloads on integer signedness where the reference has one function

Two sightings, and -- given the entry immediately above -- recorded as an
observation rather than a rule, with no case yet sought that would break it.

    ?setFlashColor@Drawable@@QAEXH@Z   at 0xD0    Int
    ?setFlashColor@Drawable@@QAEXI@Z   at 0x164   UnsignedInt
    ?winSetLayout@GameWindow@@QAEH...  at 0x00478E10
    ?winSetLayout@GameWindow@@QAEX...  at 0x0026ED70   (return type, not a parameter)

MSVC encodes both the parameter types and the return type, so these are distinct
symbols sharing a source name. The practical consequence is the one already
recorded for winSetLayout: a header declaring one spelling cannot serve the TU
that defines the other, and a matched row for one says nothing about the other.

## THE MARKER QUEUE, MEASURED END TO END

273 destinations, one compile each. This supersedes every estimate:

    5,182  markers with NO ledger row -- a body present in the tree with no
           matched retail address behind it. Not foldable by anything. This is
           AUTHORING work, and it is the overwhelming majority of the queue.
      792  miss verdicts; dropping 5-byte jmp stubs, whose miss counts are
           meaningless, leaves ~493 real ones
      217  errors -- the symbol is not in the destination's object at all
           (donor-private spellings, ICF twins)
       46  MATCH, collapsing to 16 distinct symbols, of which 10 landed

The six MATCHes that did not land each failed differently, and the distinctions
matter: two needed per-symbol `--apply`; two have no cluster at all so the fold
is not expressible as a merge; one was already home (donor equals destination);
one has its donor under `reference/`, which is a different decision entirely.

The ten destinations judged "at floor" were screened too: ZERO MATCHes. That
call is now measured rather than assumed.

**Do not budget a lane against the marker count.** The queue is ~5% foldable and
~85% unclaimed bodies.

## A small miss(N) is a CLASSIFICATION, not a distance

Every miss(1) and miss(2) opened fell into one of four buckets, and the number
does not tell you which:

  * **A constant BFME changed.** WeaponSet's three miss(1)s are all "loop to 4"
    where ZH's WEAPONSLOT_COUNT is 3 -- BFME's weapon set has a fourth slot.
  * **A field offset.** `User::setName` is `add ecx,0x4C` against our `add ecx,4`:
    one byte, seventy-two bytes of layout behind it.
  * **A TRUNCATION -- the one most easily misread as drift.**
    `W3DSnowManager::update`'s three bytes are where OUR body ENDS and retail
    keeps going: `mov ecx,esi / call / mov ecx,esi / pop esi / add esp,4 / jmp`.
    BFME's snow update does two more things per frame than the ZH body. A miss(3)
    at the end of a row is a MISSING FEATURE, not an offset.
  * **Two facts at once.** `WorkerAIUpdate::isCurrentlyFerryingSupplies` has
    deltas +0x14, -4, -4 across two classes. No single lever closes a miss whose
    deltas disagree.

Three checks before costing a miss: is the row a 5-byte jmp stub (its miss count
is meaningless); do the diffs sit at the END of the row (truncation, not drift);
do the deltas agree (one lever, or several).

## A register-allocation wall moves on a TU FLAG, never on a source rewrite

The zero-register hoist is a class now, not a one-off -- it has blocked three
bodies. The instructive part is what beat it the one time it was beaten: a TU
FLAG (a string shim on the cl line), not a source shape. Seven separate source
rewrites of `RequestSetName` produced nothing at all.

That is the cost rule. When a body is exact in size and structure and differs
only in which registers hold which values, rewriting the source is close to
free of information: MSVC's allocator is responding to what the TU declares and
includes, not to how you spell the statement. Reach for the cl line -- a shim,
an inliner flag, an STLport knob -- or record the wall and move on.

Two corollaries already in this file, now with a shared cause: a fresh view can
make a body WORSE by moving allocation more than the corrected offset was worth
(objectChangedTeam, 62.4% to 29.7%), and six correct offsets applied at once did
exactly that. Same mechanism, opposite direction -- allocation is a TU-level
response, so TU-level inputs are the only reliable lever on it.

## TWO defects can MULTIPLY to a pass: six green GameWindow rows are false

The worst case in the tree, and the one that most needs stating plainly. Six
currently-MATCHED rows are green because a wrong row->address BINDING and a
wrong LAYOUT cancel each other. Fix either alone and all six go red.

Retail emits NINE draw-data setters, three groups of three, with array bases
0x48 / 0xB4 / 0x120, element stride 0x0C and fields at +0x00 Image, +0x04
Color, +0x08 BorderColor:

    0x00478FE0 byte 0x48    0x00479010 byte 0x4C    0x00479040 byte 0x50
    0x00479070 byte 0xB4    0x004790A0 byte 0xB8    0x004790E0 byte 0xBC
    0x00479120 byte 0x120   0x00479150 byte 0x124   0x00479190 byte 0x128

This paragraph first said SIX, and that the three `winSet*BorderColor` bodies
were never emitted. **That was wrong** -- they exist, parked under placeholder
`?dup_004790XX@@YAXXZ` names. See "CORRECTION: the GameWindow BorderColor
bodies DO exist" below for how they were found and for what the mistake
teaches. The cancellation described here is unaffected: it is a uniform
one-field rotation across all nine rows rather than six bodies with three
missing, which if anything makes it tidier -- there is no retirement to decide,
only a rebinding.

Every row in the family is bound ONE FIELD TOO HIGH. Our GameWindow is 4 bytes
short at the front, so our `.color` write lands on retail's `.image` byte and
our `.borderColor` lands on retail's `.color` byte. Verified against our own
object rather than inferred: our compiled `winSetEnabledColor` is
`lea [eax+eax*2+0x12]; mov [ecx+eax*4]` -- instruction for instruction retail's
`winSetEnabledImage`.

**So the qualifier this file has needed all along:** a matched row proves the
offsets it COMPILES, never that the RIGHT FUNCTION compiled them. Where a class
is uniformly shifted and the fields are a contiguous same-size run, an
off-by-one-slot name binding is invisible to the gate, because the shift
supplies exactly the error that cancels it. "The already-matched rows are the
proof" holds only for offsets, not for identity.

The repair is in the LEDGER, not the header:

    winSetEnabledColor   0x478FE0 -> 0x479010
    winSetDisabledImage  0x479120 -> 0x479070
    winSetDisabledColor  0x479070 -> 0x4790A0
    winSetHiliteColor    0x479120 -> 0x479150
    the three BorderColor rows have NO retail body at all
    winSetEnabledImage and winSetHiliteImage were already correct

## A detector for mis-bound rows that offsets alone cannot find

An address claimed by **2+ distinct row names**, where **at least one is matched
and at least one is not**, AND the names are **same-family functions that cannot
possibly compile identically** -- so ICF cannot explain the sharing.

In the GameWindow cluster that flags exactly the three real defects and nothing
else. The fourth multi-named address there,
GameWinDefaultInput/GameWinDefaultSystem at 0x006CF680, is a genuine ICF fold of
two identical default handlers, and the family test is what separates it.

Ledger-wide there are **1032 addresses carrying 2+ names**. Most will be honest
ICF. The family test is the only cheap thing that distinguishes them, and this
class of defect cannot be found by reading offsets, because the offsets agree --
that is the whole problem.

The same defect nearly produced a second false green deliberately:
0x00478EB0 is claimed by both winSetPrev and winSetTooltipFunc; the body writes
0x1EC, retail's m_tooltip is at 0x1EC and m_prev at 0x1FC, and our class is 16
short there. winSetTooltipFunc is the true owner. Landing winSetPrev would have
authored a false green on purpose.

## A pad that must be UNDONE at every call site is a wrong layout

`vertmaterial.h` carried a deliberate `unsigned int _bfme_vmat_v0` pad ahead of
MaterialOld. `MeshMatDescClass_Do_Mappers_Need_Normals_Thunk.cpp` then carried
two `reinterpret_cast<unsigned char *>(mtl) - 4` adjustments, subtracting that
pad back off every VertexMaterialClass pointer before calling through it.
Deleting the pad makes those casts unnecessary and the body matches.

Treat a correction that has to be reversed at each use as evidence against
itself. It is the same tell as a matched TU declaring a local class to work
around a shared header: the workaround marks where the shared artefact is wrong.
`meshmatdesc.cpp` had independently reached the same conclusion from different
evidence and worked around it by including the reference header through angle
brackets -- two separate per-file workarounds for one wrong dword.

## Enumerate a header's includers with a SOURCE GREP, not the deps sidecars

The sidecars record what THIS worktree has compiled, not what includes what. A
per-file enumeration built from them missed
`MeshMatDescClass_Do_Mappers_Need_Normals_Thunk.cpp` entirely, and only the full
gate caught it. Use the sidecars to learn which header a TU actually opened;
use a grep over sources to learn who includes a header at all.

## `g_bfme5ParseVtable` names three different globals

`?g_bfme5ParseVtable@@3PAXA` resolves to three addresses -- 0x0108B1B8,
0x0108D638 and 0x0108D748 -- one for each of `bfme5MakeParseNodeA`, `B` and `C`
in `Code/GameEngine/Source/Common/Bfme5NodeMakers.cpp`, each at +0x11.

One placeholder name standing for three distinct vtables is exactly what the
DIR32 check exists to catch, and it fails the gate for the whole tree: a header
or shim change makes the pre-commit hook run the FULL gate, so this blocks every
lane, not only the one that introduced it. Three distinct globals need three
distinct names; a shared placeholder asserts they are one object.

## The DIR32 check only fires once a SECOND base exists

`Bfme5ReadyQueue.cpp` declared `extern PartitionManager *ThePartitionManager;`
locally in the TU and used it twice in `bfmeIsShrouded` -- a shroud predicate
reaching the shroud manager through the wrong name. The check caught it within
hours, which is the argument against ever whitelisting it.

But note the limit honestly: **it catches a misnamed global only once a second
base exists.** A new file that declares the extern itself and is the ONLY
reference to that name passes silently while being just as wrong. The
declaration being TU-local is what makes this recurrable -- nothing in the tree
prevents the next new file from doing the same, and the ledger's own pin for the
correct name does not help, because the wrong name never has to resolve against
it.

If this recurs a third time, the fix is a positive check -- every global a TU
declares `extern` must have a symbols.csv pin agreeing with the address its
references resolve to -- not another rename.

## `this` is not always the entry pointer: measure the base, and use a control

`GarrisonContain::getApparentControllingPlayer` is 88B/88B with nine differing
bytes, all member offsets. The first views moved every offset by a constant
-0x20 rather than fixing anything, which is what proved the mechanism: MSVC
treats `this` in that method as **the entry pointer minus 0x20**, so a
`this`-relative view needs +0x20 on the number you want to see in the
instruction.

Two things made that a measurement rather than a guess. The file's own
`findConditionIndex` already documented the same base ("m_object at module+0x08")
-- independent corroboration already sitting in the file. And the fourth view,
on the `observingPlayer` PARAMETER, needed no adjustment and landed first time,
which isolates the effect to `this` specifically. **Keep a view that should not
need the correction as a control**; without it, a uniform shift looks like a bad
view rather than a different base.

Corrected targets: m_object at this+0x08, hide flag at this+0x9b5, m_originalTeam
at this+0xd4, Player's default team at observingPlayer+0x230.

## SYMBOLIC vs VIEW-BASED: the sharpest form of "a matched row proves bytes"

The rule that made Squad decidable, in the form it was actually used:

**A symbolic matched row is evidence about the header, because the COMPILER
chose the number. A view-based matched row is not, because the AUTHOR did.**

Squad.cpp has two matched rows naming the member symbolically -- `m_objectIDs.size()`
and `m_objectIDs.push_back(objectID)`, no view anywhere near them:

    getSizeOfGroup  0x000ED420  mov eax,[ecx+0x0C]; sub eax,[ecx+0x08]; sar eax,2
    addObjectID     0x0036B770  mov eax,[ecx+0x0C]; mov edx,[ecx+0x10]; add ecx,8

start +0x08, finish +0x0C, end_of_storage +0x10 -- this tree's two-vptr layout
exactly. So retail's Squad IS our Squad and the +0x04 claims are the error, which
is the liveness test answering positively: retail does use our offset.

That indicted a row nobody was looking at. `?removeObject@Squad@@` at 0x0018B620
is matched only through an inline `struct BFMESquad { char pad[0x04];
VecObjectID m_objectIDs; }`, and its retail bytes `lea edi,[ecx+0x04]; mov
esi,[ecx+0x08]` agree with that view while contradicting both symbolic siblings.
It sits one body after 0x0018B520 and both read a container at +0x04 -- siblings
of each other, not of Squad.

## CORRECTION: the GameWindow BorderColor bodies DO exist

An earlier reading concluded that nothing writes +8, so the three
`winSet*BorderColor` functions were never emitted and their rows had no retail
body. **That was wrong**, and acting on it would have thrown away three genuine
claims. They are emitted, and already parked under placeholder names as
`?dup_004790XX@@YAXXZ` in GameWindowBorderColorSetters.cpp.

Nine prologues in 0x478F80..0x4791E0, three groups of three, element stride 0x0C:

    0x478FE0 base 0x48    0x479010 +0x4C   0x479040 +0x50
    0x479070 base 0xB4    0x4790A0 +0xB8   0x4790E0 +0xBC
    0x479120 base 0x120   0x479150 +0x124  0x479190 +0x128

Fields are +0x00 Image, +0x04 Color, +0x08 BorderColor, so the true mapping is
Image/Color/BorderColor in address order within each group. Every Color and
BorderColor row is one field low; only winSetEnabledImage and winSetHiliteImage
are correct. A uniform one-field rotation -- the VertexMaterialClass shape again,
and byte-verifying for the same reason.

The lesson beyond the correction: **"no body writes that offset" is a claim about
what you enumerated, not about what exists.** Nine bodies were in one address
range and only six had been listed. Count the prologues in the range before
concluding a function was never emitted.

## Two placeholder conventions, for two different things

  * `?j_XXXXXXXX@@YAXXZ` -- an ILT thunk claimed by ADDRESS, 5 bytes, no identity
    claim. 1,048 of these in gen_small.
  * `?dup_XXXXXXXX@@YAXXZ` -- a REAL BODY whose identity is unknown or disputed,
    parked under its address.

So a mis-anchored row is re-homed to whichever fits its SIZE: a 5-byte jmp stub
becomes `?j_`, and a 38- or 62-byte real body becomes `?dup_`. Neither throws
away the byte coverage, and neither asserts an identity the evidence does not
support.

## Re-homing a mis-anchored row: the recipe, and why `object-symbol=` is the trick

Retiring a false row throws away real byte coverage. Re-homing keeps it:

  1. retire the false-named row and tombstone it in `reverse/deleted_rows.csv`
     with the evidence, so a union merge from an older branch cannot restore it;
  2. `add_match '?j_00048b9e@@YAXXZ' 0x00048B9E 5 <donor> \
         --notes 'object-symbol=<the symbol the donor actually emits>;...'`

**`object-symbol=` is what makes it work.** The row's NAME becomes
address-derived and claims nothing, while the byte comparison still knows which
emitted symbol supplies the bytes. Coverage unchanged, identity claim gone, no
file deleted. AutoHealBehavior verified as it stood: `Functions: OK 1/1 matched`.

Deletion is the fallback for the case re-homing cannot reach -- the three
AsciiString rows went that way because their donor held nothing else, and
`verify_source_claims` forbids a row-less .cpp. That took the matched total
161787 -> 161784, stated in the commit message. **An honest decrease beats a
total you cannot trust**, and the tombstone reason carries what the false rows
were hiding: retail's TeamsInfoRec::addTeam and ::removeTeam are UNLOCATED.

## The FILE name describes the C++; the ROW name describes the bytes

They are allowed to differ, and after a re-homing they must.

`AutoHealBehaviorCtorThunk.cpp` keeps its name even though its row is now
`?j_00048b9e@@YAXXZ`, because the file genuinely does declare AutoHealBehavior's
constructor -- that declaration is precisely what makes the compiler emit a
tail-call thunk of the right shape. The name is accurate about the SOURCE. What
was false was the ROW's claim that those five bytes ARE that constructor, and
that claim is what got removed.

So do not rename these donors. Renaming rewrites every row's `source` in a
union-merged ledger for a benefit one comment already delivers -- and the
comment is mandatory: without a line saying the class name is there to shape the
emitted thunk and is not an identity claim, the file is a trap for the next
reader.

## Worktrees do NOT isolate the stash stack

The one-lane-per-worktree rule protects the working tree and the index. It does
not protect `refs/stash`, the reflog, or the object store -- those are one per
REPOSITORY, shared by every worktree of it.

A lane stashed WIP by explicit path, and while it worked, another lane pushed a
stash labelled "HOLD until dir32 green". That put the HOLD stash at `stash@{0}`,
so the first lane's subsequent bare `git stash pop` applied SOMEONE ELSE'S held
work into its tree and dropped their stash ref.

Recoverable, and worth knowing how: back up the working state, re-create the
dropped ref from its commit with `git stash store -m '<original message>'
<sha>`, return the affected files to HEAD, then pop your own by explicit ref.

The rule is in AGENTS.md now: never `git stash pop` bare, and prefer a patch
file or a temp branch, which no other lane can consume.

**Corollary for push_retry.sh:** it refuses a dirty tree and says so, which is
correct -- another lane's uncommitted edit is not yours to rebase over. Do NOT
add `rebase.autoStash`; autostash pushes and pops through the same shared stack,
so it reintroduces exactly this race. Use
`git -c rebase.autoStash=true pull --rebase` deliberately and only when you have
read the stash list, or better, wait for the tree to be yours.

## ICF needs identical RELOCATIONS, so relocations decide it -- not size
**FALSIFIED AS A RULE ABOUT IDENTITY. Retail folds constructors that store
DIFFERENT vftables. This test says whether two bodies are byte-identical; it
does NOT say whether a shared address is a mis-anchoring. See "a call site beats
stub topology" below. It cost five wrong retirements.**

The ambiguous middle of the mis-anchored list was framed as a size question:
bodies between 32 and 130 bytes where an ICF fold is a live alternative to a
mis-anchoring. Size is the wrong axis. **ICF folds bodies that are identical
INCLUDING their relocations**, so two constructors that store different vftables
cannot fold however small and however similar their code.

That makes it decidable rather than a judgement call:

  * read both candidate bodies' relocation lists (`read_object_symbol_bytes`
    returns `(body, relocs)`);
  * if the targets differ -- different vftables, different string literals,
    different callees -- ICF is IMPOSSIBLE and a shared address is a
    mis-anchoring, whatever the size;
  * if the targets are identical, an ICF fold is genuinely possible and the row
    may be correct bookkeeping that merely looks odd. Log it, do not convert it.

This is the same instrument that named the two vftables behind the
`/DBFME_MODULE_NO_MPO` diagnosis. When a diff or an identity question lands on a
masked DIR32, read the relocations rather than the disassembly.

## Caller counts go silent exactly where the topology test earns its keep

All four constructor thunks re-homed in one pass had caller counts of **1
against 1**. The histogram that cracked the AsciiString case -- 6,947 sites
against one -- says nothing at all here.

That is the argument for keeping both discriminators rather than the one that
fired first. Caller counts settle a case where an import thunk serves the whole
binary; the topology test (incremental linking emits ONE thunk per function, so
a body already matched under name B with exactly one stub reaching it owns that
stub) settles the case where both counts are one, which is most of them.

## Re-homing is duplicate-prone in a way ordinary folds are not

A retire-plus-add-match writes the SAME ADDRESS twice in one commit, so any
concurrent rebase has two rows to union. A duplicate `?j_00048b9e@@YAXXZ`
appeared exactly this way and pre-push caught it -- the documented case, fixed
with ledger_io keeping the first, never dedup_csv.

Expect it on every re-homing commit and check `check_csv` before pushing rather
than after the rebase surprises you.

## Quote the heredoc when a commit message contains backticks

`git commit -F -` with an unquoted `<<EOF` lets the shell execute backticks and
`$` inside the message; two phrases vanished from one message this way and a
word from another. Use `<<'EOF'`. Amend before pushing if you catch it; do not
force-push over shared history to fix prose if you do not.

## A detector that goes quiet has finished; bucket the leftovers, do not list them

The ILT identity sweep ran to exhaustion: five rows re-homed, three retired, and
the 62 survivors of the unique-stub test bucketed by the RELATIONSHIP between the
claiming name and the body's name:

    25  FX getClass<T> -> getInstance<T>                       real tail call
    13  ~ConcreteModuleTemplate<Tag> -> ~<Name>ModuleTemplate  one dtor, two spellings
     4  same-class pairs reading as genuine tail calls
     5  cross-class constructors -- the shape that was real
    15  cross-name oddities needing individual reading

**47 of the 62 need nobody.** That count is the artefact worth having: a bucket
tells the next agent which rows to stop re-deriving, where a raw list of 62
invites the whole investigation again.

And the honest limit of the instrument, from running it to the end: **the
topology test is decisive when the two names are UNRELATED and the body is
large, and it stops separating cases as soon as the names are related** -- a
template spelling against a typedef spelling, a method against its own class's
operator=, a getter against its own instance accessor. It found the real defects
and then went quiet. That is correct behaviour for a detector, but it means the
remainder is judgement rather than screening, and should be labelled as such
instead of left looking like a backlog.

Every survivor that shared the acted-on shape had its own reason to stop:
`??0SupplyWarehouseCripplingBehavior@@` points at a 154-byte body claimed by SIX
names, which is either a large ICF group or a defect bigger than one row;
`??0SimpleParameterClass<int,0>` points at a body claimed by two ClientBehavior
constructors from one file, an ICF twin pair.

The sharpest thing left is a multi-name case rather than a topology one:
**0x0000B9CE**, where `?getClassMemoryPool@ObjectDefectionHelper@@` and
`?Clear@VectorClass<TangentsClass>@@` -- two entirely unrelated names -- both
claim a stub jumping to a 74-byte `?reset@NetCommandList@@`.

## A finding is only as durable as the instrument that produced it

Two of the most productive scripts in this effort -- a batch screener that made
a 273-destination sweep affordable, and a multi-name-per-address detector that
rediscovered a known defect unaided from 1,041 addresses -- were reported as
"built and validated" while living in a session scratchpad. The commit named as
building the detector changed one line of `re_attempts.log`.

The findings landed. The instruments did not. That leaves numbers in a log that
nobody can reproduce, extend, or check -- and the scratchpad directories on this
machine hold a dozen dead one-off scripts from earlier sessions (`vtab.py`,
`vt2.py`, `vt3.py`, `vorder.py`) that were each presumably worth something once.

Two rules. **Land the instrument in the same stretch as the finding it
produced**, with tests, or the finding degrades to an anecdote the moment the
session ends. And when reporting, **say "built, not yet committed" when that is
what happened** -- a table of commits is the thing a reader is least likely to
re-derive, and the difference between planning around a tool and planning around
an idea is total.

Ephemeral scratch is correct for a one-off probe answering a question you will
never ask again. It is wrong for anything that produced a number you reported.

## A marker must be ADJACENT to its definition: explanation goes ABOVE it

`find_declared_unmatched` reads a marker as declaring the body that FOLLOWS it.
Twenty lines of explanation inserted between the marker and the code made the
hook read the body as undeclared, and the pre-commit failed.

    // why this row is re-homed, at whatever length              <- explanation
    // ?dup_0018b520@@YAXXZ present-unmatched                    <- marker
    void Squad::isOnSquad(...) { ... }                           <- the body

Never between the marker and the code. This bites precisely when documenting a
re-homing in place, which is exactly when the explanation is longest.

## batch_screen's safety contract is the INVERSE of marker_screen's

marker_screen clears a marker to ask its question, so it MUST restore it, even
on BaseException. batch_screen must never have cleared one, because a marker is
a comment and cannot change what the compiler emits -- which is the whole reason
one compile answers a destination's entire marker list.

So its first test is that contract: **it never writes** -- not the source, not
the ledger. If it ever starts editing to get a better answer, it needs the
restore machinery, and that test should fail loudly rather than be relaxed. Two
tools, opposite invariants, each pinned by the test that would catch the other's
bug.

Its other tests encode things this effort learned expensively: a truncated label
resolves only when unambiguous (two overloads sharing a prefix return
`ambiguous`, never a guess); an unknown label is REPORTED, not skipped, since
~2,000 of ~3,000 markers name no row and that is the largest bucket; a miss
reports its byte count; and `moves` counts only rows a marker HERE names -- the
miscount that turned one lane's eleven ready rows into two.

## CORRECTION: compare relocation STRUCTURE, not relocation NAMES

"Compare the claimants' relocation targets" was the instruction given, and the
obvious reading of it is actively misleading. Measured against 1,041 multi-name
addresses:

  * **Target NAMES flags 367 and is useless.** Two classes' constructors name
    different vftables -- but that is a masked DIR32 the byte comparison never
    sees, so this flags every template and module family in the tree.
  * **REL32 call targets only gives 225 and still over-flags.** One function
    under a C and a C++ decoration (`?png_handle_IHDR@D3DX@@` against
    `_png_handle_IHDR@12`) and per-instantiation template symbols resolve to
    different names for the same call.
  * **Structure is decisive: 11.** Mask every relocation site to zero in BOTH
    bodies, then compare the remaining bytes AND the `(offset, type)` list.

The reasoning is the important part: two ICF-folded bodies **are the same
bytes**, so their relocation SITES must coincide however differently our objects
happen to name the targets. Names are a property of our compile; sites are a
property of the code.

Final classification of 1,041 multi-name addresses: **965 real folds, 65
all-placeholder, 11 that cannot be one body.** 976 of 1,041 need nobody.

## Five of the eleven are GameWindow, and four were new

    0x00478EB0  winSetPrev           | winSetTooltipFunc
    0x00478E40  getEnergyBonus       | winGetPrevInLayout
    0x00478E30  getEnergyProduction  | winGetNextInLayout
    0x00478710  getContain           | winGetEnabledTextBorderColor
    0x00478490  getFrame@GameLogic   | winGetStyle

Each pairs a GameWindow accessor with an unrelated accessor of a DIFFERENT
CLASS at one address, matched claimants on both sides. The detector was told
nothing about GameWindow and rediscovered 0x00478EB0 unaided, which is the
reason to trust the other four.

**The six of the eleven deliberately NOT called** are large trivial-constructor
groups -- 24 names at 18 bytes, 40 at 9, 17 at 16 -- where at least one member
compiles differently here. The likelier fault is our compile of one member than
a 40-name group being wrong. A detector saying "these cannot be one body" is
evidence about the group, and when the group is that large the evidence points
at the odd member first.

## The funclet self-heal searched the wrong section, and 18,690 rows cannot heal at all

`funclet_candidates` re-identified a renumbered `$L` pin by searching the section
holding `__ehhandler$<parent>`. But MSVC 7.1 gives that handler a COMDAT OF ITS
OWN, while the `$L` funclet bodies stay in the PARENT function's section. In
StagingRoomGameInfo.obj the parent is section 342 and its handler 343, and all
eighteen ehhandlers in that object split the same way -- so the search returned
no candidate and the row died on its stale pin.

The symptom is opaque: a one-line view shifts two pins by two and the build stops
on `ValueError: symbol not found in object: $L70459`, naming a compiler-local
label and nothing else, while the body sits in the object as `$L70461`. Fixed by
searching the parent's own section as well as the handler's; both paths still go
through `holds_funclet` and a group of look-alikes still fails loudly, so this
widens where evidence is sought without picking anything on faith.

**RETRACTED: there is no tree-wide tripwire.** This entry claimed 18,690
parent-less `gen-funclet` rows were a hazard under every header change. Scoping
the back-fill answered the question instead of starting it. Of 20,052
`gen-funclet` rows:

    hand-edited sources    1,361 rows -- ALL carry parent=, zero without
    generated sources      18,689 without, 2 with   (gen_small/, gen_asm/)

Every parent-less row is in a GENERATED TU. Checked against git rather than
inferred: before the StagingRoomGameInfo fix there was exactly ONE parent-less
funclet row in a hand-edited TU in the whole tree, and that was the one that
froze the build. Someone had already done the annotation everywhere else; the
last gap is now closed.

The error is worth keeping: a tree-wide hazard was inferred from one instance
without checking how the instances were DISTRIBUTED. Alarm is as much a failure
of measurement as complacency, and it is the easier one to feel virtuous about.

What survives is a REGENERATION risk, not an edit risk: if whatever produces
`gen_small` re-emits those TUs with different label numbering, 18,689 rows go
stale at once and none can self-heal. Not urgent, not blocking, worth someone's
judgement before a regeneration.

The back-fill method, if it is ever needed: build the TU, find the `$L` symbol
the pin names, record the non-`$L` symbol sharing its section, refuse any section
with more than one candidate owner.

## Two cheap screens that save a build

**A donor declaring a class with a method it never defines: the mangled name IS
the pin.** `ThingTemplate::parsePrerequisites` reaches retail only because its
donor declares a fake `PrereqVector` with an `erase` it never defines -- retail's
`clear()` calls a range-destroy helper where our readable `m_prereqInfo.clear()`
calls STLport's `vector::erase`, a different function. Folding it would mean
importing that fiction into a readable TU to gain one file. Grep the donor for a
declared-never-defined method before spending a build.

**A masked compare can say MATCH while build.sh says FAIL**, because masking
hides relocation TARGETS as well as addresses. A screen is a filter; a fold is
only verified by build.sh.

## Withdrawing a wrong rule about a shared tool

A lesson was logged saying `merge_cluster --apply` discards uncommitted edits to
the destination. It is wrong and was withdrawn: a later `--apply` ran over an
unstaged view in StagingRoomGameInfo.cpp and the view survived. Something else
reverted the earlier edit and the cause was never established.

The rule kept is the defensive one -- apply the view after the merge and grep
that it is still there. Worth the retraction: a wrong rule about a SHARED tool
has every other lane working around behaviour the tool does not have, which is
more expensive than the original confusion.

## The two identity detectors are COMPLEMENTARY: neither subsumes the other

The natural assumption is that the newer structural detector replaces the older
thunk-topology one. It does not, and `0x0000B9CE` is the proof.

That address carries four names -- three `?Clear@VectorClass<...>` instantiations
and `?getClassMemoryPool@ObjectDefectionHelper@@` -- and `multi_name` classifies
it as a genuine FOLD. Correctly: all four are 5-byte jmp thunks whose only
differing content is the masked rel32, so **structurally they really are
identical bytes**. It was predicted to be the detector's first confirmed hit, by
two people, and it was not.

    a STRUCTURAL comparison cannot separate thunks
        -- every 5-byte jmp is structurally identical to every other
    a THUNK-TOPOLOGY test cannot see a wrong field offset
        -- it only asks which stub reaches which body

So run both. `multi_name.py` finds defects where the offsets agree;
the unique-stub topology test finds mis-anchored ILT stubs. Each is blind
exactly where the other sees.

## A detector that CLOSES a question is worth as much as one that opens one

The 69-byte body shared by `??0DestroyDieModuleData@@` and
`??0KeepObjectDieModuleData@@` -- the ambiguous middle that was deliberately left
alone for hours because ICF was a live alternative -- classifies as a **real
fold**: identical masked bytes, identical relocation sites. Logged `refuted`.

That pile is correct bookkeeping rather than odd-looking bookkeeping, and it
comes OFF the suspect list instead of staying uncertain forever. "Twelve rows we
chose not to touch" was the right call at the time and is now a closed question
rather than a standing doubt. Prefer the instrument that can return a negative.

## Byte-verification is evidence about bytes, in both directions

Address 0x0018B520 was UPGRADED from the placeholder `?d_0018b520@@YAXXZ` to
`?isOnSquad@Squad@@…` as a "byte-verified" identity, and has now been DOWNGRADED
to `?dup_0018b520@@YAXXZ` on the evidence of two symbolic siblings. **The same 38
bytes verified both times.**

The tombstone chain records the mistake being made and unmade, which is what that
file is for. A byte-verified upgrade is not proof of identity either.

## An ICF POOL address is never identity evidence

A matched row whose address carries many names tells you only that your body
compiled to a shape many classes share. It says nothing about whose body it is.

`??0StringInfo@@QAE@XZ` at 0x0005C5D0 shares that address with **eighteen** other
constructors -- ArmorTemplateSet, ModuleInfo, Smudge, four DLNodeClass<>
instantiations, TeamsInfoRec. It is the generic "zero three pointers"
constructor, and our StringInfo lands in that pool precisely BECAUSE we made it
twelve bytes. The row is a binding to a pool the wrong layout fell into, and it
would read as proof that the layout is right.

`??_EStringInfo@@QAEPAXI@Z` at 0x0005E420 is the same, shared with five
HashTemplateClass<StringClass,...>::Entry vector-deleting destructors.

**The converse is the useful half: a UNIQUELY named row IS identity evidence.**
Retail's `~StringInfo` at 0x004368F0 is the only claimant of that address, and it
destroys exactly two members -- `lea ecx,[esi+4]` into one destructor, then
`mov ecx,esi` into a DIFFERENT one. Two members at +0 and +4, reverse order,
two different destructors: an AsciiString and a UnicodeString. That settled the
layout where the pool rows could not.

So before treating a matched row as evidence about a class, run one awk pass over
functions.csv for other names at its address. `tools/multi_name.py` answers it
directly. This has now cost two hypotheses -- check it before spending a build.

## BFME's StringInfo is 8 bytes, and a 12-byte one manufactures its own proof

`{ AsciiString label; UnicodeString text; }` -- no `speech` field, where ZH has
three members and this tree copies it. Three independent strands:

  * the uniquely-named `~StringInfo` destroys exactly two members (above);
  * `GameTextManager::reset` and `::deinit` both pass **8** as the element size
    to the vector destructor iterator `??_M@YGXPAXIHP6EX0@Z@Z` where our twelve
    bytes make us pass 0xc -- the ONLY differing byte in either body, 85/85 and
    137/137 at ndiff 1, with the destructor argument relocating to
    `??1StringInfo@@QAE@XZ` on both sides;
  * dropping `speech` reddens exactly two rows, and both are ICF pool members
    that prove nothing.

The circularity is the thing to notice: the twelve-byte struct is what puts our
constructor in a nineteen-name pool, and the pool membership then reads as
confirmation. A wrong layout can manufacture the evidence that appears to support
it.

## A this-ADJUSTMENT residue cannot be viewed, even in principle

The strongest form of "a view is only honest when the number it encodes is the
member's real offset from the pointer the compiler actually holds".

`WorkerAIUpdate::isCurrentlyFerryingSupplies` is entered with the
`SupplyTruckAIInterface` sub-object at +0x204, so retail's `mov eax,[ecx+0xe0]`
and our `[ecx-0x124]` differ by exactly that adjustment. A view written to force
retail's encoding would read `object+0x204+0xe0` instead of `object+0xe0` -- it
would **byte-match while reading the wrong member**, and the gate cannot tell the
difference. `RTS2DScene::draw` is the same in one instruction.

So where the residue is a this-adjustment from base-class ordering, the recorded
refusal is CORRECT and permanent, not a stale measurement waiting to be
overturned. Three written "cannot come home" verdicts were re-tested and all
three held; two held for this reason.

That is the sharpest statement of the trap this file keeps circling: **the gate
is blind to names AND to which object a displacement lands in.**

## `verify_source_claims` reports the LEDGER's status, not a byte comparison

Its stale-annotation complaint used to read "X is byte-verified matched from
this file", which sounds like proof. It is not: `matched_sources` is the ledger's
status column, and `merge_cluster --apply` sets that status without building. So
immediately after an apply the message asserts a verification nobody performed.

It cost a near-miss. A repointed row was believed proven, an overturned verdict
was almost written into a source comment, and the build disagreed. The message is
reworded now and pinned by tests -- it names the ledger as the source of the
claim and points at `./build.sh` as the thing that would settle it.

General form, and it has bitten twice today: **when a check's message and a
check's implementation disagree, agents follow the message.** check_csv's
duplicate hint was the other one. Fix the wording where it is emitted; docs do
not reach the moment of decision.

## BFME's LANMessage enum carries two extra types, and the enum is POSITIONAL

`LANAPI::setIsActive` stores the type constant directly and reproduces retail
byte for byte: the wire byte is 0x10 where a build from the reference enum
computes 0xe. Two additional message types sit ahead of `MSG_INACTIVE`.

Because the enum is positional, **every type after the two additions is
renumbered by two**. Two clients built from the two enums would not merely
disagree about inactive announcements -- each would misread every later type as
its neighbour two places down. The two extra types are not identified yet; only
that there are exactly two. Recorded in docs/lan-testing.md as behaviour.

## Validate a proposal by running the REAL consumer, not a reimplementation

The funclet back-fill tool does not merely resolve a parent and write it. For
each proposal it runs the actual `funclet_candidates` and requires it to recover
the funclet before the annotation is offered at all.

That is the right shape for any tool that writes ledger annotations another tool
consumes. A reimplementation of the consumer's logic can agree with the proposal
and disagree with the consumer -- which is exactly the drift that put a
measuring tool and an acting tool out of step earlier today, where merge_cluster
had the rule right and screen_cluster did not. Call the real thing.

## A THIRD kind of false green: the five-byte virtual-dispatch thunk

`0x00495580` is `8b 01 ff 60 0c` -- `mov eax,[ecx]; jmp [eax+0x0C]`. **No E9, no
jump target.** It was handed between lanes as an ILT stub and a ready-made
re-homing; it is neither.

**Neither detector can see this class.** The unique-stub topology test needs an
E9 to follow. The structural comparison cannot separate two forwarders to the
same vtable slot, because they genuinely are the same five bytes. So this joins
the E9 ILT jump and the local-replica body as a third way a row goes green while
naming the wrong function -- and it is the first one no instrument catches.

**What caught it was SIZE AGAINST SIBLINGS.** The three other
`reverseAnimateWindow` implementations in retail are 260 to 263 bytes --
SlideFromBottom 0x004966E0, SlideFromTop 0x00496260, SlideFromRightFast
0x00497760. A real one is not five bytes of forwarding. The row verified only
because its `object-symbol` pinned it to the first five bytes of an unrelated
function, and ANY method forwarding to vtable slot +0x0C compiles to exactly
those bytes.

That heuristic -- compare a row's size against its named family's siblings -- is
cheap, is in neither tool, and is the obvious fourth pass.

Re-homed to `?dup_00495580@@YAXXZ` rather than `?j_`: a real body of unknown
owner, not an ILT entry. `?j_` is for a 5-byte E9 claimed by address; this is
five bytes of something else.

## Re-derive a row handed over pre-diagnosed, from the bytes

The premise travelled between two lanes and a team lead and was wrong at every
hop: "a 5-byte ILT row whose destination already compiles it byte-exact." It was
not an ILT row, and `batch_screen` on the destination returns
`error symbol not found in object: ?init@ScriptActions@@UAEXXZ` -- the row's
`object-symbol` exists only in the donor, so a repoint could never have verified.

Ten minutes of reading bytes stopped a repoint that could not have worked. **A
diagnosis arriving from another lane is a hypothesis with a good prior, not a
finding**, and the cost of re-deriving it is far below the cost of acting on it.
This applies with most force to the relay in the middle: a lead passing a lane's
diagnosis onward launders it into fact.

## When two measurements of the same thing DISAGREE, the finding is the disagreement

The single most expensive one-line decision of this effort, and it is worth
stating as a rule because the reasoning felt entirely normal at the time.

An enumeration of the GameWindow draw-data bodies was run twice. A loose grep
returned 0x479040, 0x4790E0, 0x479190. An exact mangled-name grep returned
0x479010, 0x4790A0, 0x479150. Two answers to one question. The exact one looked
more trustworthy, the loose one was written off as an artifact in a single line,
and the report that followed claimed three retail bodies had never been emitted
at all.

**The exact grep reads the LEDGER's bindings -- which were the thing under
suspicion.** So a contradiction was resolved by trusting the very source being
audited, and the loose grep, which had stumbled onto the real bodies, was
discarded. All nine bodies exist; they were parked under `?dup_004790XX@@YAXXZ`
placeholder names, which is precisely why a search for the real names found
nothing.

Neither measurement is "the corrected one" until you know WHY they differ. A
discrepancy is data. Write off a discrepancy and you have chosen an answer
without reading the evidence that would have chosen it for you -- and if one of
the two methods reads the artefact you are auditing, it is the one to distrust.

## Log both hypotheses when one call site cannot choose between them

`DX8Wrapper::Set_Gamma` agrees on 482 of 568 bytes. Retail's gamma call pushes an
extra leading zero and uses vtable slot 0x54 where the d3d8 shim gives
`SetGammaRamp` two arguments at 0x48 -- which is the D3D9 signature shape.

The tempting conclusion is that BFME is a D3D9 title. It was NOT drawn, and the
reason is the right one: all 101 rows in `dx8wrapper.cpp` are matched and their
retail bytes call slots up to 0x178, several above 0x54, so the shim's ordering
is correct everywhere those rows touch. One call site cannot distinguish "the
shim mis-places this one method" from "this method goes through another
interface", so the log records both and picks neither.

A single observation that would rewrite a large shared assumption is exactly the
one to hold rather than bank -- especially when a hundred matched rows already
constrain the same artefact.

## A FOURTH false green: the adjustor thunk, and it has MORE real bytes than the others

    0x00C2787D   add ecx,0x194 ; jmp 0x0000D828
    0x0000D828   jmp 0x0005EE90   =   ??1AsciiString@@QAE@XZ

Eleven bytes that adjust `this` by 0x194 to reach an AsciiString member and
destroy it. Two rows claimed it -- `?addTeam@SidesList@@` and
`?removeTeam@SidesList@@`, neither of which is a string destructor; both forward
to `m_teamrec`. They matched because the jump is masked, so the only compared
content is the add-ecx immediate, and our `m_teamrec` offset happens to equal
retail's AsciiString member offset.

**Name it separately because it has MORE compared bytes than the other three** --
six bytes of real immediate, against a 5-byte jmp's one. That is exactly why two
rows could share it and look solid. **A comparison being partly real is not the
same as it being enough.** The question is never how many bytes agreed, but
whether the bytes that agreed could distinguish this function from another.

The four classes now: the E9 ILT jump, the local-replica body, the
virtual-dispatch thunk, and the adjustor thunk. Retail's
`SidesList::addTeam`/`::removeTeam` are UNLOCATED, exactly as TeamsInfoRec's pair
turned out to be -- the same family, found four hours later, in the finder's own
file, by its own detector's FAMILY refinement.

## Redo a stale ledger patch with the TOOLS; never replay it

A held patch stopped applying once `functions.csv`, `re_attempts.log` and
`reloc_names.csv` moved under it. The source half still applied cleanly and was
kept. The ledger half was **redone with `add_match` and `merge_cluster` against
the current ledger** rather than replayed.

That is the right split and the reason is specific: replaying a stale ledger
patch is how a union merge resurrects a retired row -- the patch reintroduces
lines the tombstone was written to keep out. The tools re-verify as they go and
operate on the ledger that exists, not the one that existed when the patch was
cut.

Hold source in a patch; hold ledger work as a list of tool invocations.

**Sharpened by using it: split by REPRODUCIBILITY, not by file type.** A held
shim change spanned `functions.csv`, which an unrelated commit also needed. The
right split was not source-versus-ledger but reproducible-versus-not: the merge
was one `merge_cluster` command, so it was RESTORED and re-run rather than held,
while only the hand-written source edits stayed parked. A new shim DIRECTORY is
untracked, so it survives a rebase untouched and needs no holding at all.

Ask of each piece: can I regenerate this with one command? If yes, let it go and
re-run it. Only what you cannot reproduce needs a patch.

## A call through an ILT thunk is PERMANENTLY unreachable from source

`GameSpyInfo::removeFromSavedIgnoreList` reads 118 of 118 bytes exact and the
gate still refuses it. Retail's call at +35 lands on `?j_000052bd`, an
incremental-link thunk in gen_small, where this tree calls the map's `erase`
directly. Every other call in the body matches.

**Nothing in the source chooses whether a call goes through an ILT stub.** That
is a property of how retail's binary was linked, so no view, no spelling, no
shim and no cl-line flag reaches it. Record it as permanent, not deferred --
this is the same category as the this-adjustment residue, not the same category
as a missing header fact.

**The consequence that changes how donors are read: an `__emit` body can be
LOAD-BEARING.** It encodes the rel32 that points at the thunk, which readable
C++ cannot express. So a naked dump is not always scaffolding waiting to be
drained, and "the destination already compiles this exactly" is not sufficient
grounds to fold.

The screen is cheap and belongs in front of every fold: for each direct call in
the retail body, decode the rel32, resolve the destination in functions.csv, and
look for a `?j_` name. Running it on `Set_Transform` cleared that fold before a
build was spent; running it after would have cost one.

## A near-miss filter hides the already-perfect

A scan built to surface rows within N bytes of retail filtered out `nd == 0`
along with the rows too far away to reach. Those are the CHEAPEST wins in the
tree -- rows whose destination already compiles them exactly and whose donor is
pointed at for no reason -- and the instrument was structurally blind to them
because it was built to find near-misses.

Two folds came out of noticing it: `UnicodeString`'s default constructor (9
bytes, no relocations at all, uniquely named) and
`DX8Wrapper::Set_Transform(Matrix3D)` (682 bytes, forty relocations, every one a
data reference to a named global -- so no direct call could resolve wrongly).

Check what your filter excludes at BOTH ends. A tool built to measure distance
will quietly drop the zero.

## A CALL SITE beats stub topology, and beats the relocation argument

Five rows were re-homed on this reasoning: ICF needs identical bodies WITH
identical relocations, so two module constructors storing different vftables can
never fold, so each stub must belong to whichever class owns the body it jumps
to. **Retail folds them anyway.** All five re-homings were wrong and are
retracted.

The evidence that settles it is the caller, not the stub:

    0x00048B9E  called by friend_newModuleInstance of AutoHealBehavior,
                SpyVisionUpdate, EMPUpdate and FireOCLAfterWeaponCooldownUpdate
    0x0002A379  called by FireWeaponWhenDamagedBehavior and MobMemberSlavedUpdate
    0x0001002D  called by BridgeScaffoldBehavior and ParkingPlaceBehavior

Several classes' factories calling ONE constructor stub is direct evidence of a
real fold. Each row was a legitimate member of an ICF group.

**The rule: the unique-stub test says which body a stub REACHES. It cannot say
whose that body IS when the body is shared.** A matched caller that names the
symbol outranks any inference from topology or from relocation structure. Check
callers before re-homing anything.

Note what still stands, because it was re-verified the same way rather than
assumed: the TeamsInfoRec trio at 0x0000D828 keeps its retirement -- its 31
matched callers are all destructor paths (`_Destroy`, `__destroy_aux`,
`_M_clear`, scalar-deleting destructors), which is what a string destructor's
thunk looks like and not what `addTeam` looks like. SidesList 0x00C2787D and
0x00495580 have no matched callers at all, so they rest on their own evidence.

## Retiring a row can break a matched row in ANOTHER file, and delta verify misses it

Retiring the AutoHealBehavior row broke `?friend_newModuleInstance@AutoHealBehavior@@`
at 0x00114200 -- a 96-byte matched body in a different file -- with
`unresolved call(s)`. **The delta verify that passed when the retirement landed
only built the donor.**

So: a retirement removes a symbol from the map, and any matched row that CALLS
that symbol loses its address. Before retiring, scan matched rows for calls to
the address. The full gate is the only thing that catches this after the fact,
which is an argument for running one after a batch of retirements even when each
one verified individually.

## Keep the cautious framing when a sharper rule arrives; run BOTH

Two lanes arrived at one rule today from opposite directions, which is why it is
worth stating twice.

One had the enumeration answer in hand from a loose grep, got a second answer
from an exact grep, wrote the first off in a line, and lost the central claim of
a report. The other had a cautious size-based framing for the mis-anchored rows,
dropped it when a sharper relocation-based rule arrived from the lead, and
retracted five commits.

**Both errors are the same shape: a disagreement between two methods was
resolved by picking one, rather than treated as the finding.** The correct move
in both cases was to run both and notice they disagreed -- which costs one extra
run and would have caught both.

A sharper rule does not supersede a cautious one until they have been run
against the same case and agreed. Where they disagree, the disagreement is data
about the rules, not noise to be resolved by preference.

## None of the four detectors establishes IDENTITY

Written into `size_outlier.py`'s own docstring rather than left as folklore,
because the natural assumption is that the newest tool replaces the rest:

    the ILT unique-stub test   needs an E9, and cannot say whose a SHARED body is
    multi_name's structural test  cannot separate two forwarders to one vtable slot
    multi_name's FAMILY rule   needs two names; most stubs carry one
    size_outlier               needs siblings implementing the same method

`0x0000B9CE` falls out of `size_outlier` and multi_name correctly does NOT flag
it -- four 5-byte jmp thunks are structurally identical bytes. Each instrument
is blind exactly where another sees, so **a clean run from one is not a clean
bill of health**, and a hit from one is a candidate rather than a verdict.

**A matched caller naming the symbol outranks every inference any of them
makes.** Check call sites before touching a row.

## size_outlier: both halves of the rule are load-bearing

A row is suspect when its body is SMALL AGAINST ITS FAMILY -- at most a quarter
of the median size of the same method name across three or more classes, median
itself at least 48 bytes -- AND the body TAIL-JUMPS. A forwarder delegates; an
implementation returns.

Size alone flags 104: a virtual method may legitimately have a tiny override,
and `?onEnter@AIBusyState@@` really is three bytes. Tail-jump alone flags every
honest thunk in the tree. Together: 14, with the tests pinning both boundaries.

Sharpest of them: `?duplicate@Condition@@` at 5B against a 167B family,
`?onEnter@AIInternalMoveToState@@` 5B against 122B, `?setPingString@GameSpyInfo@@`
8B against 102B, `?Free@DistLODClass@@` 5B against 50B.

## Never validate a layout fix against the CURRENT byte output

GameWindow.cpp's `winSetPrev` body is `m_prev = prev`. Under our short header
that writes +0x1EC, and retail's byte at that site agrees -- so the body **looks
correct and is not**. `m_prev` is at +0x1FC; +0x1EC is `m_tooltip`, which a
separate matched row already claims.

So when correcting a layout, write the definitions in terms of the MEMBERS and
let the corrected header supply the offsets. Checking the result against the
bytes the current header produces confirms the bug: the agreement you are
testing against is the thing you are fixing.

Same shape as the six draw-data false greens one level up -- a body right about
its member name and wrong about where that member lives, agreeing with retail
because two errors cancel.

## Two independent derivations meeting is the standard to reach BEFORE acting

The GameWindow renames had a byte proof from one lane -- thirteen getters, each
a single load, plus the setters read against them. They also had, from the other
lane and derived independently, three ALREADY-MATCHED rows landing on the same
offsets from the opposite side of the getter/setter pair:

    matched winGetPrev reads +0x1FC   <->  the void winSetPrevInLayout writes +0x1FC
    two matched rows read +0x200 as parent <-> the void winSetLayout writes +0x200
    matched winSetTooltipFunc holds +0x1EC, so +0x1EC cannot also be m_prev

**A matched getter and a matched setter agreeing on one offset settles a
member.** Neither derivation used the other's evidence.

Worth naming because today's retractions all share the opposite shape: a single
derivation, acted on, then falsified. The five re-homings had one argument; the
six-versus-nine setter claim had one grep whose disagreement with another was
written off. Where a structural change is about to be made on inference, the
question to ask first is not "how strong is my evidence" but "is there a second,
independent route to it".

## Two fixes paid off within the hour, on TUs nobody had flagged

Worth recording because both were made on one instance and doubted as
over-fitting at the time.

`verify_source_claims`' reworded complaint -- "the LEDGER records X as matched
from this file (status only -- not a byte comparison) ... either the marker is
stale, or the row was repointed here and has not been byte-verified yet;
./build.sh settles which" -- reached the same agent who had misread the old
wording, within the hour, and it went straight to clearing the markers instead
of inferring a match. Fixing the message where it is EMITTED rather than in a
doc is the whole difference.

The `funclet_candidates` section fix caught its first unknown case the same way:
GameText.cpp's `uw_00c222b6` renumbered from `$L37642` to `$L36977` under an
unrelated struct edit and HEALED rather than freezing the build. That is a TU
nobody had identified as affected -- the fix was made against one known case and
immediately earned its keep on another.

## The gate swallowed its own error text, and we diagnosed the silence twice

`build.py`'s `run(label, check)` catches `SystemExit` so every check reports
before the gate exits once -- a good design. But it discarded `exc.code`, and
`exc.code` is where a check raising `SystemExit("<explanation>")` puts its whole
diagnosis. So this:

    uw_00c054b0 (AIPlayer.cpp): $L85894 does not hold this funclet and 2 bodies
    in the parent's group match it equally ($L85915, $L86009). Byte evidence
    cannot tell them apart, so the gate will not pick one.

was reduced to "verify_functions did not produce a patch set" -- which reads as
a crash rather than a finding. **Two people independently concluded "race" from
the absence of output**, across three full-gate runs, before anyone called
`verify_functions()` directly to recover the text.

Fixed where it is emitted: the handler prints `exc.code` unless it is an int (a
bare exit status carries no diagnosis). Third time today a tool's MESSAGE, not
its logic, was the defect -- after check_csv's duplicate hint and
verify_source_claims' false "byte-verified" claim.

**The organisational half is worth as much:** the "everyone diagnosing everyone
else's file" problem is partly a reporting problem. Four consecutive reds
belonged to a lane other than the one that hit them, and this one took three
runs to attribute only because the tool ate the evidence. A check that names its
TU and its candidates hands the right lane the right file immediately.

## An ambiguous funclet heal is a REFUSAL, not a crash

Distinct from the withdrawn tripwire, which was `symbol not found in object`.
Here the pin renumbered, the self-heal searched the parent's group, and **two
bodies matched equally** -- so it declined to pick one. That is correct: byte
evidence genuinely cannot separate them, and guessing would anchor a row on a
coin flip.

RESOLVED, and not by re-anchoring: **the two candidates were never equal.**
`$L85915` is `lea ecx,[ebp-0x1c]; jmp <AsciiString dtor>` -- retail's own
instructions with only the jump target relocated. `$L86009` is a DATA table of
four label pointers, `$L78697` through `$L78700`, whose relocations cover ALL
EIGHT of its bytes.

`holds_funclet` masks every relocation site on both sides, so **a body with no
unmasked byte left compares equal to ANY target of its length.** The table was
not matching the funclet; there was nothing left of it to compare. The tie was
between one candidate carrying byte evidence and one carrying none.

Requiring at least one surviving byte separates them without choosing between
them, and the refusal on a genuine tie still fires. Three rows healed on it --
uw_00c054b0, uw_00c054b8 and uw_00c056a0 -- and AIPlayer.cpp went 42/42.

**This is the file's own "100 percent masked is not a pass" rule, which we apply
to folds, missing from the healer that does the same masking.** Before treating
an ambiguous heal as a re-anchoring job, check whether a candidate is fully
relocated: it is not a rival body, it is an absence of evidence.

## A CONSTANT delta is a shifted member list; a SCATTERED one is a different list

The cheapest first read on any near-miss, and it tells you which kind of work it
is before you spend anything:

  * **constant delta across every differing operand** -> the members are the
    same and sit at a uniform offset. View-or-shim work.
  * **scattered divergence** -> the member LIST differs. You need the class;
    no view reaches it.

`GameInfo::clearSlotList`, `W3DTreeDrawModuleData`'s constructor and
`evaluateAsVisibleCliff` are all scattered -- header items. `Image`'s
constructor confirms it from a third direction: it initialises two members BFME
does not have, and retail's EH state byte is **1** where ours is **2**, so BFME's
Image tracks one unwindable member where ours tracks two. An EH state count is
another readout of the member list.

## A frame-size difference is SHIM work by nature, not by preference

`ControlBarSchemeManager::init` is 177 bytes with every operand identical except
three, and those differ by a uniform **0x1BF0**. Our prologue reserves 0x243c
through `__chkstk` where retail reserves 0x84c, and the body constructs a local
`INI`. So **BFME's INI is 7152 bytes smaller than this tree's** -- almost
certainly a shorter line buffer.

The reason it cannot be a view: **a frame size is computed by the compiler from
`sizeof`**, so no cast, no local replica and no reinterpretation reaches it. That
is a different category from "a view would be ugly here" -- it is unreachable in
principle, like the this-adjustment residue and the ILT-routed call.

It is still TU-scoped, so it is a small contained shim rather than a shared
header change.

## Sweeping a suspected blind spot and finding it nearly empty IS the result

The `nd > 40` band was taken by hand precisely because the automated scan could
not see it -- the scan only ever surfaced rows whose difference was small enough
to be constants. The band contained one shim item and four header items, and no
views at all.

That closes the question rather than leaving it as a standing "we never looked
there". A negative sweep of a region you had reason to suspect is worth its cost;
what is not worth it is carrying the suspicion indefinitely.

## Every base class in a virtual family is a size outlier BY CONSTRUCTION

The dominant false positive in size-against-siblings, and it is structural
rather than incidental. `?Flush@Pipe@@` is 17 bytes **precisely because**
`?Flush@Base64Pipe@@` is 299 and does the work. The family median is computed
over the derived implementations, so a thin base-class body is not an anomaly --
it is what a base class in a virtual family looks like.

Five of six clearances in the call-site sweep were exactly that shape.

The clearing test, now in the tool: build the caller index once, then clear any
candidate whose callers include **the same method name in a different class**
(delegation) **or any method of its own class**.

That second clause has a mangling trap in it: **a constructor or destructor
names its class without a leading `@`** -- `??1DistLODClass@@`, not
`@DistLODClass@@` -- so a naive same-class check misses its own destructor. A
first pass did exactly that and reported `?Free@DistLODClass@@` as suspicious
when its only caller was `??1DistLODClass@@`.

## Silence is UNDECIDED, never confirmed

Of 14 candidates: 6 cleared, **7 with no matched caller at all**, 1 other, and
**0 confirmed defects**. The seven are undecided, not guilty. No caller is not
evidence of a defect -- it is the absence of the evidence that would decide, and
this tree has plenty of matched bodies nothing else matched calls.

There is a test pinning that specifically, because a verdict tally is exactly
where "no evidence" quietly becomes "evidence of".

## A detector that returns nothing across a full sweep has reported a result

`size_outlier` found zero defects in its own 14 candidates. That is not a
failure to report: it means the sweep is clean, and it says something honest
about the instrument -- **size-against-siblings is much weaker than the other
three**, because a small base-class body is normal where a 5-byte jmp thunk or a
one-name-three-addresses collision is not.

It earned its place on exactly one find, the virtual-dispatch thunk at
0x00495580, where the class has no siblings implementing that method so no
delegation explanation exists. One real find and a clean sweep is a fair account
of a weak-but-real instrument, and it is worth writing down rather than quietly
retiring the tool or quietly trusting it.

## THE MASKING RULE, generalised: ask what a fully-masked input compares equal to

Three places in this tree mask bytes before comparing, and the same failure hides
in each. Stated once, because it has now been discovered three times separately:

**Wherever you mask before comparing, an input with nothing left unmasked
compares equal to EVERYTHING of its length. That is an absence of evidence, and
counting it as a match is how the comparison certifies whatever you hand it.**

(This is the QUANTITY failure -- filter 1 above. It is distinct from the
LOCATION failure, where the bytes that survive masking are identical and the
discriminator sits in the masked region. Different diagnoses, different fixes.)

    the FOLD comparison    -- "a 100% masked screen is necessary, not sufficient".
                              openDataChunk scores 100% and still fails, because
                              masking hides the callee.
    holds_funclet          -- a DATA table of four label pointers, relocations
                              covering all eight bytes, tied with a real funclet.
                              Now requires one surviving byte.
    multi_name's STRUCTURAL test -- ** worth re-examining. ** It classifies
                              0x0000B9CE as a real fold because four 5-byte jmp
                              thunks are "structurally identical". They are --
                              but a 5-byte jmp has ONE unmasked byte, the E9
                              opcode. Every 5-byte jmp in the tree is
                              structurally identical to every other by that
                              measure.

The third is not necessarily wrong -- the ILT topology test covers that case, and
the two instruments were designed to be complementary -- but the verdict
"identical masked bytes and reloc sites, therefore a real fold" is carrying much
less evidence for a 5-byte thunk than for a 154-byte constructor, and the output
does not distinguish them.

**The cheap guard, wherever this pattern appears: report the number of surviving
unmasked bytes alongside the verdict.** A match on 1 byte and a match on 600 are
not the same claim, and today they printed the same way in three different tools.

## THE AMBIGUOUS-HEAL PROCEDURE (there was no "three-filter recipe"; here is the real one)

A phrase -- "re-anchor with the three-filter recipe" -- circulated between two
lanes and a lead as though it named a documented procedure. It did not exist
anywhere. What follows was derived from the data instead, and both filters are
demonstrated on real cases.

On an ambiguous heal, BEFORE reaching for a re-anchor:

**(1) Drop any candidate with no unmasked byte.** `holds_funclet` masks every
relocation site on both sides, so a body that is entirely relocations compares
equal to any target of its length. AIPlayer.cpp's `$L86009` is a data table of
four label pointers covering all eight bytes; it tied with `$L85915`, which is
retail's own `lea ecx,[ebp-0x14]; jmp <dtor>`. Requiring one surviving byte
separates them without choosing between them. **Implemented and tested.**

**(2) When the survivors differ only INSIDE the masked region, resolve the
relocation.** `uw_00c46f00` in LANGameInfo.cpp has three candidates that really
are byte-identical in everything `holds_funclet` compares -- `$L49714`,
`$L49524`, `$L49691`, each four unmasked bytes of `lea ecx,[ebp-0x14]; jmp`.
Their relocation TARGETS differ:

    $L49714 -> ??1UnicodeString@@QAE@XZ
    $L49524 -> ??1?$pair@$$CBVUnicodeString@@V1@@_STL@@QAE@XZ
    $L49691 -> ??1UnicodeString@@QAE@XZ

and retail settles it: decoding the jump in the target bytes gives 0x00047EFB,
the ILT `?j_00047efb@@YAXXZ`, which forwards to 0x0068E6D0 -- the **pair**
destructor. Only `$L49524` relocates where retail jumps. `load_symbol_map`
already builds the body-plus-thunks list this needs. **Demonstrated by hand, not
yet implemented.**

**(3) Only if more than one survives both filters is it a genuine tie** -- and
then it is a boundary finding, not a task.

**The two filters are DIFFERENT failure modes and must not be collapsed.**

  * **Filter 1 is about the QUANTITY of evidence.** `$L86009` did not hide a
    discriminator -- it had no unmasked region at all, so nothing about it was
    ever compared in either direction. This is the repo's own "a 100% masked
    screen is necessary, not sufficient", applied to a tie-break instead of a
    fold. Someone handed the filter-2 rule and AIPlayer's tie would go hunting
    for a discriminator inside a data table's relocations, and there is nothing
    there to find.
  * **Filter 2 is about the LOCATION of evidence.** The LANGameInfo candidates
    had IDENTICAL unmasked bytes; the only thing separating them was the
    relocation target, which is exactly what the comparison masks. Once two
    bodies have compared equal, the discriminator can only be in what was
    masked.

**And filter 2 does NOT mean "unmask it".** A pre-link addend genuinely is not
an address, so comparing those bytes raw compares nothing meaningful. Filter 2 is
a DIFFERENT OPERATION: resolve the relocation's SYMBOL to its ledger address,
thunks included, and compare that against the destination decoded from retail's
own bytes. A symbolic comparison where the byte comparison has nothing to say --
not the same comparison with masking switched off. That distinction is the whole
implementation.

## A second "permanently blocked" verdict overturned by measurement

`isUser@LANGameSlot` -- 132 bytes with "zero differences outside two REL32s" --
is logged as blocked, with the only escapes recorded as a new anchor or a
separate thunk TU. Its sole blocker was the `uw_00c46f00` tie above, and that tie
is resolvable. The verdict was a correct measurement of what was then visible and
is now simply out of date.

That is the second today, after the "cannot come home" AudioEventRTS verdict that
a padded local closed. **A logged verdict is a measurement, not a door.** Both
were overturned by looking at evidence the original measurement had no reason to
consult -- and in both cases the person who overturned it went and re-derived
rather than trusting the note.

## For a family of forwarders, THE CALLEE NAMES THE CALLER

No heuristic, no stub topology, no name comparison: decode the rel32, follow the
ILT, read the name. W3DTerrainVisual's water accessors are thin forwarders into
WaterRenderObjClass, so each is named by what it calls:

    0x00730A20 -> setGridChangeAttenuationFactors  = setWaterAttenuationFactors
    0x00730A50 -> setGridTransform                 = setWaterTransform
    0x00730AC0 -> setGridResolution                = setWaterGridResolution
    0x00730AF0 -> getGridResolution                = getWaterGridResolution

The ledger had `setWaterTransform` and `getWaterGridResolution` each one body
early. Both retired, tombstoned and re-anchored; W3DTerrainVisual.cpp 27/27.

This is the same evidence class that refuted five wrong re-homings earlier the
same day -- a call site naming the symbol -- used constructively rather than
defensively.

## A one-slot rotation MUST leave a hole: the spare placeholder is the proof

The strongest form an identity argument has taken here. A rotation cannot
consume its own displaced body, so it necessarily leaves one body spare -- and
in both confirmed cases the spare was sitting in the ledger under a generated
`?dup_` name.

    VertexMaterialClass   the colour-source rotation left Get_Diffuse_Color_Source
                          unclaimed, with a marker and no row
    W3DTerrainVisual      two one-slot rotations left ?dup_00730a50@@ and
                          ?dup_00730af0@@ holding the two real bodies

That converts "these two rows look wrong" into a positive prediction the evidence
either satisfies or refutes. **If you suspect a rotation and there is no spare
body, that absence is evidence AGAINST it** -- which is what makes this stronger
than any of the four detectors.

## Two pending pieces that both touch the ledger cannot be stashed independently

Sharper form of "hold source as a patch, ledger as tool calls". If two held
changes both write `functions.csv`, the second to land cannot be restored -- its
rows would point at bodies whose source changes are still parked. It has to be
REDONE with the tools against the ledger that exists.

So when work is queued behind a blocker, expect the ledger half of every held
piece but the first to be re-run once per landing ahead of it. Keeping that half
as a short list of tool invocations rather than a patch is what makes re-running
it cheap; one held piece had its four tool calls re-run three times.

## Making a broken thing HEAL is not the same as making it right

`uw_0045bea0` was the single parent-less `gen-funclet` row in a hand-edited TU in
the whole tree. It was annotated with a `parent=` so the healer could find it --
a reasonable-looking tooling fix, and the row then healed onto `$L70461`: twenty
bytes, all twenty relocated, matching on nothing. It stayed green for another
half day.

The row was already bogus before the annotation -- twelve `int3` through the
middle of a claimed funclet, two ILT slots, two `?b_` pins -- so the annotation
did not create the false green. **It extended its life by one heal.**

The failure is treating an unhealable row as a TOOLING gap without asking whether
the row deserved to heal. A row that cannot find its body is telling you
something; the first question is whether it should have one, not how to help it
find one.

## A fix that resolves cases DESTROYS the test cases for its own diagnostics

Sequencing insight, and it decided an ordering:

The refusal diagnostic (print each candidate with its surviving unmasked byte
count) and filter 2 (resolve ties by relocation symbol) were queued in that
order by default. But **filter 2 resolves ties, so after it lands there are
strictly fewer refusals left to exercise the diagnostic against.** Right now two
live refusals exist -- a no-candidate case and a genuine three-way tie -- and
building the reporting first means checking its output against real refusals
rather than synthetic ones.

So: **when one change removes instances of the condition another change reports
on, build the reporting first.** The general form is that diagnostics are
cheapest to validate while the thing they diagnose still happens.

## A refusal that prints nicely and PASSES is worse than a crash

The guard to write into any change that turns a crash into a report. A bare
`ValueError` killing the gate is unreadable but honest -- it stops. A refusal
that reports beautifully and lets the row through is the fallback path this
project forbids, wearing the costume of an improvement.

So when replacing a crash with a diagnostic, check the exit path explicitly:
does the gate still go red? That is the question, not whether the message reads
well.

## A HIGH surviving-byte count is not a pass either

The surviving-unmasked-byte column was added on the suspicion that some verdicts
rested on almost nothing. That suspicion was half right, and the half that was
wrong is the more useful half.

**Right:** 44 of 958 folds rest on three bytes or fewer, and printed identically
to the 694 that rest on sixteen or more. The column earns its place.

**Wrong:** no group rests on ZERO bytes, so the logic needed no change -- the ILT
topology test does cover the thunks, exactly as the complementarity argument
said.

**And the sharpest case is the inversion: both GameWindow draw-data families rest
on ALL 37 of their bytes and are still wrong.** Full byte evidence, nothing
masked, and the error is visible only in the NAMES.

So the column is a caveat and never a verdict. A low count says "this verdict is
thin"; a high count says nothing at all about identity. **Byte evidence, however
complete, cannot see a naming error** -- which is the day's central lesson in its
shortest form, and it took a tool printing 37/37 next to a wrong answer to state
it that plainly.

## Fourteen predicted addresses, fourteen hits, on full evidence

The GameWindow layout correction was verified the honest way: the shim added to
the cl line, the three definitions changed to return `Int`, the TU compiled, and
each emitted body compared against the RETAIL bytes at its PREDICTED address --
never against our own current output, which is where the false green lives.

    winSetEnabledImage    0x00478FE0  37B  rests on 37/37
    winSetDisabledBorderColor 0x004790E0 40B rests on 40/40
    winSetPrev            0x00478DD0  13B  rests on 13/13
    ... fourteen in all, every one MATCH

The 37/40 size split came out right although nothing in the derivation forced it
-- the kind of prediction that is hard to satisfy by accident.

**And the predicted trap sprang exactly as forecast.** `winSetPrev` does not
belong at 0x00478EB0; written in member names against the corrected header it
walked off the tooltip body onto 0x00478DD0 by itself. One lane predicted that
behaviour from its own matched rows; the other observed it. Two witnesses, and
the second was an experiment the first could not run.

Consequence for the commit: the three `?dup_004790XX` rows are NOT renames.
GameWindow.cpp now emits those bodies byte-exact, so the 101-line replica file
folds home -- same nine addresses, one fewer file.

## A name held HOSTAGE on the wrong address forces someone to invent a name

Third instance of one shape today, and it is now predictive rather than
anecdotal.

`winSetStatus`'s row sat on a body that ORs into +0x04 -- the anchor pointer.
`m_status` is +0x08, and TWO matched rows in the same accessor run already said
so (`winClearStatus`@0x00478440 and `winGetStatus`@0x00478480, both noted
"BFME m_status@0x08"). The correctly-written body compiles to a 19-byte sequence
occurring **exactly once** in retail, at 0x00478420 -- immediately before those
two.

And that address was already claimed, by `?_bfme_winSetStatus@GameWindow@@QAEII@Z`.
**Someone had converted the right body and had to invent a name for it, because
the real name was hostage on the wrong address.** `GameWindowStatusThunk.cpp`
existed only to house that invention.

The three instances:

    VertexMaterialClass   Get_Diffuse_Color_Source unclaimed while its two
                          neighbours sat one field high
    W3DTerrainVisual      two ?dup_ placeholders holding the real bodies of two
                          rotated accessors
    GameWindow            ?_bfme_winSetStatus invented for a body whose true
                          name was pinned elsewhere

**So an invented `?_bfme_`, `?dup_` or thunk-file name adjacent to a real one is
a SYMPTOM.** Someone met a correct body that could not take its correct name and
worked around it. Read those as evidence of a displaced row nearby, not as
scaffolding.

## A fabricated MECHANISM in a comment is worse than a wrong offset

`GameWindowFields.cpp` had `winSetDisabledImage` writing `m_hiliteDrawData`,
under a comment asserting: *"BFME never wrote a distinct disabled-image path
here; write the same field so our object code folds the same way."*

That is an invented mechanism, constructed to justify a body that made a wrong
row verify. Retail has nine separate setters at 0x478FE0 + 0x30, and 0x479070 is
exactly the disabled-image one.

A wrong offset is a mistake and the next reader can measure it. **A wrong
offset with a mechanism attached is an argument, and the next reader has to
refute it** -- the reasoning reads as evidence while being the opposite of it.
It also survives review better than a bare wrong number, which is what makes it
more expensive.

When correcting one, name the old claim in the comment so nobody re-derives it.
And when writing one: a comment may state what was MEASURED and what remains
UNKNOWN. It may not supply a reason the measurement did not establish.

## Byte-exactness proves OUR SOURCE COMPILES TO THOSE BYTES -- never that the name is right

The day's central lesson in its final and sharpest form, and it cost a fully
built, fourteen-address, full-unmasked-evidence GameWindow mapping that was
wrong.

Fourteen bodies each matched retail exactly at a predicted address, on 37/37 and
40/40 and 13/13 surviving bytes. The mapping was still wrong, and retail's own
callers say so -- decoded through the ILT with no names involved:

    GadgetSliderSetEnabledThumbBorderColor  -> ILT 0x000262B0 -> 0x00479010
    GadgetSliderSetDisabledThumbBorderColor -> ILT 0x0001EAEC -> 0x004790A0
    GadgetProgressBarSetHiliteBarBorderColor-> ILT 0x000248B1 -> 0x00479150
    GadgetSliderSetEnabledThumbImage        -> ILT 0x00035E09 -> 0x00478FE0
    GadgetSliderSetHiliteThumbImage         -> ILT 0x0000B406 -> 0x00479120

Five of the nine addresses, naming **the binding that was already in the
ledger**. The mapping was derived entirely from body bytes; no call site was ever
opened.

**The self-check, and it is one grep: before moving a row, ask who calls the
address it is LEAVING.** A caller that names the old binding is the evidence that
outranks any amount of byte agreement -- the same rule that refuted five
re-homings earlier the same day, unused by the same lane a few hours later while
it was writing the commit message about the vertmaterial pad.

**Only the full gate could see it.** All twelve reds were CALLERS in a third file
-- `GameWindowManager.cpp` -- green before the change and invisible to a scoped
run over the two files being edited.

## multi_name's own docstring, falsified by its own tool

The docstring claimed two accessors one family member apart "cannot be one body
whatever our compile says". **AABTree disproves it.**
`Cast_AABox_Recursive`, `Cast_OBBox_Recursive` and `Intersect_OBBox_Recursive`
share 0x0096B100 legitimately: every method they call on their differing type had
already folded, so the callers became genuinely identical.

The rule that separates the two live cases:

  * **FAMILY is REAL when the difference would have to appear in the COMPARED
    bytes.** GameWindow -- a field offset is a literal, and the claimants rest on
    all 37 of their bytes.
  * **FAMILY is UNDECIDABLE when the difference lives inside the MASKED
    relocations.** AABTree -- 211/219 surviving, and the difference is in the two
    calls.

Each FAMILY line now reports which case it is, and **it does not auto-clear**:
clearing a candidate automatically is how a real defect gets filed as noise --
the forbidden fallback in this tool's shape.

## Stop at "not self-consistent" rather than guessing twice

The caller evidence does not yet close: 0x00479120 is reached both as
`GadgetSliderSetHiliteThumbImage`'s image call and as
`GadgetProgressBarSetHiliteBarColor`'s colour call. Either one of those Gadget
rows is itself misnamed, or the parameter convention differs.

That is the correct place to stop -- no replacement mapping proposed, and the
rejected diff banked outside the repo because its four forced discoveries are a
map of where the pressure is even though the binding is wrong. **A wrong answer
kept for its by-products, with the answer itself withdrawn.**

## THE ASYMMETRY FAILURE: a relocation WE have and retail does not

Third distinct way masking hides a difference, and the largest so far: **67
matched rows across 20 bodies.**

Masking blanks every DIR32 site, and it chooses WHICH bytes to blank from the
COMPILED side's relocation list. So a site that is a relocation for us and a
plain literal for retail gets blanked on both sides -- and the one field that
separates the two bodies is the one field nobody compares:

    ours    8b c1  c7 00 <DIR32 ??_7X@@6B@>  c3     mov [eax], vftable
    retail  8b c1  c7 00  00 00 00 00        c3     mov [eax], 0

**A linked absolute address is never zero. All-zero retail bytes under one of our
DIR32 sites prove retail stored NO POINTER there.**

The three masking failures, now distinct:

    QUANTITY   no surviving byte at all (AIPlayer's data table)
    LOCATION   identical surviving bytes, discriminator inside the mask
    ASYMMETRY  we have a relocation site retail does not -- and these rows have
               PLENTY of surviving bytes, all of which agree

15 of the 67 carry an explicit `icf-owner=`, which made the alias look
sanctioned. 23 sit on 0x00087A50 and 21 on 0x00061D90, both storing literal
zero: abstract-base and interface constructors -- MemoryPoolObject, InputStream,
DockUpdateInterface, ObjectDrawInterface, the eight Blit*Xlat instantiations,
PostLoadableClass.

**The real constructors exist and are distinguishable.** Retail holds 215
pointer-storing bodies of the 9-byte shape against 203 zero-storing, and 66 of
the 18-byte shape against 3, each storing a different vftable. So these rows are
on the wrong side of a fork the comparison cannot see, and each is in principle
re-homeable by its own `??_7X@@6B@` address.

**One legitimate zero, excluded BY NAME with a test rather than by a threshold:**
`mov eax, fs:[__except_list]` really does relocate against absolute 0 -- a TIB
offset, not a linked address -- and it opens every try-block in the tree. A
threshold would have buried the result or admitted noise; naming the one real
case does neither.

## A green row over an `__emit` dump is evidence about the DUMP, never its name

`?Recolor_Texture@W3DAssetManager@@QAEHHHHHHHHHH@Z` was a fabricated nine-int
thiscall signature resting on a 658-line `__emit` dump. **Re-emitting retail's
bytes cannot fail to match**, so the green said nothing whatever about whether
the name was right.

Settled by call sites, as it should have been originally: the only two callers of
0x00A5828A in the whole image are `D3DXSaveMeshToXofEx` and
`D3DXPatchSaveMeshToXofEx`, both from `d3dx9.lib`. Retired; the d3dx9 row still
covers the address so no bytes are lost, and both real `Recolor_Texture`
overloads return to `present-unmatched`, which is what they are.

The conversion-direction gate stops new ones. This was an old one verifying
itself.

## COUNT BODIES, NOT ROWS -- where duplicate names are the audit, rows let the defect vote

Second counting defect to change a conclusion today, and the sharper one.

A caller sweep over the GameWindow draw-data run counted ledger ROWS, so a
single body carrying four claimant names contributed four "caller sites". The
apparent six-to-three Colour majority at 0x00479010 was **two bodies**:

    0x0047B650   SetEnabledThumbColor | SetDisabledThumbColor |
                 SetHiliteThumbColor  | SetEnabledThumbBorderColor
    0x0047B700   the same four names, Selected variants

One 28-byte body wearing four names, counted four times, in a sweep whose whole
purpose was to detect bodies wearing several names. **Where duplicate names are
the thing under audit, counting rows lets the defect vote on its own case.**

Recounted by unique body the signal reversed: six unambiguous single-name
BorderColor bodies across two groups, from two independent wrapper families,
and not one Color.

## A displacement is a NUMBER; it names nothing

A proposed shortcut for settling `WinDrawData`'s field order -- "check whether
position 2's displacement is the one our header calls Color" -- is circular, and
it fails in the direction that looks like confirmation.

Position 2 writes base+8, and our header calls +8 `borderColor`. So the test
appears to REFUTE the (correct) hypothesis -- but only by assuming our header's
field order, which is exactly the thing in question. **There is no caller-free
version of this test.**

What retail alone does give is the geometry, which needs no names: bases
0x48 / 0xB4 / 0x120, fields at +0 / +4 / +8, stride 0x6C = 9 x 12. So
MAX_DRAW_DATA is 9 and WinDrawData is three 4-byte fields. Geometry from bytes,
identity from callers -- and never identity from a byte offset interpreted
through the header you are auditing.

## WITHDRAWN: BFME's WinDrawData is ZH's {image, color, borderColor}
**This entry claimed a swapped field order. It is wrong -- the order is
UNCHANGED from ZH. See "an offset is only as absolute as its TU's layout" below;
the apparent swap was a uniform 4-byte base bias read as a field rotation.**

Position 1 is BorderColor on six single-name bodies across two groups and two
independent wrapper families; position 2 has no named callers **because the
Colour wrappers' rows are piled onto the enabled group's position-1 body
instead**. Our header has the last two fields swapped.

So the GameWindow fix is a `WinDrawData` field-order correction in the shim --
not the ledger rebinding that was attempted and reverted. The six
Colour/BorderColor rows and the three `?dup_` position-2 bodies should fall out
once it lands, with the Image third already proven independently.

One residue that does NOT resolve this way and was correctly left alone:
`?GadgetProgressBarSetEnabledBarColor@@` at 0x0047A8C0 is a single-name body
still calling position 0 with idx=4. Under the settled order that looks
misnamed, but it has no companion name to convict it and no inference was made.

## Validate a NULL against a control before trusting it

"Zero callers" and "my query is broken" produce identical output. Before
concluding that 0x00061D90 and 0x00087A50 have no call sites, the same code path
was run against 0x00478FE0 and returned **70 caller bodies**, ILT hops included.
Only then was the null evidence.

This costs one extra query and it is the difference between a finding and a
silent failure -- the same shape as the sweep that once reported "0 refs" for 314
objects it had failed to load, and the regression test that passed with and
without its fix.

**Any time an absence is the result, produce the control that proves the
instrument can see a presence.**

## POOL CAPACITY is evidence, and it can point opposite ways for one defect

The 67-row `null_reloc` family looked like one problem with a leverage point --
44 of the rows on two addresses. The two addresses turned out structurally
opposite:

     9-byte shape   215 pointer-storing bodies   190 free   for 21 rows
    18-byte shape    66 pointer-storing bodies     4 free   for 23 rows

The 9-byte pool has room to spare. **The 18-byte pool has none**: 62 of its 66
bodies are held by a legitimate, coherent template family --
`??0?$SubsystemSlot@V<T>@@@@QAE@PAX@Z`, one instantiation per subsystem, each
with its own vftable -- and those names look right. So its 23 claimants have
nowhere in that pool to go, while the other 21 have 190 candidate homes.

Counting the free bodies in the destination pool tells you whether a re-homing is
even arithmetically possible, before any per-row work.

## Four closed routes are a result; the hypothesis they suggest is still not one

For those 44 rows the negative is solid -- all store a vftable through a DIR32
where retail stores a literal zero, and a linked absolute address is never zero.
The positive half is unavailable, and every route was checked rather than
assumed:

    call sites          zero caller bodies for either (control-validated);
                        expected -- a 9-byte base ctor is inlined into every
                        derived ctor at /O2
    vftable pins        73 ??_7 symbols pinned; none of the 44 classes
    object-symbol=      zero of 146 placeholder-named bodies carries one
    vftable by contents  no matched virtuals exist -- they are abstract interfaces

The hypothesis this suggests -- that retail emits **no standalone constructor at
all** for these classes -- fits every observation and matches the `StringInfo`
disposition already in `deleted_rows.csv`. **It was recorded and not acted on.**
Retiring 44 rows on an inference with no positive evidence would be the reverted
GameWindow mapping at twenty-three times the scale.

Leave them flagged. Either of two events cracks the 9-byte group at once, since
it has 190 free bodies waiting: a vftable pin for one of these classes, or a
single matched virtual method, which locates the vftable by contents and then the
constructor by the address it stores.

**And the framing correction worth keeping: "two questions, not sixty-seven" was
the right instinct, and both answers came back UNAVAILABLE rather than SETTLED.
The leverage was real; the evidence was not there to spend it on.**

## A cache keyed on what was OPENED cannot see a file that changes what WILL be opened

The most dangerous no-op yet, because it wears the appearance of a passed
prediction.

Adding a new header to a shim directory does **not** invalidate the deps cache.
The sidecar records the files the compiler actually opened last time, and a new
higher-priority header is not among them -- so nothing looks stale. The run
reported `Compile: 0 of 3 TU(s)` and a green 209/209, which read exactly like the
prediction being confirmed. Nothing had been compiled at all.

Caught only by asking the sidecar which `WinInstanceData.h` it had read, rather
than trusting the green.

**So whenever a change ADDS a file to an include path rather than editing one
already on it, the deps cache cannot know. Force the rebuild, or verify from the
sidecar that the new file was opened, before believing any result.** This is the
same family as editing `reference/.../vertmaterial.h` when a local copy wins:
both are the build reading something other than what you edited.

## A shim-path grep matched a DIFFERENT shim by prefix

`grep -rl '/Ireference/shims/gamewindow'` also matches
`/Ireference/shims/gamewindowlist`. A substring false positive hid an entire
third shim, and with it the fact that two shims disagree about GameWindow's
layout.

Third matching-or-counting defect of the day, after counting rows instead of
bodies and the double-counted caller table. **When a name is a prefix of another
name, an unanchored grep is a guess.** Anchor the path or read the deps sidecar
-- which is what eventually caught this one, and is the rule this file already
carried for a different reason.

## PREDICT THE CASUALTIES: first use, and it stopped a wrong change

The discipline is: write down which rows will go red BEFORE compiling, name the
ones expected to stay green, then compare.

Predicted three -- `winGet{Enabled,Disabled,Hilite}Color` moving position 0 to
position 2 -- with the three BorderColor getters explicitly called out as
staying green. **Measured ten.** All six getters plus four `GadgetSlider Get*`
wrappers; the headline "stays green" prediction was wrong.

The cause was the hidden third shim: `GameWindowManager.cpp` builds against a
GameWindow.h with no `m_bfmeAnchor`, so its draw-data base sits four low, and
under that base the ZH field order coincidentally puts `color` and `borderColor`
where the correct order puts `image` and `borderColor`. Swapping two fields
slides both by four instead of moving one to position 2.

**Without the written prediction, ten red rows would have read as "the change is
bigger than expected" rather than "the model is wrong."** A count that misses is
a falsification; a count you never wrote down is a surprise you rationalise.

## The rotation-hole proof held, independently of the failed change

Untouched by the revert, and it is the strongest evidence in the round: the three
position-2 getter bodies exist -- 0x0047A280, 0x0047A2C0, 0x0047A300 --
interleaved with the correctly-named BorderColor getters at 0x0047A260,
0x0047A2A0, 0x0047A2E0, and **all three are held by `?dup_` placeholders**.

A rotation must leave a hole. There are three holes, one per group, exactly
where the field order predicts. That is the third confirmed instance of the
rotation-hole structure, and the first where the prediction was made before the
holes were looked for.

## Measure on a PARAMETER to break the circularity

Every GameWindow derivation until now went through `GameWindow`'s own layout --
which was the thing under question -- so each answer depended on the assumption
it was testing. `?parseTooltipDelay@@` breaks it: `add ecx, 0x198` on a
**`WinInstanceData*` PARAMETER**, so the offset is measured INSIDE
`WinInstanceData` with no GameWindow layout anywhere in the path.

Combined with two `this`-relative measurements the system becomes
**over-determined** -- three measurements, two unknowns, no free parameters:

**The first solution of it was WRONG, and the way it was wrong is the lesson.**
It counted `m_id, m_state, m_style, m_status, m_owner` as 0x14 and concluded
`m_instData = 0x2C`, "8 extra bytes in WinInstanceData", and "neither shim's
insertion is real". `WinInstanceData` declares `virtual ~WinInstanceData()`, so
it carries a **vptr at +0** that was not counted. Corrected:

    offsetof(m_enabledDrawData) = 0x18            (vptr + five dwords)
    m_instData                  = 0x48 - 0x18 = 0x30
    m_tooltipDelay              = 0x1C4 - 0x30 = 0x194
    parseTooltipDelay measures                  0x198
    residual                                      4 bytes, AFTER the arrays

**0x30 is exactly what `reference/shims/gamewindow` already asserts**, so that
shim was right all along and only `gamewindowlist` is wrong. The residual 4 bytes
sit after the draw arrays and do not touch the draw-data question.

**Reading five members and stopping is how you get an offset exactly one pointer
wrong** -- and four or eight bytes is precisely the size of error that still
produces plausible, self-consistent arithmetic. Count the vptr. A class with any
virtual function has one, and it is not in the member list you are reading.

This is the same move as the GarrisonContain control view -- the fourth view, on
the `observingPlayer` PARAMETER, needed no adjustment and isolated the effect to
`this`. **A parameter-relative measurement carries no assumption about the class
you are auditing.** Look for one before deriving a layout from `this` alone.

## A shim comment named its own resolution condition, and evidence arrived later

`reference/shims/gamewindowlist` documented the conflict it could not settle: the
`gamewindow` spread "breaks all seven" accessors, and the +0x04 field "can only
coexist with them if something before +0x48 is 4 bytes SMALLER in BFME, which
nothing here proves."

Caller evidence supplied exactly that, from the other side: **three of those
seven pins are on the wrong bodies.** `winGet{Enabled,Disabled,Hilite}Color` sit
at position 0 -- the Image bodies -- so the +0x48 pin they appeared to provide
was never real, and the constraint the author could not discharge was never
binding.

Worth the pattern: **a comment that states its unproven condition precisely is
worth writing even when you cannot discharge it.** It let a later measurement
close a question its author had correctly refused to guess at. Contrast the
fabricated `winSetDisabledImage` mechanism, which asserted a reason and cost a
reader the work of refuting it.

## Predict the OFFSET, not just which rows go red

The prediction discipline sharpened by one turn. First use predicted a set of
rows and got ten where three were named -- a falsification, correctly reverted.
Second use predicted **each row's resulting offset**:

    winGetEnabledColor        -> +0x4C   measured +0x4C
    winGetDisabledBorderColor -> +0xBC   measured +0xBC
    winGetHiliteColor         -> +0x124  measured +0x124
    setTooltipDelay           -> 0x1C8 against retail 0x1C4, red with no home
    ... 11 predicted, 11 measured, zero unpredicted

**A set of row names can be satisfied by a wrong model that happens to break the
same rows. A set of offsets cannot.** Predicting where each row LANDS turns the
check from "did I anticipate the damage" into "is my model of the layout right",
and it costs nothing extra to write down.

Note the fix that came out of it was not the one authorised: not an invented
`m_bfmeAnchor`, but **restoring `m_userData` to its ZH position in front of
`m_instData`**, which `gamewindowlist` had moved to the tail. Restoring a
vendored position beats adding a BFME-only member whenever the arithmetic allows
both -- one asserts less.

## Two independent routes meeting on the same three bodies

The Colour field order was derived from **callers** (six single-name BorderColor
bodies across two groups, counted by body). The probe then derived it from
**layout**: with the field order corrected, Color lands at elem+8 -> +0x50 /
+0xBC / +0x128, which are 0x0047A280 / 0x0047A2C0 / 0x0047A300 -- the three
`?dup_` placeholder bodies.

Neither route used the other's evidence, and the rotation-hole argument predicted
the holes before either had been checked. **Three independent derivations meeting
on the same three addresses** is the strongest standard reached on this class,
and it is the standard the two reverted attempts did not have.

## Investigation sequencing is not COMMIT sequencing

A standing instruction -- "one change, one prediction, its own commit" -- does
not survive when the first change has no green state of its own.

Probe 1 (restore `m_userData`, shrink the pad) leaves 11 rows red; that is what
the probe MEASURED. Those casualties are repaired only by the field order plus
the ledger moves. So splitting it into two commits means landing the first one
red, which is worse than any benefit the split offers.

**The split was right as INVESTIGATION and it worked** -- probing the anchor
alone is what proved the model and localised the residue. It simply is not
separable as commits. When a staged investigation converges, ask whether each
stage has a green state before insisting on one commit per stage; if it does
not, the whole convergence is one commit with one prediction covering all of it.

## The residual dissolved by asking the call-site question first

`setTooltipDelay` compiled to 0x1C8 where retail wrote 0x1C4 -- a 4-byte residue
that would otherwise have gone in as unnamed padding. Asking who calls it
instead:

    0x0098D2B0  writes +0x1C4, claimed by TWO names --
                ?Set_Frame_Mode@ParticleEmitterDefClass@@UAEXH@Z
                ?setTooltipDelay@GameWindow@@QAEXH@Z   <- ZERO callers
    0x0047A330  writes +0x1C8, held by ?set@Rva0047A330DwordSlot@@, whose own
                note reads "disp32 accessor at this+0x1C8; address-derived
                placeholder"

`setTooltipDelay` was on an ICF body shared with an unrelated class's virtual
setter, with no callers -- while a body writing exactly the predicted offset sat
under a placeholder **in the middle of the GameWindow accessor run**. No padding
was needed; the row was simply in the wrong place.

**Five placeholders in one accessor run is itself a signal.** 0x0047A280,
0x0047A2C0, 0x0047A300 and 0x0047A330 all sit interleaved with correctly-named
getters. A dense band of address-derived names inside an otherwise-named run
marks displaced rows, not scaffolding.

And the arithmetic now closes with **zero free parameters** on four independent
measurements:

    m_instData 0x30 + offsetof(m_enabledDrawData) 0x18  = 0x48   caller-confirmed
    m_instData 0x30 + offsetof(m_tooltipDelay)   0x198  = 0x1C8  body at 0x0047A330

The parameter-relative 0x198 is the only number in the system that never passes
through `GameWindow`, and it is the only one that survived both failed
derivations unchanged.

## Check both the READERS and the WRITERS before naming a field

The field order was derived from setter call sites -- 81 of them, six wrapper
families, counted by body -- and the getters were never asked. They disagree.

    setters (call graph)     group+0 is IMAGE
    inline getters (names)   group+0 is COLOR, and the third field is image

Both families are internally consistent. `GadgetButtonGetDisabledColor` and
`GadgetCheckBoxGetDisabledColor` both read +0xB4; the BorderColor pair both read
+0xB8; the SelectedImage pair both read +0xBC -- and the same pattern repeats
exactly at +0x120 / +0x124 / +0x128 in the hilite group. That is structural
agreement across two groups, not one row's opinion.

**One grep would have caught it.** A field has readers and writers, and deriving
its identity from only one side is the same single-derivation failure that
produced two reverted mappings earlier the same day, in a narrower form.

## When two witnesses contradict, rank them by HOW THEY COULD BE WRONG

Not by count, and not by which was found first.

    setter evidence   retail's own CALL GRAPH. No ledger binding can distort it;
                      a wrong row name cannot move where retail jumps.
    getter evidence   ledger row NAMES -- the exact class of thing this lane
                      exists because it is unreliable. Several of those
                      addresses carry two names, with `?dup_` siblings at each
                      offset.

So the setters are the stronger witness *by kind*. But that is a lean, not a
settlement, and a lean is not what should move nine rows. The getter family is
not weak either -- `...GetHiliteSelectedImage` reading the same field offset in
two different groups is a structural claim.

**The resolution of two internally-consistent contradictory witnesses is not a
third derivation. It is finding the question whose answer both must satisfy.**
Here: the "Selected" variants should differ from their plain siblings by INDEX
-- twelve bytes, one `WinDrawData` -- and not by four. If they differ by four,
that is an index-versus-field confusion large enough to explain the whole
contradiction, and it is read-only to check.

## A getter and a setter for one property cannot disagree about which SLOT it lives in

The invariant that resolved the WinDrawData contradiction, and it settles a
two-witness deadlock without counting either side.

The inline getter names, taken at face value, do not fit EITHER candidate order.
They fit a third:

                              +0xB4     +0xB8         +0xBC
    getter names say          Color     BorderColor   SelectedImage
    {image, color, border}    image X   color X       borderColor X
    {image, border, color}    image X   borderColor X color X
    {color, border, image}    color OK  borderColor OK image OK

**A witness that fits neither candidate is not evidence between them** -- it is a
claim about a third possibility, and that possibility has its own consequences to
test. Here: `{color, borderColor, image}` requires "Selected" to mean a different
FIELD of one element.

It does not. Retail's call graph shows every `Selected` wrapper calling the SAME
setter as its plain sibling with a different INDEX:

    GadgetButtonSetEnabledImage          -> 0x00478FE0   idx 0, 5, 6
    GadgetButtonSetEnabledSelectedImage  -> 0x00478FE0   idx 1, 2, 3

Same body, same field, different slot in the nine-element array. So under the
getter-name reading, `GetDisabledSelectedImage` would read index 0's THIRD FIELD
while `SetDisabledSelectedImage` writes index 1's FIRST FIELD -- a getter and a
setter for one property disagreeing about which slot it occupies. That cannot be.

The invariant is sound and it does rule out `{color, borderColor, image}`. But
the conclusion drawn from it -- that `{image, borderColor, color}` therefore
stands -- **was wrong**: the third candidate was an artefact of a 4-byte base
bias, and removing it restores ZH's `{image, color, borderColor}` rather than the
swap. The getters' zero-caller status is still true and still makes them weak as
NAMES; what was misread was their OFFSETS. See the entry below.

## Refuse a stale go-ahead

An approval to run probe 2 crossed the stop report that made probe 2 wrong.
Acting on it would have been "absorbing a known problem" with a lead's
authorisation attached.

**An instruction issued before your latest evidence is not an instruction about
it.** When a go-ahead crosses a finding that changes the question, the finding
wins and the approval needs re-asking. This is the second time today a lane has
been right to decline an instruction of mine -- the other being the
one-commit-per-change rule that would have required landing red.

## An offset read out of a TU is only as ABSOLUTE as that TU's layout

The whole GameWindow field-order detour, in one rule.

`Selected` is exactly `+0x0C` from its plain sibling -- one whole `WinDrawData`
-- across six independent pairs in two groups, eighteen names fitting one model
with no exceptions:

    +0x0B0 GetDisabledImage        +0x0BC GetDisabledSelectedImage
    +0x0B4 GetDisabledColor        +0x0C0 GetDisabledSelectedColor
    +0x0B8 GetDisabledBorderColor  +0x0C4 GetDisabledSelectedBorderColor

So the order is **image +0, color +4, borderColor +8 -- ZH's, unchanged.**

The apparent conflict with the setter callers was never about field order. It is
a uniform **4-byte base offset**:

    enabled   getters say 0x44   setters say 0x48
    disabled  getters say 0xB0   setters say 0xB4
    hilite    getters say 0x11C  setters say 0x120

The inline getters live in a TU whose `GameWindow` is four bytes short -- the
same unshimmed defect already proved for `GameWindow.cpp` and `gamewindowlist`.
**A global -4 makes `{image, color, borderColor}` read as
`{color, borderColor, image}` shifted into the neighbouring slots**, which is
exactly the phantom third order that looked like a decisive third witness.

**Compare DIFFERENCES before comparing OFFSETS.** The getters' spacing was
trustworthy from the first look; their absolute values carried a bias already
measured in two other files. Two errors, and the second was hidden by the first:
absolute offsets read out of a biased TU, and a field-order swap inferred from
setter-caller names when no swap existed.

The `Selected` labels are ledger names and carry no weight. **The load-bearing
evidence is the 0x0C spacing** -- six pairs at one constant is a structural fact;
the words attached to them are not.

## What GameWindow actually established, after three withdrawn derivations

Parked. Solid:

  * geometry -- bases 0x48 / 0xB4 / 0x120, stride 0x6C, nine elements of twelve
  * `m_instData` at 0x30 and `setTooltipDelay` at 0x1C8, closing with no free
    parameter on a parameter-relative measurement
  * `setTooltipDelay` mis-anchored on an ICF body with zero callers; real home
    0x0047A330
  * `gamewindowlist` is four bytes short because `m_userData` was moved to the
    tail -- and the inline getters are a SECOND, independent witness to that
    same shift
  * five placeholders interleaved through one named accessor run

Not established: which of `color`/`borderColor` sits at element+4 under the
setter-wrapper names. Six single-name setter bodies say BorderColor at position
1; eighteen internally cross-checked getter names say Color. **That residue is
left open deliberately** -- it is a fourth derivation on a class that has already
produced three withdrawals, and nothing depends on it.

## When BOTH witnesses are names, the question may be undecidable -- say so

The `color`-versus-`borderColor` question at `WinDrawData` element+4 resisted
three derivations, and the reason is structural rather than a failure of effort:

  * the call GRAPH is retail's -- which body a wrapper calls is a fact;
  * but "bodies named `*BorderColor*` call element+4" leans on the WRAPPER's
    name, which is a ledger binding;
  * and the inline getters lean on the GETTER's name, also a ledger binding.

Two name-based witnesses pointing opposite ways, with **no structural
tiebreak** -- because swapping two same-width fields changes no structure. The
+0x0C Selected spacing, the 0x6C stride, the nine elements and the array bases
all agree with BOTH readings.

**The question is invisible to every byte measurement available.** Naming that
is a result. Three internally-consistent answers that each rested on unaudited
names is what an undecidable question looks like from the inside, and the
correct output is a park with the unblock conditions written down -- not a
fourth attempt.

## Retail's own STRINGS are non-circular naming evidence

The one route out that is not circular: **a parse table.** The `.wnd` script
parser reads these fields by keyword, so `parseDrawData`-style code maps a
literal string -- `"ENABLEDBORDERCOLOR"` -- to an offset. That is a name
supplied by RETAIL rather than by our ledger, which is exactly what every other
witness lacked.

**The machinery already exists.** `tools/fieldnames.py` extracts precisely this
and has produced `reverse/field_names.csv`: 4,416 rows of
`table_rva, ini_key, bfme_offset`, e.g.

    0x00cfc430,CommandBarBorderColor,0x30,ControlBarScheme,m_commandBarBorderColor,65,64

So the unblock is not a research project -- it is pointing an existing extractor
at a specific table, if that table exists. The current file has no `.wnd`
draw-data entries, so the table has not been located; that is a search, and a
search has a clean negative.

**General form: when a naming question deadlocks between two ledger-derived
witnesses, look for a place where retail names the thing itself** -- a parse
table, a keyword string, a debug format. Those are the only names in the binary
that are not ours.

## A THROWAWAY script gets the same audit as a committed tool

The sharpest self-catch of the day. A small follow-up script, written four hours
after the tool that detects exactly this, did:

    len({addrs_a, addrs_b}) == 1

Two **empty** tuples compare equal, so an unpinned symbol on both sides printed
`same-address=True` and was declared a real fold. **Absence of evidence counted
as agreement** -- the masking failure the entire day has been about, reproduced
in a fresh script because the script was small and felt obviously right.

It is the throwaway ones nobody reviews. **Ask a scratch script the same
question you ask a committed one: what does an empty result compare equal to?**

## `symbols.csv` is ADDITIVE, so intersect the candidate sets -- never compare them

Second defect in the same script, and it inverted two verdicts. The resolver
keeps the first pinned address that reproduces retail, so a symbol legitimately
carries several candidates. Comparing SETS for equality calls two claimants
different when they merely have different candidate lists; what matters is
whether the **intersection is non-empty**.

    0x006F7C80  Cull_Box / Cull_Sphere       {0x008DB060, 0x008DB380} vs {0x008DB060}
    0x00979D20  Set_Position / Set_Transform  all three sets contain 0x00982110

Both had been called "cannot be one body". Neither is refuted at all. A corrected
test intersects the sets AND treats an unpinned symbol as *no information*
rather than as agreement.

## The careful tool was right; the quick script was not

`multi_name` reported all five FAMILY candidates as *"the claimants name
different relocation targets, so what separates them was masked"* -- it declined
to guess, and it was right about every one. The follow-up script written to
"settle" them produced two wrong refutations and two false folds.

Honest tally: **1 resolved, 4 undecided**, not the 1-plus-4-defects the first
read suggested. 0x00924840 is real ICF -- all three claimants' single relocation
resolves to exactly 0x0096B100, consistent with the other two AABTree families.

Worth remembering when a tool's cautious verdict feels unsatisfying: the
caution was the tool being correct about the limits of its evidence, and the
instinct to go past it needs an instrument at least as careful as the one that
stopped.

## CLOSED: retail contains no `BORDERCOLOR` string, so the parse-table route does not exist

The `.wnd` route was the one non-circular way to name `WinDrawData` element+4.
It is closed on the strongest evidence available -- **the name is not in the
binary**:

    ENABLEDDRAWDATA    5 hits
    DISABLEDDRAWDATA   5 hits
    HILITEDRAWDATA     5 hits
    ENABLEDCOLOR       1 hit   (a TEXT colour, alongside SELECTED/HILITE/DISABLED)
    BORDERCOLOR        0 hits
    IMAGE:             0 hits
    COLOR:             0 hits

The `...DRAWDATA` keywords exist; their sub-fields do not. The parser reads the
three fields **positionally** inside the value, so retail never spells `color`
or `borderColor` as a string, and there is no `{token, proc, offset}` table for
`fieldnames.py` to read.

**Record it as CLOSED rather than open.** "We could not find the table" invites
another search; "there is nothing to find" does not. A negative established this
firmly is a permanent saving.

So element+4 has **no retail-side name evidence of any kind**. Three sources
could in principle have named it -- the setter wrappers, the inline getters, and
the parser -- and the first two are ledger bindings pointing opposite ways while
the third does not name it at all. With the structural point that swapping two
same-width fields changes no structure, the question is **undecidable from the
tree as it stands**, not merely unsolved.

What could still unblock it, from elsewhere: a caller passing a **literal colour
value** to a position-1 setter, or independent identity for any one of the
`Gadget*Get*Color` / `Set*BorderColor` wrappers from its own callers.

## A discipline survives only if it is cheap enough to use every time

The prediction files, the deps-sidecar check and the stop rule caught five wrong
bindings in one day and let none of them reach the tree. The reason they worked
is not that they were rigorous -- it is that **each one costs almost nothing**.

Banking a prediction to a file before compiling is seconds. Asking the sidecar
which header was opened is one command. Stopping when an unpredicted row goes
red requires no analysis at all. The expensive version of that discipline --
review boards, second opinions, formal write-ups before each attempt -- would
have been skipped by the third attempt and absent for the two that mattered
most.

**Design the check so that using it is cheaper than justifying skipping it.**
