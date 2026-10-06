# The 0x28-byte member transferred through ILT 0x00026DD7 is Rva001CB270BitFlags

Two matched callers transfer a 0x28-byte member with one direct call to the
incremental-link slot 0x00026DD7:

- `?bfmeSaveBH@BfmeOwnVUM@@QAEXPAVBfmeAgentBH@@@Z` (0x00361030, member +0x50)
- `?bfmeSaveBH@BfmeHostBH@@QAEXPAVBfmeAgentBH@@@Z` (0x00297040)

`tools/callees.py` resolves that slot for both: `0x26dd7 -> 0x1cb270`.
0x001CB270 is the matched row `?xfer@Rva001CB270BitFlags@@QAEXPAVXfer@@@Z`
(Rva001CB270BitFlagsXfer.cpp, 497 B), a 304-bit named-flag transfer whose
object is 0x28 bytes, the size both callers reserve for the member.

The callers used to name the member's class `BfmeSubOneBH` and the method
`bfmeSaveBH`. That spelling has no body: its only trace is the symbols.csv pin
`?bfmeSaveBH@BfmeSubOneBH@@QAEXPAVBfmeAgentBH@@@Z,0x00026DD7`, which names the
ILT slot, not a function. No object defines it, so the caller files could not
link. `BfmeSubOneBH` was an invented stand-in, not a descriptive name with
evidence; the callers now use the class and method the matched callee row
carries.
