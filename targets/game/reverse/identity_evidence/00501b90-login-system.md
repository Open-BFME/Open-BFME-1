# WOLLoginMenuSystem — 00501B90

The retail function lexicon at RVA 00EA9560 contains the triple
`{0, VA0108760C, VA0041C364}`. The string is `WOLLoginMenuSystem`;
ILT RVA 0001C364 is `E9 27 58 4E 00`, reaching RVA 00501B90.
This is independent identity evidence, also agreeing with the reference
FunctionLexicon.cpp and the full WOLLoginMenu.cpp callback twin.

The whole native extent is [00501B90,00503740), 7088 bytes. The final RET
is at +1BAF, followed by INT3 padding before the next aligned start. The
7078-byte historical lift omitted the final ten bytes. This change removes
that naked file and uses one main-body ledger owner.

## Native source and retail differences

The reference callback's create-account, login, email/nickname selection,
password/date restoration, age gate, and terms-of-service control flow are
preserved. Retail adds a GetStringFromRegistry read of `\\ergc` / the empty
value name to the create-account path only, then copies the resulting value
to request+276. The field is deliberately address-derived; its enclosing
struct records the observed destination without inventing an SDK member name.
Retail omits the web-browser branch and its two boolean state stores, and
loads the text from `Lang\%s\TOS.txt` rather than the reference `Data` directory.

BuddyRequest's 2B8-byte extent is independently copied by getRequest at
0063C770 (also documented in 004ed400-buddy-control.md). Its login fields
start at +4, +23, +56, and +75; the copied registry string starts at +276.
These imply character capacities 31, 51, 31 and a one-byte firewall flag.
The unused interval and trailing field retain address-derived names.
The existing name oracle has no BuddyRequest or GameSpyInfoInterface layout.

File virtual slots are independent of this caller: the named File base and
Win32LocalFile vtables at VA01143AF8/VA01143C10 carry close at +8, read at +C,
and size at +2C. File.cpp and LocalFile.cpp byte-match those implementations;
File::size is RVA009CB670 and File::close is RVA009CB880. The legacy
MemoryPoolObject header introduces an extra slot, so this TU uses the proven
File interface locally. No shared-header change is needed.

The canonical AsciiString/UnicodeString headers own the string types.
Visible forwarding bodies call the existing StringBase constructors,
releaseBuffer, setters, and getters. getCharAt is called through StringBase
explicitly so that the remaining out-of-line call denotes the real
StringBase<unsigned short>::getCharAt at 0043D590, not a new UnicodeString
wrapper. `_WCTYPE_INLINE_DEFINED` retains the real MSVCR71 iswspace import;
otherwise the compiler header emits an iswctype call and changes register
allocation throughout the terms-of-service loop.

## Bounded list-destructor dependency

The callback gets a complete `list<AsciiString>` from the independently
matched getNicksForEmail at 00082660 and destroys those two scoped returned
lists through ILT0001E227 -> 000808D0. The 27-byte target calls the independently
matched AsciiString list clear through ILT0001900B -> 000800C0, then releases
its 12-byte sentinel through node allocator deallocate at 0082E5F0; ECX is
this, there are no stack parameters, and the target ends in plain RET.
The STLport complete list destructor emits exactly this body and both real
callee operands verify. The gen-tgrid placeholder at 000808D0 is replaced
by that complete list destructor in this TU. The separately claimed base
class destructor at 000803E0 remains a separate address and source; no alias
or additional symbol pin is introduced.

## Ownership and verification

WOLLoginMenu.cpp remains unchanged because it owns six already verified
legacy cleanup-helper rows whose parent metadata names System, plus other
functions. Its reference System is not a main-body claim and earns no new
coverage. No cleanup-helper row is moved or newly inferred from adjacency.

Probe: 7088/7088 bytes, 465 aligned relocations, zero masked differences.
The mechanical EH search tried seven variants and found no improvement;
all changes retained here correspond to witnessed BFME behavior or ABI.
The complete list destructor separately byte-verifies 27/27 bytes, including
both callees. The scoped gate must also verify the main body's relocation
operands and string literals before publication. No new symbols.csv pins.
Model: GPT-6. Started 2026-09-26 21:25 UTC.
