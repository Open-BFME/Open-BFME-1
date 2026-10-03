# DefaultModuleName separator correction

All six existing DefaultModuleName::GetValue instantiations in
fx_particle_system_module_names.cpp reference VA `0x01111374` at body
operand `+0x27`. The unpacked PE and Ghidra both contain the nine-byte literal
`Default \0`, including the space before the category name. The old source
used the eight-byte literal `Default\0`. Its shorter non-NUL prefix passed
the old string verifier, which removed terminators before comparing.

| Template argument | RVA | Size | Final RET |
|---|---:|---:|---:|
| 0 | 0x005DFEE0 | 193 | 0x005DFFA0 |
| 1 | 0x005DFC50 | 193 | 0x005DFD10 |
| 2 | 0x005E0400 | 193 | 0x005E04C0 |
| 3 | 0x005E0170 | 193 | 0x005E0230 |
| 6 | 0x005DEDE0 | 193 | 0x005DEEA0 |
| 7 | 0x005E0690 | 193 | 0x005E0750 |

Every RET is followed by INT3. These are existing identities and extents;
this finding changes neither. The common template initializer is the single
source correction, rather than six independently written bodies.

`docs/matching.md`, Relocations, requires literal strings to byte-equal the
referenced retail strings. Add the proven separator to the common source
literal. All six 193-byte bodies remain exact, and the stronger checker now
verifies six complete Default-space literals and six empty-string references.
A separate COFF/PE comparison checks each +0x27 operand and all nine bytes.
There is no new pin, ledger identity, or function-byte coverage.
