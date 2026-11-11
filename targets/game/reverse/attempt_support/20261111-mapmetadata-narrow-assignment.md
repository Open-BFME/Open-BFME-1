# MapMetaData narrow-string assignment

Queue70 at census90c15cdeca reports assignment-provider losers. Read the
existing assignment and Unicode setter attempt records first. The target
assignment spans0x000C1050/229B. `callees.py` independently reports four
calls to StringBase<unsigned short>::set at0x00888530 and one to
StringBase<char>::set at0x00887C90, alongside three existing container ILTs.

The private declaration called the latter through UnicodeString::set,
relying on a historical narrow-address pin for a wide-string class name.
Replace only that one-word field view with the existing StringBase<char>
declaration and remove the now-unused private UnicodeString class. The
normal scoped gate preserves all229B; the object now names the narrow
provider directly. No pin, shared header, class size, field offset or member
name changed. This does not solve other units' emitted assignment copies.

Donor76f0baefa6, Code/GameEngine/Source/GameClient/MapMetaDataCopyDeferred.cpp,
independently models the corresponding field as AsciiString and explicitly
uses StringBase<char>::set for its assignment. Donor member name and256B
layout are not imported. The BFME1 call target and existing local member
ordering support this limited type correction. Existing /O2 /Ob0 and
header context retained. No newly linked bytes claimed; current linking
requires the missing census dependencies.
