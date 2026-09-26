// ?d_0024c010@@YAXXZ
// partial score=0.78 date=2026-09-17
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#include <list>

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct HordeContainTransform
{
	unsigned char unused_00[0x10];
	float x;
	unsigned char unused_14[0x0c];
	float y;
	unsigned char unused_28[0x0c];
	float z;

	__forceinline HordeContainTransform(const HordeContainTransform &other)
		: x(other.x), y(other.y), z(other.z) {}

	__forceinline void getTranslation(Coord3D *position) const
	{
		position->x = x;
		position->y = y;
		position->z = z;
	}
};

class Thing
{
public:
	void setPosition(const Coord3D *position);

	void *m_vtable;
	HordeContainTransform m_transform;
	unsigned char unused_38[0x1fc - 0x38];
};

class HordeContainInterface;

class ContainModuleInterface
{
public:
#define SLOT(N) virtual int slot##N() = 0
	SLOT(00); SLOT(01); SLOT(02); SLOT(03); SLOT(04); SLOT(05); SLOT(06); SLOT(07);
	SLOT(08); SLOT(09); SLOT(10); SLOT(11); SLOT(12); SLOT(13); SLOT(14); SLOT(15);
	SLOT(16); SLOT(17); SLOT(18); SLOT(19); SLOT(20); SLOT(21); SLOT(22); SLOT(23);
	SLOT(24); SLOT(25);
	virtual HordeContainInterface *getHordeContainInterface() = 0;
#undef SLOT
};

typedef _STL::list<class Object *> BfmeMemberList;

class HordeContainInterface
{
public:
#define SLOT(N) virtual int slot##N() = 0
	SLOT(00); SLOT(01); SLOT(02); SLOT(03); SLOT(04); SLOT(05); SLOT(06); SLOT(07);
	SLOT(08); SLOT(09); SLOT(10); SLOT(11); SLOT(12); SLOT(13); SLOT(14); SLOT(15);
	SLOT(16); SLOT(17); SLOT(18); SLOT(19); SLOT(20); SLOT(21); SLOT(22); SLOT(23);
	SLOT(24); SLOT(25); SLOT(26); SLOT(27); SLOT(28); SLOT(29); SLOT(30); SLOT(31);
	SLOT(32); SLOT(33); SLOT(34); SLOT(35); SLOT(36); SLOT(37); SLOT(38); SLOT(39);
	SLOT(40); SLOT(41); SLOT(42); SLOT(43); SLOT(44); SLOT(45); SLOT(46); SLOT(47);
	SLOT(48); SLOT(49); SLOT(50); SLOT(51); SLOT(52); SLOT(53); SLOT(54); SLOT(55);
	SLOT(56); SLOT(57); SLOT(58);
	virtual BfmeMemberList *getMemberList() = 0;
#undef SLOT
};

class Object : public Thing
{
public:
	ContainModuleInterface *m_contain;
};

class Rva00249C50HordeContain
{
public:
	void resetContainState();
	void resetPair(void *first, void *second);
	void finishReset();

private:
	unsigned char unused_000[8];
	Thing *m_owner;
	unsigned char unused_00c[0x38 - 0x0c];
	BfmeMemberList m_members;
	unsigned char unused_03c[0x4c - 0x3c];
	unsigned char m_pairState;
	unsigned char unused_04d[0xec - 0x4d];
	unsigned char m_first[0x0c];
	unsigned char m_second[0x0c];
};

// ?resetContainState@Rva00249C50HordeContain@@QAEXXZ
void Rva00249C50HordeContain::resetContainState()
{
	resetPair(m_first, m_second);
	finishReset();
}

// ?finishReset@Rva00249C50HordeContain@@QAEXXZ
void Rva00249C50HordeContain::finishReset()
{
	Rva00249C50HordeContain *saved = this;
	BfmeMemberList output;
	BfmeMemberList contained;
	BfmeMemberList members(m_members);
	BfmeMemberList::iterator it = members.begin();
	for (; it != members.end(); ++it)
	{
		Object *member = *it;
		if (member != 0 && member->m_contain != 0)
		{
			HordeContainInterface *horde =
				member->m_contain->getHordeContainInterface();
			if (horde != 0)
			{
				Coord3D position;
				HordeContainTransform transform(m_owner->m_transform);
				transform.getTranslation(&position);
				member->setPosition(&position);
				contained = *horde->getMemberList();
				for (BfmeMemberList::iterator containedIt = contained.begin();
					containedIt != contained.end(); ++containedIt)
					output.insert(output.end(), *containedIt);
			}
		}
	}
	saved->resetPair(&output, &saved->m_pairState);
}
