# 0x002C7E10 is not Drawable::setFlashColor

Facts from BFME 1 retail:

- 0x002C7E10 is 13 bytes: `mov eax,[esp+4]; mov [ecx+0xD0],eax; ret 4`. The only
  rel32 reference to it is the unused ILT stub 0x00010F6E, which has no rel32 caller.
- Matched `ScriptActions::doNamedFlash` 0x002EE7C0 and `doTeamFlash` 0x002F3E90 store
  the flash colour at drawable+0x164 and the flash count at drawable+0x160
  (see `002ed3d0-drawable-setflashcount.md`).
- `tools/ilt_oracle.py` contradicts `?setFlashColor@Drawable@@QAEXH@Z` at this address.
  The name was already in `ilt_contradicted_baseline.txt`.

The old row came from ScriptActions.cpp's stale Zero Hour `doNamedFlash` copy, whose
Drawable.h view puts the colour at +0xD0. That copy also emitted a wrong
`?setFlashCount@Drawable@@QAEXH@Z` COMDAT (+0xCC). The real body lives in
ScriptActions_doNamedFlash_Thunk.cpp, so the stale copy is removed.

Inference: the owning class stays unknown, so the row keeps an address-derived name.
