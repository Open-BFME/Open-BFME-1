# Indexed audio entry element contracts

The parent independently decoded these retail bytes before adding bindings:

- ILT 0004A818 jumps to 0069C300. The 23-byte body loads destination from `[esp+4]`, checks it for null, loads source from `[esp+8]`, copies exactly two dwords, and returns without stack cleanup. Callers including 006A3DB0 remove eight stack bytes. This is the two-argument cdecl placement-copy contract emitted by STLport `_Construct` for the non-POD eight-byte element.
- ILT 000251D0 jumps to 006A3DB0. This 306-byte vector overflow body computes counts with `sar eax,3`, sizes with `lea eax,[ecx*8]`, advances element pointers by eight, calls 0004A818 four times across its copy paths, and returns with `ret 0x14`. The receiver is the three-pointer vector; five stack parameters match the vendored `_M_insert_overflow` declaration. Its already-matched native STLport implementation independently confirms that signature.
- Dispatcher 006A8210 reaches 006A8120 with receiver at entry+0xB8 and two integer arguments. Matched audio callers 006AE2C0 and 006B3F90 pass an audio-info pointer whose +0x8C/+0x90 words delimit the input records.

The prior candidate reused `ModelConditionInfo::HideShowSubObjInfo` solely to resolve existing pins. Those names are not evidence. The existing graphics spelling implies an AsciiString member, whereas the independently decoded copy performs two plain dword moves and no reference-count operation. The replacement retains an opaque address-derived element name, `Rva0069C300Element`, without asserting semantics for either word.

The two new bindings point to the actual bodies, 0069C300 and 006A3DB0. They do not claim the ILT addresses as function residences. The resolver derives the retail thunk routes from the image. Existing graphics-name claims are left for a separately scoped identity audit; their presence is not used as proof of the new element's name.
