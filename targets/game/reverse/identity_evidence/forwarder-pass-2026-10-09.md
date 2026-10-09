# Name-forwarder pass, 2026-10-09

Owner-approved single pass (build/linkfleet/owner_forwarder_verdict.md, groups 1 and 2) over the `#define` /
`typedef` forwarders the 2026-10-06..09 link fleet added so call respellings would not trip name_regression.
Each forwarder kept an old spelling and routed it to the ledger row's name. This pass deletes the forwarder and
spells the call with the ledger name. A `#define` or `typedef` emits no code, so every touched TU stays
byte-identical (`./build.sh`, 100% matched) and keeps linking (`tools/link_check.py`, LINKED unchanged).

None of the descriptive spellings below is EA's name for its target. BFME1 retail ships no symbols, so a
descriptive name needs an independent witness: a Zero Hour counterpart, an ILT bucket fit
(`tools/ilt_oracle.py check`), or matched callers that use the name. The forwarder spellings were invented by
workers to keep the old call text compiling; a define is not evidence for its own name.

## FESL message helpers (Rva008097D0LanTheaterRemove, Rva00803730FeslAttrs, FeslEchoNotifier, FeslTidMessageSender, Rva0080A110Route)

- `sendFeslMessage` -> `Rva007F93E0` (0x007F93E0, ledger note "FESL routed message sender").
  `tools/ilt_oracle.py check '?sendFeslMessage@@YAPAXPAX00@Z' 0x7F93E0` and the same check of the ledger name
  both return UNTESTABLE (not a thunk target: FESL library region), so the ILT cannot witness any name here.
  FESL is EA Online code that Zero Hour does not contain, so there is no ZH name either. The body does route a
  message (dispatcher callers), but "sendFeslMessage" is a worker's paraphrase, not a recovered identity.
  Unproven: callers now spell `Rva007F93E0`.
- `addInt` -> `BfmeThingCIB::bfmeGoCIB` (0x007E88D0), `getPtr` -> `BfmeThingRF::bfmeGoRF` (0x007E8900),
  `getBool` -> `BfmeThingVMQ::bfmeGoVMQ` (0x007E89C0): FESL key/value accessors in the same library region,
  same ILT status, no ZH counterpart. Unproven paraphrases; callers spell the ledger names.
- `submit` -> `Rva008038F0Sender::send` (0x008038F0): the ledger name already says "send"; "submit" was a
  second, unwitnessed spelling. Callers spell `send`.
- `typedef BfmeC994 FeslEchoMessage`: BfmeC994 is the FESL message class (ctor 0x007E8850). No witness names
  it FeslEchoMessage; the local is declared as `BfmeC994`.
- `Rva007EFFC0Get()` / `Gen00809750_delete()` (group 2, placeholder to placeholder): spelled as their
  expansions (`bfmeGo929C`, `Gen007F0170::operator delete`).
