# Name correction for the 0x005406E0 reconstruction

The old `attempts/0x005406e0.cpp` file was a score-0.39 draft, not a recovered
identity. The ledger still named the body `?d_005406e0@@YAXXZ`. The draft's
`enterLobby`, `AptMovieHost`, and `prepareLobby` labels were hypotheses derived
from the guessed behavior and field accesses in that draft.

## `enterLobby` to `Rva005406E0`

The retail selector scan walks the APT constructor registration table from
`AptScreenFactories.cpp`. Its seven remaining open rows are at 0x005151F0,
0x00514DA0, 0x0051DB30, 0x005625C0, 0x005694E0, 0x00569420, and 0x000FBA80;
0x005406E0 is not registered there. The scan therefore supplies no callback
identity for this body. No matched caller, vtable slot, symbol pin, or selector
ties the method name `enterLobby` to the address. Its UI strings suggest that
behavior, but the source name must keep the address until stronger evidence
appears.

## `AptMovieHost` to `Rva005406E0Field34`

Retail reads a pointer at `this+0x34`, then a dword at `pointer+0x250`. The
name oracle reports no witnessed `BfmeAptScreenOnlineCustomMatch` layout at
0x34. No caller, vtable, RTTI name, or field table identifies the pointed-to
type as `AptMovieHost`; that class name existed only in the draft. The new
type records the two observed offsets without claiming an owner or meaning.

## `prepareLobby` to `Rva005406E0`

At RVA 0x0054083C the retail body calls ILT 0x0002F4AF, which targets the
matched body at 0x005397D0. Its identity evidence names that callee
`Rva005397D0AptScreen::rva005397D0PopulateGroupRoomListbox` and explicitly
leaves its owning class unknown. This refutes the draft's invented
`BfmeAptScreenOnlineCustomMatch::prepareLobby` callee. The reconstructed body
now calls the proven address-derived helper directly.
