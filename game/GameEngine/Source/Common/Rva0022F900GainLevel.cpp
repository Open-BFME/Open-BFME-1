// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0022F900. If the object has a drawable, run bfmeGo1057A(0x19)
// on it, then ExperienceLevelSystem::gainLevel and a two-arg this continuation.

class Drawable
{
};

class Object
{
public:
	virtual void objectSlot00() = 0;
	virtual void objectSlot04() = 0;
	virtual void objectSlot08() = 0;
	virtual void objectSlot0c() = 0;
	virtual void objectSlot10() = 0;
	virtual void objectSlot14() = 0;
	virtual void objectSlot18() = 0;
	virtual void objectSlot1c() = 0;
	virtual void objectSlot20() = 0;
	virtual void objectSlot24() = 0;
	virtual Drawable *getDrawable() const = 0;
};

class BfmeA1057
{
public:
	void bfmeGo1057A(int value);
};

class ExperienceLevelSystem
{
public:
	void gainLevel(Object *obj, bool showFx);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

class Gen_0022F900
{
public:
	void bfmeGain(Object *obj, void *extra);
};

// The second half of the retail body calls through ILT 0x00047EE7, the
// 5-byte thunk in front of the body at 0x0023F1A0.  That thunk symbol is the
// only name defined at the call target, so reference it here; the
// member-pointer view types the call thiscall (ecx = this, obj and extra
// pushed, popped by the callee) without defining another Gen_0022F900.
extern "C" void __identifier("?j_00047ee7@@YAXXZ")();

// ?bfmeGain@Gen_0022F900@@QAEXPAVObject@@PAX@Z
void Gen_0022F900::bfmeGain(Object *obj, void *extra)
{
	if (obj->getDrawable() != 0)
		((BfmeA1057 *)obj->getDrawable())->bfmeGo1057A(0x19);
	TheExperienceLevelSystem->gainLevel(obj, true);
	union {
		void (*thunk)();
		void (Gen_0022F900::*method)(Object *, void *);
	} after;
	after.thunk = &__identifier("?j_00047ee7@@YAXXZ");
	(this->*after.method)(obj, extra);
}
