# RVA 0x008A6100: native spelling unknown, toString callback proven

The retail PE and GhidraMCP's `00 61 CA 00` search agree that the only
stored pointer to body VA 0x00CA6100 is the PUSH immediate at VA
0x00CA7784. There is no ILT to this body and no direct E8/E9 caller.

That instruction belongs to the already matched property lookup at RVA
0x008A73E0. Its case 7 lazily constructs a callback wrapper at RVA
0x00899FC0 with 0x00CA6100 as the argument, stores it in global
0x01337AB8, and returns that wrapper. The matched source's case mapping
was cross-checked against the retail instruction at VA 0x00CA7783.

The native perfect-hash lookup at RVA 0x008A44A0 uses table VA
0x012D5490 (loads at VA 0x00CA44C7 and 0x00CA44CE). Entry VA
**0x012D54D0** contains pointer **0x0113666C**, whose retail bytes spell
`toString`, and integer **7**. Thus this callback implements the toString
property served by that object. The other properties include load, send,
sendAndLoad, loaded, contentType, getBytesLoaded and getBytesTotal.

The body returns a pooled string-like value built by keyValuePairs at
RVA 0x00898D80 and append at 0x008927C0. Final RET at +0xEA and INT3 at
+0xEB establish 235 bytes. Its byte-identical twin at 0x008A62A0 does not
prove that their native names or owners coincide.

This establishes a script-facing callback role, not an original decorated
C++ identity. No native AptLoadVars type or callback spelling is claimed.
The current synthetic/string-owner declarations still need a coherent
typed conversion; no production source, pin or progress row changes here.
