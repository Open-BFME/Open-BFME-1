# VertexMaterialClass::Get_UV_Source at 0x00921270

`VertexMaterialClass::Get_UV_Source(int stage)` returns `UVSource[stage]` in `vertmaterial.cpp`, the file that defines this class's methods. `tools/probe.py`, the byte-comparison tool, compiles the method to the 11-byte retail body at `0x00921270`.

Retail `MeshModelClass::post_process_fog` at `0x0096EE60` calls `0x00921270` at offsets `+0x202` and `+0x211`. At `+0x202`, the caller passes the material-array accessor's result in the `ECX` register and pushes stage 0. At `+0x211`, it passes `Material[1]` in `ECX` and pushes stage 0. The `+0x202` call returns the UV source that the caller later passes to the `Set_UV_Source` method pinned at `0x00921250`. The `+0x211` call invokes the same getter on `Material[1]` in the source fallback branch, which discards its return value.

`reverse/functions.csv`, the ledger of matched names and byte ranges, assigns this range to `?dup_00921270@@YAXXZ` and records `object-symbol=?getNthExtraOffset@MultiIniFieldParse@@QBEIH@Z`. The exact method body and the caller's receiver, argument, and later setter call identify the body as `VertexMaterialClass::Get_UV_Source`. Replace the placeholder row and pin that method to `0x00921270`.
