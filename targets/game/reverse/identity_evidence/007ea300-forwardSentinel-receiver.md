# RVA 0x007EA300 preserves its incoming receiver

The 20-byte retail body begins PUSH ECX, obtains its four-byte local with
LEA EAX,[ESP], pushes that pointer and stores -204 at [ESP+4]. Its CALL
at 0x007EA30D reaches 0x007EA0A0 without replacing ECX. POP ECX and RET
at 0x007EA313 close the extent. This is a zero-argument member forwarding
on its incoming receiver, not a free function calling a stdcall helper.

The independently source-backed 118-byte Rva007EA0A0Owner::notify(void*)
at 0x007EA0A0 saves ECX into ESI, reads receiver fields +0x254/+0x288/+0x26C
and the caller-supplied pointer, and ends RET 4. The source and identity in
GameNetwork/Rva007EA0A0Notify.cpp establish that address-derived owner.
The matching teardown 0x007EA120 likewise passes its real owner in ECX.

Both tails of the native 35-byte callback at 0x007F4740 move virtual slot0's
return EAX into ECX before JMP 0x007EA300. The non-null context uses its
embedded interface at +4; the null path zeroes ECX and dereferences it.
This independently proves the wrapper receiver survives and is meaningful.

Preserve the already established basename forwardSentinel under the proven
Rva007EA0A0Owner. Retire the free ?forwardSentinel@@YAXXZ claim and the
wrong ?helper@@YGXPAH@Z candidate pin at 0x007EA0A0. The old union-cast
member/stdcall source hid ECX's live ABI and did not prove a free identity.
No EA semantic class name is asserted, and no helper alias replaces it.
The current authoritative baseline is retail-1.03-unpacked lotrbfme.exe.

## Callback subobject and compiler proof

The matched registrar at 0x007F46F0 invokes virtual slot1 on its owner at
+0 and registers that same owner as the callback context. The callback
invokes slot0 through the interface at +4. Address-derived primary and
secondary virtual-interface declarations represent those independently
proven receiver offsets. A normal derived-to-secondary static_cast keeps
null null, then the virtual call deliberately dereferences null. The
original EA inheritance syntax remains unknown; this is the smallest
physical C++ interface model reproducing both native dispatch paths.
Three bounded hypotheses were tested. Literal null and explicit embedded
interface paths preserved behavior but failed the null-arm register shape;
the normal secondary-interface conversion passed strict full 35-byte and
two tail relocation checks. No assembly or retail byte embedding was used.

## Established callback basename

The registrar historically names its callback bfmeCbBZC. Preserve that exact
basename in the address-derived organizational scope Rva007F4740; it does
not claim an EA class or a hidden receiver. Its static two-argument cdecl
signature has precisely the native physical ABI. The unpublished global
Rva007F4740 draft failed the descriptive-name preservation hook, so only
that draft row and its tombstone were reverted with ledger_io before the
original generated row was replaced through add_match. No name exception,
semantic refutation of the old callback basename, alias or new pin was added.
