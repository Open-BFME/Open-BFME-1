// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AutoHealBehavior::pulseHealObject, retail 0x001EECB0 size 121.
// Same +4/+8/+0x2C/+0x30 facade as the landed onDamage body. BFME adds
// Object::bfmeGetBonus(0x11) onto the module-data healing amount and truncates
// through __ftol2 before the Object vcalls at +0x40/+0x44. Particle pulse is
// not in this 121B body. Focused TU -- do not fold into AutoHealBehavior.cpp.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

class Object;
class GameLogic
{
public:
	unsigned char m_pad[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void attemptHealing(Real amount, const Object *source);
	virtual Bool attemptHealingFromSoleBenefactor(
		Real amount, const Object *source, UnsignedInt duration);

	Bool bfmeGetBonus(Int kind, Real *out) const;
};

struct AutoHealBehaviorModuleData
{
	unsigned char m_pad_000[0x74];
	Int m_healingAmount;
	UnsignedInt m_healingDelay;
	UnsignedInt m_startHealingDelay;
	UnsignedInt m_radius;
};

class AutoHealBehavior
{
public:
	void pulseHealObject(Object *obj);

private:
	void *m_vtable;
	const AutoHealBehaviorModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad_00C[0x2C - 0x0C];
	UnsignedInt m_soonestHealFrame;
	Bool m_stopped;
};

// ?pulseHealObject@AutoHealBehavior@@QAEXPAVObject@@@Z
void AutoHealBehavior::pulseHealObject(Object *obj)
{
	if (m_stopped)
		return;

	const AutoHealBehaviorModuleData *data = m_moduleData;
	Real bonus;
	m_object->bfmeGetBonus(0x11, &bonus);
	Int truncated = (Int)((Real)data->m_healingAmount + bonus);
	if (data->m_radius == 0)
		obj->attemptHealing((Real)truncated, m_object);
	else
		obj->attemptHealingFromSoleBenefactor((Real)truncated, m_object, data->m_healingDelay);

	m_soonestHealFrame = TheGameLogic->m_frame + data->m_healingDelay;
}
