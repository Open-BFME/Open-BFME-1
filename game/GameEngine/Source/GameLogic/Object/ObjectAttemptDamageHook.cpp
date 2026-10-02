// ?apply@ObjectAttemptDamageHook@@QAEXPAVDamageInfo@@@Z
// Retail 0x001CDE30, 825 bytes. Object::attemptDamage (0x001D0490) calls it
// through ILT 0x0001491B under the pinned name above. The body lives in
// Object.cpp: its GameLogicRandomValueReal calls pass that file (literal
// 0x0109EC20) and lines 3673 and 3682. It clears drawable+0x2EC, plays the
// drawable's sound slot 0x6B, then applies a physics shock scaled by the
// damage direction. The shock sets model condition 120, and a unit in AI
// state 0x2D is killed. The drawable reacts last. The method's real name is
// unrecovered, so the caller's pinned spelling stays; ObjectAttemptDamageHook
// is a view of Object with the same layout.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/GameLogic/Object
// stlport

struct Coord3D
{
	float x, y, z;
	float length() const;
	void normalize();
	void scale(float s) { x *= s; y *= s; z *= s; }
};

enum ObjectID { INVALID_ID = 0 };
enum DamageType { DAMAGE_00001CDE30_8 = 8 };
enum DeathType { DEATH_00001CDE30_0 = 0 };
enum AIStateType { AI_STATE_00001CDE30_2D = 0x2d };

#include <bitset>
class ModelConditionFlags
{
public:
	bool test(int bit) const { return m_bits.test(bit); }
	void set(int bit) { m_bits.set(bit); }
private:
	_STL::bitset<320> m_bits;
};

class AttributeModifierPoolUpdate;
class ObjectAttemptDamageHook;

#define BFME_HAVE_OBJECTID
#define BFME_HAVE_MODELCONDITIONFLAGS
#define BFME_HAVE_COORD3D
#define OBJECT_TU_MEMBERS \
	void kill(DamageType damageType, DeathType deathType); \
	friend class ObjectAttemptDamageHook; \
private: \
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
#include "object.h"

class DamageInfo
{
public:
	unsigned char m_pad00[8];
	int m_sourceID008;
	unsigned char m_pad0C[0x1c];
	unsigned int m_word028;
	unsigned char m_pad2C[4];
	Coord3D m_direction030;
	float m_amount03C;
	float m_amount040;
	float m_amount044;
	float m_amount048;
};

struct ReactionInfo0041EBD0;

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &right);
	~AudioEventRTS();
	void setObjectID(ObjectID objectID);
private:
	unsigned char m_data[0x70];
};

extern void j_0001bfd1(void);
extern void j_0002a284(void);
extern void j_0001b94b(void);
extern void j_00017a26(void);

class Drawable
{
public:
	const AudioEventRTS *sound0041AFA0(int index)
	{
		union { void *raw; const AudioEventRTS *(Drawable::*fn)(int); } u;
		u.raw = (void *)j_0001bfd1;
		return (this->*u.fn)(index);
	}
	void replaceModelConditionState(const ModelConditionFlags &flags, unsigned int a, unsigned int b);
	void react0041EBD0(const ReactionInfo0041EBD0 *info);

	unsigned char m_pad000[0x2ec];
	int m_field2EC;
};

class AudioManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16();
	virtual unsigned int addAudioEvent(const AudioEventRTS *eventToAdd);
};
extern AudioManager *TheAudio;

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad008[0x4a8];
	bool m_flag4B0;
};

class PhysicsBehavior
{
public:
	void rva0029A7D0();
	void rva0029A6A0(bool flag);
	void applyShock0029AC40(const Coord3D *force)
	{
		union { void *raw; void (PhysicsBehavior::*fn)(const Coord3D *); } u;
		u.raw = (void *)j_0002a284;
		(this->*u.fn)(force);
	}
	unsigned char m_pad00[0x5c];
	bool m_flag5C;
};

class AttributeModifierPoolUpdate
{
public:
	bool getAttributeModifierBonus(int type, float *bonus);
};

#define AI_SLOTS8(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); virtual void p##5(); virtual void p##6(); virtual void p##7();
class AIUpdateInterface
{
public:
	AI_SLOTS8(a) AI_SLOTS8(b) AI_SLOTS8(c) AI_SLOTS8(d) AI_SLOTS8(e) AI_SLOTS8(f) AI_SLOTS8(g) AI_SLOTS8(h)
	AI_SLOTS8(i) AI_SLOTS8(j) AI_SLOTS8(k) AI_SLOTS8(l) AI_SLOTS8(m) AI_SLOTS8(n) AI_SLOTS8(o) AI_SLOTS8(p)
	AI_SLOTS8(q)
	virtual void r0();
	virtual void slot224();
	virtual void friend_notifyStateMachineChanged();
	AIStateType getAIStateType() const;
};

class BodyModuleInterface
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
	virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
	virtual void b08(); virtual void b09(); virtual void b10(); virtual void b11();
	virtual void b12(); virtual void b13(); virtual void b14();
	virtual const DamageInfo *getLastDamageInfo() const;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};
extern GameLogic *TheGameLogic;

float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);

class ObjectAttemptDamageHook : public Object
{
public:
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() const { return m_ai; }
	void apply(DamageInfo *damageInfo);

private:
	const ThingTemplate *getFinalTemplate() const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride)
			return (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
		return tmpl;
	}
	__forceinline void setModelConditionState(int bit)
	{
		if (!m_modelConditionFlags.test(bit))
		{
			m_modelConditionFlags.set(bit);
			if (m_drawable)
				m_drawable->replaceModelConditionState(m_modelConditionFlags, 0, 0);
			if (m_ai)
				m_ai->AIUpdateInterface::friend_notifyStateMachineChanged();
		}
	}
	void touch001C9490(Object *damaged, bool flag)
	{
		union { void *raw; void (ObjectAttemptDamageHook::*fn)(Object *, bool); } u;
		u.raw = (void *)j_0001b94b;
		(this->*u.fn)(damaged, flag);
	}
	void copy001BE200(unsigned int value)
	{
		union { void *raw; void (ObjectAttemptDamageHook::*fn)(unsigned int); } u;
		u.raw = (void *)j_00017a26;
		(this->*u.fn)(value);
	}
};

template <class T> inline const T &minOf(const T &a, const T &b) { return b < a ? b : a; }

void ObjectAttemptDamageHook::apply(DamageInfo *damageInfo)
{
	if (m_drawable)
		m_drawable->m_field2EC = 0;

	Drawable *draw = getDrawable();

	if (damageInfo->m_amount03C > 0.0f && damageInfo->m_amount040 > 0.0f)
	{
		PhysicsBehavior *physics = m_physics;
		if (physics && !physics->m_flag5C)
		{
			if (draw)
			{
				AudioEventRTS sound(*draw->sound0041AFA0(0x6b));
				sound.setObjectID(getID());
				TheAudio->addAudioEvent(&sound);
			}

			if (getFinalTemplate()->m_flag4B0)
			{
				physics->rva0029A7D0();
			}
			else
			{
				float bonus;
				AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
				if (pool)
					pool->getAttributeModifierBonus(9, &bonus);
				if (bonus >= 1.0f)
					return;

				const Coord3D *direction = &damageInfo->m_direction030;
				float ratio = direction->length() / damageInfo->m_amount040;
				float strength = 1.0f - (1.0f - damageInfo->m_amount044) * minOf(ratio, 1.0f);
				float random = GetGameLogicRandomValueReal(0.85f, 1.15f,
					"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Object.cpp", 3673);
				Coord3D force = *direction;
				force.normalize();
				force.scale(random * damageInfo->m_amount03C * strength);
				random = GetGameLogicRandomValueReal(0.85f, 1.15f,
					"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Object.cpp", 3682);
				force.z = force.length() * damageInfo->m_amount048 * random;

				setModelConditionState(120);
				physics->rva0029A6A0(true);
				if (force.z < 0.0f)
					force.z = -force.z;
				physics->applyShock0029AC40(&force);

				if (m_ai && m_ai->getAIStateType() == AI_STATE_00001CDE30_2D)
				{
					int sourceID = m_body->getLastDamageInfo() ? m_body->getLastDamageInfo()->m_sourceID008 : 0;
					Object *source = TheGameLogic->findObjectByID(sourceID);
					if (source && (m_privateStatus & 1) == 0)
						((ObjectAttemptDamageHook *)source)->touch001C9490(this, true);
					kill(DAMAGE_00001CDE30_8, DEATH_00001CDE30_0);
					kill(DAMAGE_00001CDE30_8, DEATH_00001CDE30_0);
				}
				AIUpdateInterface *ai = getAI();
				if (ai)
					ai->slot224();
				copy001BE200(damageInfo->m_word028);
			}
		}
	}

	if (draw)
		draw->react0041EBD0((const ReactionInfo0041EBD0 *)damageInfo);
}
