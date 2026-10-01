# DirtySock: canonical native Sleep import

Retail's actual PE import directory identifies IAT VA01358F30 as
KERNEL32.dll!Sleep. Three existing matched bodies call that cell:
_Rva007FE620/67B, _Rva007FE670/75B and _Rva007FEBD0/214B. Their original
DIR32 offsets are respectively +34, +29 and +183. Each callee inspection at
its full ledger extent independently reports that native import identity.

The native installed PlatformSDK WinBase.h declares WINBASEAPI VOID WINAPI
Sleep(DWORD dwMilliseconds) at line2670. The already included pristine
Gamespy C windows.h:108 declares dllimport void __stdcall Sleep(DWORD), with
DWORD unsigned long (32-bit under the actual compiler). Actual argument
constants are 50, 1 and 1; adopting the canonical prototype changes no code.
The tracked __imp__Sleep@4 DIR32 home already equals the retail slot.

Only the old Rva01358F30Wait declaration and its three calls are replaced;
the misleading anonymous-import comment is corrected. No header, type,
critical-section layout, pin or other Winimport declaration changes. All
three bodies were claimed; after discovering the third site through the
complete COFF audit, the initial edit was restored before claiming and
reapplying it. The final full TU gate is freshly run on that claimed version.

Before63540 and finalafter45529 gates both exit0: 40/40 functions, 113 DIR32,
zero string/float references. Independent comparison proves all forty raw
COFF bodies identical and all relocation offsets/kinds unchanged. Exactly
three external names change, from __imp__Rva01358F30Wait@4 to __imp__Sleep@4;
compiler-local labels retain their section/value/type/storage.

Strict controls under build/y4_sleep_import use genuine native import
archives, /NODEFAULTLIB and no /FORCE. Because the C TU has one ordinary
shared .text, controls preserve and reparse bounded actual COFF extracts.
The positive includes the complete compiled 67B and 75B shutdown bodies.
The third 214B body also calls four unrepaired other Windows aliases; its
strict control is ONLY the exact eight bytes at RVA007FEC83: push1 followed
by FF15, preserving the original Sleep relocation at extracted offset4.
This code-site control does not claim that the complete 214B caller links.
Its complete raw214B equality is independently proved by the all40 audit
and full-body scoped gate.

The native positive LINK exits0. All three selected FF15 operands must equal
the selected PE's actual KERNEL32.dll!Sleep import-directory slot. Unrepaired
alias and missing Kernel32 archive controls each fail LINK96. A fake canonical
IAT stub links0 but is rejected by selected_import_audit: the selected address
has no actual native DLL/name import identity. Other imports are not faked
in the positive; unrelated data/helper stubs are explicitly labelled in the
receipt. No scratch weak aliases or production alias bridge is introduced.

Actual numerical exits, hashes, MAP/PEs, complete40-body comparison and
extraction/reparse checks are in controls.py/json. This proves one native API
and three source edges, not whole-caller/TU/program runtime closure. Zero new
matched C++ or data bytes are claimed. The independent clone spent about
11 minutes packing; no duplicate clone/compiler/link job or lock override
was used.

Official current link_check against the accepted5d21 census remains
LINKED0->0 for this 6,988-byte TU; other Windows imports and data/callees
remain unresolved. Pin consistency and CSV validation pass (171165 function
rows /89947 symbols /21 data rows). No whole-TU clean credit is taken.
