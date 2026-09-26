# InGameUI subtitle slot identity correction

## Evidence and finding

The current ledger calls the 585-byte body at `0x00441D30`
`InGameUI::militarySubtitle(const AsciiString &, int)`. That exact signature is
inconsistent with the BFME call path. Both installed InGameUI vtables put
`0x00441D30` in slot 19, `0x0043E510` in slot 20, and the independently matched
`removeMilitarySubtitle()` (`0x004431B0`) in slot 21. The 132-byte slot-20 body
reads an `AsciiString const&`, calls `TheGameText` slot 9 to obtain a
`UnicodeString`, and passes that wide string by value with the duration to
slot 19. Slot 19 handles the wide string and tests its `StringBase<WideChar>`
header; it does not fetch an ASCII label. Both bodies end in `ret 8`, which
alone cannot distinguish a string handle from a reference.

The Zero Hour `InGameUI.h` declares
`militarySubtitle(const AsciiString&, Int)` immediately before
`removeMilitarySubtitle()`. The BFME slot-20 ABI and label-to-wide behavior,
the installed slot order, and BFME's matched slot-21 removal method together
support rehoming that lexical name to `0x0043E510`. The old Zero Hour
`ScriptActions` calls and BFME's present-unmatched `InGameUI.cpp` definition
corroborate the interface but are not matched-caller proof. Slot 19 remains an
address-qualified InGameUI wide-text method because its semantic spelling is
not independently proven. This supersedes the unresolved-name paragraph in
`0x0043e510-ingameui-subtitle-label.md`.

## Design checkpoint before ledger changes

Proceed with a two-row identity correction, preserving both RVAs, extents,
sources and emitted symbols. First replace the slot-19 name with
`?rva00441D30@InGameUI@@UAEXVUnicodeString@@H@Z` through
`add_match.py --correct-identity`, keeping its existing
`object-symbol=_bfme_InGameUIMilitarySubtitle_441D30`. Then use
`correct_match_identity.py` to give the slot-20 row the now-free
`?militarySubtitle@InGameUI@@UAEXABVAsciiString@@H@Z` name. That tool records
the slot-20 C++ symbol as `object-symbol`, so the compiled
`subtitleLabelRva0043E510` method stays distinct from the present-unmatched
`InGameUI.cpp` definition. Tombstone both retired `(name, RVA)` claims. Add an
exact-hash entry to `name_corrections.json` for the necessary slot-19 downgrade.

The alternative of leaving both slots address-qualified would remove the
false claim but discard the supported slot-20 lexical identity. Renaming the
native wrapper source would risk a duplicate C++ definition; changing the
historical naked emitter would create an unrelated anti-lift problem. Neither
source-body change is needed. A successful byte gate cannot prove the new
identity, so the vtable/ABI evidence above remains the naming proof.

## Adversarial review and verification plan

An independent reviewer checked the installed pair, the slot-20 forwarding
contract, the matched slot-21 anchor, and the Zero Hour declaration order.
The strongest contrary explanation is that BFME changed the virtual method
order relative to Zero Hour. That would have to preserve the slot-20 ASCII
label signature and adjacent slot-21 removal method while giving the name to
slot 19's wide-text worker; it conflicts with the declared interface and is
less supported than the proposed rehome. `ret 8` alone is insufficient and
is not used as identity evidence. The review also found the duplicate-source
symbol hazard and requires explicit `object-symbol` aliases.

Run both scoped byte gates, `check_csv`, identity/pin consistency, the naming
regression gate with an exact correction entry, and the normal hooks. A failure
at either gate requires restoring both rows and tombstones as one logical
correction. Expected benefit is removal of a false semantic claim without
changing byte coverage; neither byte progress nor throughput is claimed.
