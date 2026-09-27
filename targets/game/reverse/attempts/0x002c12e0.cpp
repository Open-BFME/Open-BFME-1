// ?d_002c12e0@@YAXXZ
// partial score=0.88 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc
//
// Opaque recovery for retail 0x002C12E0 (322 B, dump d_002bbb80.asm).
//
// Evidence (all read off the retail bytes, no identity invented):
// - __thiscall, no stack args, returns int: 0x3fffffff (UPDATE_SLEEP_FOREVER)
//   on one early path, 1 (UPDATE_SLEEP_NONE) everywhere else.
// - Calls chooseGoodLocomotorFromCurrentSet (0x00270D40 via ILT 0x00036A3E)
//   with this, so the receiver shares the AIUpdate shape.
// - Reads this+0x1CC (witnessed AIUpdateInterface::m_curLocomotor) and
//   this+0x32B (witnessed AIUpdateInterface::m_isAiDead).
// - Head and mid-body repeat the native OVERRIDE<T> + unrolled
//   Overridable::getFinalOverride inline from AIUpdate_chooseLocomotorSet.cpp
//   (separate `add eax,4` / `mov eax,[eax]`, out-of-line call via ILT
//   0x000022BB), then test a template flag byte (+0xC8 bit 2, +0xCC).
// - Switches on the int at this+0x460 (1/2/3, dec/je chain) over locomotor
//   helpers reached through ILTs 0x000230AB/0x00001032/0x0000E52A/0x00002121/
//   0x00002EDC, touching this+0x400/+0x464/+0x468/+0x46C.
// - Tail matches the Zero Hour doLocomotor ending: compare the object's
//   height above terrain against the locomotor template's int height at
//   +0xBC (fild), then Object::setStatusBit(6,1) or Object::clearStatus(6).
// Identity beyond that is unproved, so the owner keeps the address token.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum ObjectStatusTypes
{
	RVA002C12E0_STATUS_6 = 6
};

class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	Overridable *m_nextOverride;
};

template <class T> class OVERRIDE
{
public:
	const T *operator*() const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}

	operator const T *() const { return operator*(); }

private:
	const T *m_overridable;
};

class Rva002C12E0ObjTmpl : public Overridable
{
public:
	char m_pad08[0xc8 - 8];
	unsigned char m_flagC8;
};

class Rva002C12E0LocoTmpl : public Overridable
{
public:
	char m_pad08[0xbc - 8];
	Int m_heightBC;
	char m_padC0[0xcc - 0xc0];
	unsigned char m_flagCC;
};

class Thing
{
public:
	virtual ~Thing();

	float getHeightAboveTerrain() const;
};

class Object : public Thing
{
public:
	const Rva002C12E0ObjTmpl *getTemplate() const { return m_template; }

	void setStatusBit(Int bit, Bool set);
	void clearStatus(ObjectStatusTypes status);

	OVERRIDE<Rva002C12E0ObjTmpl> m_template;
};

class Rva002C12E0Locomotor
{
public:
	Rva002C12E0Locomotor *m_next;

	const Rva002C12E0LocoTmpl *locoTemplate() const { return m_template; }

	float locoSpeed(void *obj);
	unsigned char locoQuery(void *obj, float speed, void *p468, void *p400);
	void locoUpdate2(void *obj, void *p464);
	void locoUpdate1(void *obj);

	OVERRIDE<Rva002C12E0LocoTmpl> m_template;
};

#pragma comment(linker, "/alternatename:?getHeightAboveTerrain@Thing@@QBEMXZ=?j_00001c30@@YAXXZ")
#pragma comment(linker, "/alternatename:?setStatusBit@Object@@QAEXH_N@Z=?j_00032dee@@YAXXZ")
#pragma comment(linker, "/alternatename:?clearStatus@Object@@QAEXW4ObjectStatusTypes@@@Z=?j_00031f7a@@YAXXZ")
#pragma comment(linker, "/alternatename:?helper002BD940@Rva002C12E0Owner@@QAEXXZ=?j_00002edc@@YAXXZ")
#pragma comment(linker, "/alternatename:?chooseGoodLocomotorFromCurrentSet@Rva002C12E0Owner@@QAEXXZ=?j_00036a3e@@YAXXZ")
#pragma comment(linker, "/alternatename:?locoUpdate2@Rva002C12E0Locomotor@@QAEXPAXPAX@Z=?j_0000e52a@@YAXXZ")
#pragma comment(linker, "/alternatename:?locoUpdate1@Rva002C12E0Locomotor@@QAEXPAX@Z=?j_00002121@@YAXXZ")

class Rva002C12E0Owner
{
public:
	int method002C12E0();

	void chooseGoodLocomotorFromCurrentSet();
	void helper002BD940();

	char m_pad00[8];
	Object *m_object;
	char m_pad0C[0x1cc - 0x0c];
	Rva002C12E0Locomotor *m_curLocomotor;
	char m_pad1D0[0x32b - 0x1d0];
	unsigned char m_dead32B;
	char m_pad32C[0x400 - 0x32c];
	void *m_query400;
	char m_pad404[0x60 - 4];
	Int m_goal460;
	void *m_ptr464;
	void *m_field468;
	unsigned char m_byte46C;
};

// ?method002C12E0@Rva002C12E0Owner@@QAEHXZ
int Rva002C12E0Owner::method002C12E0()
{
	const Rva002C12E0ObjTmpl *objTmpl = m_object->getTemplate();
	if (objTmpl->m_flagC8 & 4)
		return UPDATE_SLEEP_FOREVER;

	chooseGoodLocomotorFromCurrentSet();

	Rva002C12E0Locomotor *loco = m_curLocomotor;
	if (loco == 0)
		return UPDATE_SLEEP_NONE;

	if (m_dead32B != 0)
	{
		unsigned char flag = loco->locoTemplate()->m_flagCC;
		if (flag == 0)
			return UPDATE_SLEEP_NONE;
	}

	switch (m_goal460)
	{
	case 1:
	{
		float speed = loco->locoSpeed(m_object);
		loco->locoQuery(m_object, speed, &m_field468, m_query400);
		m_byte46C = *(unsigned char *)&speed;
		break;
	}
	case 2:
		loco->locoUpdate2(m_object, m_ptr464);
		break;
	case 3:
		helper002BD940();
		loco->locoUpdate1(m_object);
		m_byte46C = 1;
		break;
	}

	Rva002C12E0Locomotor *next = loco->m_next;
	if (next == 0)
		return UPDATE_SLEEP_NONE;
	Int height = next->locoTemplate()->m_heightBC;
	Thing *thing = m_object;
	float above = thing->getHeightAboveTerrain();
	Int cmp = height;
	if (cmp < above)
	{
		m_object->setStatusBit(6, true);
		return UPDATE_SLEEP_NONE;
	}
	m_object->clearStatus(RVA002C12E0_STATUS_6);
	return UPDATE_SLEEP_NONE;
}
