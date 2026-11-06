# IFEBrowserEngine2 interface ID at retail 0x0113DF00

Retail `.rdata` VA `0x0113DF00` holds the 16-byte `IFEBrowserEngine2` interface
ID:

```
17 3b 88 ee 78 07 18 4b a1 2b e4 4c 0d 29 84 12
```

i.e. `{ee883b17-0778-4b18-a12b-e44c0d298412}` in registry order.

## Facts

- The repo's COM browser wrappers report failures with `g_bfmeIidTSA`
  (`game/GameEngine/Source/GameNetwork/WOLBrowser/WebBrowserComWrappers.cpp`
  rows `?invoke@Rva00958D30@@QAEJVBfmeBstrVGP@@@Z` and
  `?invoke@Rva00958940Ptr...`; symbols.csv pins
  `?g_bfmeIidTSA@@3UBfmeGuidTSA@@A` at `0x00D3DF00`).
- The 6-byte IID leaves in
  `game/GameEngine/Source/Common/Small03eComGuard.cpp`
  (`?get@Rva00958770Iid@@SAABU_GUID@@XZ` at `0x00958770`,
  `?iid@Rva00958940Ptr@@SAABU_GUID@@XZ` at `0x00958950`) return the address of
  this constant via `__uuidof(IFEBrowserEngine2)`.
- `targets/game/reverse/dir32_addresses.csv` records
  `?g_bfmeIidTSA@@3UBfmeGuidTSA@@A` at `0x0113DF00` (+4 more spellings).
- `game/GameEngine/Source/Common/BfmeConv1322.cpp` referenced the same 16
  bytes through the TU-local `__GUID_ee883b17_...` extern, which names no
  defining body. The TU now defines the datum under the recorded name and
  passes its address to both `bfmeReportTSA` calls, matching the IID the
  wrappers and leaves use.

## Contract

- Own only the 16 datum bytes at `0x0113DF00`; no COM behavior, vtable, or
  whole-link credit is claimed here.
- `BfmeGuidTSA g_bfmeIidTSA` is the recorded identity; the TU-local
  `__GUID_...` spelling is retired for the two call sites.
