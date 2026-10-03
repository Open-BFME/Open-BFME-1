# Include the D3DX cube-texture error-tail back edge

The1787B claim at00A0009A cuts the second byte of JMP at00A00794.
JE branches at00A0019B,00A00247,00A003BF,00A004B4,00A005AB and
00A006A0 all reach00A0078F, which loads HRESULT8876086C and jumps
back to the shared cleanup at00A00762. The earlier RET12 at00A0078C
is not the physical end. Original d3dx9tex.obj ends after that back edge
at1788B; next function starts00A00796. Local PE/Ghidra agree.

The complete archive comparison has1636concrete matching bytes; archive
relocations remain masked under the existing verifier. Retain the original
_D3DXFillCubeTexture@12 identity and library provenance; no new source,
caller declaration, callee binding or pin is introduced.
