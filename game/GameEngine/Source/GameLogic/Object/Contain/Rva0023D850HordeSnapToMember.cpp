// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

// Retail 0x0023D850 (147 bytes): HordeContain secondary-interface slot 69
// (rdata 0x00CAE344).  It resets the formation bookkeeping (+0x100/+0x104
// cleared, +0x118 off, +0x10C on), calls the interface's own slot 46, then
// walks the contained list below the interface: for each member whose final
// template override carries flag 0x800 at +0xC8 it moves the horde's owner
// object onto that member (Thing::setOrientation, Thing::setPosition) and
// raises the +0x04/+0x05 dirty bytes.  IDENTITY IS NOT RECOVERED: the slot
// name and the flag keep the address.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// Retail spells this accessor ?getFinalOverride@Overridable@@QBEPBV1@XZ
// (public const, upstream Overridable.h); the TU-local stand-in carries the
// template layout this body reads, so it takes the defining class/member name.
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	unsigned char m_head[4];
	Overridable *m_next;
	unsigned char m_mid[0xc0];
	unsigned int m_flagsC8;
};

static __forceinline Overridable *finalOverride(Overridable *p)
{
	if (p == 0)
		return 0;
	if (p->m_next == 0)
		return p;
	return const_cast<Overridable *>( p->m_next->getFinalOverride() );
}

class Thing
{
public:
	void setOrientation(Real angle);
	void setPosition(const Coord3D *pos);

	unsigned char m_head[4];
	Overridable *m_template;
	unsigned char m_mid[0x30];
	Coord3D m_cachedPos;
	Real m_cachedAngle;
};

class Object : public Thing
{
};

typedef _STL::list<Object *> BfmeMemberList;

class Rva0023D850HordeContain
{
public:
#define HORDE_SLOT(N) virtual void slot##N() = 0
	HORDE_SLOT(00); HORDE_SLOT(01); HORDE_SLOT(02); HORDE_SLOT(03);
	HORDE_SLOT(04); HORDE_SLOT(05); HORDE_SLOT(06); HORDE_SLOT(07);
	HORDE_SLOT(08); HORDE_SLOT(09); HORDE_SLOT(10); HORDE_SLOT(11);
	HORDE_SLOT(12); HORDE_SLOT(13); HORDE_SLOT(14); HORDE_SLOT(15);
	HORDE_SLOT(16); HORDE_SLOT(17); HORDE_SLOT(18); HORDE_SLOT(19);
	HORDE_SLOT(20); HORDE_SLOT(21); HORDE_SLOT(22); HORDE_SLOT(23);
	HORDE_SLOT(24); HORDE_SLOT(25); HORDE_SLOT(26); HORDE_SLOT(27);
	HORDE_SLOT(28); HORDE_SLOT(29); HORDE_SLOT(30); HORDE_SLOT(31);
	HORDE_SLOT(32); HORDE_SLOT(33); HORDE_SLOT(34); HORDE_SLOT(35);
	HORDE_SLOT(36); HORDE_SLOT(37); HORDE_SLOT(38); HORDE_SLOT(39);
	HORDE_SLOT(40); HORDE_SLOT(41); HORDE_SLOT(42); HORDE_SLOT(43);
	HORDE_SLOT(44); HORDE_SLOT(45);
#undef HORDE_SLOT
	virtual void refreshFormation() = 0;

	void snapToFlaggedMember();

private:
	bool m_flag04;
	bool m_flag05;
	unsigned char m_pad06[0xfa];
	int m_state100;
	int m_state104;
	unsigned char m_pad108[4];
	bool m_state10c;
	unsigned char m_pad10D[0x0b];
	bool m_state118;
};

void Rva0023D850HordeContain::snapToFlaggedMember()
{
	m_state118 = false;
	m_state10c = true;
	m_state100 = 0;
	m_state104 = 0;
	refreshFormation();

	Object *owner = *(Object **)((char *)this - 0xdc);
	const BfmeMemberList &contained =
		*(const BfmeMemberList *)((char *)this - 0xac);
	for (BfmeMemberList::const_iterator it = contained.begin();
		it != contained.end(); ++it)
	{
		Object *member = *it;
		if (member != 0 && (finalOverride(member->m_template)->m_flagsC8 & 0x800))
		{
			owner->setOrientation(member->m_cachedAngle);
			owner->setPosition(&member->m_cachedPos);
			m_flag05 = true;
			m_flag04 = true;
		}
	}
}
