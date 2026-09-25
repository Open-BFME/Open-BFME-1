# ControlBar adapter and owning-handle evidence

The matched caller at RVA 00588C70 (BfmeConv1022.cpp) loads the global
VA 012F33F8 and calls 004C1B60 through ILT 0003BCCD. That global is also
TheControlBar in independently matched UI callers. Body 004C1B60 calls
GameWindow::winGetStyle (478490) and GadgetButtonGetData (4BBEE0), then
constructs a 16-byte temporary with ControlBar at +4, GameWindow at +8,
and button data at +C. It installs table VA 010FD964. Its EH cleanup
C290E0 calls 4C1150, which installs the abstract base table VA 010EDAA0.

Table 010FD964 slot +4 routes through ILT 4526E to 4C1AE0. That body
allocates 16 bytes, copies the three fields and returns a four-byte
owning handle through a hidden result pointer (RET 4). Its consumer
4C15D0, offsets +1F4..+20D, extracts the pointer into a by-value stack
argument and clears the returned handle before invoking 4C1510.

The 96-byte body 4C1510 conditionally deletes the old pointee through
vtable slot zero with deleting flag 1, adopts the incoming pointer and
returns its receiver. EH cleanup C29060 destroys the by-value argument
through ILT 224D0 -> 499F30 if deletion throws. The complete 13-byte
499F30 body null-checks the pointer and calls that same deleting slot.
There is no reference-count field operation. A native virtual destructor
and an owning handle passed by value reproduce all 96 bytes, including
the cleanup frame that the prior raw-pointer argument omitted.

The former bank's virtual `release(int)` declaration is replaced by a
native virtual destructor; this is an ABI correction, not a loss of a
proven semantic method. The name checker aligns that removed declaration
with the new address-derived base class in its textual diff. Likewise,
the old clone bank's PartitionFilterPossibleToAttack attribution came
from an existing vtable label, not an independently named caller. Its
attack-type/Object/command-source field interpretation conflicts with
the witnessed ControlBar/GameWindow/button-data construction above.
The replacement retains 004C1AE0 in its adapter type and makes no
partition-filter or attack-behavior claim. Other existing ledger claims
using that disputed label are outside this bounded implementation.
