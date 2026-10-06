# ControlBar::populateObserverList is the 0x004A9CD0 body, not its ILT thunk

The ledger held `?populateObserverList@ControlBar@@QAEXXZ` on the 5-byte
incremental-link thunk at 0x00036BA1 (`jmp 0x004A9CD0`), written as a C++
member forwarding to a TU-local `ControlBarPopulateObserverListShim::populate`
that owned the 1,061-byte body.

- EA's label for 0x004A9CD0 is `ControlBar::populateObserverList`
  (ea_evidence.csv, chain/strong).
- `tools/ilt_oracle.py check '?populateObserverList@ControlBar@@QAEXXZ' 0x004A9CD0`
  is CONFIRMED exact: the decorated name hashes into the window of ILT slot
  0x00036BA1, the thunk that jumps to this body.
- Retail was linked without identical-COMDAT folding, so the name has one
  body: the function the thunk reaches.

The body row takes the real name (ControlBarObserver.cpp defines it as a
ControlBar member), the thunk row becomes the address-claimed
`?j_00036ba1@@YAXXZ`, and the caller pin at 0x00036BA1 carries
`route=0x004A9CD0`.
