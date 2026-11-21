# Independent B1 ti_inst review

**Boundedly positive for native identity, ABI, three code bodies and97B original
RTTI. Normal admission and complete provider/link closure are still pending.**
No compiler, production/Git/claim/index/baseline write by this reviewer.

REVIEW-NATIVE.json comes from directly reading the original and already produced
candidate COFFs, not just accepting the author's comparison report. Original
member SHA256a03833b45869b6b2396e8e44c3ebccc59af1c18d1bae29cb42cd24da8768c0ba;
candidate553dc5d5819a92bc09cd2634347a660d85c1d23166e15b1fdecc2a7f13f0840f.
Only the original binary/CodeView and allowed public SDK header were read;
no Microsoft CRT implementation source was consulted.

## Original type and assignment identity

The original complete type_info CodeView class is12B, no base, one virtual
destructor slot, data pointer+4 and char[1]+8. The candidate preserves that
contract and every public SDK method/access role. The original member contains
the complete11B private copy constructor and75B vector deleting destructor with
thiscall type records/this-adjust0. Both candidate bodies and all relocations
match the original COFF exactly.

The original assignment procedure record really has type_index0. Do not present
that missing record as a recovered CodeView function prototype. Independent
evidence is nevertheless strong: actual original external COFF code symbol
`??4type_info@@AAEAAV0@ABV0@@Z`, public toolchain SDK private declaration
`type_info& operator=(const type_info&)`, and the complete original5B
`8bc1c20400` (return ECX in EAX, pop one argument). The candidate's return*this
matches it exactly and performs no field copy. No guessed second name or alias
is needed. Normal unrowed-boundary/identity admission remains Root's job.

The97B original physical RTTI graph is preserved, including the anonymous4B
COL-pointer prefix before the named vtable at section+4, the20B COL,24B
TypeDescriptor,16B CHD,5B BaseClassArray and24B BCD. Data bytes, section flags,
pointer names/relocation types and the vtable's vector-dtor target agree. Do not
trim the original5B BaseClassArray to an assumed4B shape or invent a second
address-named prefix global.

## Emission adapters and actual extra definitions

The default argument and `if(0) new type_info[2]` are disclosed TU-local compiler
emission adapters from the authored donor, not original source/API evidence.
The actual copy constructor has no new allocation or helper call: it is the
original11B vptr-only body. The false branch executes no array allocation.
The constructor's parameter count/mangled ABI, layout, vslots and assignment ABI
are unchanged. Adding a default changes source-level default-constructibility
inside this private implementation context, so do not put this declaration in a
shared consumer header or claim exact source/API equivalence.

The candidate object is **not whole-object identical** to the original member:

- New11B compiler default-argument closure `??_Ftype_info@@QAEXXZ` contains
  `push offset ??_R0H@8; call copy-constructor; ret`.
- New11B primitive int TypeDescriptor `??_R0H@8` references the type_info vtable.

The closure has no incoming relocation in this object; the int descriptor has
one incoming relocation from that closure. These are local graph observations,
not global deadness proof. The int descriptor is already pinned in B1 at
RVA00EC83B0, and real catchable type00E4549C points to it. Independently relocating
the candidate's full11 bytes gives`68581401000000002e4800`, exactly that original
descriptor. Transport has separately found a current CaseOps equal-data copy;
this reviewer does not turn that into a globally current selected-provider or
actual-link claim. Preserve visibility/selection in the final footprint and
check incoming references from the entire kept population normally.

## Native gate behavior and remaining prerequisites

The actual B1 find_declared_unmatched lexical reader finds only two explicit
source definitions: type_info::type_info and type_info::operator=. It does not
invent an unclaimed source body for compiler `_F` or a data object. Until the
new11B/5B functions are normally banked and the75B library owner is normally
replaced, this is not a claimed production FDU pass.

Native body_guard.row_findings checks row extents/tails, same-section targets
and TU-local data reached by that row. It has no special `_F` or primitive-RTTI
whitelist, and no global extra-definition/reference inventory. Its lack of
findings cannot establish that these extra COMDATs are dead or correctly
selected. The independent full original data graph and ordinary data/provider/
link checks remain necessary; no baseline or marker should hide the extras.

The75B body uses the independently proved CODE destructor thunk009F7ED4, not its
IAT cell directly. Current native route metadata still rejects the old generated
row's display target`~type_info` against the actual DLL symbol. Private exact
bytes do not fix this: Root must perform ordinary sanctioned metadata/route
admission and preserve the actual thunk/source bytes. Scalar delete/iterator
providers must remain current and correct.

Transport reports its native NOENTRY control itself stops at missing uuid.lib.
That is an unresolved setup/closure boundary, not evidence the candidate links
or evidence of a candidate-specific regression; do not silence it with
NODEFAULTLIB, custom stubs or a whitelist. No new body/task credit is approved
by this independent review.
