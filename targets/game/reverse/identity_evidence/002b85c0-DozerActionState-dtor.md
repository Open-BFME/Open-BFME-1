# 0x002B85C0 is ??1DozerActionState@@UAE@XZ

The 94-byte body at RVA 0x002B85C0, matched under the address-derived placeholder `??1Rva002B85C0@@UAE@XZ` (R4OwnedPointerDestructors.cpp), is DozerActionState's complete destructor.

Evidence:
- The matched `??_GDozerActionState@@UAEPAXI@Z` at 0x002B8590 (slot zero of vtable 0x00CC6F70, whose slots name DozerActionState) calls ILT 0x00030B52, which jumps to 0x002B85C0. symbols.csv already pins `??1DozerActionState@@UAE@XZ` at that ILT.
- `python3 tools/ilt_oracle.py check '??1DozerActionState@@UAE@XZ' 0x002B85C0` prints CONFIRMED (exact, p_false=9.78e-04); the MAE spelling is CONTRADICTED.
- The body stores vftable VA 0x010C6F70 (RVA 0x00CC6F70), recorded in dir32_addresses.csv as `??_7DozerActionState@@6B@`; the duplicate placeholder record `??_7Rva002B85C0@@6B@` for the same VA is deleted.
- The body deletes the owned pointer at +0x24 and calls the State base destructor, matching the upstream `DozerActionState::~DozerActionState() { if (m_actionMachine) m_actionMachine->deleteInstance(); }` with m_actionMachine after m_task.

The correction preserves the start, extent, instructions and relocation targets.
