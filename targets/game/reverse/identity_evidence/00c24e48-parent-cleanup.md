# RVA 00C24E48 cleanup ownership

The 41-byte range is a compiler cleanup for the existing native destructor
at RVA `00465430`, not a standalone function. Retail evidence:

- The parent's prologue pushes handler VA `01024E71` at RVA `00465433`.
- That handler loads FuncInfo VA `01215018`.
- FuncInfo has two states and unwind-map VA `01215008`.
- State 1 at VA `01215010` contains predecessor 0 and action VA `01024E48`.
- The action conditionally adjusts the saved receiver at `[ebp-10h]` by
  `218h`, then tail-jumps at RVA `00C24E6C` to ILT `00021FC1`.
  Its extent ends at `00C24E71`, the separately referenced handler.

`tools/eh_info.py 0x00465430` reproduces the ownership chain. Ghidra MCP
`read_memory` of VA `01215008` agrees with the retail PE bytes; its unanalysed
xref index reports no references to the action, so the actual table is the
ownership evidence.

The existing `Rva00465430AptGameWindowDestructor.cpp` emits this action as
`$L902` in the parent's EH group. The scoped build verifies the parent and
its deleting destructor; add_match verifies the complete cleanup including
its tail-jump binding. No new class or method identity is asserted.
