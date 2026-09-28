# Name correction for 0x00763AC0

The earlier bank used `ModelDraw` in the owner name and gave semantic names to fields at 0x00763AC0. Its own comment says the retail image does not prove the owner or method name. The bank also had no caller, vtable, string, or BFME layout evidence for its field labels.

The caller at 0x00767B30 calls this body through ILT 0x0002E7B7 and passes a render object and a float output pointer. The caller leaves its owner address-derived and does not name this body's owner or members. The file that checks witnessed member layouts, `tools/name_oracle.py`, reports no BFME layout for `Rva00763AC0ModelDraw`. It also reports no witness for `MeshClass+0xC8` or `MeshModelClass+0x24`. The old local declarations came from the same reconstruction, so they cannot prove the names they contain.

The revised bank keeps the address in the class and method names. It names unproven fields by their byte offsets.

| Earlier field name | Replacement |
| --- | --- |
| `m_array` | `m_00C` |
| `m_drawable` | `m_field_008` |
| `m_model` | `m_0C8` |
| `m_moduleData` | `m_field_004` |
| `m_polyCount` | `m_024` |
| `m_polys` | `m_02C` |
| `m_transform` | `m_008` |
| `m_vertexCount` | `m_028` |
| `m_vertices` | `m_030` |
| `vertex` | `m_000` |
| `x` | `m_000` |
| `y` | `m_004` |
| `z` | `m_008` |
