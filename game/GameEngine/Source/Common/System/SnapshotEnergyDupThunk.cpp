// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: per-TU duplicate copy of Snapshot's default constructor,
// retail 0x007E86B0. The real name ??0Snapshot@@QAE@XZ is already claimed
// at 0x0006B180 (game/GameEngine/Source/Common/System/Snapshot.cpp); MSVC
// left this TU's copy of the same inline-able constructor un-folded at a
// separate address, called by ??0Energy@@QAE@XZ at 0x00808880
// (game/GameEngine/Source/Common/RTS/EnergyConstructorThunk.cpp). Claimed
// here under the dup_ convention as a duplicate of the real symbol.
//
// Shape: install the vtable at +0, zero one hidden dword at +4, return --
// matching re_attempts.log's finding that Snapshot carries a hidden 4-byte
// member the vendored ZH header omits. A local minimal replica with a
// single virtual (to force a vtable) and one 4-byte member reproduces it
// exactly.

class SnapshotDupReplica
{
public:
	SnapshotDupReplica();
	virtual void crc() {}

private:
	int m_reserved;
};

// ?SnapshotDupReplica::SnapshotDupReplica present-unmatched
SnapshotDupReplica::SnapshotDupReplica() : m_reserved(0)
{
}
