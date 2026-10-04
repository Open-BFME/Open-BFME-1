# RenderObjClass virtual stubs live at the addresses retail's vtable reaches

Retail's RenderObjClass vtable is at VA 0x0113BD88 (file offset image 0xD3BD88 in
`lotrbfme.exe`). The slot addresses, followed through the 5-byte ILT `jmp` where the
slot holds one, are authoritative for `RenderObjClass::<method>`. These bodies are
byte-identical to other same-shaped bodies, so a byte match proved nothing about
which copy carried the name; the ledger had put several names on copies that no
vtable references.

| slot | method | retail slot value | final body | old (wrong) claim |
| --- | --- | --- | --- | --- |
| 19 | Set_Container | 0x0091F8E0 (direct, 22 vtables share it) | 0x0091F8E0 | 0x006F6CB0 |
| 23 | _bfme_ro_set_98 | ILT 0x0000FEED | 0x006CF370 | 0x002ED1F0 |
| 24 | _bfme_ro_get_98 | ILT 0x000408D6 | 0x006CF380 | 0x0045C0D0 |
| 69 | _bfme_ro_set_8c | ILT 0x00003EAE | 0x006CF540 | 0x0060D210 |
| 88 | Get_Snap_Point | ILT 0x0001AD5C | 0x006CF640 | 0x006C8CC0 |
| 44 | Set_Animation(HAnimClass*, float, int) | ILT 0x00048775 | 0x006CF440 | 0x006CF660 (icf-owner row) |

## Evidence

- Every old address is reached only by its own never-referenced ILT stub
  (`j_000360bb`, `j_0002882b`, `j_0000dbe3`, `j_00010b77`, `j_0003ef54`); a scan of the
  whole image for absolute and rel32 references finds nothing else pointing at
  0x2ED1F0, 0x45C0D0, 0x60D210, 0x6C8CC0 or 0x6F6CB0. They are other classes'
  same-shaped bodies (0x2ED1F0 is already `ParticleSystemManager::setLocalPlayerIndex`).
- Each new address is the one the RenderObjClass vtable slot (and, for slot 19, 22
  derived vtables at the same slot) names, and its bytes are the stub the header
  declares: `mov eax,[esp+4]; mov [ecx+0x84],eax; ret 4` (Set_Container, +0x84 field),
  `... [ecx+0x98] ...` (set_98), `fld [ecx+0x98]; ret` (get_98), `... [ecx+0x8C] ...`
  (set_8c), `ret 8` (Get_Snap_Point(int, Vector3*)), `ret 0xC` (Set_Animation, three
  dwords). The ZH header order and the Animatable3DObjClass overrides at
  0x982190/0x9822C0/0x982170/0x982330 sit in the same slot order as 0x6CF440/450/460/430.
- 0x00920410 versus 0x0097E9E0: the RenderObjClass vtable slot 67 is 0x00920410, also
  shared by a second vtable, while 0x0097E9E0 is referenced only by the
  ParticleEmitterClass vtable (0x00D3EE88) beside its own Get_Obj_Space_Bounding_Sphere
  at 0x0097E9C0, so the two names swap addresses.
- No ICF in retail: one identity per address. The displaced copies keep honest
  address-derived names.
