# Contester machine identity evidence and blocked migration

## Native evidence

Verified against retail BFME 1.03 unpacked `lotrbfme.exe`, SHA-256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Addresses below are RVAs unless explicitly called VA; image base is `0x00400000`.
The critical routes were re-read through the actual readonly PyGhidra MCP
stdio tools and compared with direct PE bytes on 2026-10-04.

* Factory `0x00184110`, case 4, allocates `0x44` bytes and constructs the
  by-value string `AIAttackContesterMachine` (VA `0x0109B2C0`). Its call at
  `0x00184245` goes through ILT `0x000349DC` to constructor `0x00171B40`.
* Constructor `0x00171B40` is 413 bytes, ending in `ret 0x0C`. At +`0x52`
  it writes vtable VA `0x01097310`. Vtable slot +8 contains VA `0x0043533C`,
  an ILT to `0x0016AC50`. The getter bytes `B8 5C 73 09 01 C3` return
  VA `0x0109735C`, the literal `AttackContesterStateMachine`.
* Vtable slot zero contains VA `0x0040131B`, an ILT to scalar-deleting
  destructor `0x0016E630` (30 bytes; `ret 4`). Its +3 call reaches ILT
  `0x0001BD65`, whose bytes `E9 D6 EE 14 00` route to complete destructor
  `0x0016AC40` (11 bytes). That complete destructor writes the same vtable
  VA `0x01097310` and tail-jumps through `0x00031D5E` to StateMachine's
  destructor `0x000A1130`.
* Independent Horde contrast: factory case 5 uses `AIHordeMachine`, allocates
  `0x44`, and calls ILT `0x000268DC` to constructor `0x001812B0` (767 bytes).
  That constructor writes VA `0x01097238`. Slot +8 routes through
  `0x0001BEDC` to getter `0x0016ABB0`, whose bytes `B8 84 72 09 01 C3`
  return the actual `AttackHordeStateMachine` literal at VA `0x01097284`.
  Its separate scalar/complete destructor routes are `0x0016E5D0` and
  `0x0016ABA0`. This patch does not rename that distinct class.

The old Horde constructor and scalar-dtor ledger identities at `0x00171B40`
and `0x0016E630` are therefore false, independently of their existing names.

## Evidence-only result

This change records decisive identity evidence and a blocked migration plan.
It changes no source, ledger identity, pin, baseline, resolver, compiler helper,
or native provider. The existing false Horde claims remain implementation debt;
this report does not endorse them. Zero new matched or linked bytes are claimed.

Current relevant spellings are:

* Constructor ledger: `??0AttackHordeStateMachine@@QAE@PAVObject@@PAVAIAttackState@@VAsciiString@@@Z`
  at `0x00171B40`, with object-symbol mapping to the address-qualified
  `Rva00171B40AttackHordeStateMachine` constructor.
* Factory: opaque `AttackHordeStateMachine`, size `0x44`, declaring the above
  constructor. That spelling does not have a native emitted provider.
* Scalar wrapper: `??_GAttackHordeStateMachine@@UAEPAXI@Z` at `0x0016E630`;
  its source macro also emits a complete destructor under the same false class.
* Complete-dtor pin: `??1AttackHordeStateMachine@@UAE@XZ` at ILT `0x0001BD65`.
* Vtable pin: `??_7AttackHordeStateMachine@@6B@` at VA `0x01097310`.
* The sole complete-dtor ledger provider at `0x0016AC40` is already clean C++:
  `??1Rva0016AC40TailDtor@@UAE@XZ` in `Common/VptrTailJumpDestructors.cpp`.
  A future repair must reconcile that provider, not add a second real identity.

## Why a caller-only rename is unsafe

The factory currently models its callee as an opaque `0x44`-byte object; the
constructor's TU-local StateMachine base is only a one-vptr shell. Giving those
incompatible definitions the same compiler symbol would hide a layout problem.
The sweep `Common/StateMachine.h` is also unsuitable: its two-argument ctor and
two-vptr inheritance differ from the native three-argument ctor.

The separately exact base constructor `0x000A1BD0` proves one vptr, a 12-byte
STLport map beginning +4, owner +`0x10`, trailing flags +`0x40/+0x41/+0x42`,
`sizeof 0x44`, and `(Object*, AsciiString, bool)` with by-value string cleanup.
That data layout alone does not recover the full virtual contract. Native
Contester has 16 nonzero slots, followed by zero padding:

| Vtable offset | Resolved body RVA |
|---|---|
| 00 | 0016E630 |
| 04 | 000A1290 |
| 08 | 0016AC50 |
| 0C | 0016AC10 |
| 10 | 000A0760 |
| 14 | 0009FFF0 |
| 18 | 000A1CF0 |
| 1C | 000A1460 |
| 20 | 000A1D60 |
| 24 | 000A1250 |
| 28 | 000A1260 |
| 2C | 000A1270 |
| 30 | 000A0040 |
| 34 | 000A0080 |
| 38 | 000A0C40 |
| 3C | 000A00A0 |

The base vtable at VA `0x01080710` differs at slots 00, 08 and 0C, which resolve
to `0x000A1CC0`, `0x000A12A0`, and `0x000A1510` respectively. A shared native
migration must establish these method signatures, inherited/override ownership,
and actual selected providers; a one-destructor table is not a complete runtime
class. That work is intentionally not papered over with aliases, dummy virtuals,
new pins, casts, or a duplicate complete destructor in this correction.

## Linking measurement boundary

The supported fresh two-source preview uses the immutable historical census
from commit `1677ebdc33b984da91173ad45707c94e4fbb7bed`, dated
2026-10-03 17:32. Index SHA-256:
`034ebdbd7f13546b5fd7f5f79240e5d75e973fabcc4bad425a0f4ee9dd0d9573`.
The unchanged factory remains blocked by its existing false Horde constructor spelling. Its potential
future direct-caller value is 510 non-0xCC bytes, within a 516-byte extent;
that is already-matched code, not new coverage. The 409-byte constructor provider
separately remains blocked by State destructor and selected State constructor /
StateMachine destructor providers. No index provenance or selection rule changes.

## Rejected identity-only prototype and exact guard diagnostics

A local, unlanded prototype demoted the constructor/scalar ledger claims to
address-only rows with unchanged object-symbol mappings. Removing the old
constructor ledger name also removed the factory byte verifier's REL32 name
resolution. A distinct address-qualified opaque factory call-contract view was
therefore considered; it deliberately did not unify the provider's incompatible
type view. Its original ILT was independently decoded, not inferred from a match.

The attempted routing pins were:

* `??0Rva00171B40FactoryMachine@@QAE@PAVObject@@PAVAIAttackState@@VAsciiString@@@Z`
  at `0x000349DC`, with `route=0x00171B40`.
* Existing legacy `??1AttackHordeStateMachine@@UAE@XZ` at `0x0001BD65`,
  annotated with `route=0x0016AC40`.

`python3 tools/pin_consistency.py --check` rejected both:

> Route pins: FAIL 2 inadmissible route= row(s) in targets/game/reverse/symbols.csv
>
> 0x000349DC jumps to 0x00171B40, which the ledger names nothing -- not
> ??0Rva00171B40FactoryMachine@@QAE@PAVObject@@PAVAIAttackState@@VAsciiString@@@Z
>
> 0x0001BD65 jumps to 0x0016AC40, which the ledger names
> ??1Rva0016AC40TailDtor@@UAE@XZ -- not ??1AttackHordeStateMachine@@UAE@XZ

The guard's `route=` exemption requires the jump target's matched ledger row
to name the identical typed symbol. An address-only body/object-symbol mapping
is intentionally not such a canonical identity proof. Moving a disputed name
onto the direct body would assert an identity rather than establish routing;
it does not resolve the structural problem. No representation change, alias,
new exception, or relaxed checker was accepted as a workaround. All prototype
source/ledger/pin changes were reverted; only this evidence is proposed to land.

The prototype's scoped byte check passed 74/74 rows across the factory,
constructor, six scalar wrappers and tail-destructor TU. That did not override
the failed pin guard and is not an approved implementation result. Existing
constructor and scalar helpers were not reimplemented; no shared header was
introduced. The original matching providers and all other destructor siblings
remain untouched.

## Bounded next steps

1. Recover a coherent native StateMachine declaration from the proven data layout
   and all 16 virtual slots. Establish each signature and actual selected provider
   independently; do not manufacture dummy virtuals or assume current names.
2. Share a Contester declaration between its constructor, factory and scalar-
   deleting destructor while preserving the three-argument/by-value-string ABI,
   protected base destructor, and public derived scalar wrapper.
3. Reconcile the existing `0x0016AC40` complete-dtor emitter as a single provider.
   Merely adding another class destructor to satisfy the scalar wrapper is not
   acceptable. Re-evaluate all emitted helper symbols, including destructor
   force-emission code that currently relies on default construction.
4. Verify every affected sibling and outgoing symbol-loss selector, pin
   consistency, one-identity/name checks, and the shared-header full gate.
   Preserve historical index provenance and report the still-unresolved provider
   dependencies separately from any eventual 510-byte direct-caller gain.
5. Independently audit the native slot `+0x3C` body `0x000A00A0`: the 16-slot
   contract investigation found a 12-byte halt body against a 4-byte claim.
   That extent issue is separate from this evidence-only identity report and
   must be repaired under its own complete boundary and call-site evidence.
