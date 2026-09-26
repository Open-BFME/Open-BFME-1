# Profile statistics renderer — RVA 0x005674F0

The full 5,762-byte body now has native C++. Its owner is not semantically
identified, so `Rva005674F0Profile::apply` retains the retail address. The matched
caller at 0x0057ED70 passes its receiver at +0x390 and a 24-byte copied argument
from +0x3AC through ILT 0x00048A0E. Retail ends with `ret 0x18`. The copy goes
through ILT 0x0001050A to 0x0057ECF0; the final destructor goes through ILT
0x00046B82 to the independently identified SkirmishPreferences destructor at
0x0009F7A0. The SkirmishPreferences constructor/vtable and its list destructor
establish that argument identity. The old bank called the two views
BfmeConsumerED and BfmeArgED; neither old opaque label is promoted into a guessed
semantic owner name.

The receiver has a four-byte prefix before its preference view. Retail copies
the tree, the string and the list through this+8, +0x14 and +0x18. The source
keeps offset names for the string rather than calling it a user name: the
getUserName method queries the preference map. The 60-byte SkirmishBattleHonors
view comprises its 20-byte UserPreferences part and the 40-byte member also
present in the independently matched constructor. Unknown fields remain opaque.

## Recovered behavior

The body builds SkirmishBattleHonors from the copied profile and fills the APT
labels for profile creation, overall wins/losses, streaks, player name, favorite
side, total games and the four factions. Faction ordering is Gondor, Rohan,
Isengard, Mordor, independently witnessed by retail literals. A missing favorite
side becomes `--`. Each label and its copied Unicode value is sent to the already
matched WindowManager::bfme_setAptText. There are 37 such calls.

The old bank repeatedly constructed number buffers and copied a faction into
an inline helper's by-value parameter. Retail instead constructs one Unicode
output buffer and one Ascii faction selector just after SkirmishBattleHonors.
The output buffer lives through every label; the faction selector is assigned
once per faction and copied only into the statistics getters. The helper source
now expresses those lifetimes, including direct GameText fetch arguments for
streak formatting. This restores retail's 0x64-byte frame and every exception
state. The final body is exactly 5,762 bytes with all 465 relocation sites
aligned. No assembly or artificial frame padding is used.

## Dependency review

All 31 distinct direct targets and the wcslen import were decoded before the
body was changed. The canonical ASCII/Unicode headers are used; the actual
Unicode constructor, assignment and destructor forwarding bodies are visible
locally. No shared header is changed. The copied Unicode arguments call the
StringBase<unsigned short> constructors/destructors witnessed in retail.

The first strict gate rejected the old bank's invented no-argument `getWins`
overload. The aligned target is ILT 0x000344CD to 0x0009C6F0, already native as
`SkirmishBattleHonors::rva0009c6f0`; its four faction calls independently establish
its contract. The source uses that existing address-derived method. No pin was
added to accommodate the mistaken spelling. The per-faction getWins overload
at 0x0009C650 is distinct and remains named as already established.

Tree assignment uses the existing address-derived Rva005672C0Map binding. The
old ledger's NameKeyType/float template label at 0x005672C0 does not establish
that template identity for this preference object, and is not adopted here.
List assignment uses the existing Rva005673A0Vec binding at 0x005673A0; its
independently matched implementation is list<UnicodeString>::operator=.

The generated dump is left untouched. Its row is replaced with the native
source, and add_match removes the obsolete bank. Normal strict body/string,
ledger, identity, conversion, commit and push gates are required. Existing
helper bodies and bindings receive zero progress credit; this conversion adds
only the 5,762-byte main body.
