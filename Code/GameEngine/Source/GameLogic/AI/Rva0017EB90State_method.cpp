// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <bitset>

enum ObjectStatusTypes
{
	OBJECT_STATUS_38 = 0x38
};

enum DamageType
{
	DAMAGE_TYPE_8 = 8
};

enum DeathType
{
	DEATH_TYPE_0 = 0
};

class Rva0017EB90ConditionBits
{
public:
	bool test(int bit) const { return m_bits.test(bit); }
	void set(int bit) { m_bits.set(bit); }

private:
	_STL::bitset<320> m_bits;
};

class Rva0017EB90StateData;

class Object
{
public:
	void clearStatus(ObjectStatusTypes status);
	void notifyModelConditionChanged();
	void kill(DamageType damage, DeathType death);

	unsigned char m_bfmeHead[0x110];
	Rva0017EB90ConditionBits m_bfmeFlags;
	unsigned char m_bfmePad[0xcc];
	Rva0017EB90StateData *m_bfmeState;
};

class Gen001C9AC0
{
public:
	void handle(int value);
};

class Rva0017EB90StateMachine
{
public:
	unsigned char m_bfmeHead[0x10];
	Object *m_bfmeOwner;
};

class Rva0017EB90State
{
public:
	void method(void *unused);

	unsigned char m_bfmeHead[0x1c];
	Rva0017EB90StateMachine *m_bfmeMachine;
};

class Rva0017EB90StateData
{
public:
	unsigned char m_bfmeHead[0x333];
	unsigned char m_bfmeA;
	unsigned char m_bfmeB;
};

static __forceinline void markState(Object *object)
{
	if (!object->m_bfmeFlags.test(124))
	{
		object->m_bfmeFlags.set(124);
		object->notifyModelConditionChanged();
	}
}

void Rva0017EB90State::method(void *unused)
{
	Object *obj = m_bfmeMachine->m_bfmeOwner;

	if (obj == 0)
		return;

	Rva0017EB90StateData *state = (Rva0017EB90StateData *)obj->m_bfmeState;

	if (state == 0)
		return;

	obj->clearStatus(OBJECT_STATUS_38);
	((Gen001C9AC0 *)obj)->handle(8);

	state->m_bfmeA = 0;
	state->m_bfmeB = 0;

	markState(obj);

	obj->kill(DAMAGE_TYPE_8, DEATH_TYPE_0);
}
