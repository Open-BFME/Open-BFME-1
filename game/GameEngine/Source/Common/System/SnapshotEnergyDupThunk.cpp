// cl: /DNDEBUG /MD /EHsc
// Two 16-byte constructors of one shape -- install the vtable at +0, zero the
// dword at +4, return this -- for two different classes:
//   0x007E86B0 installs 0x01129358; Energy's constructor (0x00808880) and the
//     LAN-game sources call it as SnapshotDupReplica.
//   0x003828C0 installs 0x010EAD58, the base table the destructors in
//     BigTwoMemberDtors.cpp and ThreeMemberDtor00476440.cpp store as
//     Inner010EAD58.
// Neither is Snapshot's constructor: that is 0x0006B180, which installs
// 0x01073744 and zeroes nothing.

class SnapshotDupReplica
{
public:
	SnapshotDupReplica();
	virtual void crc() {}

private:
	int m_reserved;
};

SnapshotDupReplica::SnapshotDupReplica() : m_reserved(0)
{
}

class Inner010EAD58
{
public:
	Inner010EAD58();
	virtual ~Inner010EAD58() {}

private:
	int m_reserved;
};

Inner010EAD58::Inner010EAD58() : m_reserved(0)
{
}
