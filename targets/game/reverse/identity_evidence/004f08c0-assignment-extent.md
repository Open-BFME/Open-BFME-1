# GameSlot assignment: complete 135-byte extent

The old 82-byte claim in PeerDefs.cpp stops after the E8 opcode at
RVA 004F0911. Its missing displacement and the second string assignment
are part of the same body. Retail returns with `ret 4` at 004F0944,
followed by INT3 from 004F0947: total135 bytes. Ghidra reports
VA008F08C0..008F0946; the independently decoded PE confirms that span.

The old full native emission calls the narrow StringBase set for the wide
field, omits the second owning string, and copies the wrong tail offsets.
The new TU includes canonical ascii_string.h/unicode_string.h/string_base.h.
The wide assignment forwards to existing StringBase<unsigned short>::set,
called directly at004F0911 ->00888530; the narrow field at+2C delegates to
existing StringBase<char>::set at004F091D ->00887C90. Both take one reference
and pop4. No alternate callee identities or pins are introduced.

The class/member baseline is the GeneralsMD GameNetwork/GameInfo.h GameSlot
twin. BFME inserts a narrow owning string at+2C; no semantic name is claimed
for that field. The old gameinfo shim instead puts a size-only pad at the
end, so it cannot represent this layout. There is no game/ GameSlot header.
The local BFME view retains the independently witnessed m_state+4,
m_startPos+10, m_playerTemplate+14 and m_disconnected+40; the other original
scalar fields follow the twin, with the unknown connect-info words kept
address-qualified. Virtual reset supplies the native vptr; assignment does
not overwrite it. No shared header or existing PeerDefs body is edited.

The retained assignment identity is also the existing named callee of
GameInfo::setSlot at0061F630 through ILT000126E8 ->004F08C0.
The recovered body returns its receiver in EAX and consumes one argument,
consistent with that assignment contract. This repair changes source and
extent, not the inherited identity.
