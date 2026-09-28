# 0x000DA610 Player::init: retired raw-storage member names

The retired bank (`targets/game/reverse/attempts/0x000da610.cpp`) did not
model Player's members. It addressed the object through
`struct RawPlayerStorage { unsigned char m_data[0x6a0]; }` and a
`playerField<T>(this, offset)` accessor, and gave the two 0x18-byte relation
maps an opaque `unsigned char m_storage[0x14]` blob after their vptr.
`m_data` and `m_storage` therefore named whole-object / whole-container byte
blobs, not the fields at Player+0x54 and Player+0x694 that name_regression
pairs them with by layout.

The landed source (`game/GameEngine/Source/Common/RTS/PlayerInit.cpp`) takes
its layout from the matched Player::~Player (`PlayerDestructor.cpp`,
0x000DD440), which also leaves +0x54 and +0x694 as unnamed padding. Neither
offset is read or written by Player::init (retail 0x000DA610), and
`tools/name_oracle.py --class Player` has no witness for either, so they keep
offset-derived names. The relation map's +4 blob is now the real
`hash_map<Int, Relationship>` whose operator[] is already pinned at ILT
0x0001219D (setPlayerRelationship).
