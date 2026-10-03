# Native ListBox timer initializer 0x00C6BA30

Retail SHA256: 1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75.

Actual CRT XC slot VA012A5870 points to RVA00C6BA30. The body calls
USER32 GetDoubleClickTime through IAT VA01359000, stores EAX to VA012F3640,
and returns at +0x0B, followed by four INT3 bytes. Its complete extent is 12 B.
The SDK API is UINT WINAPI GetDoubleClickTime(void): no arguments, uint32 return.
The canonical GadgetListBox.cpp naturally emits _$E14 for its timer initializer;
the logical ledger identity retains the target address and does not claim an
original C++ function name. The native _$S15 CRT pointer binds this exact body.

Canonical source originally used a TU-static UnsignedInt doubleClickTime.
Pristine GeneralsMD Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBox.cpp
line75 authenticates that established name; retail API/store supports its meaning.
The reconstructed matched consumer had an address-derived extern spelling
for the same VA012F3640 cell. Preserve the established doubleClickTime name: the
producer becomes external and the consumer extern/read adopt it. The existing
DIR32 mapping is renamed to the canonical actual COFF symbol at the same address;
no second mapping or data cell is added. No additional storage, alias, type, header,
pin, wrapper or manually authored CRT body is added.
Canonical full GadgetListBoxInput output is 2158 B versus retail 3495 B; therefore
its existing matched fragment is not rehomed.

The timer VA012F3640 is aligned 4 and lies in the retail .data virtual tail:
loader zero before initialization. The native initializer writes exactly one
DWORD, subsequently read by the proven consumer. Supported add_data_match
independently proves sizeof(::doubleClickTime)=4 with allocation
extent 4 under the actual build flags, and verifies the initial zero bytes.

Fresh producer gate: 138/138 functions and 24 DIR32 references. Corrected
consumer gate: 2/2 functions and 29 DIR32 references. Whole native-object CRT
preview has exactly one common XC entry, no extra/unresolved/out-of-order entries;
missing 482 other XC entries is expected for this single-object preview and is
not a whole-program CRT or link success.

Broad data_check baseline and candidate both exit 1: 1 verified, 45 contradicted,
9 unverified. Exact contradiction sets are identical, with zero introduced and
zero resolved failures. These pre-existing failures are retained, not ignored.
A strict supported data row verifies the 4 B timer separately; full link remains
unmeasured. Independent fresh_lifts accepts the corrected source/COFF/consumer
hashes and physical shared-cell contract; normal commit hooks remain required.

The consumer retains its pre-existing five-byte UnicodeString release adapter.
Its COFF body is only a tail jump to the wide StringBase release routine; it has
zero incoming code/data relocations and one .debug$F SECREL reference. Retail
RVA008881D0 is the 134-byte wide implementation, not this unused wrapper. The
repository-supported absent-from-retail annotation records this precise discarded
COMDAT fact without changing code, adding a row, or broadening a baseline.
