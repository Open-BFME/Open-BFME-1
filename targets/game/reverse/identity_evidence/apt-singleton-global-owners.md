# Physical owners for Apt singleton globals

Seventeen existing extern declarations become zero-valued definitions, with
their types and repository spellings preserved. Sixteen belong to the
matched initializer at 0x0089BBF0; the registerClass value belongs to its
matched lookup at 0x008A48A0. This supplies 68 bytes of previously missing
data ownership. It does not assert original names for address-derived
globals or convert another function.

All addresses below are image VAs. Each cell is four loader-zero bytes in
retail `.data`, independently verified by `tools/add_data_match.py` using
the defining symbol, its compiled size, and the retail image.

| VA | Existing global | Defining source |
|---|---|---|
| 0x01337A28 | g_Rva01337A28Index | Rva0089BBF0InitGlobals.cpp |
| 0x013379B4 | g_Va013379B4 | Rva0089BBF0InitGlobals.cpp |
| 0x013379FC | g_Va013379FC | Rva0089BBF0InitGlobals.cpp |
| 0x013379AC | g_Va013379AC | Rva0089BBF0InitGlobals.cpp |
| 0x013387D8 | g_Va013387D8 | Rva0089BBF0InitGlobals.cpp |
| 0x0133846C | g_bfmeMap1024 | Rva0089BBF0InitGlobals.cpp |
| 0x01337A00 | g_Va01337A00 | Rva0089BBF0InitGlobals.cpp |
| 0x013379F0 | g_Va013379F0 | Rva0089BBF0InitGlobals.cpp |
| 0x01337A04 | g_bfmeB1038 | Rva0089BBF0InitGlobals.cpp |
| 0x013379EC | g_Va013379EC | Rva0089BBF0InitGlobals.cpp |
| 0x013379C4 | g_Va013379C4 | Rva0089BBF0InitGlobals.cpp |
| 0x013379C8 | g_Va013379C8 | Rva0089BBF0InitGlobals.cpp |
| 0x013379F8 | g_Va013379F8 | Rva0089BBF0InitGlobals.cpp |
| 0x013379B8 | g_Va013379B8 | Rva0089BBF0InitGlobals.cpp |
| 0x013379B0 | g_Va013379B0 | Rva0089BBF0InitGlobals.cpp |
| 0x01337A2C | g_Va01337A2C | Rva0089BBF0InitGlobals.cpp |
| 0x013379A8 | g_bfmeRegisterClass1015 | BfmeM1015Fallback.cpp |

The initializer's byte-verified stores establish the first sixteen bindings.
Its constructors and casts already determine the declared pointer types;
the existing integer spelling for the buffer value remains unchanged.
The registerClass lookup reads its cell after comparing against the literal
`registerClass`; retail initializer 0x0089BBA5 writes that same cell. These
observations bind each symbol to its address independently of zero contents.
The full decorated spellings and per-cell evidence are recorded in
`data_rows.csv`.

## Verification and limits

Both original code bodies pass before and after the definitions, including
one string literal and 82 DIR32 references. The final scoped gate also
verifies all seventeen data rows. The object additions are a 64-byte BSS
section in the initializer TU and a four-byte BSS section in the lookup TU.

All pre-existing code and unwind sections retain their complete bytes and
relocation targets. The initializer's `.sxdata` changes only its two COFF
symbol-table indices: they still identify the same CreateString and
InitGlobals EH handlers. This is a change of object symbol numbering, not
a new cleanup path or a repaired inherited EH implementation.

The source contains exactly the same address-global occurrences as before;
the unchanged hatch gate passes without a baseline edit or allowance.
No alias, pin, shared header, runtime change or linked-byte gain is added.
`progress.py` reports 68 additional static-data bytes and zero code or
linking delta for this change.
