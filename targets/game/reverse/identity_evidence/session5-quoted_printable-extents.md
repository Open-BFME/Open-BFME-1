# Complete the quoted-printable encoder epilogue

The 282-byte claim at00106150 cuts ADD ESP,10h at00106269 after its
first byte. The unchanged native body continues through that instruction
and RET0010626C; INT3 padding starts0010626D, proving285B. Local retail
PE and Ghidra memory at00506260 agree through the complete return.
There is no overlapping live claim. The original COFF full span matches
285B with no unresolved relocations; normal scoped and complete-reference
verification confirm it again in the repair tree.

Keep the existing AsciiStringToQuotedPrintable identity, whose source is
an adapted EA QuotedPrintable.cpp, and all current source/pin declarations.
This corrects only an independently contradicted extent. AGENTS.md requires
matched rows to cover the complete byte-verified body, not an instruction
prefix. No source, header or semantic-name edits are made.
