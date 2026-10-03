# Complete retail string operands at 0x00718A10

The existing 260-byte body has the following mismatched string operands. The strengthened verifier from reviewed commit 7bfaf884e4 detects each missing suffix by comparing the complete object literal including its NUL terminator. Local retail PE and independent Ghidra memory reads agree on the corrected bytes.

- Body operand +0xA8 points to VA 0x1120cb8: `"Failed to allocate memory to load shader\n"` must be `"Failed to allocate memory to load shader\n "`. Complete retail bytes: `4661696c656420746f20616c6c6f63617465206d656d6f727920746f206c6f6164207368616465720a2000`.
- Body operand +0xE8 points to VA 0x1120c98: `"Failed to create shader\n"` must be `"Failed to create shader\n "`. Complete retail bytes: `4661696c656420746f20637265617465207368616465720a2000`.

Retain the existing body name, call ABI, extent and pins; this is a correction of the independently identified literal operands, with no new semantic identity claim. AGENTS.md requires matched rows to be backed by real source and byte verification. A prefix ending before the retail terminator does not satisfy the complete string operand.

Adopt the existing Common/file.h and Common/FileSystem.h declarations for File, FileInfo and FileSystem in this TU. Keep shared headers unchanged; the scoped byte gate validates their use at this call site.

Use the existing zhcanonascii include bridge so the vendor headers see the same canonical BFME AsciiString already used by this source. This avoids the incompatible standalone Zero Hour string declaration; no shim is edited.

The vendor File header has an extra inherited virtual slot relative to this BFME caller. The first adoption build matched every byte except the read/close displacements (+0x10/+0x0C versus retail +0x0C/+0x08). Keep the existing header type and express those two dispatches through an address-scoped virtual-call view at the independently proven retail slots; do not redefine File or modify shared headers. The TU enables STLport for FileSystem.h and uses the existing canonical AsciiString bridge.

VC7.1 rejects free-function __thiscall pointer syntax (C4234); the narrow Rva00718A10Dispatch view supplies the member-call convention without redefining the canonical File or claiming a semantic class identity. Only slots +0x08 and +0x0C are used. The header remains the definition of File and FileSystem; this separate view records the positively different BFME dispatch ABI.

## Header adoption is not a FileInfo identity change

The name checker falsely pairs removed TU-local `FileInfo` with newly added `Rva00718A10Dispatch`. `FileInfo` still exists under exactly that name in Common/FileSystem.h (four Int members: sizeHigh, sizeLow, timestampHigh, timestampLow), and the function still declares `FileInfo fileInfo` and passes it to getFileInfo. The new dispatch view has four virtual declarations, no FileInfo fields, and is used only to call two File slots. These are unrelated types; no FileInfo identity was renamed. The exact before/after source hash correction follows docs/naming_evidence.md's explicit provision for false pairings, not a reusable exemption.
