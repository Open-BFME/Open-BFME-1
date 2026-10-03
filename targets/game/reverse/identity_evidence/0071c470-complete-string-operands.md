# Complete retail string operands at 0x0071C470

The existing 696-byte body has the following mismatched string operands. The strengthened verifier from reviewed commit 7bfaf884e4 detects each missing suffix by comparing the complete object literal including its NUL terminator. Local retail PE and independent Ghidra memory reads agree on the corrected bytes.

- Body operand +0x278 points to VA 0x1120de0: `"shaders\\Shrubs_darken.vs"` must be `"shaders\\Shrubs_darken.vso"`. Complete retail bytes: `736861646572735c5368727562735f6461726b656e2e76736f00`.
- Body operand +0x290 points to VA 0x1120dc0: `"shaders\\Shrubs_lighten.vs"` must be `"shaders\\Shrubs_lighten.vso"`. Complete retail bytes: `736861646572735c5368727562735f6c69676874656e2e76736f00`.

Retain the existing body name, type declarations, call ABI, extent and pins; this is a correction of the independently identified literal operands, with no new semantic identity claim. AGENTS.md requires matched rows to be backed by real source and byte verification. A prefix ending before the retail terminator does not satisfy the complete string operand.
