// ?getPreAttackDelay@Weapon@@QBEHPBVObject@@HH@Z
// partial score=0.86 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;

struct Coord3DBase
{
	float x, y, z;
};

struct Coord3D : public Coord3DBase
{
	bool equals(const Coord3DBase &other) const;
};

union BfmeFiringPositionWord
{
	float f;
	volatile UnsignedInt u;
};

struct BfmeFiringPosition
{
	BfmeFiringPosition() {}
	BfmeFiringPosition(const BfmeFiringPosition &other)
	{
		x.u = other.x.u;
		y.u = other.y.u;
		z.u = other.z.u;
	}

	BfmeFiringPositionWord x, y, z;
};

class ObjectFilter
{
public:
	bool isValid() const;

private:
	char m_fields[12];
};

class Object;

class AIUpdateInterface
{
public:
#define UNUSED_AI_SLOT(n) virtual void unused##n() = 0;
	UNUSED_AI_SLOT(00) UNUSED_AI_SLOT(01) UNUSED_AI_SLOT(02) UNUSED_AI_SLOT(03)
	UNUSED_AI_SLOT(04) UNUSED_AI_SLOT(05) UNUSED_AI_SLOT(06) UNUSED_AI_SLOT(07)
	UNUSED_AI_SLOT(08) UNUSED_AI_SLOT(09) UNUSED_AI_SLOT(10) UNUSED_AI_SLOT(11)
	UNUSED_AI_SLOT(12) UNUSED_AI_SLOT(13) UNUSED_AI_SLOT(14) UNUSED_AI_SLOT(15)
	UNUSED_AI_SLOT(16) UNUSED_AI_SLOT(17) UNUSED_AI_SLOT(18) UNUSED_AI_SLOT(19)
	UNUSED_AI_SLOT(20) UNUSED_AI_SLOT(21) UNUSED_AI_SLOT(22) UNUSED_AI_SLOT(23)
	UNUSED_AI_SLOT(24) UNUSED_AI_SLOT(25) UNUSED_AI_SLOT(26) UNUSED_AI_SLOT(27)
	UNUSED_AI_SLOT(28) UNUSED_AI_SLOT(29) UNUSED_AI_SLOT(30) UNUSED_AI_SLOT(31)
	UNUSED_AI_SLOT(32) UNUSED_AI_SLOT(33) UNUSED_AI_SLOT(34) UNUSED_AI_SLOT(35)
	UNUSED_AI_SLOT(36) UNUSED_AI_SLOT(37) UNUSED_AI_SLOT(38) UNUSED_AI_SLOT(39)
	UNUSED_AI_SLOT(40) UNUSED_AI_SLOT(41) UNUSED_AI_SLOT(42) UNUSED_AI_SLOT(43)
	UNUSED_AI_SLOT(44) UNUSED_AI_SLOT(45) UNUSED_AI_SLOT(46) UNUSED_AI_SLOT(47)
	UNUSED_AI_SLOT(48) UNUSED_AI_SLOT(49) UNUSED_AI_SLOT(50) UNUSED_AI_SLOT(51)
	UNUSED_AI_SLOT(52) UNUSED_AI_SLOT(53) UNUSED_AI_SLOT(54) UNUSED_AI_SLOT(55)
	UNUSED_AI_SLOT(56) UNUSED_AI_SLOT(57) UNUSED_AI_SLOT(58) UNUSED_AI_SLOT(59)
	UNUSED_AI_SLOT(60) UNUSED_AI_SLOT(61) UNUSED_AI_SLOT(62) UNUSED_AI_SLOT(63)
#undef UNUSED_AI_SLOT
	virtual UnsignedInt getShotCount(const ObjectFilter *filter) = 0;
};

class Object
{
public:
	BfmeFiringPosition bfmeGetLastShotPosition() const;
	AIUpdateInterface *getAI() const { return m_ai; }

	char m_fields[0x38];
	Coord3DBase m_position;
	char m_fields44[0x1fc - 0x44];
	AIUpdateInterface *m_ai;
};

class Gen_001BF950
{
public:
	int bfmeForward(void *arg1, void *arg2);
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

struct WeaponBonus
{
	WeaponBonus()
	{
		m_values[0] = 1.0f;
		m_values[1] = 1.0f;
		m_values[2] = 1.0f;
		m_values[3] = 1.0f;
		m_values[4] = 1.0f;
		m_values[5] = 1.0f;
	}

	float m_values[6];
};

struct WeaponTemplate
{
	char m_fields[0x4ac];
	int m_clipSize;
	char m_fields4b0[0x4e8 - 0x4b0];
	ObjectFilter m_shotCountFilter;
	int m_prefireType;
	char m_fields4f8[8];
	int m_preAttackDelay;
};

class Weapon
{
public:
	int getPreAttackDelay(const Object *source, int arg2, int arg3) const;

private:
	void computeBonus(const Object *source, UnsignedInt extra,
		WeaponBonus &bonus) const;

	void *m_vtable;
	WeaponTemplate *m_template;
	int m_ownerID;
	int m_weaponSlot;
	int m_status;
	int m_ammoInClip;
	char m_fields18[0x58 - 0x18];
	int m_preAttackJitter;
};

int Weapon::getPreAttackDelay(const Object *source, int arg2, int arg3) const
{
	int type = m_template->m_prefireType;
	if (type == 2)
	{
		if (m_template->m_clipSize > 0)
		{
			UnsignedInt shotCount;
			if (m_template->m_shotCountFilter.isValid())
			{
				Object *owner = TheGameLogic->findObjectByID(m_ownerID);
				AIUpdateInterface *ai = owner ? owner->getAI() : 0;
				if (ai)
					shotCount = ai->getShotCount(&m_template->m_shotCountFilter);
				else
					shotCount = m_ammoInClip;
			}
			else
			{
				shotCount = m_ammoInClip;
			}

			if (shotCount < static_cast<UnsignedInt>(m_template->m_clipSize))
				return 0;
		}
	}
	else if (type == 1)
	{
		if (reinterpret_cast<Gen_001BF950 *>(const_cast<Object *>(source))->
			bfmeForward(reinterpret_cast<void *>(arg2),
				reinterpret_cast<void *>(arg3)) > 0)
		{
			return 0;
		}
	}
	else if (type == 3)
	{
		BfmeFiringPosition last = source->bfmeGetLastShotPosition();
		if (reinterpret_cast<const Coord3D *>(&last)->equals(source->m_position))
			return 0;
	}

	WeaponBonus bonus;
	computeBonus(source, 0, bonus);
	return static_cast<int>(m_template->m_preAttackDelay * bonus.m_values[4])
		+ m_preAttackJitter;
}
