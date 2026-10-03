# Three unresolved referenced-name contradictions

Reviewed7bfaf884e4 complete-string verification rejects these current
source literals against the retail operands. The fresh-object checkpoint
ran on frozen aaf68fc977; the current source declarations retain these same
literals. These are positive referenced-byte failures, not merely absent
name evidence. Full source/owner/caller reconciliation remains pending;
changing only the string could preserve a wrong semantic identity.

| RVA / extent | Existing row | Operand / VA | Source string | Retail string |
| --- | --- | --- | --- | --- |
| 0x00359EE0 / 204 | `?WriteScriptDataChunk@@YAXAAVDataChunkOutput@@PAVScriptList@@PAVScript@@@Z` | +88 / 0x10e8478 | `Script` | `ScriptGroup` |
| 0x002A6520 / 104 | `?getClassMemoryPool@SpecialAbility@@CAPAVMemoryPool@@XZ` | +49 / 0x109025c | `SpecialAbility` | `SpecialAbilityUpdate` |
| 0x002B2B30 / 104 | `?getClassMemoryPool@Weapon@@CAPAVMemoryPool@@XZ` | +49 / 0x1090424 | `Weapon` | `WeaponModeSpecialPowerUpdate` |

The104B pool bodies return at002A6587/002B2B97; the204B chunk writer
returns at00359FAB. Each is followed by INT3; complete compiled-boundary
checks passed on the checkpoint objects. The pool bodies both call
ILT0003ADD7 ->0008FFC0. The chunk writer recursively calls its own
ILT00002310 and separately calls000285D3 ->00357B30. These paths are
leads for independent ownership/ABI proof, not authority for a new name.

Keep these three claims unchanged until the owner/callee relationships are
proved or an honest opaque repair is ready. Do not weaken the literal
checker or treat old prefix-matching success as evidence. No baseline growth,
new pin, semantic rename or production source change accompanies this note.
