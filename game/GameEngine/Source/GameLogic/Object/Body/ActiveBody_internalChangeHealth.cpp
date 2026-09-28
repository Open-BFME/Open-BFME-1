// ActiveBody secondary BodyModuleInterface view, retail RVA002103A0/592B.
// The second stack slot is unused by this body. Both attemptHealing at
// 0020FBC0 and the respawn helper at 002147E0 pass DamageInfo*, proving the
// pointer contract; the older Bool pin only had zero-valued caller evidence.
// Compared with the old bank: revive when previous health equals zero;
// reference-returning max clamps preserve native x87 stores and NaN behavior;
// primary slot48 is called on this-16, not through a loaded receiver pointer;
// slot90 notification is conditional, but effective-dead and linked-body
// synchronization run regardless of damage-state change.
// Quarter factor is a witnessed data read at01083B6C; keeping it separate
// from literal0.75 avoids folding the two retail floating-point operations.
// cl: /DNDEBUG /MD /EHsc
typedef float Real;
typedef bool Bool;
typedef int Int;
class DamageInfo;

#define BfmeZeroRange 0.0f
#define g_bfmeMul1 (*(const float *)0x01083b6c)
#define g_bfmeMul2 0.75f
#define g_bfmeDefaultBU 1.0f

class Object
{
public:
	void setEffectivelyDead(Bool isDead);		// pinned retail 0x00030887
	unsigned char pad[0x90]; unsigned int m_status;
 
};

class GameLogic
{
public:
	Object *findObjectByID(int id);		// pinned retail 0x0001F253
};
extern GameLogic *TheBfmeGameLogic;	// VA 0x012F0898

class BfmeActiveBodySub10 {
public:
#define VP(N) virtual void unused##N();
 VP(00) VP(01) VP(02) VP(03) VP(04) VP(05) VP(06) VP(07) VP(08) VP(09) VP(10) VP(11) VP(12) VP(13) VP(14) VP(15) VP(16) VP(17)
 virtual void setCorrectDamageState(int);
};
inline const float &healthMax(const float &a,const float &b) { return a>b ? a:b; }
class BodyModuleInterface
{
public:
	virtual void pad00(); virtual void pad04(); virtual void pad08(); virtual void pad0C();
	virtual void pad10(); virtual void pad14();
	virtual Real pad18();				// slot 0x18, returns a float seed
	virtual void pad1C(); virtual void pad20(); virtual void pad24(); virtual void pad28();
	virtual void pad2C(); virtual void pad30(); virtual void pad34(); virtual void pad38();
	virtual void pad3C(); virtual void pad40(); virtual void pad44(); virtual void pad48();
	virtual void pad4C(); virtual void pad50(); virtual void pad54(); virtual void pad58();
	virtual void pad5C(); virtual void pad60(); virtual void pad64(); virtual void pad68();
	virtual void pad6C(); virtual void pad70(); virtual void pad74(); virtual void pad78();
	virtual void pad7C();
	virtual void internalChangeHealth(Real delta, DamageInfo *info);
	virtual void setMaxHealth(Real maxHealth, int healthChangeType);
 virtual void pad88(); virtual void pad8c(); virtual void stateChanged();
 virtual void pad94();virtual void pad98();virtual void pad9c();virtual void syncHealth(float,bool);
};

class ActiveBody : public BodyModuleInterface
{
public:
	virtual void internalChangeHealth(Real delta, DamageInfo *info);

private:
	unsigned char m_pad04[4];
	Real m_currentHealth;					// +0x08
	Real m_prevHealth;					// +0x0c
	Real m_maxHealth;					// +0x10
	unsigned char m_pad14[0x20 - 0x14];
	Int m_curDamageState;					// +0x20, unproven
	Int m_unreconstructed_24;
	unsigned char m_pad28[0x9c - 0x28];
	Real m_unreconstructed_9c;
	Real m_unreconstructed_a0;
	Real m_unreconstructed_a4;
	Real m_unreconstructed_a8;
	unsigned char m_pad_ac[0xbc - 0xac];
	Int m_linkedObjectId;					// +0xbc, unproven
};

void ActiveBody::internalChangeHealth(Real delta, DamageInfo *info)
{
	m_prevHealth = m_currentHealth;
	m_currentHealth += delta;

	Real maxHealth = m_maxHealth;
	if (m_currentHealth > maxHealth)
	{
		m_currentHealth = maxHealth;
		m_unreconstructed_9c = 0;
		m_unreconstructed_a0 = 0;
		m_unreconstructed_a4 = 0;
		m_unreconstructed_a8 = 0;
	}
	else
	{
		if (m_prevHealth == BfmeZeroRange)
		{
			Real v = pad18();
			v = v * g_bfmeMul1 * g_bfmeMul2 - g_bfmeDefaultBU;
			m_unreconstructed_9c = v;
			m_unreconstructed_a0 = v;
			m_unreconstructed_a4 = v;
			m_unreconstructed_a8 = v;
		}
		else if (delta > BfmeZeroRange)
		{
			Real reduce = delta * g_bfmeMul1 * g_bfmeMul2;

			m_unreconstructed_9c -= reduce;
			m_unreconstructed_9c = healthMax(0.0f,m_unreconstructed_9c);

			m_unreconstructed_a0 -= reduce;
			m_unreconstructed_a0 = healthMax(0.0f,m_unreconstructed_a0);

			m_unreconstructed_a4 -= reduce;
			m_unreconstructed_a4 = healthMax(0.0f,m_unreconstructed_a4);

			m_unreconstructed_a8 -= reduce;
			m_unreconstructed_a8 = healthMax(0.0f,m_unreconstructed_a8);
		}
	}

	if (m_currentHealth < 0.0f)
		m_currentHealth = 0.0f;

	Int savedState = m_curDamageState;
 Int savedOther = m_unreconstructed_24;
 ((BfmeActiveBodySub10*)((char*)this-16))->setCorrectDamageState(0);
 Object *us = *(Object **)((char *)this - 8);
 if(m_curDamageState != savedState || m_unreconstructed_24 != savedOther) {
  if(m_currentHealth<=0.0f || !(us->m_status&4)) stateChanged();
 }
 us->setEffectivelyDead(m_currentHealth<=0.0f);
 if(m_linkedObjectId) {
  Object *other = TheBfmeGameLogic->findObjectByID(m_linkedObjectId);
  if(other) {
   BodyModuleInterface *body = *(BodyModuleInterface**)((char*)other+0x200);
   if(body) {
    body->syncHealth(m_currentHealth,delta>0.0f);
    *(Int*)((char*)other+0x220)=*(Int*)((char*)*(Object**)((char*)this-8)+0x220);
   }
  }
 }
}
