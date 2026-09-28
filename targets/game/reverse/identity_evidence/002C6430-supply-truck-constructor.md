# SupplyTruckStateMachine constructor: RVA 0x002C6430

The 1153-byte range ends at VA 0x006C68B1, immediately after `ret 4` at
0x006C68AE. The prior lift named a by-value AsciiString argument that does not
exist. The corrected identity is `??0SupplyTruckStateMachine@@QAE@PAVObject@@@Z`.

## Independent identity and ABI evidence

- The Zero Hour SupplyTruckAIUpdate.cpp constructor takes only Object* and
  constructs the literal "SupplyTruckStateMachine" itself.
- The retail body does the same: at 0x006C6457 it pushes string VA 0x010C92CC;
  after its StringBase<char> constructor call it pushes the sole incoming
  owner argument and calls ILT 0x0000F123 -> StateMachine at RVA 0x000A1BD0.
  The extra false argument is for the BFME base constructor, not this body.
- WorkerAIUpdate::createMachines constructs SupplyTruckStateMachine(owner).
  Its established one-argument constructor pin is ILT RVA 0x00047C80, which
  jumps to this body. The other caller is SupplyTruckAIUpdate's constructor.
- This body installs vtable VA 0x010C9280, also installed by destructor RVA
  0x002C59E0. The native state constructors install their individual vtables
  and carry the matching class string literals.

## BFME differences from Zero Hour

Six states are allocated with size 0x24: SupplyTruckBusyState (ID 1),
SupplyTruckIdleState (0), SupplyTruckWantsToPickUpOrDeliverBoxesState (2),
RegroupingState (3), DockingState (4), and BFME-only HarvestingState (5).
Their vtables respectively are 0x010C94C8, 0x010C9538, 0x010C9308,
0x010C9390, 0x010C93F8, and 0x010C9460. The constructor strings independently
identify all six. Harvesting shares dockingConditions. Regrouping's transition
list differs from Zero Hour; the source reproduces the retail table.

Condition pointer routes in retail:

| Pointer VA | Body RVA | Evidence |
| --- | --- | --- |
| 0x00425C7A | 0x002C5C10 | ownerIdle: State+0x1c -> machine+0x10 -> Object+0x204 then idle predicate |
| 0x00421909 | 0x002C5BB0 | already matched SupplyTruckStateMachine::ownerDocking |
| 0x004032DD | 0x002C5BE0 | same owner chain then AI state comparison to 0x2f; address-derived condition name retained |
| 0x0041C445 | 0x002C5B70 | supply interface forced-busy predicate; Zero Hour condition position agrees |
| 0x00431C87 | 0x002C5B30 | supply interface forced-wanting predicate; Zero Hour condition position agrees |
| 0x0040C5E0 | 0x002C5CA0 | not idle and AI state neither docking (14) nor harvesting (47) |
| 0x0043D42E | 0x002C5C40 | supply interface available predicate and AI idle predicate |

The five local static tables and compiler guard are native C++ initialization,
not manually reproduced stores. Calls use established State, StateMachine,
defineState and operator-new declarations. No new callee pins are required.

The dedicated class-home TU follows AIStateMachineConstructor.cpp's BFME
constructor/layout views, because SupplyTruckAIUpdate.cpp includes Zero Hour
headers with incompatible State and StateMachine layouts and base signature.
No shared header change is needed. The existing ascii_string.h provides native
StringBase forwarding and temporary lifetime behavior.

## Validation

Initial scoped probe: 1153 bytes, 131 relocations, EXACT outside relocation
slots. Required EH lever search stopped at unchanged trial zero with an exact
masked shape. Final add_match and source build validate calls, string constants
and DIR32 consistency; see build/astra_seat/REPORT.md for their outcome.
