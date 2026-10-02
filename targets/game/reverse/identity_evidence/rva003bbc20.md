# RVA 0x003BBC20 destructor

The retail body spans 145 bytes, ending in `ret` at `+0x90` and INT3 padding
at `+0x91`. The complete body and the following helpers were decoded from
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe` with Capstone.
No EA class or method spelling is asserted.

## Owner and destructor identity

The existing matched constructor `Rva003BD6D0::Rva003BD6D0` at `0x003BD6D0`
installs vtable VA `0x010ED8F8` and zeroes the pointer at `+0x0C`.
This destructor installs the same vtable at entry. That table's first slot
contains ILT VA `0x0040A920`, routing to the scalar deleting destructor at
RVA `0x003BC060`. The wrapper preserves ECX, calls ILT `0x000225AC` to this
body, conditionally invokes operator delete when its flag has bit zero set,
and returns the receiver with `ret 4`. These independent constructor and
vtable routes support reusing the existing address-derived owner name.

The final vptr store is VA `0x01073744`, using the existing `BfmeBaseVUQ`
ABI view and vtable binding. Its seven-byte destructor at `0x003BBB60`
consists solely of that same store and `ret`.

## Member lifetime and cleanup

`eh_info.py 0x003BBC20` reports two unwind states. State zero calls the base
cleanup via ILT `0x00036C9B` to `0x003BBB60`. State one addresses `this+0x0C`
and calls ILT `0x000362FF` to `0x000877B0`. The latter's complete 35-byte body
loads the member pointer, conditionally calls the decrement import on its
referent's `+4` field, then invokes virtual deleting-destructor slot zero
with flag one if the signed result is nonpositive. It does not clear the
member pointer. This agrees with the existing `ThingRef` native destructor
alias at that RVA.

The PE import directory independently names IAT VA `0x01358E54` as
`KERNEL32.dll!InterlockedDecrement`; the reconstruction uses its ordinary
`long __stdcall(long volatile *)` contract.

The first cleanup is the destructor body's explicit member reset: the zero
store at `+0x50` occurs only when the member was non-null. The second cleanup
is the member's automatic destructor and performs no zero store. The old bank
instead duplicated the operations manually, marked the pointer volatile,
and cleared it unconditionally twice. An actual reference member with an
inline reset method and destructor reproduces the two unwind states.
Calling its inline release method directly through the member, where release
uses `delete this`, preserves both retail null checks and produces all 145
bytes. No volatile or assembly code is needed.

`name_oracle.py` reports no witnessed layout for `Rva003BD6D0`, the old
`Rva003BBC20` owner, or the new address-derived reference-member view.
No shared header is changed, no new symbol pin is required, and the existing
constructor and helper ledger identities remain unchanged.
