# 0x007F9D00: FeslConnectionHandler slot 3, method name unproven

Retail body 0x007F9D00..0x007F9FC6 (710 bytes, `ret 4`), byte-matched as
`FeslConnectionHandler::rva007F9D00(Rva00800E50Header *)`.

## Owning class

- The Rva007F9B80 constructor stores vtable 0x0112BAD0 at +4 of the FESL
  transactor. Slots 0 and 1 of that vtable are the matched
  `FeslConnectionHandler::onConnectionMade` (0x007F9140) and
  `onConnectionBroken` (0x007F9170). Slot 2 is the "conn err %d" handler
  (0x007F91A0), slot 3 is this body, and slot 4 is the scalar deleting
  destructor. So this body runs with `this` at the transactor's +4
  subobject, which is the FeslConnectionHandler view.
- Consistent with that, it calls the transactor's matched methods with
  `lea ecx, [edi-4]`: `onTxn` (0x007F96C0), `clearSlot` (0x007F9AC0) and
  0x007F97B0. It also reads the transactor's hub, dispatch depth and slot
  table at their offsets minus 4.

## Method name

The earlier bank named this `Rva007F9D00Owner::process` on an invented owner
class. Nothing supports `process`: no string, caller symbol or reference
source names the method. The body is a vtable slot reached only through
the handler interface. It keeps the address token `rva007F9D00`.

The checker also paired an unrelated `v0` (Rva007EB810Diag's first virtual
slot, which is still declared as `v0` in the new source) with the new
method name. That is a false pairing.
