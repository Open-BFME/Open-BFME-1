# Parser bank declaration review

The previous 0x006087E0 bank locally redeclared StringInlineData, StringBase,
and AsciiString. The replacement includes the canonical ascii_string.h instead.
StringInlineData described string storage (reference count, length, character
array); it was not a sound-upgrade mask and was not renamed to one.

Rva006087E0Mask is a separate, newly introduced wrapper around
_STL::bitset<192>. Its two instances describe the six-word masks consumed by
Rva006083A0SoundUpgrade::buildMasks at 0x00608090, whose matched implementation
is in Code/GameEngine/Source/GameClient/Drawable/Behavior/
UpgradeSoundSelectorClientBehaviorInterface.cpp. The parser passes two separate
six-word output arrays to that function. There is no string-storage relationship.

The token matcher paired the removed string declaration with the added mask
declaration because of their positions in the replacement block. This exact
snapshot correction records that false pairing; it authorizes no semantic-name
replacement and adds no byte-match credit. The parser remains a partial bank.
