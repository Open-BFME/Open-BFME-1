# Module slot 4: BeaconClientUpdate::getModuleNameKey

Retail SHA-256: `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Addresses below are RVAs unless marked VA. Findings were checked with pefile
and capstone against the unpacked 1.03 baseline.

## Owner, slot and lexical witness

The registered owner chain is also documented in
[the ClientUpdate slot-10 census](clientupdate-slot10-clientupdate.md): registry
site `00130800`, factory `00121B70`, allocation size `0x14`, constructor
`006030C0`. The factory call at `00121BAB` uses ILT `00046B1E` to that
constructor. The constructor installs table VA `01115248` at `006030D4`;
slot 2 resolves to `00603100`, which returns the literal `BeaconClientUpdate`.
Slot 4 at pointer RVA `00D15258` contains VA `00401186`; that E9 ILT stub
resolves to `00603130`. A bytewise image scan finds the stub VA exactly once,
at this slot. The sibling SwayClientUpdate slot 4 resolves to its already
matched getModuleNameKey at `00604560`.

The unmodified Zero Hour header `GameClient/Module/BeaconClientUpdate.h`
invokes `MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA` for this exact owner.
`Common/Module.h` supplies the explicit public virtual twin:
`virtual NameKeyType getModuleNameKey() const`, with a static name key
initialized by `NAMEKEY(#cls)`. This establishes the method name and complete
ABI, including const, enum return, public virtual access, and no arguments:
`?getModuleNameKey@BeaconClientUpdate@@UBE?AW4NameKeyType@@XZ`.

Retail `00603130` implements precisely that lazy name-key initializer. It
tests guard VA `012F7024`, calls through ILT `0003ADD7` to `0008FFC0` with
ECX = TheNameKeyGenerator (VA `012ED600`) and one argument, the literal
BeaconClientUpdate, then caches the enum at VA `012F7020`. The matched
NameKeyGenerator::nameToKey pin passes pin_consistency. This cannot be the
old ledger's private static getClassMemoryPool: the receiver, argument list,
callee and primary virtual slot independently contradict that claim.

## Byte match and exception cleanup

The dedicated TU includes the upstream class header, without redeclaring the
class, and uses a qualified call only as an emission anchor. `/Ob1` inlines
NAMEKEY as retail does. The emitted virtual is exactly 104 bytes, including
both epilogues through RET at `00603197`; padding begins at `00603198`.
The probe matched all 104 bytes and all 12 relocations.

The cleanup is not assigned by adjacency. Retail's push at `0060313E`
references handler `00C3D40E`, whose FuncInfo is `00E2CEE8`. Its unwind map
contains state 0 -> -1 with action `00C3D400`. That 14-byte action clears
bit 0 of guard VA `012F7024` and returns at `00C3D40D`. The new COFF parent's
handler relocation is at offset 15; its unwind map likewise has state 0 ->
-1, action `$L35217`. Thus `uw_00c3d400` moves with its real parent and this
state-proven local symbol, retaining its address-derived identity.

The old bulk pool TU remains needed by its other claims, including Beacon's
placement delete and a different emission anchor's cleanup. It is intentionally
not edited: only these two wrongly associated ledger rows move. The old
getClassMemoryPool symbol ceases to claim this retail address. No new callee
pin, speculative member name, or header modification is required.
