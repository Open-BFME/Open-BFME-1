# LAN-start handler argument-slot audit

The contiguous retail body is RVA0068BFA0 through RET8 at0068C0BA; INT3 begins
0068C0BD, proving285 bytes. Let S be ESP after the EH record and the two saved
registers. The dead message argument is S+18, and sender-address argument is
S+1C. Offsets in this note are hexadecimal.

At0068BFFD, LEA EAX,[ESP+1C] passes the first options result slot: S+1C.
The call at0068C002 is followed by ADD ESP,4. The serialized-info callback
consumes its four stack arguments, returning ESP to S. The successful arm
constructs and releases its short result at S+18 (0068C030 and0068C03D).

In the failure arm,0068C052 first PUSHes ECX, reserving the by-value wide
string. ESP is now S-4. Therefore0068C058's MOV [ESP+1C],ESP writes S+18,
NOT S+1C. Its copy constructor consumes the source pointer; OnPlayerLeave
consumes the four-byte string argument. The final options cleanup at0068C099
again takes LEA ECX,[ESP+1C], now S+1C.

This refutes the earlier re_attempts claim that the failure arm overwrites
the still-live options string. The two slots are distinct; the old claim
compared identical ESP displacements without accounting for PUSH ECX.

The served bank remains286B/201 differing bytes. Native ascii_string.h and
unicode_string.h preserve that result. Exposing the actual wide forwarding
constructor also leaves the caller unchanged; that constructor independently
probes exact for the19-byte body at000682C0. The existing extra local/frame
slot remains a code-generation problem, not evidence of overlapping live
retail objects. No production source or pin is changed.
