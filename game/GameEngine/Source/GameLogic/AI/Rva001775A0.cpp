// ?method@Rva001775A0@@QAE?AW4StateReturnType@@XZ
// cl: /DNDEBUG /MD
//
// Retail 0x001775A0. No owning state class is proven, so both the type and
// entry point retain the address. The +0x44 virtual call is kept as an opaque
// slot; the final qualified call uses the same receiver as the tail jump to
// AIInternalMoveToState::onEnter, without asserting that this type derives from it.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum CrushSquishTestType
{
	TEST_CRUSH_ONLY,
	TEST_SQUISH_ONLY,
	TEST_CRUSH_OR_SQUISH
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;							// +0x00
	const Overridable *m_nextOverride;			// +0x04
};

class AIUpdateInterface
{
public:
	void destroyPath();
};

class Object
{
public:
	bool crushPolicy(Object *other, CrushSquishTestType testType) const;
	void setStatusBit(int bit, bool set);

	void *m_vtable;							// +0x00
	const Overridable *m_template;			// +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position;						// +0x38
	unsigned char m_pad044[0x204 - 0x44];
	AIUpdateInterface *m_ai;					// +0x204
};

class StateMachine
{
public:
	Object *getGoalObject();

	void *m_vtable;							// +0x00
	unsigned char m_pad004[0x10 - 0x04];
	Object *m_owner;							// +0x10
	unsigned char m_pad014[0x20 - 0x14];
	int m_goalObjectID;						// +0x20
};

// The helper's recovered declaration and +0x20 id layout are in
// BfmeConv1024.cpp; this receiver is the state-machine pointer at this+0x1c.
class BfmeF1024
{
public:
	char bfmeGo1024F();

	unsigned char m_pad000[0x20];
	int m_bfmeId;							// +0x20
};

// Recovered helper signature in Bfme5TinyTwentyFive.cpp.
class Gen_0029A7A0
{
public:
	bool bfmeFlagged() const;
	unsigned int m_bfmeHead[2];
	void *m_bfmeOwner;						// +0x08
};

class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a();
typedef void (__cdecl *Rva001775A0CritterLog)(void *, const char *, ...);

class Rva001775A0
{
public:
	virtual void rvaSlot00() = 0;
	virtual void rvaSlot01() = 0;
	virtual void rvaSlot02() = 0;
	virtual void rvaSlot03() = 0;
	virtual void rvaSlot04() = 0;
	virtual void rvaSlot05() = 0;
	virtual void rvaSlot06() = 0;
	virtual void rvaSlot07() = 0;
	virtual void rvaSlot08() = 0;
	virtual void rvaSlot09() = 0;
	virtual void rvaSlot10() = 0;
	virtual void rvaSlot11() = 0;
	virtual void rvaSlot12() = 0;
	virtual void rvaSlot13() = 0;
	virtual void rvaSlot14() = 0;
	virtual void rvaSlot15() = 0;
	virtual void rvaSlot16() = 0;
	virtual bool rvaSlot17() = 0;

	StateReturnType method();

private:
	unsigned char m_pad004[0x1c - 0x04];
	StateMachine *m_field1c;					// +0x1c
	unsigned char m_pad020[0x4c - 0x20];
	unsigned char m_field4c;					// +0x4c
	unsigned char m_pad04d[0x50 - 0x4d];
	unsigned int m_field50;					// +0x50
	Coord3D m_field54;						// +0x54
};

StateReturnType Rva001775A0::method()
{
	StateMachine *machine = m_field1c;
	Object *owner = machine->m_owner;

	if (((*((const unsigned char *)owner + 0x98) & 8) == 0) &&
		(*((const unsigned char *)owner->m_ai + 0x33a) == 0))
	{
		const Overridable *objectTemplate = owner->m_template;
		if (objectTemplate != 0 && objectTemplate->m_nextOverride != 0)
			objectTemplate = objectTemplate->m_nextOverride->getFinalOverride();
		if (((const unsigned char *)objectTemplate)[0x49d] != 0)
		{
			if (((BfmeF1024 *)machine)->bfmeGo1024F() == 0)
			{
				if (g_012F0239 && g_012ED4FC)
					((Rva001775A0CritterLog)j_0003a17a)(g_012ED4FC,
						(const char *)0x0109964c);

				m_field4c = 0;
				m_field50 = 0;

				Object *goal = m_field1c->getGoalObject();
				if (goal != 0)
				{
					Gen_0029A7A0 *goalFlag =
						*(Gen_0029A7A0 **)((unsigned char *)goal + 0x208);
					if (goalFlag == 0 || !goalFlag->bfmeFlagged())
					{
						if (owner->crushPolicy(goal, TEST_CRUSH_OR_SQUISH))
						{
							m_field54 = goal->m_position;
							owner->m_ai->destroyPath();

							if (g_012F0239 && g_012ED4FC)
								((Rva001775A0CritterLog)j_0003a17a)(g_012ED4FC,
									(const char *)0x01099628);

							if (rvaSlot17())
							{
								owner->setStatusBit(0x1c, true);
								return ((AIInternalMoveToState *)this)
									->AIInternalMoveToState::onEnter();
							}
						}
					}
					else
						goto failure;
				}
				else
					goto failure;
			}
			else
				goto failure;
		}
	}

	goto success;
failure:
	return STATE_FAILURE;
success:
	return STATE_SUCCESS;
}
