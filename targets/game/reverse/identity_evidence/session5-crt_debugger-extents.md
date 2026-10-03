# Include the complete CRT debugger SEH epilogues

The old70/88-byte claims at009F75DC/009F7629 cut the final MOVZX at
009F761F/009F767E and omit CALL009F7EC3 plus RET009F7628/009F7687.
Original libc.lib error.obj defines77/95B code sections; local PE and
Ghidra independently agree through both final returns. Adjacent next
functions start009F7629/009F7688; there is no padding to include.

Retain the inherited archive symbols and member provenance. The unchanged
archive comparison agrees on61/79concrete non-relocation bytes over the
complete bodies; archive mode masks relocations and does not prove their
bindings merely by this comparison. This is a complete-span correction,
with no authored code, compiler settings, pins or identity changes.
