# 0x007FE780 logger: native OutputDebugStringA binding

The existing 242-byte `_Rva007FE780` logger in Y4DirtySockDebug.c calls through
VA 0x01358EA8. Retail's PE import directory, independently reported by
`callees.py 0x007FE780 242`, identifies this slot as
`KERNEL32.dll!OutputDebugStringA`. It is an IAT slot, not a hookable ordinary
data pointer. The existing DIR32 row already names `__imp__OutputDebugStringA@4`
at that address; no pin or mapping was added.

Retail pushes one text pointer before `FF 15 A8 8E 35 01`; ESP checking after
that call witnesses callee cleanup. Its result is ignored; the logger returns
zero separately. The existing WWLib/win.h declaration gives the native
`__declspec(dllimport) void __stdcall OutputDebugStringA(LPCSTR)` contract.
That header is C++ only. This C TU uses the existing Gamespy C windows shim's
LPCSTR and WINAPI types, with the same missing API declaration locally.

Before and after scoped gates both exit 0: 1/1 existing function, 2 DIR32.
The complete 242-byte COFF body is identical. Its external relocation at
+157 changes only from `_g_Rva01358EA8Print` to
`__imp__OutputDebugStringA@4`. Three compiler-local `$L` names renumber with
unchanged section/value/type/storage; all relocation offsets and kinds agree.

Official import_binding check exits 0, with actual imports
KERNEL32.dll!OutputDebugStringA and MSVCR71.dll!vsprintf. Independent strict
controls use /NODEFAULTLIB, no /FORCE, retail-native import archives and seven
explicitly labelled non-import scaffolding symbols:

- Native positive: LINK exit 0. Selected logger's FF15 operand is 0x10002000,
  exactly the selected PE's Kernel32 OutputDebugStringA IAT slot.
- Old ordinary-data alias: LINK exit 96, unresolved `_g_Rva01358EA8Print`.
- Native Kernel32 archive omitted: LINK exit 96, unresolved canonical IAT.
- Canonical-name fake stub: LINK exit 0, but selected_import_audit rejects it;
  its selected address has no actual native import-directory identity.

Scratch receipts/scripts/objects/MAPs are under build/output_debug_import;
official receipt is build/import_binding/Y4DirtySockDebug/receipt.json.
This repair adds zero matched function/data bytes. These scoped controls
prove the native import edge, not whole-program runtime closure. The old
census queue's byte projection is not counted as a measured gain.
