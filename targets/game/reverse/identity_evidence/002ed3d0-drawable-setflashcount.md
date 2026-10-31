# 0x002ED3D0 is Drawable::setFlashCount (13 B)

Facts from BFME 1 retail:

- 0x002ED3D0: `mov eax,[esp+4]; mov [ecx+0x160],eax; ret 4` (13 bytes, int3
  follows). The row was the gen-alias `?dup_002ed3d0@@YAXXZ` whose
  object-symbol was already `?setFlashCount@Drawable@@QAEXH@Z` from
  ScriptActions_doNamedFlash_Thunk.cpp.
- The matched retail ScriptActions::doTeamFlash (0x002F3E90, 282 B,
  ScriptActions_doTeamFlash_Thunk.cpp) inlines `draw->setFlashCount(count)`
  as `mov [ebp+0x160],edi` (+0x104): Drawable's flash count is this+0x160.
- 0x006FCF50 stores to this+0xCC. It is claimed by the matched
  `?setFlashCount@CommandButton@@QBEXH@Z` (ControlBarCommandProcessing.cpp).
  A second row named `?setFlashCount@Drawable@@QAEXH@Z` sat on the same
  address, sourced from ScriptActions.cpp, whose Zero Hour Drawable.h view
  puts m_flashCount at 0xCC; it verified only because both setters are the
  same 13-byte store shape. That row is retired (deleted_rows.csv): retail
  links without identical-COMDAT folding, so 0x006FCF50 has one identity.

Structural inference: the CommandButton row keeps 0x006FCF50 (its const
mangling and the ControlBar caller context); the Drawable name follows the
+0x160 store proven by the matched doTeamFlash body.
