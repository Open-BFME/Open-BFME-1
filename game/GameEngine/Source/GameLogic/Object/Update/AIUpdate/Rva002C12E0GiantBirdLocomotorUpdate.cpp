// cl: /DNDEBUG /MD /EHsc
// Retail 0x002C12E0 (322 B, thiscall, returns int): GiantBirdAIUpdate vtable 0x010C7F40 slot 133 (+0x214) reaches it through ILT 0x0002A31F.
// Picks a locomotor, runs the goal-type 1/2/3 locomotor update unless dead without the template flag, then sets or clears status bit 6 by airborne height.

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

	unsigned char locoQuery(void *obj, float speed, void *p468, void *p400);
	void locoUpdate2(void *obj, void *p464);
	void locoUpdate1(void *obj);

	OVERRIDE<Rva002C12E0LocoTmpl> m_template;
};

class BfmeSub1CC_EC3
{
public:
	float effectiveMaxSpeed(void *obj);
};

class AIUpdateInterface
{
	friend class Rva002C12E0Owner;

protected:
	void chooseGoodLocomotorFromCurrentSet();
};

class Rva002C12E0Owner
{
public:
	int method002C12E0();

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

	((AIUpdateInterface *)this)->chooseGoodLocomotorFromCurrentSet();
	Rva002C12E0Locomotor *loco = m_curLocomotor;
	if (loco)
	{
		if (m_dead32B && !loco->locoTemplate()->m_flagCC)
		{
		}
		else
		{
			switch (m_goal460)
			{
			case 1:
			{
				float speed = ((BfmeSub1CC_EC3 *)loco)->effectiveMaxSpeed(m_object);
				Object *obj = m_object;
				m_byte46C = loco->locoQuery(obj, speed, &m_field468, &m_query400);
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
			Thing *thing = m_object;
			Int height = loco->locoTemplate()->m_heightBC;
			if (thing->getHeightAboveTerrain() > height)
				m_object->setStatusBit(6, true);
			else
				m_object->clearStatus(RVA002C12E0_STATUS_6);
		}
	}
	return UPDATE_SLEEP_NONE;
}
