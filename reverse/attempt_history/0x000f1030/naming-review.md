# Team build-variation bank replacement: declaration review

The old partial invented three shim types: BfmeStrFK, BfmeHolderFK and BfmeHostFK. The byte-verified replacement uses canonical AsciiString, native vector<AsciiString>, ThingTemplate and the actual Team caller. The released Common/RTS/Team.cpp isInBuildVariations and its recruitment loop establish the template, string and vector identities independently of the byte match. ThingTemplate+2D0 is witnessed as m_buildVariations; +20 is its name.

The token matcher pairs removed fields with unrelated newly introduced padding in the caller's classes:

- BfmeStrFK::m_bfmeDataFK is character storage at +8. It is represented by StringBase<char>::Header::data in the canonical header, not by TeamPrototype::m_unknown_1bd (padding after its AI-recruitable flag).
- BfmeStrFK::m_bfmeGapFK is the two-byte gap after string length. The canonical Header includes its capacity field there. It is not TeamPrototype::m_unknown_00c, which spans the player pointer to the AI-recruitable flag.
- m_bfmeHeadFK names three unrelated prefix byte arrays in the old shim types. The canonical string header provides reference count and length; real ThingTemplate declarations provide its name and vector. Added m_unknown_000 prefixes belong to Player, TeamPrototype, Object and Team layouts needed by the real caller, and m_unknown_008 belongs to Team. These were not present as such in the helper-only bank.

The exact snapshot corrections below record false declaration pairings, not a permission to downgrade established names. No detector or baseline is changed. The new source also adopts the witnessed TeamPrototype::m_owningPlayer spelling.
