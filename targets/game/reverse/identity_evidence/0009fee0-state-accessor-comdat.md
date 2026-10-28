# State accessor identities and shared COMDAT layout

The old claims `?getID@State@@QBEIXZ` at 0x00106670 and
`?getMachine@State@@QAEPAVStateMachine@@XZ` at 0x00232180 are contradicted
by the frozen exact-name ILT oracle (p_false 0.000326 and 0.000652). Their
four-byte bodies read +8 and +0x20. These claims were copied into the
sweep and turretai StateMachine.h comments as purported retail evidence.
The ZH-derived State declaration has an extra Snapshot base, so those
offsets also happen to agree with its incompatible natural layout.

Independent evidence:
- Matched State constructor 0x000A19E0 places m_ID at +4 and m_machine
  at +0x1c. Its exact-name ILT verdict is CONFIRMED.
- Enumerating the frozen ILT windows for the fixed existing getID spelling
  produces ten compatible targets; only 0x0009FEF0 has `8b4104c3`.
  CONFIRMED p_false=0.00026091948024839533.
- The fixed getMachine spelling produces thirteen compatible targets; only
  0x0009FEE0 has `8b411cc3`. CONFIRMED p_false=0.0007175285706830872.
- The independent layout witness records State::m_machine at +0x1c.
- Both corrected getters compile byte-exact in the existing StateConstructor
  layout. There is no claimed direct-caller identity proof for these getters.
  ILT fits alone are not proof; the constructor and layout distinguish them.

Identity corrections (one body per address):
- 0x00106670: `?getID@State@@QBEIXZ` becomes
  `?get@Rva00106670Dword@@QBEIXZ`, preserving +8 bytes in AITNGuard.cpp.
- 0x00232180: `?getMachine@State@@QAEPAVStateMachine@@XZ` becomes
  `?get@Rva00232180Dword@@QBEIXZ`, preserving +0x20 bytes in Rva00232180Dword.cpp.
- 0x0009FEF0: `?get@Rva0009FEF0Dword@@QBEIXZ` becomes the real getID
  spelling, owned by the existing select-any emitter in AITNGuard.cpp.
- 0x0009FEE0: `?get@Rva0009FEE0Dword@@QBEIXZ` becomes the real getMachine
  spelling, owned by the existing select-any emitter in TurretAI.cpp.

Keep the three header variants otherwise intact: replacing turretai_constructor
with sweep changes unrelated constructor/vtable layout. Correct only these
accessor offsets. The StateMachine::getCurrentStateID symbol
`?getCurrentStateID@StateMachine@@QBEIXZ` at 0x0009FF60 is independently
CONFIRMED and reads currentState+0x1c, then State+4.

Controlled original-source probes cover all eight previously wrong emitters:
AIStates, StateMachine, AIUpdate, AITNGuard, JetAIUpdate, AIGuardRetaliate,
WorkerAIUpdate and HackInternetAIUpdate. Their 280 other matched bodies remain
exact. Only the disputed old getID row changes. TurretAI separately preserves
42 other bodies, changing only its disputed old getMachine row. All nine
emit `8b411c85c074048b4004c3b83f420f00c3`, no relocations, COMDAT ANY(2).

The earlier census reports 19084 affected authored bytes for StateMachine's
getter, with zero sole-blocker bytes. This is diagnostic scope, not a linked
gain. Fresh before/after link validation remains required.

The normal full commit gate passed all 3,403 matched rows across 109 TUs,
including relocation, string/constant/data-reference and body checks.
Supplemental checks cover the identity-dependent sources; AITNGuard passed
13/13 rows, TurretAI 43/43, and the separate opaque getter 1/1. Full COFF
inspection found all 37 State-family definitions byte-exact, with no
relocations and selection ANY(2). This is object-level evidence; measured
linked coverage is reported separately after the census.
