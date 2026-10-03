# 0090D280 bank declaration repairs

This changes evidence-only C++ in the attempt bank. No game definition, ledger row, symbol pin, or semantic identity is promoted.

The archived pre-edit preferred bank is `attempt_history/0x0090d280/04abd257991e87f7e774dafc5c03cba89c73c4d2938743c787c867d208c0244c.json`. It does not compile: it includes surfaceclass.h and then redeclares SurfaceClass with an invented method(int*,bool). Its typed .906 score was an instruction-shape score. The repaired native draft measures .8628 byte quality (1392 bytes, 191 non-relocation differences), and is still partial.

## Load declaration

Retail 0090D2A3 loads ECX from receiver+14; 0090D2A6 pushes the result of vslot0; 0090D2A7 directly calls0090CD00. That complete649-byte body is already claimed as Rva0090C2F0Inner::rva0090CD00LoadFromMemory(const char*) by Rva0090C2F0InnerLoad.cpp. Its source and retail read the resource at+8 and input pointer as a string. The old BfmeSub937B::bfmeCall937B(void*) spelling is a stale bank declaration, not the current provider. Both name substitutions align the bank with that existing address-qualified definition; no pin or full-name inference is added.

## Lock declaration

Retail0090D344 calls008FC660 with ECX=&surface and two stack arguments: &pitch and false. The current provider surfaceclass_lock_discard.cpp defines SurfaceClass::Lock(int*,bool) at008FC660. The canonical SurfaceClass header declares only Lock(int*), and does not declare any method(int*,bool). The bank's second SurfaceClass declaration therefore both conflicts with the header and uses an unsupported method name. SurfaceClass remains included and used for SurfaceDescription, Get_Description and Unlock. Rva008FC660 is an explicitly unpinned scratch ABI view, not a proposed new identity for SurfaceClass or Lock. Its declaration must be reconciled with the native BFME overload before promotion.

## Temporary construction and destruction

Retail0090D320 calls008FC590 after placing the resource argument on the stack and the temporary address in ECX. The existing25-byte provider is BfmeThingDC::BfmeThingDC(BfmeItemDC*) in BfmeOneHundredEightySix.cpp: it stores the pointer at+0 and conditionally calls its AddRef slot at+4. Retail0090D78D calls008FC5B0, the existing13-byte W3DRadarResetSurface destructor provider: it reads+0 and conditionally calls resource Release at+8. The bank formerly attached both operations to an unproved W3DRadarResetSurface constructor. The new local Rva0090D280Surface adapter derives from BfmeThingDC to call the actual constructor and explicitly invokes the still-named W3DRadarResetSurface destructor. W3DRadarResetSurface is retained as that destructor view; it is not renamed to the adapter. The checker pairs the old temporary declaration with the new adapter at its use, so that reported pair is a source-correspondence correction.

Retail/Ghidra corroboration: tableVA0113A668 slot3 at0113A674 points to bodyVA00D0D280; constructor0090E470 installs that table. Body code ends at RET0090D7AA, followed by aligned owned switch tables through0090D7EF. The owner/method remain opaque. No successful byte score is used to establish a name.
