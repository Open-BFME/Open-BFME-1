# Complete retail string operands at 0x007F91D0

The existing 477-byte body has the following mismatched string operands. The strengthened verifier from reviewed commit 7bfaf884e4 detects each missing suffix by comparing the complete object literal including its NUL terminator. Local retail PE and independent Ghidra memory reads agree on the corrected bytes.

- Body operand +0x48 points to VA 0x112ba3c: `"req"` must be `"req "`. Complete retail bytes: `7265712000`.
- Body operand +0x5C points to VA 0x112ba34: `"res"` must be `"res "`. Complete retail bytes: `7265732000`.

Retain the existing body name, type declarations, call ABI, extent and pins; this is a correction of the independently identified literal operands, with no new semantic identity claim. AGENTS.md requires matched rows to be backed by real source and byte verification. A prefix ending before the retail terminator does not satisfy the complete string operand.
