# pdblkup whole original member: private source-recovery handoff

Root admission is pending. The private candidate recovers **3 complete bodies / 2,008 B of existing original-library coverage** as readable C++; it adds **0 B to total exact coverage**. No game runtime or full-image link improvement is claimed. Rating: **sicher** for the bounded native/object/type/import/link observations below; production acceptance is not yet observed.

Production home: `game/Libraries/Source/CRT/VS2003/RtcPdbLookup.cpp`. Whole authored source: local `RtcPdbLookup.cpp.txt`; source SHA256 `839bdb8fa5cd961b0715487862a1033417710c3cb9248ad6747ed4d28967b354`. Root holds24 code/private-data scopes under lease `2f26276958f64402b55e8afdc95d6a90`. Worker changed no production source, claims, ledger, header, import/pin/resolver, gate or Git state.

## Independent native ownership, identity and extent

Original: `inputs\toolchains\vs2003\Program Files\Microsoft Visual Studio .NET 2003\Vc7\lib\libc.lib`, member `..\build\intel\st_obj\pdblkup.obj`. Library SHA256 `25f494ca0238ae308edeab90dfaaa8c616b12f804a2156b51b9fba50eb144af1`; member SHA256 `d7bb84cdb386828cf9eab669816d53317ac385d502e3d31d6d74531fc4ddc48b`. The whole original member has exactly these3 code procedures; current library rows cover exactly `[009F808E,009F8866)`:

| Exact original COFF identity | RVA | Complete bytes | Original / source linkage |
| --- | --- | ---: | --- |
| `?GetImageInfo@@YAPAUImageInfo@@K@Z` | 0x009F808E | 849 | private STATIC storage3 |
| `?GetPdbDll@@YAPAUHINSTANCE__@@XZ` | 0x009F83DF | 312 | private STATIC storage3 |
| `?_RTC_GetSrcLine@@YAHKPADHPAHPAPAD@Z` | 0x009F8517 | 847 | public external storage2 |

Each complete original section equals its row extent. Every raw source code byte AND every original relocation tuple (offset/type/real target name) agrees with the original member, independently of relocation masking. The normal unmodified B1 symbol map also gives3/3 strict equal retail bodies, masked=false, zero unresolved. Compiler helpers retain actual native `__alloca_probe` (existing map target RVA009F6C60); no address aliases, object-symbol notes, new pins or arbitrary definitions.

## Authored donor and bounded adaptations

Authored BFME2 donor `147fd3e52b36ee0306aaeef5b316beb09f7c7671:Code/Libraries/Source/CRT/RtcPdbLookup.cpp`, SHA256 `f3e96ffb21b744cac8b706aa3cb4009442675b663101293d224d3b5b36a4e922`. This is authored donor C++, not Microsoft implementation source or a code lift. Native B1 COFF/CV/retail independently establish identities, extents, all private data names/layouts/types, direct import routes and consumed callbacks; donor control flow is a lead until the native proof above.

One executable source form was sufficient. Preserve real SDK types by including existing public windows/tlhelp32/psapi/malloc/stddef headers. B1 include mapping uses its existing native VC7 alias to its own PlatformSDK. Actual native showIncludes trace records74 genuine dependency files with hashes and confirms windows.h/tlhelp32.h/psapi.h from the intended local SDK, malloc.h/stddef.h from the intended local Vc7/include. No implementation headers/source were read. No donor toolchain or shim fallback is used.

Two donor data spellings (`pGetModuleInformation`, `pEnumProcessModules`) become the original native private spellings. Only unused same-named public psapi function declarations are hidden by two temporary macros while importing genuine SDK structs; no renamed API definition, undefined symbol, import, emitted function, call or link route exists. Both macros are immediately undefined. The source object defines exactly the3 original procedures and retains the original complete external-undefined set.

Native CodeView establishes mutable char* arguments on PDBOpenValidate3 and PDBOpenDBI; both pointer declarations and GetProcAddress casts are corrected from donor const char*. Native `_mspdbName` is a mutable32-bit pointer to const char. Callback signatures and calling conventions are compared recursively, not inferred solely from equal code.

## All21 private data objects /84 B

All retain original storage3, individual4 B extents, section offsets/extents/flags, raw initialization and data relocation identity. Native BSS is read with the loader-aware image reader; raw-file offsets are not used for zero-fill. No new data row or external replacement global is appropriate. Strong72 B original .bss is base VA0134FBB4 with18 independently CodeView-sized cells. Two explicit local software flags have their own4 B BSS COMDATs; no compiler guard was invented. The4 B initialized pointer points to complete12 B MSPDB71.DLL literal VA01145D28.

| Original private identity | RVA | Bytes | Native loader initial bytes |
| --- | --- | ---: | --- |
| `_lImages` | 0xf4fbf8 | 4 | `00000000` |
| `_Module32NextW9x` | 0xf4fbf4 | 4 | `00000000` |
| `_Module32FirstW9x` | 0xf4fbf0 | 4 | `00000000` |
| `_CreateToolhelp32SnapshotW9x` | 0xf4fbec | 4 | `00000000` |
| `_EnumProcessModules` | 0xf4fbe8 | 4 | `00000000` |
| `_GetModuleInformation` | 0xf4fbe4 | 4 | `00000000` |
| `_ImageNtHeader` | 0xf4fbe0 | 4 | `00000000` |
| `_PDBClose` | 0xf4fbdc | 4 | `00000000` |
| `_DBIClose` | 0xf4fbd8 | 4 | `00000000` |
| `_ModClose` | 0xf4fbd4 | 4 | `00000000` |
| `_ModQueryLines` | 0xf4fbd0 | 4 | `00000000` |
| `_DBIQueryModFromAddr` | 0xf4fbcc | 4 | `00000000` |
| `_PDBOpenDBI` | 0xf4fbc8 | 4 | `00000000` |
| `_PDBOpenValidate3` | 0xf4fbc4 | 4 | `00000000` |
| `_kernel` | 0xf4fbc0 | 4 | `00000000` |
| `_imghlp` | 0xf4fbbc | 4 | `00000000` |
| `_psapi` | 0xf4fbb8 | 4 | `00000000` |
| `_mspdb` | 0xf4fbb4 | 4 | `00000000` |
| `_mspdbName` | 0xedbdf4 | 4 | `285d1401` |
| `?alreadyTried@?1??GetPdbDll@@YAPAUHINSTANCE__@@XZ@4HA` | 0xf4fbfc | 4 | `00000000` |
| `?PDBOK@?3??_RTC_GetSrcLine@@YAHKPADHPAHPAPAD@Z@4HA` | 0xf4fc00 | 4 | `00000000` |

Native/source diagnostic Z7 graphs match for all21 data and all3 complete procedure prototypes/kinds/extents. Pointer modifiers, cdecl versus stdcall, argument count/order/types, and native opaque PDB/DBI/Mod tags are preserved. Complete consumed layout projections agree for ImageInfo32, MODULEINFO12, ANSI MODULEENTRY32 548, NT_HEADERS248, SECTION_HEADER40 and local source-module/line structures. Compile-time sizeof/offsetof assertions check consumed layouts. Opaque or forward SDK records are honestly limited to their witnessed identity/consumed layout; missing complete native internals are not asserted. Z7 changes neither raw code nor relocation tuples of any body.

## Strings, imports and actual non-executed closure

All25 pooled literal definitions have original names, complete raw bytes, original section size/flags/storage, and independently derived original target addresses. Existing pools include shared empty string atRVA00C7301C and r atRVA00D30B38; they are not new exclusive external data ownership. Original mspdbName data-DIR32 selects original MSPDB71.DLL literal. No approximate matching or pool padding masks are used.

Both native original-control and authored-candidate were linked successfully by the actual VC7 linker as non-executed /DLL /NOENTRY units using genuine original msvcrt.lib/kernel32.lib/oldnames.lib, /NODEFAULTLIB, /OPT:NOICF, /OPT:NOREF, forcing the actual public source-line symbol. No fake callback/import/provider, custom DEF/import-library, library mutation, /FORCE or source helper substitution. Link maps prove all3 code providers from the respective actual object; candidate does not select original pdblkup.obj. Linked code operands independently recover all21 real private addresses;20 loader zeros and the relocated literal pointer agree. These are bounded real closure checks, not a full game-link scoreboard or runtime result.

Exactly9 actual direct IAT cells agree with the real native retail PE import identities, in both source/control links; no extra import:

| Original IAT COFF name | Retail IAT VA | Native route |
| --- | --- | --- |
| `__imp__CloseHandle@4` | 0x1358ccc | KERNEL32.dll!CloseHandle |
| `__imp__FreeLibrary@4` | 0x1358d48 | KERNEL32.dll!FreeLibrary |
| `__imp__GetCurrentProcess@0` | 0x1358d70 | KERNEL32.dll!GetCurrentProcess |
| `__imp__GetModuleFileNameA@12` | 0x1358dc0 | KERNEL32.dll!GetModuleFileNameA |
| `__imp__GetProcAddress@8` | 0x1358dd8 | KERNEL32.dll!GetProcAddress |
| `__imp__GetProcessHeap@0` | 0x1358ddc | KERNEL32.dll!GetProcessHeap |
| `__imp__HeapAlloc@12` | 0x1358e3c | KERNEL32.dll!HeapAlloc |
| `__imp__HeapFree@12` | 0x1358e44 | KERNEL32.dll!HeapFree |
| `__imp__LoadLibraryA@4` | 0x1358e78 | KERNEL32.dll!LoadLibraryA |

## Actual compiler context and proof boundaries

Executable source profile: `/O1 /G6 /Oi /Ob1 /MD /GX- /GS-` plus genuine local SDK include alias. Native helper adds its ordinary `-O2 -GR- -EHsc-` before per-source overrides. Compiler SHA256 `2ecf86a3edfd3deae498e08298e210e984537ce9e11759930561e43f40bd2515`. Full argument vector, unmodified source/object hashes and fresh compile output are in form1.compile.json. Actual compiler diagnostics include D4025 overriding /O2 with /O1; D4025 overriding /EHs with /GX-; and D4002 ignoring unknown option `-G-`. The actual warning is preserved; unsupported flag behavior is not claimed effective or silently cleaned up. Despite it, full code/relocations/undefineds independently equal original. No additional profile search was needed.

The one source form was compiled normally, again with diagnostic Z7 only for native typegraph, and unchanged again with showIncludes only to preserve actual dependencies. These are diagnostic contexts, not alternative body forms. Explicit private outputs only, BFME_OBJSTORE=off, at most4 workers. Private build/ sources intentionally do not obtain reusable native inventory receipts; evidence is explicitly fresh diagnostic, not claimed cache currency. Root must run ordinary admission and scoped verification against the current checkout.

Current related repair_queue.parse_debt result: **none** for any of24 code/private-state identities. No fictitious debt pass-test is proposed. If fresh current debt changes, root must use its exact native baseline_line/pass-test and cannot add/widen a baseline.

## Root-only normal landing sequence

1. Inspect/copy the exact source into the proper home and preserve this HDF under `targets/game/reverse/attempt_support/20261120-pdblkup-whole-member.md`; no existing C++ source is replaced. Keep all21 data private and unchanged; no add_data_match commands.
2. Use the companion `normal-admission-commands.py.txt`: ordinary add_match --replace-existing for each unchanged original function identity/extent, no --no-verify, no identity or archive-import bypass. Preserve one verified substantive body per commit as requested, while publishing the whole3-body member coherently. Existing library rows supply the other identities during staged rehoming; never create fake present-unmatched markers.
3. Ordinary check_csv, find_declared_unmatched, and Windows build.cmd for the complete TU; native body/private-data/DIR32/provider/consumer checks remain authoritative. No header or resolver change is needed. Review fresh actual callers of public source-line function and the existing alloca/IAT providers together; do not infer full-census linked bytes from this bounded proof.
4. Preserve original claims until normal root publication and use proper Claim-Lease trailer/release. No worker admission, commit or publication has occurred.

Private evidence directory: `W:\OpenBFME\diagnostics\continue-20261120-body-recovery-1656\agents\transport\pdb-reservation`. LANDING-MANIFEST.json hashes native/object/type/dependency/closure receipts; RESERVATION.md/json retain independent original addresses and individual native CodeView sizes. Reproduction scripts in its parent: pdb-port-form1.py, pdb-port-form1-proof.py, pdb-port-typegraph-proof.py, pdb-final-context-proof.py and pdb-native-closure.py. These private paths are host-local audit evidence, not tracked dependencies or cache proof. Root normal CLI is the portable admission authority.
