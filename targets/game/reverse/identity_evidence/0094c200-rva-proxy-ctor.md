# Rva0094C200Proxy ctor owns the 11-byte body at 0094C200

Retail image: inputs/baselines/bfme1/retail-1.03-unpacked lotrbfme.exe.

## Boundary and ABI

0094C200: 8b c1 8b 4c 24 08 89 08 c2 08 00 (mov eax,ecx; mov ecx,[esp+8];
mov [eax],ecx; ret 8), 11 bytes (tools/dis_retail.py). Receiver in ECX, two
stack dwords, the first ignored, the second stored at this+0, returns this.

## Identity

The previous row ?dup_0094c200@@YAXXZ was a gen-alias whose object symbol
(GameAudio.cpp's _STLP_alloc_proxy<unsigned int, hash node of
AsciiString->AudioEventInfo*> ctor) is shared by hundreds of byte-identical
11-byte dup rows; the alias proves only the byte shape, not this address's
identity. Its only direct caller is the matched Rva0094C4F0Owner ctor at
0094C4F0 (tools/callees.py 0x0094C4F0 35), which passes an empty allocator
temporary and 0. No specialization is provable, so the body takes the
address-derived name the caller already declares:
??0Rva0094C200Proxy@@QAE@ABURva0094C4F0Allocator@@I@Z.
