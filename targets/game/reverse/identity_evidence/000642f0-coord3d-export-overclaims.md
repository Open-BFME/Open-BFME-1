# RVA 0x000642F0 is the exported three-float Coord3D constructor

The unpacked BFME 1.03 image independently exports
`??0Coord3D@@QAE@MMM@Z` at RVA `0x000156C7`. Its bytes are
`E9 24 EC 04 00`: `0x000156C7 + 5 + 0x0004EC24 = 0x000642F0`.
This is a PE export-directory witness, not a name inferred from another ledger
row or generated source.

The complete 25-byte body is:

```text
000642F0  8B542408      mov edx,[esp+8]
000642F4  8BC1          mov eax,ecx
000642F6  8B4C2404      mov ecx,[esp+4]
000642FA  8908          mov [eax],ecx
000642FC  8B4C240C      mov ecx,[esp+0Ch]
00064300  895004        mov [eax+4],edx
00064303  894808        mov [eax+8],ecx
00064306  C20C00        ret 0Ch
```

Seven INT3 bytes follow, then another body at `0x00064310`. The return value
is the incoming this pointer; the three float bit patterns are copied without
arithmetic. Ghidra MCP `read_memory` on program `lotrbfme.exe` at VAs
`0x004156C7` (5 bytes) and `0x004642F0` (32 bytes) agrees with direct
pefile/Capstone decoding of
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, SHA-256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.

The existing exported row and its C++ implementation in
`game/Libraries/Source/WWVegas/WWMath/coord3d.cpp` are retained. Three
non-exported rows also claim these same bytes:

- `??0BlockHeader@TagBlockFile@@QAE@HHH@Z`
- `??0ResolutionDescClass@@QAE@HHH@Z`
- `??0Vector3i@Strip@@QAE@HHH@Z`

Their three-integer stores can produce identical instruction bytes, but the
export proves the identity of this particular retail copy. The no-ICF evidence
in `tools/one_identity.py` rules out treating the address as all four functions.
Under docs/naming_evidence.md “One body, one name”, retire and tombstone these
three surplus claims. This does not assert that those other constructors are
absent from the game, or identify their actual addresses. None has a symbols.csv
pin. Their implementations remain available in the original TUs; no speculative
replacement address or name is introduced.

The retained Coord3D row was already present in the June 28 ledger snapshot
`6459ad7276`, before the modern identity guard and one-body/one-name check.

The false BlockHeader row was added by `c13eb35ab2` on July 13; the false
ResolutionDescClass row by `d73b4e807c` on July 13. This is early-era
shape matching that predates the August 29 identity guard and September 24
one-identity enforcement. The retained constructor passes the current strict
`./build.sh '??0Coord3D@@QAE@MMM@Z'` gate (1/1 functions).
