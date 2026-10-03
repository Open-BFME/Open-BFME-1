# Complete LANAPI::OnNameChange callback

The old 30-byte claim ends inside the MOV to the EH state at RVA689B8B.
Direct retail decoding reaches RET8 at689BB4, followed by INT3 at689BB7:
the contiguous body is71 bytes. Ghidra's created function independently
covers the same body. The GeneralsMD LANAPICallbacks.cpp OnNameChange twin
calls OnPlayerList(m_lobbyPlayers), then destroys the by-value UnicodeString.

At71 bytes the existing source differs in one non-relocation byte: virtual
OnPlayerList calls slot5C rather than retail70. Retail tableVA111AF50 slot28
(at111AFC0) contains ILT VA407400, whose E9 enters the separately matched
OnPlayerList body689A40/238B. Slot41 at111AFF4 contains ILT VA44B619, whose
E9 enters689B70. The same GeneralsMD callback family and those independently
matched method bodies prove the virtual-call identity and its BFME slot.

Reuse the canonical LANAPI definition and add only an address-qualified
local callback view with28 preceding virtual slots. Its OnPlayerList
parameter is the canonical LANPlayer pointer. No shared-header modification,
new body identity, or new callee pin is needed. The existing matched
LANAPIOnPlayerList.cpp independently walks m_lobbyPlayers at+08; retain that
field access. name_oracle's alternate LANAPI+08 witness is contradicted by
this actual matched roster walker and is not used to invent a new field.

The direct call at689BA2 enters StringBase<WideChar>::releaseBuffer8881D0,
matching tools/callees.py and the existing canonical UnicodeString destructor.
The pure C++ virtual view emits all71 non-relocation bytes exactly; the
final source gate additionally proves relocations and every sibling claim.
