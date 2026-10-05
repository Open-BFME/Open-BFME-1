# TheWeaponStore pointer at VA 0x012EF738

The selected datum is `class WeaponStore *TheWeaponStore`, a single mutable singleton pointer. Its canonical decorated spelling is `?TheWeaponStore@@3PAVWeaponStore@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012EF738-retail.log`. A null initial value contains no initialized target relocation to resolve. Its mutation and address passed to the subsystem registration prove this is a writable datum rather than a compiler constant.

The registration names TheWeaponStore. Retail users resolve weapon templates, create weapons and update the store. The reference declares WeaponStore *TheWeaponStore. The Rva0038DA10System update view and the void pointer declaration in BezierProjectileBehavior are views of the identical pointer, with casts retaining their prior access contracts.

The reference facts that can be checked independently are:

- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h:340: friend class WeaponStore;`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h:567: friend class WeaponStore;`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h:818: class WeaponStore : public SubsystemInterface`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h:886: extern WeaponStore *TheWeaponStore;`

The pointer is defined once in `game/GameEngine/Source/GameLogic/Object/Weapon.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The users now declare the canonical pointer type. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?TheWeaponStore@@3PAVBfmeWeaponStore@@A` | 0 |
| `?TheWeaponStore@@3PAVWeaponStore@@A` | 23 |
| `?g012EF738@@3PAURva0038DA10System@@A` | 1 |
| `?g_bfmeMake1010@@3PAVBfmeMake1010@@A` | 0 |
| `?g_bfmeRegistryAS@@3PAVBfmeRegistryAS@@A` | 0 |
| `?g_bfmeRegistryBN@@3PAVBfmeRegistryBN@@A` | 0 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012EF738-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012EF738-writer.log` preserves the full registration helper and the pointer store through its address. `build/rlink/pointer-globals-1791178372/012EF738-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x00079060 | 0x00479991 | `push 0x12ef738` |
| 0x000BAEC0 | 0x004BAED9 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001C6870 | 0x005C6A2F | `mov ecx, dword ptr [0x12ef738]` |
| 0x001C6870 | 0x005C6A72 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001D5EA0 | 0x005D5EC0 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001E8D10 | 0x005E8D85 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001E9C40 | 0x005E9CB6 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001E9C40 | 0x005E9CE5 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001EA940 | 0x005EA944 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001EA9C0 | 0x005EA9C8 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001EAA40 | 0x005EAA48 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001EAAD0 | 0x005EAAD8 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001EB5C0 | 0x005EB790 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001EBBC0 | 0x005EBC96 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001EBBC0 | 0x005EBCA6 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001F00A0 | 0x005F00F5 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001F00A0 | 0x005F0112 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001F01D0 | 0x005F01EC | `mov ecx, dword ptr [0x12ef738]` |
| 0x001F1860 | 0x005F1A6E | `mov ecx, dword ptr [0x12ef738]` |
| 0x001F1860 | 0x005F1AB4 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001F1CE0 | 0x005F1DC5 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001FB5D0 | 0x005FB68C | `mov ecx, dword ptr [0x12ef738]` |
| 0x001FB5D0 | 0x005FB6B7 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001FB5D0 | 0x005FB6E2 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001FB5D0 | 0x005FB70D | `mov ecx, dword ptr [0x12ef738]` |
| 0x001FB5D0 | 0x005FB738 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001FB5D0 | 0x005FB763 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001FB5D0 | 0x005FB78E | `mov ecx, dword ptr [0x12ef738]` |
| 0x001FB5D0 | 0x005FB7B9 | `mov ecx, dword ptr [0x12ef738]` |
| 0x001FC0B0 | 0x005FC1FD | `mov ecx, dword ptr [0x12ef738]` |
| 0x001FF880 | 0x005FF9A1 | `mov ecx, dword ptr [0x12ef738]` |
| 0x00200DF0 | 0x00600F02 | `mov ecx, dword ptr [0x12ef738]` |
| 0x00201770 | 0x0060179D | `mov ecx, dword ptr [0x12ef738]` |
| 0x002080B0 | 0x006081B3 | `mov ecx, dword ptr [0x12ef738]` |
| 0x002098B0 | 0x006098FD | `mov ecx, dword ptr [0x12ef738]` |
| 0x002143B0 | 0x00614427 | `mov ecx, dword ptr [0x12ef738]` |
| 0x002144D0 | 0x0061454A | `mov ecx, dword ptr [0x12ef738]` |
| 0x00216430 | 0x0061648D | `mov ecx, dword ptr [0x12ef738]` |
| 0x0022DD10 | 0x0062DEE8 | `mov ecx, dword ptr [0x12ef738]` |
| 0x00250BA0 | 0x00650BBD | `mov ecx, dword ptr [0x12ef738]` |
| 0x002579D0 | 0x00657AD8 | `mov ecx, dword ptr [0x12ef738]` |
| 0x002579D0 | 0x00657B8F | `mov ecx, dword ptr [0x12ef738]` |
| 0x002579D0 | 0x00657BAB | `mov ecx, dword ptr [0x12ef738]` |
| 0x0026D670 | 0x0066D6EE | `mov ecx, dword ptr [0x12ef738]` |
| 0x0026D670 | 0x0066D6FD | `mov ecx, dword ptr [0x12ef738]` |
| 0x0028CA70 | 0x0068CA8E | `mov ecx, dword ptr [0x12ef738]` |
| 0x00292CF0 | 0x00692D60 | `mov ecx, dword ptr [0x12ef738]` |
| 0x00292E00 | 0x00692E19 | `mov ecx, dword ptr [0x12ef738]` |
| 0x002AF840 | 0x006AF8D8 | `mov ecx, dword ptr [0x12ef738]` |
| 0x002AF840 | 0x006AF98F | `mov ecx, dword ptr [0x12ef738]` |
| 0x002B0010 | 0x006B00C3 | `mov ecx, dword ptr [0x12ef738]` |
| 0x002DAE80 | 0x006DAE99 | `mov ecx, dword ptr [0x12ef738]` |
| 0x002DE300 | 0x006DE319 | `mov ecx, dword ptr [0x12ef738]` |
| 0x002E6650 | 0x006E66B8 | `mov ecx, dword ptr [0x12ef738]` |
| 0x002E6650 | 0x006E66CB | `mov ecx, dword ptr [0x12ef738]` |
| 0x0038DA10 | 0x0078E149 | `mov ecx, dword ptr [0x12ef738]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.
