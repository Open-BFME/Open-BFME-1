# SpecialPowerTemplate::getName: remove the duplicate strong provider

Task 10 of the sequential ten-task session; queue rank 18 at d08539a550.
Starting BFME 1 revision 676d5307fc. Existing symbol, identity, 0x00098F80
address and 52-byte extent are unchanged.

## Repair and evidence

The split SpecialPowerTemplate.cpp supplied a strong definition while
SpecialPower.cpp already emitted a retail-equal select-any copy of the same
method. Keep the existing inline provider in its native RTS source and remove
only the redundant strong body. The separate getViewObjectDuration body remains
in the split file: a dry-run whole-file rehome correctly rejected that member
because SpecialPower.cpp does not emit it. No header, class layout, name, pin,
import binding or compiler flag changes.

The original matched getter's identity comes from the existing SpecialPowerTemplate
declaration and callers, including the matched Gen0026AC60Owner::getPowerName
at 0x0026AC60. callees.py 0x98F80/52 identifies the override walker through
ILT 0x48C61 -> 0x97880 and StringBase copy construction 0x887B60.
The native provider's COFF body has 52 bytes and those same two relocations.
add_match --replace-existing verifies it under the existing decorated identity.
After rebuilding, COFF symbol inspection finds one definition in SpecialPower.obj
and no definition in SpecialPowerTemplate.obj. Source-claim inspection finds no
new unmatched definitions in the edited split source.

Normal scoped build passes 19/19 function rows and the existing data row across:
SpecialPower.cpp, SpecialPowerTemplate.cpp, AISkirmishPlayer_computeSuperweaponTarget.cpp,
SpecialPowerCompletionDieDestructorThunk.cpp, Rva0026AC60GetPowerName.cpp.
All seven DIR32 references, eight literals and four float constants pass.

## Linking limits

This repairs the duplicate-provider cause served by the queue. Other inline
getName copies (e.g. InGameUI / SpecialPowerModule) are not retail-equal, so this
is partial linking progress, not an assertion that the callers now link.
The available e9a5ae5b4c census predates the queue: before, its census-only
preview reports selected-getName conflicts for all three consumers, plus an
AsciiString::compare conflict for AISkirmishPlayer. After, current-object
selection cannot be established with the cold/stale census; no linked bytes
are claimed. Do not reorder ledger rows to choose a different copy.

## Donor review

Reviewed BFME 2 59e3f8f825b698775df9e1728265fe962a5d0c02,
Code/GameEngine/Source/Common/RTS/SpecialPower.cpp and the SpecialPowerTemplate
source/header search. This is an existing BFME 1 provider repair; no donor
body, address, layout or method name is imported. The donor checkout was
populated at BFME 1's verified tracked pointer without nested submodules.
