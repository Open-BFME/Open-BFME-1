# Skirmish profile display, RVA 0057A470

The existing bank was a 2,614-byte outline. The complete retail body is 5,296
bytes, through the RET at +14AF. Three calls from the matched AptSkirmish
initialization path and the Skirmish profile widget labels identify the screen
method. The reconstruction retains its existing `_bfme_updateProfileDisplay`
spelling; it does not infer names for unidentified object fields.

The new native attempt reconstructs all three paths: absent profile, absent or
random faction, and a selected faction. It recovers profile date/user name,
career counts, streaks, formatted play time, four faction labels, the movie,
rank/next-win text, progress percentage and level-icon tooltip. The old
`SkirmishProfileSnapshot` and its invented padding are removed. Retail directly
uses preferences at receiver +3AC and battle honors at +3C4, with APT level +250.
The slot accessor returns a GameSlot whose faction integer is read at +14;
PlayerTemplate's side string is read at +8.

## Measured state

On 2026-09-26, VC7.1 with `/DNDEBUG /MD /EHsc` emits exactly 5,296 bytes and
372 aligned relocation sites. Instruction structure is identical after
register/constant normalization. There are still 226 differing concrete bytes,
primarily stack homes: dash is +28 rather than +24, scalar/string temporaries
cycle through different slots, and the two 16-byte movie buffers exchange
homes. The 256-byte progress buffer and frame size agree. The bank score is
0.94065 = 1 - 226 / (5296 - 372*4), not the 1.000 structural score. This is
unfinished evidence, not a byte-verified conversion.

The complete 251 direct call sites were checked at aligned operands against
retail. 250 already resolve to their existing ledger targets, with zero wrong
targets. The one remaining source binding is described below. `_itoa` is called
through the retail MSVCR71 IAT slot three times. No pin, source claim or progress
row was added.

## Remaining callee contract

The call through ILT 00022C23 targets 0009C4B0, a 205-byte body already owned by
`bfmeTimePlayedAM` in `BfmeTimePlayedAM.cpp`. It formats days/hours from the float
returned by `SkirmishBattleHonors::getTimePlayed`. This caller explicitly loads
ECX from its honors receiver and supplies the hidden UnicodeString result plus
float; the callee returns with RET 8 and does not use ECX. The old ownership
spelling instead claims stdcall and a TU-specific UnicodeStringAM return.

The bank spells that witnessed contract as the address-derived
`SkirmishBattleHonors::rva0009c4b0(float)`. Its body is present; it is not a
missing implementation. Landing requires an independently reviewed signature/
ownership repair of the existing 205-byte native helper, or a justified single
address-derived binding. Do not invent a semantic member name. A linker
`/alternatename` directive is not consumed by the current byte-gate resolver
and is intentionally not left as an apparent solution.

The icon helper continues to use the existing `BfmeA1024::bfmeGo1024A(int,int)`
binding with the two witnessed AsciiString object addresses; it needs no new
pin. The GameInfo accessor must use `class GameSlot`, not `struct GameSlot`,
to match the existing decorated signature.

## Productive levers and exhausted variants

* Canonical ASCII/Unicode headers and local wide-string forwarding definitions
  preserve all observed constructor/destructor calls.
* The output UnicodeString persists across updates. A distinct dash string is
  initialized with `APT:DashDash` and passed by value to format operations.
* Two real 16-byte `_itoa` buffers account for the retail frame; a third real
  256-byte buffer holds percentage text. No artificial frame padding is used.
* The percentage is converted to int before a reference-returning two-stage
  clamp. This restores the six missing instructions and exact extent.
* An inline APT-call forwarder restores receiver-load scheduling.
* A typed external `Rva012B8054ProfileIconName`, used at both witnessed reads of
  VA 012B8054, restores the one-byte absolute-load difference and final receiver
  scheduling. This was independently confirmed by a second agent.

Scalar declaration scope/order, const strings, equivalent combined arithmetic,
min/max templates, named string scopes versus inline helper scopes, implicit
key temporaries, `/Ob1`, `/EHs`, movie-buffer declaration order and enclosing
scope changes did not change the remaining allocation. A diagnostic original
StringBase-derived wide view was byte-identical to the canonical forwarding
view, so no shared-header repair is supported by this residue. The authentic
49-byte setAptText body made visible likewise did not change the caller.

Start from the complete bank. A future pass needs a new stack-lifetime or
callee-visibility lever, not another reconstruction from the old outline.
