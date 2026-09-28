The earlier bank called a local copy `object84`. That local copied `m_field84`, which the temporary `BfmeShadowMesh` view places at offset +0x84.

The layout witness has no member name for `BfmeShadowMesh` offset +0x84. `tools/name_oracle.py --class BfmeShadowMesh --offset 0x84` returned exit code 2. The body keeps `m_field84` as an offset label.

The new source reads `m_field84` for the guard and virtual receiver. `tools/probe.py` reports 66 bytes, 14 byte differences outside relocations, and 0.870 shape similarity. The source that declares `object84` emitted 64 bytes with 43 byte differences outside relocations and 0.826 similarity.

Retail loads the value at +0x84 into EAX, tests EAX, then copies it into ECX for the virtual call. The direct field version matches retail through that virtual call.

The matched `BfmeShadowBufferEntryUpdate` caller and the symbol pin at RVA 0x0092C390 identify `Get_Deformed_Vertices`. They provide no member name for offset +0x84.
