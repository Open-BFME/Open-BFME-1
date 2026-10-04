# 0x00271DB0 is AIUpdateInterface::xfer, not any Transport/Wander destructor

## Vtable-slot proof

Exactly one ILT stub targets 0x00271DB0: stub RVA 0x0043441
(`E9 6AE92200` -> `0x43441 + 5 + 0x22E96A = 0x271DB0`).

Retail vtable at VA 0x010BA8A8 holds that stub VA at slot 3 (+0xC). The table
is AIUpdateInterface's own primary vtable: both the matched ctor
(`??0AIUpdateInterface@@QAE@PAVThing@@PBVModuleData@@@Z` @ 0x0027F4B0) and the
matched dtor (`??1AIUpdateInterface@@UAE@XZ` @ 0x0027EF60) install it at
`[esi]` (+0), verified by disassembly (0x67F523 / 0x67EF81:
`mov [esi], 0x10BA8A8`).

Sibling slots confirm the table and the slot numbering:

- slot 0 -> stub 0x004FD4 -> 0x0027FAC0 `??_GAIUpdateInterface@@UAEPAXI@Z`
  (scalar deleting dtor: slot 0 is the dtor slot, as expected)
- slot 1 -> stub 0x0029CD5 -> 0x0027A5E0
  `?loadPostProcess@AIUpdateInterface@@MAEXXZ`
- slot 2 -> stub 0x000BC67 -> 0x0027F1C0 (6-byte literal getter)
- slot 3 -> stub 0x0043441 -> 0x00271DB0 (this body)

Per-family slot alignment: row 134039 (`?xfer@DozerAIUpdate@@MAEXPAVXfer@@@Z`
@ 0x002B7080) documents "Dozer primary vtbl slot3" and "calls
AIUpdateInterface::xfer@0x271db0". Slot 3 of AI Update primary vtables is the
`xfer` virtual; the derived override delegates to this base body.

## Callee proof

Direct-call targets decoded from retail [0x271DB0, +2099) via capstone,
resolved through stubs to ledger bodies:

- `?doXfer@AICommandParmsStorage@@QAEXPAVXfer@@@Z`
- `?xferSelfAndCurLocoPtr@Rva001B74D0Owner@@QAEXPAVXfer@@PAPAX@Z`
- `?xfer@Rva001CB270BitFlags@@QAEXPAVXfer@@@Z`
- `_xferGuardTargetTypes`
- `?xfer00401C70@Path@@QAEXPAVXfer@@@Z`
- nine calls into Xfer virtual slots (`Rva0010BE00@MidVirtualSlot90Receiver`
  family: xferVersion/xferSnapshot/typed transfers)
- StringBase/map/format helpers, `operator new`

The body is an Xfer serializer delegating to sub-object xfers. A destructor
would install a vtable; this body installs none (prologue is SEH + virtual
call `[eax+0x28]` + base xfer call).

## EA reading

`targets/game/reverse/ea_evidence.csv` names `AIUpdateInterface::DoXfer`
(chain+direct, aligned). EA's "DoXfer" display label denotes the xfer virtual
(cf. packet row 8: `TerrainLogic::DoXfer` for a `?xferTerrainState@...`
body). With the slot alignment and callee proof above, the aligned item is
confirmed. Mangled identity, following the MAE-protected Dozer override and
ZH's protected `Snapshot::xfer`:
`?xfer@AIUpdateInterface@@MAEXPAVXfer@@@Z`.

## Refuted claims

Three naked `__emit` dumps claim 0x00271DB0 as `??1AssaultTransportAIUpdate@@`,
`??1TransportAIUpdate@@`, `??1WanderAIUpdate@@` (functions.csv lines for
0x00271DB0; `one_identity --list` surplus 2). Retail links without ICF
folding, so three classes cannot share one destructor body; the body sits at
slot 3, not the dtor slot 0; and `one_identity --callers` names no C++ caller
for any of them. All three are over-claims. Retiring them needs multi-row
retirement tooling (`add_match --replace-rva` accepts exactly one row;
see help/o1.md 0x00013101 entry). The existing `AIUpdateInterface::xfer`
draft in `AIUpdate.cpp` (present-unmatched) probes at 0.355 (1927 vs 2099 B),
so a conversion session must also rework the body.
