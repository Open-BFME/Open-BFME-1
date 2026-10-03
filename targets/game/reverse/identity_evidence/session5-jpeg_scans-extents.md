# Include the final return in the D3DX scan-filling claim

The46B claim at00A62610 ends after POP EBP at00A6263D, omitting
RET4 at00A6263E. NOP padding starts00A62641, proving49B. Ghidra and
local PE agree. Original jcparam.obj has a64B COFF section, including
15NOPs beyond that return; claim only49B. All49bytes match without any
relocation slots. The earlier exploratory51B trial included two padding
bytes and is not the final extent. Retain the original archive identity,
member/release provenance and source; no pins or code changes.
