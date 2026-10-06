# Remaining initializer storage and empty-string binding

This change supplies three existing objects used by the matched initializer
at 0x0089BBF0. It preserves their repository names and types:

| Image VA | Existing object | Size | Independent operand evidence |
|---|---|---:|---|
| 0x01337A20 | g_Rva01337A20 | 4 | initializer +0x87; matched 0x00898D60 consumer +0x0B |
| 0x013379CC | g_Va013379CC | 32 | eight consecutive float stores at initializer +0x29E through +0x2E4 |
| 0x013387B0 | g_Va013387B0 | 16 | four word stores at initializer +0x662, +0x668, +0x66E and +0x678 |

All three ranges are disjoint from existing data rows and are initially
zero in the PE loader-zero `.data` tail. The color block starts at zero;
its identity transform values are assigned later by the initializer.
`add_data_match.py` independently proves each compiled extent and all 52
initial bytes. The already-owned matrix and the separately claimed
fallback-value cell are outside this change.

The initializer's string-pool comparison previously referenced
`g_default012D5298` under a TU-local block type with no definition. It now
references the existing `EAStringC::StringDataC g_rva012D5298Empty`, defined
once in `Common/Data/Rva012D5298.cpp`, through the same local pointer view.
Only the address is compared. Retail uses VA 0x012D5298 at initializer
+0x230; the canonical owner has exactly the same address and its verified
16-byte initial contents begin with refcount 0x0101, followed by zeros.
No alias, pin, extra helper or duplicate sentinel definition is added.

The changed sentinel relocation occurs in the 1,684-byte initializer and
its 184-byte CreateString copy. That copy has internal linkage (COFF
storage class 3); shared constructor and helper COMDATs are unaffected.

The scoped gate passes the initializer, all 20 data rows in its source and
the sentinel source, and all 81 DIR32 references. Complete object comparison
preserves 22 non-debug sections after resolving only the approved sentinel
symbol substitution and compiler metadata: local `$L`/`$T` labels are
compared by actual section, offset and type, and SafeSEH indices still name
the same handlers. All remaining code/unwind bytes and relocation targets
are identical. The BSS section grows from 64 to 116 bytes, with the earlier
sixteen scalar definitions retained and the three new objects added.

Address-global occurrence counts remain unchanged. No baseline, verifier,
shared header or runtime changes are involved. Static data increases by
52 bytes; no new code-conversion or linked-byte credit is claimed.
