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

23 donors carry a marker for a ??0X@@QAE@PAVThing@@PBVModuleData@@@Z, every one
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

Three of the misses are one finding: retail stores a FOURTH vtable at this+0x18
that the vendored UpgradeModule hierarchy has nowhere to put -- BehaviorModule
+0x00, UpgradeMux +0x0C and UpgradeModuleInterface +0x10 are all correct, BFME
simply has one more interface base after them. Header change, not a fold.

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

## $L-anchored rows are broken by ANY added declaration, not just a header change

The 403-row re-anchoring cost is usually quoted against the tree-wide string
header, which makes it read as a cost of BIG changes. It is not. The labels are
assigned across the whole TU during codegen, so ANY edit that adds a
DECLARATION renumbers them -- a forty-slot view class is enough.

GameSpyInfo::updateStagingRoom is one instruction from home (addStagingRoom is
vtable +0xA0 in BFME against the vendored +0x84, and the by-value copy and its
unwind slot already match). The view that reaches +0xA0 renumbers PeerDefs.cpp's
labels, and uw_00c40e10 / uw_00c40e8a are anchored on them: one fails its byte
compare and the other can no longer be told from two siblings, so the gate
refuses to guess.

COMMENTS ARE FREE; CODE IS NOT. Before adding a view to a TU, check:
    grep -F ",<destination>," reverse/functions.csv | grep -c 'object-symbol=[$]'
and if it is non-zero, re-anchor those rows (give them a parent=) FIRST.

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
