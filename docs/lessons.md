# Codegen recipes

What this tree has learned about reproducing retail's bytes from C++, and about
the ways a green build can still be wrong. Full history in `docs/lessons-archive.md`
and in `git log`.

**This file is curated, not append-only.** Edit a recipe in place; the commit
message is the place for the war story. If you find yourself adding a section
that restates one already here, you have found the section to edit instead. It
is kept near 2,000 lines deliberately -- a reference nobody can read end to end
stops being consulted and starts being re-derived.

## Contents

**A. What the byte gate proves, and what it cannot**
- [The gate is blind to NAMES and authoritative about IMMEDIATES](#the-gate-is-blind-to-names-and-authoritative-about-immediates)
- [Byte-exactness proves OUR SOURCE COMPILES TO THOSE BYTES, never that the name is right](#byte-exactness-proves-our-source-compiles-to-those-bytes-never-that-the-name-is-right)
- [Masking hides three different things -- name which one you have](#masking-hides-three-different-things----name-which-one-you-have)
- [A 100% masked screen is necessary, not sufficient](#a-100-masked-screen-is-necessary-not-sufficient)
- [A naked body passing the byte gate proves nothing](#a-naked-body-passing-the-byte-gate-proves-nothing)
- [Row boundary rules](#row-boundary-rules)
- [An extent complaint on an already-matched row is about the body, not the row](#an-extent-complaint-on-an-already-matched-row-is-about-the-body-not-the-row)
- [The baseline exe is not entirely compiler output](#the-baseline-exe-is-not-entirely-compiler-output)

**B. Identity: how a green row names the wrong function**
- [The four false greens](#the-four-false-greens)
- [The four detectors, and what each is blind to](#the-four-detectors-and-what-each-is-blind-to)
- [Any two 5-byte jmp thunks byte-match, so count the callers](#any-two-5-byte-jmp-thunks-byte-match-so-count-the-callers)
- [A CALL SITE beats stub topology, and beats the relocation argument](#a-call-site-beats-stub-topology-and-beats-the-relocation-argument)
- [Compare relocation STRUCTURE, not relocation NAMES](#compare-relocation-structure-not-relocation-names)
- [An ICF POOL address is never identity evidence](#an-icf-pool-address-is-never-identity-evidence)
- [A row can be GREEN because a layout error cancels a naming error](#a-row-can-be-green-because-a-layout-error-cancels-a-naming-error)
- [TWO defects can MULTIPLY to a pass](#two-defects-can-multiply-to-a-pass)
- [A one-slot rotation MUST leave a hole: the spare placeholder is the proof](#a-one-slot-rotation-must-leave-a-hole-the-spare-placeholder-is-the-proof)
- [A name held HOSTAGE on the wrong address forces someone to invent a name](#a-name-held-hostage-on-the-wrong-address-forces-someone-to-invent-a-name)
- [For a family of forwarders, THE CALLEE NAMES THE CALLER](#for-a-family-of-forwarders-the-callee-names-the-caller)
- [An ordered call sequence names its unnamed members, like a vtable does](#an-ordered-call-sequence-names-its-unnamed-members-like-a-vtable-does)
- [Two placeholder conventions, for two different things](#two-placeholder-conventions-for-two-different-things)
- [Re-homing a mis-anchored row: the recipe](#re-homing-a-mis-anchored-row-the-recipe)
- [Retiring a row can break a matched row in ANOTHER file](#retiring-a-row-can-break-a-matched-row-in-another-file)
- [Byte-verification is evidence about bytes, in both directions](#byte-verification-is-evidence-about-bytes-in-both-directions)
- [SYMBOLIC vs VIEW-BASED: which matched rows are evidence about a header](#symbolic-vs-view-based-which-matched-rows-are-evidence-about-a-header)

**C. MSVC codegen: what source controls and what it does not**
- [Ordering levers that ARE source-controllable](#ordering-levers-that-are-source-controllable)
- [Register allocation: sometimes a wall, sometimes a lever](#register-allocation-sometimes-a-wall-sometimes-a-lever)
- [Encoding tie-breaks with no source lever](#encoding-tie-breaks-with-no-source-lever)
- [MSVC has a private calling convention, and it decides which functions share a file](#msvc-has-a-private-calling-convention-and-it-decides-which-functions-share-a-file)
- [A callee defined LATER in the same TU can still inline](#a-callee-defined-later-in-the-same-tu-can-still-inline)
- [A this-adjustment hoists only if the source goes through the owning base](#a-this-adjustment-hoists-only-if-the-source-goes-through-the-owning-base)
- [`this` is not always the entry pointer: measure the base, and use a control](#this-is-not-always-the-entry-pointer-measure-the-base-and-use-a-control)
- [Reaching a member as a MEMBER or through a local pointer picks the registers](#reaching-a-member-as-a-member-or-through-a-local-pointer-picks-the-registers)
- [Retail rarely caches a global or a member across a call](#retail-rarely-caches-a-global-or-a-member-across-a-call)
- [Write the reference's loop; MSVC's rotation is the target](#write-the-references-loop-msvcs-rotation-is-the-target)
- [Byte loads widen within the array they belong to](#byte-loads-widen-within-the-array-they-belong-to)
- [A call through an ILT thunk is PERMANENTLY unreachable from source](#a-call-through-an-ilt-thunk-is-permanently-unreachable-from-source)
- [A frame size is computed from sizeof, so no view reaches it](#a-frame-size-is-computed-from-sizeof-so-no-view-reaches-it)
- [`and esp,-8` with no floating point anywhere](#and-esp-8-with-no-floating-point-anywhere)
- [x87 flags from byte tests are mostly false](#x87-flags-from-byte-tests-are-mostly-false)

**D. Exceptions, vtables and object layout**
- [vptr scheduling: screen before writing](#vptr-scheduling-screen-before-writing)
- [novtable is one knob with two effects](#novtable-is-one-knob-with-two-effects)
- [Read destructible subobjects off the unwind states](#read-destructible-subobjects-off-the-unwind-states)
- [throw() removes EH frames and temporary unwind states](#throw-removes-eh-frames-and-temporary-unwind-states)
- [Buy throw() with an explicit specialisation, not a shim directory](#buy-throw-with-an-explicit-specialisation-not-a-shim-directory)
- [SEH shape is a flag, not code](#seh-shape-is-a-flag-not-code)
- [The EH-temporary transposition: a two-byte wall this toolchain cannot cross](#the-eh-temporary-transposition-a-two-byte-wall-this-toolchain-cannot-cross)
- [A vtable slot belongs to the class that DECLARES the virtual](#a-vtable-slot-belongs-to-the-class-that-declares-the-virtual)
- [`delete p` shape reads the type's completeness](#delete-p-shape-reads-the-types-completeness)
- [Temporaries schedule by how visible their type is](#temporaries-schedule-by-how-visible-their-type-is)
- [Layout facts you can read straight off the bytes](#layout-facts-you-can-read-straight-off-the-bytes)

**E. Diagnosing a wrong class shape**
- [Accessor disagrees with a body: second member, or shifted class?](#accessor-disagrees-with-a-body-second-member-or-shifted-class)
- [A getter and a setter for one member cannot disagree about its offset](#a-getter-and-a-setter-for-one-member-cannot-disagree-about-its-offset)
- [Displacement is CUMULATIVE: map the whole class with its getters](#displacement-is-cumulative-map-the-whole-class-with-its-getters)
- [An offset read out of a TU is only as ABSOLUTE as that TU's layout](#an-offset-read-out-of-a-tu-is-only-as-absolute-as-that-tus-layout)
- [Count the vptr](#count-the-vptr)
- [Measure on a PARAMETER to break the circularity](#measure-on-a-parameter-to-break-the-circularity)
- [A CONSTANT delta is a shifted member list; a SCATTERED one is a different list](#a-constant-delta-is-a-shifted-member-list-a-scattered-one-is-a-different-list)
- [A vendored class that is too SMALL needs BYTES, not a new class](#a-vendored-class-that-is-too-small-needs-bytes-not-a-new-class)
- [To correct an allocation size, use a standalone view -- not derive-and-pad](#to-correct-an-allocation-size-use-a-standalone-view----not-derive-and-pad)
- [A member-order difference does not need the header changed](#a-member-order-difference-does-not-need-the-header-changed)
- [A pad that must be UNDONE at every call site is a wrong layout](#a-pad-that-must-be-undone-at-every-call-site-is-a-wrong-layout)
- [Never validate a layout fix against the CURRENT byte output](#never-validate-a-layout-fix-against-the-current-byte-output)
- [The rows ALREADY matched tell you which regions are safe to change](#the-rows-already-matched-tell-you-which-regions-are-safe-to-change)
- [Known BFME divergences from the reference](#known-bfme-divergences-from-the-reference)
- [BFME ships BOTH module layouts -- a family lever is not a family fact](#bfme-ships-both-module-layouts----a-family-lever-is-not-a-family-fact)
- [BFME overloads on integer signedness where the reference has one function](#bfme-overloads-on-integer-signedness-where-the-reference-has-one-function)

**F. Strings**
- [Four string levers, four symptoms: pick by which operation retail calls](#four-string-levers-four-symptoms-pick-by-which-operation-retail-calls)
- [Retail's string payload is at m_data+8, and this tree inlines m_data+4](#retails-string-payload-is-at-m_data8-and-this-tree-inlines-m_data4)
- [A by-value string argument needs a VISIBLE copy, not an opaque one](#a-by-value-string-argument-needs-a-visible-copy-not-an-opaque-one)
- [Read the whole shims directory before asking for a new one](#read-the-whole-shims-directory-before-asking-for-a-new-one)

**G. STL and STLport**
- [Two STLport knobs a merged container body usually needs](#two-stlport-knobs-a-merged-container-body-usually-needs)
- [Two more cl-line flags that look like a rewrite and are not](#two-more-cl-line-flags-that-look-like-a-rewrite-and-are-not)
- ["Same body, different template instantiation" is only cheap if something keeps the old one alive](#same-body-different-template-instantiation-is-only-cheap-if-something-keeps-the-old-one-alive)

**H. Headers and shims**
- [Before adding a shim, check whether the tree already OWNS that header](#before-adding-a-shim-check-whether-the-tree-already-owns-that-header)
- [A shared shim header is not the place for a member declaration](#a-shared-shim-header-is-not-the-place-for-a-member-declaration)
- [One source name, two real functions, two addresses](#one-source-name-two-real-functions-two-addresses)
- [An access specifier can make a body unmergeable](#an-access-specifier-can-make-a-body-unmergeable)
- [Header edits cost the host-wide full gate -- batch them](#header-edits-cost-the-host-wide-full-gate----batch-them)
- [Shim headers do not invalidate the build cache](#shim-headers-do-not-invalidate-the-build-cache)
- [Enumerate a header's includers with a SOURCE GREP, not the deps sidecars](#enumerate-a-headers-includers-with-a-source-grep-not-the-deps-sidecars)
- [The `// cl:` line must be the FIRST line of the file](#the-cl-line-must-be-the-first-line-of-the-file)

**I. The ledger: rows, pins and funclets**
- [A `pinharvest` row in symbols.csv is a candidate, not an address](#a-pinharvest-row-in-symbolscsv-is-a-candidate-not-an-address)
- [`tools/pin_consistency.py` enforces one name, one function](#toolspin_consistencypy-enforces-one-name-one-function)
- [A work packet's callee pins were matched by name, not followed](#a-work-packets-callee-pins-were-matched-by-name-not-followed)
- [A $L funclet row self-heals ONLY if its notes say gen-funclet AND parent=](#a-l-funclet-row-self-heals-only-if-its-notes-say-gen-funclet-and-parent)
- [$L numbering is file-sequential, so any codegen change ABOVE a pin renumbers it](#l-numbering-is-file-sequential-so-any-codegen-change-above-a-pin-renumbers-it)
- [A funclet with NO candidate is a diagnostic, not a pin problem](#a-funclet-with-no-candidate-is-a-diagnostic-not-a-pin-problem)
- [An ambiguous funclet heal is a REFUSAL, not a crash -- and the tie may be fake](#an-ambiguous-funclet-heal-is-a-refusal-not-a-crash----and-the-tie-may-be-fake)
- [Making a broken thing HEAL is not the same as making it right](#making-a-broken-thing-heal-is-not-the-same-as-making-it-right)
- ["symbol not found in object" has three causes and none is a byte mismatch](#symbol-not-found-in-object-has-three-causes-and-none-is-a-byte-mismatch)
- [A fold can delete a compiler-generated symbol another matched row needs](#a-fold-can-delete-a-compiler-generated-symbol-another-matched-row-needs)
- [When a reference inline owns a row and your body needs a different offset](#when-a-reference-inline-owns-a-row-and-your-body-needs-a-different-offset)
- [Ledger file mechanics](#ledger-file-mechanics)
- [The marker system, and what a marker count is worth](#the-marker-system-and-what-a-marker-count-is-worth)

**J. Folding, screening and measuring**
- [Screen a whole cluster with ONE build, before applying anything](#screen-a-whole-cluster-with-one-build-before-applying-anything)
- [A small miss(N) is a CLASSIFICATION, not a distance](#a-small-missn-is-a-classification-not-a-distance)
- [Some rows only need repointing](#some-rows-only-need-repointing)
- ["Naked donor" is not a reason to skip -- 75% of them are the BEST folds](#naked-donor-is-not-a-reason-to-skip----75-of-them-are-the-best-folds)
- [Three screen MATCHes that are not folds](#three-screen-matches-that-are-not-folds)
- [Screening one symbol does not license applying the DONOR](#screening-one-symbol-does-not-license-applying-the-donor)
- [The first build after --apply can look like a pass it never ran](#the-first-build-after---apply-can-look-like-a-pass-it-never-ran)
- [A stripped marker over an unmoved row hides a non-matching body](#a-stripped-marker-over-an-unmoved-row-hides-a-non-matching-body)
- [A destination can be uncommittable at HEAD](#a-destination-can-be-uncommittable-at-head)
- [Two ways to finish a reference TU that locate.py gives up on](#two-ways-to-finish-a-reference-tu-that-locatepy-gives-up-on)
- [Fresh views need tuning ONE AT A TIME against the residue](#fresh-views-need-tuning-one-at-a-time-against-the-residue)
- [When a diff lands on a masked DIR32, read the relocations, not the disassembly](#when-a-diff-lands-on-a-masked-dir32-read-the-relocations-not-the-disassembly)
- [Triaging a red DIR32 gate: the count points, the structure proves](#triaging-a-red-dir32-gate-the-count-points-the-structure-proves)

**K. Working rules**
- [Convert families, not functions](#convert-families-not-functions)
- [Count the blockers before starting, and stop at single digits](#count-the-blockers-before-starting-and-stop-at-single-digits)
- ["It did not match" is a deferral, not a dead end](#it-did-not-match-is-a-deferral-not-a-dead-end)
- [PREDICT THE CASUALTIES, and predict the OFFSETS](#predict-the-casualties-and-predict-the-offsets)
- [Two independent derivations meeting is the standard to reach BEFORE acting](#two-independent-derivations-meeting-is-the-standard-to-reach-before-acting)
- [When two measurements DISAGREE, the finding is the disagreement](#when-two-measurements-disagree-the-finding-is-the-disagreement)
- [When BOTH witnesses are names, the question may be undecidable -- say so](#when-both-witnesses-are-names-the-question-may-be-undecidable----say-so)
- [Validate a NULL against a control before trusting it](#validate-a-null-against-a-control-before-trusting-it)
- [COUNT BODIES, NOT ROWS, where duplicate names are the audit](#count-bodies-not-rows-where-duplicate-names-are-the-audit)
- [Silence is UNDECIDED, never confirmed](#silence-is-undecided-never-confirmed)
- [Every base class in a virtual family is a size outlier BY CONSTRUCTION](#every-base-class-in-a-virtual-family-is-a-size-outlier-by-construction)
- [A refusal that prints nicely and PASSES is worse than a crash](#a-refusal-that-prints-nicely-and-passes-is-worse-than-a-crash)
- [A REGRESSION test and a BOUNDARY GUARD are different things](#a-regression-test-and-a-boundary-guard-are-different-things)
- [Design a defect out rather than avoiding it](#design-a-defect-out-rather-than-avoiding-it)
- [A finding is only as durable as the instrument that produced it](#a-finding-is-only-as-durable-as-the-instrument-that-produced-it)
- [A discipline survives only if it is cheap enough to use every time](#a-discipline-survives-only-if-it-is-cheap-enough-to-use-every-time)
- [Re-derive a diagnosis that arrives from somewhere else](#re-derive-a-diagnosis-that-arrives-from-somewhere-else)
- [A fabricated MECHANISM in a comment is worse than a wrong offset](#a-fabricated-mechanism-in-a-comment-is-worse-than-a-wrong-offset)
- [Investigation sequencing is not COMMIT sequencing](#investigation-sequencing-is-not-commit-sequencing)
- [A full gate's GREEN is a statement about the base it ran on](#a-full-gates-green-is-a-statement-about-the-base-it-ran-on)
- [Git and process](#git-and-process)


--------------------------------------------------------------------------

# A. What the byte gate proves, and what it cannot

The gate compiles your source and compares the bytes against retail, with
relocation sites masked on both sides. Everything in this section follows from
those two facts.

## The gate is blind to NAMES and authoritative about IMMEDIATES

Opposite properties of one check, and this tree has confused them in both
directions:

  **A NAME is unvalidated.** A row's symbol, a member name, an enum spelling, a
  function identity -- all compile to the same instruction whether right or
  wrong. Only a second body disagreeing exposes them.

  **AN IMMEDIATE IS PROVEN.** `isKindOf(KINDOF_INERT)` compiles to `push 0x54`;
  if retail pushes `0x58` the row does not match. Same for a vtable slot
  (`ff 50 20` against `ff 50 2c`), a structure offset, a frame size.

So when you find a renumbered enum, a shifted vtable or a changed constant, the
exposure is NEVER the matched bodies -- those are self-proving. It is bodies not
yet converted (which will fail as an ordinary byte mismatch when attempted) and
new code written against the vendored header. That is a header correction to
schedule, not a fire to fight. Say which of the two you mean when you report
one: "N call sites are testing the wrong bit" reads as the first and is usually
the second.

## Byte-exactness proves OUR SOURCE COMPILES TO THOSE BYTES, never that the name is right

The central lesson of this file, and it cost a fully built, fourteen-address
GameWindow mapping on full unmasked evidence. Fourteen bodies each matched
retail exactly at a predicted address, on 37/37, 40/40 and 13/13 surviving
bytes. The mapping was still wrong, and retail's own callers said so.

**The self-check is one grep: before moving a row, ask who calls the address it
is LEAVING.** A matched caller that names the symbol outranks any amount of byte
agreement.

## Masking hides three different things -- name which one you have

Wherever you mask before comparing, ask what a fully-masked input compares equal
to. Three distinct failures, three different fixes:

    QUANTITY   no surviving unmasked byte at all, so the body compares equal to
               ANYTHING of its length. AIPlayer's `$L86009` is a data table of
               four label pointers, relocations covering all eight bytes; it
               "tied" with a real funclet. Absence of evidence, counted as a
               match.
    LOCATION   identical surviving bytes, with the discriminator inside the
               masked region. LANGameInfo's three `$L` candidates are each four
               unmasked bytes of `lea ecx,[ebp-0x14]; jmp`; only the relocation
               TARGET separates them.
    ASYMMETRY  a relocation WE have that retail does not. Masking chooses which
               bytes to blank from the COMPILED side's relocation list, so a
               site that is a relocation for us and a literal for retail is
               blanked on both sides:

                   ours    8b c1  c7 00 <DIR32 ??_7X@@6B@>  c3
                   retail  8b c1  c7 00  00 00 00 00        c3

               **A linked absolute address is never zero.** All-zero retail bytes
               under one of our DIR32 sites prove retail stored NO POINTER there.
               67 matched rows across 20 bodies are in this state, and they have
               PLENTY of surviving bytes, all of which agree.

`tools/null_reloc.py` sweeps the third class and runs in the full gate.

**A HIGH surviving-byte count is not a pass either.** 44 of 958 folds rest on
three bytes or fewer and printed identically to the 694 resting on sixteen or
more, so the column earns its place -- but both GameWindow draw-data families
rest on ALL 37 of their bytes and are still wrong. A low count says "this verdict
is thin"; a high count says nothing at all about identity.

## A 100% masked screen is necessary, not sufficient

`DataChunkInput::openDataChunk` reaches 100% of masked bytes and still fails the
build, because the masked comparison cannot see a call that resolves to the
WRONG FUNCTION. Retail's `AsciiString("")` there calls RVA `0x00102D90` -- an
unidentified 77-byte dump that reads `[ecx]` and compares `[m_data+0xC]` against
its argument, a `set` and not the constructor at `0x00888BC0` this tree resolves
to. A perfect score means every byte you can see agrees, and the bytes you cannot
see are exactly the ones that name the callee. When a 100% screen fails the
build, read the relocation SYMBOLS out of the object.

## A naked body passing the byte gate proves nothing

`Functions: OK N/N` on a file that is still `__declspec(naked)` / `__asm { __emit
... }` -- the dump reproduces its own bytes by construction. Removing only the
`naked` keyword around a pure `__emit` block also still passes. A conversion means
NO `__asm`/`__emit` anywhere in the file; check what is on disk, not the ledger,
since `status=matched` can be left over from the original dump commit.

**And its name was never tested.** Read the body against the claimed signature
BEFORE starting: `ret N` against the mangled argument list, `or eax,-1` against a
void return, this-relative offsets that make no sense for the claimed class.
`??1TooltipUpgrade@@UAE@XZ` ends in `ret 4` -- destructors take no arguments, so
the name is wrong whatever the bytes say.

`?Recolor_Texture@W3DAssetManager@@QAEHHHHHHHHHH@Z` was a fabricated nine-int
thiscall signature resting on a 658-line `__emit` dump; the only two callers of
its address in the whole image are `D3DXSaveMeshToXofEx` and
`D3DXPatchSaveMeshToXofEx`, from `d3dx9.lib`. Retired.

## Row boundary rules

A MASM dump matches at any length (one 231-byte function claimed 1006 bytes and
swallowed three neighbours); a 5-byte row matches any `E9` thunk; a 1-byte row
matches every bare `ret`. Before adding or trusting a row: deref the thunk chain,
measure the body by disassembly, and check the claimed address is an instruction
boundary -- linear-decode from the containing function's start, and interior
`int3` is decisive. Functions from different TUs do not interleave in the image.

## An extent complaint on an already-matched row is about the body, not the row

The build asks you to raise a row's `target_size` and the row already matched
from its donor. Do not raise it: the extent was proven when the donor landed, so
if the merged body now needs more bytes the merged body is wrong -- it is reaching
past where retail's function ends. Raise the extent LOCALLY as a diagnostic to
read what the extra bytes are, then REVERT before fixing the body. Usually an
inlined tail retail calls out of line, or a destructor the merged shape emits.

## The baseline exe is not entirely compiler output

`CopyProtect::notifyLauncher` at `0x001020D0` will not match, and the reason is
not in our source:

    0x0010211F   eb ..      jmp    (where the port emits 75 .. jne)
    0x00102173   eb 00      jmp    to the very next instruction
    0x001021B2   eb 04      jmp    followed by 90 90 90 90

A `jmp` whose displacement is zero, and `nop` padding inside a body, are what a
**hand patch** looks like. `baselines/bfme1/workshop-vanilla-1.03` is a
redistributable, not a pressed retail image. The damage is narrow -- the other
three `CopyProtection.cpp` bodies byte-match from clean C++ -- but the rule
generalises: when a diff is *only* conditional branches turning unconditional, or
shows `nop` runs inside a body, suspect the binary before rewriting the source.

--------------------------------------------------------------------------

# B. Identity: how a green row names the wrong function

Four ways a row goes green while naming something else, four detectors, and none
of them establishes identity on its own.

## The four false greens

    E9 ILT JUMP           a `jmp rel32` is five bytes of which four are masked.
                          ONE byte is compared, so every 5-byte tail-call thunk
                          in the tree byte-matches every other.
    LOCAL-REPLICA BODY    a `*_Thunk.cpp` donor that declares its own struct to
                          reach an offset has chosen those offsets as free
                          parameters to fit the bytes it wanted. Squad_isOnSquad
                          declares the membership pair at +0x04 and matches;
                          three siblings compiled from the REAL class say
                          +0x08/+0x0C.
    VIRTUAL-DISPATCH      `8b 01 ff 60 0c` -- `mov eax,[ecx]; jmp [eax+0x0C]`.
      THUNK               No E9, no jump target. ANY method forwarding to vtable
                          slot +0x0C compiles to exactly those bytes.
    ADJUSTOR THUNK        `add ecx,0x194 ; jmp <dtor>`. Eleven bytes, six of them
                          real immediate -- MORE compared bytes than the others,
                          which is exactly why two rows could share it and look
                          solid. **A comparison being partly real is not the same
                          as it being enough.** The question is never how many
                          bytes agreed, but whether the bytes that agreed could
                          distinguish this function from another.

## The four detectors, and what each is blind to

    the ILT unique-stub test    needs an E9; cannot say whose a SHARED body is
    multi_name's structural test cannot separate two forwarders to one vtable slot
    multi_name's FAMILY rule    needs two names; most stubs carry one
    size_outlier                needs siblings implementing the same method

Each is blind exactly where another sees, so **a clean run from one is not a
clean bill of health**, and a hit from one is a candidate rather than a verdict.
`0x0000B9CE` is the proof: four 5-byte jmp thunks are structurally identical
bytes, so `multi_name` correctly calls it a fold while `size_outlier` flags it.

**A matched caller naming the symbol outranks every inference any of them makes.**

The fast two run in the commit hook via `tools/identity_guard.py`, baselined in
`reverse/identity_baseline.txt`; `null_reloc` runs in the full gate. Those counts
only go DOWN.

## Any two 5-byte jmp thunks byte-match, so count the callers

The discriminator is the call profile, one pass over `.text`:

    hist = Counter()
    for i in range(len(text) - 5):
        if text[i] in (0xE8, 0xE9):
            hist[tva + i + 5 + int32_at(text, i+1)] += 1

Then read the count against what the claimed function is FOR.
`?addTeam@TeamsInfoRec@@QAEXPBVDict@@@Z` claimed a stub with 6,947 callers;
retail calls addTeam from a handful of places, and 6,947 is what a string
destructor's import thunk looks like. The stub was `jmp 0x0005EE90`, already
recorded as `??1AsciiString@@QAE@XZ`.

**The second test, for when both counts are 1.** Caller counts go silent exactly
where most cases live -- all four constructor thunks re-homed in one pass had 1
against 1. Incremental linking emits ONE thunk per function, so build the map of
every 5-byte `E9` to its target and ask how many stubs reach the body: if a body
already has a matched claim under name B and exactly one stub jumps to it, that
stub is B's thunk, whatever name a row has parked on it.

## A CALL SITE beats stub topology, and beats the relocation argument

Five rows were re-homed on the reasoning that ICF needs identical bodies WITH
identical relocations, so two module constructors storing different vftables can
never fold. **Retail folds them anyway.** All five re-homings were wrong and are
retracted.

    0x00048B9E  called by friend_newModuleInstance of AutoHealBehavior,
                SpyVisionUpdate, EMPUpdate and FireOCLAfterWeaponCooldownUpdate
    0x0002A379  called by FireWeaponWhenDamagedBehavior and MobMemberSlavedUpdate

Several classes' factories calling ONE constructor stub is direct evidence of a
real fold. **The unique-stub test says which body a stub REACHES; it cannot say
whose that body IS when the body is shared.** Check callers before re-homing.

## Compare relocation STRUCTURE, not relocation NAMES

Measured against 1,041 multi-name addresses:

  * **Target NAMES flags 367 and is useless.** Two classes' constructors name
    different vftables -- a masked DIR32 the comparison never sees -- so this
    flags every template and module family in the tree.
  * **REL32 call targets gives 225 and still over-flags.** One function under a C
    and a C++ decoration, and per-instantiation template symbols, resolve to
    different names for the same call.
  * **Structure is decisive: 11.** Mask every relocation site to zero in BOTH
    bodies, then compare the remaining bytes AND the `(offset, type)` list.

Two ICF-folded bodies **are the same bytes**, so their relocation SITES must
coincide however differently our objects name the targets. Names are a property
of our compile; sites are a property of the code. Final classification: 965 real
folds, 65 all-placeholder, 11 that cannot be one body.

## An ICF POOL address is never identity evidence

A matched row whose address carries many names tells you only that your body
compiled to a shape many classes share. `??0StringInfo@@QAE@XZ` at `0x0005C5D0`
shares that address with **eighteen** other constructors -- it is the generic
"zero three pointers" constructor, and our StringInfo lands there precisely
BECAUSE we made it twelve bytes. The row is a binding to a pool the wrong layout
fell into, and it reads as proof that the layout is right.

**The converse is the useful half: a UNIQUELY named row IS identity evidence.**
Retail's `~StringInfo` at `0x004368F0` is the only claimant of that address and
destroys exactly two members -- `lea ecx,[esi+4]` into one destructor, then
`mov ecx,esi` into a different one. Two members at +0 and +4, reverse order: an
AsciiString and a UnicodeString. BFME's StringInfo is 8 bytes, not twelve.

Run `tools/multi_name.py` before treating a matched row as evidence about a
class. This has now cost two hypotheses.

## A row can be GREEN because a layout error cancels a naming error

The worst case, because nothing complains. In `VertexMaterialClass` three bodies
-- Get_Ambient, Get_Specular, Get_Emissive -- each stop on ONE byte, all the
same: retail loads the material pointer with `mov eax,[ecx+0x08]` where this tree
emits `[ecx+0x0C]`. Given that shift, two MATCHED rows in the same file read one
field past their names: `?Get_Ambient_Color_Source@` is `mov eax,[ecx+0x14]` and
`?Get_Emissive_Color_Source@` is `[ecx+0x18]` -- our offsets for those fields,
while in retail's layout +0x14 is EmissiveColorSource and +0x18 is
DiffuseColorSource. They match ONLY because the +4 shift slides our field under
retail's load.

**Expect it: fixing the layout will turn those rows red, and that is the fix
working.** Before a class correction, identify which matched rows are green by
cancellation and predict them as expected casualties in the commit message --
otherwise the next agent reverts a correct change to get the count back.

## TWO defects can MULTIPLY to a pass

Six GameWindow draw-data rows are green because a wrong row-to-address BINDING
and a wrong LAYOUT cancel. Our GameWindow is 4 bytes short at the front, so our
`.color` write lands on retail's `.image` byte. Verified against our own object
rather than inferred: our compiled `winSetEnabledColor` is
`lea [eax+eax*2+0x12]; mov [ecx+eax*4]` -- instruction for instruction retail's
`winSetEnabledImage`.

**So a matched row proves the offsets it COMPILES, never that the RIGHT FUNCTION
compiled them.** Where a class is uniformly shifted and the fields are a
contiguous same-size run, an off-by-one-slot name binding is invisible to the
gate, because the shift supplies exactly the error that cancels it.

## A one-slot rotation MUST leave a hole: the spare placeholder is the proof

The strongest form an identity argument has taken here. A rotation cannot consume
its own displaced body, so it necessarily leaves one body spare -- and in every
confirmed case the spare was in the ledger under a generated `?dup_` name.

    VertexMaterialClass   the colour-source rotation left Get_Diffuse_Color_Source
                          unclaimed, with a marker and no row
    W3DTerrainVisual      two one-slot rotations left ?dup_00730a50 and
                          ?dup_00730af0 holding the two real bodies
    GameWindow            three position-2 getter bodies, all three ?dup_

**If you suspect a rotation and there is no spare body, that absence is evidence
AGAINST it** -- which makes this stronger than any of the four detectors.

## A name held HOSTAGE on the wrong address forces someone to invent a name

`winSetStatus`'s row sat on a body that ORs into +0x04. `m_status` is +0x08, and
two matched rows in the same accessor run already said so. The correctly-written
body compiles to a 19-byte sequence occurring exactly once in retail, at
`0x00478420` -- and that address was already claimed by
`?_bfme_winSetStatus@GameWindow@@QAEII@Z`. Someone had converted the right body
and had to invent a name for it.

**An invented `?_bfme_`, `?dup_` or thunk-file name adjacent to a real one is a
SYMPTOM** -- read it as evidence of a displaced row nearby, not as scaffolding.
Likewise **a dense band of address-derived names inside an otherwise-named
accessor run marks displaced rows**: five placeholders interleave GameWindow's.

## For a family of forwarders, THE CALLEE NAMES THE CALLER

No heuristic, no topology: decode the rel32, follow the ILT, read the name.
W3DTerrainVisual's water accessors are thin forwarders into WaterRenderObjClass:

    0x00730A20 -> setGridChangeAttenuationFactors  = setWaterAttenuationFactors
    0x00730A50 -> setGridTransform                 = setWaterTransform

The ledger had two of them one body early. Both retired, tombstoned and
re-anchored; W3DTerrainVisual.cpp 27/27.

## An ordered call sequence names its unnamed members, like a vtable does

`W3DRoadBuffer::loadRoads`'s donor called its seven callees `loadRoadsHelper0..6`.
The destination's source calls seven named methods in a fixed order, and four
already resolved to ledger-named `W3DRoadBuffer` members at exactly the positions
the source puts them. Four independent agreements in a row fix the other three BY
POSITION. The agreements have to be independent and in order to count -- one or
two matches is coincidence.

Same argument as "ask the vtable": scan `.rdata` for the target address as a VA
(`rva + 0x400000`), read the rest of that vtable, and look every entry up. Six of
eight `Apply@` bodies were named that way because their vtable also held an
already-named `Clone@X`, and `Clone` is class-specific because it constructs its
own class.

**Do not finish the job by elimination.** Elimination is only as strong as the
claim that the group is closed, and the slot that looked like the last two
candidates' `Clone` held a 44-byte dump where every other `Grid*` `Clone` is 85 --
the window was misaligned. Anything whose only argument is *what else could it be*
is a guess.

## Two placeholder conventions, for two different things

  * `?j_XXXXXXXX@@YAXXZ` -- an ILT thunk claimed by ADDRESS, 5 bytes, no identity
    claim. 1,048 of these in `gen_small`.
  * `?dup_XXXXXXXX@@YAXXZ` -- a REAL BODY whose identity is unknown or disputed,
    parked under its address.

A mis-anchored row is re-homed to whichever fits its SIZE. Neither throws away
byte coverage, and neither asserts an identity the evidence does not support.

## Re-homing a mis-anchored row: the recipe

Retiring a false row throws away real byte coverage. Re-homing keeps it:

  1. retire the false-named row and tombstone it in `reverse/deleted_rows.csv`
     with the evidence, so a union merge from an older branch cannot restore it;
  2. `add_match '?j_00048b9e@@YAXXZ' 0x00048B9E 5 <donor> \
         --notes 'object-symbol=<the symbol the donor actually emits>;...'`

**`object-symbol=` is what makes it work.** The row's NAME becomes
address-derived and claims nothing, while the byte comparison still knows which
emitted symbol supplies the bytes. Coverage unchanged, identity claim gone, no
file deleted.

Deletion is the fallback for what re-homing cannot reach -- three AsciiString
rows went that way because their donor held nothing else and `verify_source_claims`
forbids a row-less `.cpp`. That took the matched total 161787 -> 161784, stated
in the commit message. **An honest decrease beats a total you cannot trust.**

**The FILE name describes the C++; the ROW name describes the bytes**, and after
a re-homing they must differ. `AutoHealBehaviorCtorThunk.cpp` keeps its name
because it genuinely declares that constructor -- which is precisely what makes
the compiler emit a tail-call thunk of the right shape. Do not rename these
donors; renaming rewrites every row's `source` in a union-merged ledger for a
benefit one comment delivers. The comment is mandatory.

## Retiring a row can break a matched row in ANOTHER file

Retiring the AutoHealBehavior row broke
`?friend_newModuleInstance@AutoHealBehavior@@` -- a 96-byte matched body in a
different file -- with `unresolved call(s)`. **The delta verify that passed when
the retirement landed only built the donor.** Before retiring, scan matched rows
for calls to the address, and run a full gate after a batch of retirements even
when each verified individually.

## Byte-verification is evidence about bytes, in both directions

Address `0x0018B520` was UPGRADED from `?d_0018b520@@YAXXZ` to `?isOnSquad@Squad@@`
as a byte-verified identity, and later DOWNGRADED to `?dup_0018b520@@YAXXZ` on
the evidence of two symbolic siblings. **The same 38 bytes verified both times.**
A byte-verified upgrade is not proof of identity either.

## SYMBOLIC vs VIEW-BASED: which matched rows are evidence about a header

**A symbolic matched row is evidence about the header, because the COMPILER chose
the number. A view-based matched row is not, because the AUTHOR did.**

`Squad.cpp` has two matched rows naming the member symbolically --
`m_objectIDs.size()` and `m_objectIDs.push_back(objectID)`, no view anywhere near
them -- giving start +0x08, finish +0x0C, end_of_storage +0x10, this tree's
layout exactly. That indicted `?removeObject@Squad@@`, which is matched only
through an inline `struct BFMESquad { char pad[0x04]; VecObjectID m_objectIDs; }`.


--------------------------------------------------------------------------

# C. MSVC codegen: what source controls and what it does not

## Ordering levers that ARE source-controllable

- Initialiser list emits in declaration order; body assignments emit as written.
  Retail's store order tells you which to use -- a flag at +0x54 stored before
  the word at +0x50 means body statements, not init list.
- Independent locals initialise in declaration order.
- Switch arms lay out in source order; sort the jump table by target address to
  recover it.
- `x = y` (inline `operator=` forwarding to `set`) materialises the destination
  before the argument; `x.set(y)` pushes the argument first.
- A discarded return value becomes a tail jump: retail's real call where you emit
  `jmp` means the function returns something the reference discards.

## Register allocation: sometimes a wall, sometimes a lever

Two phenomena get filed together and only one is a wall.

**RECOVERABLE -- a chain that switches register one load too early.** On
`ControlBar::onPlayerRankChanged` the walk switched from eax to ecx ahead of
retail's; routing the local-player fetch through an IN-CLASS accessor on the view
made it reuse eax down the chain exactly as retail does.

**A WALL -- two registers swapped wholesale.** On `Path::appendNode` retail keeps
the parameter in esi and `this` in edi while the merged TU does the reverse.
Three source shapes all produced byte-identical output.

Three screens before spending anything on it:

  * **Rule out an inlined same-TU callee first.** It looks IDENTICAL to a
    tie-break in a byte diff -- extra register traffic clustered around a missing
    call. The tell is a call whose target is not one the body should make.
  * **The accessor lever needs a GLOBAL at the head of the chain.** It works by
    changing how that global is fetched. On a pure member walk off `this` there
    is no global fetch to reorder and it cannot help.
  * **Check it is not CSE.** Five 83-byte twins logged as register allocation
    were common-subexpression elimination of a member read: retail consumes
    `m_begin` as a memory operand so nothing holds it, then re-loads it, while
    MSVC materialises it into esi once. A view does NOT defeat this, even reading
    through a distinct view type at the same offset -- MSVC folds on the address
    computation and does not care that the struct type differs.

**And the cost rule: a register-allocation wall moves on a TU FLAG, never on a
source rewrite.** The one time it was beaten, a string shim on the cl line did
it; seven separate source rewrites of `RequestSetName` produced nothing. MSVC's
allocator responds to what the TU declares and includes, not to how you spell the
statement.

**A fresh view can make a body WORSE.** `objectChangedTeam` agreed on 62.4% of
masked bytes; correcting all six known offset facts at once dropped it to 29.7%.
The offsets were right and the spellings were wrong -- each fresh view moved
allocation more than the corrected offset was worth. Add one view, measure, keep
or revert.

## Encoding tie-breaks with no source lever

**A SIB base/index inversion.** `W3DGadgetStaticTextImageDraw` came out 237 of
238. Retail computes `end.x` as `8d 1c 08` (`lea ebx,[eax+ecx]`, base EAX, index
ECX); this toolchain emits `8d 1c 01`. Identical operation, identical registers,
inverted encoding. It survived every reordering, and `/G7` rewrote the body.

That instance is a wall, but the class is not: **when one operand comes from a
member of a padded VIEW STRUCT, re-spell it as a direct address dereference.**
`InGameUI::removeMilitarySubtitle` came out 154/154 with one byte wrong, and
reaching the record pointer as `*(Rec **)((UnsignedByte *)this + 0x818)` instead
of `view->militarySubtitle` encoded it retail's way.

**An allocator split.** `drawStaticTextText` came out 344 of 346: retail spills
`tData` to `[esp+0xc]` and defers `push ebx / push ebp` past the early return,
leaving a register free later.

When the last difference is which register got picked or how an equivalent
encoding was spelled, stop rewriting. Log it, and note that the body, the layout
and the convention were all correct -- that is the part worth keeping.

## MSVC has a private calling convention, and it decides which functions share a file

`drawStaticTextText` is entered with its first argument in **EAX**:

    callee   sub esp,0x2c / push esi / push edi / mov edi,eax
    caller   push outline / push color / mov eax,esi / call ... / add esp,8

Two stack arguments, one register argument, and an `add esp,8` that does not
account for the third. Not `__fastcall`, and not anything writable on a
declaration: it is MSVC's convention for a `static` function whose every call
site the compiler can see, and this toolchain reproduces it exactly.

**A file-static retail called this way and its callers must be converted in the
same TU.** Before drawing a work packet for a body whose calls do not account for
all their arguments, find the callee and check whether it takes one in a register.

**And the inverse is the merge hazard.** Merging a body INTO the TU that defines
its callee turns the mechanism against you: `ScreenBWFilter::init` came out three
bytes short with everything right, because MSVC reached `getChipset` with the
private convention, concluded ECX survives the call, and kept a value there where
retail pays the push/pop. The tell is a caller SHORTER than retail by exactly a
callee-saved save/restore, with a value live across a call to a same-file static.
Fix: declare the callee on a view class -- declared, never defined -- and pin that
spelling at the ILT the real name already uses.

## A callee defined LATER in the same TU can still inline

`TeamPrototype::hasAnyBuildFacility` failed while three structurally identical
sibling walks passed, because the inliner declined their callees and took that
one. Declare the callee on a view class so the call survives, then alias that
spelling at the ILT address.

The screen costs one build -- list the callees defined in the same TU and rebuild
-- and **go one level deeper than your own body**: for each body RETAIL inlines
into yours, screen ITS callees for in-TU definitions too. Retail inlines the whole
`TeamPrototype::teamAboutToBeDeleted` walk into the TeamFactory one, and at that
depth MSVC also took `Team::removeOverrideTeamRelationship`.

## A this-adjustment hoists only if the source goes through the owning base

An override of a virtual declared in a *secondary* base is entered with that
subobject's `this`. Reading a member off it directly gives negative displacements:

    ours:   mov esi,ecx / mov eax,[esi-8] / mov ecx,[esi-0xc]
    target: mov eax,[ecx-8] / lea esi,[ecx-0x10] / mov ecx,[esi+4]

Retail materialises the *primary* base once and indexes forward off it. That is
not a scheduling tie-break: the reference source calls a helper declared on the
primary base, so the adjustment is a real subexpression with two uses. Write the
wrapper as an inline member of the base that declares it, then call it
unqualified. Same instruction count either way, so size is no clue -- look at
whether displacements off the entry register are negative.

**A this-ADJUSTMENT residue cannot be viewed, even in principle.**
`WorkerAIUpdate::isCurrentlyFerryingSupplies` is entered with the
`SupplyTruckAIInterface` sub-object at +0x204, so retail's `mov eax,[ecx+0xe0]`
and our `[ecx-0x124]` differ by exactly that adjustment. A view forcing retail's
encoding would read `object+0x204+0xe0` -- it would **byte-match while reading the
wrong member**, and the gate cannot tell. Where the residue is a this-adjustment
from base-class ordering, the recorded refusal is CORRECT and permanent.

## `this` is not always the entry pointer: measure the base, and use a control

`GarrisonContain::getApparentControllingPlayer` is 88/88 with nine differing
bytes, all member offsets. The first views moved every offset by a constant
-0x20, which is what proved the mechanism: MSVC treats `this` there as **the entry
pointer minus 0x20**.

Two things made that a measurement rather than a guess: the file's own
`findConditionIndex` already documented the same base, and the fourth view -- on
the `observingPlayer` PARAMETER -- needed no adjustment and landed first time.
**Keep a view that should not need the correction as a control**; without it a
uniform shift looks like a bad view rather than a different base.

## Reaching a member as a MEMBER or through a local pointer picks the registers

Not a style choice. `view->field` off a hoisted local makes MSVC keep the MEMBER's
address in a register and read small offsets from it; `self->sub.field` off a
padded view struct makes it keep `this` and read `this+K+field`. Retail picks one,
and getting it wrong moves every offset in the body.

**When a data member is the RECEIVER of a call, bind it once as a local
reference** (`Thing &t = m_thing; t.f(x);`). Spelled `m_thing.f(x)` MSVC keeps
`this` in the register and reads `this+K+field`; retail keeps the MEMBER's address
and reads `+field`, and orders `add ecx,K` before the argument push instead of
after.

## Retail rarely caches a global or a member across a call

Binding `ThePlayerList` to a local cost `showSpecialPowerShortcut` its match: MSVC
parked the local in ebp where retail loads the global three separate times.
Spell it out as often as retail does and let the compiler decide.

## Write the reference's loop; MSVC's rotation is the target

A counted `for`/`while` gets rotated (entry test peeled, value test on the back
edge) and small counted loops get unrolled -- `for (i=0;i<4;i++) size=(size<<8)|b[i]`
unrolls two-at-a-time into paired dword/word loads that no hand-unrolled spelling
reproduces. Retail's bottom-tested scan with an early exit past the loop is
`do{}while` plus `goto`; reach for that only when no plain loop form works.

## Byte loads widen within the array they belong to

Adjacent byte reads widen to the widest access that stays inside their own array:
`struct { u8 magic[2]; u8 size[4]; }` gets dword+word where a flat `u8[6]` gets
neither. Split buffers into the sub-arrays retail's accesses imply.

## A call through an ILT thunk is PERMANENTLY unreachable from source

`GameSpyInfo::removeFromSavedIgnoreList` reads 118 of 118 bytes exact and the gate
still refuses it: retail's call at +35 lands on `?j_000052bd`, an incremental-link
thunk, where this tree calls the map's `erase` directly. **Nothing in the source
chooses whether a call goes through an ILT stub** -- it is a property of how
retail's binary was linked. Record it as permanent, not deferred.

**The consequence that changes how donors are read: an `__emit` body can be
LOAD-BEARING.** It encodes the rel32 that points at the thunk, which readable C++
cannot express. So a naked dump is not always scaffolding, and "the destination
already compiles this exactly" is not sufficient grounds to fold. The screen: for
each direct call in the retail body, decode the rel32, resolve it in
`functions.csv`, and look for a `?j_` name.

## A frame size is computed from sizeof, so no view reaches it

`ControlBarSchemeManager::init` is 177 bytes with three operands differing by a
uniform **0x1BF0**. Our prologue reserves 0x243c through `__chkstk` where retail
reserves 0x84c, and the body constructs a local `INI`. **BFME's INI is 7152 bytes
smaller than this tree's.** A frame size is unreachable in principle, like the
this-adjustment residue and the ILT-routed call -- but it is TU-scoped, so it is a
small contained shim rather than a shared header change.

## `and esp,-8` with no floating point anywhere

`LANAPI::update` opens `push ebp / mov ebp,esp / and esp,0xfffffff8`. MSVC 7.1
emits that for a local needing eight-byte alignment, which normally means a double
or an `__int64` -- and that is FALSE here: scanning all 2030 retail bytes for x87
and qword operands returns nothing. That leaves `__declspec(align)`, `_alloca`, or
inline asm, and it must be settled before anything downstream can be judged, since
it fails at offset zero.

**The wider point: re-measuring after the LANAPI layout correction landed produced
NO movement at all (393/2030 before and after). A body that does not move when you
fix a real thing is telling you the real thing was not what held it.**

## x87 flags from byte tests are mostly false

`any byte in D8..DF` matches displacements and immediates: 603 of 753 flagged
functions had no x87 at all. Decode with capstone before believing an x87 (or any
opcode-shaped) label, and re-screen parked rows when a screen is fixed.

--------------------------------------------------------------------------

# D. Exceptions, vtables and object layout

## vptr scheduling: screen before writing

MSVC sinks a constructor's vptr store exactly to the end of the leading run of
same-valued member stores, no further; retail's placement varies. Compare retail's
vptr position against that prediction: if they agree, convert; if not, park -- no
source ordering reaches vptr placement. Members initialised by a member
constructor land after the vptr and before the body; stores between the interim
and most-derived vtable groups are base-subobject member inits, not body
statements.

## novtable is one knob with two effects

It removes the interim per-base vtable stores (module ctors writing each interface
vtable twice -> once) AND removes that base's unwind entry (all EH states shift
down by one, body a few bytes short). Set it by what retail shows, not habit.
Destructor variant: retail restoring only the base vptr at the end means the
derived class is novtable; a derived vptr store at entry means it is not.

## Read destructible subobjects off the unwind states

Retail's highest EH state + 1 = destructible subobjects, bases included. A base
gets an unwind entry only if it has a declared destructor -- declaring `~Base();`
(undefined) adds the missing frame; a virtual destructor where retail has none
adds a state and shifts every index.

A virtual destructor stores a vptr only in a ROOT polymorphic class; in derived
destructors it is elided as redundant, so "no vptr store AND no base-destructor
call" is the test for non-polymorphic, and neither half alone means anything.

An EH state count is another readout of the member list: `Image`'s constructor
initialises two members BFME does not have, and retail's EH state byte is **1**
where ours is **2**.

## throw() removes EH frames and temporary unwind states

`new T` carries an EH frame just to call `operator delete` if T's ctor throws;
declaring the reachable constructors `throw()` removes it (an undefined ctor is
assumed throwing). Wider: `throw()` on whatever executes between a temporary's
construction and destruction removes that temporary's unwind state. Declaring
`void __cdecl operator delete[](void *) throw();` removes the state for `delete[]`
in a destructor. Scope the declaration to a TU shim.

Counter-lesson: the constructor-inlined-into-new-expression shape is NOT reachable
from source (forceinline/throw()/nothrow all tried) -- park those.

**A view's constructor may need throw().** Without it MSVC wraps the allocation in
an SEH prologue purely to free the block if the constructor throws. On
`LocomotorStore::newOverride` that was the difference between an entire prologue
and none.

## Buy throw() with an explicit specialisation, not a shim directory

A nothrow declaration is often the whole difference between a merged body and
retail -- `addGame` was 77 diverging instructions with the throwing declaration
and 6 without. The declaration usually lives in a shared header you must not
change (`WWLib/string_base.h`). You do not need a new shim file:

    template <>
    class StringBase<UnsignedShort>
    {
    public:
        Int compareNoCase( const StringBase<UnsignedShort> &that ) const throw();
    };

An explicit specialisation REPLACES the primary for that one argument, so every
other TU sees the shared declaration untouched. Legal while nothing has forced an
implicit instantiation for that argument; declare only the members this TU calls.
`wchar_t` and `unsigned short` are the same mangled type (G) under MSVC 7.1, so
one specialisation covers both.

## SEH shape is a flag, not code

Base build is `/EHs-c-`. Right length but an extra `fs:[0]` prologue means the
per-file `// cl:` line re-enabled exceptions (`/GX-` restores). The
`mov [esp+N],esp` stash before a by-value class argument is the /EHs model; /EHsc
and /EHa add an SEH prologue retail may lack. Probe flags directly with a
throwaway TU and `build.py`'s `compile_source` instead of round-tripping the byte
gate, and give the probe the same destructible locals as the target.

**/EH mode is per-TU, so a donor needing a different one can never fold into a
destination that cannot move.** Retail's `LANAPI::RequestAccept` has NO SEH frame
while constructing and destroying a temporary, which only happens under `/EHs-c-`;
lanapi.cpp is `/EHsc` and cannot change. Record that as "wrong destination", not
"blocked" -- "blocked" invites a retry.

## The EH-temporary transposition: a two-byte wall this toolchain cannot cross

    target: 89 64 24 08   mov [esp+8], esp      ours: 8b cc         mov ecx, esp
            8b cc         mov ecx, esp                89 64 24 08   mov [esp+8], esp

`mov [esp+N], esp` is MSVC recording the address of a **by-value class argument**
so the unwind funclet can destroy it. Retail writes that record *before* setting
up the constructor's `this`; this toolchain writes it *after*.

Between them it survived `/G5`, `/G6`, `/O1`, `/O2 /Oi`, `/Ox`, `-Os`, `-Ot`,
`-Oy-`, `-Gy`, `/EHa`, `/EHs`, `/EHac`, an inline versus declared-only destructor,
and replacing the implicit conversion with an explicit temporary.

**Recognise it and stop:** correct compiled size, every member offset and vtable
slot already proven right, and the only diff a pair of adjacent `esp` moves around
a by-value class argument. There is one cl.exe in `build/toolchains/vs2003` and no
second one to try. A 93-byte specimen to start from, with everything else settled:
`?sendDisconnectChat@Network@@UAEXVUnicodeString@@@Z` at `0x006824C0`.

Log it with everything the attempt DID prove -- `setPlayerName` established that
`m_playerNameControlNames` is a file-scope array and that `winGetWindowFromId` is
`GameWindowManager` vtable `+0xDC`, and both are worth as much as the landing
would have been.

## A vtable slot belongs to the class that DECLARES the virtual

Reordering a derived header cannot move a base-declared slot. Reference base
classes often carry slots BFME lacks (SubsystemInterface adds six;
MemoryPoolObject's pure `getObjectMemoryPool` adds one) -- one wrong base slot
count shifts every virtual in every derived class. Same-name virtual overloads lay
out in reverse declaration order.

**A vtable slot read off ONE call site is a guess.** Three
AIUpdateInterface/DozerAIInterface slots move together: `getDozerAIInterface`
+0x13C against +0xFC, `isIdle` +0x180 against +0x13C -- isIdle landing exactly
where the header put getDozerAIInterface, which is what an interface that GAINED
sixteen entries looks like, not one that was reordered. Two of the three were
assigned backwards on the first attempt and the gate caught it.

**A shared header's vtable can be wrong, but a matched row proves its own slot.**
BFME's GameClient vtable is not the vendored one: `findDrawableByID` is slot 11
(+0x2C) where the header puts it at slot 8. A body that BYTE-MATCHED cannot be
dispatching through the wrong slot, since the call encodes the offset. The
exposure is unconverted bodies and new code.

## `delete p` shape reads the type's completeness

Null check + `push 1` + call through vtable slot 0 = complete polymorphic type
(deleting destructor). Plain `operator delete` call = incomplete type. Complete
the class (with virtual dtor) or keep it forward-declared to match.

## Temporaries schedule by how visible their type is

An extern, undefined constructor makes a temporary opaque and reorders the
unwind-slot store vs the receiver load; making construction visible (inline
delegation) restores retail's order.

## Layout facts you can read straight off the bytes

Element size from the `sar`/`shl` pair or a reciprocal-multiply magic constant;
POD-ness from `memmove` vs an element-wise loop; funclet count = EH-protected
temporaries; an untouched gap between stored offsets is still a member (declare
it, do not initialise it). A raw address literal is honest where a name would be
invented: `(void (*)(MultiIniFieldParse &))0x0043ABC0` emits the same push as an
unattested name without asserting one.


--------------------------------------------------------------------------

# E. Diagnosing a wrong class shape

## Accessor disagrees with a body: second member, or shifted class?

The tempting fix -- a view that moves the body onto the accessor's offset -- makes
the row match and silently merges two distinct members. There is a cheap
mechanical test needing no view and no build. Collect the offsets the class's
MATCHED TINY ACCESSORS prove (they are authoritative about their own offset,
being byte-verified) and look at the shape of the disagreement:

  * **A RUN of consecutive members displaced by the SAME delta -> the CLASS IS
    SHORT and the header is wrong.** GameWindow's `m_status`, `m_size`,
    `m_userData` and `m_instData` are every one exactly +4 out. Four coincidental
    second members all four bytes apart is not credible; one inserted member is.

  * **Anything else needs the LIVENESS TEST: does retail use OUR offset anywhere
    -- an accessor, or a matched body? If nothing does, our offset is the error
    and there is one member.**

**A gap in the accessor set is NOT enough on its own, and the rule that said so
is dead.** `Drawable::getID` falsified it within the hour: retail reads +0x100,
this tree reads +0x8C, the accessors either side both AGREE at retail's offsets,
and +0x100 sits in the gap between them. The gap rule calls that a second member.
It is not -- it is ONE member declared in the wrong position, and the row lands
7/7 by pointing at +0x100.

Current standings: **LANGameInfo PASSES** (+0x360 by get/setNext, +0x398 by three
matched bodies -- a genuine second link). **Drawable FAILS** -- one misplaced
member. **Script is UNRESOLVED**: its +0x20 has no accessor and no matched body,
only retail's bytes in the one function that cannot land, which is good evidence
the offset is real and no evidence that +0x20 and +0x28 are two members rather
than one relocated one.

So "BFME classes carry two links where the reference carries one" rests on ONE
solid case. Treat it as a single-witness observation and do not let it steer a
diagnosis.

**The mechanism of that error is the part to keep:** two positives, a rule built
to explain both, shipped without a case that could have falsified it. A rule that
explains every case you have is not evidence -- it is a description of the cases
you have. Find the case that would break it BEFORE writing it down, and if you
cannot construct one, say the rule is untested.

## A getter and a setter for one member cannot disagree about its offset

The cheapest identity evidence in the tree. Three matched GameWindow setters write
`this+0x1F8`, `+0x1FC` and `+0x200` as plain `m_nextLayout = next;` bodies. The
getters prove those offsets are **m_next, m_prev and m_parent** -- `m_nextLayout`
sits at +0x208. So all three setters are misnamed, matching only because our
header puts `m_nextLayout` exactly where retail puts `m_next`.

Reach for the getter/setter pair BEFORE escalating an identity question -- it is
one disassembly per member and it answers outright.

**And a getter and a setter for one property cannot disagree about which SLOT it
lives in.** Retail's call graph shows every `Selected` wrapper calling the SAME
setter as its plain sibling with a different INDEX, so a reading where
`GetDisabledSelectedImage` reads index 0's third field while
`SetDisabledSelectedImage` writes index 1's first field cannot be.

## Displacement is CUMULATIVE: map the whole class with its getters

GameWindow was read twice and reported wrongly both times -- first as uniformly
+4, then as "short at the front, already correct at the tail". Both were artefacts
of measuring one end. The truth is a staircase, one step per insertion:

    +0x2C m_userData  +4     +0x34 m_id      +4     +0x3C m_style    +4
    +0x1EC m_tooltip  +8
    +0x1F8 m_next    +16     +0x200 m_parent +16    +0x210 m_layout +16

**A sizeof tells you the TOTAL, never the distribution.** 112 against 108 is
consistent with one insertion anywhere, or four.

**The cheap instrument is the getters.** Each is a single load, so each PROVES one
retail offset outright -- no build, no view, no inference. Thirteen of them mapped
GameWindow after two wrong readings from partial data.

## An offset read out of a TU is only as ABSOLUTE as that TU's layout

The whole GameWindow field-order detour in one rule. Six independent getter pairs
put `Selected` exactly `+0x0C` from its plain sibling -- one whole `WinDrawData`
-- across two groups with no exceptions. But their absolute values disagreed with
the setters by a uniform four bytes:

    enabled   getters say 0x44   setters say 0x48
    disabled  getters say 0xB0   setters say 0xB4

The inline getters live in a TU whose `GameWindow` is four bytes short. **A global
-4 makes `{image, color, borderColor}` read as `{color, borderColor, image}`
shifted into the neighbouring slots** -- a phantom field order that looked like a
decisive third witness.

**Compare DIFFERENCES before comparing OFFSETS.** The spacing was trustworthy from
the first look; the absolute values carried a bias already measured in two other
files.

## Count the vptr

Reading five members and stopping is how you get an offset exactly one pointer
wrong -- and four or eight bytes is precisely the size of error that still
produces plausible, self-consistent arithmetic. `WinInstanceData` declares
`virtual ~WinInstanceData()`, so it carries a vptr at +0 that a member-list count
misses. **A class with any virtual function has one, and it is not in the member
list you are reading.**

## Measure on a PARAMETER to break the circularity

Every GameWindow derivation went through GameWindow's own layout -- the thing under
question. `?parseTooltipDelay@@` breaks it: `add ecx, 0x198` on a
**`WinInstanceData*` PARAMETER**, so the offset is measured inside
`WinInstanceData` with no GameWindow layout in the path. Combined with two
`this`-relative measurements the system becomes over-determined -- three
measurements, two unknowns, no free parameters -- and it closed on `m_instData =
0x30`, exactly what `reference/shims/gamewindow` already asserted.

**A parameter-relative measurement carries no assumption about the class you are
auditing.** Look for one before deriving a layout from `this` alone. Same move as
the GarrisonContain control view.

## A CONSTANT delta is a shifted member list; a SCATTERED one is a different list

The cheapest first read on any near-miss:

  * **constant delta across every differing operand** -> same members at a uniform
    offset. View-or-shim work.
  * **scattered divergence** -> the member LIST differs. You need the class; no
    view reaches it.

## A vendored class that is too SMALL needs BYTES, not a new class

Player.cpp carried a written verdict against `disableRadar`: "retail's
AudioEventRTS is 0x70 where this tree's is 0x64 ... a class-shape difference, not
a field view." The diagnosis was right and the conclusion was wrong. All three
radar bodies match byte for byte on a padded local:

    struct BfmeAudioEventStorage
    {
        BfmeAudioEventStorage( const AudioEventRTS &src ) : e(src) { }
        AudioEventRTS e;
        UnsignedByte _bfme_tail[12];
    };

The member sits at offset 0, so its address, constructor and destructor are
unchanged and every call stays what it was; only the frame grows. **THE
CONSTRUCTOR IS LOAD-BEARING** -- declaring the storage then assigning
default-constructs and then assigns, where retail copy-constructs in one call.

**Measure the frame per body, do not pad on faith:** `addRadar` reserves 0x60
where the other three reserve 0x70 and lives well away from them. The twelve bytes
belong to the FRAME those three share, not to AudioEventRTS everywhere.

## To correct an allocation size, use a standalone view -- not derive-and-pad

Deriving from the vendored class and padding it gets `push <size>` right and still
does not reproduce `new T(...)`: the derived constructor is inlined, so only the
BASE constructor is called, and MSVC will not reuse that return value as the
derived pointer. A STANDALONE view at retail's size, with its constructor DECLARED
AND NEVER DEFINED, has a constructor of its own and matches exactly.

Same shape as the by-value string view and the campaignmanagerascii constructor:
**declared-never-defined is what makes MSVC emit the call retail emits instead of
expanding something in its place.** Three different problems, one mechanism.

## A member-order difference does not need the header changed

An initialiser list emits in the CLASS's declaration order whatever order it is
written in -- so when BFME declares members in a different order, the reference
constructor stores each argument into the wrong slot and no list can fix it. Body
assignments emit AS WRITTEN, and that is enough:
`PartitionFilterPossibleToAttack`'s constructor lands all 32 bytes from the body
form, vptr store included. Works for POD members; a member needing construction
still wants the list, and then the order really is the class's.

## A pad that must be UNDONE at every call site is a wrong layout

`vertmaterial.h` carried a deliberate `unsigned int _bfme_vmat_v0` pad ahead of
MaterialOld, and a thunk file then carried two `reinterpret_cast<unsigned char *>(mtl) - 4`
adjustments subtracting it back off before calling through. Deleting the pad makes
those casts unnecessary and the body matches. **Treat a correction that has to be
reversed at each use as evidence against itself.**

## Never validate a layout fix against the CURRENT byte output

GameWindow.cpp's `winSetPrev` body is `m_prev = prev`. Under our short header that
writes +0x1EC, and retail's byte at that site agrees -- so the body **looks correct
and is not**: `m_prev` is at +0x1FC, and +0x1EC is `m_tooltip`, which a separate
matched row already claims. When correcting a layout, write the definitions in
terms of the MEMBERS and let the corrected header supply the offsets. The
agreement you are testing against is the thing you are fixing.

## The rows ALREADY matched tell you which regions are safe to change

The question is never "how many rows depend on this class" but **"which of them
read the region I am moving, and HOW".**

  * **A row reaching an offset through a TU-LOCAL VIEW is immune to a header
    change** -- it compiled an absolute number. Seventeen of GameWindow.cpp's
    twenty at-risk rows were this.
  * **A row that reads a member BY NAME is the one at risk.** Three did.

Enumerate by MECHANISM, not by offset range -- and enumerate properly: the first
pass here grepped for one macro name and counted five view-based rows as symbolic
because their views were spelled differently. **One naming convention is not a
census.**

## Known BFME divergences from the reference

    KindOfType        four entries longer past index 41: MOB_NEXUS 46 (ref 42),
                      IGNORED_IN_GUI 47 (43), INERT 0x58 (0x54), PROJECTILE bit
                      25 (22). KINDOF_STRUCTURE is 7 in both, so the extras are
                      not at the front.
    ObjectStatusTypes ONE FEWER entry ahead of UNDER_CONSTRUCTION, which is bit 2
                      where ZH numbers it 3. 240 use sites.
    LANMessage        two extra types ahead of MSG_INACTIVE, and the enum is
                      POSITIONAL, so every later type is renumbered by two.
    GameClient vtable off by three and five slots (findDrawableByID slot 11,
                      destroyDrawable slot 24).
    WEAPONSLOT_COUNT  4, where ZH has 3.
    StringInfo        8 bytes -- `{AsciiString label; UnicodeString text;}`, no
                      `speech` field.
    INI               7152 bytes smaller than this tree's.
    BehaviorModule    eight bytes bigger; retail's Module has no MemoryPoolObject
                      base. See `BFME_MODULE_NO_MPO`.

`getStatusBits().test(X)` compiles the enum INDEX into the instruction, so every
matched body testing any status bit is a constraint on the ordering. Collect the
constraints and solve; do not edit the enum and see what survives.

## BFME ships BOTH module layouts -- a family lever is not a family fact

`reference/shims/sweep/Common/Module.h` carries the switch as `BFME_MODULE_NO_MPO`.
Screened one file at a time: **6 land, 10 turn their destination RED** (so their
module layout genuinely is the wide one), 6 miss for unrelated reasons, 3 are
genuinely different bodies. **Setting this define tree-wide would break ten
files.** Apply the same caution to any switch that looks like it characterises a
family.

**A GREEN build under a layout define is not evidence the define is right.**
`AssaultTransportAIUpdate` stays GREEN under it and gets WORSE -- ctor miss(7)
without, miss(11) with. Nothing in that TU contradicted the define, so the build
had nothing to say; only the screen did. Take the miss count, not the exit code.
And note the shape of the proof in the RED pair: **a matched this-adjusting thunk
in the same TU is a layout witness you already own**, because a this-adjustment
encodes base offsets directly.

## BFME overloads on integer signedness where the reference has one function

    ?setFlashColor@Drawable@@QAEXH@Z   at 0xD0    Int
    ?setFlashColor@Drawable@@QAEXI@Z   at 0x164   UnsignedInt
    ?winSetLayout@GameWindow@@QAEH...  at 0x00478E10
    ?winSetLayout@GameWindow@@QAEX...  at 0x0026ED70   (return type, not a parameter)

MSVC encodes both parameter types and the return type, so these are distinct
symbols sharing a source name. A header declaring one spelling cannot serve the TU
that defines the other, and a matched row for one says nothing about the other.

--------------------------------------------------------------------------

# F. Strings

## Four string levers, four symptoms: pick by which operation retail calls

"Retail calls it, we inline it" has four shapes and four fixes. They are not
interchangeable, and all four are per-file cl-line or TU-local changes, so none
costs a full-tree gate:

    inlined DESTRUCTOR   -> /Ireference/shims/asciistringsetoutofline   (5 TUs)
    inlined CONSTRUCTOR  -> /Ireference/shims/campaignmanagerascii      (71 TUs)
    inlined str() at +4  -> /Ireference/shims/asciistring8              (6 TUs)
                            plus /ICode/Libraries/Source/WWVegas/WWLib
    inlined COMPARE      -> a TU-local view of retail's eight-byte header; the
                            include-path shims do NOT substitute, because they
                            give a strcmp-based compare where retail does a
                            length-bounded memcmp

Note `asciistringsetoutofline` does NOT fix an inlined constructor.

**A fifth symptom is NOT a string problem at all:** if the residue after the
string construction matches is an extra vptr store (`mov dword ptr [esi+4]` right
after the vtable store), that is a second vptr the vendored hierarchy carries and
BFME does not. No `.cpp` reaches it. Revert the shim with the body.

## Retail's string payload is at m_data+8, and this tree inlines m_data+4

`AsciiString::str()` inlines to a fixed idiom:

    85 c0        test eax, eax
    74 05        je   +5
    83 c0 08     add  eax, 8
    eb 05        jmp  +5
    b8 8b 38 07 01   mov eax, 0x0107388B

Counting that idiom across retail `.text` gives **808 sites, every one `add
eax,8`** -- 734 falling back to `0x0107388B` (a `char`) and 74 to `0x0107388C` (a
`WideChar`). Both string classes agree and **retail never emits `add eax,4`**. The
same idiom across this repo's objects gives 87 sites at `+4`.

The reason is in the vendored header: `AsciiStringData`'s `m_debugptr` is
compiled out under `#if defined(_DEBUG) || defined(_INTERNAL)`. Four bytes without
it, eight with -- and eight is what retail uses.

**This is safe to fix and it is cheap PER FILE.** A matched row cannot contain
`add eax,4`, because retail has no such site, so all 87 are in unlanded bodies. A
single body stuck on that one instruction does not need the tree-wide change: put
`/Ireference/shims/asciistring8` on that file's own cl line.
`UpgradeCenter::findUpgrade` came home that way with sixteen prior rows unchanged.

**The tree-wide version is a different piece of work** -- full gate, plus **403
ledger rows in those 135 sources are `uw_*` funclets anchored on `$L` labels**
that recompiling renumbers. Two more traps if you attempt it: the define must not
reach `Common/Debug.h` (it reads `_INTERNAL` too, and turns `DEBUG_ASSERTCRASH`
back on), and adding a header *earlier on the search path* does not change any
recorded header list, so `./build.sh` reuses 324 stale objects and the full gate
passes on them.

## A by-value string argument needs a VISIBLE copy, not an opaque one

Retail passes `AsciiString`/`UnicodeString` by value, and the vendored header's
copy constructor is out of line, so the temporary is opaque and MSVC schedules the
unwind-slot store after the receiver load where retail stores first. It gates
roughly 114 of 511 clean cluster donors.

The fix is a per-file view, and the obvious shape is the wrong one. A view with an
opaque copy -- declared, never defined -- still leaves MSVC hoisting the receiver's
global across the call. Retail's compiler saw a VISIBLE copy delegating to a base
constructor which is itself declared and never defined:

    class BfmeStringArgBase { friend class BfmeAsciiStringArg;
    private: BfmeStringArgBase( const BfmeStringArgBase & ); ~BfmeStringArgBase(); };

    class BfmeAsciiStringArg { public:
        BfmeAsciiStringArg( const AsciiString &that )
        { ((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
              *(const BfmeStringArgBase *)&that); }
        ~BfmeAsciiStringArg();
    private: char *m_text; };

**AND THE CONVERSION AT THE CALL SITE MUST BE IMPLICIT.** `f(Arg(x))` makes MSVC
materialise the temporary in a NAMED LOCAL and pass its address; `f(x)` builds it
directly in the argument slot, which is what retail does. So the callee has to be
declared under a name of its own rather than as an overload of the real one -- an
overload taking the real string type is an exact match and wins.

Cost is a few additive aliases at addresses already pinned under the real string
spellings, each reached through a call so the rel32 proves it -- and ZERO for any
call site whose callee is virtual, since a view's virtual signature can change
types freely.

**The same shape rule governs a LOCAL string.** This tree spells retail's one-dword
string as `BFMERetailAsciiString` with a DECLARED-ONLY literal constructor, which
schedules the unwind-slot store after the receiver load. Make it delegate visibly
to an undefined base and it matches. Copy the shape, not the spelling.

**Failure signature to know before it costs a build:** a body with a local string
has an unwind funclet of its own, and changing the local's type makes the funclet
reference the inline destructor MSVC emits. That fails as an UNRESOLVED RELOCATION
-- `e9 00 00 00 00` -- which reads like a broken build and is really a missing
alias for the destructor ILT the funclet jumps to. One additive pin fixes it.

**And check for `object-symbol=$` rows before reaching for a TU-wide string shim:**
in lanapi.cpp `asciistringsetoutofline` changes codegen enough that a funclet row
on a body you are NOT editing stops finding a byte-equal candidate.

## Read the whole shims directory before asking for a new one

They are named for the TU that motivated them, not for what they do. Five
AsciiString shims were surveyed, none judged to have both the 8-byte header and an
out-of-line copy constructor, and a sixth requested -- but `campaignmanagerascii`
has both and was already on 71 TUs. It is StringBase-based, so its 8-byte `Header`
comes from `string_base.h` rather than a field of its own, which is why grepping
the shims for the ZH `m_debugptr` marker misses it.

Two mechanics when you reach for it:

  * `/ICode/Libraries/Source/WWVegas/WWLib` goes **LAST** on the cl line.
    `string_base.h` resolves from anywhere on the path, but WWLib ahead of the
    sweep shim shadows headers sweep needs and `snmp.h` stops compiling.
  * Its `operator==` forwards to a StringBase one that is declared and never
    defined, so `a == b` compiles to a call retail does not make. Write
    `a.compare(b) == 0`.

And know the price: it makes AsciiString's copy constructor THROWING, which can
put an EH frame on anything that copy-constructs a class holding one.
`SpecialPower.cpp` absorbed that with all 13 rows intact; `W3DModelDraw.cpp` did
not.

--------------------------------------------------------------------------

# G. STL and STLport

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
include path. On InGameUI.cpp all 65 rows already landing there still verified.
**Try this before anything else when a diff opens at a container teardown.**

**Two node sizes in one TU.** `BFME_PARTICLE_LIST_NODE_TAIL` pads EVERY
`_List_node` in the TU by 0x20, and a destination can need it for one container
and not another: InGameUI.cpp's `list<SuperweaponInfo*>` copy constructor allocates
a 0x2C head node while its idle-worker lists are plain 12-byte nodes. The two
cannot share `list<>::clear()`. Give the 12-byte one a local node struct and a
local `clear()` spelled the way STLport spells it -- head re-read on every
iteration, `_STL::allocator<Node>().deallocate(p, 1)` for the free.

## Two more cl-line flags that look like a rewrite and are not

`/D_STLP_USE_STATIC_LIB` missing makes every STLport call INDIRECT: STLport
declares its exports dllimport, so a map's tree-increment compiles to a six-byte
`ff 15` through a pointer where retail has a five-byte direct `e8`. The one-byte
shift moves the whole tail and an otherwise byte-exact body reads as unrelated.
**565 cl lines carry the define, so its ABSENCE is the anomaly.**

A `// cl:` line REPLACES the flag list, it does not add to it. Two vector
destructor TUs prove the cost: `-GX` gives retail's `cmp eax,0x80` dispatch
between operator delete and the node allocator, while `/DNDEBUG /MD /EHsc` links
the DLL CRT and routes the deallocation through an imported operator delete --
same C++, 40 bytes apart.

## "Same body, different template instantiation" is only cheap if something keeps the old one alive

A call site resolving to the wrong template instantiation looks like a free fix.
But the OLD instantiation's COMDATs are matched rows too, and if your call site
was their only emitter in that TU, the fix trades one matched row for another.

`GameSpyInfo::removeFromSavedIgnoreList`: retail's `m_savedIgnoreMap` has a
twelve-byte value type, so its `erase` belongs to the generic 12-byte `_Rb_tree`
instantiation rather than the AsciiString one -- but that erase is the ONLY
expression in the TU instantiating the AsciiString tree's `_M_upper_bound`, a
MATCHED 38-byte row claimed from that same file. `operator[]` and `find()` do not
instantiate it; only `erase` does.

**And when you find the real reason, REPLACE the note that named the wrong one.**
A note naming the wrong blocker bills the next agent for the wrong fix.

--------------------------------------------------------------------------

# H. Headers and shims

## Before adding a shim, check whether the tree already OWNS that header

Five separate requests for a new shim have now dissolved on an artefact the repo
already had. `CachedFileInputStream::open` appeared to need a Compression.h shim
because BFME's `decompressData` takes a `const void *src` -- but
`Code/Libraries/Source/Compression/compression.h` is OUR copy, byte-identical to
the reference bar a provenance comment, and `DataChunk.cpp` was the ONLY file
including it, reaching the reference copy merely because our directory was not on
its include path.

**THE TELL: a MATCHED TU carrying a local workaround for a shared declaration is
evidence about the DECLARATION, not a trick to copy.**
`CompressionManager_decompressData.cpp` reproduces its body byte for byte and has
to declare its own local class to say `const`. That is retail telling you the
shared header is wrong.

**And when a shim seems wrong, check which side it disagrees with before
discarding it.** `reference/shims/gamewindow/GameClient/GameWindow.h` already
carried the exact layout nine GameWindow rows needed. It had been opened, read as
disagreeing, and dismissed -- because it was compared against the DESTINATION's
current class rather than against the retail bodies. Agreeing with the bodies and
disagreeing with the destination is precisely what a correct shim for a wrong
destination looks like.

## A shared shim header is not the place for a member declaration

`ArchiveFileSystem.cpp` did not compile for twelve hours because two copy
constructors' declarations were added to a shared shim header. Declaring a copy
constructor suppresses the **implicit default constructor**, and
`ArchivedDirectoryInfoMap` default-constructs its values, so a TU that merely
*included* the header stopped compiling.

There is a second effect that adding a default constructor back does not fix: with
the copy constructor visible in the shared header, MSVC stops inlining `pair`'s
copy constructor in the including TU.

**Both effects disappear if the declaration lives in the TU that needs it.**
Guard-suppress the shim (`#define __ARCHIVEFILESYSTEM_H_`) and spell the class
locally. A shim header is compiled into every TU that includes it, so any change
to a class in one is a change to all of them.

## One source name, two real functions, two addresses

The gamewindow shim declares `winSetLayout` returning `Int` where GameWindow.cpp
defines it returning `void` -- **and BOTH ARE REAL**, at 0x00478E10 and
0x0026ED70. So a shim can carry a correct layout AND a set of signatures belonging
to one TU only. **A TU-local view takes the layout without the signatures**, which
is why views keep working where the shim cannot be adopted.

## An access specifier can make a body unmergeable

MSVC encodes access in the mangled name -- Q public, I protected, A private -- so a
member the shim declares `protected` emits `?name@Class@@IAE...` while the ledger
row carries the public `QAE` spelling. No view struct and no alias pin reaches an
access specifier; only a shim-header edit does.

## Header edits cost the host-wide full gate -- batch them

Any staged header/shim change runs the full gate, serialised host-wide (one commit
queued 44 minutes). Per-file verifies (<8 TUs) take no lock: make every header edit
first, verify each dependent source with `./build.sh`, then pay the gate once.
Never run a per-file verify while a full gate is running.

## Shim headers do not invalidate the build cache

The deps cache keys on content of previously-seen paths, so a brand-new shim
compiles nothing ("Compile: 0 of 1 TU(s)") and you diff stale bytes.

**The dangerous form: a cache keyed on what was OPENED cannot see a file that
changes what WILL be opened.** Adding a new header to a shim directory does not
invalidate anything -- the sidecar records the files the compiler actually opened
last time, and a new higher-priority header is not among them. One run reported
`Compile: 0 of 3 TU(s)` and a green 209/209, which read exactly like the prediction
being confirmed. Nothing had been compiled.

**Whenever a change ADDS a file to an include path rather than editing one already
on it, force the rebuild or verify from the sidecar that the new file was opened.**
Same family as editing `reference/.../vertmaterial.h` when a local copy wins: both
are the build reading something other than what you edited.

**And `#error` proves the file RECOMPILES, not that you are editing the file the
build READS.** Those are different questions and only the second matters. Ask the
compiler for a `sizeof` with `static char (*p)[sizeof(X)] = 1;`, but validate the
probe first -- a probe silently reusing a cached object reads as a clean negative.

## Enumerate a header's includers with a SOURCE GREP, not the deps sidecars

The sidecars record what THIS worktree has compiled, not what includes what. Use
the sidecars to learn which header a TU actually opened; use a grep over sources to
learn who includes a header at all.

**And anchor the grep.** `grep -rl '/Ireference/shims/gamewindow'` also matches
`/Ireference/shims/gamewindowlist` -- a substring false positive hid an entire
third shim, and with it the fact that two shims disagree about GameWindow's layout.
When a name is a prefix of another name, an unanchored grep is a guess.

## The `// cl:` line must be the FIRST line of the file

Put an explanatory comment above it and every flag on it is silently dropped -- no
error, no warning, and the body then fails for reasons that have nothing to do with
the edit you made. Explanations go BELOW.


--------------------------------------------------------------------------

# I. The ledger: rows, pins and funclets

## A `pinharvest` row in symbols.csv is a candidate, not an address

`reverse/symbols.csv` is additive by design: each pinned address becomes one more
candidate for the resolver, which tries them in order and keeps the first that
reproduces retail's bytes. That is what makes incremental-link thunks work, and it
is why a pin cannot be read as *the* address of anything.

Measured: of the 1,361 pins whose notes say `pinharvest` and whose name also has a
matched body in `functions.csv`, **1,193 do not reach that body**. Harmless for
byte-matching -- a wrong candidate simply fails and the next is tried -- and not
harmless for reasoning.

**Before spending a name on the strength of a callee, resolve the thunk and check
it against the ledger's own body** -- and if they disagree, say so rather than
picking the convenient one.

**Corollary for any script comparing pins: intersect the candidate sets, never
compare them.** Comparing SETS for equality calls two claimants different when
they merely have different candidate lists; what matters is whether the
intersection is non-empty. Two verdicts were inverted by getting this wrong.

## `tools/pin_consistency.py` enforces one name, one function

Every address pinned to a name must follow its thunk chain to a body byte-equal to
every other body that name pins.

    python3 tools/pin_consistency.py --symbol <mangled>   # chains, extents, owners
    python3 tools/pin_consistency.py --check              # what the hooks run, 1.6s

`reverse/pin_consistency_baseline.csv` is the backlog of known-bad pin sets and
**is only allowed to shrink** -- enforced, not merely requested.

Two things it does not cover: names pinning a single address (70,144 of 70,633),
and the `functions.csv` half of the resolver's candidate list, which
`--candidates` reports.

**And the trap:** a session landed all 47 `--clear-cut` verdicts and the gate
turned 111 byte-matched rows red, 110 reaching a pin it had just deleted.
**A byte-verified caller outranks a byte-verified identity row.** `--clear-cut`
emits candidates, not verdicts; retract in small batches, full-gate each one.

## A work packet's callee pins were matched by name, not followed

A packet listed `??0AttackNugget@@QAE@XZ,0x000047A5 (already in the ledger)`.
`0x000047A5` is an incremental-link thunk jumping to `0x0059EB00`; the ledger's
`??0AttackNugget@@QAE@XZ` is at `0x001D6CD0`. The sweep took the name from its
Zero Hour candidate, found it already in the ledger, and marked the pin resolved
without following the thunk it had just printed.

**A marking says an address is pinned, never that the body is the function its name
promises.** The second check is cheaper and would have caught it alone: look at
what the ledger already claims either side of the address.

**And read the data the body points at.** The decisive evidence was the field-parse
table: the body pushes one address into `INI::initFromINI`, and at that address are
sixteen zero bytes -- an empty table. Both candidates parse fields. Two mechanics
make this readable: absolute operands in the disassembly are **VAs** while
`target_rva` is an **RVA**, so subtract 0x400000; and prove your mapping by
resolving a string you already know.

## A $L funclet row self-heals ONLY if its notes say gen-funclet AND parent=

A row whose `object-symbol=` names a compiler-local label (`$L51425`, `$T294`) is
pinned to a per-compilation ordinal, and ANY edit to its TU can renumber it.
`build.py` handles that -- `funclet_candidates` re-finds the body inside the
parent's own COMDAT group and prints "was renumbered by an edit to this TU ...
(stale ledger pin, not a byte mismatch)" -- but `is_funclet_row()` gates on the
notes containing **gen-funclet** AND a **parent=**.

A row with `parent=` but no `gen-funclet` never reaches the healer: it dies with
`symbol not found in object: $L<n>`, which reads exactly like a hard wall and is
why lanapi.cpp was called frozen for weeks. It was one word. `gen-alias` and
`gen-funclet` are not exclusive, and then the notes must say both (keep
`gen-alias;` leading, check_csv enforces that prefix).

Exactly three rows tree-wide are gen-alias + $L + parent=: lanapi's (fixed),
`?a_00bfd4b8@@YAXXZ` and `?a_00c52ae0@@YAXXZ`. If either destination looks frozen,
that is why. **THE FIX IS THE NOTE, not a new pin.**

**The healer also searched the wrong section.** MSVC 7.1 gives `__ehhandler$<parent>`
a COMDAT OF ITS OWN while the `$L` funclet bodies stay in the PARENT function's
section. Fixed by searching both.

**There is no tree-wide tripwire, and the alarm that said so is retracted.** Of
20,052 `gen-funclet` rows, every parent-less one is in a GENERATED TU
(`gen_small/`, `gen_asm/`); all 1,361 in hand-edited sources carry `parent=`. What
survives is a REGENERATION risk, not an edit risk. **A tree-wide hazard was
inferred from one instance without checking how the instances were DISTRIBUTED.
Alarm is as much a failure of measurement as complacency, and it is the easier one
to feel virtuous about.**

## $L numbering is file-sequential, so any codegen change ABOVE a pin renumbers it

Not only new declarations, and not only new types. On StagingRoomGameInfo.cpp a
plain function-pointer typedef -- no class, no members, no emitted code --
renumbers them:

    typedef Bool (__fastcall *BfmeAmIHostFn)( const GameSpyStagingRoom * );

**COMMENTS ARE FREE; CODE IS NOT**, and a `#line` directive is genuinely free. The
useful corollary is that **a view added BELOW every pinned row does not renumber
it**, so check where the pins sit before concluding a TU is frozen:

    grep -F ",<destination>," reverse/functions.csv | grep -c 'object-symbol=[$]'

(Aside: MSVC 7.1 rejects `__thiscall` on a function-pointer type with C4234, so a
hand-rolled vtable call has to be `__fastcall` -- call-compatible for a no-argument
method, and nothing to do with the renumbering.)

## A funclet with NO candidate is a diagnostic, not a pin problem

`funclet_candidates` returning nothing for a row that HAS a `parent=` means no `$L`
body in the parent's COMDAT matches retail's bytes -- so the merged body lays its
TEMPORARIES out differently. That fires before a single byte of the parent is
compared, which makes it the cheapest signal this lane has that a body carrying
unwind states is wrong. `LANAPI::addGame` is the worked case: every pin and offset
was right, and the two `getName()` temporaries were not being built the way retail
builds them.

## An ambiguous funclet heal is a REFUSAL, not a crash -- and the tie may be fake

The pin renumbered, the self-heal searched the parent's group, and two bodies
matched equally, so it declined to pick one. Correct behaviour -- but **the two
candidates were never equal.** `$L85915` is `lea ecx,[ebp-0x1c]; jmp <dtor>` --
retail's own instructions with only the jump target relocated. `$L86009` is a DATA
table of four label pointers whose relocations cover ALL EIGHT of its bytes.

`holds_funclet` masks every relocation site on both sides, so **a body with no
unmasked byte left compares equal to ANY target of its length.** The tie was
between one candidate carrying byte evidence and one carrying none. Requiring at
least one surviving byte separates them without choosing between them.

**The ambiguous-heal procedure**, in order (there was never a "three-filter
recipe"; this is the real one):

  1. **Drop any candidate with no unmasked byte.** Implemented and tested.
  2. **When the survivors differ only INSIDE the masked region, resolve the
     relocation.** `uw_00c46f00` has three candidates byte-identical in everything
     `holds_funclet` compares; their relocation TARGETS differ, and decoding the
     jump in retail's own bytes gives the ILT that forwards to the **pair**
     destructor. Only `$L49524` relocates where retail jumps.
  3. **Only if more than one survives both is it a genuine tie** -- and then it is
     a boundary finding, not a task.

**The two filters are DIFFERENT failure modes and must not be collapsed** --
filter 1 is about the QUANTITY of evidence, filter 2 about its LOCATION. Handed
the filter-2 rule, AIPlayer's tie would go hunting for a discriminator inside a
data table's relocations, and there is nothing there to find.

**And filter 2 does NOT mean "unmask it".** A pre-link addend genuinely is not an
address. Filter 2 resolves the relocation's SYMBOL to its ledger address, thunks
included, and compares that against the destination decoded from retail's own
bytes -- a symbolic comparison where the byte comparison has nothing to say.

## Making a broken thing HEAL is not the same as making it right

`uw_0045bea0` was annotated with a `parent=` so the healer could find it -- a
reasonable-looking tooling fix -- and the row then healed onto a twenty-byte body
with all twenty bytes relocated, matching on nothing. It stayed green for another
half day. The row was already bogus before the annotation; the annotation
**extended its life by one heal**. A row that cannot find its body is telling you
something: the first question is whether it should have one, not how to help it
find one.

## "symbol not found in object" has three causes and none is a byte mismatch

The message means the destination is not EMITTING the symbol the row wants. Do not
go reading the disassembly.

  **ACCESS SPECIFIER** -- check the row's access letter against the shim's
  declaration.

  **object-symbol NOTE** -- a row's notes can pin it to a spelling that is not its
  name, and `build.py` reads THAT out of the object. 1,662 of 4,402 cluster-donor
  rows carry one:

      grep -F "<symbol>," reverse/functions.csv | grep -o "object-symbol=[^;]*"

  Two shapes, one recoverable: a spelling the destination COULD emit with the
  right declaration is a view problem; a spelling naming a DONOR-PRIVATE symbol is
  not. `?preloadAssets@ControlBar@@` carries
  `object-symbol=?bfme_preloadAssets_wrapper@ControlBar@@QAEXXZ` -- a private
  wrapper whose arity differs too. The override is the correct mechanism, not a
  wart: it is what lets the donor hold a body the real class cannot express.

  **A DELETED COMPILER-GENERATED SYMBOL** -- see below.

**Run the object-symbol check BEFORE authoring, not after.** It is free and it is
one grep. `GameSpyBuddyMessageQueueInterface::createNewMessageQueue` looked like a
one-diff allocation-size fix, but its row carries an object-symbol naming a
different class's method that ICF folded onto the same body -- a repoint could
never have verified.

## A fold can delete a compiler-generated symbol another matched row needs

The merged body compiles clean and a DIFFERENT function fails with "symbol not
found in object". Some matched rows are not hand-written bodies at all -- they are
symbols MSVC emits as a side effect of an expression in the TU. Two proven shapes:

  **memory-pool placement delete.** `newInstance(Upgrade)` is the only pool-new for
  Upgrade in Player.cpp and is what makes MSVC emit its `??3Upgrade@@SAX...` row.
  **But CHECK THE GLUE'S EXPANSION before declining:** the rule is that the
  EXPRESSION disappears, not that retail reaches a different allocator.
  `InGameUI::addNamedTimer` looked like the blocker and was not -- the sweep shim's
  `MEMORY_POOL_GLUE` routes placement operator new to `::operator new`, MSVC
  inlines it to exactly retail's call, and still emits the COMDAT.

  **inline COMDAT.** `becomingTeamMember`'s call to `areModulesReady` is the only
  one in the TU, and the COMDAT copy MSVC emits for that inline is a matched
  7-byte row.

Pre-check, one command -- rows claimed from the destination whose owning class is
NOT the destination's:

    cls=Player
    grep -F ",Code/.../$cls.cpp," reverse/functions.csv | cut -d, -f1 \
      | grep -v "@${cls}@@" | grep -v "_STL@@" | grep -v '?\$'

**A related shape: an orphan accessor with NO retail caller.** `callers_of` on
`?setNext@LANGameInfo@@` returns no named caller anywhere in retail -- it is an
orphan COMDAT the linker kept, and our row is green only because converted bodies
call an accessor RETAIL INLINES AWAY. Writing the body correctly stops emitting it.
Check whether the row has another real home before declining: `setName` is called
three times from LANAPIhandlers.cpp and byte-verifies there, so it was repointed
and the fold landed.

**`tools/find_emitter.py` answers "which TU could this row live in" without a
build**, reading the already-compiled symbol tables. The distinction it enforces is
the one grep cannot make: **EMITTING is what the ledger needs, and calling is not
enough.**

## When a reference inline owns a row and your body needs a different offset

Unmergeable, and worth recognising in one read rather than three builds. The
reference's inline expansion has its OWN matched row byte-matching retail's
standalone body at some offset, while retail inlines a read of a DIFFERENT offset
into the body you are merging. Both offsets are right -- they are not the same
member, and the donor's single name for both is doing double duty. Seen twice:
`Object::areModulesReady` (+0x295 standalone against +0x341 inlined) and
`Script::getAction/setAction` (+0x28 against +0x20).

## Ledger file mechanics

**Union-merge duplicates: delete the lines by hand, not with dedup_csv.** The
ledgers mix `\r\r\n`, `\r\n` and bare-LF terminators (~94k `\r\r\n` rows) and
`add_match` indexes by physical line. `dedup_csv.py` rewrites both files normalised
-- a ~157,000-line diff conflicting with every branch in flight -- so ignore
check_csv's own `Fix: dedup_csv` hint, which is wrong for this case and agents have
followed it. Drop records whose payload is byte-identical to an earlier record,
keep the first, and do it with `tools/ledger_io.py` so terminators survive.

Do not assume it is ONE line: union merge duplicates CONTIGUOUS BLOCKS -- six exact
duplicate pins arrived in one rebase.

**And it recurs on EVERY rebase over your own pins**, not once: `merge=union`
re-applies your commit's appended pins on top of a master that already has them.
Check `check_csv` after every `pull --rebase`. **Re-homing is especially
duplicate-prone**, because a retire-plus-add-match writes the SAME ADDRESS twice in
one commit.

**symbols.csv is sorted, and its header sorts AFTER a mangled name.** The header
line `name,address,notes` sorts after any `??0...` symbol, so a naive sorted insert
places the new row ABOVE the header. Start the scan at index 1.

**A mixed-ending file turns a one-line edit into a lift accusation.** 13 cluster
destinations hold a CRLF `__emit` block inside an otherwise-LF file, and Python's
`read_text()`/`write_text()` translates on read and writes LF, so a scripted edit
silently rewrites every CRLF line and `conversion_gate.py` reports thousands of
re-added `__emit` lines. Script every edit with `read_bytes().decode("utf-8")` and
`write_bytes(s.encode("utf-8"))`, and check `git diff --stat` after.

**Comment lines that start with a mangled name are parsed as claims.**
`find_declared_unmatched.py` reads any line starting `// ?` as the next
definition's declared symbol, so a wrapped prose comment fails the claims gate on
an unrelated function. Write names in prose form.

**A marker must be ADJACENT to its definition; explanation goes ABOVE it.** Twenty
lines of explanation between the marker and the code made the hook read the body as
undeclared. This bites precisely when documenting a re-homing in place, which is
exactly when the explanation is longest.

**Redo a stale ledger patch with the TOOLS; never replay it.** Replaying is how a
union merge resurrects a retired row -- the patch reintroduces lines the tombstone
was written to keep out. Split by REPRODUCIBILITY, not by file type: hold source in
a patch, hold ledger work as a list of tool invocations, and ask of each piece "can
I regenerate this with one command?"

## The marker system, and what a marker count is worth

**Half the markers are truncated**, so a name-shaped grep undercounts by about
half: 4,545 `present-unmatched` markers carry a truncated mangled name against
4,640 carrying a full one. Treat any such count as a LOWER BOUND.

One cause, three symptoms: a bare `// ??0Class@@` marker **binds by PREFIX**, so
landing one constructor staleens the other (give the survivor its FULL mangled
name); a donor carrying a full spelling for one destination and a truncated one for
another **LOOKS multi-destination and is not**; and `find_declared_unmatched`
resolves an abbreviated label only when the file carries exactly ONE marker with
it, so **a stale marker with an overloaded sibling is invisible to it permanently**.

**Prefix resolution binds a truncated marker to the WRONG overload**, so fixing
stale markers by script would destroy true statements: `render2d.cpp` carries three
`// ?Add_Quad@Render2DClass@@` markers while the matched row is a fourth overload
that correctly carries none. **Replace such a line in place rather than deleting
it** -- files compiling macros that expand `__LINE__` change bytes below any
removed line.

**A marker can sit above a CALL, not a definition.** `W3DVolumetricShadow.cpp`
carries four `// ?Fabs@WWMath@@SAMM@Z` lines INSIDE a function body, one above each
CALL. `--apply` consumes the pair it matched and leaves the others, so landing one
inline-emitted COMDAT staleens every remaining annotation of that symbol.

**A cluster member is a MARKERED ROW, not every row its donor owns.** ini.cpp owns
256 rows and carries 32 markers, so screening every row those files own reported
224 non-members as candidates -- an "eleven ready rows" verdict that was really
two. `merge_cluster` -- the tool that ACTS -- had it right, intersecting owned rows
against `claims(...)`; `screen_cluster` -- the tool that MEASURES -- did not.
**When a measuring tool and an acting tool encode the same rule separately, the
measuring one is where the drift hides, because nothing fails when it is wrong.**

**THE MARKER QUEUE, MEASURED END TO END** -- 273 destinations, one compile each:

    5,182  markers with NO ledger row -- a body present in the tree with no
           matched retail address behind it. AUTHORING work, not repointing.
      792  miss verdicts; dropping 5-byte jmp stubs leaves ~493 real ones
      217  errors -- the symbol is not in the destination's object at all
       46  MATCH, collapsing to 16 distinct symbols, of which 10 landed

**Do not budget a lane against the marker count.** The queue is ~5% foldable and
~85% unclaimed bodies. The ten destinations judged "at floor" were screened too:
zero MATCHes, so that call is measured rather than assumed.

--------------------------------------------------------------------------

# J. Folding, screening and measuring

## Screen a whole cluster with ONE build, before applying anything

Repointing a row to find out how close it is costs an apply, a build and a revert,
and leaves the ledger dirty if you die between them. After ONE build of the
destination, read each candidate's symbol straight out of the `.obj`, mask the
relocation sites, and compare against retail:

    build.read_object_symbol_bytes(obj, symbol, size)  vs
    build.read_target_bytes(rva, size)

Twenty InGameUI candidates ranked in a single build, no applies. It put
`addMessageText` (64.9%) at the top -- it landed 388/388 -- and correctly warned off
`update`, which agrees on 19.3% and fails at offset ZERO.

**Markers are COMMENTS, so one compile answers a whole destination.** A marker
cannot change what the compiler emits, so a destination carrying 65 markers does
not need 65 builds. 24 destinations and ~1,300 markers screened in one pass against
roughly 2,600 compiles the old way. The general form: **when the thing you are
varying is a comment, an annotation or a ledger note, the expensive artifact is
invariant and belongs outside the loop.**

**Read the compiled SIZE beside the percentage.** Once the sizes differ the
percentage stops moving even as you fix real things, because every byte after the
first divergence is compared against the wrong position. Three separate correct
offset fixes left `addSuperweapon` at exactly 60.4%. Size converging on retail's is
the signal.

**Detect a match on the success string, not by counting diff lines** -- an ERRORED
run also has zero.

## A small miss(N) is a CLASSIFICATION, not a distance

Every miss(1) and miss(2) opened fell into one of four buckets, and the number does
not tell you which:

  * **A constant BFME changed.** WeaponSet's three miss(1)s are all "loop to 4"
    where ZH's WEAPONSLOT_COUNT is 3.
  * **A field offset.** `User::setName` is `add ecx,0x4C` against our `add ecx,4`:
    one byte, seventy-two bytes of layout behind it.
  * **A TRUNCATION -- the one most easily misread as drift.**
    `W3DSnowManager::update`'s three bytes are where OUR body ENDS and retail keeps
    going. A miss(3) at the END of a row is a MISSING FEATURE, not an offset.
  * **Two facts at once.** `WorkerAIUpdate::isCurrentlyFerryingSupplies` has deltas
    +0x14, -4, -4 across two classes. No single lever closes a miss whose deltas
    disagree.

Three checks before costing a miss: is the row a 5-byte jmp stub (its count is
meaningless); do the diffs sit at the END; do the deltas agree.

**And a near-miss filter hides the already-perfect.** A scan built to surface rows
within N bytes filtered out `nd == 0` along with the rows too far away. Those are
the CHEAPEST wins in the tree -- rows whose destination already compiles them
exactly. **Check what your filter excludes at BOTH ends.**

## Some rows only need repointing

`DX8Wrapper::Set_Shader` needed no source change at all -- `dx8renderer.cpp`
already produced it byte for byte, and the row pointed at `boxrobj.cpp` only
because that is where it was originally lifted from. The marker-clear screen finds
these for free: clear the marker, build the destination, and if it is already green
the work is a repoint.

## "Naked donor" is not a reason to skip -- 75% of them are the BEST folds

Two opposite operations get confused under the anti-lift policy. **Folding a dump
into a destination** puts `__emit` into readable code -- forbidden, and
`conversion_gate.py` rejects it. **Deleting a dump whose destination ALREADY has a
readable body, and repointing the row at it**, retires the dump and lands the row
on real C++ -- the best fold available.

Measured: 415 marked donors are naked, and 310 of them -- 75% -- have a destination
that already defines a body for that symbol. Screen the pair first.

**But half the cluster-marker files are naked dumps that are NOT merge work**: of
887 files carrying a `readable body of` marker, 408 are dumps and 479 are real C++.
`merge_cluster.py --list`'s per-destination count is an upper bound, sometimes a
wild one -- InGameUI.cpp listed 25 donors of which 6 were mergeable.

## Three screen MATCHes that are not folds

  * **A symbol matching from a SECOND destination** -- the body compiles identically
    in several TUs, and chasing it is ping-pong.
  * **Donor equals destination** -- a no-op.
  * **Donor under `reference/`, not `Code/`** -- repointing a row onto a
    reference-tree source is a different decision from folding two of our own files.

**And some MATCHes are not expressible as a merge at all.**
`?Set_Transform@DX8Wrapper@@` matches from both W3DWater.cpp and
W3DWaterTracks.cpp; one row cannot land in two files, and the file that owns it
carries no marker naming either. **Do not add a marker to create the cluster** --
the marker is the evidence the tool reads, and writing one to make an apply
possible is manufacturing the input rather than recording a finding.

## Screening one symbol does not license applying the DONOR

`?parseArmorTemplateSet@ArmorTemplateSet@@` screened MATCH, but the apply moved a
SECOND row in the same donor that was never screened. **Compare a donor's row count
against its marker count before `--apply`.** And check the donor's remaining ROW
COUNT after: `--plan` reports a donor with a second destination as kept, which is
misleading when the donor's ONLY row is the one you just moved -- the file survives
owning ZERO rows and the gate refuses that outright.

    grep -c ",<donor>," reverse/functions.csv

**Two cheap screens that save a build.** A donor declaring a class with a method it
never defines has made the mangled name into the pin -- folding it means importing
that fiction into a readable TU. And a masked compare can say MATCH while build.sh
says FAIL: a screen is a filter; a fold is only verified by build.sh.

## The first build after --apply can look like a pass it never ran

`merge_cluster.py --apply` repoints the rows; it does NOT clear the donor's
`present-unmatched` marker. `verify_source_claims` reads that stale annotation and
fails BEFORE the byte comparison runs, so the output is about the marker, not the
bytes. **Only the `Functions:` line is evidence.** Clear the marker first, then
build. One body did turn out to match once the marker was dropped -- which is the
trap: the message is sometimes right by accident.

**`verify_source_claims` reports the LEDGER's status, not a byte comparison.**
`matched_sources` is the status column and `--apply` sets it without building, so
immediately after an apply the message asserted a verification nobody performed. It
is reworded now and pinned by tests. **When a check's message and a check's
implementation disagree, agents follow the message.** Fix the wording where it is
emitted; docs do not reach the moment of decision.

## A stripped marker over an unmoved row hides a non-matching body

The worst state a half-finished fold can leave, because the gate reports success
BECAUSE of it: a body rewritten, its marker deleted, and only ONE of two rows
repointed. `verify_source_claims` has nothing to complain about and the byte
comparison never looks at it. Diagnosing it, `git show <sha> -- <dest> | grep
"^+.*ClassName"` does NOT work -- a signature stays as unchanged context. Compare
the bodies directly and count the markers the commit deleted against the rows it
repointed. They must match.

## A destination can be uncommittable at HEAD

`DeletionUpdate.cpp` defines `setLifetimeRange` and the ledger names only
`calcSleepDelay`, so staging the file fails the claims gate naming a function you
never went near. It sits at HEAD and is invisible until somebody edits the file for
an unrelated reason. Revert your edit, record the file, and pick another.

## Two ways to finish a reference TU that locate.py gives up on

`reference/` sources that already own ledger rows are the cheapest lane in the
tree: source and flags are both known-good. `vertmaterial.cpp` went 19 -> 21 rows
and `mapper.cpp` 23 -> 30 in one sitting without a line of new C++.

**Find them by SIZE, not by bytes.** `locate.py` places a function by masked
byte-scan and needs a relocation-free run long enough to be unique, so a body dense
with pointer stores comes back unlocated. What it prints for those is the compiled
size: take the address span the TU already owns, list every unclaimed dump in it,
and match on size. A size match is a *candidate* -- it costs one `explain_mismatch`
to find out.

**When several names match one address, ask the vtable** -- four mapper classes
compile `Apply` to the same 860 bytes.

## Fresh views need tuning ONE AT A TIME against the residue

See "a fresh view can make a body WORSE" above. **And read which REGISTER a call
goes through, not which line it sits next to:** `FileSystem::openFile` was assumed
virtual because the vtable call NEXT TO IT had shifted; adding the view emitted an
extra `mov edx,[ecx]` and took agreement from 98.4% to 95.7%. It is a DIRECT call
in both trees. The indirection is visible in the instruction -- read it.

## When a diff lands on a masked DIR32, read the relocations, not the disassembly

`explain_mismatch` rendered two vptr stores as `mov DWORD PTR [esi+0x4],0x5ec68b00`
followed by stray `.byte`s, because relocation targets are zero-filled in the
object and the disassembler ran off the end of the immediate. Read as a mystery
member, it sent an agent looking for a field that does not exist.
`read_object_symbol_bytes` returns `(body, relocs)`, and the relocation list named
both vftables outright.

## Triaging a red DIR32 gate: the count points, the structure proves

`tools/dir32.py <symbol>` lists the rows resolving to each base, and one row
against twenty says which to doubt -- but that is a pointer, not a proof: a majority
can be an ICF artifact and a 1-vs-1 split says nothing. Structure proves it. The six
symbols red on one day were **all six wrong rows**, none a second legitimate base.

**Offsets fix the class.** A base sub-object is not 0x0C bytes in one body and 0x14
in another. Padding invented to seat a body IS the finding.
**A `??_M` names a container's element** -- the call carries element size and
destructor together. Two ILT thunks are the same function only if they jump to the
same place; check the target, not the parity.
**COMDAT adjacency breaks a 1-vs-1** -- constructor, deleting destructor, vtable and
the member that uses the buffer travel together.

**Before renaming to fix a red, check the TARGET symbol's existing bases.** If the
name you are moving TO is itself referenced at a different address, the rename hands
it a second base and the gate stays red under a new name. And the completion test
needs no gate run: when the rename is done the misnamed symbol should have ZERO
DIR32 references, not one base.

**The check only fires once a SECOND base exists.** A new file that declares an
extern itself and is the ONLY reference to that name passes silently while being
just as wrong. If this recurs a third time, the fix is a positive check -- every
global a TU declares `extern` must have a symbols.csv pin agreeing with the address
its references resolve to -- not another rename.

**And a red DIR32 blocks EVERY header and shim change in the tree**, because
`.githooks/pre-commit` forces the full gate on any staged `*.h` or
`reference/shims/*`. Fixing one of these rows unblocks a category.

**Two failure modes hide it completely.** A TU that will not compile stops the gate
at the compile phase, so DIR32 never runs -- twelve hours of commits landed behind
that wall. And a Windows extended-length path threw in `verify_string_refs` after
157,929 functions had verified.

The payoff for having the gate back: it immediately caught
`RegistryGetUnicodeString.cpp` calling `RegOpenKeyExA` where retail calls
`RegOpenKeyExW`, seen as one symbol resolving to both the A and W IAT slots four
bytes apart. **When a symbol reports two bases four bytes apart in the IAT, suspect
A-versus-W before a duplicate import.**

--------------------------------------------------------------------------

# K. Working rules

## Convert families, not functions

Normalise bodies (zero rel32 operands and image-address immediates) and hash
against converted rows AND against other naked rows: ICF-folded twins convert by
substituting the one class name that reaches the mangled symbol; constructors
differing only in vtable address are one reconstruction written N times. Each
landed conversion is a model for whatever still matches it.

## Count the blockers before starting, and stop at single digits

A big function's cost is its least-known callee: count unresolved call targets
against `functions.csv`/`symbols.csv` first (`GameEngine::init`: ~50 independent
naming problems). Read the disassembly before building -- a bare `ret` against
claimed arguments, or provably dead code retail kept, kills a candidate in one read.

When a body stalls within single digits of exact with every instruction present,
the residue is retail's TU structure, not a spelling.

## "It did not match" is a deferral, not a dead end

Read `tools/re_log.py`'s status doctrine before recording a verdict:

  **DEAD_END_STATUSES** -- no-match, refuted, identity-suspect, mis-anchored -- are
  findings about the BOUNDARY. Re-serving cannot fix them.
  **DEFERRED_STATUSES** -- blocked, attempted, abandoned, partial -- are properties
  of the ATTEMPT.

Conflating them retired 535 symbols the project cannot finish without. An SEH-frame,
register-allocation, CSE or inlining-depth wall is a deferral: it was usually
measured by an agent working the body SOLO, and the land rate is 19.5% solo against
46.5% with ten or more siblings landed.

Use `re_log.is_dead_end()`, not text: `note`, `evidence`, `lever` and `correction`
are ANNOTATIONS, not verdicts.

**And sizing work off `re_attempts.log` overstates it.** The log is append-only, so
a body that later lands leaves its old note behind forever. One slice collapsed 61
matching LINES -> 58 distinct symbols -> 30 that are ledger rows -> 18 still on a
dump: a 21% false-parked rate. Do NOT filter on `status=matched` to find the
unconverted ones -- all 18 are matched, from `Code/gen_asm/*.asm`, because a dump
matches by construction. **The discriminator is the SOURCE PATH, not the status
column.**

**A logged verdict is a measurement, not a door.** Two "permanently blocked"
verdicts were overturned in one day, both by looking at evidence the original
measurement had no reason to consult.

## PREDICT THE CASUALTIES, and predict the OFFSETS

Write down which rows will go red BEFORE compiling, name the ones expected to stay
green, then compare. First use predicted three and measured ten -- and **without
the written prediction, ten red rows would have read as "the change is bigger than
expected" rather than "the model is wrong."** A count that misses is a
falsification; a count you never wrote down is a surprise you rationalise.

Sharpened by one turn: predict **each row's resulting offset**. Eleven predicted,
eleven measured, zero unpredicted. **A set of row names can be satisfied by a wrong
model that happens to break the same rows. A set of offsets cannot.**

## Two independent derivations meeting is the standard to reach BEFORE acting

The GameWindow renames had a byte proof from one lane -- thirteen getters, each a
single load -- and, derived independently from the other side, three already-matched
rows landing on the same offsets. Where a structural change is about to be made on
inference, the question is not "how strong is my evidence" but **"is there a second,
independent route to it"**.

## When two measurements DISAGREE, the finding is the disagreement

An enumeration run twice returned two answers. The exact one looked more
trustworthy, the loose one was written off in a line, and the report that followed
claimed three retail bodies had never been emitted. **The exact grep read the
LEDGER's bindings -- the thing under suspicion.** All nine bodies exist, parked
under `?dup_` names, which is why a search for the real names found nothing.

Neither measurement is "the corrected one" until you know WHY they differ, and
**a sharper rule does not supersede a cautious one until both have been run against
the same case and agreed.**

**And when two witnesses contradict, rank them by HOW THEY COULD BE WRONG** -- not
by count, and not by which was found first. Retail's own CALL GRAPH cannot be
distorted by a wrong row name; ledger row NAMES are the exact class of thing this
lane exists because it is unreliable. But that is a lean, not a settlement.
**The resolution of two internally-consistent contradictory witnesses is not a
third derivation. It is finding the question whose answer both must satisfy.**

## When BOTH witnesses are names, the question may be undecidable -- say so

`WinDrawData` element+4 -- `color` or `borderColor` -- resisted three derivations,
and the reason is structural. The call GRAPH is retail's, but "bodies named
`*BorderColor*` call element+4" leans on the WRAPPER's name, a ledger binding; and
the inline getters lean on the GETTER's name, also a ledger binding. **Two
name-based witnesses pointing opposite ways, with no structural tiebreak, because
swapping two same-width fields changes no structure.**

The one non-circular route -- a parse table, where retail names the field itself --
**is CLOSED**: `BORDERCOLOR` has zero hits in the binary; the `...DRAWDATA` keywords
exist but the parser reads the three fields positionally. **Record a negative
established this firmly as CLOSED rather than open** -- "we could not find the
table" invites another search; "there is nothing to find" does not.

**General form: when a naming question deadlocks between two ledger-derived
witnesses, look for a place where retail names the thing itself** -- a parse table,
a keyword string, a debug format. `tools/fieldnames.py` already extracts these into
`reverse/field_names.csv` (4,416 rows).

What GameWindow DID establish, and it is parked there: geometry (bases
0x48/0xB4/0x120, stride 0x6C, nine elements of twelve); `m_instData` at 0x30 and
`setTooltipDelay` at 0x1C8, closing with no free parameter on a parameter-relative
measurement; `setTooltipDelay` mis-anchored on an ICF body with zero callers;
`gamewindowlist` four bytes short because `m_userData` was moved to the tail.

## Validate a NULL against a control before trusting it

"Zero callers" and "my query is broken" produce identical output. Before concluding
two addresses had no call sites, the same code path was run against a third and
returned **70 caller bodies**. Only then was the null evidence. **Any time an
absence is the result, produce the control that proves the instrument can see a
presence.**

Same shape as a sweep that once reported "0 refs" for 314 objects it had failed to
load, and as a regression test that passed with and without its fix.

## COUNT BODIES, NOT ROWS, where duplicate names are the audit

A caller sweep over the GameWindow draw-data run counted ledger ROWS, so a single
body carrying four claimant names contributed four "caller sites". The apparent
six-to-three majority was **two bodies**. One 28-byte body wearing four names,
counted four times, in a sweep whose whole purpose was to detect bodies wearing
several names. **Where duplicate names are the thing under audit, counting rows lets
the defect vote on its own case.**

## Silence is UNDECIDED, never confirmed

Of `size_outlier`'s 14 candidates: 6 cleared, **7 with no matched caller at all**,
0 confirmed defects. The seven are undecided, not guilty -- no caller is the
absence of the evidence that would decide, not evidence of a defect.

**A detector that returns nothing has reported a result, and one that CLOSES a
question is worth as much as one that opens one.** Prefer the instrument that can
return a negative. **And when a detector goes quiet, bucket the leftovers rather
than listing them** -- the ILT sweep's 62 survivors bucketed into 47 that need
nobody, where a raw list invites the whole investigation again.

## Every base class in a virtual family is a size outlier BY CONSTRUCTION

`?Flush@Pipe@@` is 17 bytes **precisely because** `?Flush@Base64Pipe@@` is 299 and
does the work; the family median is computed over the derived implementations. Five
of six clearances in one sweep were that shape. The clearing test: build the caller
index once, then clear any candidate whose callers include the same method name in a
different class (delegation) or any method of its own class -- and note that **a
constructor or destructor names its class without a leading `@`**, so a naive
same-class check misses its own destructor.

## A refusal that prints nicely and PASSES is worse than a crash

A bare `ValueError` killing the gate is unreadable but honest -- it stops. A refusal
that reports beautifully and lets the row through is the fallback path this project
forbids, wearing the costume of an improvement. When replacing a crash with a
diagnostic, check the exit path explicitly: **does the gate still go red?**

**And build the reporting FIRST when one change removes instances of the condition
another change reports on.** Filter 2 resolves ties, so after it lands there are
strictly fewer refusals left to exercise the diagnostic against.

## A REGRESSION test and a BOUNDARY GUARD are different things

A **regression test** was verified FAILING without the change and passing with it,
so it proves the change did something. A **boundary guard** passes either way today
and only fails against a wrong future implementation. Both are worth writing;
**claiming a boundary guard as a regression test is how a suite grows tests that
certify nothing.** At least three tests written in one day passed with and without
the fix they claimed to cover.

## Design a defect out rather than avoiding it

Filter 2 had to avoid two known traps -- set-equality over additive symbol
addresses, and treating an unpinned symbol as agreement. Neither was avoided by
remembering to; both were made unreachable. **No new comparison was written** (the
gate already resolves a relocation by trying each candidate, so set equality is not
expressible on that path), and **the verdict is three-valued** -- with only `False`
eliminating, so an unresolvable tie stays a REPORTED tie.

**A rule you must remember fails the moment someone writes a small script that
feels obviously right.** `len({addrs_a, addrs_b}) == 1` with two EMPTY tuples comparing
equal declared an unpinned symbol a real fold -- the same masking failure, reproduced
four hours later by someone who had just read it. **Ask a scratch script the same
question you ask a committed one: what does an empty result compare equal to?**

## A finding is only as durable as the instrument that produced it

Two of the most productive scripts in this effort were reported as "built and
validated" while living in a session scratchpad. The findings landed; the
instruments did not. **Land the instrument in the same stretch as the finding it
produced**, with tests, and say "built, not yet committed" when that is what
happened.

**The careful tool is usually right.** `multi_name` declined to guess on five FAMILY
candidates and was right about every one; the follow-up script written to "settle"
them produced two wrong refutations and two false folds. When a tool's cautious
verdict feels unsatisfying, the caution was the tool being correct about the limits
of its evidence, and the instinct to go past it needs an instrument at least as
careful as the one that stopped.

## A discipline survives only if it is cheap enough to use every time

The prediction files, the deps-sidecar check and the stop rule caught five wrong
bindings in one day. The reason they worked is not that they were rigorous -- it is
that **each one costs almost nothing**. The expensive version -- review boards,
formal write-ups before each attempt -- would have been skipped by the third attempt.
**Design the check so that using it is cheaper than justifying skipping it.**

## Re-derive a diagnosis that arrives from somewhere else

A premise travelled between two lanes and a lead and was wrong at every hop. Ten
minutes of reading bytes stopped a repoint that could not have worked. **A diagnosis
arriving from another lane is a hypothesis with a good prior, not a finding** -- and
this applies with most force to the relay in the middle: a lead passing a lane's
diagnosis onward launders it into fact.

**Refuse a stale go-ahead.** An approval issued before your latest evidence is not an
instruction about it. When a go-ahead crosses a finding that changes the question,
the finding wins and the approval needs re-asking.

**And withdraw a wrong rule about a SHARED tool loudly.** A lesson claiming
`merge_cluster --apply` discards uncommitted edits was wrong; every other lane
working around behaviour the tool does not have is more expensive than the original
confusion.

## A fabricated MECHANISM in a comment is worse than a wrong offset

`GameWindowFields.cpp` had `winSetDisabledImage` writing `m_hiliteDrawData` under a
comment asserting *"BFME never wrote a distinct disabled-image path here."* That is
an invented mechanism, constructed to justify a body that made a wrong row verify.

**A wrong offset is a mistake and the next reader can measure it. A wrong offset with
a mechanism attached is an argument, and the next reader has to refute it.** A comment
may state what was MEASURED and what remains UNKNOWN. It may not supply a reason the
measurement did not establish.

**Contrast the shim comment that named its own resolution condition** --
`gamewindowlist` documented precisely the thing it could not settle, and caller
evidence arriving later discharged it. A comment that states its unproven condition
precisely is worth writing even when you cannot discharge it.

## Investigation sequencing is not COMMIT sequencing

"One change, one prediction, its own commit" does not survive when the first change
has no green state of its own -- splitting it means landing the first one red. When
a staged investigation converges, ask whether each stage has a green state before
insisting on one commit per stage.

## A full gate's GREEN is a statement about the base it ran on

**Eighteen commits landed during one full-gate run**, so its green described a tree
that no longer existed. Worse, that gate refreshed `reloc_names.csv` -- a *valid*
refresh of an 18-commit-stale tree, which is what makes it dangerous: it looks
current, it is internally consistent, and it silently reverts eighteen commits of
other lanes' updates. **Treat any file a long run REGENERATED as stale output rather
than as a result.**

The choices look like *trust it* (wrong) or *re-run it* (ten minutes, and the base
may move again). **The one that works is neither: treat the green as provisional and
re-verify cheaply on the new base** -- one scoped `./build.sh <file>`, seconds --
since the expensive part was establishing that everything else is green.

## Git and process

**One agent per checkout, not one agent per cluster.** There is one index and one
`reverse/functions.csv`, and `merge_cluster.py --apply` git-adds both. So the
committer's staged set contains the other agent's row repoints without their sources,
the pre-commit gate only byte-verifies the sources THAT agent staged, and it passes
leaving the ledger naming a file that does not hold those bodies. Give a second agent
a `git worktree` (seed `build/` by hardlink and `build/readability/counts.json` by
COPY) or a different clone.

Corollary: authoring-without-applying is safe ONLY if nobody else can commit your
tree -- `git commit` takes the working tree for tracked files.

**Worktrees do NOT isolate the stash stack.** `refs/stash`, the reflog and the object
store are one per REPOSITORY. A bare `git stash pop` applied another lane's held work
and dropped their ref. Never pop bare; prefer a patch file or a temp branch. Do NOT
add `rebase.autoStash` -- it pushes and pops through the same shared stack.

**Never reset a checkout you share.** `git reset --hard` did not feel like a mutation
at the time; it felt like setup for a read-only investigation, which is exactly how
the dangerous ones look. Investigate from a worktree you own, or from `git
cat-file`/`git show` against a ref, which touch nothing.

**A push loop that trusts an empty commit range cannot see its own failure.**
`git log origin/master..HEAD` is empty when you are pushed AND when a conflicted
rebase has left HEAD detached with your commit only in the reflog. Use
`tools/push_retry.sh`, which never silences the pull, refuses to start mid-rebase,
and confirms the commit SUBJECT is in origin/master.

**Quote the heredoc when a commit message contains backticks.** `git commit -F -`
with an unquoted `<<EOF` lets the shell execute backticks and `$`.


**The {pfn, -100, 0} DLINK member-pointer wall is a vbptr-inheritance signature.**
A dozen `d_002f6330.asm` bodies materialize PMF constants delta=-100/vbindex=0 and
were blocked because every reconstruction gave delta=+4 or vbindex=4. Measured law
(probe `build/_pmf_v6.cpp`): MSVC 7.1 encodes delta=-100 with vbindex=0 exactly when
the class's vbptr is INHERITED from a base sitting at +0x68 that introduces the
virtual base at its own +0 (so vbtable[0]==0), with the member's class at +4:
delta = 4 - 0x68. A most-derived-introduced vbptr instead yields vbtable[0]==-vbpofs
and delta==member offset — the shapes that do not match. Skeleton to copy:
`reference/shims/objectdlink/ObjectDlinkPmf.h`. The generic dispatch loop
(`mov eax,[obj+0x68]; mov ecx,[eax+vbindex]; add ecx,delta; lea ecx,[ecx+obj+0x68]`)
falls out byte-shaped once the PMF is passed as a value (parameter or local the
optimizer cannot fold).

**SIB base/index order is a source-level lever, not allocator noise.** A body that
misses by one ModRM/SIB byte -- ours `[edi+edx]`, retail `[edx+edi]` -- has the
counter and the pointer in swapped SIB slots. MSVC 7.1 puts the POINTER in the base
slot for `p[i]`, `*(p+i)` and `i[p]` alike; it puts the COUNTER in the base slot
only when the pointer enters the address as an integer on the right of the counter:
`*(const char *)(i + (unsigned int)p)`. Proven on 0x009D7B80 (57/57 from a
one-byte miss, `build/sib_gen.py` matrix); the same four-byte SIB defect gates the
563-byte VP6 filters 0x009AFA60/0x009AFEC0 (score 0.97) and any "single SIB byte"
partial. Tool for the other side of that coin: `tools/vtable_lookup.py <vtable VA>`
prints a class's retail slot table, ledger names per slot, and every ctor/dtor that
installs the vtable -- the usual answer to "owning class unidentified".
