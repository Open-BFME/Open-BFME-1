// ?rva0023d850@Rva0023D850HordeContainView@@UAEXXZ
// partial score=0.98 date=2026-09-16
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: address-derived HordeContain secondary-view body, retail
// 0x0023D850 (147 bytes).  The vtable installed by HordeContain places this
// body at slot 69.  Its receiver is the +0xE4 secondary interface subobject.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>

typedef bool Bool;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;

	void *m_vptr;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	char m_unmodelled_008[0xc0];
	unsigned int m_kindOf;
};

class Thing
{
public:
	void setOrientation(float angle);
	void setPosition(const Coord3D *position);
	float getOrientation(void) const
	{
		return *(const float *)((const char *)this + 0x44);
	}

	void *m_vptr;
	ThingTemplate *m_template;
	char m_unmodelled_008[0x30];
	Coord3D m_position;
	float m_orientation;
};

class Object : public Thing
{
};

typedef _STL::list<Object *> BfmeMemberList;

extern void j_000399a5();
extern void j_0003a1a7();

typedef void (Thing::*ThingSetOrientationCall)(float);
typedef void (Thing::*ThingSetPositionCall)(const Coord3D *);

static __forceinline void rva0023d850SetPosition(Thing *thing,
	const Coord3D *position)
{
	union { void (*raw)(); ThingSetPositionCall member; } call;
	call.raw = j_0003a1a7;
	(thing->*call.member)(position);
}

static __forceinline void rva0023d850SetOrientation(Thing *thing,
	float angle)
{
	thing->setOrientation(angle);
}

class Rva0023D850HordeContainView
{
public:
#define HORDE_SLOT(N) virtual void slot##N(void) = 0
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
	HORDE_SLOT(46);
	HORDE_SLOT(47); HORDE_SLOT(48); HORDE_SLOT(49); HORDE_SLOT(50);
	HORDE_SLOT(51); HORDE_SLOT(52); HORDE_SLOT(53); HORDE_SLOT(54);
	HORDE_SLOT(55); HORDE_SLOT(56); HORDE_SLOT(57); HORDE_SLOT(58);
	HORDE_SLOT(59); HORDE_SLOT(60); HORDE_SLOT(61); HORDE_SLOT(62);
	HORDE_SLOT(63); HORDE_SLOT(64); HORDE_SLOT(65); HORDE_SLOT(66);
	HORDE_SLOT(67); HORDE_SLOT(68);
	virtual void rva0023d850(void);
#undef HORDE_SLOT

	unsigned char m_flag04;
	unsigned char m_flag05;
	unsigned char m_unmodelled_006[0xfa];
	unsigned int m_state100;
	unsigned int m_state104;
	unsigned char m_unmodelled_108[4];
	unsigned char m_state10c;
	unsigned char m_unmodelled_10d[0xb];
	unsigned char m_state118;

	private:
		Thing *rva0023d850Owner(void) const
		{
			return *(Thing *const *)((const char *)this - 0xdc);
		}
};

typedef void (Rva0023D850HordeContainView::*Rva0023D850Slot46Call)(void);

// ?rva0023d850@Rva0023D850HordeContainView@@UAEXXZ
void Rva0023D850HordeContainView::rva0023d850(void)
{
	m_state100 = 0;
	m_state104 = 0;
	void *vtable = *(void **)this;
	_ReadWriteBarrier();
	m_state118 = 0;
	m_state10c = 1;
	union { void (*raw)(); Rva0023D850Slot46Call member; } slot46Call;
	slot46Call.raw = (void (*)())((void **)vtable)[46];
	(this->*slot46Call.member)();

	BfmeMemberList &members = *(BfmeMemberList *)((char *)this - 0xac);
	BfmeMemberList::iterator node = members.begin();
	Thing *owner = rva0023d850Owner();
	while (node != members.end())
	{
		Object *member = *node;
		if (member != 0)
		{
			ThingTemplate *thingTemplate = member->m_template;
			if (thingTemplate != 0 && thingTemplate->m_nextOverride != 0)
			{
				thingTemplate = (ThingTemplate *)
					thingTemplate->m_nextOverride->getFinalOverride();
			}
			if ((thingTemplate->m_kindOf & 0x00000800) != 0)
			{
				rva0023d850SetOrientation((Thing *)owner,
					member->getOrientation());
				rva0023d850SetPosition((Thing *)owner,
					&member->m_position);
				m_flag05 = 1;
				m_flag04 = 1;
			}
		}
		++node;
	}
}
