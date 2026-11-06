# AssetList pointer-set destructor replacement

BFME 1 1.03, base `5c1834555e`. The pinned BFME 2 donor
`dbde7dbe3be16481b2c8d6f2f9577bc322f6b7ce` identifies the pointer-key
view in `Code/Libraries/Source/assetmanager/AssetPointerSetFind.cpp`.
The BFME 1 object for `game/Libraries/Source/assetmanager/AssetRegistryKeySet009EF7D0.cpp`
already emits the corresponding 124-byte STLport destructor at
`0x00140950`. The native `add_match.py --replace-rva` trial verified
3/3 rows in the provider under its existing MSVC options.

The expanded pre-commit scope failed 3/26. The three callers still
relocate to the generated `_Rb_tree<Gen_t_00140950_k4>` destructor name.

- `W3DRoadBuffer::addMapObjects` in `W3DRoadBuffer.cpp`
- `Rva007896C0::bindHAnim` in `W3DAptComponentView3D.cpp`
- `Image::load` in `ImageLoad.cpp`

The replacement and its verdict were reverted. Before retiring the
old definition, reconcile these consumers and verify their existing
relocations and unwind paths together. The separate S4 array consumer
still spells `Rva0077CDE0ArrElem::~Rva0077CDE0ArrElem`, whose ILT
`0x0000E746` reaches the same retail body. The local link previews timed
out, so there is no new linked-byte result.
