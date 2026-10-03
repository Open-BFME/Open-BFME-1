# 006BEE90 is W3DLogicalScreenToPixelScreen

- targets/game/reverse/symbols.csv pins `?W3DLogicalScreenToPixelScreen@@YAXMMPAH0HH@Z` at ILT 0x000277B9 ("BFME W3DView worldToScreen helper ILT"); the gen-thunk row ?j_000277b9 targets FUN_00abee90 = RVA 0x006BEE90.
- The matched callers Rva006FD180Mouse::worldToScreen (0x006FD180) and the W3DView worldToScreen body call that ILT with (logX, logY, int*, int*, width, height), exactly the Zero Hour W3DView::worldToScreenTriReturn call.
- 0x006BEE90 sits 0x50 bytes before PixelScreenToW3DLogicalScreen (0x006BEEE0), its sibling in Zero Hour W3DDevice/Common/W3DConvert.cpp, which the ledger already homes in W3DConvert.cpp.
- The body is the Zero Hour W3DLogicalScreenToPixelScreen formula (width*(x+1)/2, height*(1-y)/2) with a plain (int) truncation.
- The earlier name bfmeGoVGM was an opaque placeholder with no evidence.
