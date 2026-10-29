# 0x0069F540: bank name `eraseKey` retired for `MilesAudioManager::rva0069F540`

- Retail 0x0069F540 (106 B, ret 4) is MilesAudioManager vtable 0x0111C0C0 slot 88
  (entry ILT 0x000165EF), so the body is a virtual member of MilesAudioManager,
  not the non-virtual `Rva0069F540Owner::eraseKey` the 2026-10-29 bank declared.
- `tools/ilt_oracle.py check '?eraseKey@Rva0069F540Owner@@QAEXPAX@Z' 0x69F540`:
  CONTRADICTED (outside every window of slots 12260-12267). `eraseKey` was a
  bank-local descriptive guess with no caller, string or donor naming it.
- No source names the method, so it keeps an address-derived name, matching the
  table's other slots (`rva006B86D0@MilesAudioManager`, slot 9).
