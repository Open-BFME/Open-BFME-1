# Lua script paths at RVA 0x002ECF40

The reconstruction is `LuaScriptEngine::rva002ECF40(const AsciiString &)`, with an address-derived method name. Its complete 454-byte body matches retail at revision `b4dbdc1abaea773c77e26e3a0dd5d4f7ce03f969`. The original EA method name remains unknown. This recovery replaces the generated dump without asserting that name.

## New evidence and falsification

Earlier attempts had no saved body and treated unidentified helpers or an unknown method name as blockers. The current ledger supplies authored C++ for registration at 0x002EC990, file loading at 0x002E55C0, token-file parsing at 0x002EC840 and the save-directory test at 0x0010F1E0. Their actual decoded bodies agree with the declarations used here. The new hypothesis was that these declarations and the canonical string header permit a complete reconstruction, including the conditionally constructed string temporary. A different receiver adjustment, argument cleanup, buffer-header access or unwind action would refute it.

## Boundary, receiver and arguments

The target begins after `int3` padding and ends with `ret 4` at 0x002ED103, followed by padding from 0x002ED106. Its only return path is the shared epilogue at target offset 0x1B0. All conditional branches and local jumps remain within the extent. The one argument is a pointer to an existing string object, read first at `[ebp+8]`; there is no hidden result storage. Every receiver call uses the original `ecx` without adjustment. The caller consumes no scalar result.

The complete 7643-byte caller at 0x00394260 contains the aligned call at 0x00394773. It pushes the address of the string at the writable GlobalData singleton plus 8, loads the receiver from VA 0x012F060C, and calls ILT 0x00022697. That five-byte thunk jumps to this target. The existing `initSubsystem<LuaScriptEngine>` registration at 0x00074ED0 identifies the singleton. Independently, the complete constructor at 0x002EB4A0 installs vtable VA 0x010CFAC4 and zeros receiver offset 8. Vtable slot 10 resolves through ILT 0x00036255 to the complete six-byte getter at 0x002EB5B0, which returns the literal `LuaScriptEngine`. The decoded registration helper operates on its Lua state at receiver offset 8 and uses the Lua APIs. No field layout of the whole LuaScriptEngine is re-created in the new source.

## String and GameState evidence

The argument is a four-byte string buffer pointer. The target reads the buffer's unsigned 16-bit length at offset 4 and its text at offset 8. These are the canonical `StringBase<char>` header fields. The 72-byte C-string constructor at 0x00888BC0 has both return paths decoded, writes the string pointer, and returns with `ret 4`. Its actual allocation helper at 0x008879D0 was decoded over all 388 bytes: it writes the 32-bit reference count at offset 0, the 16-bit capacity at offset 6, the 16-bit length at offset 4, the text and terminator from offset 8, and the owning pointer in the string object. The complete 134-byte release helper at 0x00887940 decrements the buffer reference count, frees the buffer at zero and clears the string pointer.

When the save-directory test succeeds, the target reads the same string representation from GameState offset 0x1C. The landed `GameStateSetPristineMapName.cpp` body at 0x00387960 writes the narrow string at that offset. Its complete 75-byte decode and the Zero Hour `GameState.h` setter identify `m_pristineMapName`. The new source uses an address-derived partial view containing only that witnessed field. It does not infer an inline pristine-map getter from the existing by-value getter pin.

## Calls and exception cleanup

Complete decodes and checked callee inventories were retained for the target, caller, registration helper, Lua file loader, token-file parser, save-directory predicate, string constructor, string release helper and file-existence predicate. The registration helper's outgoing tail jump resolves through ILT 0x0002788B to 0x002E3360. File-existence results are tested in `al`; its virtual calls use archive slot 0x20 and local slot 0x10. Lua file loading takes one character pointer and returns with `ret 4`. Token-file parsing takes the character pointer followed by a Boolean stack argument, reads the Boolean byte, and returns with `ret 8`. The target's `sprintf` import uses the canonical CRT declaration and cdecl cleanup.

The target handler at 0x00C15D12 names FuncInfo 0x00E058A8, with exactly one unwind state. State 0 transitions to -1 through the complete 34-byte action at 0x00C15CF0. It tests and clears bit 0 at `[ebp-0x228]`, then destroys the temporary at `[ebp-0x224]`. Its tail jump resolves through 0x0000D828 and `AsciiString::~AsciiString` at 0x0005EE90 to the release helper at 0x00887940. The compiled unwind map has the same one-state transition, and its full 34-byte action matches outside its independently checked destructor relocation, including the conditional return. The temporary is created only on the successful singleton guard and destroyed before the subsequent path work.

## Measured experiments and checks

The initial canonical-header reconstruction emitted 470 bytes and had 315 differing non-relocation bytes. Eight generated EH trials supplied no improvement. Making the witnessed string emptiness check visible emitted 466 bytes with 305 differing bytes. Replacing array aggregate initialization with explicit zeroing emitted exactly 454 bytes with no differing non-relocation bytes. The final source was independently probed at its game path with the same exact result.

The verified `add_match.py` replacement and the scoped byte gate passed, including source claims, literal references, recorded DIR32 targets and the body guard. `find_declared_unmatched.py`, `class_gate.py` and `pin_consistency.py --check` passed. No symbols, shared headers or STL rows changed. The final `check_csv.py` reports only that the new source is untracked; staging it requires coordinator collection because this worker's Git index is read-only.

Raw probes, complete decodes, checked inventories, EH comparison and gate logs are retained under `build/lua-002ecf40/`. The final receipts are `probe-final.log`, `add_match.log`, `scoped-gate-bash.log`, `eh-final-full.log`, `find_declared_unmatched.log`, `class_gate.log`, `pin_consistency.log` and `check_csv.final.log`.
