# RVA 0x007A8400: water polygon drawing route

The 2443-byte native body is reached through ILT 0x0003CB2D; its only caller
is 0x007AA86D inside 0x007AA820. At 0x007AA86A that caller pushes EDI and
at 0x007AA86B sets ECX = ESI, preserving its complete receiver for this helper.
It calls this path when byte [EDI+4] is set; otherwise it processes pairs of
12-byte vertices from [EDI+0x54], using count [EDI+0x58]. The caller traverses
a node list whose sentinel pointer is stored at receiver +0x2AC (the load at
0x007AA826). The sentinel itself is an allocated node, not an embedded field. These are native object/layout
facts; they do not recover a C++ owner or original helper spelling.

The caller is reached through ILT 0x000243B6 by matched address-qualified
wrapper 0x007A2330 at 0x007A2361, and by anonymous 0x007AAA30 at
0x007AAAAE. The wrapper toggles backface culling around its helper invocation.
The candidate calls the separately matched address-qualified water-shader
setup at 0x007A6460, allocates dynamic index/vertex buffers and issues triangle
draws. This establishes a water-polygon drawing role without proving an
original name. Neither the candidate's body nor its entry stub has a stored
pointer; no named vtable identity was found for the body.

Last native RET 4 at 0x007A8D88, followed by INT3 at 0x007A8D8B, establishes
2443 bytes and one stack word. All routes, receiver setup and complete extent
were checked against retail-1.03-unpacked lotrbfme.exe via pefile/Capstone.
The callee ledger still has two identities at 0x009EB7A0; no dependency pin is
added based on that ambiguity. Existing 2427-byte/1802-difference bank stays
unchanged; no source, pin or production ledger name is changed.
