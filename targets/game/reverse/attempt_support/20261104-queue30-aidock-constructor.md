# AIDockMachine provider: remove the obsolete constructor, retain its helpers

Queue57 claim F48C7B60. The retail constructor at0014F7C0 is826 bytes and
already byte-proven in AIDockMachineCtor.cpp. AIDock.cpp still defined the
old Zero Hour constructor, using a different StateMachine ABI and class
layouts. The queued AIDockState_xfer.cpp is declaration-only and needs the
existing native provider. Remove only that wrong constructor.

The previous removal failed8 of29 AIDock.cpp rows because the constructor
was the only use forcing8 existing placement-delete COMDATs to be emitted.
Their signatures,12-byte bodies and shared target007EFFF0 already belong
to AIDock.cpp in the ledger. Change the TU-local pool macro's placement
delete body into its same declaration, then define those8 actual methods
out of line in this TU with the same BfmePoolGlue::free call. This keeps the
already-verified providers independently of an unrelated wrong constructor.
No new function identity, address, pin, data anchor or class layout is added.
A preliminary typed-address-anchor trial also passed, but was discarded;
the final source has8 ordinary definitions and no emission-only globals.

Normal gate:44/44 rows across AIDock.cpp, AIDockMachineCtor.cpp and
AIDockState_xfer.cpp;20 DIR32 and11 literal references pass. This includes
all8 placement deletes, the entire826-byte native constructor, its existing
cleanup actions and the218-byte consumer. COFF inspection confirms no ctor
definition in AIDock.obj, the ctor definition in AIDockMachineCtor.obj,
and8 placement-delete definitions in AIDock.obj. Existing same-named state
views in the native ctor/deleting-wrapper units do not declare pool glue.

Target identity/boundary evidence is unchanged: matched state callers route
ILT00014F15 to0014F7C0; constructor vtable01095A38,826-byte complete extent,
and existing state-family source establish the native constructor.
callees.py0014F7C0/826 witnesses the native StateMachine constructors,
state definitions and eight plain-new sites. Nothing from the obsolete
constructor is needed to establish its identity.

Donor reviewed a9286edec5374324e40c1f5dd29c3a8ab5582283:
Code/GameEngine/Source/GameLogic/AI/AIDock.cpp and AIDockXfer.cpp. BFME2's
constructor also registers eight native states but uses a hashed name-key
StateMachine ABI and different size/layout context. Those differences
rule out copying its constructor or flags. This repair derives from existing
BFME1 providers/helper definitions; no donor code/addresses/includes imported.

Before link_check on xfer: non-retail selected AIDockMachine ctor. After:
current selection unknown against stale Oct19 census, no linked-byte gain.
