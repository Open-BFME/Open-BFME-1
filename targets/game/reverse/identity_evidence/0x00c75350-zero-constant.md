# Existing four-byte zero constant at VA 0x01075350

The existing tracked source `game/GameEngine/Source/Common/Rva005BDBC0IsZero2D.cpp` defines `extern const Real BfmeZeroRange = 0.0f`, with `Real` a float typedef. This component validates that existing definition without adding another definition, changing a name or pin, or claiming semantic provenance for the historical name.

VA 0x01075350 is RVA 0x00C75350 under ImageBase 0x00400000. Native .rdata contains exactly four zero bytes at this naturally four-byte-aligned address; the following DWORD at VA 0x01075354 is 0x3CF5C28F and belongs to a distinct nonzero constant. Supported sizeof/allocation-extent checks establish the emitted external constfloat object is four bytes, with no dynamic initialization.

The existing 49-byte matched zero-test function reads this cell as a DWORD floating operand twice. The immutable 1568-byte FX writer candidate (source SHA-256 e0d72c905006acd2b6cd69fc7cdc3788eb0fc8b64660189d474c6df5386c8589; object SHA-256 aa0a1f1122905fda0327c771e5c529bd488c8110ab4c6355aacea61d732705ec) references the exact same `?BfmeZeroRange@@3MB` external constfloat symbol twelve times. Native instructions at function offsets 0x294,0x2A9,0x320,0x335,0x362,0x377,0x3A4,0x3B9,0x3E6,0x3FB,0x428,0x43D are all FLD DWORD [0x01075350]. No callee passes or guessed aggregate layout is involved.

Other historical names pinned to this shared float constant are not converted into new definitions or extra recovered extents here. The constant definition is preserved exactly; only its independently gated data row is new. This is four bytes of static-data coverage, zero new code bytes, and no measured linking gain. The previously banked FX writer remains unaccepted until its separate source/dependency gates pass.

## Canonical upstream provider convergence

Upstream aeb01cfb already owns the aligned readonly four-byte cell at VA01075350 as `g_rva01075350` in `Common/BfmeAngleWrap0079D0.cpp`. Its original EA name is unproven. The redundant local data row was removed during synchronization; this adds zero data coverage. All163 source caller/declaration tokens now name that one existing provider. `Rva005BDBC0IsZero2D.cpp` retains its real49-byte function and changes only the duplicate constant definition to an external declaration. The pre-existing nonconst declaration in `InGameUI_addFloatingText.cpp` is corrected to the actual readonly float ABI. No header, layout, thunk, alias or address pin is added. Old BfmeZeroRange symbol/DIR32 mappings are retired.

Fresh current-strict gate:1363/1363 code rows across164 translation units, three existing data rows,161literals plus4empty,198float constants and2565DIR32 references all verified. This is a scoped receipt, not a whole-program link or full integration verdict; mandatory normal hooks and whole current-tool gate remain required.
