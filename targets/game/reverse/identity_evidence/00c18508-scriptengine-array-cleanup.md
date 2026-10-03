# RVA 0x00C18508: ScriptEngine array cleanup

Matched ScriptEngine constructor 0x00347E60 pushes handler 0x00C18615,
which loads FuncInfo 0x00E086DC. State 10 -> 9 selects action 0x00C18508.
Its unchanged native source emits $L18315 at compiler state 10 -> 9.
The action invokes the EH vector destructor iterator for 256 elements
of stride 16 at saved this + 0x1607C. RET 0x00C18522 proves 27 bytes
before the next independent action. Ghidra confirms these arguments.

The destructor callback is independently identified, rather than accepted
because relocation-masked bytes match. The already-matched constructor
has a DIR32 operand at +0x1B5 naming ??1AttackPriorityInfo@@UAE@XZ and
retail gives it VA 0x004268F5. The cleanup's +1 operand names the same
symbol and uses the same address. ILT RVA 0x000268F5 jumps to 0x0034E2E0,
currently ledgered under the opaque destructor owner Rva0034E2E0.

The Zero Hour twin is in GeneralsMD/Code/GameEngine/Source/GameLogic/
ScriptEngine/ScriptEngine.cpp (AttackPriorityInfo destructor): delete the
priority map if present, then clear it; its header supplies the inherited
Snapshot, AsciiString name, default priority and map fields. The existing
native BFME destructor at 0x0034E2E0 has exactly that member teardown.
This provides an independent twin and matched caller for the callback;
this change does not add another destructor row, pin or alias.

Both parent and action pass the scoped byte gate. The DIR32 check agrees
between their two references (the callback is not yet in the recorded
DIR32 census). Ownership is from EH metadata, not adjacency; no synthetic
standalone frame or source edits are introduced.
