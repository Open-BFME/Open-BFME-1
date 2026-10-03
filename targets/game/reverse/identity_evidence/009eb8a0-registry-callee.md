# Opaque 009EB8A0 and its one callee binding

The caller is a36-byte native thiscall method. The matched base constructor009EB7D0 installs tableVA01145744 at009EB7F0; table slot11 atVA01145770 points directly toVA00DEB8A0. Derived prototype tables share that slot, including the independently checked tablesVA0113E6F0 and0113E7B0. Ghidra raw bytes, its created36-byte function, and independent PE/Capstone decoding all agree on the caller extent through RET009EB8C3, then INT3. No full owner or method name is inferred.

Caller009EB8A0 saves incoming receiver ECX in EAX, reads flags at receiver+4, masks00FF0000 and returns if equal00030000. It then loads ECX from globalVA0134FAAC, tests it, pushes the original receiver and calls009F0FA0 at009EB8BE. The already-recorded DIR32 spelling is g_q1Receiver0134FAAC of Q1Receiver0134FAAC; no new global or alias is introduced.

The callee ABI was checked independently of the candidate probe and the old bank:

- At009F0FB9, after the actual EH prologue and PUSH ESI, [ESP+34] is the sole incoming stack argument. The callee immediately reads argument+8 at009F0FBD and flags+4 at009F0FCF. It tests the same00FF0000 state mask against00030000.
- At009F0FC3 it preserves incoming ECX in EDI and uses that receiver's +60 critical section, +190 set, and +78-family queues. This is the same physical registry receiver used by the already matched Q1Receiver0134FAAC family and existing global-forwarder TUs.
- At009F141A it stores the original argument pointer in a local;009F1424 writes that pointer into a registry deque, or009F1431 passes its address to009EF0D0. The existing address-derived Rva009EF0D0Element name is only a pointer view of this element family, not a semantic asset-class claim.
- All normal branches share the restoring epilogue009F143B..009F144B, ending RET4. The executable body is1198 bytes. Two alignment bytes and owned switch data extend to009F146C, the1228-byte existing generated claim, followed by INT3. Ghidra independently reports a void thiscall function with one pointer argument. The early return paths preserve incidental values rather than construct a return result.

The new pin m009F0FA0(Q1Receiver0134FAAC*, Rva009EF0D0Element*) expresses exactly that thiscall ABI and keeps the callee address in its name. It also agrees with the existing unlanded bank spelling, but that bank is not the proof. No second function row is added for009F0FA0, no generated source is edited, and no semantic identity is asserted. The initial caller gate failed only on this unresolved REL32; the caller's existing global DIR32 was already exact.
