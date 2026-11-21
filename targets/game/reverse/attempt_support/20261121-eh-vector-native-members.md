# Complete original ehvecdtr/ehvecctr C++ recoveries

Ready for root-only normal admission after the canonical terminate callable is
admitted. One evidence-backed source form per complete original TU succeeded.
Original library members, current ledger, claims, Git and productive sources
were never changed by this worker. All outputs are private and BFME_OBJSTORE
was off. No Microsoft CRT implementation source was read.

## Complete source and byte scope

| Source | Native full procedures | Complete code bytes |
|---|---|---:|
| game/Libraries/Source/CRT/VS2003/ehvecdtr.cpp | ArrayUnwindFilter009F6D06/18; __ArrayUnwind009F6D18/94; ??_M009F6D76/96 |208|
| game/Libraries/Source/CRT/VS2003/ehvecctr.cpp | ??_L009F6EE4/98 |98|

Both full candidate TUs emit exactly the original whole-member code scope,
without extra code definitions. All four raw COFF bodies are byte-identical to
their original libc.lib bodies, not merely relocation-masked prefixes.

Original native member hashes:

- ehvecdtr.obj: 5df79725f97f58721818c293ad77d872c18910996c3771950489baf98773888a
- ehvecctr.obj: be5be268b9dcbe3b5113408cfbe036eb39591c69c100bc9e470f7fee0a489a2d

Candidate source hashes:

- ehvecdtr-CANDIDATE.cpp: a207ee4d801dbc1624319565dfebb1f02542ea85c24bec945d42211c8f7e3999
- ehvecctr-CANDIDATE.cpp: f04a9a55823af86d62c0fe3cebd185a5a9c123e05ed7e286b7648a5f3edd7ac4

Candidate patches are adjacent. Complete evidence is proof.json; the reproducible
probe and finalizer are ../probe-b1-ehvec-family.py and
../finalize-b1-ehvec-family.py.

## Independent ABI, native headers and donor adaptation

Original CodeView and candidate Z7 CodeView agree for ALL four defined
procedures, including exact full extents. The outer iterators/ArrayUnwind have
void return and stdcall CC7, arguments void*, unsigned32 stride, signed32 count,
and real thiscall CC11 callback pointer(s), each void(void*). Names encode P6E,
not a silently demoted P6A declaration. Native calls deliver the element address
in ECX; outer returns pop16/20 as expected. Static ArrayUnwindFilter retains its
original cdecl/private optimized form and 18B body.

Full original and candidate public platform layouts agree: EXCEPTION_RECORD80B,
EXCEPTION_POINTERS8B, CONTEXT716B, FLOATING_SAVE_AREA112B, with identical fields,
sizes, offsets, bases and absence of virtual slots. The constructor TU does not
define these platform records and no layout is invented for that source.

BFME2 donor147fd3e52b36ee0306aaeef5b316beb09f7c7671 supplied the two identically
placed Code/Libraries/Source/CRT/VS2003/ehvec*.cpp files and
reverse/attempt_support/ehvec-thiscall-d1binl-20261024/readme.md. The new lever
over the older failed callback/compiler attempts is the native VC7.1 /d1Binl
front-end option admitting the actual P6E callback type. Source profile is
/O1 /G6 /MD /EHsc /d1Binl. B1 uses its actual existing native PlatformSDK
Include alias, replacing the donor sweep-shim include path. No shared header,
class copy, manual SEH frame or hand-written cleanup body is introduced.

## Complete SEH and dependency binding

The actual candidate parent DIR32 operands identify these three full12B tables:

| Runtime table RVA | EnclosingLevel | Filter RVA | Handler RVA |
|---|---:|---|---|
|00D45870|-1|009F6D47|009F6D6B|
|00D45880|-1|0|009F6DBE|
|00D45890|-1|0|009F6F2E|

For each table, the actual object relocation target, its actual owning code
section and its real label offset were rebased to the independently placed
parent. Every relocated table byte equals retail. The compiler's .sxdata4B in
each TU resolves its real symbol index to the same original strong undefined
Function __except_handler3. Raw symbol index numbers legitimately differ from
the original object; they are not runtime table addresses. No hand-label or
state pin was made. Z7 controls preserve complete code and the full semantic
relocation/table graph despite per-compilation $T/$L ordinal renumbering.

Real external dependencies:

- __SEH_prolog009F7E88/59 and __SEH_epilog009F7EC3/17, already native library rows.
- __except_handler3 via .sxdata; Root has now admitted the real canonical CPP
  provider at009F6C50, f12bebc903. No second route pin is needed.
- ?__ArrayUnwind@@YGXPAXIHP6EX0@Z@Z at009F6D18, already named and to be rehomed.
- ?terminate@@YAXXZ at009F7EDA, originally called by native ehvecdtr COFF REL32s
  and the actual retail PE import thunk. The first probe's NORMAL map correctly
  reported it unresolved for Filter and ArrayUnwind. A private independent map
  copy with only this genuinely proven target gave all306B strict, masked=false,
  unresolved[]. No productive map or pin was changed. The normal canonical
  terminate body admission must precede claiming those checks as ordinary passes.

## Native extent reconciliation and ordinary admission

Current old-library rows are Filter18, ArrayUnwind47, destructor72 plus its
24B child009F6DBE, constructor74 plus its24B child009F6F2E. Full original member
CodeView and physical code prove94,96,98: ArrayUnwind's previously omitted47B
is its filter/handler suffix, including its original final INT3 after the
noreturn call; iterator cleanups are emitted inside their own full procedures.

Ordinary add_match refuses a full96/98B parent while its child row survives;
parent= does not exempt add_match's overlap check. Use the documented evidence-
backed retraction/tombstone route for the two old placeholder child identities,
with each full parent conversion in the same atomic commit. Do not introduce
new compiler-label rows, hand aliases, padding copies or duplicate coverage.
Native row_extent.check of the four full corrected parents with those two
child rows removed returned no findings against actual current Ghidra extents
and retail bytes. Every new compiled-body boundary guard also returns None.

Normal root add_match operations, each with its appropriate identity/extent
note and MODEL, keeping full original TU context:

1. `?ArrayUnwindFilter@@YAHPAU_EXCEPTION_POINTERS@@@Z 0x009F6D06 18 game/Libraries/Source/CRT/VS2003/ehvecdtr.cpp --replace-existing`
2. `?__ArrayUnwind@@YGXPAXIHP6EX0@Z@Z 0x009F6D18 94 game/Libraries/Source/CRT/VS2003/ehvecdtr.cpp --replace-existing`
3. `??_M@YGXPAXIHP6EX0@Z@Z 0x009F6D76 96 game/Libraries/Source/CRT/VS2003/ehvecdtr.cpp --replace-existing`, paired with documented retraction/tombstone of `?d_009f6dbe@@YAXXZ` at009F6DBE.
4. `??_L@YGXPAXIHP6EX0@Z1@Z 0x009F6EE4 98 game/Libraries/Source/CRT/VS2003/ehvecctr.cpp --replace-existing`, paired with documented retraction/tombstone of `?d_009f6f2e@@YAXXZ` at009F6F2E.

These are ordinary verified same-identity rehomes, not a fake identity correction
to allow an extent. If another normal gate refuses, preserve its exact reason;
this packet does not grant bypass permission. Keep defined siblings accounted
for by the ordinary source-claim rules while banking each verified body, and
publish the whole ehvecdtr member coherently so an intermediate mixed original
archive/C++ provider set is not mistaken for complete link proof.

This prepares four genuine main procedures/306B of authored C++ from complete
original library members, with47B of previously missing ledger coverage. The
two old cleanup rows are absorbed, not two extra new tasks/bytes. No source
row, full-image link, runtime, crash, memory or performance result is claimed
by this private packet. Normal source currency, admission, whole gates and
current provider/link checks remain Root work.
