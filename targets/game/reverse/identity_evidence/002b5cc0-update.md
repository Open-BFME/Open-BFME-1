# DeployStyleAIUpdate::update at RVA 0x002B5CC0

The recovered body is `?update@DeployStyleAIUpdate@@UAE?AW4UpdateSleepTime@@XZ`. The independent owner evidence is the matched constructor at 0x002B5510: it installs vtable VA 0x010C63DC at primary offset 0x10, whose slot zero points through ILT 0x00010618 to this body. The constructor's module-data and pool identities name DeployStyleAIUpdate. The decoded body receives that secondary interface, reads the owning Object at receiver minus 8, and calls primary-interface methods with receiver minus 0x10. Its niladic RET returns a signed 32-bit sleep value in EAX. There is no hidden return buffer.

The earlier attempts used the Zero Hour update strategy. The new hypothesis was that the landed BFME state transition and command declarations, together with the older Generals attack-target algorithm, describe the additional retail paths. The hypothesis would be refuted by different decoded target selection, state transitions, receiver offsets, command ownership or cleanup. The GeneralsMD update was inspected first; its state-machine strategy differs. The Generals update was then compared against the complete retail instructions rather than accepted as a donor identity. BFME constructs the restored command with AICMD_NO_COMMAND, uses the five-argument goal-position range test with a float zero, and has the witnessed BFME offsets below.

## Boundary and control flow

The code occupies 0x43C bytes, including the only RET at offset 0x43B. All direct conditional branches and direct jumps terminate at decoded instruction starts inside that code. Two five-entry switch tables occupy offsets 0x43C through 0x463. Their destinations, relative to the body, are respectively `(0x22F, 0x353, 0x255, 0x3A2, 0x3B7)` and `(0x3F2, 0x3F9, 0x3F2, 0x3F9, 0x407)`. Twelve INT3 bytes follow the tables. The claimed extent is therefore 1124 bytes. The probe's warning about decoding offset 0x462 as an instruction is caused by interpreting the second table as code; the table entries and their indirect-jump references were checked explicitly.

The checked callee inventory succeeds over the complete 1084-byte code extent. Running it over the ledger extent rejects the embedded tables, so those tables are validated separately. There are no outgoing conditional branches or direct tail jumps in the target. The normal return path restores the EH registration and returns without removing stack arguments.

## Layout and indirect calls

Primary offsets 0x340, 0x3E0, 0x3E4 and 0x3E8 are the stored command, its presence byte, the deploy state and the wake frame. They agree with the independently landed constructor, aiDoCommand and setMyState. Target IDs are at 0x3EC and 0x3F0, the position is at 0x3F4, and the five attack-mode bytes occupy 0x400 through 0x404. AIUpdateInterface's state-machine pointer, path and path-wait byte are at 0x30, 0x140 and 0x31E. The module-data byte read at 0x6E is `m_turretsMustCenterBeforePacking`, as confirmed by the field-name oracle. Object+0x344 is the canonical `m_privateStatus` field; bit zero is the effectively-dead test witnessed in the target and the turret helper.

The inlined ALIGNING_TURRETS transition calls Object vtable slot 0x28 with the Object receiver and no stack arguments. The matched state-transition source and Object declarations identify this as getDrawable; its pointer result is unused here. Restoring the outside command calls secondary AICommandInterface slot zero at primary plus 0x20 with one pointer argument. The matched aiDoCommand body at 0x002B5600 receives exactly that subobject and returns with RET 4. No indirect call uses a guessed receiver adjustment.

## Direct callee contracts

Each extent below was decoded completely, and its checked inventory was retained under `build/target-002B5CC0/`. Stack-byte counts exclude the receiver and return address. Return widths were checked on all return paths. Existing names are bindings rather than independent identity proof.

| Final RVA | Extent | Contract used by this body |
|---|---:|---|
| 0x001BE230 | 47 | Object receiver; optional weapon-slot pointer; RET 4; weapon pointer in EAX. |
| 0x001E6930 | 597 | Weapon receiver; source, source position, target, target position and float extension in that order; RET 20; Bool in AL. The fifth slot is consumed by FLD and FMUL, not integer conversion. |
| 0x0009A510 | 82 | GameLogic receiver; integer object ID; RET 4; Object pointer in EAX. Lookup compares node key at +4 and returns payload at +8. The target dereferences that returned object at +0x344 and +0x74. |
| 0x001E8930 | 46 | Weapon receiver; source, target and integer extension bits; RET 12; Bool in AL. It forwards those bits unchanged into the float slot of 0x001E6930. |
| 0x0026EB70 | 51 | Primary AI receiver; no arguments; signed turret enum in EAX, including -1. |
| 0x0026E960 | 55 | Primary AI receiver; turret index; RET 4; 32-bit result reinterpreted as Object pointer using the existing opaque getResult declaration. |
| 0x000A1490 | 16 | StateMachine receiver; no arguments; tail-calls the object lookup with its ID at +0x20; Object pointer in EAX. |
| 0x00279A50 | 1760 | Primary AI receiver; two Bool stack slots, read as bytes; every return uses RET 8 and returns an Object pointer or zero in EAX. |
| 0x001535A0 | 214 | Secondary command receiver; Object pointer, shot limit and command source; RET 12; result unused. It constructs and dispatches the canonical AICommandParms block. |
| 0x00278830 | 99 | Primary AI receiver; no arguments; Bool in AL. The existing neutral bfmeBlocksFormationRefresh binding is retained; this recovery does not add an isMoving identity claim. |
| 0x0026EA10 | 23 | Primary AI receiver; turret enum; RET 4; result unused. |
| 0x00185910 | 211 | AICommandParms receiver; command enum then source enum; RET 8; receiver returned in EAX. |
| 0x00180710 | 205 | Const stored-command receiver; mutable AICommandParms reference; RET 4; result unused. |
| 0x000D7330 | 65 | Whole AICommandParms receiver; no arguments; destructor frees only the coordinate-vector allocation. |
| 0x002B5800 | 941 code | Primary DeployStyle receiver; deploy-state enum; RET 4; result unused. Its visible source allows only the retail ALIGNING_TURRETS path to inline into update. |
| 0x0026EA60 | 28 | Primary AI receiver; turret enum; RET 4; Bool in AL. |
| 0x000D87E0 | 192 | Secondary command receiver; source enum; RET 4; result unused. |
| 0x0027E5A0 | 843 | Update-interface receiver at primary plus 0x10; no arguments; 32-bit sleep value in EAX. This is reached through the existing update pin at ILT 0x00028772. Its legacy AnimalAI destructor ledger label is not used as identity evidence. |

The turret result's pointer interpretation is independently established by the complete helper at 0x0018C7D0 (129 bytes), reached through ILT 0x0002C746. It writes the Object pointer returned by StateMachine::getGoalObject through its first output argument, dereferences the result at Object+0x344, and writes all three coordinate fields through its second output argument. The outer 0x0026E960 body returns the first output only for target kind 1. Allocation width or the existing getResult name is not the pointer evidence.

## Command payload and exception ownership

The AICommandParms constructor initializes the vector's three pointer words at +0x20, +0x24 and +0x28. Reconstitution copies the stored vector at +0x24 into the live command vector at +0x20 through ILT 0x0002E00F, whose final assignment body is 0x00152530 (280 bytes). All assignment paths were decoded. Its copying and allocation helpers at 0x001504B0 (77 bytes), 0x00150420 (45 bytes) and 0x001508E0 (97 bytes) copy or construct elements through the actual helper reached by ILT 0x0003FDA5, namely 0x000B73B0 (29 bytes). That complete helper reads and writes each word at element offsets 0, 4 and 8, with no fourth payload or padding field. The constructor's empty-range copy helper at 0x000B6BB0 (77 bytes) has the same complete field list. Element iteration advances by 12 bytes.

The independent float-type witness is AICommandParmsStorage::doXfer at 0x00187860 (805 bytes): its vector begins at storage+0x24 and its saving loop at +0x130 loads all three element fields using FLD from offsets 0, 4 and 8, advances by 12 bytes, and passes the complete coordinate to virtual xferCoord3D at slot 0x60. Its loading loop initializes those same three fields and appends the coordinate. This connects the actual copied payload to the canonical Coord3D header without relying on a template pin or allocation size. Reconstitution copies every remaining field of the canonical 0x9C-byte AICommandParms layout; the only owned member is the coordinate vector. The destructor has both large-allocation delete and small-allocation pool-deallocation paths, and neither destroys an additional element resource.

Retail's EH FuncInfo contains seven states. States 0 through 5 have no cleanup; state 6 transitions to -1 and calls AICommandParms::~AICommandParms through ILT 0x00017C2E with ECX equal to EBP minus 0xA8. The candidate object's relocated FuncInfo, unwind map and cleanup were compared independently and have the same states, predecessor values, receiver offset and final destructor target 0x000D7330. The normal destructor call and the cleanup both receive the whole local, rather than an embedded vector or DamageInfo member. The visible setMyState definition preserves the six empty states left by pruned inline paths. Its emitted out-of-line copy also matches retail through the following switch table; the existing setter row is not changed by this recovery.

## Reproduction and refutation

The preserved compiler trials, raw probe outputs, complete target and helper decodes, COFF object, relocation list and structural assertions are under `build/target-002B5CC0/`. The final source must pass the scoped byte gate, including resolved relocations and both switch tables. A different vtable owner, argument cleanup, field offset, vector element read/write, unwind predecessor or cleanup target would refute this recovery even if a masked probe remained exact. No STL ledger row, symbol pin, shared header or unrelated body is changed.
