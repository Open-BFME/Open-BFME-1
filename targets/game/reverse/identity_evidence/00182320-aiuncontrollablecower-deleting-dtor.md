# 0x00182320 is AIUncontrollableCower's scalar deleting destructor

Two AI state classes pass the literal "AICowerState" (0x01098460) to State's
constructor:

| Constructor | Installs vtable | Extra member | Slot 2 (class-name getter) returns |
|---|---|---|---|
| 0x00171930 (46 B) | 0x01098408 | none | "AICowerState" (0x00171970) |
| 0x001744C0 (50 B) | 0x010991D0 | byte +0x24 = 1 | "AIUncontrollableCower" (0x00174500) |

In every AI state vtable, slot 2 returns the class's own name literal. Seven pinned
tables were checked, for example AIAttackAreaState 0x01098398 -> "AIAttackAreaState"
and AIAttackMeleeEngageState 0x01099848 -> "AIAttackMeleeEngageState". So 0x01098408 is
AICowerState's table and 0x010991D0 is AIUncontrollableCower's. The shared State name
fits AIUncontrollableCower deriving from AICowerState, which is how
AIStateMachineConstructor.cpp already declares the two classes. Its stores of both
tables name them that way. BackAwayAndCowerStateMachine (0x00182190) also installs
0x01098408.

The pins disagreed with that code. They put `??_7AICowerState@@6B@` at 0x010991D0 and
used "constructor 0x001744C0" plus the literal as evidence. The literal is inherited,
so it cannot tell the two classes apart. The same reading named slot 0's scalar
deleting destructor 0x00182320 `??_GAICowerState@@MAEPAXI@Z` and its callee ILT
0x00007E0A `??1AICowerState@@MAE@XZ`.

Corrected:
- The row at 0x00182320 is `??_GAIUncontrollableCower@@MAEPAXI@Z`.
- The destructor pin at 0x00007E0A is `??1AIUncontrollableCower@@MAE@XZ`.
- `??_7AICowerState@@6B@` points at 0x01098408.
- The `??_GAICowerState` pin at ILT 0x0000C38D is dropped. The ledger row already
  supplies that thunk, and nothing calls it.

AICowerState's own table sends slot 0 to 0x001803E0, the generated
`??_GGen_dtor_001803e0@@UAEPAXI@Z`. That row is not renamed here.
