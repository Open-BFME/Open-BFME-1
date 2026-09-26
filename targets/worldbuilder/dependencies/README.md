# WorldBuilder MFC71 imports

`mfc71.csv` names 531 of this target's 532 MFC71 ordinal imports. It is an
identity map, not reconstructed game/editor source or a coverage claim.
`mfc71.json` pins the WorldBuilder image, runtime version, all evidence hashes,
and the generated mapping hash.

```sh
python3 tools/worldbuilder_mfc.py fetch    # download pinned evidence and verify
python3 tools/worldbuilder_mfc.py verify   # reproduce from existing cached inputs
python3 tools/worldbuilder_mfc.py prepare  # also build an ordinal import library
```

Downloads and generated DLL/PDB/DEF/LIB artifacts stay under
`build/worldbuilder/dependencies/mfc71/`. No installed game, Ghidra database,
or system-wide installation is required. `prepare` uses the repository's
MSVC 7.1 toolchain and Wine on Linux. A failed download or hash check is an
error; the tool does not substitute a different runtime or ordinal table.

## Evidence

The Microsoft symbol server supplies both the exact `MFC71.dll` version
**7.10.3077.0** and its matching unstripped PDB. The DLL's RSDS GUID/age must
agree with the PDB before names can be used. Microsoft's BBT optimization
reordered this DLL, so public symbol addresses must pass through the PDB's
`OMAP_FROM_SRC` table using its original section headers.

The [Ghidra ordinal table](https://github.com/NationalSecurityAgency/ghidra/blob/74585d2c02e4cfd0c2f4a0513a009a6896db586f/Ghidra/Features/Base/data/symbols/win32/mfc71.exports)
independently assigns the decorated name to each ordinal. For each accepted
row, that name must also be a public symbol at the exact Microsoft DLL export
address after OMAP translation. This conjunction matters: multiple PDB names
can share one address in MFC, and choosing an arbitrary public would not
establish the ordinal's API. Ghidra is an NSA open-source project distributed
under [Apache 2.0](https://github.com/NationalSecurityAgency/ghidra/blob/74585d2c02e4cfd0c2f4a0513a009a6896db586f/LICENSE).

`pdb_rva_candidates` records how many PDB public names share the address; it is
not a list of accepted aliases. There are 395 accepted single-name rows and
136 accepted rows with multiple names. The mapping includes 530 code imports
and one data import. Both the PDB function flag and DLL section permissions
must agree on that classification. `prepare` reads back all 531 generated
COFF import members and verifies symbol, ordinal, machine, ordinal-import
mode and data/code type.

The narrow PDB parser follows the [MSF layout documented by LLVM](https://llvm.org/docs/PDB/MsfFile.html),
the [DBI stream layout](https://llvm.org/docs/PDB/DbiStream.html), and Microsoft's
[`S_PUB32` record definition](https://github.com/microsoft/microsoft-pdb/blob/master/include/cvinfo.h).
LLVM pdbutil 21 and 22 crash while dumping this old PDB's publics on the
investigation host; reproducing this map therefore does not depend on them.

## Explicit exclusion

Ordinal **5230** is intentionally unresolved and omitted from the library.
Ghidra identifies `CWinThread::PumpMessage`, but its PDB public has been removed
by OMAP and the export address belongs to `AfxInternalPumpMessage`. The shipped
MFC source makes the former a wrapper around the latter; this explains the
observation but does not satisfy the direct symbol/address proof used here.
A caller needing 5230 fails with an unverified-ordinal error. Do not replace
its API name with the surviving implementation's name to make a caller match.

This is a partial import library for independently proved WorldBuilder calls,
not a complete replacement for the original MFC SDK import library or proof
that the complete editor can now link. In particular, ordinal 5230 and APIs
not imported by this WorldBuilder binary are excluded.
