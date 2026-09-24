# Retail identity of 0x0092C350

The retail body at `0x0092C350` reads `Container` from `this+0x84` and calls virtual slot `0xe4` only when `Container` exists.

The body passes that call result and both stack arguments to `Model` at `this+0xc8`.

The wrapper source in `Code/Libraries/Source/WWVegas/WW3D2/mesh.cpp` names this operation `MeshClass::Get_Deformed_Vertices(Vector3*, Vector3*)`. The header `Code/Libraries/Source/WWVegas/WW3D2/meshgeometry.h` declares its three-argument target as `MeshGeometryClass::get_deformed_vertices(Vector3*, Vector3*, const HTreeClass*)`.

The corrected wrapper matches all 53 retail bytes except the relocated call operand and places that call at the same instruction.
