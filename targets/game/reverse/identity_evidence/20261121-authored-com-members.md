# B1 authored COM members, private handoff, 2026-11-21

Status: private evidence only, no normal admission, claim/register/production/Git change.
Root holds the fourteen actual RVAs in `bfme1/com-members-claim-scope.json`.
Suggested tracked evidence destination:
`targets/game/reverse/identity_evidence/20261121-authored-com-members.md`.

## Final files and accounting

`ComInvoke-CANDIDATE.cpp` is the complete original `Release\invkprxy.obj`:

| RVA | Complete bytes | Native body | New C++ exact |
|---|---:|---|---:|
| 00AFDB40 | 1571 | _com_invoke_helper | 1571 |
| 00AFE170 | 74 | _com_dispatch_raw_method | 74 |
| 00AFE1C0 | 35 | _com_dispatch_raw_propget | 0, existing authored wrapper |
| 00AFE1F0 | 105 | _com_dispatch_raw_propput | 105 |

`ComSupp-CANDIDATE.cpp` deliberately contains five bodies of the fully audited
six-body `Release\comsupp.obj`, preserving the existing generated owner outside:

| RVA | Complete bytes | Native body | New C++ exact |
|---|---:|---|---:|
| 00AFD530 | 12 | _set_com_error_handler | 12 |
| 00AFD540 | 16 | _com_issue_error, unchanged named_000.cpp | 0 |
| 00AFD550 | 110 | _com_issue_errorex | 110 |
| 00AFD5C0 | 73 | _com_dispatch_method | 73 |
| 00AFD610 | 35 | _com_dispatch_propget | 0, existing authored wrapper |
| 00AFD640 | 104 | _com_dispatch_propput | 104 |

Maximum new recovery is seven bodies / 2,049 C++-exact bytes, zero new total-text
coverage. The two35B wrappers and the generated16B body earn no new body credit.
This is source recovery, not a memory/crash/FPS/runtime improvement.

### Native refusal preserved

Root found that ordinary `add_match --replace-existing` refuses moving any
game/gen_small owner and `--replace-rva` does not admit this gen-named owner.
Therefore do not move/delete/rewrite `game/gen_small/named_000.cpp` or its row,
and do not change the admission guard. Final ComSupp omits _com_issue_error.
`retained-generated.json` independently compiles that unchanged source to private
normal/+Z7 outputs and proves its complete16B strict exact with the normal map.
Its source hash is unchanged. `whole-six-*` receipts are historical private
evidence for the initially exact full original member, not the final landing.

## Provenance and smallest adaptations

Authored BFME2 donor revision147fd3e52b36ee0306aaeef5b316beb09f7c7671:

- `Code/Libraries/Source/COM/_com_error.cpp`, hash
  6949f661f5af60082c71dd55114d10d8515e4a7c442753bc58655fa7f5486c48.
  Only its previously authored, historically standalone ComInvoke four-procedure
  section is used. The B1 original archive proves that whole-member boundary.
- `Code/Libraries/Source/COM/ComSupp.cpp`, hash
  829cf258372494976cf951dd26bb19a234a3250a70dda89627ba112005094a46.
- Supporting native-recovery records: `com-invoke-exact-20261018/receipt.json`,
  `com-invoke-native-structure-20261018`, `0x00654b10-com-dispatch/readme.md`.

The inherited local name `vARIANTARG` is unchanged from donor _com_error.cpp:69
and its uses. It was not introduced or varied for code generation.

Native B1 CV supplies HRESULT and const wchar_t*; those replace the donor's
equivalent long/unsigned-short spelling. All candidate procedure signatures,
calling conventions, parameter counts and complete extents now equal native CV.
The source uses canonical SDK COM declarations. No _com_error/_variant_t class
is copied, no implementation header comdef.h/comutil.h is included, and no
assembly, emitted bytes, alias, dummy definition or pin is introduced.

The zero GUID is expressed as `__uuidof(0)` and ISupportErrorInfo's GUID as
`__uuidof(ISupportErrorInfo)`. Both emit the original exact native GUID symbols;
there are no second IID names or borrowed donor addresses. The callback uses
the original typed `__errorPfn` definition and real _com_raise_error initializer.

Disclosure: during the earlier read-only scout an overly long public comdef.h
declaration excerpt accidentally exposed subsequent _com_error inline bodies.
No _com_error implementation/class is used or copied into these two candidates;
their implementation provenance remains the pre-existing authored BFME2 files.
The final source comment states this narrower, accurate provenance.

## Native B1 identity, extents, graph and ABI

Original existing archive SHA256:
b897c136cb2eb0607d4a581f230b0b9cccec9f79c8e736710e359beda42ff45a.

- invkprxy.obj SHA256
  db29048286427dc8ec09654ec1fbf7001c453b116d9393fb7b34da2342b19fd7.
- comsupp.obj SHA256
  dd31c16ad9268f0d4aac857f9daadd1aecccc41e419573cc71e38b05fa9a3082.

Original native function definitions occupy complete separate CODE sections and
their CV procedure records independently give the listed extents. Normal and
+Z7 private builds pass every candidate body using native build.compile_function
and the unchanged normal symbol map: no map overrides, no unresolved REL32,
no library/gen-alias masked mode. All four/six original public native identities
are established independently of source placement; the final partition has five.

`*-normal-graph.json` and `*-z7-graph.json` bind native and candidate runtime nodes
bijectively by actual function/relocation relationships, check complete bytes,
real relocation offsets/types/targets, undefined and absolute identities,
COMDAT selections/associations, and original retail placement. Every compared
node's RAW bytes also agree, before relocation resolution. Final invkprxy has
six nodes (1785CODE+28data); final ComSupp has seven (334CODE+20data), plus the
explicit external16B provider. Undefined footprints are identical to originals.
No runtime section is silently omitted from the original-member accounting.

Canonical SDK CodeView agrees with the original full IUnknown/IDispatch/
IErrorInfo/GUID/VARIANT/DISPPARAMS/EXCEPINFO contracts. IUnknown has slots0..2;
IDispatch inherits at0 and adds slots3..6. GUID/VARIANT/DISPPARAMS/EXCEPINFO
are16/16/16/32B. The pure ISupportErrorInfo cast is optimized out of the candidate
debug type inventory. The explicitly separate `sdk-interface-type-witness.json`
forces that SDK type in the same include/flag context: original and compiled
records both give size4, IUnknown base0, no fields and slot3
InterfaceSupportsErrorInfo(REFIID). Original candidate bodies stay exact in this
type-witness object. Its extra diagnostic function is never a candidate body.
The witness predates only omission of the independent generated16B function and
comment changes, with the same SDK include and flag context.

The complete native SEH table is RVA00DBC370/12B. Its two action/filter targets
are within the already counted1571B helper. No separate cleanup/body row is
proposed. The actual .sxdata index binds the strong undefined Function
__except_handler3 in both original and candidate. Full graph proof covers all
scope bytes and pointer edges; do not manufacture a public data symbol for its
local compiler label.

## Data owners and real providers

| Native object symbol | RVA | Bytes | Owner/source |
|---|---|---:|---|
| __GUID_00000000_0000_0000_0000_000000000000 | 00DBC35C | 16 | ComInvoke.cpp, compiler GUID |
| __GUID_df0b3d60_548f_101b_8e65_08002b2bd119 | 00DBC334 | 16 | ComSupp.cpp, compiler GUID |
| ?__errorPfn@@3P6GXJPAUIErrorInfo@@@ZA | 00EE600C | 4 | ComSupp.cpp, typed callback |

All three native names are already in dir32_addresses; no matched data_rows
owner was found at these addresses during the scout. Add real owner rows only
through add_data_match and retain any native refusal. Its normal form is
`python3 tools/add_data_match.py NAME RVA --rva SOURCE --size N --model MODEL
--evidence EVIDENCE`; the two public compiler GUIDs and typed callback are the
only proposed data rows. The local12B scope remains compiler metadata.

The callback initializer names the unchanged original comraise _com_raise_error
at RVA00AFDA50. ComSupp calls the real invkprxy helper at00AFDB40; that helper
calls the unchanged native invkerr _com_handle_excepinfo at00AFE280. The existing
normal map already supplies all REL32 names. __except_handler3 is the current
Root-admitted CPP provider f12bebc903; the scope read here does not reprove its
entire102-body source-owned IAT package or full-game selection.

`external_bindings` in graph receipts independently binds original IAT references
to the real PE exports: GetErrorInfo, lstrlenW, GetLastError, VariantInit,
VariantClear, VariantChangeType and SetErrorInfo. __except_list is the original
absolute FS-chain offset0, not an invented global. The old generated16B body
references legacy `__imp_?_com_raise_error@@YGXJPAX@Z` at callback VA012E600C.
That is NOT a PE IAT import. It is preserved unchanged; no alias, fake import
cell, pin or provider workaround is proposed for it. Normal current provider/
data-owner/link gates must judge the integrated tree.

The bounded non-executed DLL (`focused-link.json`) links all nine final candidate
bodies together with untouched native archives/import libraries. MAP proves all
nine from candidate objects, only comraise.obj and invkerr.obj selected from
original COM archive, and no selected original comsupp.obj/invkprxy.obj. It also
records the actual CRT/Win32/OLE providers. No /INCLUDE/alias/FORCE/DEF was used.
The unchanged generated16B external owner is explicitly outside this bounded
closure and has only its separate normal-map byte proof. The DLL's import handler
comes from the untouched native CRT archive; this is not the full game's selected
CPP-handler/link-census proof. No DLL/EXE was executed.

## Source/flag mapping and Root landing

Both final source-only patches target `game/Libraries/Source/COM/`.
Invkprxy retains donor's explicit /O2 /G6 /Ob2 /EHsc /GR /DNDEBUG /MD profile;
ComSupp retains /Ob2 /EHsc /DNDEBUG /MD with native B1 O2 defaults. The supported
native toolchain-include resolver maps the source's
`inputs/toolchains/vs2003/Vc7/PlatformSDK/Include` to the actual installed SDK
directory. All actual /showIncludes paths and hashes are frozen in PACKAGE.json;
no missing include directory is silently substituted. Objstore is off; all
outputs are explicit private paths, at most two workers. No flags were swept.

1. Integrate ComInvoke first. The existing row at00AFE1C0 is
   `?bfmeRva00AFE1C0DispatchRawMethod@@YGJPAUIDispatch@@JGPAX@Z`;
   native original identity is
   `?_com_dispatch_raw_propget@@YGJPAUIDispatch@@JGPAX@Z`.
   Use ordinary add_match --replace-rva 0x00AFE1C0 --correct-identity OLD_NAME
   --identity-evidence NOTE; use --replace-existing for the three same-name
   library rows. Source contains the complete real original member.
2. `wrapper-phase1-after-ComInvoke.patch` removes only that former wrapper and
   its now-unused raw-method declaration from the existing Common source.
3. Integrate final five-body ComSupp. At00AFD610 the existing name is
   `?bfmeRva00AFD610DispatchMethod@@YGJPAUIDispatch@@JGPAX@Z`; native original is
   `?_com_dispatch_propget@@YGJPAUIDispatch@@JGPAX@Z`. Use the same ordinary
   correction route, and --replace-existing only for its four library rows.
   Do not touch AFD540 or its generated source.
4. `wrapper-phase2-after-ComSupp.patch` is based on the phase1 result and deletes
   the old Common source only once both35B rows are rehomed. Freshly compare its
   base hash before either patch; preserve concurrent edits. No ledger/Git edit
   is included in any package patch.
5. Root runs normal source/data/identity/extent/provider gates and banks verified
   bodies separately. Native refusals remain binding; private graph receipts
   do not grant admission. Check the two data owners and retained generated
   caller together before publication. Native progress measures actual results.

Repro tools are `probe_members.py`, `check_graph.py`, `retained_generated.py`,
`focused_link.py`, `make_package.py`, all under this private diagnostics folder.
Use the existing B1 environment.ps1, BFME_OBJSTORE=off and explicit private
outputs. No production helper should read a diagnostic object as a cached build.

Final source and source-patch SHA256 values, all dependency hashes and sequential
wrapper base hashes are in PACKAGE.json. The package is immutable for Root's
review; subsequent source changes require a new receipt.
