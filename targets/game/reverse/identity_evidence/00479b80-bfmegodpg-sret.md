# 0x00479B80: BfmeThingDPG::bfmeGoDPG returns UnicodeString

ABI correction of an opaque placeholder; the name stays address-opaque.

- callees.py 0x479B80 30: one call, ILT 0x000424D3 -> 0x00479B00, matched
  as `?getText@WinInstanceData@@QAE?AVUnicodeString@@XZ`.
- Bytes: `push ecx; push esi; mov esi,[esp+0Ch]; push esi; add ecx,30h;
  mov dword [esp+8],0; call getText; mov eax,esi; pop esi; pop ecx; ret 4`:
  the hidden return pointer is forwarded to getText and returned, and the
  zeroed stack slot is MSVC's return-value construction flag. This is
  `UnicodeString f() { return m_member30.getText(); }`, not a
  `void call(Other*)` helper; the old declaration named a callee
  (`?bfmeCallDPG@BfmeSubDPG@@...`) nothing defines.
- The byte gate passes with the corrected signature.
