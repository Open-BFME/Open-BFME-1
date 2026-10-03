# Laser texture-vector audit: AsciiString is the wrong element contract

The matched W3DLaserDraw constructor at RVA 0x00757E70 is 982 bytes:
RET 8 is at 0x00758243 and INT3 starts at 0x00758246. Ghidra memory reads
and the unpacked retail image agree. The current constructor byte-verifies,
but its local AsciiString definition is also used as a texture-copy surrogate.

At 0x00757FDC retail increments a WORD at the pointed-to object +4. The
source reproduces this by casting vector<BFMEWaterTrackTextureHandle> to
vector<AsciiString>, with a local AsciiString copy constructor that increments
an unsigned short at +4. The canonical StringBase<char> header instead puts
a DWORD reference count at +0 and a WORD string length at +4. These are
different ownership contracts, not interchangeable names for one type.

The overflow branch calls ILT 0x000112C0, which routes to 0x00757C70.
That 268-byte body is currently claimed as vector<AsciiString>::_M_insert_overflow.
Its four calls through ILT 0x0004725D reach 0x00756D90. That 25-byte leaf
copies a pointer and increments WORD [pointer+4] at 0x00756DA4, then returns
at 0x00756DA8 before INT3. Its current _Construct<AsciiString,AsciiString>
claim is backed by LadderDefs.cpp's reconstructAsciiString, which manually
performs that same incompatible pointer/WORD operation.

The September review independently established the other half of this
family: clear 0x007578F0 releases texture handles through 0x0005CC00;
AsciiString clear 0x000630B0 instead reaches StringBase<char>::releaseBuffer.
See [the prior review](20260927-router-worker-review.md#shared-blocker-false-asciistring-container-identity).

A constructor candidate using canonical ascii_string.h and direct
m_textureVector.push_back(handle) is preserved as measured source in
`attempt_history/0x00757e70/b1a81bb8dee69cc9e1117c704b9e74de0fa8bfb5e802e7e8d15e0ef37180c2c2.json`.
The preferred attempts/ stash was removed as required by check_csv: an
already matched real C++ row cannot have a preferred open-work stash.
Probe and automatic bank measurement report 982-byte exact shape, score 1.0
modulo relocations. Strict verification rejects one unresolved typed texture
vector overflow call. The candidate's four float constants and nine DIR32
references pass independent checks. Production source was restored.

Do not pin that new template name to the old AsciiString claim just to pass
the gate. Repair the contradictory helper identities and their dependent
callers together, using address-derived identities unless a genuine original
element type is independently proved. This note does not claim such a name,
change a ledger row, or promote the archived constructor.
