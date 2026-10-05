# TheTeamFactory pointer at VA 0x012ED810

The selected datum is `class TeamFactory *TheTeamFactory`, a single mutable singleton pointer. Its canonical decorated spelling is `?TheTeamFactory@@3PAVTeamFactory@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012ED810-retail.log`. A null initial value contains no initialized target relocation to resolve. Its mutation and address passed to the subsystem registration prove this is a writable datum rather than a compiler constant.

The registration names TheTeamFactory. Retail callers use this singleton for team prototypes and team state transitions; they pass the loaded pointer in ECX. The reference declares TeamFactory *TheTeamFactory. The Rva002BD630TeamFactory and Glo00EED810 views are callers of that factory, rather than independent objects.

The reference facts that can be checked independently are:

- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h:106: class TeamFactory;`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h:680: class TeamFactory : public SubsystemInterface,`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h:747: extern TeamFactory *TheTeamFactory;`

The pointer is defined once in `game/GameEngine/Source/Common/RTS/Team.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The users now declare the canonical pointer type. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?TheBfmeTeamFactory@@3PAVRva002BD630TeamFactory@@A` | 2 |
| `?TheTeamFactory@@3PAVTeamFactory@@A` | 32 |
| `?g_Glo00EED810@@3PAVGlo00EED810@@A` | 1 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012ED810-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012ED810-writer.log` preserves the full registration helper and the pointer store through its address. `build/rlink/pointer-globals-1791178372/012ED810-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x00079060 | 0x00479F8A | `push 0x12ed810` |
| 0x000CFB50 | 0x004CFBB5 | `mov ecx, dword ptr [0x12ed810]` |
| 0x000DC270 | 0x004DC5D9 | `mov ecx, dword ptr [0x12ed810]` |
| 0x000DC270 | 0x004DC869 | `mov ecx, dword ptr [0x12ed810]` |
| 0x000DF2B0 | 0x004DF2B3 | `mov ecx, dword ptr [0x12ed810]` |
| 0x000E0060 | 0x004E007D | `mov ecx, dword ptr [0x12ed810]` |
| 0x000E0060 | 0x004E0287 | `mov ecx, dword ptr [0x12ed810]` |
| 0x000E0640 | 0x004E065D | `mov ecx, dword ptr [0x12ed810]` |
| 0x000E0640 | 0x004E0889 | `mov ecx, dword ptr [0x12ed810]` |
| 0x000F6E10 | 0x004F6E19 | `mov ecx, dword ptr [0x12ed810]` |
| 0x000F71C0 | 0x004F723A | `mov ecx, dword ptr [0x12ed810]` |
| 0x000F74C0 | 0x004F74FC | `mov dword ptr [0x12ed810], 0` |
| 0x000F7FA0 | 0x004F80D0 | `mov ecx, dword ptr [0x12ed810]` |
| 0x000F7FA0 | 0x004F80E0 | `mov ecx, dword ptr [0x12ed810]` |
| 0x001112D0 | 0x005113EC | `mov eax, dword ptr [0x12ed810]` |
| 0x001112D0 | 0x005116C9 | `mov eax, dword ptr [0x12ed810]` |
| 0x0015B750 | 0x0055B753 | `mov ecx, dword ptr [0x12ed810]` |
| 0x0015C330 | 0x0055C34A | `mov ecx, dword ptr [0x12ed810]` |
| 0x0015C570 | 0x0055C5A4 | `mov ecx, dword ptr [0x12ed810]` |
| 0x0015C7A0 | 0x0055C7EF | `mov ecx, dword ptr [0x12ed810]` |
| 0x0015CCE0 | 0x0055CD07 | `mov ecx, dword ptr [0x12ed810]` |
| 0x0015D530 | 0x0055D5DF | `mov ecx, dword ptr [0x12ed810]` |
| 0x0015E180 | 0x0055E1B7 | `mov ecx, dword ptr [0x12ed810]` |
| 0x0015E2F0 | 0x0055E330 | `mov ecx, dword ptr [0x12ed810]` |
| 0x0015E510 | 0x0055E594 | `mov ecx, dword ptr [0x12ed810]` |
| 0x00161B50 | 0x00561C99 | `mov ecx, dword ptr [0x12ed810]` |
| 0x001650F0 | 0x00565189 | `mov ecx, dword ptr [0x12ed810]` |
| 0x001650F0 | 0x005654F7 | `mov ecx, dword ptr [0x12ed810]` |
| 0x00167930 | 0x00567983 | `mov ecx, dword ptr [0x12ed810]` |
| 0x00167930 | 0x005679F3 | `mov ecx, dword ptr [0x12ed810]` |
| 0x001699C0 | 0x00569A13 | `mov ecx, dword ptr [0x12ed810]` |
| 0x001699C0 | 0x00569B05 | `mov ecx, dword ptr [0x12ed810]` |
| 0x001709E0 | 0x00570AAB | `mov ecx, dword ptr [0x12ed810]` |
| 0x00180710 | 0x0058075C | `mov ecx, dword ptr [0x12ed810]` |
| 0x0018C480 | 0x0058C5C0 | `mov ecx, dword ptr [0x12ed810]` |
| 0x001C4670 | 0x005C4694 | `mov ecx, dword ptr [0x12ed810]` |
| 0x001C6D00 | 0x005C6D55 | `mov ecx, dword ptr [0x12ed810]` |
| 0x001CEFC0 | 0x005CF05A | `mov ecx, dword ptr [0x12ed810]` |
| 0x001D48A0 | 0x005D4D00 | `mov ecx, dword ptr [0x12ed810]` |
| 0x00219960 | 0x006199E9 | `mov ecx, dword ptr [0x12ed810]` |
| 0x0021DAA0 | 0x0061DB0D | `mov ecx, dword ptr [0x12ed810]` |
| 0x0023CEC0 | 0x0063CF56 | `mov ecx, dword ptr [0x12ed810]` |
| 0x002BD020 | 0x006BD054 | `mov ecx, dword ptr [0x12ed810]` |
| 0x002BD230 | 0x006BD267 | `mov ecx, dword ptr [0x12ed810]` |
| 0x002BD310 | 0x006BD35F | `mov ecx, dword ptr [0x12ed810]` |
| 0x002BD630 | 0x006BD667 | `mov ecx, dword ptr [0x12ed810]` |
| 0x002BD8B0 | 0x006BD8D7 | `mov ecx, dword ptr [0x12ed810]` |
| 0x002C07E0 | 0x006C088F | `mov ecx, dword ptr [0x12ed810]` |
| 0x002C0D50 | 0x006C0DDD | `mov ecx, dword ptr [0x12ed810]` |
| 0x002C0E70 | 0x006C0EDE | `mov ecx, dword ptr [0x12ed810]` |
| 0x002C0FE0 | 0x006C1064 | `mov ecx, dword ptr [0x12ed810]` |
| 0x003006B0 | 0x00700818 | `mov ecx, dword ptr [0x12ed810]` |
| 0x003262C0 | 0x00726310 | `mov ecx, dword ptr [0x12ed810]` |
| 0x0032A2E0 | 0x0072A3B9 | `mov ecx, dword ptr [0x12ed810]` |
| 0x00336D90 | 0x00736DED | `mov ecx, dword ptr [0x12ed810]` |
| 0x0033E490 | 0x0073E58C | `mov ecx, dword ptr [0x12ed810]` |
| 0x00340F10 | 0x00740FFD | `mov ecx, dword ptr [0x12ed810]` |
| 0x0034C670 | 0x0074C6A8 | `mov ecx, dword ptr [0x12ed810]` |
| 0x0034F160 | 0x0074F2D4 | `mov ecx, dword ptr [0x12ed810]` |
| 0x0034F160 | 0x0074F331 | `mov ecx, dword ptr [0x12ed810]` |
| 0x0034F160 | 0x0074F41E | `mov ecx, dword ptr [0x12ed810]` |
| 0x00394260 | 0x00794992 | `mov ecx, dword ptr [0x12ed810]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.
