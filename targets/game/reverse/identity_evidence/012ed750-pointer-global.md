# ThePlayerTemplateStore pointer at VA 0x012ED750

The selected datum is `class PlayerTemplateStore *ThePlayerTemplateStore`, a single mutable singleton pointer. Its canonical decorated spelling is `?ThePlayerTemplateStore@@3PAVPlayerTemplateStore@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012ED750-retail.log`. A null initial value contains no initialized target relocation to resolve. Its mutation and address passed to the subsystem registration prove this is a writable datum rather than a compiler constant.

The registration names ThePlayerTemplateStore. The readers look up player templates by name, index the template collection, and parse PlayerTemplate blocks. The reference declares PlayerTemplateStore *ThePlayerTemplateStore. The Rva000E0F30 view in SidesList.cpp accesses that same pointer; it is not a second singleton.

The reference facts that can be checked independently are:

- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h:206: class PlayerTemplateStore : public SubsystemInterface`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h:235: extern PlayerTemplateStore *ThePlayerTemplateStore;	///< singleton instance of PlayerTemplateStore`

The pointer is defined once in `game/GameEngine/Source/Common/RTS/PlayerTemplate.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The users now declare the canonical pointer type. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?ThePlayerTemplateStore@@3PAVPlayerTemplateStore@@A` | 17 |
| `?ThePlayerTemplateStore@@3PAVRva000E1410Store@@A` | 0 |
| `?g012ED750@@3PAURva000E0F30@@A` | 1 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012ED750-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012ED750-writer.log` preserves the full registration helper and the pointer store through its address. `build/rlink/pointer-globals-1791178372/012ED750-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x00079060 | 0x004798D6 | `push 0x12ed750` |
| 0x000868D0 | 0x0048692A | `mov ecx, dword ptr [0x12ed750]` |
| 0x0009E6E0 | 0x0049E738 | `mov ecx, dword ptr [0x12ed750]` |
| 0x000A5D40 | 0x004A603E | `mov ecx, dword ptr [0x12ed750]` |
| 0x000A5D40 | 0x004A607D | `mov ecx, dword ptr [0x12ed750]` |
| 0x000AC3B0 | 0x004AC40A | `mov ecx, dword ptr [0x12ed750]` |
| 0x000D1C30 | 0x004D1CD9 | `mov ecx, dword ptr [0x12ed750]` |
| 0x000DB020 | 0x004DB086 | `mov ecx, dword ptr [0x12ed750]` |
| 0x000DB020 | 0x004DB1BC | `mov ecx, dword ptr [0x12ed750]` |
| 0x000E4210 | 0x004E424A | `mov ecx, dword ptr [0x12ed750]` |
| 0x000E4210 | 0x004E42AE | `mov esi, dword ptr [0x12ed750]` |
| 0x00198A10 | 0x00598ABD | `mov ecx, dword ptr [0x12ed750]` |
| 0x001A0390 | 0x005A0718 | `mov ecx, dword ptr [0x12ed750]` |
| 0x0035F4E0 | 0x0075F511 | `mov ecx, dword ptr [0x12ed750]` |
| 0x003865B0 | 0x00786671 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00390A50 | 0x00790A8A | `mov ecx, dword ptr [0x12ed750]` |
| 0x00390A50 | 0x00790B01 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00390A50 | 0x00790B68 | `mov eax, dword ptr [0x12ed750]` |
| 0x00390A50 | 0x00790C2C | `mov ecx, dword ptr [0x12ed750]` |
| 0x00390A50 | 0x00790D0C | `mov ecx, dword ptr [0x12ed750]` |
| 0x00390A50 | 0x00790D5B | `mov ecx, dword ptr [0x12ed750]` |
| 0x00392D00 | 0x00792F61 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00392D00 | 0x00792F7F | `mov ecx, dword ptr [0x12ed750]` |
| 0x00393880 | 0x00793AEB | `mov ecx, dword ptr [0x12ed750]` |
| 0x00393880 | 0x00793B63 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00394260 | 0x007954B7 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00394260 | 0x007954CD | `mov eax, dword ptr [0x12ed750]` |
| 0x00394260 | 0x00795501 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00394260 | 0x00795511 | `mov eax, dword ptr [0x12ed750]` |
| 0x00394260 | 0x00795547 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00418600 | 0x00818637 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00418600 | 0x0081867C | `mov ecx, dword ptr [0x12ed750]` |
| 0x00492400 | 0x008924A8 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00492400 | 0x008924C6 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00493120 | 0x008931C4 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00493120 | 0x008931E2 | `mov ecx, dword ptr [0x12ed750]` |
| 0x0049FC90 | 0x0089FDB6 | `mov ecx, dword ptr [0x12ed750]` |
| 0x004C8B40 | 0x008C8E91 | `mov ecx, dword ptr [0x12ed750]` |
| 0x004CD5F0 | 0x008CD656 | `mov ecx, dword ptr [0x12ed750]` |
| 0x004DBE80 | 0x008DC66D | `mov ecx, dword ptr [0x12ed750]` |
| 0x004E5DF0 | 0x008E6F6B | `mov ecx, dword ptr [0x12ed750]` |
| 0x004E5DF0 | 0x008E6FAC | `mov ecx, dword ptr [0x12ed750]` |
| 0x004F2410 | 0x008F270D | `mov ecx, dword ptr [0x12ed750]` |
| 0x004F6B60 | 0x008F8A5D | `mov ecx, dword ptr [0x12ed750]` |
| 0x004FA800 | 0x008FABD5 | `mov ecx, dword ptr [0x12ed750]` |
| 0x005082D0 | 0x009082E8 | `mov eax, dword ptr [0x12ed750]` |
| 0x005082D0 | 0x009083B1 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00509B30 | 0x00909DE5 | `mov eax, dword ptr [0x12ed750]` |
| 0x00509B30 | 0x00909E30 | `mov ecx, dword ptr [0x12ed750]` |
| 0x0051C2D0 | 0x0091C92E | `mov ecx, dword ptr [0x12ed750]` |
| 0x0051C2D0 | 0x0091CC35 | `mov ecx, dword ptr [0x12ed750]` |
| 0x0051C2D0 | 0x0091CC53 | `mov ecx, dword ptr [0x12ed750]` |
| 0x005294F0 | 0x009295C3 | `mov eax, dword ptr [0x12ed750]` |
| 0x005294F0 | 0x009296D5 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00559E60 | 0x00959EDF | `mov eax, dword ptr [0x12ed750]` |
| 0x00559E60 | 0x00959FA0 | `mov ecx, dword ptr [0x12ed750]` |
| 0x0055B200 | 0x0095B403 | `mov eax, dword ptr [0x12ed750]` |
| 0x0055B200 | 0x0095B440 | `mov ecx, dword ptr [0x12ed750]` |
| 0x0057A200 | 0x0097A23E | `mov ecx, dword ptr [0x12ed750]` |
| 0x0057A470 | 0x0097A99E | `mov ecx, dword ptr [0x12ed750]` |
| 0x0057BE50 | 0x0097BFD3 | `mov ecx, dword ptr [0x12ed750]` |
| 0x0057C890 | 0x0097C8E3 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00619C40 | 0x00A19D34 | `mov ecx, dword ptr [0x12ed750]` |
| 0x0061F130 | 0x00A1F1C4 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00621C40 | 0x00A224E9 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00621C40 | 0x00A229EE | `mov ecx, dword ptr [0x12ed750]` |
| 0x006247B0 | 0x00A247DB | `mov eax, dword ptr [0x12ed750]` |
| 0x006247B0 | 0x00A248A5 | `mov ecx, dword ptr [0x12ed750]` |
| 0x0062AD50 | 0x00A2B277 | `mov ecx, dword ptr [0x12ed750]` |
| 0x00689F00 | 0x00A8A198 | `mov ecx, dword ptr [0x12ed750]` |
| 0x0068EF70 | 0x00A8F2D7 | `mov ecx, dword ptr [0x12ed750]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.
