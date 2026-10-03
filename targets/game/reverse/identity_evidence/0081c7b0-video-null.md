# VideoPlayer slot12 null return

The VideoPlayer table at VA0112CCC0 points at RVA0081C7B0 in slot12.
Matched complete destructor0081C590 installs that table, and named
init/addVideo/removeVideo/getVideo anchor this owner family independently.
Ghidra read_memory at00C1C7B0 agrees with the baseline's full14B body:
LEA ECX,[ESP+4]; CALL00887940; XOR EAX,EAX; RET8, then two INT3 bytes
before the next aligned function. This is not a tail inside the preceding
function.

The matched315B PlayMovieAndBlock at004E2D50 independently proves the
call contract. At+19 it pushes a scalar zero; at+1B..+33 it constructs a
four-byte by-value AsciiString on the stack. At+34..+3E it loads
TheVideoPlayer, reads the vptr and calls slot+30. It retains EAX as a
VideoStreamInterface pointer, tests null and subsequently dispatches the
stream interface. Its existing typed slot declaration has an AsciiString
and Int argument. The native ZH VideoPlayer::open twin also returns a null
VideoStreamInterface pointer, but lacks BFME's second scalar parameter.
No meaning for that unused scalar is invented here.

Production includes the canonical BFME ascii_string.h, whose inline
destructor reaches the established StringBase<char>::releaseBuffer at
00887940. The callee inventory independently names that exact method.
The argument lifetime emits the complete retail cleanup automatically;
no manual storage, destructor alias, header edit or new pin is needed.
The entry remains address-qualified despite the existing caller's open
label. /O2 /MD gives14B and one strictly verified canonical call.
