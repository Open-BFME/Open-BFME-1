# Complete native vector-copy-constructor iterator

Ready for root-only normal admission of the fully reserved ehvccctr.obj family.
One evidence-backed source form plus unchanged Z7 control, explicit private
objects, BFME_OBJSTORE=off. No productive source, ledger, pin, claim, Git state
or shared object was changed. No implementation source of Microsoft CRT was read.

Proposed source `game/Libraries/Source/CRT/VS2003/ehvccctr.cpp`.
Candidate SHA256:
`5a52d8b2b9ad3fae7e76f6c326cbd2c6fb7da0be3343c34da363a66606a8094a`.
Adjacent candidate CPP, new-file patch and proof.json; reproduction script
`../probe-b1-eh-copy-member.py`.

Independent original libc.lib `..\build\intel\st_obj\ehvccctr.obj` SHA256
`a5c205fb211b86d53df5dcae61b59a930c060957d27daf4b72200aa3a6402f02`
contains exactly one complete executable procedure,102B:
`??__C@YGXPAX0IHP6EX00@ZP6EX0@Z@Z` at RVA009F7036.
Its main path ends RET18 at009F7081..009F7084; its true finally action occupies
009F7084..009F709C, ending RET009F709B before the independent FF25 import at
009F709C. Original and candidate CodeView independently give the full102B
procedure extent. All102 raw code bytes equal the original COFF, not a masked
prefix. The candidate emits no additional code body.

The actual original and candidate procedure contracts agree exactly: void,
stdcall CC7, six arguments destination void*, source void*, unsigned32 stride,
signed32 count, thiscall CC11 copy callback void(void*,void*), thiscall CC11
destructor callback void(void*). Native loop pushes the source and puts the
destination in ECX before the copy callback; the callback consumes the one
stack argument. Success/count/frame lifetime is identical to the native body.

Donor147fd3e52b36ee0306aaeef5b316beb09f7c7671:
`Code/Libraries/Source/CRT/VS2003/ehvccctr.cpp` and the existing
ehvec-thiscall-d1binl-20261024 recipe. The whole original source context is
retained with /O1 /G6 /MD /EHsc /d1Binl. Only the introductory target address
was translated. No private headers, class copies, forced symbols, aliases,
assembly, emitted bytes, manual frame or hand-written action are used.

Both normal and Z7 controls pass102/102 against the actual current NORMAL
symbol map: no private dependency mapping, masked fallback or unresolved name.
The original full four-relocation graph is retained: scope-table DIR32+3,
SEH_prolog REL32+8, SEH_epilog REL32+71, ArrayUnwind REL32+97. The compiled-body
boundary guard reports no issue.

The complete12B scope table at RVA00D458A0 is {-1,0,VA00DF7084}. Its original
$T330+8 relocates to original $L323 at parent+78. Each private object independently
binds its actual scope-table symbol and actual same-section action label at+78,
then reproduces all12 retail bytes after normal relocation. Its .sxdata4B
resolves the real index to strong undefined Function __except_handler3, as in
the original member. Local label numbers are evidence, not proposed pins.

All dependencies already resolve through the normal map: canonical
ArrayUnwind009F6D18, SEH_prolog009F7E88, SEH_epilog009F7EC3, and the newly
admitted canonical except_handler3 provider009F6C50. No additional route pin,
import provider or data object is required by this private byte proof.

Ordinary root transaction:

1. Retract precisely the old `?dup_009F7084@@YAXXZ` 24B library/funclet row at
   0x009F7084 and add its evidence-bearing tombstone, in the same atomic commit
   as the full parent conversion. Its old gen-funclet/object-symbol/parent notes
   are unnecessary once the actual compiler procedure covers the entire102B.
   Use the documented exact-row deletion+tombstone procedure from
   docs/naming_evidence.md60-63 with existing terminator-preserving ledger_io
   primitives. This is not a new Retire CLI or an overlap exemption.
2. Apply the private complete source and run ordinary verification:

   `python3 tools/add_match.py "??__C@YGXPAX0IHP6EX00@ZP6EX0@Z@Z" 0x009F7036 102 game/Libraries/Source/CRT/VS2003/ehvccctr.cpp --replace-existing --model MODEL --notes "Original complete102B ehvccctr.obj iterator including native finally action; original CV and six-argument P6E callback ABI; full ScopeD458A0 and SXdata verified; BFME2 donor147fd3e"`

3. Require ordinary full source, current-object, ledger, pin, identity, import
   and link/provider gates. If any normal guard refuses, preserve its exact
   reason rather than modifying a guard or adding an alias. Do not import the
   private build/ object as a normal current receipt.

There is one real newly authored parent/102B to admit. This member absorbs
exactly24B of existing cleanup coverage. It does not add a second
new task for that child or any new unique ledger bytes. No full-image link,
startup, runtime, memory, crash or performance improvement is claimed here.
